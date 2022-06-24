#include <SPI.h>
byte buff [100];
volatile byte indx;
volatile boolean process;

void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= (1<<CPHA); //設定模式2
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
        Serial.print (".");
        if(i%3==0)
        {
          Serial.println (" ");
        }
        Serial.print (buff[i],HEX);
      }
      indx= 0; //reset button to zero
   }
}
