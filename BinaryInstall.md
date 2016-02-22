# 下载 #

根据你的系统下载编译好的[二进制包](http://bamboo.googlecode.com/files/bamboo-1.0beta1-i686.tar.bz2)。

# 解压缩 #

sudo tar -jxvf tarball.tar.bz2 -C /

# 生成辞典和训练集 #

```
cd /opt/bamboo
bin/auto_build
```

NOTE: 由于CRF训练时间较长，训练脚本会提示您是否训练CRF模型。

# 配置 #

请参考HowToConfig

# 测试 #
```
cd /opt/bamboo
bin/lexizer
```