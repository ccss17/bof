#!/bin/bash

createuser() {
    sudo useradd -m -d /home/$1 -s $(which bash) $1
    echo "$1:$1" | sudo chpasswd
    sudo cp $1 $1.c /home/$1/
    sudo cp _deploy_gdbinit /home/$1/.gdbinit
    sudo cp _deploy_tmux.conf /home/$1/.tmux.conf
    sudo chown root:root /home/$1/$1
    sudo chmod 4755 /home/$1/$1
}

deluser(){
    sudo userdel $1
    sudo rm -rf /home/$1
}

case "$1" in
--remove-all)
    make clean
    for i in {0..9};do
        deluser bof$i
    done
    ;;
*)
    make
    sudo cp pass /usr/local/bin/
    for i in {0..9}; do
        createuser bof$i
    done
;;
esac
