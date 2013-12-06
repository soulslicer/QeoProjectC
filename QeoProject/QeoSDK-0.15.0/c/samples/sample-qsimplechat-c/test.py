import serial

ser=serial.Serial("/dev/ttyAMA0")
ser.baudrate=9600
ser.port=0
print ser.name
ser.write("hello")
ser.close()
