# Customize to fit your system

SRCDIR = ./src
BLDDIR = ./build

# paths
PREFIX = /usr/local

# includes and libs
LIBS = -L${PREFIX}/lib -L/usr/lib

# Linux/BSD
CFLAGS = -std=c++11 -O3 -Wall -Wno-unknown-pragmas -I. -I${PREFIX}/include -I/usr/include
#LDFLAGS = ${LIBS} ../libjackcpp.a `pkg-config --libs jack`
LDFLAGS = ${LIBS} -ljackcpp -ljack -lpthread -lrt -larmadillo -lsndfile 

CC = g++


SRC = \
	${SRCDIR}/wdfLooper.cpp \
	${SRCDIR}/potis/potis.cpp \
	${SRCDIR}/PI/singlesample.cpp \
	${SRCDIR}/rt-wdf_lib/Libs/rt-wdf/rt-wdf.cpp \
	${SRCDIR}/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlModels.cpp \
	${SRCDIR}/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlSolvers.cpp

	
TARGETS = ${SRC:.cpp=}
OBJ = ${SRC:.cpp=.o}

all: ${TARGETS} out

%: %.cpp
	@echo CC $<
	@${CC} -c ${CFLAGS} -o $@.o $@.cpp ${LDFLAGS}

out:
	@echo OUT ${BLDDIR}/wdfLooper
	@mkdir -p build
	@${CC} ${CFLAGS} -o ${BLDDIR}/wdfLooper ${OBJ} ${LDFLAGS}

clean:
		@rm -f *.o ${OBJ}