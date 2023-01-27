
CFLAGS = -O2 -Wall -pedantic -I../shared
XTABLES_SO_DIR = $(shell pkg-config xtables --variable xtlibdir)

all: libxt_evil.so libxt_MARKEVIL.so

install:
	sudo cp *.so $(XTABLES_SO_DIR)

lib%.so: lib%.o
	gcc -shared -fPIC -o $@ $^

lib%.o: lib%.c
	gcc $(CFLAGS) -D_INIT=lib$*_init -fPIC -c -o $@ $<
