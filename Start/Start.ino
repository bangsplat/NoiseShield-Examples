/*
  NoiseShield
  
  Demo sketch
  
  use this as a starting point for your own sketches
*/

const int leftPin = 9;
const int rightPin = 10;
const int buttonOnePin = 5;
const int buttonTwoPin = 6;
const int buttonThreePin = 7;

//
//  Close Encounters Of The Third Kind
//
//  Play the five-note motif
//

//	Notes
//
//	D5	587.330	0.001702620333	1703 us		851
//	E5	659.255	0.001516863733	1516 us		758
//	C5	523.251	0.001911128693	1911 us		956
//	C4	261.626	0.003822250082	3822 us		1911
//	G4	391.995	0.002551052947	2551 us		1275

uint16_t notes[5] = { 1703, 1516, 1911, 3822, 2551 };
uint16_t delays[5];
uint32_t cycles[5];
uint16_t i, j;

uint32_t  target_us = 500000;
uint16_t  delay_ms = 1000;

void setup() {
  // Set up the serial port
  Serial.begin( 9600 );

//  pinMode( SPEAKER_PIN, OUTPUT );
  pinMode( leftPin, OUTPUT );
  pinMode( rightPin, OUTPUT );
  pinMode( buttonOnePin, INPUT );
  pinMode( buttonTwoPin, INPUT );
  pinMode( buttonThreePin, INPUT );
  
  //  set the internal pullup resistors
  digitalWrite( buttonOnePin, HIGH );
  digitalWrite( buttonTwoPin, HIGH );
  digitalWrite( buttonThreePin, HIGH );
  
  //  set up our array of number of cycles per note
  //  doing this here so that we can make it smart (later on)
  for( i = 0; i < 5; i++ ) {
    delays[i] = notes[i] / 2;                  //  we need two delays per cycle
    cycles[i] = target_us / (uint32_t)notes[i];
    
//    Serial.print( i );
//    Serial.print( " " );
//    Serial.print( delays[i] );
//    Serial.print( " " );
//    Serial.print( cycles[i] );
//    Serial.print( "\n" );
    
  }
}

void loop() {
  if( digitalRead( buttonOnePin ) == LOW ) {
    Serial.print( "button\n" );
  
    for( i = 0; i < 5; i++ ) {              //  notes
      for( j = 0; j < cycles[i]; j++ ) {    //  cycles
        digitalWrite( leftPin, HIGH );
        digitalWrite( rightPin, HIGH );    //  ))) in stereo (((
        delayMicroseconds( delays[i] );
        digitalWrite( leftPin, LOW );
        digitalWrite( rightPin, LOW );    //  ))) in stereo (((
        delayMicroseconds( delays[i] );
      }
    }
  }
}

