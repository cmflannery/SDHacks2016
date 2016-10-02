#include <xxtea-iot-crypt.h>

void setup() {
  Serial.begin(115200);
}

void encrypt() {
  Serial.println();

  String keybuf = F("Hello Password");
  Serial.print(F(" Password : "));
  Serial.println(keybuf);

  // Setup the Key - Once
  if (!xxtea.setKey(keybuf))
  {
    Serial.println(" Assignment Failed!");
    return;
  }

  String plaintext = F("32.8856, -117.2395");
  Serial.print(" Plain Text: ");
  Serial.println(plaintext);

  // Perform Encryption on the Data
  String result = xxtea.encrypt(plaintext);
  if (result == F("-FAIL-"))
  {
    Serial.println(" Encryption Failed!");
    return;
  }
  else
  {
    Serial.print(F(" Encrypted Data: "));
    Serial.println(result);
  }

  // Perform Decryption
  String result1 = xxtea.decrypt(result);
  if (result1 == F("-FAIL-"))
  {
    Serial.println(" Decryption Failed!");
    return;
  }
  else
  {
    Serial.print(F(" Decrypted Data: "));
    Serial.println(result1);
  }
  delay(1000);
}
