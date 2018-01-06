#ifndef PARSER_H
#define PARSER_H


#include <QObject>
#include <QDebug>

#define SOP			0x96
#define MSG_LEN			8

#define SET_MASK 0x01
#define GET_MASK 0x00
#define ASYNC_MSG_BIT 0x02
#define SYNC_MSG_BIT 0x04

//Config masks
#define CFG_MANUAL (1 << 24)
#define CFG_AUTOMATIC  (1 << 25)
#define CFG_CAL_CONTROLLER_ON  (1 << 16)
#define CFG_CAL_CONTROLLER_OFF (1 << 17)
#define CFG_CAL_MOTOR  (1 << 18)
#define CFG_CAL_SETNORTH (1 << 19)

//Status masks
#define STS_STARTUP 0x80

typedef enum
{
    //system
    ID_ERROR					= 0,
    ID_STATUS 					= 1,
    ID_CONFIG 					= 2,

    //wind sensor
    ID_WIND_SPEED 				= 10,
    ID_WIND_DIRECTION			= 11,
    ID_WIND_TEMP				= 12,

    //GPS
    ID_GPS_LONGITUDE			= 20,
    ID_GPS_LATTITUDE			= 21,
    ID_GPS_SOG					= 22,
    ID_GPS_HEADING				= 23,

    //IMU
    ID_IMU_ROLL					= 30,
    ID_IMU_PITCH				= 31,
    ID_IMU_YAW					= 32,

    //motor control
    ID_MOTCTRL_P				= 40,
    ID_MOTCTRL_I				= 41,
    ID_MOTCTRL_D				= 42,
    ID_MOTCTRL_POSITION			= 43,

    //sail control
    ID_SAILCTRL_G1				= 50,
    ID_SAILCTRL_G2				= 51,
    ID_SAILCTRL_G3				= 52,
    ID_SAILCTRL_SP_LONG			= 53,
    ID_SAILCTRL_SP_LAT			= 54,
    ID_SAILCTRL_COURSE_VAR_1	= 55,
    ID_SAILCTRL_COURSE_VAR_2	= 56
} MSG_ID;

typedef struct
{
    unsigned char c[4];
} Payload;

typedef struct
{
    unsigned char 	sot;
    unsigned char 	cmd;
    unsigned char 	id;
    Payload 		d;
    unsigned char 	crc;
} Msg;

class Parser: public QObject
{
    Q_OBJECT

public:
    Parser();
    int parse(QByteArray data, int length);
    int asyncMsgRecv();
    int syncMsgRecv();
    unsigned char CalcCRC(unsigned char *msg);
    void setLastSendID(unsigned char ID);

signals:
    void sAsyncMsg(unsigned int id, float value);
    void sSyncMsg(unsigned int id, float value);
    void sReboot();

private:
    Msg msg;
    int size;
    unsigned char lastSendID;

private:





};

#endif // PARSER_H
