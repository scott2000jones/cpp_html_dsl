# cpp_html_dsl
A simple DSL for HTML in C++

To use this in another project, copy the files `html_dsl.h` and `html_dsl.cpp` into the project. Include the header file in other files with `#include "html_dsl.h"`, and include `html_dsl.cpp` when compiling.

Example:
```
Tag *root = new Tag("html", std::vector<Tag*>{
    new A_Tag("www.github.com", std::vector<Tag*>{
        new Tag("p", std::vector<Tag*>{
            new Text("lorem ipsum etc")
        })
    }),
    new Img_Tag("icon.png", "a really cool icon"),
    new Unary_Tag("br")
});
std::cout << root->to_string() << std::endl;
```