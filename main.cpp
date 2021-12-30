#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Tag {
    public:
        Tag(std::string tag_name) {
            this->tag_name = tag_name;
            // std::cout << tag_name << " (no child tags) " << std::endl;
        }
        Tag(std::string tag_name, std::vector<Tag*> child_tags) {
            this->tag_name = tag_name;
            // std::cout << tag_name;
            this->child_tags = child_tags;
            // for (auto c : this->child_tags) std::cout << c << " ";
            // std::cout << " end " << std::endl;
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

int main() {
    std::cout << "Hello from the C++ HTML DSL world " << std::endl << std::endl;

    Tag *root = new Tag("root_tag", std::vector<Tag*>{
            new Tag("new_tag"),
            new A_Tag("www.twitch.tv", std::vector<Tag*>{
                new Img_Tag("twitch.png")
            }),
            new Img_Tag("icon.png", "cool icon image")
        });
    std::cout << root->to_string() << std::endl;
    return 0;
}