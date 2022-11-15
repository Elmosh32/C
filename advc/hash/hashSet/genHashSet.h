#ifndef __GEN_HASH_SET_H__
#define __GEN_HASH_SET_H__

#include <stddef.h> /*size_t*/

typedef struct Hash Hash;

typedef enum HashSet_Result
{
    SET_SUCCESS = 0,
    SET_UNINITIALIZED, /** Uninitialized HasSeterror*/
    SET_KEY_DUPLICATE, /** Duplicate key error */
    SET_KEY_NOT_FOUND, /** Key not found */
    SET_OVERFLOW       /**No more space in HashSe */
} HashSet_Result;

typedef size_t (*HashFunction)(void *_data);
typedef int (*EqualityFunction)(void *_firstData, void *_secondData);

Hash *HashCreate(size_t _size, size_t (*_hashFunction)(void *), int (*_equalityFunction)(void *, void *));
void HashDestroy(Hash **_hash, void (*_keyDestroy)(void *_data));
HashSet_Result HashInsert(Hash *_hash, void *_data);
HashSet_Result HashRemove(Hash *_hash, void *_key, void **_data);
int HashIsFound(const Hash *_hash, void *_key);
size_t HashNumOfItems(const Hash *_hash);
size_t HashCapacity(const Hash *_hash);
double HashAverageRehashes(const Hash *_hash);
size_t HashMaxReHash(const Hash *_hash);

void HashPrint(const Hash *_hash, void (*PrintKey)(void *));

#endif /* __GEN_HASH_SET_H__ */
