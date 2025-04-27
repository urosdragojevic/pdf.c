#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

typedef struct StringBuilder {
  char* items;
  size_t count;
  size_t capacity;
} StringBuilder;

void sb_init(StringBuilder *sb, size_t initial_capacity);

void sb_append_cstr(StringBuilder *sb, char *c);

void sb_to_cstr(StringBuilder *sb, char* str, int length);

void sb_reset(StringBuilder *sb);

void sb_free(StringBuilder *sb);

#endif
