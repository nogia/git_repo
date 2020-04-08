#ifndef DEF_SERIALPORT_CONFIG
#define DEF_SERIALPORT_CONFIG

struct SerialPortConfigStr
{
        long portid;      //@key
        long baud;
        long parity;
        long bits;
        long stopbits;
        long flowcontrol;
};
typedef struct SerialPortConfigStr SERIALPORTCONFIGSTR;


#endif
