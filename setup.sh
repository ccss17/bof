#!/bin/bash

createuser() {
    sudo useradd -m -d /home/bof$1 -s $(which bash) bof$1
    echo "bof$1:bof$1" | sudo chpasswd
    sudo cp bof$1 bof$1.c /home/bof$1/
    sudo chown root:root /home/bof$1/bof$1
    sudo chmod 4755 /home/bof$1/bof$1
    sudo chown root:root /home/bof$1/bof$1.c
    sudo chmod 644 /home/bof$1/bof$1.c
    sudo cp _deploy_gdbinit /home/bof$1/.gdbinit
    sudo cp _deploy_tmux.conf /home/bof$1/.tmux.conf
}

deluser(){
    sudo userdel $1
    sudo rm -rf /home/$1
}

case "$1" in
--remove-all)
    make clean
    for i in {0..11};do
        deluser bof$i
    done
    ;;
*)
    make
    sudo cp pass /usr/local/bin/
    for i in {0..11}; do
        createuser $i
    done
;;
esac
