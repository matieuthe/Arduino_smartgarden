import serial, time, urllib2

#Connection to the USB
arduino = serial.Serial('/dev/cu.usbmodem1431', 9600, timeout=.1)
time.sleep(1)

statutTap = 0
arduino.write(statutTap)
while True:
    #time between each loop
    time.sleep(1)
    #Check if the arduino send data
    data = arduino.readline()
    if data:
        #if data are send, we upload it to website
        response = urllib2.urlopen("http://localhost:8888/projet/api/uploadHumidity.php?humidity=" + str(data))
        #print data
    else:
        #We check statut of the tap and if he need to be start
        response = urllib2.urlopen("http://localhost:8888/projet/api/getLimit.php")
        lineRep = response.readline()
        if lineRep != statutTap :
            statutTap = lineRep
            arduino.write(statutTap)