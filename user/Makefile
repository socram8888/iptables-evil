
CFLAGS = -O2 -Wall -pedantic -I../shared -fPIC
XTABLES_SO_DIR = $(shell pkg-config xtables --variable xtlibdir)

OBJS := libxt_evil.so libxt_MARKEVIL.so

ifeq ($(XTABLES_SO_DIR),)
	$(error Cannot find xtables path - are pkg-config and libxtables-dev installed?)
endif

all: $(OBJS)

install: $(OBJS)
	install -t $(XTABLES_SO_DIR) -m 644 $(OBJS)

lib%.so: lib%.o
	$(CC) $(CFLAGS) -shared -o $@ $<

lib%.o: lib%.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS)

uninstall:
	$(RM) $(XTABLES_SO_DIR)/libxt_evil.so
	$(RM) $(XTABLES_SO_DIR)/libxt_MARKEVIL.so
