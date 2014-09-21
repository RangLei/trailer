%{
#include "object/object.h"

extern int client_msgparse(void);
extern int client_msglex(void);
extern void client_msgerror(const char* ptr);

%}

%union{
    char*   m_pchar;
    unsigned int    m_uint;
    unsigned long   m_ulong;
    double  m_udouble;
    MSG_Type    m_msg_type;
    GPS_ISValid_Flag    m_gps_isvalid_flag;
    Longitude_Latitude_Type m_longitude_latitude_type;
}

%token<m_pchar> SIG_CDKEY SIG_SSMMHH SIG_CMDSN SIG_VALID_FLAG SIG_DDMMYY SIG_BOX_STATUS SIG_TRAILER_STATUS
%token<m_uint> SIG_DATALENGTH SIG_RSSI
%token<m_ulong> SIG_TRAILER_ODOMETER
%token<m_udouble> SIG_LATITUDE SIG_LONGITUDE SIG_SPEED SIG_DIRECTION SIG_PDOP SIG_BATTERY_VOLTAGE
%token<m_msg_type> SIG_MSG_BASIC SIG_MSG_EXTERN SIG_MSG_THIRD SIG_MSG_ACK SIG_MSG_ALARM SIG_MSG_IPCHANGE SIG_MSG_HEARTBEAT
%token<m_gps_isvalid_flag> SIG_GPS_VALID_FLAG SIG_GPS_INVALID_FLAG
%token<m_longitude_latitude_type> SIG_W_TYPE SIG_E_TYPE SIG_N_TYPE SIG_S_TYPE
%%
program:
    | program terminal_basic_res
    ;

terminal_basic_res:
    SIG_CDKEY {}
    ;

%%




