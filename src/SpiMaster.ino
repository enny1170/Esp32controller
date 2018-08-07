// Written by Nick Gammon
// April 2011
// enny

#include <Arduino.h>
#include <SPI.h>
#include <SpiDmx.h>

#define DMX_MODE_PIN 15

SSPIDMXclass Controler(SS,DMX_MODE_PIN);
int counter=0;

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  Controler.Debug=true;
  Controler.DebugLevel=4;
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  // Slow down the master a bit
  // SPI.setClockDivider(SPI_CLoCK_DIV8);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  //SPI.setBitOrder(LSBFIRST);
  //digitalWrite(SS,LOW);
  Controler.debugDMX();
  Serial.println("Waiting 10 sec.");
  delay(10000);
  
}  // end of setup


void loop (void)
{

  
  switch (counter)
  {
    case 0:
      setRed();
      counter++;
      break;
    case 1:
      setGreen();
      counter++;
      break;
    case 2:
      setBlue();
      counter++;
      break;
    case 3:
      setWhite();
      counter++;
      break;
    default:
      setOff();
      counter=0;
      break;
  }
  Serial.println("Sending Data");
  Controler.sendDMX();
  Serial.print("wait");  
  delay (1000);  // 1 second delay 
}  // end of loop

struct spiDmxPackage
{
    char Mark;
    byte Data[1024];
};

void setRed(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,255);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,120);
}

void setGreen(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,255);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,120);
}
void setBlue(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,255);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,120);
}
void setWhite(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,255);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,120);
}

void setOff(void)
{
  // Master Dimmer
  Controler.writeChannel(1,255);
  // Jump Change
  Controler.writeChannel(6,120);  
  Controler.writeChannel(2,0);  
  Controler.writeChannel(3,0);  
  Controler.writeChannel(4,0);  
  Controler.writeChannel(5,0);  
}
