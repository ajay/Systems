#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <assert.h>

// Linked list in here

struct LLNode {
  int data;
  struct LLNode *next;
};

struct LL {
  struct LLNode *root;
  struct LLNode *ptr;
};

struct LLNode *create_LLNode(int data) {
  // create the object
  struct LLNode *new_node;
  new_node = malloc(sizeof(struct LLNode));
  // set the fields
  new_node->data = data;
  new_node->next = NULL;
  // return the new_node
  return new_node;
}

struct LL *create_LL(struct LLNode *node) {
  // create the LL
  struct LL *list;
  list = malloc(sizeof(struct LL));
  list->root = node;
  list->ptr = node;
  return list;
}

int can_has_next(struct LL *list) {
  return list->ptr != NULL;
}

int get_next_item(struct LL *list) {
  assert(list->ptr != NULL);
  int temp = list->ptr->data;
  list->ptr = list->ptr->next;
  return temp;
}

int main() {
  // create the nodes 
  struct LLNode *A = create_LLNode(3), *B = create_LLNode(4), *C = create_LLNode(5);
  A->next = B;
  B->next = C;
  // create the linked list
  struct LL *list = create_LL(A);
  // print a linked list
  while (can_has_next(list)) {
    int item = get_next_item(list);
    printf("%d\n", item);
  }
  return 0;
}
