SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: $(BINARIES) 
	make -C pwntest

#%: %.c shellcode
	#gcc -fno-stack-protector -z execstack $< -o $@
	#sudo chown root:root $@
	#sudo chmod 4755 $@

bof:
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

clean:
	rm -f $(BINARIES) *.o a.out hello *.hex *.txt
	make clean -C pwntest
