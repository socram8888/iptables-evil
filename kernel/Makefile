
EXTRADIR := /lib/modules/$(shell uname -r)/extra
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

ccflags-y := -I$(src)/../shared
obj-m := xt_evil.o xt_MARKEVIL.o

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install: modules
	mkdir -p $(EXTRADIR)
	install -m 644 -t $(EXTRADIR) xt_evil.ko xt_MARKEVIL.ko
	depmod

uninstall:
	$(RM) $(EXTRADIR)/xt_evil.ko $(EXTRADIR)/xt_MARKEVIL.ko
	depmod

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
