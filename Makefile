CFLAGS=-g -Wall -MD
PREFIX?=/usr
BINDIR=${DESTDIR}${PREFIX}/bin
INSTALL_BIN=install -m 0755
OBJ=spp.o
ODF=$(subst .o,.d,$(OBJ))
BIN=spp

all: ${BIN}

config.h:
	cp config.def.h config.h

${BIN}: config.h ${OBJ}
	${CC} ${LDFLAGS} -o ${BIN} ${OBJ}

symlinks:
	ln -s ${BIN} acr
	ln -s ${BIN} cpp
	ln -s ${BIN} pod
	ln -s ${BIN} sh

test:
	@for a in t/*spp* ; do \
	  echo Testing $$a ; \
	  ./spp -tspp $$a | grep BUG ; \
	  true ; \
	done

install:
	${INSTALL_BIN} spp ${BINDIR}

clean:
	-rm -f ${BIN} ${OBJ} ${ODF}

-include ${ODF}
