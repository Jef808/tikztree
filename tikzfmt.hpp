#include <algorithm>
#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <sstream>

#ifndef __TIKZFMT_H_
#define __TIKZFMT_H_

template <class Node_T>
class tikztree {
public:
    using s_ptr = std::unique_ptr<std::string>;

    static inline const std::vector<std::string> tikzpre {
        "\\documentclass{minimal}",
        "\\usepackage{tikz}",
        "\\usetikzlibrary{trees}",
        "\\begin{document}",
        "\\begin{tikzpicture}",
        "\\tikzstyle{every node}=[circle,fill=red!30]"
    };

    static inline const std::vector<std::string> tikzpost {
        "\\end{tikzpicture}",
        "\\end{document}"
    };

static s_ptr get_tikz_tree(Node_T* node, int depth = 0)
{
    auto children = node->get_children();

    std::string res = std::string("node {" + node->to_s() + "}");

    if (children.empty()) {
        return std::make_unique<std::string>(res);
    }

    for (const auto& child : children) {
        res += "\n      " + std::string(depth * 2, ' ') + "child { " + *std::move(get_tikz_tree(child.get(), depth + 1)) + " }";
    }
    return std::make_unique<std::string>(res);
}

static void write_tikz_file(const std::string& filename, s_ptr stree)
{
    std::ofstream ofs;

    freopen("tikz_test.tex", "w", stdout);

    for (auto& s : tikzpre) {
        std::cout << s << std::endl;
    }

    auto tree = std::move(stree);

    std::cout << std::endl << std::endl;
    std::cout << "    " << "\\" << *tree << ';' << std::endl;
    std::cout << std::endl << std::endl;

    for (auto& s : tikzpost) {
        std::cout << s << std::endl;
    }
}

};
// Node->children() etc... into...
//
// \begin{tikzpicture}
//    \node {root}
//      child {node {left}}
//      child {node {right}
//       child {node {child}}
//       child {node {child}}
//       };
// \end{tikzpicture}
//
// Notice how easy it is to specify the parent-child relationships! We can simply open-close brackets!
//
//
// Can also add text to nodes with synthax like
//
// \tikz \draw (1,0) node (text) -- (0,0) -- (1,0) -- cycle;
// instead of the plain
// \tikz \draw (1,0) -- (0,0) -- (1,0)
//
// Note:
//
//     we can make coordinates 'relative' in tikz as follows:
//
//     \begin{tikzpicture}
//          \draw (0, 0)      -- ++(1,0) -- ++(0,1) -- ++(-1, 0) -- cycle;
//          \draw (2, 0)      -- ++(1,0) -- ++(0,1) -- ++(-1, 0) -- cycle;//
//     \end{tikzpicture}
//
//     which draws two squares, one based at the origin and the other at (2,0).


#endif // __TIKZFMT_H_
