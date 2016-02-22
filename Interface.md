# Bamboo C++ API #
## 创建Parser Factory ##
```
ParserFactory* ParserFactory::get_instance();
```
  * 参数：无
  * 返回值：ParserFactory指针
## 创建Parser ##
```
Parser* ParserFactory::create(const char *name, const char *cfg, bool verbose);
```
  * 参数：
    * name：Bamboo Parser的name，取值可以是ugm\_seg,mfm\_seg, crf\_seg, crf\_pos, crf\_ner\_nr, crf\_ner\_ns, crf\_ner\_nt, keyword
    * cfg：Parser对应的配置文件名，缺省用/opt/bamboo/etc目录下的标准配置文件
    * verbose: 是否打印详细信息
  * 返回值：Bamboo Parser对象指针
## 设置Parser选项参数 ##
```
void Parser::setopt(enum bamboo_option option, const void *arg);
```
  * 参数：
    * option：Parser的参数名，取值可以是BAMBOO\_OPTION\_TEXT，BAMBOO\_OPTION\_TITLE，前者是所有Parser共用的，后者只在KeywordParser中使用
    * arg：Parser的参数值，即文章正文和标题的内容
  * 返回值：无
## 获取Parser参数 ##
```
const void* Parser::getopt(enum bamboo_option option);
```
  * 参数：
    * option：Parser的参数名，取值可以是BAMBOO\_OPTION\_TEXT，BAMBOO\_OPTION\_TITLE，前者是所有Parser共用的，后者只在KeywordParser中使用
  * 返回值：Parser的参数值
## Parse文本字符串 ##
```
int Parser::parse(std::vector<Token *> &out);
```
  * 参数：
    * out：Parser parse出来的结果结合，out中的token指针在使用完后需要释放
  * 返回值：Parser parse出来结果的数量

## 获取Parse出的分词 ##
```
const char* Token::get_orig_token();
```
  * 参数：无
  * 返回值：
    * 分词、实体词、主题词
## 获取Parse出的词性 ##
```
unsigned short Token::get_pos();
```
  * 参数：无
  * 返回值：
    * 词性编码
  * 词性编码转换：
    * 按照中科院和北大的词性标准，词性都是由1或者2位字符组成，例如：n，nr，v等
    * 词性的第一字符=(char)词性编码%256
    * 词性的第一字符=(char)词性编码/256

# Bamboo C API #
## 初始化Bamboo Parser ##
```
void* bamboo_init(const char *parser, const char *cfg);
```
  * 参数：
    * parser：Bamboo Parser的name，取值可以是ugm\_seg,mfm\_seg, crf\_seg, crf\_pos, crf\_ner\_nr, crf\_ner\_ns, crf\_ner\_nt, keyword
    * cfg：Parser对应的配置文件名，如果为null或者不指定，则缺省用/opt/bamboo/etc目录下的标准配置文件
  * 返回值：Bamboo Parser指针
## 设置Bamboo Parser参数 ##
```
void bamboo_setopt(void *handle, enum bamboo_option option, void *arg);
```
  * 参数：
    * handle: Bamboo Parser指针
    * option：Parser的参数名，取值可以是BAMBOO\_OPTION\_TEXT，BAMBOO\_OPTION\_TITLE，前者是所有Parser共用的，后者只在KeywordParser中使用
    * arg：Parser的参数值，即文章正文和标题的文本内容
  * 返回值：无

## 获取Bamboo Parser参数 ##
```
const void* bamboo_getopt(void *handle, enum bamboo_option option);
```
  * 参数：
    * handle: Bamboo Parser指针
    * option：Parser的参数名，取值可以是BAMBOO\_OPTION\_TEXT，BAMBOO\_OPTION\_TITLE，前者是所有Parser共用的，后者只在KeywordParser中使用
  * 返回值：Parser的参数值
## Parse输入文本 ##
```
char* bamboo_parse(void *handle);
```
  * 参数：
    * handle: Bamboo Parser指针
  * 返回值：Parser的Parse结果，各词之间用空格分开，词性会以“/”作为分隔符附加在分词后面
## 释放Bamboo Parser ##
```
void bamboo_clean(void *handle);
```
  * 参数：
    * handle: Bamboo Parser指针
  * 返回值：无
# PHP扩展接口 #
## 初始化Bamboo Parser ##
  * 通过在php.ini中添加bamboo.parsers参数，注册bamboo的各种parser，后续可以通过parser\_name来操作parser
## 设置Bamboo Parser参数 ##
```
bamboo_setopt("parser_name", bamboo_option, "arg");
```
  * 参数：
    * parser\_name: php.ini中注册的parser name
    * bamboo\_option: Parser的参数名，取值可以是BAMBOO\_OPTION\_TEXT，BAMBOO\_OPTION\_TITLE，前者是所有Parser共用的，后者只在KeywordParser中使用
    * arg: Parser的参数值，即文章正文和标题的文本内容
  * 返回值：无
## Parse输入文本 ##
```
bamboo_parse("parser_name");
```
  * 参数：
    * parser\_name: php.ini中注册的parser name
  * 返回值：Parser的Parse结果，各词之间用空格分开，词性会以“/”作为分隔符附加在分词后面