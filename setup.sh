#!/bin/bash

FINAL_STAGE=12

setting_ctf() {
    USER="bof$1"
    echo "$USER:$2" | sudo chpasswd
    if [[ $1 != $FINAL_STAGE ]]; then
        PWN="bof$(($1 + 1))"
        BIN="/home/$USER/$USER"
        SRC="/home/$USER/$USER.c"
        sudo cp _$USER /home/$USER/$USER
        sudo cp _$USER.c /home/$USER/$USER.c
        #sudo chown $PWN:$USER $BIN
        sudo chown $PWN:$PWN $BIN
        sudo chmod 6555 $BIN
        sudo chown root:root $SRC
        sudo chmod 644 $SRC
    else
        echo "R=\"\e[1;31m\"
C=\"\e[1;36m\"
E=\"\e[0m\"
echo -e \$R \"Congratulations!\"
echo -e \$C \"You solved all BOF CTFs.\" \$E
exit" | sudo tee /home/$USER/.bashrc
    fi
}

cleanup(){
    make clean
    for ((i=1; i<=$FINAL_STAGE; i++)); do
        sudo userdel bof$i
        sudo rm -rf /home/bof$i
        sudo rm -rf _bof$i.c
    done
}

main(){
    case "$1" in
    --remove)
        cleanup
        ;;
    *)
        # compile
        # create users
        for ((i=1; i<=$FINAL_STAGE; i++)); do
            sudo useradd -m -d /home/bof$i -s $(which bash) bof$i
        done
        for ((i=2; i<=$FINAL_STAGE; i++)); do
            _UID=$(cat /etc/passwd | grep "bof$i:" | cut -d ':' -f3)
            sed 's/UID_BOF'$i'/'$_UID'/g' bof$((i - 1)).c > _bof$((i - 1)).c
        done
        make
        for ((i=1; i<=$FINAL_STAGE; i++)); do
            if [[ $i == "1" ]]; then
                PASSWORD="bof1"
            else
                PASSWORD=$(cat /dev/urandom | hexdump -n 4 -e '"%02x"')
                PW_FILE="bof$i.password"
                echo $PASSWORD > $PW_FILE
                sudo mv $PW_FILE /home/bof$((i - 1))
                FLAG=/home/bof$((i - 1))/$PW_FILE
                sudo chown root:bof$i $FLAG
                sudo chmod 440 $FLAG
            fi
            setting_ctf $i $PASSWORD
        done
    ;;
    esac
}

main $@
