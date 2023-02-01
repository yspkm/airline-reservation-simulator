CC = gcc
CCFLAGS = -Wall -g
LDFLAGS = -Wl,-z,stack-size=268435456

HDIR = .
TDIR = .
TARGET = ${TDIR}/air-reservation-sim
OBJECT = main.o graph.o input.o table.o rbtree.o state.o inputgen.o
HEADERS = param.h path.h rbtree.h table.h graph.h inputgen.h

${TARGET}: ${OBJECT}
	${CC} ${LDFLAGS} ${CCFLAGS} -o ${TARGET} ${OBJECT} -lm

main.o: main.c ${HEADERS}
	${CC} ${CCFLAGS} -c main.c
state.o: state.c ${HEADERS}
	${CC} ${CCFLAGS} -c state.c
inputgen.o: inputgen.c inputgen.h
	${CC} ${CCFLAGS} -c inputgen.c
rbtree.o: rbtree.c table.o path.h param.h 
	${CC} ${CCFLAGS} -c rbtree.c
graph.o: graph.c table.o path.h param.h
	${CC} ${CCFLAGS} -c graph.c -lm
table.o: table.c param.h path.h
	${CC} ${CCFLAGS} -c table.c
input.o: input.c param.h
	${CC} ${CCFLAGS} -c input.c

clean:
	rm -f *.o ${TARGET} *a.out
