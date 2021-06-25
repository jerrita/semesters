#!/usr/bin/env bash

#================================================
# Description: Auto add my pubkey to your vps
# Version: 1.0
# Author: Jerrita
# Designed for: OS Homework
#================================================

VERSION=1.0
RED_FONT_PREFIX="\033[31m"
LIGHT_GREEN_FONT_PREFIX="\033[1;32m"
FONT_COLOR_SUFFIX="\033[0m"
INFO="[${LIGHT_GREEN_FONT_PREFIX}INFO${FONT_COLOR_SUFFIX}]"
ERROR="[${RED_FONT_PREFIX}ERROR${FONT_COLOR_SUFFIX}]"
[ $EUID != 0 ] && SUDO=sudo

PUB_KEY="ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC7qpLwqUgPQy3bRvDyclX485ijfIXe4W2lq7VLhIsKN1xJG4fR5JdOJkMyG5c2vybEnNEKLGr/spRNWxqrmKdT+h9GUC22cl86VplDHCwE1MXXN05hvg28iH4iYPypJb2OKDUV61nnfX6gBG7SMqrWWz/YswJbPDNFMmNX9z9MwIb81Sd7mJHVIbvRBksCnnsMRFb2zsKgQC6Bai/8vwQoHE6d6B5c6zuNOxEBcTUbHdbLGTyRy+I/yd7gUrLgiuRLH0nK1j0XhUWcK1nZT/8/kB7NTiJR1M1X6wYsAYjtQvD0GxJCBQPfz+LKHkZk3+J9imNojxwFv7GHZEMEZNB7"

USAGE() {
    echo "
My SSH Key Installer $VERSION

Usage:
  bash key.sh [options...] <arg>

Options:
  -o	Overwrite mode, this option is valid at the top
  -i    Install my key
  -p	Change SSH port, the arguments is port number
  -d	Disable password login"
}


if [ $# -eq 0 ]; then
    USAGE
    exit 1
fi


install_key() {
    if [ ! -f "${HOME}/.ssh/authorized_keys" ]; then
        echo -e "${INFO} '${HOME}/.ssh/authorized_keys' is missing..."
        echo -e "${INFO} Creating ${HOME}/.ssh/authorized_keys..."
        mkdir -p ${HOME}/.ssh/
        touch ${HOME}/.ssh/authorized_keys
        if [ ! -f "${HOME}/.ssh/authorized_keys" ]; then
            echo -e "${ERROR} Failed to create SSH key file."
        else
            echo -e "${INFO} Key file created, proceeding..."
        fi
    fi
    if [ "${OVERWRITE}" == 1 ]; then
        echo -e "${INFO} Overwriting SSH key..."
        echo -e "${PUB_KEY}\n" >${HOME}/.ssh/authorized_keys
    else
        echo -e "${INFO} Adding SSH key..."
        echo -e "\n${PUB_KEY}\n" >>${HOME}/.ssh/authorized_keys
    fi
    chmod 700 ${HOME}/.ssh/
    chmod 600 ${HOME}/.ssh/authorized_keys
    [[ $(grep "${PUB_KEY}" "${HOME}/.ssh/authorized_keys") ]] &&
        echo -e "${INFO} SSH Key installed successfully!" || {
        echo -e "${ERROR} SSH key installation failed!"
        exit 1
    }
}

change_port() {
    echo -e "${INFO} Changing SSH port to ${SSH_PORT} ..."
    if [ $(uname -o) == Android ]; then
        [[ -z $(grep "Port " "$PREFIX/etc/ssh/sshd_config") ]] &&
            echo -e "${INFO} Port ${SSH_PORT}" >>$PREFIX/etc/ssh/sshd_config ||
            sed -i "s@.*\(Port \).*@\1${SSH_PORT}@" $PREFIX/etc/ssh/sshd_config
        [[ $(grep "Port " "$PREFIX/etc/ssh/sshd_config") ]] && {
            echo -e "${INFO} SSH port changed successfully!"
            RESTART_SSHD=2
        } || {
            RESTART_SSHD=0
            echo -e "${ERROR} SSH port change failed!"
            exit 1
        }
    else
        $SUDO sed -i "s@.*\(Port \).*@\1${SSH_PORT}@" /etc/ssh/sshd_config && {
            echo -e "${INFO} SSH port changed successfully!"
            RESTART_SSHD=1
        } || {
            RESTART_SSHD=0
            echo -e "${ERROR} SSH port change failed!"
            exit 1
        }
    fi
}

disable_password() {
    # if use termux
    if [ $(uname -o) == Android ]; then
        sed -i "s@.*\(PasswordAuthentication \).*@\1no@" $PREFIX/etc/ssh/sshd_config && {
            RESTART_SSHD=2
            echo -e "${INFO} Disabled password login in SSH."
        } || {
            RESTART_SSHD=0
            echo -e "${ERROR} Disable password login failed!"
            exit 1
        }
    else
        $SUDO sed -i "s@.*\(PasswordAuthentication \).*@\1no@" /etc/ssh/sshd_config && {
            RESTART_SSHD=1
            echo -e "${INFO} Disabled password login in SSH."
        } || {
            RESTART_SSHD=0
            echo -e "${ERROR} Disable password login failed!"
            exit 1
        }
    fi
}

while getopts "oip:d" OPT; do
    case $OPT in
    o)
        OVERWRITE=1
        ;;
    i)
        install_key
        ;;
    p)
        SSH_PORT=$OPTARG
        change_port
        ;;
    d)
        disable_password
        ;;
    ?)
        USAGE
        exit 1
        ;;
    :)
        USAGE
        exit 1
        ;;
    *)
        USAGE
        exit 1
        ;;
    esac
done

if [ "$RESTART_SSHD" = 1 ]; then
    echo -e "${INFO} Restarting sshd..."
    $SUDO systemctl restart sshd && echo -e "${INFO} Done."
elif [ "$RESTART_SSHD" = 2 ]; then
    echo -e "${INFO} Restart sshd or Termux App to take effect."
fi