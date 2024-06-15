#ifndef LIST_H
#define LIST_H

struct List {
    void *item;
    struct List *next;
};

struct List *create_node(void *item);
struct List *push(struct List *list, void *item);

#endif //LIST_H