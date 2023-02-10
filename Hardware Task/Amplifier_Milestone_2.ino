#define dataPin 13
#define latchPin 15
#define clockPin 12

//looping variables
byte i;
byte j;

//storage variable
byte dataToSend;

//storage for led states, 4 bytes
byte ledData[] = {15, 15, 15, 15};

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  
  for (i=0;i<4;i++){
    
    //send data from ledData to each row, one at a time
    byte dataToSend = (1 << (i+4)) | (15 & ~ledData[i]);
      
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);
    // shift out the bits of dataToSend to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, dataToSend);
    //set latch pin high- this sends data to outputs so the LEDs will light up
    delay(1000);
    digitalWrite(latchPin, HIGH);
      
  }  
  
}