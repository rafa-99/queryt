# queryt - youtube query tool
# See LICENSE file for copyright and license details.

# Source Code
SRC = queryt.c src/utils.c src/video.c libs/curl.c libs/string.c libs/json.c

# Compiler
CC = cc
CFLAGS = -Wall

# Install Dir
PREFIX = /usr/local

# Libraries
LDFLAGS = -lcurl -ljson-c
## Uncomment for OpenBSD
# LDFLAGS = -lcurl -ljson-c -I/usr/local/include -L/usr/local/lib

# Binary Name
BIN = queryt


# Compiled Code
CLEAN = ${BIN} ${BIN}_debug

# MakeOPTS
build: clean
	${CC} ${CFLAGS} -o ${BIN} ${SRC} ${LDFLAGS}

debug: clean
	${CC} ${CFLAGS} -g -o ${BIN}_debug ${SRC} ${LDFLAGS}

clean:
	rm -rf ${CLEAN}

install: build
	mkdir -p ${PREFIX}/bin
	cp -f ${BIN} ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp -f ${BIN}.1 ${PREFIX}/share/man/man1
	chmod 644 ${PREFIX}/share/man/man1/${BIN}.1

uninstall:
	rm -rf ${PREFIX}/bin/${BIN}
	rm -f ${PREFIX}/share/man/man1/${BIN}.1
