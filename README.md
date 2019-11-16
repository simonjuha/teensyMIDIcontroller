# Simple teensy USB MIDI-CC Controller
10 pontentiometers and 10 digital buttons sending MIDI CC messages over USB
This is a easy way of using all ports avalible on the teensy 2.0
Other teensy boards should work with this code but changes might have to be made

i Used the ResponsiveAnalogRead-library to smoothen out the analog input
* https://github.com/dxinteractive/ResponsiveAnalogRead


This project uses the MIDI controller library: 
  * https://www.pjrc.com/teensy/td_midi.html
  * https://github.com/joshnishikawa/MIDIcontroller
  
  
  additional functions can be used to send MIDI via USB:
  ```
    usbMIDI.sendNoteOn(note, velocity, channel);
    usbMIDI.sendNoteOff(note, velocity, channel);
    usbMIDI.sendAfterTouchPoly(note, pressure, channel);
    usbMIDI.sendControlChange(control, value, channel);
    usbMIDI.sendProgramChange(program, channel);
    usbMIDI.sendAfterTouch(pressure, channel);
    usbMIDI.sendPitchBend(value, channel);
    usbMIDI.sendSysEx(length, array, hasBeginEnd);
    usbMIDI.sendTimeCodeQuarterFrame(index, value);
    usbMIDI.sendSongPosition(beats);
    usbMIDI.sendSongSelect(song);
    usbMIDI.sendTuneRequest();
    usbMIDI.sendRealTime(usbMIDI.Clock);
    usbMIDI.sendRealTime(usbMIDI.Start);
    usbMIDI.sendRealTime(usbMIDI.Continue);
    usbMIDI.sendRealTime(usbMIDI.Stop);
    usbMIDI.sendRealTime(usbMIDI.ActiveSensing);
    usbMIDI.sendRealTime(usbMIDI.SystemReset);
```
