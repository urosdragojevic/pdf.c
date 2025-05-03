BUILD=build
SRC=src
EXAMPLES=examples

all: ${BUILD}/hello_world_pdf ${BUILD}/minimal_pdf

${BUILD}/hello_world_pdf: ${EXAMPLES}/hello_world_pdf.c ${BUILD}/string_builder.o ${SRC}/string_builder.h
	gcc -o ${BUILD}/hello_world_pdf ${EXAMPLES}/hello_world_pdf.c ${BUILD}/string_builder.o

${BUILD}/minimal_pdf: ${EXAMPLES}/minimal_pdf.c ${BUILD}/string_builder.o ${SRC}/string_builder.h
	gcc -o ${BUILD}/minimal_pdf ${EXAMPLES}/minimal_pdf.c ${BUILD}/string_builder.o

${BUILD}/string_builder.o:
	gcc -o ${BUILD}/string_builder.o -c ${SRC}/string_builder.c

${BUILD}: 
	mkdir -pv ${BUILD}
