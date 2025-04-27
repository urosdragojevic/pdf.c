#include<stdio.h>
#include "./string_builder.h"

size_t write_sb_to_file(StringBuilder *sb, FILE* file) {
  size_t written = fwrite(sb->items, sizeof(char), sb->count, file);
  printf("Written %zu bytes to file.\n", written);
  return written;
}

// Generates an absolutely minimal ./test.pdf file
int main() {
  FILE* file;
  file = fopen("./test.pdf", "w");

  if (file == NULL) {
    fprintf(stderr, "Could not open file.\n");
    return 1;
  }

  printf("Opened file\n");

  StringBuilder sb = {0};

  sb_init(&sb, 256);

  sb_append_cstr(&sb, "%PDF-1.7\n");
  sb_append_cstr(&sb, "1 0 obj\n    << /Type /Catalog\n       /Version 1.7\n    >>\nendobj\n");

  sb_append_cstr(&sb,"\n");

  size_t start_xref_count = sb.count; 

  sb_append_cstr(&sb,"xref\n");
  sb_append_cstr(&sb,"0 2\n");
  sb_append_cstr(&sb,"0000000000 65535 f\n");
  sb_append_cstr(&sb,"0000000009 00000 n\n");

  sb_append_cstr(&sb,"\n");

  // trailer
  sb_append_cstr(&sb,"trailer\n");
  sb_append_cstr(&sb,"    << /Size 2\n       /Root 1 0 R\n    >>\n");
  sb_append_cstr(&sb,"startxref\n");

  char count[10] = {0};
  sprintf(count, "%zu\n", start_xref_count);
  sb_append_cstr(&sb, count);

  sb_append_cstr(&sb,"%%EOF");

  write_sb_to_file(&sb, file);

  sb_free(&sb);

  // TODO: Handle errno when closing file.
  int closed = fclose(file);

  printf("Closed file.\n");


  return 0;
}
