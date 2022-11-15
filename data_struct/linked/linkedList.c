#include <stdio.h>

#include "linkedList.h"

Person* ListInsertHead(Person* _head,Person* _p){
        if(NULL == _p)
                return _head;

        _p->m_next = _head;

        return _p;
}

int age(Person* _head){
        int ageVal;
        if (_head == NULL)
                return;

        ageVal = _head->m_age;
        if (ageVal > age(_head->m_next)) {
                return ageVal;
        }

}
Person* age2(Person* _head){
        Person *max;
        if (_head == NULL || _head->m_next == NULL)
                return _head;

        max = age2(_head->m_next);

        return (max->m_age < _head->m_age) ?_head :max;
}


Person* ListInsertByKey(Person *_head, int _key, Person *_p){
        Person* pCurr = _head;

        if (_p == NULL)
                return _head;

        if(_head == NULL ||_key < _head->m_id) {
                _p->m_next = _head;
                return _p;
        }

        while(pCurr != NULL) {
                if(_key == _head->m_next->m_id)
                        return _head;

                if(pCurr->m_next == NULL || pCurr->m_next->m_id > _key)
                {
                        _p->m_next = pCurr->m_next;
                        pCurr->m_next = _p;
                        break;
                }
                pCurr = pCurr->m_next;
        }

        return _head;
}

Person* ListInsertByKeyRec(Person *_head, int _key, Person *_p){
        if (_p == NULL)
                return _head;

        return AuxiliaryInsertRec(_head, _key, _p);
}

Person* AuxiliaryInsertRec(Person *_head, int _key, Person *_p){
        if (_head == NULL || _head->m_id > _key) {
                _p->m_next = _head;
                _head = _p;
                return _head;
        }

        if (_head->m_id == _key)
                return _head;

        _head->m_next = AuxiliaryInsertRec(_head->m_next, _key, _p);
        return _head;
}

Person* ListRemoveHead(Person* _head, Person** _item){
        if (_item == NULL)
                return _head;

        if (_head == NULL) {
                *_item = NULL;
                return _head;
        }

        *_item = _head;

        return _head->m_next;
}

Person* ListRemoveByKey(Person* _head,int _key, Person** _p){
        Person* pCurr;
        pCurr = _head;

        if(_head == NULL || _p == NULL)
                return _head;

        if (_key == _head->m_id) {
                *_p = _head;
                return _head->m_next;
        }

        while(pCurr->m_next != NULL) {
                if(pCurr->m_next->m_id == _key) {
                        *_p = pCurr->m_next;
                        pCurr->m_next = pCurr->m_next->m_next;
                        break;
                }

                pCurr = pCurr->m_next;
        }

        return _head;
}

Person* ListRemoveByKeyRec(Person* _head,  int _key, Person** _p){
        if(_head == NULL || _p == NULL)
                return _head;

        return AuxiliaryRemoveRec(_head, _key, _p);
}

Person* AuxiliaryRemoveRec(Person* _head,  int _key, Person** _p){
        if (_head == NULL || _head->m_id > _key)
                return _head;

        if ( _head->m_id == _key) {
                *_p = _head;
                _head  = _head->m_next;
                return _head;
        }

        _head->m_next = AuxiliaryRemoveRec(_head->m_next, _key,_p);
        return _head;
}

void PrintList(Person* _head){
        if(_head == NULL)
                return;

        while(_head != NULL) {
                printf("ID: %d\t name: %s\t age:%d\n", _head->m_id, _head->m_name, _head->m_age);
                _head = _head->m_next;
        }
}
