// Node implementation for data structures

#ifndef LINUXPROJ_NODE_H
#define LINUXPROJ_NODE_H

struct Node{
    void *data;
    struct Node *next;
    struct Node *previous;
};

// Constructor
struct Node node_constructor(void *data, unsigned long size);

// Destructor
void node_destructor(struct Node *node);

#endif //LINUXPROJ_NODE_H
