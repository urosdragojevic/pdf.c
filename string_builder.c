#include <stdio.h>
#include <stdlib.h>

typedef struct StringBuilder {
  char* items;
  size_t count;
  size_t capacity;
} StringBuilder;

void sb_init(StringBuilder *sb, size_t initial_capacity) {
  sb->items = malloc(initial_capacity * sizeof(char));
  sb->count = 0;
  sb->capacity = initial_capacity;
}

void sb_append_cstr(StringBuilder *sb, char *c) {
  char *tmp = c;
  while (*tmp != '\0') {
    if (sb->count == sb->capacity) {
      sb->capacity = sb->capacity * 2;
      sb->items = realloc(sb->items, sb->capacity * sizeof(char));
    }
    sb->items[sb->count++] = *tmp++;
  }
}

void sb_to_cstr(StringBuilder *sb, char* str, int length) {
  if (sb->count > length - 1) {
    printf("ERROR: Provided char array is too small");
    return;
  }
  int i;
  for (i = 0; i < length - 1; i++) {
    str[i] = sb->items[i];
  }
  str[i+1] = '\0';
}

void sb_reset(StringBuilder *sb) {
  sb->count = 0;
}

void sb_free(StringBuilder *sb) {
  free(sb->items);
  sb->items = NULL;
  sb->count = 0;
  sb->capacity = 0;
}

int main() {

  StringBuilder sb = {0}; // this is stack
  sb_init(&sb, 2);

  sb_append_cstr(&sb, "abc");

  printf("%c\n", sb.items[0]);
  printf("%c\n", sb.items[1]);
  printf("%c\n", sb.items[2]);

  sb_reset(&sb);

  sb_append_cstr(&sb, "def");

  printf("%c\n", sb.items[0]);
  printf("%c\n", sb.items[1]);
  printf("%c\n", sb.items[2]);

  char a[4] = {0};

  sb_to_cstr(&sb, a, sizeof(a));

  printf("%s\n", a);


  sb_free(&sb);

  // sb.count = 0;
  // sb.capacity = 1024;
  // sb.items = malloc(1024); // ptr on stack, memory on heap
                           //
  // char* hello = "hello"; // this is a cstr
  //                        //
  //                        //
  // while(*hello != NULL) {
  //   printf("%d\n", *hello);
  //   hello = hello + 1;
  // }

  return 0;
}
