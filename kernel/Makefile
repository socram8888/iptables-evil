
EXTRADIR := /lib/modules/$(shell uname -r)/extra
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m := xt_EVIL.o

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install: modules
	mkdir -p $(EXTRADIR)
	install -m 644 -t $(EXTRADIR) xt_EVIL.ko
	depmod

uninstall:
	$(RM) $(EXTRADIR)/xt_EVIL.ko
	depmod

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
