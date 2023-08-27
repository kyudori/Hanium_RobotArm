import serial

com = serial.Serial(port = "/dev/ttyACM0",
		baudrate = 9600,
		bytesize = serial.EIGHTBITS,
		parity = serial.PARITY_NONE,
		timeout = 1)
s = "TEST CODE"
com.write(s.encode())