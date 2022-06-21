#include <SPI.h>
byte buff [100];
volatile byte indx;
volatile boolean process;

void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   Serial.println ("OK");
   SPI.attachInterrupt(); // turn on interrupt
}
ISR (SPI_STC_vect){ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) {
      buff [indx++] = c; // save data in the next index in the array buff
      process = true;
   }
}

void loop (void) {
   if (process) {
      process = false; //reset the process
      for(int i = 0;i<indx;i++)
      {
        if(i%4==0)
        {
          Serial.println (" ");
        }
        Serial.print (buff[i],HEX);
        if(buff[i]<10)
        {
          Serial.print ("0");
        }
      }
      indx= 0; //reset button to zero
   }
}
