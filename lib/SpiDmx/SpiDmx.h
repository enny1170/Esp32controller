/***************************************************************************************************
 * Declarations for SpiDMX, this has to included in your program
 * E. Ziehe 2018
 * 
 * *************************************************************************************************/

#ifndef SPIDMX_H
#define SPIDMX_H

enum COMM_MODE
{
    SEND_DATA=0x01,
    RECEIVE_DATA=0x00,
    COMMAND=0x02,
    IDLE=0x03,
    DEBUG=0x04
} ;

class SSPIDMXclass
{
  private:
    int SS_Pin;
    int RxCounter=0;
    int TxCounter=0;
    char tmp[100];
    void SendReceive(COMM_MODE dmxMode);
    void debug(const char * data);
    void debug(char * data);
  public:
    SSPIDMXclass(int ssPin);
    SSPIDMXclass(int ssPin,int modePin);
    ~SSPIDMXclass() {}

    unsigned char Rx_Buffer[512];
    unsigned char Tx_Buffer[512];
    bool Debug=false;
    int DebugLevel=0;
    int Mode_Pin=5;
    void resetBuffer(unsigned char * buf);
    void enableSlave(void);
    void disableSlave(void);
    void writeChannel(int channel, unsigned char value);
    unsigned char readChannel(int channel);
    void sendDMX(void);
    void readDMX(void);
    void debugDMX(void);
} ;

#endif