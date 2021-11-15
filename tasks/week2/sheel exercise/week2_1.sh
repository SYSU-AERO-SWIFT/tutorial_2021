main_content="/tmp/scripts"  //主目录的名字
mkdir -p $main_content //创建主目录

cd $main_content // 转到主目录下
cp -R /etc/pam.d . //将/etc/pam.d复制到主目录下

mv pam.d test  //改名
useradd redhat  //创建redhat属主
chown -R redhat $main_content/test   //将属主改为redhat
chmod -R o-x $main_content/test   //更改其他用户的权限
