#include <stdio.h>
#include <time.h>

typedef void (*func)(int *, int);

void bubble_sort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i; j++)
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
}

void heapify(int *a, int i, int heap_size) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if (left < heap_size && a[left] > a[largest])
    largest = left;
  if (right < heap_size && a[right] > a[largest])
    largest = right;
  if (largest != i) {
    int temp = a[i];
    a[i] = a[largest];
    a[largest] = temp;
    heapify(a, largest, heap_size);
  }
}

void heap_sort(int *a, int n) {
  int heap_size = n;
  for (int i = n / 2; i >= 0; i--)
    heapify(a, i, heap_size);
  while (heap_size != 1) {
    int temp = a[0];
    a[0] = a[heap_size - 1];
    a[heap_size - 1] = temp;
    heap_size--;
    heapify(a, 0, heap_size);
  }
}

void counting_sort(int *arr, int n) {
  int max = arr[0];
  for (int i = 0; i < n; i++)
    if (arr[i] > max)
      max = arr[i];
  int a[max + 1];
  for (int i = 0; i <= max; i++)
    a[i] = 0;
  for (int i = 0; i < n; i++)
    a[arr[i]] += 1;
  int cnt = 0;
  for (int i = 0; i <= max; i++)
    for (int j = 0; j < a[i]; j++) {
      arr[cnt] = i;
      cnt++;
    }
}
// Для размерностей 10M и 100M объявление переменной пришлось вынести в
// глобальную область, иначе не хватает памяти
int numbers[100000000];
int main(int argc, char const *argv[]) {
  int n = 100000000;
  FILE *f = fopen("100M", "r");

  printf("Please, choose sorting method:\n");
  printf("1 - Bubble sort\n");
  printf("2 - Heap sort\n");
  printf("3 - Counting sort\n");
  func methods[] = {bubble_sort, heap_sort, counting_sort};
  int method;
  scanf("%d", &method);
  // int numbers[n];
  int t = 0, i = 0;
  while (fscanf(f, "%d", &t) > 0)
    numbers[i++] = t;
  fclose(f);
  clock_t time1 = clock();
  methods[method - 1](numbers, n);
  printf("%f\n", (float)(clock() - time1) / CLOCKS_PER_SEC);
  // for (int i = 100000; i < 100100; i++) {
  //   printf("%d\n", numbers[i]);
  // }
  return 0;
}
