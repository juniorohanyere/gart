#!/usr/bin/env python3
'''text to speech module
'''

import sys
import pyttsx3


def gtts(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()

gtts(sys.argv[1])
