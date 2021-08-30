# queryt - youtube query tool
# See LICENSE file for copyright and license details.

# Source Code
SRC = queryt.c utils.c libs/curl.c libs/string.c video.c

# Compiled Code
CLEAN = queryt

# MakeOPTS
build: clean
	cc -o queryt ${SRC} -lcurl

debug: clean
	cc -g -o queryt ${SRC} -lcurl

clean:
	rm -rf ${CLEAN}
