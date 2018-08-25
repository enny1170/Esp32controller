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
  //SPI.setClockDivider(SPI_CLOCK_DIV8);
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
  //printState();
  Controler.sendDMX();
  Serial.print("wait");  
  delay (30);  // 1 second delay 
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
  Controler.writeChannel(6,20);
}

void setGreen(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,0);
  Controler.writeChannel(3,255);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,20);
}
void setBlue(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,0);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,255);
  Controler.writeChannel(5,0);
  Controler.writeChannel(6,20);
}
void setWhite(void)
{
  Controler.writeChannel(1,255);
  Controler.writeChannel(2,0);
  Controler.writeChannel(3,0);
  Controler.writeChannel(4,0);
  Controler.writeChannel(5,255);
  Controler.writeChannel(6,20);
}

void setOff(void)
{
  // Master Dimmer
  Controler.writeChannel(1,255);
  // Jump Change
  Controler.writeChannel(6,20);  
  Controler.writeChannel(2,0);  
  Controler.writeChannel(3,0);  
  Controler.writeChannel(4,0);  
  Controler.writeChannel(5,0);  
}

void printState(void)
{
  char tmp[100];
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[0],0);
  Serial.println(tmp);
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[1],1);
  Serial.println(tmp);
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[2],2);
  Serial.println(tmp);
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[3],3);
  Serial.println(tmp);
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[4],4);
  Serial.println(tmp);
  sprintf(tmp,"%i - %i",(int)Controler.Tx_Buffer[5],5);
  Serial.println(tmp);

}
