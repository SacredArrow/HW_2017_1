#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct LinkedList {
  size_t length;
  struct Node *head;
  struct Node *end;
};

struct Node *createNode(int value) {
  struct Node *node = calloc(1, sizeof(struct Node));
  node->value = value;
  return node;
}

void push_back(struct LinkedList *list, int value) {
  struct Node *node = createNode(value);
  node->next = list->head;
  list->head = node;
  list->length++;
}

void push(struct LinkedList *list, int value) {
  struct Node *node = createNode(value);
  list->end->next = node;
  list->end = node;
  list->length++;
}

struct LinkedList *createList(int value) {
  struct LinkedList *list = calloc(1, sizeof(struct LinkedList));
  struct Node *node = createNode(value);
  list->length = 0;
  list->head = node;
  list->end = node;
  return list;
}

void push_after(struct LinkedList *list, int value, int after) {
  struct Node *node = createNode(value);
  struct Node *i = list->head;
  while (i) {
    if (i->value == after) {
      if (i == list->end) {
        push_back(list, value);
      }
      node->next = i->next;
      i->next = node;
      list->length++;
      return;
    }
    i = i->next;
  }
  printf("Node not found!\n");
}

void del_element(struct LinkedList *list, int value) {
  struct Node *i = list->head;
  struct Node *last;
  while (i) {
    if (i->value == value) {
      if (i == list->head) {
        list->head = i->next;
        free(i);
        i = list->head;
        list->length--;
        continue;
      }
      if (i == list->end) {
        free(i);
        list->end = last;
        list->length--;
        return;
      }

      last->next = i->next;
      free(i);
      list->length--;
      i = last->next;
    }
    last = i;
    i = i->next;
  }
}

void print_list(struct LinkedList *list) {
  struct Node *i = list->head;
  while (i) {
    if (i != list->end)
      printf("%d -> ", i->value);
    else {
      printf("%d\n", i->value);
      return;
    }
    i = i->next;
  }
}

void clear_list(struct LinkedList *list) {
  struct Node *i = list->head;
  struct Node *temp;
  while (i) {
    temp = i->next;
    free(i);
    i = temp;
  }
  free(list);
}
