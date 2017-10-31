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

typedef void (*func)(struct LinkedList *);

struct Node *createNode(int value) {
  struct Node *node = calloc(1, sizeof(struct Node));
  node->value = value;
  return node;
}

void push_back(struct LinkedList *list) {
  printf("Please, enter the value you want to push:\n");
  int value;
  scanf("%d", &value);
  struct Node *node = createNode(value);
  node->next = list->head;
  list->head = node;
  list->length++;
}

void push(struct LinkedList *list) {
  printf("Please, enter the value you want to push:\n");
  int value;
  scanf("%d", &value);
  struct Node *node = createNode(value);
  list->end->next = node;
  list->end = node;
  list->length++;
}

struct LinkedList *createList() {
  printf("Please, enter the first value:\n");
  int value;
  scanf("%d", &value);
  struct LinkedList *list = calloc(1, sizeof(struct LinkedList));
  struct Node *node = createNode(value);
  list->length = 1;
  list->head = node;
  list->end = node;
  return list;
}

void push_after(struct LinkedList *list) {
  printf("Please, enter the value you want to insert:\n");
  int value;
  scanf("%d", &value);
  printf(
      "Please, enter the value, after which you want to insert your value:\n");
  int after;
  scanf("%d", &after);
  struct Node *node = createNode(value);
  struct Node *i = list->head;
  while (i) {
    if (i->value == after) {
      if (i == list->end) {
        list->end->next = node;
        list->end = node;
        list->length++;
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

void del_element(struct LinkedList *list) {
  printf("Please, enter the value you want to delete:\n");
  int value;
  scanf("%d", &value);
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

void interface() {
  struct LinkedList *list;
  int initialized = 0;
  while (1) {
    printf("Please, choose, what do you want to do:\n");
    printf("1 - Create list\n");
    printf("2 - Push element to the end\n");
    printf("3 - Push element to the beginning\n");
    printf("4 - Push element after another\n");
    printf("5 - Delete element\n");
    printf("6 - Print list\n");
    printf("7 - Clear list\n");
    printf("100 - Exit\n");
    func functions[] = {push,        push_back,  push_after,
                        del_element, print_list, clear_list};
    int number;
    scanf("%d", &number);
    if (number == 100)
      return 0;
    if (number == 1) {
      list = createList();
      initialized = 1;
      continue;
    }
    if (initialized) {
      functions[number - 2](list);
      if (number == 7)
        initialized = 0;
    } else
      printf("Create list first!\n\n");
  }
}
