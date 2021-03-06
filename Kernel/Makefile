#!Makefile
#
# --------------------------------------------------------
#
#    hurlex 这个小内核的 Makefile
#    默认使用的C语言编译器是 GCC、汇编语言编译器是 nasm
#
# --------------------------------------------------------
#

# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm
RM = rm
#must add '-fno-pic' option to clean '__x86.get_pc_thunk_ax()' up 
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -fno-pic -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

# The automatic variable `$<' is just the first prerequisite
.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o Fucker_kernel

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) Fucker_kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt
	sudo cp Fucker_kernel /mnt/Fucker_kernel
	sleep 1
	sudo umount /mnt

.PHONY:mount_image
mount_image:
	sudo mount floppy.img /mnt

.PHONY:umount_image
umount_image:
	sudo umount /mnt

.PHONY:qemu
qemu:
	qemu-system-i386 -fda floppy.img -boot a

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc.txt

.PHONY:debug
debug:
	qemu-system-i386 -S -s -fda floppy.img -boot a &
	sleep 1
	cgdb -x scripts/gdbinit
