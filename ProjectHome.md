**由于各种原因,该项目已经长期无人维护.如果有人对这个项目的维护感兴趣欢迎联系我<jianingy.yang AT gmail DOT com>**

![http://nlpbamboo.googlecode.com/files/bamboo.png](http://nlpbamboo.googlecode.com/files/bamboo.png)&lt;wiki:gadget url="http://www.ohloh.net/projects/nlpbamboo/widgets/project\_users.xml" height="100"  border="0" /&gt;
# 最新更新 #

Bamboo 1.1.1 重要更新

Bamboo 1.1.1正式发布，请点击右侧的Feature Download进行下载。该版本修正了一些愁人的Bug。

## Changelog ##
1.1.1:
  * 修正了Makefile不能指定lib路径的问题，现在64位RH机器的用户不需要手工拷贝lib到lib64了
  * 修正了一个单个英文单词过长导致CRF++出错的问题
  * 修正了Trie结构的一个bug，现在32位和64位系统上可以共用同一个Trie字典了。(由于字典格式的改变用户需要重新build已有的字典)
  * 修正了当libbamboo被当作shared library引用时，会出现symbol not found的问题
  * 修正了maxforward分词方法不能正常工作的问题

特别感谢agentzh 和 杨波 在百忙之中抽出时间帮我进行测试！

1.1.0:

  * 分词配置文件中use\_break, use\_single\_combine, use\_maxforward\_combine选项现在可以正常工作了
  * 修正了一个因为缺少字典而导致PostgreSQL崩溃的Bug

1.1.0 rc1:

  * 经过weibingzheng同学的不懈努力，bamboo现在可以很好的进行命名实体的识别了。这些实体包括：人名，地名和机构名称。在此感谢weibingzheng同学的辛勤工作。
  * 同时bingzheng同学还给bamboo带来的关键词抽取模块kea
  * 根据ifengle同学的建议，我重构了bamboo的C++接口。新的接口使用factory模式来创建用于各种用途的解释器。包括：crf\_seg(crf分词), keyword(关键词提取), crf\_ner\_ns(crf地名提取),.....
  * 根据ifengle同学的建议，我们一起规范了所有的配置文件和文件中配置项的命名。
  * 为postgresql增加了关键词抽取的接口
  * prepare\_processor中无法分离连续两个标点的问题被修正了(blame me!)
  * 修正了trie字典不能正确处理\r的问题。（感谢bingzheng的提醒）
  * perl的扩展被放到了unstable中。（我们的确需要一个了解xs的同学能帮帮我们）
  * 特别感谢ifengle同学重写了许多文档，更详细地描述了bamboo的许多细节

# Case #

  * [eeee工程队](http://www.eeeeworks.org)
  * [jianingy的blog](http://blog.jianingy.com)

# NLPBamboo Widget #

如果您觉得NLPBamboo好使，我们希望您能在您的页面上加入NLPBamboo的小图标：https://www.ohloh.net/projects/nlpbamboo/widgets

如果您在使用Bamboo，请让我们知道。我们非常愿意了解您在使用中得出的意见和经验。

# 简介 #

bamboo是一个中文语言处理系统。目前包括中文分词和词性标注部分。

bamboo提供了C,PHP,PostgreSQL的编程接口。
详情请参考:
  * [ApplicationInterface](ApplicationInterface.md)
  * [InstallPHPExtension](InstallPHPExtension.md)
  * [TSearch2](TSearch2.md)

# BENCHMARK #

使用Bakeoff2005工具进行测试的结果： [Benchmark](Benchmark.md)