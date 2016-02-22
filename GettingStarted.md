## Bamboo项目介绍 ##
  1. Bamboo项目是一个基于机器学习技术的中文自然语言处理平台。
  1. Bamboo项目的主要目标：
    * 中文分词
    * 词性标注
    * 命名实体识别
    * 主题词抽取
## Bamboo安装部署 ##
### 方法一: 安装打过包的最新稳定版 ###
  1. 下载源代码
    * http://nlpbamboo.googlecode.com/files/nlpbamboo-1.1.2.tar.bz2
  1. 安装CRF++工具包
    * 请参考 http://crfpp.sourceforge.net
  1. 安装CMake编译环境
    * Slackware 默认自带CMake
    * Ubuntu & Debian 系统使用: apt-get install cmake
    * archlinux系统: 使用pacman -S cmake
    * 其他Linux/Unix系统，请去CMake官方下载源代码编译。地址是:http://www.cmake.org
    * 注：cmake需要2.6版本以上
  1. 使用CMake编译Bamboo
```
cd bamboo
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=release
make all
```
  1. 安装Bamboo到/opt/bamboo目录
```
make install
```
  1. 编译Bamboo PHP扩展
```
cd /opt/bamboo/exts/php
phpize
make
```
  1. 安装Bamboo PHP扩展
```
make install
```

  1. 安装后Bamboo的目录结构
    * /opt/bamboo/bin/ : 可执行程序和训练脚本文件
    * /opt/bamboo/etc/ : 配置文件
    * /opt/bamboo/template/ : CRF训练模板文件 (.tmpl)
    * /opt/bamboo/processor/ : processor库
    * /opt/bamboo/exts/ : 扩展接口
    * /usr/lib/ : 动态链接库
    * /usr/include/bamboo/ : C/C++的头文件
### 方法二：安装测试svn trunk的最新源码 ###

  1. 从google code的subversion导出最新的bamboo trunk源码:
    * svn checkout http://nlpbamboo.googlecode.com/svn/trunk/ nlpbamboo
    * mkdir build; cd build; ../configure; make; make install
    * 不再强制安装在/opt/bamboo，make后可以直接使用

## Bamboo配置 ##
  1. Bamboo安装完成后，其默认的配置文件都在/opt/bamboo/etc/目录下，每个Bamboo Parser都有自己的配置文件
  1. Bamboo配置方法可以参见[Bamboo Configure Guide](http://code.google.com/p/nlpbamboo/wiki/Configure)，建议初次使用者保留参数不变;对于对程序内部流程相对了解的高级用户，可以根据需要对参数进行调整
  1. 在php.ini配置文件中添加如下2行：
    * extension = bamboo.so
    * bamboo.parsers = crf\_seg,crf\_pos，crf\_ner\_ns, keyword

## Bamboo训练统计 ##
  1. Bamboo中的分词，词性标注和命名实体识别算法都是基于由字构词的文本标注思想，因此在使用Bamboo之前需要准备好已完成标注的的文本语料，然后使用CRF++工具包和相应的特征模板进行训练，最终得出各自的字典，统计信息和模型文件
  1. Bamboo中的主题词抽取是在TF和IDF的基础上，用词句关系图分析的算法计算所有分词的权重，最终给出Top权重词，因此在使用Bamboo的主题词抽取前也需要收集一定规模的文本语料，对其中的分词进行统计和训练，得出各种词的IDF和同现关系，以供抽取时计算使用。
  1. Bamboo训练工具：
```
/opt/bamboo/bin/auto_build -t [train_type] -f [train_file.txt] -d [train_dir] -p [thread_number]
```
  1. auto\_build的训练参数：
    * -t 选项指定了训练的类型，即是分词、词性、实体词还是主题词的训练
    * -f 选项指定了训练语料的路径，缺省会自动下载98年人民日报1月份的文章作为语料
    * -d 选项指定了训练语料的目录，该目录下的.txt文本文件会被当做主题词抽取的语料
    * -p 选项指定了CRF++训练的线程数量，推荐和cpu数量一致
  1. auto\_build的配置文件是/opt/bamboo/etc/build\_settings，默认训练完成后，会在/opt/bamboo/下产生2个新目录：data/和index/
    * data目录中存放了文本格式的语料和字典文件
    * index目录中存放了二进制格式的训练model和字典trie树文件
  1. 除了缺省字典，Bamboo还为用户提供了自定义字典的工具lexicon，其具体方法请参考[Bamboo Tools](http://code.google.com/p/nlpbamboo/wiki/Tools)，用户可以使用lexicon定制自己的user\_combine和break辞典，其功能如下所示：
    * 次 贷 =>  次贷
    * 雅虎口碑 => 雅虎 口碑

### 在代码树中训练模型 ###

在svn co出来的代码树里面，我们可以直接用下面命令训练模型（在代码树根目录下）：

```
./source/tools/auto_build -t seg
```

生成的字典文件会在代码树根目录下的 index 目录里。

## Bamboo测试 ##
  1. Bamboo命令行接口：
```
/opt/bamboo/bin/bamboo -p [bamboo_parser] -c [bamboo_cfg]
```
  1. -p 选项的取值可以是crf\_seg, crf\_pos, crf\_ner\_nr, crf\_ner\_ns, crf\_ner\_nt, keyword，分别对应相应的Bamboo Parser
  1. -c 选项可以指定配置文件的路径，缺省会用/opt/bamboo/etc/目录下默认的配置文件
  1. Bamboo命令从标准输入接收文本，并根据不同的Parser选项输出相应的结果，例如：分词，词性，地名，主题词等