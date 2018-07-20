/***************************************************************************************************
 * Implementations for SpiDMX, this has to included in your program
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

    char * SSPIDMXclass::receiveDmxData()
    {
        throw "not implented jet";
    }

    void SSPIDMXclass::sendDmxData(unsigned char * buff)
    {
        // First send Command to set the Slave as DMX Sender
        debug("sendDmxData...");
        //SetSenderMode();
        Serial.println("resetting Buffers");
        resetBuffer(Tx_Buffer);
        resetBuffer(Rx_Buffer);
        RxCounter=0;
        TxCounter=0;
        enableSlave();
        SendReceive(buff,DMX_COMMAND::SET_SENDER_MODE);
        disableSlave();
        
    }

    void SSPIDMXclass::SetSenderMode(void)
    {
        debug("SetSenderMode...");
        //sendCommand(DMX_COMMAND::SET_SENDER_MODE);
        Tx_Buffer[0]=DMX_COMMAND::SET_SENDER_MODE;
    }

    void SSPIDMXclass::SetReceiverMode(void)
    {
        debug("SetReceiverMode");
        //sendCommand(DMX_COMMAND::SET_RECEIVER_MODE);
        Tx_Buffer[0]=DMX_COMMAND::SET_RECEIVER_MODE;
    }

    void SSPIDMXclass::SendReceive(void)
    {
        uint8_t c;
        char tmp[100];
        sprintf(tmp,"SendReceive() size %i",sizeof(Tx_Buffer));
        debug(tmp);
        
        for(size_t i = 0; i < sizeof(Tx_Buffer)+1; i++)
        {
            if((int)Tx_Buffer[i]==0)
            {
                sprintf(tmp,"Break SendReceive after %i bytes",i+1);
                debug(tmp);
                break;
            }
            else
            {
                unsigned char w = Tx_Buffer[i];
                c = SPI.transfer(w);
                Rx_Buffer[i] = c;
                if (DebugLevel > 3)
                {
                    sprintf(tmp, "Sending %i", (int)Tx_Buffer[i]);
                    debug(tmp);
                    sprintf(tmp, "Receiving %i", (int)c);
                    debug(tmp);
                }
            }
        }
    }
/* 
    void SSPIDMXclass::SendReceive(unsigned char * buff)
    {
        byte c;
        char tmp[100];
        sprintf(tmp,"SendReceive(buf) size %i",512);
        debug(tmp);
        for(int i = 0; i < 512; i++)
        {
                c=SPI.transfer(buff[i]);
                Rx_Buffer[i]=c;

                if(DebugLevel>4)
                {
                sprintf(tmp,"Sending %i",i);
                debug(tmp);
                sprintf(tmp,"Receiving %i",(int)c);
                debug(tmp);
                }
        }
    }

 */
    void SSPIDMXclass::SendReceive(unsigned char * buff,DMX_COMMAND cmd)
    {
        byte c;
        char tmp[100];
        debug("SendReceive(buf,cmd)...");
        sprintf(tmp,"SendReceive(buf) size %i",512);
        debug(tmp);
        for(int i = -1; i < 512; i++)
        {
                if(i==-1)
                {
                    c=SPI.transfer((unsigned char)cmd);
                }
                else
                {
                    c=SPI.transfer(buff[i]);
                    Rx_Buffer[i]=c;
                }

                if(DebugLevel>3)
                {
                    sprintf(tmp,"Sending byte index %i, value: %i, retval: %i",i,(int)buff[i],(int)c);
                    debug(tmp);
                }
        }
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

    void SSPIDMXclass::sendCommand(DMX_COMMAND cmd)
    {
        debug("SendCommand...");
        resetBuffer(Tx_Buffer);
        resetBuffer(Rx_Buffer);
        RxCounter=0;
        TxCounter=0;
        Tx_Buffer[0]=COMM_MODE::COMMAND;
        Tx_Buffer[1]=cmd;
        enableSlave();
        SendReceive();
        delayMicroseconds(20);
        disableSlave();
    }
