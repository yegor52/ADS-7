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

    VAL *head;
    VAL *tail;

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}

    ~TPQueue();

    void push(const T &);

    T pop();

    void rmTail();
};
template<typename T>
void TPQueue<T>::push(const T &data) {
    if (head == nullptr) {
        tail = create(data);
        head = tail;
    } else if (head == tail) {
        if (tail->data.prior < data.prior) {
            tail->next = create(data);
            tail = tail->next;
        } else {
            VAL *tempo = head;
            head = create(data);
            head->next = tempo;
        }
    } else {
        VAL *temp = head;
        if (data.prior > tail->data.prior) {
            tail->next = create(data);
            tail = tail->next;
        } else if (data.prior < head->data.prior) {
            VAL *t = head;
            head = create(data);
            head->next = t;
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

#endif  // INCLUDE_TPQUEUE_H_