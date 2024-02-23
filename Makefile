SHELL 	:= /bin/sh
CC 		:= clang
LINK	:= clang

CFLAGS 	:= -ggdb -Wall -Wextra -pedantic -std=c99 -Wno-gnu-zero-variadic-macro-arguments
LDFLAGS :=
LIBS	:= -lc -lm -lGL -lglfw -lGLEW
INCLUDE := -I./src
DEFINES := -D_GNU_SOURCE

FLAGS = ${CFLAGS} ${INCLUDE} ${DEFINES}

BINDIR := ./build
BIN := DOOM

SRCDIR := ./src
OBJDIR := ${BINDIR}/obj

SRC = ${wildcard ${SRCDIR}/*.c ${SRCDIR}/core/*.c ${SRCDIR}/wad/*.c}
OBJ = ${patsubst ${SRCDIR}/%.c, ${OBJDIR}/%.o, ${SRC}}

.PHONY : all run clean

all : ${BIN}

${BIN} : ${OBJ}
	@mkdir -p ${dir $@}
	@${LINK} ${LDFLAGS} ${LIBS} $^ -o $@
	@echo " LD -> $@"

${OBJDIR}/%.o : ${SRCDIR}/%.c
	@mkdir -p ${dir $@}
	@${CC} ${FLAGS} -c $< -o $@
	@echo " CC    $<"

clean :
	@rm -f ${BIN}
	@rm -f ${OBJ}
	@rm -rf ${OBJDIR}/*
	@rm -rf ${BINDIR}/*
