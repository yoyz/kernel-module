#obj-m += hello-1.o
WRAPFS_VERSION="0.1"
WRAPFS_SUPER_MAGIC=12
EXTRA_CFLAGS += -DWRAPFS_VERSION=\"$(WRAPFS_VERSION)\" -DWRAPFS_SUPER_MAGIC=\"$(WRAPFS_SUPER_MAGIC)\"
#obj-m += dentry.o  file.o  inode.o  lookup.o  main.o  mmap.o  super.o
wrapfs-y += dentry.o  file.o  inode.o  lookup.o  main.o  mmap.o  super.o
#obj-m += main.o 
#obj-$(CONFIG_WRAP_FS) += wrapfs.o
obj-m += wrapfs.o
#obj-m += main.o

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
