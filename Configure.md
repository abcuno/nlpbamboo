## Bamboo配置方案 ##
  * Bamboo Framework的核心主要由Processors和Parsers两层构成，配置选项和参数主要对应Parsers层，即每个Parser都有自己的配置文件
  * 配置文件和Parser的对应关系：
    * /opt/bamboo/etc/ugm\_seg.conf - 基于Unigram算法的分词Parser
    * /opt/bamboo/etc/crf\_seg.conf - 基于CRF模型的分词Parser
    * /opt/bamboo/etc/crf\_pos.conf - 基于CRF模型的词性标注Parser
    * /opt/bamboo/etc/crf\_ner\_nr.conf - 基于CRF模型的人名识别Parser
    * /opt/bamboo/etc/crf\_ner\_ns.conf - 基于CRF模型的地名识别Parser
    * /opt/bamboo/etc/crf\_ner\_nt.conf - 基于CRF模型的机构名识别Parser
    * /opt/bamboo/etc/keyword.conf - 主题词抽取Parser
    * /opt/bamboo/etc/build\_settings - autobuild训练程序
## Bamboo配置文件格式 ##
  * 以#开头的行为注释行
  * 可以使用$符号进行变量引用，可以使用\逃逸
  * 每一行配置为一个Key-Value对，用等号分割
## 分词主要参数 ##
  * root : bamboo的根目录，默认是/opt/bamboo
  * processor\_root : processor的根目录，默认是/opt/bamboo/processor/
  * max\_token\_length : 最大分词长度
  * crf\_seg\_model : 分词CRF模型文件的路径
  * use\_single\_combine: 是否使用单字合并
  * single\_combination\_lexicon: 单字合并字典路径
  * use\_break: 是否使用分词打散
  * break\_lexicon: 分词打散字典路径
  * break\_min\_length: 需要打散单词的最短长度
  * ele\_lambda: unigram分词的ELE平滑系数
## 词性标注主要参数 ##
  * 词性标注前需要先CRF分词，这部分和CRF分词参数一致
  * crf\_pos\_model : 词性标注CRF模型文件的路径
## 命名实体识别主要参数 ##
  * ner\_output\_type : 实体识别的输出类型，
    * 0：只输出实体词
    * 1：输出所有词，实体词有标志位
  * crf\_ner_[nr/ns/nt]_model : 命名实体CRF模型文件的路径
## 主题词抽取主要参数 ##
  * ke\_token\_id\_dict :  词语的id文件
  * ke\_token\_aff\_dict : 词与词之间的同现关系（语料统计）
  * ke\_token\_df\_dict : 词的文档频率（语料统计）
  * ke\_filter\_dict :  过滤词表
  * ke\_top\_n : 输出的主题词数量
  * ke\_algorithm : 主题词的抽取算法类型，默认是基于图的，可以选择传统的TF/IDF的，前者质量相对好，后者速度相对快
  * 主题词抽取在算法上还有一些数学参数，可以参见配置文件的内部注释