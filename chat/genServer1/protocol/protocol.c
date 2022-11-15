
#include "protocol.h"
#include <string.h>
#include <stdio.h>

int UnPackRegRequest(char *_msg, int _totalLen, char *_userName, char *_password)
{
    int nameLen, passLen;
    if (_msg == NULL || _totalLen < 3 || _userName == NULL || _password == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = _msg[2];
    passLen = _msg[3 + nameLen];
    strncpy(_userName, (const char *)&_msg[3], nameLen);

    _userName[nameLen] = '\0';
    strncpy(_password, (const char *)&_msg[4 + nameLen], passLen);

    _password[passLen] = '\0';

    return SUCCESS;
}

int PackRegRequest(char *_userName, char *_password, char *_bufferPacket)
{
    int nameLen, passLen;
    int msgLen;
    if (_userName == NULL || _password == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_userName);
    passLen = strlen(_password);
    msgLen = nameLen + passLen + 2;
    _bufferPacket[0] = REG_REQUEST;
    _bufferPacket[1] = msgLen; /* name len + password len*/
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _userName, nameLen);
    _bufferPacket[3 + nameLen] = passLen;
    strncpy(&_bufferPacket[4 + nameLen], _password, passLen);

    return (2 + msgLen);
}

int PackRegAns(char _errorCode, char *_bufferPacket)
{
    _bufferPacket[0] = REG_REP;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int UnPackRegAns(char *_message, char *_errCode, int _msgLen)
{
    if (_message == NULL || _msgLen < 3 || _errCode == NULL)
    {
        return INVALID_MSG;
    }

    *_errCode = _message[2];

    return SUCCESS;
}

int getTag(char *_msg)
{
    if (_msg == NULL)
    {
        return TAG_FAIL;
    }

    return _msg[0];
}