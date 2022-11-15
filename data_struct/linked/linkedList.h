#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#define TRUE 1
#define FALSE 0

typedef struct Person Person;

struct Person
{
        int m_id;
        char m_name[128];
        int m_age;
        struct Person* m_next;
        int m_MagicNum;
};
void ageAdd(Person* _head);

int age(Person* _head);
Person* age2(Person* _head);
/**
   Description:     Adds a new person Node to the list's head.
   Input:           Person* _head
                    Person** _item
   Output:          Pointer to the new head Node || pointer to old head Node.
   Error:           if the pointer to the new person is null.
 **/
Person* ListInsertHead(Person* _head, Person* _p);

/**
   Description:     Deletes the head Node.
   Input:           Person* _head
                    Person** _item
   output:          Pointer wich points to next person
   Error:           X
 **/
Person* ListRemoveHead(Person* _head, Person** _item);

/**
   Description:     Insert sorted by input Key.
   Input:           Person* _head
                    int _key
                    Person *_p
   output:          updated head pointer.
   Error:           X
 **/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);

/**
   Description:     Insert sorted by input Key. (Recursive function)
   Input:           Person* _head
                    int _key
                    Person *_p
   output:          updated head pointer.
   Error:           X
 **/
Person* ListInsertByKeyRec(Person* _head,  int _key, Person* _p);
Person* AuxiliaryInsertRec(Person *_head, int _key, Person *_p);

/**
   Description:     Removes node whose ID value matches the given key.
   Input:           Person* _head
                    int _key
                    Person *_p
   output:          updated head pointer.
   Error:           X
 **/
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);

/**
   Description:   Removes node whose ID value matches the given key.(Recursive function)
   Input:         Person* _head
                  int _key
                  Person *_p
   output:        updated head pointer.
   Error:         X
 **/
Person* ListRemoveByKeyRec(Person* _head,  int _key, Person** _p);
Person* AuxiliaryRemoveRec(Person* _head,  int _key, Person** _p);

/**
   Description:   Printing persons list.
   Input:         Person* _head.
   output:        Void
   Error:         x
 **/
void    PrintList(Person* _head);

#endif /* endif __LINKEDLIST_H__ */
