mkdir -p /temp/scripts
cd /temp/scripts
cp -r /etc/pam.d test
chown -R redhat test
chmod -R o-rwx test
