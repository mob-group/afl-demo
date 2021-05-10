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

int main() {
  char buffer[sizeof(int)];
  read(STDIN_FILENO, buffer, sizeof(int));

  int input = *(int*)buffer;
  int output = sum_n(input);
  printf("f(%d) = %d\n", input, output);
}
