#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include "../src/string_builder.h"


static char temp_mem[1024] = {0};

// Causes buffer overflow if length of string is greater than size of temp_mem
char* temp_sprintf(char *format, ...) {
  va_list args;
  va_start(args, format);
  vsprintf(temp_mem, format, args);
  va_end(args);
  return temp_mem;
}

// PDF contains catalog and pages
int main() {
  FILE* file;
  file = fopen("./hello_world.pdf", "w");

  if (file == NULL) {
    fprintf(stderr, "Could not open file.\n");
    return 1;
  }

  printf("Opened file\n");

  StringBuilder sb = {0};

  sb_init(&sb, 256);

  size_t objects[10] = {0};

  int obj_count = 0;

  sb_append_cstr(&sb, "%PDF-1.7\n");

  objects[obj_count] = sb.count;
  obj_count++;

  sb_append_cstr(&sb, "1 0 obj\n");
  sb_append_cstr(&sb, "<< /Type /Catalog\n");
  sb_append_cstr(&sb, "   /Version 1.7\n");
  sb_append_cstr(&sb, "   /Pages 2 0 R\n");
  sb_append_cstr(&sb, ">>\n");
  sb_append_cstr(&sb, "endobj\n");

  sb_append_cstr(&sb,"\n");

  objects[obj_count] = sb.count;
  obj_count++;

  // Add pages
  sb_append_cstr(&sb, "2 0 obj\n");
  sb_append_cstr(&sb, "<< /Type /Pages\n");
  sb_append_cstr(&sb, "   /Kids [3 0 R]\n");
  sb_append_cstr(&sb, "   /Count 1\n");
  sb_append_cstr(&sb, ">>\n");
  sb_append_cstr(&sb, "endobj\n");
  sb_append_cstr(&sb,"\n");

  objects[obj_count] = sb.count;
  obj_count++;

  sb_append_cstr(&sb, "3 0 obj\n");
  sb_append_cstr(&sb, "<< /Type /Page\n");
  sb_append_cstr(&sb, "   /Parent 2 0 R\n");
  sb_append_cstr(&sb, "   /Mediabox [0 0 612 792]\n");
  sb_append_cstr(&sb, "   /Contents 4 0 R\n");
  sb_append_cstr(&sb, "   /Resources <<  /Font << /F1 5 0 R >>  >>");
  sb_append_cstr(&sb, ">>\n");
  sb_append_cstr(&sb, "endobj\n");
  sb_append_cstr(&sb,"\n");

  objects[obj_count] = sb.count;
  obj_count++;

  sb_append_cstr(&sb, "4 0 obj\n");
  sb_append_cstr(&sb, "<< /Length 43 >>\n");
  sb_append_cstr(&sb, "stream\n");
  sb_append_cstr(&sb, "    BT\n");
  sb_append_cstr(&sb, "        /F1 24 Tf\n");
  sb_append_cstr(&sb, "        100 100 Td\n");
  sb_append_cstr(&sb, "        (Hello World) Tj\n");
  sb_append_cstr(&sb, "    ET\n");
  sb_append_cstr(&sb, "endstream\n");
  sb_append_cstr(&sb, "endobj\n");
  sb_append_cstr(&sb,"\n");

  objects[obj_count] = sb.count;
  obj_count++;

  sb_append_cstr(&sb, "5 0 obj\n");
  sb_append_cstr(&sb, "<< /Type /Font\n");
  sb_append_cstr(&sb, "   /Subtype /Type1\n");
  sb_append_cstr(&sb, "   /Name /F1\n");
  sb_append_cstr(&sb, "   /BaseFont /Helvetica\n");
  sb_append_cstr(&sb, "   /Encoding /MacRomanEncoding\n");
  sb_append_cstr(&sb, ">>\n");
  sb_append_cstr(&sb, "endobj\n");
  sb_append_cstr(&sb,"\n");

  size_t start_xref_count = sb.count;

  sb_append_cstr(&sb,"xref\n");

  sb_append_cstr(&sb, temp_sprintf("0 %d\n", obj_count + 1));

  sb_append_cstr(&sb, "0000000000 65535 f\n");

  for (int i = 0; i < obj_count; i++) {
    sb_append_cstr(&sb,  temp_sprintf("%010zu 00000 n\n", objects[i]));
  }

  sb_append_cstr(&sb, "\n");

  // trailer
  sb_append_cstr(&sb, "trailer\n");
  sb_append_cstr(&sb, temp_sprintf(
                      "<< /Size %d\n", obj_count + 1));
  sb_append_cstr(&sb, "   /Root 1 0 R\n");
  sb_append_cstr(&sb, ">>\n");
  sb_append_cstr(&sb,"startxref\n");

  sb_append_cstr(&sb, temp_sprintf("%zu\n", start_xref_count));

  sb_append_cstr(&sb,"%%EOF");

  write_sb_to_file(&sb, file);

  sb_free(&sb);

  int errno = fclose(file);
  if (errno != 0) {
      fprintf(stderr, "Error closing file: %s", strerror(errno));
  }

  printf("Closed file.\n");

  return 0;
}
