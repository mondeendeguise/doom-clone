SHELL := /bin/sh
CC := clang

CFLAGS := -g -Wall
LDFLAGS :=
INCLUDE :=
DEFINES :=

FLAGS = ${CFLAGS} ${LDFLAGS} ${INCLUDE} ${DEFINES}

BINDIR := ./build
BIN := ${BINDIR}/doom-engine

SRCDIR := ./src
OBJDIR := ${BINDIR}/obj

SRC = ${wildcard ${SRCDIR}/*.c ${SRCDIR}/*/*.c}
OBJ = ${patsubst ${SRCDIR}/%.c, ${OBJDIR}/%.o, ${SRC}}

.PHONY : all run clean

all : ${BIN}

run : all
	${BIN}

${BIN} : ${OBJ}
	@mkdir -p ${dir $@}
	${CC} ${FLAGS} $^ -o $@

${OBJDIR}/%.o : ${SRCDIR}/%.c
	@mkdir -p ${dir $@}
	${CC} ${FLAGS} -c $< -o $@

clean :
	rm ${BIN}
	rm ${OBJ}
