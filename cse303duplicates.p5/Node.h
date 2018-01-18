#ifndef NODE_H
#define NODE_H


  struct Node
  {
    int value;
    Node* next;
    Node(): value(0), next(NULL) {
    }
  };


#endif
