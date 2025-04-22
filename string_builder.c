#include <stdio.h>
#include <stdlib.h>

typedef struct StringBuilder {
  char* items;
  size_t count;
  size_t capacity;
} StringBuilder;

int main() {
  printf("Hello, world");

  StringBuilder sb = {0}; // this is stack

  sb.count = 0;
  sb.capacity = 1024;
  sb.items = malloc(1024); // ptr on stack, memory on heap
                           //
  char* hello = "hello"; // this is a cstr
                         //
                         //
  while(*hello != NULL) {
    printf("%d\n", *hello);
    hello = hello + 1;
  }
 
  printf("%d", *hello);

  free(sb.items); // free on ptr, means free memory that ptr points to

  return 0;
}
