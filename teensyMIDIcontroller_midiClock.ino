/*
  Made by Simon Juhl
  Github: https://github.com/simonjuha/teensyMIDIcontroller
  10 potentiometer and buttons sending MIDI Control Changes

  To change midi-channel change 'chl' to someting from 1 to 16

  ResponsiveAnalogRead are included 
  Helping to smooth analogRead to avoid unwanted MIDI-messages
  to install go to: tools -> mannage libraries -> search for ResponsiveAnalogRead
*/

// ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// ResponsiveAnalogRead objects are made for each potentiometer
ResponsiveAnalogRead analog[10] = {
  ResponsiveAnalogRead(0, true),
  ResponsiveAnalogRead(1, true),
  ResponsiveAnalogRead(2, true),
  ResponsiveAnalogRead(3, true),
  ResponsiveAnalogRead(4, true),
  ResponsiveAnalogRead(5, true),
  ResponsiveAnalogRead(6, true),
  ResponsiveAnalogRead(7, true),
  ResponsiveAnalogRead(8, true),
  ResponsiveAnalogRead(9, true)
};

void clock_tick(void);

// midi channel
const int chl = 1;
// last value for each of 10 potentiometers
int ccLastA[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// last value for each of 10 digital buttons
int ccLastD[10] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
// new potentiometer value to compare with last value
int ccCurrent;
// midi tempo
static unsigned int delta_samples[3];;
static unsigned char delta_count = 0;
static unsigned int delta_mean;

// isr times
elapsedMillis lastTick;
elapsedMillis newTick;
elapsedMillis deltaTick;
// main loom time
elapsedMillis midiCount;

void setup() {
  // attach interrupt
  attachInterrupt(PIN_D1, sync_ISR, FALLING );
  


  
  
  // for loop for each digital pin
  // internal pullup resistor is activated for each pin
  for (int i = 0; i <= 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {

  // for loop for each potentiometer (10)
  for (int i = 0; i <= 9; i++) {
    // update the analog objects (index by i)
    analog[i].update();
    // map analog read value to midi range and set ccCurrent
    // ResponsiveAnalogRead objects getValue() are used to get more precise value
    ccCurrent = map(analog[i].getValue(), 0, 1023, 0, 127);
    if (ccLastA[i] != ccCurrent) {
      // send midi control change (cc)
      usbMIDI.sendControlChange(i, ccCurrent, chl);
      //Serial.println("cc: "+ String(i) +"    value: "+String(ccCurrent));
      // set new potentiometer state
      ccLastA[i] = ccCurrent;
    }
  }

  // for loop for each pin not being analog (10)
  for (int i = 0; i <= 9; i++) {
    if(i==6){continue;} // skip interrupt pin
    ccCurrent = digitalRead(i);
    if (ccLastD[i] != ccCurrent) {
      // check if high or low and then send MIDI cc either 0 or 127
      if (ccLastD[i] == HIGH) {
        usbMIDI.sendControlChange(i + 10, 127, chl);
        //Serial.println("cc: "+ String(i+10) +"    value: 127");
      } else {
        usbMIDI.sendControlChange(i + 10, 0, chl);
        //Serial.println("cc: "+ String(i+10) +"    value: 0");
      }
      // set new button state
      ccLastD[i] = ccCurrent;
    }
  }
  //Timer1.setPeriod(bmp_time);

  if(midiCount >= delta_mean)
    {
      usbMIDI.sendRealTime(usbMIDI.Clock);
      midiCount = 0;
    }
    
    delay(2);
}

void sync_ISR()
{
  deltaTick = (lastTick - newTick);
  lastTick = newTick;
  newTick = 0;
  if (lastTick > 10000){delta_count = 0;} // if more than 10 sec since last tap
  delta_samples[delta_count] = deltaTick; // save in array
  delta_count++;
  if (delta_count > 3)
    {
      delta_count = 0; // reset
      unsigned int temp = 0;
      for(int i=0;i<3;i++)
      {
        temp += delta_samples[i]; // average of 4 counts
      }
    
      delta_mean = temp/48;
    }
 delay(100); // for debounce

}
