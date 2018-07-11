# Protocoll for DMX SPI Communication

## Agreements:

'~' has to use as as prefix for commands send from Master to Slave 

'\n' has to use as suffix for all Transactions. This will mark the end of the command or data block send

'?' is used to prefix a data package. This is also suffixed ba '\n' 

## Commands:

The slave will support fallowing list of Commands. Every command has to send in the format '~{0}\n'. Each comman received by the slave will be respond with '#{0}\n' in case of ok. Or '!{0}\n' in case of not understand. In case of query commands like b,d and g this respond will be fallowed by a data package.

Command|      Action
-------|----------------------------------
s      | set the slave to DMX-Sender Mode
r      | set the slave to DMX-Receiver Mode
g      | get the current Mode of the slave
d      | start a RDM discovery
b      | get the Frame Buffer content of the slave

## Data:

Data packages are arrays of byte's. The maximum lenght supported by this protocoll is 1024 bytes. Including prefix and suffix byte. if you want to work with string content you have to set a 0x00 as last byte of your content.

internally all packages will be handled as fallowing struture.

```C
struct spiDmxPackage
{
    char Mark;
    byte Data[1024];
};
```
