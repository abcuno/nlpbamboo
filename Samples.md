# 分词Sample #
```
#include <iostream>
#include <vector>
#include <cstdlib>
#include "bamboo.hxx"
using namespace bamboo;
int main()
{
        void *handle = bamboo_init("crf_seg","/opt/bamboo/etc/crf_seg.conf");
        char *t = NULL;
        const char * text = "我爱北京天安门";
        bamboo_setopt(handle, BAMBOO_OPTION_TEXT, const_cast<char *>(text));
        t = bamboo_parse(handle);
        printf("==> %s\n", t);
        free(t);
        bamboo_clean(handle);
        return 0;
}
```
```
<?php
  bamboo_setopt("crf_seg", BAMBOO_OPTION_TEXT, "我爱北京天安门");
  echo bamboo_parse("crf_seg")."\n";
?>
```
# 词性标注Sample #
```
#include <iostream>
#include <vector>
#include <cstdlib>
#include "bamboo.hxx"
using namespace bamboo;
int main()
{
        void *handle = bamboo_init("crf_pos","/opt/bamboo/etc/crf_pos.conf");
        char *t = NULL;
        const char * text = "我爱北京天安门";
        bamboo_setopt(handle, BAMBOO_OPTION_TEXT, const_cast<char *>(text));
        t = bamboo_parse(handle);
        printf("==> %s\n", t);
        free(t);
        bamboo_clean(handle);
        return 0;
}
```

# 命名实体识别Sample #
```
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include "bamboo.hxx"
using namespace bamboo;
#define USAGE "regress_ner -t nr|ns|nt [-f input_file]"
int main(int argc, char * argv[])
{
        const char * ner_type = NULL, * input_file = NULL;
        int opt;
        while( (opt=getopt(argc, argv, "t:f:")) != -1) {
                switch(opt) {
                case 't':
                        ner_type = optarg;
                        break;
                case 'f':
                        input_file = optarg;
                        break;
                case '?':
                        printf("%s\n", USAGE);
                        exit(1);
                }
        }
        if(!ner_type) {
                printf("%s\n", USAGE);
                exit(1);
        }
        std::istream * is;
        std::ifstream fin;
        if(!input_file) {
                is = & std::cin;
        } else {
                fin.open(input_file);
                is = & fin;
        }
        std::string text = "";
        while(!is->eof()) {
                std::string line;
                getline(*is, line);
                text += line + "\n";
        }
        if(input_file) {
                fin.close();
        }
        std::vector<Token *> v;
        std::vector<Token *>::iterator it;
        char parser_name[16];
        sprintf(parser_name, "crf_ner_%s", ner_type);
        ParserFactory *factory = ParserFactory::get_instance();
        Parser *p = factory->create(parser_name);
        p->setopt(BAMBOO_OPTION_TEXT, const_cast<char *>(text.c_str()));
        p->parse(v);
        for (it = v.begin(); it != v.end(); it++) {
                std::cout << (*it)->get_orig_token() << std::endl;
                delete *it;
        }
        delete p;
        return 0;
}
```
```
<?php
  bamboo_setopt("crf_ner_nr", BAMBOO_OPTION_TEXT, "姚明和刘翔");
  echo bamboo_parse("crf_ner_nr")."\n";
  bamboo_setopt("crf_ner_ns", BAMBOO_OPTION_TEXT, "我爱北京天安门");
  echo bamboo_parse("crf_ner_ns")."\n";
  bamboo_setopt("crf_ner_nt", BAMBOO_OPTION_TEXT, "北京公安局破获重大案件");
  echo bamboo_parse("crf_ner_nt")."\n";
?>
```
# 主题词抽取Sample #
```
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include "bamboo.hxx"
using namespace bamboo;
#define USAGE "regress_ner -f input_file"
int main(int argc, char * argv[])
{
        const char * input_file = NULL;
        std::istream * is;
        std::ifstream fin;
        int opt;
        while( (opt=getopt(argc, argv, "f:")) != -1) {
                switch(opt) {
                case 'f':
                        input_file = optarg;
                        break;
                case '?':
                        printf("%s\n", USAGE);
                        exit(1);
                }
        }
        if(!input_file) {
                is = & std::cin;
        } else {
                fin.open(input_file);
                is = & fin;
        }
        std::string title = "", text = "";
        size_t i = 0;
        while(!is->eof()) {
                std::string line;
                getline(*is, line);
                if(i == 0) {
                        title = line;
                }
                else {
                        text += line + "\n";
                }
                ++i;
        }
        if(input_file) {
                fin.close();
        }
        std::vector<Token *> v;
        std::vector<Token *>::iterator it;
        ParserFactory *factory = ParserFactory::get_instance();
        Parser *p = factory->create("keyword");
        p->setopt(BAMBOO_OPTION_TITLE, const_cast<char *>(title.c_str()));
        p->setopt(BAMBOO_OPTION_TEXT, const_cast<char *>(text.c_str()));
        p->parse(v);
        for (it = v.begin(); it != v.end(); it++) {
                std::cout << (*it)->get_orig_token() << std::endl;
                delete *it;
        }
        delete p;
        return 0;
}

```