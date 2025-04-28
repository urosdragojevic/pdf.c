BUILD=build
SRC=src
EXAMPLES=examples

${BUILD}/minimal_pdf: ${EXAMPLES}/minimal_pdf.c ${BUILD}/string_builder.o ${SRC}/string_builder.h
	gcc -o ${BUILD}/minimal_pdf ${EXAMPLES}/minimal_pdf.c ${BUILD}/string_builder.o

${BUILD}/string_builder.o:
	gcc -o ${BUILD}/string_builder.o -c ${SRC}/string_builder.c

${BUILD}: 
	mkdir -pv ${BUILD}
