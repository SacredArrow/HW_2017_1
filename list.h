#ifndef LIST
#define LIST

struct Node {
  int value;
  struct Node *next;
};

struct LinkedList {
  int length;
  struct Node *head;
  struct Node *end;
};

struct Node *createNode(int);

void push_back(struct LinkedList *, int);

void push(struct LinkedList *, int);

struct LinkedList *createList(int);

void push_after(struct LinkedList *, int, int);

void del_element(struct LinkedList *, int);

void print_list(struct LinkedList *);

void clear_list(struct LinkedList *);
#endif
