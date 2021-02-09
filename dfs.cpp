// -*- c++ -*-

#include "dfs.hpp"

namespace tikz {

const std::array<const std::string, 6> _header {
    "\\documentclass{minimal}",
    "\\usepackage{tikz}\n",
    "\\usetikzlibrary{trees}\n",
    "\\begin{document}\n",
    "\\begin{tikzpicture}\n",
    "\\tikzstyle{every node}=[circle,fill=red!30]\n\n"
};

const std::array<const std::string, 2> _footer {
    "\\end{tikzpicture}\n",
    "\\end{document}\n"
};

}
