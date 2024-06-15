#include <stdlib.h>

#include "../includes/list.h"
#include "../includes/util.h"

/**
 * function create_node
 * 
 * @param void* item
 * 
 * @return a new Listnode
 */
struct List *create_node(void *item) {
    struct List *node = safe_malloc(sizeof(struct List));
    node->item = item;
    node->next = NULL;

    return node;
}

/**
 * function push
 * 
 * Pushes an item to the front of the linked list. This is because the order doesn't matter
 * for our usecase and this way, we don't have to loop to the end of the list to insert 
 * 
 * @param List *list
 * @param void *item
 * 
 * @returns The head to the new linked list 
 */
struct List *push(struct List *list, void *item) {
    struct List *node = create_node(item);
    node->next = list;
    
    return node;
}