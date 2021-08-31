# queryt - youtube query tool
# See LICENSE file for copyright and license details.

# Source Code
SRC = queryt.c utils.c video.c libs/curl.c libs/string.c libs/json.c

# Libraries
LIBS = -lcurl -ljson-c

# Compiled Code
CLEAN = queryt

# MakeOPTS
build: clean
	cc -o queryt ${SRC} ${LIBS}

debug: clean
	cc -g -o queryt ${SRC} ${LIBS}

clean:
	rm -rf ${CLEAN}
