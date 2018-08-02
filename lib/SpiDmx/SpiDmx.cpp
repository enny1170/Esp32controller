/***************************************************************************************************
 * Implementations for SpiDMX, this has to be included in your program
 * E. Ziehe 2018
 * 
 * *************************************************************************************************/

#include <SpiDmx.h>
#include <Arduino.h>
#include <SPI.h>

    SSPIDMXclass::SSPIDMXclass(int ssPin)
    {
        Serial.println("Init DMX Class..");
        SS_Pin = ssPin;
        pinMode(SS_Pin,OUTPUT);
    }

    void SSPIDMXclass::resetBuffer(unsigned char * buf)
    {
        debug("Reset Buffer...");
        //memcpy(buf,(unsigned char *)'0',512);
        
        for(size_t i = 0; i < 512; i++)
        {
            buf[i]=0;
        }
        
    }

    void SSPIDMXclass::enableSlave(void)
    {
        debug("Enable Slave ...");
        digitalWrite(SS_Pin,LOW);
        delayMicroseconds(20);
    }

    void SSPIDMXclass::disableSlave(void)
    {
        debug("Disable Slave ...");
        digitalWrite(SS_Pin,HIGH);
    }

    void SSPIDMXclass::SendReceive(COMM_MODE dmxMode)
    {
        uint8_t c;
        resetBuffer(Rx_Buffer);        
        enableSlave();
        // Transfer Mode Byte
        c=SPI.transfer((unsigned char)dmxMode);   
        // wait a liitle bit, give the dive time to init
        delayMicroseconds(20);     
        for(size_t i = 0; i < 512; i++)
        {
            unsigned char w = Tx_Buffer[i];
            c = SPI.transfer(w);
            Rx_Buffer[i] = c;
            if (DebugLevel > 3)
            {
                sprintf(tmp,"Channel %i s=%i, r=%i",i,(int)Tx_Buffer[i],(int)Rx_Buffer[i]);
                debug(tmp);
            }
        }
        disableSlave();
    }

    void SSPIDMXclass::debug(const char * data)
    {
        if(Debug)
            Serial.println(data);
    }

    void SSPIDMXclass::debug(char * data)
    {
        if(Debug)
            Serial.println(data);
    }

    void SSPIDMXclass::writeChannel(int channel, unsigned char value)
    {
        if(channel>0 && channel<513)
        {
            Tx_Buffer[channel-1]=value;
        }
    }

    unsigned char SSPIDMXclass::readChannel(int channel)
    {
        unsigned char retVal=0x00;
        if(channel>0 && channel<513)
        {
            retVal=Rx_Buffer[channel-1];
        }
        return retVal;
    }

    void SSPIDMXclass::sendDMX(void)
    {
        SendReceive(COMM_MODE::SEND_DATA);
    }

    void SSPIDMXclass::readDMX(void)
    {
        SendReceive(COMM_MODE::RECEIVE_DATA);
    }

    void SSPIDMXclass::debugDMX(void)
    {
        SendReceive(COMM_MODE::DEBUG);
    }


