%{
#include "server_msg_parse.h"
#include "object/object.h"
#include "msg_handler/msg_handler.h"

#include "server_msg_yacc.h"

extern int server_msgparse(char *msg, int msg_len, Msg_Handler_Base *msg_handler);

extern int server_msglex(YYSTYPE * lvalp, void *scanner);
extern void server_msgerror(void *scanner, Msg_Handler_Base *msg_handler, const char* ptr);

GPS_Info*
copy_by_gps_info(GPS_Info* dst, const GPS_Info* src);

CDKey_And_DataLen*
copy_by_cdkey_datelen(CDKey_And_DataLen* dst, const CDKey_And_DataLen* src);

%}

%pure-parser

%lex-param {void *scanner}
%parse-param {void *scanner}
%parse-param {Msg_Handler_Base *msg_handler}

%union {
    char*   m_pchar;
    unsigned int    m_uint;
    unsigned long   m_ulong;
    double  m_udouble;
    MSG_Type    m_msg_type;
    GPS_ISValid_Flag   m_gps_isvalid_flag;
    Longitude_Latitude_Type m_longitude_latitude_type;
    CDKey_And_DataLen cdkey_and_datalen;
    GPS_Info gps_info;
}

%token<m_pchar> SIG_CDKEY SIG_SSMMHH SIG_VALID_FLAG SIG_DDMMYY SIG_BYTE_1 SIG_BYTE_4
%token<m_pchar> SIG_ALARM_STATUS SIG_IP_BYTE SIG_ECU_DATA SIG_HARDWARE_VERSION SIG_FIMWARE_VERSION
%token<m_uint> SIG_DATALENGTH SIG_RSSI SIG_SN
%token<m_ulong> SIG_TRAILER_ODOMETER
%token<m_udouble> SIG_LATITUDE SIG_LONGITUDE SIG_SPEED SIG_DIRECTION SIG_PDOP SIG_BATTERY_VOLTAGE
%token<m_msg_type> SIG_MSG_BASIC SIG_MSG_EXTERN SIG_MSG_THIRD SIG_MSG_ACK SIG_MSG_ALARM SIG_MSG_IPCHANGE SIG_MSG_HEARTBEAT
%token<m_gps_isvalid_flag> SIG_GPS_ISVALID_FLAG
%token<m_longitude_latitude_type> SIG_W_E_N_S_TYPE
%token SEP END

%type<cdkey_and_datalen> cdkey_and_datalength
%type<gps_info> message_by_gps message_by_gps_ack

%%
program:
    | program terminal_basic_res
    | program terminal_extern_res
    | program terminal_third_res
    | program terminal_ack_res
    | program terminal_alarm_res
    | program terminal_ipchange_res
    | program terminal_heartbeat_res
    ;

terminal_basic_res:
    cdkey_and_datalength SEP SIG_MSG_BASIC SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_BYTE_1 SEP SIG_BYTE_1 END
    {
        cout << "terminal_basic_res: parse ok!!!" << endl;
        Basic_Info basic_info;
        copy_by_cdkey_datelen(&(basic_info.cdkey_and_datalen), &($1));
        basic_info.msg_type = $3;
        copy_by_gps_info(&(basic_info.gps_info), &($5));

        cout << "terminal_basic_res:\r\n"
        << "cdkey=" << basic_info.cdkey_and_datalen.terminal_cdkey << "\r\n"
        << "datalen=" << basic_info.cdkey_and_datalen.data_length << "\r\n"
        << "msgtype=" << basic_info.msg_type << "\r\n"
        << "gps_info.time=" << basic_info.gps_info.time << "\r\n"
        << "gps_info.isvalid=" << basic_info.gps_info.gps_isvalid_flag << "\r\n"
        << "gps_info.latitude=" << basic_info.gps_info.latitude << "\r\n"
        << "gps_info.latitude_type=" << basic_info.gps_info.latitude_type << "\r\n"
        << "gps_info.longitude=" << basic_info.gps_info.longitude << "\r\n"
        << "gps_info.longitude_type=" << basic_info.gps_info.longitude_type << "\r\n"
        << "gps_info.speed=" << basic_info.gps_info.speed << "\r\n"
        << "gps_info.direction=" << basic_info.gps_info.direction << "\r\n"
        << "gps_info.date=" << basic_info.gps_info.date << "\r\n"
        << "gps_info.pdop=" << basic_info.gps_info.pdop << "\r\n"
        << "gps_info.rssi=" << basic_info.gps_info.rssi << "\r\n";
    }
    ;

terminal_extern_res:
    cdkey_and_datalength SEP SIG_MSG_EXTERN SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_BYTE_1 SEP
    SIG_TRAILER_ODOMETER  SEP SIG_BYTE_1 SEP SIG_BYTE_4 SEP SIG_BYTE_4 SEP SIG_ECU_DATA SEP SIG_BYTE_1 END
    {
    cout << "terminal_extern_res: parse ok!!!" << endl;
    }
    ;

terminal_third_res:
    cdkey_and_datalength SEP SIG_MSG_THIRD SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_ECU_DATA SEP SIG_BYTE_1 END
    {
    cout << "terminal_third_res: parse ok!!!" << endl;
    }
    ;

terminal_ack_res:
    cdkey_and_datalength SEP SIG_MSG_ACK SEP SIG_BYTE_1 SEP SIG_SN SEP message_by_gps_ack SEP SIG_BYTE_1 END
    {
    cout << "terminal_ack_res: parse ok!!!" << endl;
    }
    ;

terminal_alarm_res:
    cdkey_and_datalength SEP SIG_MSG_ALARM SEP SIG_BYTE_1 SEP SIG_SN SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_BYTE_1 END
    {
    cout << "terminal_alarm_res: parse ok!!!" << endl;
    }
    ;

terminal_ipchange_res:
    cdkey_and_datalength SEP SIG_MSG_IPCHANGE SEP SIG_IP_BYTE SEP SIG_SN SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_BYTE_1 END
    {
    cout << "terminal_ipchange_res: parse ok!!!" << endl;
    }
    ;

terminal_heartbeat_res:
    cdkey_and_datalength SEP SIG_MSG_HEARTBEAT SEP SIG_IP_BYTE SEP message_by_gps SEP
    SIG_BYTE_1 SEP SIG_BATTERY_VOLTAGE SEP SIG_BYTE_1 SEP
    SIG_HARDWARE_VERSION SEP SIG_FIMWARE_VERSION SEP SIG_BYTE_1 END
    {
    cout << "terminal_heartbeat_res: parse ok!!!" << endl;
    }
    ;

cdkey_and_datalength:
    SIG_CDKEY SEP SIG_DATALENGTH
    {
        strncpy($$.terminal_cdkey, $1, strlen($1));
        $$.data_length = $3;
        free($1);
    }
    ;

message_by_gps:
    SIG_SSMMHH SEP SIG_GPS_ISVALID_FLAG SEP SIG_LATITUDE SEP SIG_W_E_N_S_TYPE SEP
    SIG_LONGITUDE SEP SIG_W_E_N_S_TYPE SEP SIG_SPEED SEP SIG_DIRECTION SEP SIG_DDMMYY
    SEP SIG_PDOP SEP SIG_RSSI
    {
        strncpy($$.time, $1, strlen($1)+1);
        free($1);
        $$.gps_isvalid_flag = $3;
        $$.latitude = $5;
        $$.latitude_type = $7;
        $$.longitude = $9;
        $$.latitude_type = $11;
        $$.speed = $13;
        $$.direction = $15;
        strncpy($$.date, $17, strlen($17)+1);
        free($17);
        $$.pdop = $19;
        $$.rssi = $21;
    }
    ;

message_by_gps_ack:
    SIG_SSMMHH SEP SIG_GPS_ISVALID_FLAG SEP SIG_LATITUDE SEP SIG_W_E_N_S_TYPE SEP
    SIG_LONGITUDE SEP SIG_W_E_N_S_TYPE SEP SIG_SPEED SEP SIG_DIRECTION SEP SIG_DDMMYY
    {
        strncpy($$.time, $1, strlen($1)+1);
        free($1);
        $$.gps_isvalid_flag = $3;
        $$.latitude = $5;
        $$.latitude_type = $7;
        $$.longitude = $9;
        $$.latitude_type = $11;
        $$.speed = $13;
        $$.direction = $15;
        strncpy($$.date, $17, strlen($17)+1);
        free($17);
        $$.pdop = 0.0;
        $$.rssi = 0;
    }
    ;
%%

GPS_Info*
copy_by_gps_info(GPS_Info* dst, const GPS_Info* src)
{
    if (dst == src || NULL == dst) return dst;
    strncpy(dst->time, src->time, strlen(src->time)+1);
    dst->gps_isvalid_flag = src->gps_isvalid_flag;
    dst->latitude = src->latitude;
    dst->latitude_type = src->latitude_type;
    dst->longitude = src->longitude;
    dst->longitude_type = src->longitude_type;
    dst->speed = src->speed;
    dst->direction = src->direction;
    strncpy(dst->date, dst->date, strlen(dst->date)+1);
    dst->pdop = src->pdop;
    dst->rssi = src->rssi;

    return dst;
}


CDKey_And_DataLen*
copy_by_cdkey_datelen(CDKey_And_DataLen* dst, const CDKey_And_DataLen* src)
{
    if (dst == src || NULL == dst) return dst;
    strncpy(dst->terminal_cdkey, src->terminal_cdkey, strlen(src->terminal_cdkey)+1);
    dst->data_length = src->data_length;

    return dst;
}


