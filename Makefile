SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: $(BINARIES)

#%: %.c shellcode
	#gcc -fno-stack-protector -z execstack $< -o $@
	#sudo chown root:root $@
	#sudo chmod 4755 $@

bof:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof2:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof3:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof4:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof5:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof6:
	gcc -z execstack -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof7:
	gcc -z execstack -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof8:
	gcc -z execstack -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

bof9:
	gcc -fno-stack-protector $@.c -o $@
	sudo chown root:root $@
	sudo chmod 4755 $@

clean:
	rm -f $(BINARIES) *.o a.out hello *.hex *.txt
	make clean -C shellcode
