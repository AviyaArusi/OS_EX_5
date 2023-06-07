# obj-m += encryptedmem.o

# KDIR := /lib/modules/$(shell uname -r)/build
# PWD := $(shell pwd)

# all:
# 	$(MAKE) -C $(KDIR) M=$(PWD) modules

# clean:
# 	$(MAKE) -C $(KDIR) M=$(PWD) clean


obj-m += encryptedmem.o
encryptedmem-objs := main.o ioctl.o memory.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
