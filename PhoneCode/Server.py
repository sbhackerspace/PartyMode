#!/usr/bin/python
import serial
import web
import time
import os

import OffHookDetection
import VoiceActivation

urls = ('/(.*)', 'hello')
app = web.application(urls, globals())
try:
 Serial = serial.Serial('/dev/ttyUSB0', 9600, timeout=.1)
except:
  print 'Serial Connection could not be established'
  exit()

###############################################################################
###############################################################################
class hello:
  def POST(*args,**kwargs):
    Data  = web.input()
    print Data
    if 'On' in Data:
      print 'Starting ringer'
      Serial.write('r')
      print 'Starting off hook detection'
      if OffHookDetection.GetOffHook():
        Serial.write('o')
        time.sleep(1)
        os.system('espeak -a200 "party mode confirmation required"')
        if VoiceActivation.IsPartyModeActivated():
           os.system('scp message.txt pi@10.18.14.83:success')
           return
      os.system('scp message.txt pi@10.18.14.83:fail')

    else :
      print 'killing ringer'
      Serial.write('o')

###############################################################################
###############################################################################
if __name__ == "__main__":
  web.config.debug = False
  try:
    app.run()
  except:
    print 'webpy didnt work'
    exit()
