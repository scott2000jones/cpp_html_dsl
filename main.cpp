#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Tag {
    public:
        Tag(std::string tag_name) {
            this->tag_name = tag_name;
        }
        Tag(std::string tag_name, std::vector<Tag> children) {
            this->tag_name = tag_name;
            this->children = children;
        }
        virtual std::string to_string() {
            std::string str = "<" + tag_name + ">\n";
            for (auto c : children) str += (&c)->to_string();
            str += "</" + tag_name + ">\n";
            return str;
        }
    protected:
        std::string tag_name;
        std::vector<Tag> children;
};

class A_Tag : public Tag {
    public:
        A_Tag(std::string href_url) : Tag("a") {
            this->href_url = href_url;
        }
        A_Tag(std::string href_url, std::vector<Tag> children) : Tag("a", children) {
            this->href_url = href_url;
        }
        std::string to_string() override {
            std::string str = "<" + tag_name + " href=\"" + href_url + "\">\n";
            for (auto c : children) str += (&c)->to_string();
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



    A_Tag tag3 = A_Tag("www.google.com");
    Tag tag2 = Tag("custom_tag", std::vector<Tag>{
            A_Tag("www.twitch.tv"),
            A_Tag("www.youtube.com")
        });

    std::cout << tag2.to_string() << std::endl;
    return 0;
}