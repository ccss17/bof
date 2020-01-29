SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: _bof1 _bof2 _bof3 _bof4 _bof5 _bof6 _bof7 _bof8 _bof9 _bof10 _bof11
_bof1: _bof1.c
	gcc -fno-stack-protector $@.c -o $@
_bof2: _bof2.c
	gcc -fno-stack-protector $@.c -o $@
_bof3: _bof3.c
	gcc -fno-stack-protector $@.c -o $@
_bof4: _bof4.c
	gcc -fno-stack-protector $@.c -o $@
_bof5: _bof5.c
	gcc -fno-stack-protector $@.c -o $@
_bof6: _bof6.c
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof7: _bof7.c
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof8: _bof8.c
	gcc -z execstack -fno-stack-protector $@.c -o $@
_bof9: _bof9.c
	gcc -fno-stack-protector $@.c -o $@
_bof10: _bof10.c
	gcc -m32 -z execstack -fno-stack-protector $@.c -o $@
_bof11: _bof11.c older-glibc 
	mv older-glibc/2.23 .
	mv older-glibc/compile_older_glibc.sh .
	./compile_older_glibc.sh 2.23 $< $@
older-glibc:
	git clone https://github.com/ccss17/older-glibc
clean:
	rm -f $(BINARIES) 
	rm -rf older-glibc 2.23 compile_older_glibc.sh
