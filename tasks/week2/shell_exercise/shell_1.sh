#!/bin/bash

#创建工作目录
mkdir /tmp/scripts

#切换工作目录至此目录
cd /tmp/scripts

#复制并重命名
# -r表示递归操作，./表示当前目录
cp -r /etc/pam.d/ ./test

#更改属主
chown - R redhat ./test

#修改其他用户权限为没有任何权限
chmod -R  o=0  ./test

# 参考资料
# https://blog.csdn.net/ao1886/article/details/107687440?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163331771216780366587135%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=163331771216780366587135&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-107687440.first_rank_v2_pc_rank_v29&utm_term=%E5%A4%8D%E5%88%B6+%E7%9B%AE%E5%BD%95%E8%87%B3%E5%BD%93%E5%89%8D%E7%9B%AE%E5%BD%95%EF%BC%8C%E5%B9%B6%E9%87%8D%E5%91%BD%E5%90%8D&spm=1018.2226.3001.4187
#https://blog.csdn.net/qq_38701476/article/details/86153921?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163331807016780366569184%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163331807016780366569184&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-86153921.first_rank_v2_pc_rank_v29&utm_term=linux%E4%BF%AE%E6%94%B9%E5%85%B6%E4%BB%96%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90&spm=1018.2226.3001.4187
