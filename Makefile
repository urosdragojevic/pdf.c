pdf: pdf.c string_builder.o string_builder.h
	gcc -o pdf pdf.c string_builder.o
