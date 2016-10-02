// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#include <xxtea-iot-crypt.h>

// If you're using a GPS module:
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// If using software serial (sketch example default):
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3

// If you're using the Adafruit GPS shield, change
// SoftwareSerial mySerial(3, 2); -> SoftwareSerial mySerial(8, 7);
// and make sure the switch is set to SoftSerial

// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2);

// If using hardware serial (e.g. Arduino Mega), comment out the
// above SoftwareSerial line, and enable this line instead
// (you can change the Serial number to match your wiring):

//HardwareSerial mySerial = Serial1;


Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences.
#define GPSECHO false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

int d = 0; // user input while condition
int incomingByte = 0;   // for incoming serial data
int e = 0;
float latitude, longitude;
char buf1[25], buf2[25];

void setup()
{

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("GPS lat/long output!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

//  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}


void loop() {
  userInput();
  GPS_data();
  GPS_write();
  encrypt();
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
  // writing direct to UDR0 is much much faster than Serial.print
  // but only one character can be written at a time.
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void userInput() { // wait for user inu=put before taking GPS data
  d = 0;
  //Serial.println("Write y: ");

  while (d == 0) {
    // Wait for user input
    if (Serial.available() > 0) {
      incomingByte = Serial.read();

      if (incomingByte == 121) {
        //Serial.println("Input Accepted");
        d = 1;
      } else {
        Serial.println("Input denied.");
      }
    }
  }
}

void GPS_data() {
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
}

void GPS_write() {
  if (GPS.fix) {
    latitude = GPS.latitudeDegrees;
    longitude = GPS.longitudeDegrees;
    //    Serial.print(GPS.latitudeDegrees, 4);
    //    Serial.print(", ");
    //    Serial.println(GPS.longitudeDegrees, 4);
    e = 0;
  } else {
    Serial.println("no fix");
    e = 1;
  }
}

void encrypt() {
  String keybuf = F("Hello Password");
  //  Serial.print(F(" Password : "));
  //  Serial.println(keybuf);

  // Setup the Key - Once
  if (!xxtea.setKey(keybuf))
  {
    Serial.println(" Assignment Failed!");
    return;
  }

  String lat1 = dtostrf(latitude, 4, 4, buf1);
  String long1 = dtostrf(longitude, 4, 4, buf2);
  String plaintext =  lat1 + ", " + long1;
  //  Serial.print(" Plain Text: ");
  //  Serial.println(plaintext);

  // Perform Encryption on the Data
  String result = xxtea.encrypt(plaintext);
  if (result == "-FAIL-")
  {
    Serial.println(" Encryption Failed!");
    return;
  }
  else if (e == 0)
  {
    //    Serial.print(" Encrypted Data: ");
    Serial.println(result);
  }

  //  // Perform Decryption
  //  String result1 = xxtea.decrypt(result);
  //  if (result1 == "-FAIL-")
  //  {
  //    Serial.println(" Decryption Failed!");
  //    return;
  //  }
  //  else
  //  {
  //    Serial.print(" Decrypted Data: ");
  //    Serial.println(result1);
  //  }
  //  delay(1000);
}
