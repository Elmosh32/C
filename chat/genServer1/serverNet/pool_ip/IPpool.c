#include "../../../../advc/genQueue/genQueue.h"
#include "IPpool.h"
/* multicast ip addr (class d) 224.0.0.0 <=> 239.255.255.255
   pool ip: 224.0.0.0 <=> 224.0.0.100
   server give the same port for all groups
   when group closed the ip returns to pool ip*/

/*
que api
Queue *QueueCreate(size_t _size)
void QueueDestroy(Queue **_queue, DestroyItem _itemDestroy)
QueueResult QueueInsert(Queue *_queue, void *_item)
QueueResult QueueRemove(Queue *_queue, void **_item)
size_t QueueIsEmpty(Queue *_queue)
size_t QueueForEach(Queue *_queue, ActionFunction _action, void *_context)
*/
#define QUEUE_SIZE 100
#define IP_PTR "224.0.0."

/* THE MAX LEN OF LAST CELL
   MAX VAL  => 100  */
#define MAX_LEN 3
/* THE MAX LEN FULL IP ADR
   224.0.0.100 11 */
#define MAX_IP_LEN 11

struct IpPool
{
    Queue *m_ip;
};

static void InitQueue(Queue *_ipPool);
static void FreeQueueElement(void *_ip);

IpPool *IpPoolCreate()
{
    IpPool *ip;

    if ((ip = (IpPool *)malloc(sizeof(IpPool))) == NULL)
    {
        return NULL;
    }

    if ((ip->m_ip = QueueCreate(QUEUE_SIZE)) == NULL)
    {
        free(ip);
        return NULL;
    }

    InitQueue(ip->m_ip);
    /*    if (InitQueue(ip->m_ip))
       {
       }
    */
    return ip;
}

void DestroyIpQue(IpPool *_ipQue)
{
    QueueDestroy(&(_ipQue->m_ip), FreeQueueElement);
    free(_ipQue);
    _ipQue = NULL;
}

static void FreeQueueElement(void *_ip)
{
    free(_ip);
}

/*  queInsert when group closed
    QueueRemove when group needs ip*/
char *GetIp(IpPool *_ipQue)
{
    void *retIp;

    if ((QueueRemove(_ipQue->m_ip, &retIp)) != QUEUE_SUCCESS)
    {
        return NULL;
    }
    return (char *)retIp;
}

/* add enum of errors */
int InsertIp(IpPool *_ipQue, char *_ipToInsert)
{
    if ((QueueInsert(_ipQue->m_ip, _ipToInsert) != QUEUE_SUCCESS))
    {
        return -1;
    }

    return 1;
}

/*
static int ipCounter; => if we declare an int variable in a function also as static,
then that variable will not get destroyed as the function ends and will
not get destroyed until the program ends.
default value of static int var is 0
*/
static void InitQueue(Queue *_ipPool)
{
    static int ipCounter;
    char latCellIp[MAX_LEN];
    char *ip;
    int i;

    for (i = 0; i < QUEUE_SIZE; i++)
    {
        ip = (char *)malloc(MAX_IP_LEN);
        if (ip == NULL)
        {
            /* return something/error/null or continue? */
            i--;
        }
        else
        {
            strcpy(ip, IP_PTR);
            sprintf(latCellIp, "%0.3d", ipCounter);
            strcat(ip, latCellIp);
            ipCounter++;

            /* check something?*/
            QueueInsert(_ipPool, (void *)ip);
        }
    }
}
