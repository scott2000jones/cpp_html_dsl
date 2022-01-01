#include <iostream>
#include <string>
#include <vector>

#include "html_dsl.hpp"

/* Implementations of Tag class methods */
Tag::Tag(std::string tag_name) {
    this->tag_name = tag_name;
}
Tag::Tag(std::string tag_name, std::string on_click) {
    this->tag_name = tag_name;
    this->on_click = on_click;
}
Tag::Tag(std::string tag_name, std::vector<Tag*> child_tags) {
    this->tag_name = tag_name;
    this->child_tags = child_tags;
}
Tag::Tag(std::string tag_name, std::string on_click, std::vector<Tag*> child_tags) {
    this->tag_name = tag_name;
    this->on_click = on_click;
    this->child_tags = child_tags;
}
Tag::~Tag() {
    for (Tag *c : child_tags) delete c;
}
std::string Tag::to_string() {
    std::string str = "<" + tag_name + " onclick=\"" + on_click + "\">\n";
    for (Tag* c : child_tags) str += c->to_string();
    str += "</" + tag_name + ">\n";
    return str;
}

/* Implementations of Text class methods */
Text::Text(std::string contents) : Tag(contents) {};
std::string Text::to_string() {
    return tag_name;
}

/* Implementations of A_Tag class methods */
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

/* Implementations of Img_Tag class methods */
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

/* Implementations of Link_Tag class methods */
Link_Tag::Link_Tag(std::string rel, std::string href) : Tag("link") {
    this->rel = rel;
    this->rel = href;
}
std::string Link_Tag::to_string() {
    return "<link rel=\"" + rel + "\" href=\"" + href + "\">\n";
}

/* Implementations of Unary_Tag class methods */
Unary_Tag::Unary_Tag(std::string tag_name) : Tag(tag_name) {}
std::string Unary_Tag::to_string() {
    return "<" + tag_name + " />\n";
}