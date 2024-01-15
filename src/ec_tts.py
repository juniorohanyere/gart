#!/usr/bin/env python3
'''
text to speech module
'''

import sys
import pyttsx3


def ec_tts(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()

ec_tts(sys.argv[1])
