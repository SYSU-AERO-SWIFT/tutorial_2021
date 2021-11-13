#!/bin/bash

#显示系统日期和时间并创建目录
date
mkdir /tmp/lstest

#切换工作目录
cd /tmp/lstest

#创建目录和文件
mkdir a1d
mkdir b56e
mkdir 6test
touch xy
touch x2y
touch 732

#列出目标文件或目录
ls a* x* 6*

#列出以字母开头后跟一个任意数字，再跟任意长度字符的文件或目录
ls [\<[:alpha:][:digit:]]*

#参考资料
# https://blog.csdn.net/I_peter/article/details/51098461?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163331925516780357259603%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=163331925516780357259603&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-17-51098461.first_rank_v2_pc_rank_v29&utm_term=linux%E6%9F%A5%E6%89%BE%E4%BB%A5%E5%AD%97%E6%AF%8D%E5%BC%80%E5%A4%B4%E7%9A%84%E6%96%87%E4%BB%B6&spm=1018.2226.3001.4187
# https://blog.csdn.net/apple2417/article/details/103107764?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163331918716780366530761%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=163331918716780366530761&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-103107764.first_rank_v2_pc_rank_v29&utm_term=linux+%E5%88%97%E5%87%BA%E5%AD%97%E6%AF%8D%E5%BC%80%E5%A4%B4%E5%90%8E%E8%B7%9F%E6%95%B0%E5%AD%97&spm=1018.2226.3001.4187
