/***************************************************************************************************
 * Declarations for SpiDMX, this has to included in your program
 * E. Ziehe 2018
 * 
 * *************************************************************************************************/

#ifndef SPIDMX_H
#define SPIDMX_H

enum COMM_MODE
{
  SEND_DATA = 0x01,
  RECEIVE_DATA = 0x00,
  COMMAND = 0x02
};

enum DMX_COMMAND
{
  SET_SENDER_MODE=0x01,
  SET_RECEIVER_MODE=0x00,
  SET_DEBUG_MODE=0x02,
  GET_BUFFER=0x03
};

class SSPIDMXclass
{
  private:
    int SS_Pin;
    int RxCounter=0;
    int TxCounter=0;
    void SetSenderMode(void);
    void SetReceiverMode(void);
    void SendReceive(void);
    //void SendReceive(unsigned char * buff);
    void SendReceive(unsigned char * buff,DMX_COMMAND cmd);
    void debug(const char * data);
    void debug(char * data);
  public:
    SSPIDMXclass(int ssPin);
    ~SSPIDMXclass() {}

    unsigned char Rx_Buffer[512];
    unsigned char Tx_Buffer[512];
    bool Debug=false;
    int DebugLevel=0;
    void resetBuffer(unsigned char * buf);
    void enableSlave(void);
    void disableSlave(void);
    char * receiveDmxData();
    void sendDmxData(unsigned char * buff);
    void sendCommand(DMX_COMMAND cmd);

} ;

#endif