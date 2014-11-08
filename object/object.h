#ifndef OBJECT_H
#define OBJECT_H

#  ifndef MY_DECL
#  define MY_DECL

#  ifdef __WIN32__
#    define MY_DECL_EXPORT     __declspec(dllexport)
#    define MY_DECL_IMPORT     __declspec(dllimport)
#  else
#    define MY_DECL_EXPORT     __attribute__((visibility("default")))
#    define MY_DECL_IMPORT     __attribute__((visibility("default")))
#    define MY_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif

#  endif

#if defined(OBJECT_LIBRARY)
#  define OBJECTSHARED_EXPORT MY_DECL_EXPORT
#else
#  define OBJECTSHARED_EXPORT MY_DECL_IMPORT
#endif

#include <string>

struct OBJECTSHARED_EXPORT MBYTE
{
    int bit1:1;
    int bit2:1;
    int bit3:1;
    int bit4:1;
    int bit5:1;
    int bit6:1;
    int bit7:1;
    int bit8:1;
};

enum OBJECTSHARED_EXPORT GPS_ISValid_Flag
{
    GPS_VALID_FLAG = 0,
    GPS_INVALID_FLAG
};

enum OBJECTSHARED_EXPORT MSG_Type
{
    MSG_BASIC_TYPE = 0,
    MSG_EXTERN_TYPE,
    MSG_THIRD_TYPE,
    MSG_ACK_TYPE,
    MSG_ALARM_TYPE,
    MSG_IPCHANGE_TYPE,
    MSG_HEARTBEAT_TYPE
};

enum OBJECTSHARED_EXPORT Longitude_Latitude_Type
{
    W_TYPE,
    E_TYPE,
    N_TYPE,
    S_TYPE
};

struct OBJECTSHARED_EXPORT CDKey_And_DataLen
{
    char terminal_cdkey[16];
    unsigned int data_length;
};

struct OBJECTSHARED_EXPORT GPS_Info
{
    char time[7];
    GPS_ISValid_Flag gps_isvalid_flag;
    double latitude;
    Longitude_Latitude_Type latitude_type;
    double longitude;
    Longitude_Latitude_Type longitude_type;
    double speed;
    unsigned int direction;
    char date[7];
    double pdop;
    unsigned int rssi;
};


struct OBJECTSHARED_EXPORT Basic_Info
{
    CDKey_And_DataLen cdkey_and_datalen;
    MSG_Type msg_type;
    GPS_Info gps_info;
    MBYTE box_status;
    double battery_voltage;
    MBYTE trailer_status;
    MBYTE checksum;
};

struct OBJECTSHARED_EXPORT TRA_Table_Data{
    int primart_key;
    std::string content;
    std::string ip;
    std::string date;
    int flag;
};


#endif // OBJECT_H
