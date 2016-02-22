## ngm\_tool工具介绍 ##
### 从语料库中提取出NGram ###
  * 命令:
```
ngm_tool -n N -v corpus.txt > n_gram.txt
```
  * 参数解释：
    * -n N-Gram中的N，例如：N=1表示bigram; N=2表示bigram
    * -v 显示verbose信息
    * corpus.txt 是文本格式的语料文件，例如：人民日报1月分语料
    * n\_gram.txt 是输出的N-Gram文件，每行分2列，第一列表示分词的概率，第二列是分词
## lexicon工具介绍 ##
### 制作辞典索引文件 ###
  * 命令：
```
lexicon -b -i lexicon.idx -s words.txt
```
  * 参数解释：
    * -b build辞典索引
    * -i 辞典索引文件名（二进制）
    * -s 辞典文件（文本），即通过ngm\_tool从原始语料转换过来的文本辞典
### 显示辞典索引里所有的词 ###
  * 命令：
```
lexicon -d -i lexicon.idx
```
  * 参数解释：
    * -d dump辞典索引
    * -i 辞典索引文件名（二进制）
### 查询索引 ###
  * 命令
```
lexicon -q word -i lexicon.idx
```
  * 参数解释：
    * -q 查询辞典索引
    * word 目标查询词
    * -i 辞典索引文件名（二进制）
### 显示辞典索引统计信息 ###
  * 命令
```
lexicon -n -i lexicon.idx
```
  * 参数解释：
    * -n 查看辞典索引信息