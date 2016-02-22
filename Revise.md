## Bamboo为什么要修正分词 ##
  * Bamboo的分词可以选择多种分词算法，CRF，Unigram等，不过任何一种分词都不能保证完全正确，因此需要在主分词模块完成后，进行后续修正。
## Bamboo修正分词的方法 ##
  1. 将未分词的单字整合，user\_combine
  1. 将较长的分词结果打散，break
## Build user\_combine辞典 ##
  * 命令：
```
lexicon -b -i user_combine.idx -s user_combine.txt
```
  * user\_combine.txt格式
```
1 次贷
1 奥巴马
1 中欧
...
```
    * 第一列的数字没有意义，只是为了填充
    * 第二列是需要合并的词
  * 最后需要将user\_combine.idx拷贝到/opt/bamboo/index/目录下
## Build break辞典 ##
  * 命令：
```
lexicon -b -i break.idx -s break.txt
```
  * break.txt格式
```
41 中华人民共和国
...
```
    * 第一列的十进制数字是break标志位
```
中 华 人 民 共 和 国
0  1  0  1  0  0  1
dec(41) = bin(0101001)
```
    * 第二列是需要break的词
    * 最后需要将break.idx拷贝到/opt/bamboo/index/目录下