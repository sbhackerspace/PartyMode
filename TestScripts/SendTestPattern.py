#!/usr/bin/python

MYPORT = 31337
NumberOfPixels = 381

import sys, time
from socket import *
import numpy as np

################################################################################
def MakePixel(Red, Green, Blue):
  return chr(Red) + chr(Green) + chr(Blue)

################################################################################
def SendPacket(Socket, Packet):
  Socket.sendto(Packet, ('10.18.14.38', MYPORT)) #workroom
  Socket.sendto(Packet, ('10.18.14.93', MYPORT)) #classroom
  Socket.sendto(Packet, ('10.18.14.99', MYPORT)) #middle

################################################################################
def Larson(Socket):

  SendPacket(Socket, MakePixel(0,255,0)*NumberOfPixels)
  while True:
    for index in range(2, NumberOfPixels-5, 2):
      Packet = ''
      for pixel in range(NumberOfPixels):
        if index-5< pixel < index+5:
          Packet += MakePixel(0, 0, 255)
        else:
          Packet += MakePixel(0, 255, 0)
      SendPacket(Socket, Packet)
      time.sleep(.6)
    for index in range(NumberOfPixels-5, 2,-2):
      Packet = ''
      for pixel in range(NumberOfPixels):
        if index-5< pixel < index+5:
          Packet += MakePixel(0, 0, 255)
        else:
          Packet += MakePixel(0, 255, 0)
      SendPacket(Socket, Packet)
      time.sleep(.6)

################################################################################
def Test(Socket):
  while True:
    Packet = MakePixel(255, 255, 255) * NumberOfPixels
    SendPacket(s, Packet)
    print 'Sent 255'
    time.sleep(1)
    Packet = MakePixel(0, 0, 0) * NumberOfPixels
    SendPacket(s, Packet)
    print 'Sent 0'
    time.sleep(1)



################################################################################
#def Random(Socket):
  #randint = np.random.randint
  #while True:
    #Packet = ''
    ##for i in range(NumberOfPixels):
      ##Packet += MakePixel(randint(255), randint(255), randint(255))
    #Packet = MakePixel(randint(255), randint(255), randint(255))* NumberOfPixels
    #SendPacket(s, Packet)
    #time.sleep(.5)

################################################################################
################################################################################
if __name__ == "__main__":
  s = socket(AF_INET, SOCK_DGRAM)
  s.bind(('', 0))
  s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
  Test(s)

