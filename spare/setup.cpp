#!/bin/bash
CIPHER_DEVICE="cipher"
CIPHER_KEY_DEVICE="cipher_key"
module="cipher"
mode="664"

/sbin/rmmod $module
/sbin/insmod ./$module.ko || exit 1

rm -rf /dev/${CIPHER_DEVICE}
rm -rf /dev/${CIPHER_KEY_DEVICE}

major = $(awk "\$2==\"$module\" {print \$1}" /proc/devices)
echo "major: $major"
mknod /dev/${CIPHER_DEVICE} c $major 0
mknod /dev/${CIPHER_KEY_DEVICE} c $major 1
