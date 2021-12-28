#include "Node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Node node_constructor(void *data, unsigned long size)
{
    if (size < 1)
    {
        printf("Invalid data size\n");
        exit(1);
    }

    // Creating the actual node
    struct Node node;

    // Copy the data into the node
    node.data = malloc(size);
    memcpy(node.data, data, size);

    // Set the values of next and prev nodes to NULLs
    node.next = NULL;
    node.previous = NULL;

    return node;
}

// Free up both the data and the node
void node_destructor(struct Node *node)
{
    free(node->data);
    free(node);
}
