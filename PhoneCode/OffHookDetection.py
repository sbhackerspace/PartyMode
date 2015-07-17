#!/usr/bin/python
## This script takes input plots its waveform
## and plots a fft frquency plot
##

import alsaaudio, time
import numpy as np

################################################################################
##Set up for alsaaudio
# Open the device in nonblocking capture mode. The last argument could
# just as well have been zero for blocking mode. Then we could have
# left out the sleep call in the bottom of the loop
################################################################################
def InitializeRecording(SampleRate):
  inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
  # Set attributes: Mono, 8000 Hz, 16 bit little endian samples
  inp.setchannels(1)
  inp.setrate(SampleRate)
  inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
  inp.setperiodsize(1024)
  return inp

################################################################################
def GetSample(SampleRate):
  inp = InitializeRecording(SampleRate)
  Seconds = time.localtime()[5]
  switch = True
  while switch ==True:
    # Read data from device
    l,data = inp.read()
    if l:
      numbers = np.fromstring(data, dtype='int16')
      if 'Sample' not in vars():
        Sample = numbers
      else:
        Sample = np.append(Sample, numbers)
        if len(Sample) > 2000:
          HalfPoint = len(Sample/2)
          Sample = Sample[HalfPoint-20000:HalfPoint+20000]
          return Sample

################################################################################
def GetOffHook():
  SampleRate = 44100
  StartTime = time.time()
  while time.time() - StartTime < 10:
    Sample = GetSample(SampleRate)
    if max(Sample) > 10000:
      print 'Off the Hook'
      return True
  return False

################################################################################
################################################################################
if __name__ == '__main__':
  while True:
    GetOffHook()
