// Written by Nick Gammon
// April 2011
// enny

#include <Arduino.h>
#include <SPI.h>
#include <SpiDmx.h>

SSPIDMXclass Controler(SS);
unsigned char * buffer;

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  Controler.Debug=true;
  Controler.DebugLevel=4;
  // Fill buffer
  buffer= new unsigned char[512];

  for(size_t i = 0; i < 512; i++)
  {
    int counter=0;
    if(counter>255)
      counter=0;
    buffer[i]=(unsigned char)counter;
    counter++;
  }
  
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  // Slow down the master a bit
  // SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  //SPI.setBitOrder(LSBFIRST);
  //digitalWrite(SS,LOW);
  Serial.println("Waiting 10 sec.");
  delay(10000);
  
}  // end of setup


void loop (void)
{

  Serial.println("Sending Buffer");
  Controler.sendDmxData(buffer);
  Serial.print("wait");  
  delay (10000);  // 1 second delay 
}  // end of loop

struct spiDmxPackage
{
    char Mark;
    byte Data[1024];
};
