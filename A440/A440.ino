/*
  440A
  
  Play 440 Hz A
*/


//	Notes
//
//	D5	587.330	0.001702620333	1703 us		851
//	E5	659.255	0.001516863733	1516 us		758
//	C5	523.251	0.001911128693	1911 us		956
//	C4	261.626	0.003822250082	3822 us		1911
//	G4	391.995	0.002551052947	2551 us		1275

//      A5      440.000 0.002272727272  2272 us         1136

const  int  leftOutPin = 8;
const  int  rightOutPin = 9;
const  int  buttonPin = 5;

uint16_t  delayAmount = 1911;

uint16_t  i;

void setup() {
  pinMode( leftOutPin, OUTPUT );
}

void loop() {
  digitalWrite( leftOutPin, HIGH );
  delayMicroseconds( delayAmount );
  digitalWrite( leftOutPin, LOW );
  delayMicroseconds( delayAmount );
}

