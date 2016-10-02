import serial

# ser = serial.Serial('/dev/ttyS0', 9600)
ser = serial.Serial(port='/dev/ttyS0', baudrate=9600, timeout=2000, parity=serial.PARITY_EVEN, rtscts=1)
