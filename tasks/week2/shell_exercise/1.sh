mkdir -p /tmp/scripts
cd /tmp/scripts
cp -r /etc/pam.d /tmp/scripts/test
chown -R redhat test
chmode -R o- test
