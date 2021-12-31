#ifndef CPP_HTML_DSL_H
#define CPP_HTML_DSL_H

#include <string>
#include <vector>

class Tag {
    public:
        Tag(std::string tag_name);
        Tag(std::string tag_name, std::vector<Tag*> child_tags);
        ~Tag();
        virtual std::string to_string();
    protected:
        std::string tag_name;
        std::vector<Tag*> child_tags;
};

class A_Tag : public Tag {
    public:
        A_Tag(std::string href_url);
        A_Tag(std::string href_url, std::vector<Tag*> child_tags);
        std::string to_string() override;
    private:
        std::string href_url;
};

class Img_Tag : public Tag {
    public:
        Img_Tag(std::string img_src);
        Img_Tag(std::string img_src, std::string alt_text);
        Img_Tag(std::string img_src, std::vector<Tag*> child_tags);
        Img_Tag(std::string img_src, std::string alt_text, std::vector<Tag*> child_tags);
        std::string to_string() override;
    private:
        std::string img_src;
        std::string alt_text;
};

class Link_Tag : public Tag {
    public:
        Link_Tag(std::string rel, std::string href);
        std::string to_string() override;
    private:
        std::string rel;
        std::string href;
};

class Unary_Tag : public Tag {
    public:
        Unary_Tag(std::string tag_name);
        std::string to_string() override;
};

#endif