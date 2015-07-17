#!/usr/bin/env python2
import pyaudio
import sys
import OffHookDetection
import time
import os
from pocketsphinx import *

hmm = 'model/en-us/en-us'
dic = 'model/en-us/cmudict-en-us.dict'
lm= 'model/en-us/en-us.lm.dmp'

config = Decoder.default_config()
config.set_string('-hmm', hmm)
config.set_string('-lm', lm)
config.set_string('-dict', dic)
config.set_string('-logfn', '/dev/null')
config.set_string('-keyphrase', 'party mode confirmed')
config.set_float('-kws_threshold', 1e-40)


################################################################################
def Setup():
  decoder = Decoder(config)
  Audio = pyaudio.PyAudio()
  Stream = Audio.open(\
    format=pyaudio.paInt16, \
    channels=1, \
    rate=16000, \
    input=True, \
    frames_per_buffer=1024)

  Stream.start_stream()
  decoder.start_utt()
  return Audio, Stream, decoder

################################################################################
def ClearDecoder(decoder):
  decoder.end_utt()
  decoder.start_utt()
  return 0

################################################################################
def IsPartyModeActivated():
  Audio, Stream, decoder = Setup()
  Counter = 0
  while True:
    buf = Stream.read(1024)
    Counter += 1
    decoder.process_raw(buf, False, False)
    if decoder.hyp() != None:
      Hypothesis = decoder.hyp().hypstr
      print Hypothesis
      if "party mode confirmed" in Hypothesis:
        print "ACTIVATE!!!!!!!!!!\n"
        Counter = ClearDecoder(decoder)
        return

    if Counter > 50:
      Counter = ClearDecoder(decoder)

################################################################################
################################################################################
if __name__ == "__main__":
    OffHookDetection.GetOffHook()
    time.sleep(1)
    os.system('espeak -a200 "party mode confirmation required"')
    IsPartyModeActivated()



