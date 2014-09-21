%{
// #[TYYYYYYY,Data_length,N,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,Trailer_status,Checksum]

// #[TYYYYYYY,Data_length,E,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,Trailer_status,Trailer_Odometer,Reefer_status,Cargo_sensor, Temp_sensor,ECU_data,Checksum]

// #[TYYYYYYY,Data_length,T,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,3nd_part_data,Checksum]

// #[TYYYYYYY,Data_length,C,CMD,CMD_SN,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY, Checksum］

// #[TYYYYYYY,Data_length,A,Alarm_status,Alarm_SN,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Battery_voltage,Checksum]

// #[TYYYYYYY,Data_length,I,IPaddress,IPaddress_SN,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Battery_voltage,Checksum]

// #[TYYYYYYY,Data_length,H,IPaddress,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,Trailer_status,Hardware_Version,Firmware_Version,Checksum]

#include "object/object.h"
#include "server_msg_yacc.h"

extern int server_msgparse(void);
extern int server_msglex(void);

void server_msgerror(const char* ptr);

extern "C"
{
    int server_msgwrap(void);
}

%}

sig_cdkey   T[0-9]{7}
sig_datalength  [0-9]+
sig_basic_type  "N"
sig_extern_type "E"
sig_third_type  "T"
sig_ack_type    "C"
sig_heart_type  "H"
sig_alarm_type  "A"
sig_ipchange_type   "I"
sig_ssmmhh [0-9]{6}
sig_cmdsn [0-9]{1,2}
sig_valid_gps_flag   "A"
sig_invalid_gps_flag "V"
sig_latitude ([0-9]|[1-8][0-9]|90)\.[0-9]{4}
sig_longitude (0[0-9][0-9]|1[0-7][0-9]|180)\.[0-9]{4}
sig_speed ([0-9]{3}\.[0-9]{2})|0|[ ]
sig_direction ([x])
sig_ddmmyy [0-9]{6}
sig_pdop ([1-9]\.[0-9]|99)
sig_rssi [0-9]{1,2}
sig_box_status [0-9]{8}
sig_battery_voltage ([0-4]\.[0-9]{2}|5\.00)
sig_trailer_status [0-9]{8}
sig_trailer_odometer [0-9]{7}

%x SIG_START

%%
^#  {BEGIN SIG_START; }
<SIG_START>sig_cdkey   { server_msglval.m_pchar = strdup(yytext); return SIG_CDKEY; }
<SIG_START>sig_datalength  { server_msglval.m_uint = atoi(yytext); return SIG_DATALENGTH; }
<SIG_START>sig_basic_type  { server_msglval.m_msg_type = MSG_BASIC_TYPE; return SIG_MSG_BASIC; }
<SIG_START>sig_extern_type  { server_msglval.m_msg_type = MSG_EXTERN_TYPE; return SIG_MSG_EXTERN; }
<SIG_START>sig_third_type  { server_msglval.m_msg_type = MSG_THIRD_TYPE; return SIG_MSG_THIRD; }
<SIG_START>sig_ack_type  { server_msglval.m_msg_type = MSG_ACK_TYPE; return SIG_MSG_ACK; }
<SIG_START>sig_heart_type  { server_msglval.m_msg_type = MSG_HEARTBEAT_TYPE; return SIG_MSG_HEARTBEAT; }
<SIG_START>sig_ipchange_type  { server_msglval.m_msg_type = MSG_IPCHANGE_TYPE; return SIG_MSG_IPCHANGE; }
<SIG_START>sig_alarm_type  { server_msglval.m_msg_type = MSG_ALARM_TYPE; return SIG_MSG_ALARM; }
<SIG_START>sig_ssmmhh  { server_msglval.m_pchar = strdup(yytext); return SIG_SSMMHH; }
<SIG_START>sig_cmdsn  { server_msglval.m_pchar = strdup(yytext); return SIG_CMDSN; }
<SIG_START>sig_valid_gps_flag   { server_msglval.m_gps_isvalid_flag = GPS_VALID_FLAG; return SIG_GPS_VALID_FLAG; }
<SIG_START>sig_invalid_gps_flag { server_msglval.m_gps_isvalid_flag = GPS_INVALID_FLAG; return SIG_GPS_INVALID_FLAG; }
<SIG_START>sig_latitude { server_msglval.m_udouble = atof(yytext); return SIG_LATITUDE; }
<SIG_START>sig_longitude    { server_msglval.m_udouble = atof(yytext); return SIG_LONGITUDE; }
<SIG_START>"W" { server_msglval.m_longitude_latitude_type = W_TYPE; return SIG_W_TYPE; }
<SIG_START>"E" { server_msglval.m_longitude_latitude_type = E_TYPE; return SIG_E_TYPE; }
<SIG_START>"N" { server_msglval.m_longitude_latitude_type = N_TYPE; return SIG_N_TYPE; }
<SIG_START>"S" { server_msglval.m_longitude_latitude_type = S_TYPE; return SIG_S_TYPE; }
<SIG_START>sig_speed   { server_msglval.m_udouble = atof(yytext); return SIG_SPEED; }
<SIG_START>sig_direction   { server_msglval.m_udouble = atof(yytext); return SIG_DIRECTION; }
<SIG_START>sig_ddmmyy  { server_msglval.m_pchar = strdup(yytext); return SIG_DDMMYY; }
<SIG_START>sig_pdop    { server_msglval.m_udouble = atof(yytext); return SIG_PDOP; }
<SIG_START>sig_rssi    { server_msglval.m_udouble = atof(yytext); return SIG_RSSI; }
<SIG_START>sig_box_status  { server_msglval.m_pchar = strdup(yytext); return SIG_BOX_STATUS; }
<SIG_START>sig_battery_voltage { server_msglval.m_udouble = atof(yytext); return SIG_BATTERY_VOLTAGE; }
<SIG_START>sig_trailer_status  { server_msglval.m_pchar = strdup(yytext); return SIG_TRAILER_STATUS; }
<SIG_START>sig_trailer_odometer { server_msglval.m_ulong = atol(yytext); return SIG_TRAILER_ODOMETER; }

%%

int server_msg_parse(const char* msg, const int msg_length)
{
    int rc = 1;
    //rc = server_msgparse()
    return rc;
}

void server_msgerror(const char* ptr)
{
    fprintf(stderr, "Flex Error: line %d at [%s] reson %s\r\n", yylineno, yytext, ptr);
    fflush(stderr);
}

int server_msgwrap(void)
{
    return 1;
}



