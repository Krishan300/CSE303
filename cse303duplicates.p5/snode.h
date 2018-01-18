#ifndef SNODE_H
#define SNODE_H

struct Snode{
  Node* head;
  std::mutex g_num_mutex;
}

#endif
