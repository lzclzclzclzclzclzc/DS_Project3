
#ifndef CLOSEDHASHTABLE_H
#define CLOSEDHASHTABLE_H

#include <iostream>
using namespace std;

enum EntryType { ACTIVE, EMPTY, DELETED };
enum ProbeType { LINEAR, QUADRATIC };

template <class ElemType>
struct HashEntry {
    ElemType data;
    EntryType state;

    HashEntry() {
        state = EMPTY;
    }
};

template <class ElemType, class KeyType>
class ClosedHashTable {
protected:
    HashEntry<ElemType>* ht;
    int curSize, maxSize;
    int incNum;
    ProbeType probeType;

    int H(KeyType key) const {
        return key % maxSize;
    }

    int Collision(KeyType key, int i) const {
        if (probeType == LINEAR)
            return (H(key) + i) % maxSize;
        else // QUADRATIC
            return (H(key) + i * i) % maxSize;
    }

public:
    ClosedHashTable(int size = 17, int inc = 1, ProbeType type = LINEAR);
    ~ClosedHashTable() { delete[] ht; }
    bool Insert(const ElemType& item);
    int Search(KeyType key, int* probeCounter = nullptr) const;
};

template <class ElemType, class KeyType>
ClosedHashTable<ElemType, KeyType>::ClosedHashTable(int size, int inc, ProbeType type) {
    maxSize = size;
    incNum = inc;
    curSize = 0;
    probeType = type;
    ht = new HashEntry<ElemType>[maxSize];
}

template <class ElemType, class KeyType>
bool ClosedHashTable<ElemType, KeyType>::Insert(const ElemType& item) {
    KeyType key = item;
    int i = 0, p;
    do {
        p = Collision(key, i);
        if (ht[p].state != ACTIVE) {
            ht[p].data = item;
            ht[p].state = ACTIVE;
            curSize++;
            return true;
        }
        i++;
    } while (i < maxSize);
    return false;
}

template <class ElemType, class KeyType>
int ClosedHashTable<ElemType, KeyType>::Search(KeyType key, int* probeCounter) const {
    int i = 0, p;
    do {
        p = Collision(key, i);
        if (probeCounter) (*probeCounter)++;
        if (ht[p].state == ACTIVE && ht[p].data == key)
            return p;
        i++;
    } while (ht[p].state != EMPTY && i < maxSize);
    return -1;
}

#endif
