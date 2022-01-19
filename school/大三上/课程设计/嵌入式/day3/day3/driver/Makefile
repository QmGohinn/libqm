ifeq ($(KERNELRELEASE),)
#编译ubuntu下的模块，以下的注释打开
KERNELDIR ?= /lib/modules/$(shell uname -r)/build   
#编译板子上的模块
#KERNELDIR ?= /home/farsight/linux-3.14 
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
else
  obj-m := hello.o
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module* modules*


