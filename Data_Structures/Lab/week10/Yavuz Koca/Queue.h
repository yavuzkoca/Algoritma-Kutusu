#ifndef C_C_QUEUE_H
#define C_C_QUEUE_H

typedef char QueueDataType;
struct QueueNode{ // nodes of the list
    QueueDataType data;
    QueueNode *next;
};
class Queue {
public:
    Queue();
    QueueNode *front;
    QueueNode *back;
    void create();
    void close();
    int count;
    int max;
    void enqueue(QueueDataType);
    QueueDataType dequeue();
    bool isempty();
};

#endif //C_C_QUEUE_H
