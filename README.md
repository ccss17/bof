# bof

## Setup BOF CTF

```shell
git clone https://github.com/ccss17/bof
cd bof
./setup.sh
```

Then, check created bof users and their passwords

```shell
tail -n12 /etc/passwd
cat PASSWORDS
```

![check](https://user-images.githubusercontent.com/16812446/72774687-eaa4b580-3c4e-11ea-895e-b59762c8baf6.PNG)

First CTF stage is `bof1`. Login with SSH ID `bof1` and password `bof1`.

![check2](https://user-images.githubusercontent.com/16812446/72774697-f3958700-3c4e-11ea-820d-2b86ab92620e.PNG)

Then exploit `bof1` to get password of `bof2` in `bof2.pw`.

## Exploit

TODO