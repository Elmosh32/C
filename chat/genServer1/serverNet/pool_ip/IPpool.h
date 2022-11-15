
#ifndef __POOL_IP_H__
#define __POOL_IP_H__

typedef struct IpPool IpPool;

IpPool *IpPoolCreate();
void DestroyIpQue(IpPool *_ipQue);
char *GetIp(IpPool *_ipQue);
int InsertIp(IpPool *_ipQue, char *_ipToInsert);

#endif /* __POOL_IP_H__ */