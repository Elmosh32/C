#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define NAME_LEN_MAX 24
#define PASS_LEN_MAX 8
#define PASS_LEN_MIN 6
#define PORT_NUMBER 1990
#define PACKET_SIZE 200
#define SER_IP "127.0.0.1"

typedef enum Tags
{
    TAG_FAIL = -1,
    REG_REQUEST = 1,
    REG_REP,
    LOGIN_REQUEST,
    LOGIN_OK,
    LOGIN_FAILED,
    CLIENT_DISCONNECTED,
    REQUEST_CREATE_GROUP,
    CREATE_GROUP_OK,
    CREATE_GROUP_FAILED,
    REQUEST_JOIN_GROUP,
    JOIN_GROUP_OK,
    JOIN_GROUP_FAILED,
    REQUEST_LEAVE_GROUP,
    LEAVE_OK,
    LEAVE_FAIL,
    REQUEST_LOG_OUT,
    LOG_OUT_OK,
    LOG_OUT_FAIL

} Tags;

typedef enum ProtocolErr
{
    SUCCESS,
    INVALID_MSG = 2,
    INVALID_USERNAME,
    INVALID_PASSWORD,
    INVALID_GROUP_NAME,
    OUT_OF_IP_ADDRESSES,
    SENT_ERROR,
    RECV_ERROR,
    PACKING_ERROR,
    UNPACKING_ERROR,
    PROGRAM_CLOSED,
    REG_ERROR,
    LOGIN_ERROR
} ProtocolErr;

int UnPackRegRequest(char *_buf, int _readBytes, char *_userName, char *_password); /* unpack puts values in username and password buffers*/

/* This function puts username and passowrd in string _bufferPacket, according to TLV formatting
and returns the total len of _bufferPacket after packing */
int PackRegRequest(char *_userName, char *_password, char *_bufferPacket);
int UnPackRegAns(char *_message, char *_errCode, int _msgLen);
int PackRegAns(char _errorCode, char *_bufferPacket);
int getTag(char *_msg);
#endif /*__PROTOCOL_H__*/
