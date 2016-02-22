#summary 编译和安装PostgreSQL扩展和TSearch2扩展
#labels Phase-Deploy,Featured,Phase-Implementation

# PostgreSQL 分词函数(不需要TSearch2支持) #

PostgreSQL分词函数需要安装好Bamboo的系统(不需要Bamboo源代码)和预先安装好的postgresql，编译环境需要能找到 pg\_config 命令。
如果您的系统中没有安装Bamboo，请参考：
  * 从源代码安装Bamboo：GettingStarted
  * Bamboo 二进制包安装方法：BinaryInstall

## 编译和安装 ##

```
$ cd /opt/bamboo/exts/postgresql/pg_tokenize
$ make
$ sudo make install
```

## 创建分词函数 ##
```
$ psql
postgres=# \i /usr/local/pgsql/share/contrib/pg_tokenize.sql
```

## 确保配置文件正确 ##

请确保/etc/bamboo.cfg或者/opt/etc/bamboo.cfg存在并正确配置。

## 测试 ##

```
postgres=# select tokenize('中文分词');
 tokenize  
------------
 中文 分词 
(1 row)
```

# Tsearch2 分词模块 #

Tsearch2分词模块需要安装好Bamboo的系统以及Bamboo源代码。安装Bamboo请参考GettingStarted

## 编译和安装 ##

```
$ cd /opt/bamboo/exts/postgresql/chinese_parser
$ make
$ make install
```

## 创建分词模块 ##
```
$ psql
postgres=# \i /usr/local/pgsql/share/contrib/chinese_parser.sql
```

## 测试 ##
```
postgres=# SELECT to_tsvector('chinesecfg', '我爱北京天安门');
            to_tsvector            
-----------------------------------
 '我':1 '爱':2 '北京':3 '天安门':4
(1 row)
```