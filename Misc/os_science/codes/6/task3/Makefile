CONFIG_MODULE_SIG = n
ifneq ($(KERNELRELEASE),)
	obj-m := proc_mkdir.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
