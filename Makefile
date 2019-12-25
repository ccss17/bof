SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: _bof1 _bof2 _bof3 _bof4 _bof5 _bof6 _bof7 _bof8 _bof9 _bof10 _bof11
_bof1:
	gcc -fno-stack-protector $@.c -o $@
_bof2:
	gcc -fno-stack-protector $@.c -o $@
_bof3:
	gcc -fno-stack-protector $@.c -o $@
_bof4:
	gcc -fno-stack-protector $@.c -o $@
_bof5:
	gcc -fno-stack-protector $@.c -o $@
_bof6:
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof7:
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof8:
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof9:
	gcc -fno-stack-protector $@.c -o $@
_bof10:
	sudo apt-get install gcc-multilib
	gcc -m32 -z execstack -fno-stack-protector $@.c -o $@
_bof11:
	gcc -fno-stack-protector $@.c -o $@ -ldl
clean:
	rm -f $(BINARIES) *.o a.out hello *.hex *.txt
