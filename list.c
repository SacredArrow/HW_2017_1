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
  struct Node *last = 0;
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
  struct Node *temp = 0;
  while (i) {
    temp = i->next;
    free(i);
    i = temp;
  }
  free(list);
}

void reverse_list(struct LinkedList *list) {
  struct Node *last = list->head;
  struct Node *i = 0;
  struct Node *temp = 0;
  if (last)
    i = last->next;
  else {
    printf("Error!\n");
    return;
  }
  if (i)
    temp = i->next;
  else {
    printf("Error!\n");
    return;
  }
  while (i) {
    i->next = last;
    last = i;
    i = temp;
    if (i)
      temp = temp->next;
  }
  list->head->next = 0;
  temp = list->head;
  list->head = list->end;
  list->end = temp;
}

void create_loop(struct LinkedList *list) {
  struct Node *temp = 0;
  printf("Please, enter the number of element to create a loop:\n");
  int value;
  scanf("%d", &value);
  if (value > list->length)
    printf("Wrong value!\n");
  else {
    temp = list->head;
    for (int i = 1; i < value; i++)
      temp = temp->next;
  }
  list->end->next = temp;
}

void find_a_loop(struct LinkedList *list) {
  struct Node *pointer1 = list->head->next;
  struct Node *pointer2 = list->head;
  int i = 0;
  while (i <= 100000) {
    if (pointer1 == pointer2) {
      printf("Loop found!\n");
      return;
    }
    if (!pointer1 || !pointer2) {
      printf("No loop!\n");
      return;
    }
    pointer1 = pointer1->next;
    if (i % 2 != 0)
      pointer2 = pointer2->next;
    i++;
  }
  printf("Loop limit exceeded!\n");
}

void interface() {
  struct LinkedList *list = 0;
  while (1) {
    printf("Please, choose, what do you want to do:\n");
    printf("1 - Create list\n");
    printf("2 - Push element to the end\n");
    printf("3 - Push element to the beginning\n");
    printf("4 - Push element after another\n");
    printf("5 - Delete element\n");
    printf("6 - Print list\n");
    printf("7 - Clear list\n");
    printf("8 - Reverse list\n");
    printf("9 - Create a loop\n");
    printf("10 - Find a loop\n");
    func functions[] = {push,         push_back,   push_after,
                        del_element,  print_list,  clear_list,
                        reverse_list, create_loop, find_a_loop};
    int number;
    scanf("%d", &number);
    if (number == 1) {
      list = createList();
      continue;
    }
    if (list) {
      functions[number - 2](list);
      if (number == 7) {
        list = 0;
      }
    } else
      printf("Create list first!\n\n");
  }
}
