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

void push_back(struct LinkedList *);

void push(struct LinkedList *);

struct LinkedList *createList();

void push_after(struct LinkedList *);

void del_element(struct LinkedList *);

void print_list(struct LinkedList *);

void clear_list(struct LinkedList *);

void reverse_list(struct LinkedList *);

void interface();
#endif
