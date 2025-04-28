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

size_t write_sb_to_file(StringBuilder *sb, FILE* file) {
  size_t written = fwrite(sb->items, sizeof(char), sb->count, file);
  printf("Written %zu bytes to file.\n", written);
  return written;
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

