BINARY := char_dev
BUILD := /lib/modules/$(shell uname -r)/build
obj-m := $(BINARY).o

all:
        make -C $(BUILD) M=$(PWD) modules

install:
        sudo insmod $(BINARY).ko

remove:
        sudo rmmod $(BINARY)

clean:
        make -C $(BUILD) M=$(PWD) clean