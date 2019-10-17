#Import
import RPi.GPIO as GPIO
from time import sleep
import serial
import json




#Functions

def writeJSON(data):
    with open('/var/www/html/lib/js/json.js', 'w') as outfile:
        json.dump(data, outfile)
    print(data)
    
def readLine(port):
    s = ""
    while True:
        ch = port.read()
        s += ch
        if ch == '\n':
            return s

def readAnalogPin(n):
    return UseArduino('A'+str(n))

def rwDigitalPin(n):
    return UseArduino('D'+n)

def readTemperature():
    return UseArduino('T1')

def UseArduino(cmd):
    if ser.isOpen():
        try:
            ser.write(cmd+'\n')
            readLine(ser)
            return(readLine(ser))
        except Exception:
            print ("error communicating...: " + str())
    else:
        print ("cannot open serial port ")

    

#General config
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#GPIO setup
GPIO.setup(2,GPIO.OUT)
GPIO.setup(3,GPIO.IN)

#Serial setup
ser = serial.Serial( port='/dev/ttyACM0',
         baudrate=9600,
         bytesize=serial.EIGHTBITS,
         parity=serial.PARITY_NONE,
         timeout=2)
#ser.open()
sleep(5)
try:

    print ("Serial port is open")
    ser.isOpen()

except Exception:

    print ("error open serial port: " + str(e))

    exit()


#Main loop
print("Starting Loop...")
while True:
    values = readTemperature()
    split = values.find("/")
    humidity = values[0:split]
    temp = values[split+1:len(values)-2]
    light = readAnalogPin(0)

    data = {}
    data['values'] = []

    data['values'].append({
        'humidity': humidity,
        'temp': temp,
        'light': light[0:light.find("#")]
    })

    writeJSON(data)

    sleep(5)



#End routine
GPIO.cleanup()
exit()
