ifneq ($(KERNELRELEASE),)
obj-m += ex2driver.o
ex2driver-objs:= main.o
else
KDIR := ~/workspace/buildroot/output/build/linux-3.7.9/
CPU := arm
TOOLS := ~/workspace/buildroot/output/host/usr/bin/arm-linux-
PWD := $(shell pwd)
MODPATH := /tftpboot/apf27-root
all: 
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(CPU) CROSS_COMPILE=$(TOOLS) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
install: 
	$(MAKE) -C $(KDIR) M=$(PWD) INSTALL_MOD_PATH=$(MODPATH) modules_install
endif
