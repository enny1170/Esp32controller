// Written by Nick Gammon
// April 2011

#include <Arduino.h>
#include <SPI.h>



void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  // SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup

byte transferAndWait (const byte what)
{
  byte a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} // end of transferAndWait

void loop (void)
{

  byte a, b, c, d;
  
  // enable Slave Select
  digitalWrite(SS, LOW);    

  b=transferAndWait ('a');  // add command
 
  // disable Slave Select
  digitalWrite(SS, HIGH);

  Serial.println ("results:");
  Serial.println (b, DEC);
  
  
  delay (1000);  // 1 second delay 
}  // end of loop

struct spiDmxPackage
{
    char Mark;
    byte Data[1024];
};
