/*  
 Made by Simon Juhl
 Github: https://github.com/simonjuha/teensyMIDIcontroller
 10 potentiometer and buttons sending MIDI Control Changes
 
 To change midi-channel change 'chl' to someting from 1 to 16
 Some kind if noise filtering might be needed done
*/

// midi channel
const int chl = 1;
// last value for each of 10 potentiometers
int ccLastA[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// last value for each of 10 digital buttons
int ccLastD[10]={LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW}; 
// new potentiometer value to compare with last value
int ccCurrent; 

void setup() {
  // for loop for each digital pin
  // internal pullup resistor is activated for each pin
  for (int i = 0; i <= 9; i++) { 
      pinMode(i, INPUT_PULLUP);
    }
}

void loop() {
  // for loop for each potentiometer (10)
  for (int i = 0; i <= 9; i++) { 
    // map analog read value to midi range and set ccCurrent
    ccCurrent = map(analogRead(i), 0, 1023, 0, 127); 
    if (ccLastA[i] != ccCurrent){ 
        // send midi control change (cc) 
        usbMIDI.sendControlChange(i, ccCurrent, chl);
        // set new potentiometer state
        ccLastA[i] = ccCurrent;
    }
  }
    // for loop for each pin not being analog (10)
    for (int i = 0; i <= 9; i++) { 
    ccCurrent = digitalRead(i);
    if (ccLastD[i] != ccCurrent){ 
      // check if high or low and then send MIDI cc either 0 or 127 
      if (ccLastD[i] == HIGH){
        usbMIDI.sendControlChange(i+10, 127, chl);
        //Serial.println("cc: "+ String(i+10) +"    val: 127");
        }else{
        usbMIDI.sendControlChange(i+10, 0, chl);
        //Serial.println("cc: "+ String(i+10) +"    val: 0");
          }
        // set new button state
        ccLastD[i] = ccCurrent;
    } 
  }
  delay(1);
}
