#include<stdio.h>

int length_of_string(char* str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}


size_t write_line_to_file(char* line, FILE* file) {
  size_t written = fwrite(line, sizeof(char), length_of_string(line), file);
  printf("Written %zu bytes to file.\n", written);
  return written;
}

/*
 * TODO: re-use memory for strings
 *
 * */


// Generates an absolutely minimal ./test.pdf file
int main() {
  FILE* file;
  file = fopen("./test.pdf", "w");

  if (file == NULL) {
    fprintf(stderr, "Could not open file.\n");
    return 1;
  }

  printf("Opened file\n");

  size_t start_xref_count = 0; 

  char* version = "%PDF-1.7\n";

  // sizeof(version) is size of the pointer.

  start_xref_count += write_line_to_file(version, file);

  char* catalog = "1 0 obj\n    << /Type /Catalog\n       /Version 1.7\n    >>\nendobj\n";
  start_xref_count += write_line_to_file(catalog, file);

  start_xref_count += write_line_to_file("\n", file);

  // xref table
  char* xref = "xref\n";
  write_line_to_file(xref, file);
  char* obj_num = "0 2\n";
  write_line_to_file(obj_num, file);
  char* obj_zero = "0000000000 65535 f\n";
  write_line_to_file(obj_zero, file);
  char* obj_catalog = "0000000009 00000 n\n";
  write_line_to_file(obj_catalog, file);

  write_line_to_file("\n", file);

  // trailer
  char* trailer = "trailer\n";
  write_line_to_file(trailer, file);
  char* size = "    << /Size 2\n       /Root 1 0 R\n    >>\n";
  write_line_to_file(size, file);
  char* start_xref = "startxref\n";
  write_line_to_file(start_xref, file);
  char count[10] = {0};
  sprintf(count, "%zu\n", start_xref_count);
  write_line_to_file(count, file);
  char* eof = "%%EOF";
  write_line_to_file(eof, file);

  int closed = fclose(file);

  // TODO: Handle errno when closing file.

  printf("Closed file.\n");

  return 0;
}
