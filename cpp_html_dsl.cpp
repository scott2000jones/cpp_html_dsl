#include <iostream>
#include <string>
#include <vector>

#include "cpp_html_dsl.h"

Tag::Tag(std::string tag_name) {
    this->tag_name = tag_name;
}
Tag::Tag(std::string tag_name, std::vector<Tag*> child_tags) {
    this->tag_name = tag_name;
    this->child_tags = child_tags;
}
Tag::~Tag() {
    for (Tag *c : child_tags) delete c;
}
std::string Tag::to_string() {
    std::string str = "<" + tag_name + ">\n";
    for (Tag* c : child_tags) str += c->to_string();
    str += "</" + tag_name + ">\n";
    return str;
}

A_Tag::A_Tag(std::string href_url) : Tag("a") {
    this->href_url = href_url;
}
A_Tag::A_Tag(std::string href_url, std::vector<Tag*> child_tags) : Tag("a", child_tags) {
    this->href_url = href_url;
}
std::string A_Tag::to_string() {
    std::string str = "<" + tag_name + " href=\"" + href_url + "\">\n";
    for (auto c : child_tags) str += c->to_string();
    str += "</" + tag_name + ">\n";
    return str;
}

Img_Tag::Img_Tag(std::string img_src) : Tag("img") {
    this->img_src = img_src;
}
Img_Tag::Img_Tag(std::string img_src, std::string alt_text) : Tag("img") {
    this->img_src = img_src;
    this->alt_text = alt_text;
}
Img_Tag::Img_Tag(std::string img_src, std::vector<Tag*> child_tags) : Tag("img", child_tags) {
    this->img_src = img_src;
}
Img_Tag::Img_Tag(std::string img_src, std::string alt_text, std::vector<Tag*> child_tags) : Tag("img", child_tags) {
    this->img_src = img_src;
    this->alt_text = alt_text;
}
std::string Img_Tag::to_string() {
    std::string str = "<" + tag_name + " src=\"" + img_src + "\" alt=\"" + alt_text + "\">\n";
    for (auto c : child_tags) str += c->to_string();
    str += "</" + tag_name + ">\n";
    return str;
}

Link_Tag::Link_Tag(std::string rel, std::string href) : Tag("link") {
    this->rel = rel;
    this->rel = href;
}
std::string Link_Tag::to_string() {
    return "<link rel=\"" + rel + "\" href=\"" + href + "\">\n";
}

Unary_Tag::Unary_Tag(std::string tag_name) : Tag(tag_name) {}
std::string Unary_Tag::to_string() {
    return "<" + tag_name + " />\n";
}

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