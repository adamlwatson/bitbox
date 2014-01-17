Sample Notes:

Just for fun, here's an Arduino project I've been working on and off with for while in my spare time, named "bitbox". I'm developing both the human user interface and the software behind it. The device is a hardware-based MIDI phrase looper (I'm an avid electronic music producer when I have time to devote to it.) 

[The controller & hardware interface looks like this.](https://github.com/adamlwatson/codesamples/blob/master/bitbox-hardware.jpg) If you look closely, you can see the LCD, SD Card Reader, MIDI ports, and the extended memory module. Once the hardware design is finished, I'll iterate on a finished enclosure for the components on the 3D printer.


# bitbox
---


## Overview

A seriously badass midi phrase looper!

## Development


#### Hardware Assumptions

Flexible MIDI Shield has the following jumpers installed:

* D0 for MIDI IN
* D1 for MIDI OUT
* D13 for MIDI Enable

#### Project Setup

Arduino 1.0.1 & Mega 2560R3

Ensure that all library dirctories located under `<bitbox-project-root>/libraries/` are copied into your local Arduino Sketchbook Libraries directory. On MacOSX, this directory is usually located at `/Volumes/HD/Users/(username)/Documents/Arduino/libraries`.

However, the location may be set to a custom path in the Arduino IDE preferences.

To begin editing the project, open the main project file, `<bitbox-project-root>/bitbox/bitbox.ino`. All other associated files will appear as tabs in the IDE.

#### Third-Party Libraries
Currently, we're using these 3rd-party libraries:

[ArduinoUnit](http://code.google.com/p/arduinounit/)

[SimpleTimer](http://arduino.cc/playground/Code/SimpleTimer)

[MemoryFree](http://arduino.cc/playground/Code/AvailableMemory)
