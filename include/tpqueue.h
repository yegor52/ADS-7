// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cstdint>

template<typename T>
class TPQueue {
 private:
    struct VAL {
        T data;
        VAL *next;
    };

    TPQueue::VAL *create(const T &);

    VAL *hd;
    VAL *tl;

 public:
    TPQueue() : hd(nullptr), tl(nullptr) {}

    ~TPQueue();

    void push(const T &);

    T pop();

    void Trmil();
};

template<typename T>
typename TPQueue<T>::VAL *TPQueue<T>::create(const T &data) {
    VAL *pVal = new VAL;
    pVal->data = data;
    pVal->next = nullptr;
    return pVal;
}

template<typename T>
void TPQueue<T>::push(const T &data) {
    if (hd == nullptr) {
        tl = create(data);
        hd = tl;
    } else if (hd == tl) {
        if (tl->data.prior < data.prior) {
            tl->next = create(data);
            tl = tl->next;
        } else {
            VAL *tempo = hd;
            hd = create(data);
            hd->next = tempo;
        }
    } else {
        VAL *temp = hd;
        if (data.prior > tl->data.prior) {
            tl->next = create(data);
            tl = tl->next;
        } else if (data.prior < hd->data.prior) {
            VAL *t = hd;
            hd = create(data);
            hd->next = t;
        } else {
            while (data.prior > temp->next->data.prior) {
                temp = temp->next;
            }
            VAL *tem = temp->next;
            temp->next = create(data);
            temp->next->next = tem;
        }
    }
}
template<typename T>
void TPQueue<T>::Trmil() {
    if (hd == nullptr) {
        return;
    }
    if (hd == tl) {
        delete hd;
        hd = tl = nullptr;
    } else {
        VAL* temp = hd;
        while (temp->next != tl) {
            temp = temp->next;
        }
        delete tl;
        tl = temp;
        tl->next = nullptr;
    }
}
template<typename T>
T TPQueue<T>::pop() {
    T temp = tl->data;
    Trmil();
    return temp;
}

template<typename T>
TPQueue<T>::~TPQueue() {
    while (tl) {
        pop();
    }
}



struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
