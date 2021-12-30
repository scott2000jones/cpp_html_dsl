#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Tag {
    public:
        Tag(std::string tag_name) {
            this->tag_name = tag_name;
            std::cout << tag_name << " (no child tags) " << std::endl;
        }
        Tag(std::string tag_name, std::vector<Tag*> child_tags) {
            this->tag_name = tag_name;
            std::cout << tag_name;

            this->child_tags = child_tags;
            for (auto c : this->child_tags) std::cout << c << " ";
            std::cout << " end " << std::endl;

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



class Image_Tag : public Tag {
    private:
        std::string image_url;
};





int main() {
    std::cout << "Hello from the C++ world" << std::endl;

    Tag *root = new Tag("root_tag", std::vector<Tag*>{
            new Tag("new_tag"),
            new A_Tag("www.twitch.tv")
        });
    std::cout << root->to_string() << std::endl;
    return 0;
}