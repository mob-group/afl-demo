#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int sum_n(int n) {
  int sum = 0;

  while (n > 0) {
    sum += n;
    --n;
  }

  return sum;
}

int sum_n_v2(int n) {
  int sum = 0;

  for (int i = 0; i <= n; ++i) {
    sum += i;
  }

  return sum;
}

int main() {
  char buffer[sizeof(int)];
  read(STDIN_FILENO, buffer, sizeof(int));

  int input = *(int*)buffer;

  int v1 = sum_n(input);
  int v2 = sum_n_v2(input);

  assert(v1 == v2);
  printf("f(%d) = %d\ng(%d) = %d\n", input, v1, input, v2);
}
