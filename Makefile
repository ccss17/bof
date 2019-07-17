SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: $(BINARIES) 
	make -C pwntest
	sudo chown root:root $(BINARIES)
	sudo chmod 4755 $(BINARIES)

#%: %.c shellcode
	#gcc -fno-stack-protector -z execstack $< -o $@
	#sudo chown root:root $@
	#sudo chmod 4755 $@
bof0:
	gcc -fno-stack-protector $@.c -o $@
bof1:
	gcc -fno-stack-protector $@.c -o $@
bof2:
	gcc -fno-stack-protector $@.c -o $@
bof3:
	gcc -fno-stack-protector $@.c -o $@
bof4:
	gcc -fno-stack-protector $@.c -o $@
bof5:
	gcc -fno-stack-protector $@.c -o $@
bof6:
	gcc -z execstack -fno-stack-protector $@.c -o $@
bof7:
	gcc -z execstack -fno-stack-protector $@.c -o $@
bof8:
	gcc -z execstack -fno-stack-protector $@.c -o $@
bof9:
	gcc -fno-stack-protector $@.c -o $@
bof10:
	sudo apt-get install gcc-multilib
	gcc -m32 -z execstack -fno-stack-protector $@.c -o $@
bof11:
	gcc -fno-stack-protector $@.c -o $@ -ldl
clean:
	rm -f $(BINARIES) *.o a.out hello *.hex *.txt
	make clean -C pwntest
