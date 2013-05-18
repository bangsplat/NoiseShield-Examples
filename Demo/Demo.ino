/*
  Noise Toy Shield
  
  Demo sketch
  
  use this as a starting point for your own sketches
*/


// pins used on NoiseShield
const int pad1Pin    = 2;
const int padCommPin = 3;
const int pad2Pin    = 4;

const int button1Pin = 5;
const int button2Pin = 6;
const int button3Pin = 7;

const int audioLPin  = 9;
const int audioRPin  = 10;

const long maxRandom = 5;
const long debounce = 100;

long noteCycles;
long nextRandom;
int track;
int numTracks;

long randomA = 5;
long randomB = 5;

int delayAmount = 500;
int delayMin = 200;  // 5 kHz
int delayMax = 2000;  // 500 Hz
int down = 0;
int steppiness = 100;
int steps = 1;
long randomNumber;


int i;
int j;

void setup() {
  randomSeed(analogRead(0));
  track = 1;
  numTracks = 3;

  //  Set up the serial port
  Serial.begin( 9600 );

  //  pinMode( SPEAKER_PIN, OUTPUT );
  pinMode( audioLPin, OUTPUT );
  pinMode( audioRPin, OUTPUT );
  pinMode( button1Pin, INPUT );
  pinMode( button2Pin, INPUT );
  pinMode( button3Pin, INPUT );
  
  //  set the internal pullup resistors
  digitalWrite( button1Pin, HIGH );
  digitalWrite( button2Pin, HIGH );
  digitalWrite( button3Pin, HIGH );
}

void loop() {
  if ( track == 1 ) {
     //  TRACK 1
     //  random tones/durations

    //  Button 1 increase delay time
    if( digitalRead( button1Pin ) == LOW ) {
        randomA = randomA - 2;
    }
    
    //  Button 2 increase delay time
    if( digitalRead( button2Pin ) == LOW ) {
        randomA = randomA + 2;
    }
    
    //  Button 3 is the track button
    if( digitalRead( button3Pin ) == LOW ) {
      delay( debounce );
      if ( digitalRead( button3Pin ) == LOW ) {
        if ( track < numTracks ) { track++; }
        else { track = 1; }
      }
    }
    
     noteCycles = random(randomA)*5;
    
    for( i = 0; i < noteCycles; i++ ) {
      digitalWrite( audioLPin, HIGH );
      digitalWrite( audioRPin, HIGH );    //  ))) in stereo (((
      delay( nextRandom );
      digitalWrite( audioLPin, LOW );
      digitalWrite( audioRPin, LOW );    //  ))) in stereo (((
      delay( nextRandom );
    }
    
    nextRandom = random(randomB);
    
    
    //  Can we do button 1&2 resets the random numbers?
//    if( digitalRead( button3Pin ) == LOW ) {
//      delay( debounce );
//      if( digitalRead( button3Pin ) == LOW ) {
//        randomA = 5;
//      }
//    }

  } else if ( track == 2 ) {
    //  TRACK 2
    //  random up/down
         
    //  check Button 1
    //  check Button 2
         
    //  Button 3 is the track button
    if( digitalRead( button3Pin ) == LOW ) {
      delay( debounce );
        if ( digitalRead( button3Pin ) == LOW ) {
        if ( track < numTracks ) { track++; }
        else { track = 1; }
      }
    }
    
    // whichever way we're going, do it steps times
    for( i = 0; i < steps; i++ ) {
      for ( j = 0; j < steppiness; j++ ) {
        if( digitalRead( audioLPin ) == LOW ) { digitalWrite( audioLPin, HIGH ); } else { digitalWrite( audioLPin, LOW ); }
        if( digitalRead( audioRPin ) == LOW ) { digitalWrite( audioRPin, HIGH ); } else { digitalWrite( audioRPin, LOW ); }
        delayMicroseconds( delayAmount );
      }
      if ( down ) { delayAmount -= steppiness; } else { delayAmount += steppiness; }
    }
    
    // randomly adjust delay
    // for now just step by one
    // in the future, adjust steppiness as well
    randomNumber = random( 1000 );
    if ( randomNumber > 500 ) { if ( delayAmount > delayMax ) { down = 1; } else { down = 0; } }
    else { if ( delayAmount < delayMin ) { down = 0; } else { down = 1; } }
    
    
    
  } else if ( track == 3 ) {
    //  silence track
    
    digitalWrite( audioLPin, LOW );
    digitalWrite( audioRPin, LOW );
   
    //  Button 3 is the track button
    if( digitalRead( button3Pin ) == LOW ) {
      delay( debounce );
        if ( digitalRead( button3Pin ) == LOW ) {
        if ( track < numTracks ) { track++; }
        else { track = 1; }
      }
    }
    
  } else { track = 1; }


  
}

