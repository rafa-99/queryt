# queryt - youtube query tool
# See LICENSE file for copyright and license details.

# Source Code
SRC = queryt.c src/utils.c src/video.c libs/curl.c libs/string.c libs/json.c

# Compiler Flags
FLAGS = -march=native -flto -pipe -faggressive-loop-optimizations

# Libraries
LIBS = -lcurl -ljson-c

# Compiled Code
CLEAN = queryt queryt_debug

# MakeOPTS
build: clean
	cc -o queryt ${FLAGS} ${SRC} ${LIBS}

debug: clean
	cc -g -o queryt_debug ${FLAGS} ${SRC} ${LIBS}

clean:
	rm -rf ${CLEAN}

install: build
	mkdir -p /usr/local/bin
	cp -f queryt /usr/local/bin
	chmod 755 /usr/local/bin
	mkdir -p /usr/local/share/man/man1
	cp -f queryt.1 /usr/local/share/man/man1
	chmod 644 /usr/local/share/man/man1/queryt.1

uninstall:
	rm -rf /usr/local/bin/queryt
	rm -f /usr/local/share/man/man1/queryt.1
