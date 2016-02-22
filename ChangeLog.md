#summary ChangeLog
#labels Featured
2010-03-31
  * 整个make系统现在以configure系统为核心运行，configure && make && make install 可以处理绝大部分问题
  * 修补了auto\_build的配置build\_settings的安装和缺省路径的bug
  * 支持源代码目录下 ./source/tools/auto\_build -t seg 的动作

2009-03-19
  * 修正了Makefile不能指定lib路径的问题，现在64位RH机器的用户不需要手工拷贝lib到lib64了
  * 修正了一个单个英文单词过长导致CRF++出错的问题
  * 修正了Trie结构的一个bug，现在32位和64位系统上可以共用同一个Trie字典了。(由于字典格式的改变用户需要重新build已有的字典)
  * 修正了当libbamboo被当作shared library引用时，会出现symbol not found的问题
  * 修正了maxforward分词方法不能正常工作的问题

2008-12-19
  * 分词配置文件中use\_break, use\_single\_combine, use\_maxforward\_combine选项现在可以正常工作了
  * 修正了一个因为缺少字典而导致PostgreSQL崩溃的Bug

2008-12-08
  * 经过weibingzheng同学的不懈努力，bamboo现在可以很好的进行命名实体的识别了。这些实体包括：人名，地名和机构名称。在此感谢weibingzheng同学的辛勤工作。
  * 同时bingzheng同学还给bamboo带来的关键词抽取模块kea
  * 根据ifengle同学的建议，我重构了bamboo的C++接口。新的接口使用factory模式来创建用于各种用途的解释器。包括：crf\_seg(crf分词), keyword(关键词提取), crf\_ner\_ns(crf地名提取),.....
  * 根据ifengle同学的建议，我们一起规范了所有的配置文件和文件中配置项的命名。
  * 为postgresql增加了关键词抽取的接口
  * prepare\_processor中无法分离连续两个标点的问题被修正了(blame me!)
  * 修正了trie字典不能正确处理\r的问题。（感谢bingzheng的提醒）
  * perl的扩展被放到了unstable中。（我们的确需要一个了解xs的同学能帮帮我们）
  * 特别感谢ifengle同学重写了许多文档，更详细地描述了bamboo的许多细节

2008-10-27
  * bamboo现在有能力进行词性标注了。
  * Bamboo现在有能力进行命名实体的识别了，其中包括人名，地名和机构名。
  * Bamboo现在有能力识别各种英文标识符了，例如: UA-1234-5678, F-15,等等
  * CRF有专有的训练脚本了，您再也不用劳神去研究如果Build一个CRF2的模型了
  * 我们努力让配置文件更加具有可读性和灵活性，虽然还有很多工作需要继续完成。
  * 很多让人头疼的Bug被修正了。
  * 改变了PHP，PostgreSQL的扩展程序结构，现在他们可以运行得更快了。

2008-10-08
  * 项目从CNLexizer更名为Bamboo

2008-09-28
  * 使用自制的山寨版simple\_config代替lua进行配置，今后bamboo将不再依赖于liublua了。
  * 对代码进行了大量的优化，速度提高5倍之多。
  * 新版本的auto\_build程序，不再需要用户自己下载语料库。该程序会自动链接code.google.com下载。
  * 在auto\_build中加入了CRF模型训练的代码