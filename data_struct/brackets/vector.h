#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct Vector Vector;

/* size      - The initial allocation size.
   blockSize - The extention block size.    */
Vector*  VectorCreate   (size_t _initialSize, size_t _extensionBlockSize);
void     VectorDestroy  (Vector* _vector);
ADTErr   VectorAdd  (Vector *_vector,  int _item);    /* Add item to end. */
ADTErr   increase(Vector *_vector);
ADTErr   VectorDelete (Vector *_vector,  int* _item);   /* Delete item from the end. */
/* The Index range in the following functions is : 0..numOfItems-1 */
ADTErr   setVector(Vector *_vector, size_t _index, int _item);
ADTErr   getVector(Vector *_vector, size_t _index, int *_item);
ADTErr   getMagicNum(Vector *_vector, int*  _magicNum);
ADTErr   getNumOfItems(Vector *_vector, size_t*  _numOfItems);
/*  Unit-Test functions  */
void VectorPrint(Vector *_vector);

#endif /* __VECTOR_H__ */
