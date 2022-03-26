# queryt - youtube query tool
# See LICENSE file for copyright and license details.

# Source Code
SRC = queryt.c src/utils.c src/video.c libs/curl.c libs/string.c libs/json.c

# Compiler
CC = cc

# Install Dir
PREFIX = /usr/local

# Libraries
LIBS = -lcurl -ljson-c

# Binary Name
BIN = queryt

## Uncomment for OpenBSD
# LIBS = -lcurl -ljson-c -I/usr/local/include -L/usr/local/lib

# Compiled Code
CLEAN = ${BIN} ${BIN}_debug

# MakeOPTS
build: clean
	${CC} -o ${BIN} ${SRC} ${LIBS}

debug: clean
	${CC} -g -o ${BIN}_debug ${SRC} ${LIBS}

clean:
	rm -rf ${CLEAN}

install: build
	mkdir -p ${PREFIX}/bin
	cp -f queryt ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp -f queryt.1 ${PREFIX}/share/man/man1
	chmod 644 ${PREFIX}/share/man/man1/${BIN}.1

uninstall:
	rm -rf ${PREFIX}/bin/${BIN}
	rm -f ${PREFIX}/share/man/man1/${BIN}.1
