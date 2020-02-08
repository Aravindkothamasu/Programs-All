#!/usr/bin/env python

import RPi.GPIO as GPIO
import array as arr
import time
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()

ide = [660020036596,308090068794,908477334317,578417205842]
name= ["aravind","aravind","Adithya","abcdef"]

e=" "
buf=" "
fileDes=0
res = [True]*4
Status = 0
i = 0
###################################################################

def rfid_scan(): 
        print ("Plz place card  : ")
        id,text = reader.read()
        text = text.replace(" ","")
        return id,text

###################################################################

def rfid_check(id) :
        for i in range(len(ide)) :                 
            if ide[i] == id :
                return i+1

        return 0

###################################################################

try: 
    fileDes = open('/home/pi/Desktop/DataBase','a')
    fileDes.write("\n\t---------- Secession Started at : ") 
    fileDes.write(time.asctime( time.localtime(time.time()) ) ) 
    fileDes.write(" ----------------\n\n") 

    while 2: 
        id,text = rfid_scan() 
        print('\n\n\tPlease wait\n\n') 
        Status = rfid_check(id) 
        if  Status : 
            print ("\n\tYour Name : ",text) 
            print ("\n\tYour I'd  : ",id,"\n\n") 
            buf="\t%s\t%d\t%s  \t %s\n"%("In" if res[Status-1] else "Out",ide[Status-1],name[Status-1],time.asctime(time.localtime(time.time()))) 
#            fileDes.write("\t"),time.asctime( time.localtime(time.time())),"\n") 
            res[Status-1] = not(res[Status-1])
            fileDes.write(buf) 

        time.sleep (0.5) 

finally:
    print ("In final")
    fileDes.write("\n\t---------- Secession Ended at : ")
    fileDes.write(time.asctime( time.localtime(time.time()) ) )
    fileDes.write(" ----------------\n\n")
    fileDes.close()
    GPIO.cleanup()

