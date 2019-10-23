#Import
import RPi.GPIO as GPIO
from time import sleep
import serial
import json
from datetime import datetime
import sqlite3





#Functions

def getData():

    DHTvalues = readTemperature()
    split = DHTvalues.find("/")
    humidity = DHTvalues[0:split]
    temp = DHTvalues[split+1:len(DHTvalues)-2]
    light = readAnalogPin(0)

    data = "(" + temp + "," + humidity + "," + light[0:light.find("#")] + ");"

    writeSQL(data)

    #data = {}
    #data['values'] = []

    #data['values'].append({
    #    'humidity': humidity,
    #    'temp': temp,
    #    'light': light[0:light.find("#")]
    #})
    #with open('/var/www/html/lib/js/json.js', 'a+') as outfile:
    #    json.dump(data, outfile)
    #print(data)

def writeSQL(data):

    connection = sqlite3.connect("farmbot.db")

    cursor = connection.cursor()

    sql_command = "INSERT INTO farmbot (temp, humidity, light) VALUES  %s" % data
    print(sql_command)
    cursor.execute(sql_command)
    
    connection.commit()

    connection.close()
    
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
    

    getData()

    sleep(10)




#End routine
GPIO.cleanup()
exit()
