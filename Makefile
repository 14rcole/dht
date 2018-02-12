BUILDDIR=build
OPTS=-Wall
DEBUGOPTS=-ggdb


all: hashtable network

dir:
	mkdir -p ${BUILDDIR}

hashtable: dir
	gcc -o ${BUILDDIR}/hashtable src/libtable/*.c

debug: dir
	gcc -o ${BUILDDIR}/hashtable ${DEBUGOPTS} src/libtable/*.c

network: dir
	gcc -o ${BUILDDIR}/network src/libnetwork/*.c -lpthread

clean:
	rm -rf build
