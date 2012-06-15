# bitbox
---



## Overview

A seriously badass midi phrase looper!

## Development


#### Hardware Assumptions

Flexible MIDI Shield has the following jumpers installed:

* D2 for MIDI IN
* D3 for MIDI OUT
* ON for MIDI Enable

#### Project Setup

Arduino 1.0.1 & Mega 2560R3

Ensure that all library dirctories located under `<bitbox-project-root>/libraries/` are copied into your local Arduino Sketchbook Libraries directory. On MacOSX, this directory is usually located at `/Volumes/HD/Users/(username)/Documents/Arduino/libraries`.

However, the location may be set to a custom path in the Arduino IDE preferences.

To begin editing the project, open the main project file, `<bitbox-project-root>/bitbox/bitbox.ino`. All other associated files will appear as tabs in the IDE.