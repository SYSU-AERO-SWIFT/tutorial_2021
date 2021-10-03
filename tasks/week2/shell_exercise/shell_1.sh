#!/bin/bash

# make direction
mkdir /tmp/scripts
# go into 
cd /tmp/scripts
# copy -r---recursion
cp -r /etc/pam.d/ /tmp/scripts/test
# set a user
useradd redhat
chown -R redhat /tmp/scripts/test
#o others - remove 
chmod -R o- rwx /tmp/script/test


