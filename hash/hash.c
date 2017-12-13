#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int size;
struct Node {
  char *key;
  int value;
  struct Node *next;
};

struct LinkedList {
  size_t length;
  struct Node *head;
};

int hash(char *str) {
  unsigned int p = 53;
  int i = 0;
  unsigned int sum = 0;
  while (str[i] != '\0') {
    // printf("%c - %d\n", str[i], str[i]);
    sum += p * str[i];
    i++;
    p *= p;
  }
  return sum % size;
}

struct LinkedList *createTable(int size) {
  struct LinkedList *a = malloc(size * sizeof(struct LinkedList));
  if (!a) {
    printf("Error!\n");
    exit(1);
  }
  return a;
}

// length = length of key
void insert(struct LinkedList *table, char *key, int value, int length) {
  int h = hash(key);
  struct Node *last = table[h].head;
  if (!(table[h].head)) {
    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
      printf("Error!\n");
      exit(1);
    }
    node->value = value;
    char *tmp = malloc(length + 1);
    if (!tmp) {
      printf("Error!\n");
      exit(1);
    }
    tmp[sizeof(key)] = '\0';
    strcpy(tmp, key);
    node->key = tmp;
    table[h].head = node;
    table[h].length++;
    return;
  } else {
    while (last->next) {
      if (!strcmp(last->key, key)) {
        break;
      }
      last = last->next;
    }
  }
  if (!strcmp(last->key, key)) {
    last->value = value;
  } else {
    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
      printf("Error!\n");
      exit(1);
    }
    node->value = value;
    char *tmp = malloc(length + 1);
    if (!tmp) {
      printf("Error!\n");
      exit(1);
    }
    tmp[sizeof(key)] = '\0';
    strcpy(tmp, key);
    node->key = tmp;
    last->next = node;
    table[h].length++;
  }
}

void printTable(struct LinkedList *table) {
  for (int i = 0; i < size; i++) {
    if (table[i].head) {
      printf("%d:", i);
      struct Node *last = table[i].head;
      while (last) {
        printf("{%s:%d}  ", last->key, last->value);
        last = last->next;
      }
      printf("\n");
    }
  }
}

void clearTable(struct LinkedList *table) {
  for (int i = 0; i < size; i++) {
    struct Node *temp = table[i].head;
    while (table[i].head) {
      table[i].head = temp->next;
      free(temp->key);
      free(temp);
      temp = table[i].head;
    }
    table[i].length = 0;
  }
  free(table);
}

void getNode(struct LinkedList *table, char *key) {
  int h = hash(key);
  struct Node *last = table[h].head;
  while (last) {
    if (last->key == key) {
      printf("%s %d\n", key, last->value);
      return;
    }
    last = last->next;
  }
  printf("Key not found!\n");
}
// length = length of key
void add(struct LinkedList *table, char *key, int length) {
  int h = hash(key);
  struct Node *last = table[h].head;
  if (!(table[h].head)) {
    struct Node *node = malloc(sizeof(struct Node));
    if (!node) {
      printf("Error!\n");
      exit(1);
    }
    node->value = 1;
    char *tmp = malloc(length + 1);
    if (!tmp) {
      printf("Error!\n");
      exit(1);
    }
    tmp[sizeof(key)] = '\0';
    strcpy(tmp, key);
    node->key = tmp;
    table[h].head = node;
    table[h].length++;
    return;
  } else {
    while (last->next) {
      if (!strcmp(last->key, key)) {
        break;
      }
      last = last->next;
    }
  }
  if (!strcmp(last->key, key)) {
    last->value++;
  } else {
    struct Node *node = malloc(sizeof(struct Node));
    node->value = 1;
    char *tmp = malloc(length + 1);
    if (!tmp) {
      printf("Error!\n");
      exit(1);
    }
    tmp[sizeof(key)] = '\0';
    strcpy(tmp, key);
    node->key = tmp;
    last->next = node;
    table[h].length++;
  }
}

void statisctics(struct LinkedList *table) {
  int sum = 0;
  int diff_sum = 0;
  int max_l = 0;
  int min_l = table[0].length;
  for (int i = 0; i < size; i++) {
    printf("Длина цепочки %d: %d\n", i, table[i].length);
    if (table[i].length > max_l) {
      max_l = table[i].length;
    }
    if (table[i].length < min_l) {
      min_l = table[i].length;
    }
    sum += table[i].length;
  }
  printf("Различных ключей(слов): %d\n", sum);
  printf("Среднее количество ключей в списке: %f\n", (float)sum / size);
  printf("Самая длинная цепочка: %d ключей\n", max_l);
  printf("Самая короткая цепочка: %d ключей\n", min_l);
  char *word = "";
  int value = 0;
  for (int i = 0; i < size; i++) {
    struct Node *temp = table[i].head;
    while (temp) {
      if (temp->value > value) {
        word = temp->key;
        value = temp->value;
      }
      diff_sum += temp->value;
      temp = temp->next;
    }
  }
  printf("Самое частое слово: %s\n", word);
  printf("Всего ключей(слов): %d\n", diff_sum);
  printf("Средняя частота слова: %f\n", ((float)diff_sum / sum));
}

void parseFile(struct LinkedList *table, FILE *file) {

  char str[50];
  while (fscanf(file, "%s", str) == 1) {
    if (!strcmp(str, "–")) {
      continue;
    }
    int l = strlen(str);
    char str2[50];
    for (int i = 0; i < l; i++) {
      str2[i] = 0;
    }
    for (int i = 0; i < l; i++) {
      if (str[i] != '.' && str[i] != ',' && str[i] != '?' && str[i] != '!') {
        // printf("%d\n", strlen(str2));
        // printf("%c\n", str[i]);
        char tmp[2];
        tmp[0] = str[i];
        tmp[1] = '\0';
        // printf("%s\n", tmp);
        strcat(str2, tmp);
        // printf("%s\n", str2);
      }
    }
    // printf("%s\n", str2);
    if (strlen(str2) > 0) {
      add(table, str2, strlen(str2));
    }
  }
}

int main(int argc, char const *argv[]) {
  scanf("%d", &size);
  struct LinkedList *t = createTable(size);
  char *name = "vongozero.txt";
  clock_t time1 = clock();
  FILE *file = fopen(name, "r");
  parseFile(t, file);
  // printTable(t);
  statisctics(t);
  clearTable(t);
  printf("Время работы: %f\n", (float)(clock() - time1) / CLOCKS_PER_SEC);
  fclose(file);
  return 0;
}
