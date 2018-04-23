#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
  int *floor;
  int *top;
};

struct Command {
  char text[10];
  int value;
  char label_name[20];
};

struct Label {
  char name[20];
  int point;
};

struct Label **labels;
int label_ptr;

void push(struct Stack *stack, int value) {
  stack->top++;
  *stack->top = value;
}

int pop(struct Stack *stack) {
  if (stack->top == stack->floor) {
    printf("Stack smash detected, aborting\n");
    exit(0);
  }
  int tmp = *stack->top;
  stack->top--;
  return tmp;
}

int peek(struct Stack *stack) {
  if (stack->top == stack->floor) {
    printf("Stack smash detected, aborting\n");
    exit(0);
  }
  return *stack->top;
}

int searchForLabel(char *key) {
  for (size_t i = 0; i < label_ptr; i++) {
    if (strcmp(labels[i]->name, key) == 0) {
      return labels[i]->point;
    }
  }
  return -1;
}
void parseFile(struct Command **instructions, FILE *file) {
  char str[10];
  int cnt = 0;
  while (fscanf(file, "%s", str) == 1) {
    instructions[cnt] = malloc(sizeof(struct Command));
    if (!instructions[cnt]) {
      printf("Error while allocating memory!\n");
      exit(1);
    }
    if (str[0] == ';') {
      fgets(str, 100, file);
      continue;
    }
    if (!(strcmp(str, "ldc") == 0 || strcmp(str, "st") == 0 ||
          strcmp(str, "ld") == 0 || strcmp(str, "add") == 0 ||
          strcmp(str, "sub") == 0 || strcmp(str, "cmp") == 0 ||
          strcmp(str, "jmp") == 0 || strcmp(str, "br") == 0 ||
          strcmp(str, "ret") == 0)) {
      str[strlen(str) - 1] = '\0';
      labels[label_ptr] = malloc(sizeof(struct Label));
      if (!labels[label_ptr]) {
        printf("Error while allocating memory!\n");
        exit(1);
      }
      strcpy(labels[label_ptr]->name, str);
      labels[label_ptr]->point = cnt;
      label_ptr++;
      fscanf(file, "%s", str);
    }
    strcpy(instructions[cnt]->text, str); // important!
    if (strcmp(str, "ldc") == 0 || strcmp(str, "st") == 0 ||
        strcmp(str, "ld") == 0) {
      fscanf(file, "%d", &instructions[cnt]->value);
    } else if (strcmp(str, "jmp") == 0 || strcmp(str, "br") == 0) {
      fscanf(file, "%s", instructions[cnt]->label_name);
    }
    cnt++;
  }
}
int main(int argc, char const *argv[]) {
  int *data = (int *)calloc(1 << 19, sizeof(int));
  struct Command **instructions = malloc((1 << 19) * sizeof(struct Command));
  struct Stack *stack = malloc(sizeof(struct Stack));
  labels = malloc((1 << 19) * sizeof(struct Label));
  stack->top = malloc((1 << 19) * sizeof(int));
  if (!data || !instructions || !stack || !labels || !stack->top) {
    printf("Error while allocating memory!\n");
    exit(1);
  }
  stack->floor = stack->top;
  char *name = "gcd.txt";
  FILE *file = fopen(name, "r");
  if (!file) {
    printf("Cannot open file!\n");
    exit(1);
  }
  label_ptr = 0;
  parseFile(instructions, file);
  int ip = 0;

  while (strcmp(instructions[ip]->text, "ret") != 0) {
    char *inst = instructions[ip]->text;
    // printf("%s %d\n", inst, peek(stack));
    if (strcmp(inst, "ldc") == 0) {
      push(stack, instructions[ip]->value);
    } else if (strcmp(inst, "add") == 0) {
      int a = pop(stack);
      int b = pop(stack);
      push(stack, a + b);
    } else if (strcmp(inst, "st") == 0) {
      int a = pop(stack);
      data[instructions[ip]->value] = a;
    } else if (strcmp(inst, "ld") == 0) {
      push(stack, data[instructions[ip]->value]);
    } else if (strcmp(inst, "sub") == 0) {
      int a = pop(stack);
      int b = pop(stack);
      push(stack, a - b);
    } else if (strcmp(inst, "cmp") == 0) {
      int a = pop(stack);
      int b = peek(stack);
      push(stack, a);
      int res;
      if (a > b) {
        res = 1;
      } else if (a < b) {
        res = -1;
      } else {
        res = 0;
      }
      push(stack, res);
    } else if (strcmp(inst, "jmp") == 0) {
      int ptr = searchForLabel(instructions[ip]->label_name);
      if (ptr == -1) {
        printf("Label %s not found!\n", instructions[ip]->label_name);
        exit(0);
      } else {
        ip = ptr;
        continue;
      }
    } else if (strcmp(inst, "br") == 0) {
      if (peek(stack) != 0) {
        int ptr = searchForLabel(instructions[ip]->label_name);
        if (ptr == -1) {
          printf("Label %s not found!\n", instructions[ip]->label_name);
          exit(0);
        } else {
          ip = ptr;
          continue;
        }
      }
    }

    ip++;
  }
  while (stack->top != stack->floor) {
    printf("%d\n", *stack->top);
    stack->top--;
    /* code */
  }
  // printf("%s %d\n", labels[0]->name, labels[0]->point);
  // printf("%s %d\n", instructions[0]->text, instructions[0]->value);
  // printf("%s %d\n", instructions[1]->text, instructions[1]->value);
  // printf("%s %d\n", instructions[2]->text, instructions[2]->value);
  return 0;
}
