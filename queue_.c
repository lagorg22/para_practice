#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void* elems;
    int elem_size;
    int log_len;
    int alloc_len;
    int front;
}Queue;

void queue_init(Queue* q, int elem_size) {
    q->elem_size = elem_size;
    q->log_len = 0;
    q->front = 0;
    q->alloc_len = 10;
    q->elems = malloc(elem_size * q->alloc_len);
    assert(q->elems != NULL);
}

void queue_dispose(Queue* q) {
    free(q->elems);
}

void queue_push(Queue* q, void* val) {
    if(q->alloc_len == q->log_len + q->front) {
        q->alloc_len *= 2;
        q->elems = realloc(q->elems, q->alloc_len * q->elem_size);
        assert(q->elems != NULL);
    }
    void* place = (char*)q->elems + (q->log_len + q->front)* q->elem_size;
    memcpy(place, val, q->elem_size);
    q->log_len++;
}

void queue_front(Queue* q, void* dst_ptr) {
    assert(q->log_len > 0);
    q->log_len--;
    memcpy(dst_ptr, (char*)q->elems + q->front * q->elem_size, q->elem_size);
    q->front++;
}

int queue_size(Queue* q) {
    return q->log_len;
}

int main() {
    Queue q;
    queue_init(&q, sizeof(int));
    for (int i = 0; i <= 100; i++) {
        queue_push(&q, &i);
    }

    for (int i = 0; i <= 104; i++) {
        int size = queue_size(&q);
        int res;
        queue_front(&q, &res);
        printf("size: %d  ____  elem: %d\n", size, res);
    }
    queue_dispose(&q);
    return 0;
}