#include <stdio.h>
#include <stdlib.h>
int queries;
int n;
struct tree {
  int number;
  int freq;
  int freq_all;
  struct tree *left;
  struct tree *right;
};

struct tree *build_tree(int *a, int *f, int *p, int *q, int l, int r) {
  if (l == r) {
    struct tree *leaf = calloc(1, sizeof(struct tree));
    if (!leaf) {
      printf("Cannot allocate memory!\n");
      exit(1);
    }
    leaf->number = a[l];
    leaf->freq = f[l];
    leaf->freq_all = f[l];
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
  }
  if (l > r) {
    return NULL;
  }
  struct tree *node = calloc(1, sizeof(struct tree));
  if (!node) {
    printf("Cannot allocate memory!\n");
    exit(1);
  }
  int goal;
  if (r == n - 1) {
    goal = queries + p[l];
  } else {
    goal = p[r + 1] + p[l];
  }
  int min = abs(q[l] - goal);
  int min_i = l;
  for (int i = l; i < r; i++) {
    if (abs(q[i] - goal) < min) {
      min = abs(q[i] - goal);
      min_i = i;
    }
  }
  node->number = a[min_i];
  node->freq = f[min_i];
  if (r == n - 1) {
    node->freq_all = queries - p[l];
  } else {
    node->freq_all = p[r + 1] - p[l];
  }
  node->left = build_tree(a, f, p, q, l, min_i - 1);
  node->right = build_tree(a, f, p, q, min_i + 1, r);
  return node;
}

void print_tree(struct tree *tr, int last, int last_freq, int last_freq_all,
                FILE *out) {
  if (!last) {
    fprintf(out, "digraph {\n");
  }
  if (last) {
    fprintf(out, "\"%d\\n%d\\n%d\" -> \"%d\\n%d\\n%d\";\n", last, last_freq,
            last_freq_all, tr->number, tr->freq, tr->freq_all);
  }
  if (tr->left) {
    print_tree(tr->left, tr->number, tr->freq, tr->freq_all, out);
  }
  if (tr->right) {
    print_tree(tr->right, tr->number, tr->freq, tr->freq_all, out);
  }
}

void clear_tree(struct tree *tr) {
  if (tr->left) {
    clear_tree(tr->left);
  }
  if (tr->right) {
    clear_tree(tr->right);
  }
  free(tr);
}
// Описание алгоритма:
// Необходимо минимизировать разницу между поддеревьями
// 1.Посчитаем p(x)=кол-во элементов меньших x
// 2.Получим, что, выбрав элемент i корнем поддерева, разница между поддеревьями
// i([l..i-1],[l+1..r]) будет равна
// D(l,r,i)=p(m)-p(l)-(p(r+1)-p(m+1))=p(m)+p(m+1)-(p(r+1)+p(l)), где(если
// n-кол-во элементов) p(n+1) - всего запросов
// 3.Заранее посчитаем q(x)=p(x)+p(x+1)
// 4.Минимизируем разницу

int main(int argc, char const *argv[]) {
  FILE *fi = fopen("tree.txt", "r");
  if (!fi) {
    printf("Cannot open file!\n");
    exit(1);
  }
  FILE *out = fopen("out.dot", "w");
  if (!out) {
    printf("Cannot open file!\n");
    exit(1);
  }
  fscanf(fi, "%d", &n);
  int a[n];
  int f[n];
  for (int i = 0; i < n; i++) {
    fscanf(fi, "%d - %d", &a[i], &f[i]);
    queries += f[i];
  }
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n - j - 1; i++) {
      if (a[i] > a[i + 1]) {
        int temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        temp = f[i];
        f[i] = f[i + 1];
        f[i + 1] = temp;
      }
    }
  }
  int p[n];
  p[0] = 0;
  for (int i = 1; i < n; i++) {
    p[i] = p[i - 1] + f[i - 1];
  }
  int q[n];
  for (int i = 0; i < n - 1; i++) {
    q[i] = p[i] + p[i + 1];
  }
  q[n - 1] = p[n - 1] + queries;
  struct tree *result = build_tree(a, f, p, q, 0, n - 1);
  print_tree(result, 0, 0, 0, out);
  fprintf(out, "}\n");
  clear_tree(result);
  fclose(fi);
  fclose(out);
  return 0;
}
