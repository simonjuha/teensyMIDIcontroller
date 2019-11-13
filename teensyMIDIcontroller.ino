/*  
 Made by Simon Juhl
 Github: https://github.com/simonjuha/teensyMIDIcontroller
 10 potentiometer midicontroller sending cc messages over midi.
 
 To change midi-channel change 'chl' to someting from 1 to 16
 Some kind if noise filtering might be needed done
*/

// midi channel
const int chl = 1;
// first and last cc control number
const int firstCC = 0;
const int lastCC = 9;
// last value for each of 10 potentiometers
int ccLast[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
// new potentiometer value to compare with last value
int ccCurrent; 

void setup() {
}

void loop() {
  // for  loop for each potentiometer (10)
  for (int i = firstCC; i <= lastCC; i++) { 
    // map analog read value to midi range and set ccCurrent
    ccCurrent = map(analogRead(i), 0, 1023, 0, 127); 
    if (ccLast[i] != ccCurrent){ 
        // send midi control change (cc) 
        usbMIDI.sendControlChange(i, ccCurrent, chl);
        ccLast[i] = ccCurrent;
    } else {
      }
  }
  delay(1);
  //while (usbMIDI.read()) {
  //}
}
