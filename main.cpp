#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Tag {
    public:
        Tag(std::string tag_name) {
            this->tag_name = tag_name;
        }
        Tag(std::string tag_name, std::vector<Tag*> child_tags) {
            this->tag_name = tag_name;
            this->child_tags = child_tags;
        }
        ~Tag() {
            for (Tag *c : child_tags) delete c;
        }
        virtual std::string to_string() {
            std::string str = "<" + tag_name + ">\n";
            for (Tag* c : child_tags) str += c->to_string();
            str += "</" + tag_name + ">\n";
            return str;
        }
    protected:
        std::string tag_name;
        std::vector<Tag*> child_tags;
};

class A_Tag : public Tag {
    public:
        A_Tag(std::string href_url) : Tag("a") {
            this->href_url = href_url;
        }
        A_Tag(std::string href_url, std::vector<Tag*> child_tags) : Tag("a", child_tags) {
            this->href_url = href_url;
        }
        std::string to_string() override {
            std::string str = "<" + tag_name + " href=\"" + href_url + "\">\n";
            for (auto c : child_tags) str += c->to_string();
            str += "</" + tag_name + ">\n";
            return str;
        }
    private:
        std::string href_url;
};

class Img_Tag : public Tag {
    public:
        Img_Tag(std::string img_src) : Tag("img") {
            this->img_src = img_src;
        }
        Img_Tag(std::string img_src, std::string alt_text) : Tag("img") {
            this->img_src = img_src;
            this->alt_text = alt_text;
        }
        Img_Tag(std::string img_src, std::vector<Tag*> child_tags) : Tag("img", child_tags) {
            this->img_src = img_src;
        }
        Img_Tag(std::string img_src, std::string alt_text, std::vector<Tag*> child_tags) : Tag("img", child_tags) {
            this->img_src = img_src;
            this->alt_text = alt_text;
        }
        std::string to_string() override {
            std::string str = "<" + tag_name + " src=\"" + img_src + "\" alt=\"" + alt_text + "\">\n";
            for (auto c : child_tags) str += c->to_string();
            str += "</" + tag_name + ">\n";
            return str;
        }
    private:
        std::string img_src;
        std::string alt_text;
};

class Link_Tag : public Tag {
    public:
        Link_Tag(std::string rel, std::string href) : Tag("link") {
            this->rel = rel;
            this->rel = href;
        }
        std::string to_string() override {
            return "<link rel=\"" + rel + "\" href=\"" + href + "\">\n";
        }
    private:
        std::string rel;
        std::string href;
};

class Unary_Tag : public Tag {
    public:
        Unary_Tag(std::string tag_name) : Tag(tag_name) {}
        std::string to_string() override {
            return "<" + tag_name + " />\n";
        }
};

int main() {
    std::cout << "Hello from the C++ HTML DSL world " << std::endl << std::endl;

    Tag *root = new Tag("root_tag", std::vector<Tag*>{
            new Tag("new_tag"),
            new A_Tag("www.twitch.tv", std::vector<Tag*>{
                new Img_Tag("twitch.png")
            }),
            new Img_Tag("icon.png", "cool icon image"),
            new Unary_Tag("br")
        });
    std::cout << root->to_string() << std::endl;
    delete root;
    return 0;
}