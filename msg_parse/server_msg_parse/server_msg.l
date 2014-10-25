%{
// #[TYYYYYYY,Data_length,N,HHMMSS,S,latitude,D,longitude,G,
// speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,Trailer_status,Checksum]

// #[T0000001,111,N,120909,A,9055.3311,W,09655.2222,N,999.99,9,310614,1.9,99,0x66,3.14,0x77,0x11] ok!!!

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

#include "server_msg_parse.h"
#include "object/object.h"
#include "server_msg_yacc.h"

extern int server_msgparse(void *scanner, Msg_Handler_Base *msg_handler);
//extern int server_msgparse(char *msg, int msg_len, Msg_Handler_Base *msg_handler);
//extern int server_msglex(void);

//void server_msgerror(const char* ptr);

//extern "C"
//{
//int server_msgwrap(void);
//}

%}

%option reentrant
%option bison-bridge


sig_cdkey   T[0-9]{7}
sig_datalength  [0-9]+
sig_basic_type  "N"
sig_extern_type "E"
sig_third_type  "T"
sig_ack_type    "C"
sig_heart_type  "H"
sig_alarm_type  "A"
sig_ipchange_type   "I"
sig_date [0-9]{6}
sig_byte_1 (0(x|X)[0-9a-fA-F]{2})
sig_byte_4 (0(x|X)[0-9a-fA-F]{4,8})
sig_box_status_byte 0(x|X)[0-9a-fA-F]{1,8}
sig_ip_byte (0(x|X)[0-9a-fA-F]{2}\.0(x|X)[0-9a-fA-F]{2}\.0(x|X)[0-9a-fA-F]{2}\.0(x|X)[0-9a-fA-F]{2})
sig_sn [0-9]{1,2}
sig_valid_gps_flag   "A"
sig_invalid_gps_flag "V"
sig_latitude ([0-9]|[1-8][0-9]|90)([0-5][0-9])\.[0-9]{4}
sig_longitude (0[0-9][0-9]|1[0-7][0-9]|180)([0-5][0-9])\.[0-9]{4}
sig_speed ([0-9]{3}\.[0-9]{2})|0
sig_direction [0-9]+
sig_pdop ([1-9]{1,2}\.[0-9]|99)
sig_rssi [0-9]{1,2}
sig_battery_voltage ([0-4]\.[0-9]{2}|5\.00)
sig_trailer_odometer [0-9]{7}
sig_hardware_version [a-zA-Z]+[0-9]+
sig_fimware_version [0-9]{2}\.[0-9]{2}
sig_empty_data [ ]

%x SIG_START SIG_CDKEY_START SIG_MSG_TYPE_START SIG_GPS_START
%x SIG_BASIC_START SIG_ACK_TYPE SIG_HEART_TYPE SIG_ALARM_TYPE SIG_IPCHANGE_TYPE
%x SIG_DATE_START SIG_DIRECTION_START SIG_PDOP_START SIG_RSSI_START
%x SIG_SPEED_START SIG_VERSION_START

%%
"#["  {BEGIN SIG_START; }
<SIG_START>{sig_cdkey}   { BEGIN SIG_CDKEY_START; yylval->m_pchar = strdup(yytext); return SIG_CDKEY; }
<SIG_CDKEY_START>{sig_datalength}  { BEGIN SIG_MSG_TYPE_START; yylval->m_uint = atoi(yytext); return SIG_DATALENGTH; }
<SIG_MSG_TYPE_START>{sig_basic_type}  { BEGIN SIG_DATE_START; yylval->m_msg_type = MSG_BASIC_TYPE; return SIG_MSG_BASIC; }
<SIG_MSG_TYPE_START>{sig_extern_type}  { BEGIN SIG_DATE_START; yylval->m_msg_type = MSG_EXTERN_TYPE; return SIG_MSG_EXTERN; }
<SIG_MSG_TYPE_START>{sig_third_type}  { BEGIN SIG_DATE_START; yylval->m_msg_type = MSG_THIRD_TYPE; return SIG_MSG_THIRD; }
<SIG_MSG_TYPE_START>{sig_ack_type}  { BEGIN SIG_ACK_TYPE; yylval->m_msg_type = MSG_ACK_TYPE; return SIG_MSG_ACK; }
<SIG_MSG_TYPE_START>{sig_heart_type}  { BEGIN SIG_HEART_TYPE; yylval->m_msg_type = MSG_HEARTBEAT_TYPE; return SIG_MSG_HEARTBEAT; }
<SIG_MSG_TYPE_START>{sig_ipchange_type}  { BEGIN SIG_IPCHANGE_TYPE; yylval->m_msg_type = MSG_IPCHANGE_TYPE; return SIG_MSG_IPCHANGE; }
<SIG_MSG_TYPE_START>{sig_alarm_type}  { BEGIN SIG_ALARM_TYPE; yylval->m_msg_type = MSG_ALARM_TYPE; return SIG_MSG_ALARM; }

<SIG_ALARM_TYPE>{sig_byte_1}   { yylval->m_pchar = strdup(yytext); return SIG_BYTE_1; }
<SIG_ALARM_TYPE>{sig_sn}   { BEGIN SIG_DATE_START; yylval->m_uint = atoi(yytext); return SIG_SN; }

<SIG_ACK_TYPE>{sig_byte_1}    { yylval->m_pchar = strdup(yytext); return SIG_BYTE_1; }
<SIG_ACK_TYPE>{sig_sn}   { BEGIN SIG_DATE_START; yylval->m_uint = atoi(yytext); return SIG_SN; }

<SIG_IPCHANGE_TYPE>{sig_ip_byte}    { yylval->m_pchar = strdup(yytext); return SIG_IP_BYTE; }
<SIG_IPCHANGE_TYPE>{sig_sn}   { BEGIN SIG_DATE_START; yylval->m_uint = atoi(yytext); return SIG_SN; }

<SIG_HEART_TYPE>{sig_ip_byte}    { BEGIN SIG_DATE_START; yylval->m_pchar = strdup(yytext); return SIG_IP_BYTE; }

<SIG_DATE_START>{sig_date}  { BEGIN SIG_GPS_START; yylval->m_pchar = strdup(yytext); return SIG_SSMMHH; }

<SIG_GPS_START>{sig_valid_gps_flag}   { yylval->m_gps_isvalid_flag = GPS_VALID_FLAG; return SIG_GPS_ISVALID_FLAG; }
<SIG_GPS_START>{sig_invalid_gps_flag} { yylval->m_gps_isvalid_flag = GPS_INVALID_FLAG; return SIG_GPS_ISVALID_FLAG; }
<SIG_GPS_START>{sig_latitude} { yylval->m_udouble = atof(yytext); return SIG_LATITUDE; }
<SIG_GPS_START>{sig_longitude}    { yylval->m_udouble = atof(yytext); return SIG_LONGITUDE; }
<SIG_GPS_START>"W" { yylval->m_longitude_latitude_type = W_TYPE; return SIG_W_E_N_S_TYPE; }
<SIG_GPS_START>"E" { yylval->m_longitude_latitude_type = E_TYPE; return SIG_W_E_N_S_TYPE; }
<SIG_GPS_START>"N" { BEGIN SIG_SPEED_START; yylval->m_longitude_latitude_type = N_TYPE; return SIG_W_E_N_S_TYPE; }
<SIG_GPS_START>"S" { BEGIN SIG_SPEED_START; yylval->m_longitude_latitude_type = S_TYPE; return SIG_W_E_N_S_TYPE; }
<SIG_SPEED_START>{sig_speed}   { BEGIN SIG_DIRECTION_START; yylval->m_udouble = atof(yytext); return SIG_SPEED; }
<SIG_SPEED_START>{sig_empty_data}   { BEGIN SIG_DIRECTION_START; yylval->m_udouble = 0.0; return SIG_SPEED; }
<SIG_DIRECTION_START>{sig_direction}    { BEGIN SIG_GPS_START; yylval->m_udouble = atof(yytext); return SIG_DIRECTION; }
<SIG_GPS_START>{sig_date}  { BEGIN SIG_PDOP_START; yylval->m_pchar = strdup(yytext); return SIG_DDMMYY; }
<SIG_PDOP_START>{sig_pdop}    { BEGIN SIG_RSSI_START; yylval->m_udouble = atof(yytext); return SIG_PDOP; }
<SIG_RSSI_START>{sig_rssi}    { BEGIN SIG_GPS_START; yylval->m_udouble = atof(yytext); return SIG_RSSI; }
<SIG_PDOP_START>{sig_byte_1}  {  yylval->m_pchar = strdup(yytext); return SIG_BYTE_1; }
<SIG_GPS_START>{sig_byte_1}  {  yylval->m_pchar = strdup(yytext); return SIG_BYTE_1; }
<SIG_GPS_START>{sig_battery_voltage} { yylval->m_udouble = atof(yytext); return SIG_BATTERY_VOLTAGE; }
<SIG_GPS_START>{sig_trailer_odometer} { yylval->m_ulong = atol(yytext); return SIG_TRAILER_ODOMETER; }
<SIG_GPS_START>{sig_hardware_version} { BEGIN SIG_VERSION_START; yylval->m_pchar = strdup(yytext); return SIG_HARDWARE_VERSION; }
<SIG_VERSION_START>{sig_fimware_version} { BEGIN SIG_GPS_START; yylval->m_pchar = strdup(yytext); return SIG_FIMWARE_VERSION; }
<SIG_GPS_START>{sig_byte_4}   { yylval->m_pchar = strdup(yytext); return SIG_BYTE_4; }
<SIG_GPS_START>{sig_empty_data} { yylval->m_pchar = strdup(yytext); return SIG_ECU_DATA; }
<SIG_START>"," { return SEP; }
<SIG_DIRECTION_START>"," { return SEP; }
<SIG_CDKEY_START>"," { return SEP; }
<SIG_MSG_TYPE_START>"," { return SEP; }
<SIG_ALARM_TYPE>"," { return SEP; }
<SIG_ACK_TYPE>"," { return SEP; }
<SIG_IPCHANGE_TYPE>"," { return SEP; }
<SIG_HEART_TYPE>"," { return SEP; }
<SIG_DATE_START>"," { return SEP; }
<SIG_GPS_START>"," { return SEP; }
<SIG_PDOP_START>"," { return SEP; }
<SIG_RSSI_START>"," { return SEP; }
<SIG_SPEED_START>"," { return SEP; }
<SIG_VERSION_START>"," { return SEP; }
<SIG_GPS_START>"]" { BEGIN INITIAL; return END; }
<SIG_PDOP_START>"]" { BEGIN INITIAL; return END; }

%%

//int server_msg_parse(const char* msg, const int msg_length)
//{
//    int rc = 1;

//    return rc;
//}

void server_msgerror(void *scanner, Msg_Handler_Base *msg_handler, const char* ptr)
{
    int lineno = yyget_lineno ( scanner );
    char *text = yyget_text( scanner );
    fprintf(stderr, "Flex Error: line %d at [%s] reson %s\r\n", lineno, text, ptr);
    fflush(stderr);
}

int server_msg_parse(char *msg, int msg_len, Msg_Handler_Base *msg_handler)
{
    int rc = 0;
    void *scanner = NULL;
    rc = server_msglex_init(&scanner);
    if(rc != 0) return -1;

    server_msg_scan_bytes(msg, msg_len, scanner);
    //server_msg_scan_string(msg, scanner);
    server_msgparse(scanner, msg_handler);
    server_msglex_destroy(scanner);

    return 0;
}
int server_msgwrap(void *scanner)
{
    return 1;
}

