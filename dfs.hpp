// -*- c++ -*-

/*
 * Takes a C++ tree object and creates a {{ Tikz tree }} in
 * a latex file. The synthax is lisp-like:
 *
 *    John --|-- Kirk --|-- Alan
 *           |          |-- Alice
 *           |-- Bob
 *
 * is encoded as
 *
 *   \begin{tikzpicture}
 *   %\tikzstyle [OPTIONS]
 *     \node {John}
 *       child {node {Kirk}
 *         child {node {Alan}}
 *         child {node {Alice}}}
 *       child {node {Bob}};
 *  \end{tikzpicture}
 */

#ifndef __DFS_H_
#define __DFS_H_

#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace tikz {

const extern std::array<const std::string, 6> _header;
const extern std::array<const std::string, 2> _footer;

/**
     * Traverses a tree depth first and feeds the string representation
     * of the nodes to a buffer.
    */
class TreeIn {

public:
    using opt_str = std::optional<std::string>;
    using buf_t = std::deque<opt_str>;

    template <class Node>
    TreeIn(const Node& root, buf_t* _buf)
        : buffer(_buf)
    {
        read<Node>(&root);
        void ready_buffer();
    }

    template <class Node>
    void read(const Node* node)
    {
        append(make_optional(std::string(*node)));

        for (const auto* child : node->get_children()) {
            read(child);
        }

        append(std::nullopt);
    }

private:
    buf_t* buffer;

    void append(const opt_str& str) const
    {
        buffer->push_back(str);
        //// For debugging
        //std::cerr << "Added ";
        //std::cerr << "\"" << str << "\"" << std::endl;
    }

    // Since the root didn't have an associated open bracket.
    void ready_buffer() const
    {
        buffer->pop_back();
    }
};

class TreeOut {
public:
    using opt_str = std::optional<std::string>;
    using buf_t = std::deque<opt_str>;

    TreeOut()
        : ofs()
        , buffer()
    {
    }

    void write(const std::string& filename)
    {
        ofs.open(filename);

        write_header();
        write_body();
        write_footer();

        ofs.close();
    }

    buf_t* get_buffer()
    {
        return &buffer;
    }

private:
    std::ofstream ofs;
    buf_t buffer;

    void write_header()
    {
        for (const auto& str : _header) {
            ofs << str;
        }
    }

    void write_footer()
    {
        for (const auto& str : _footer) {
            ofs << str;
        }
        ofs << std::endl;
    }

    void write_root(std::string node, int indent = 2)
    {
        ofs << whitespace(indent) << "\\node {" << node << "}";
    }

    void write_node(std::string node, int depth, int indent = 2)
    {
        ofs << '\n'
            << whitespace(indent * (depth + 1)) << "child {node {" << node << "}";
    }

    void write_endofbranch(int depth, int indent = 2)
    {
        ofs << '}';
    }

    void write_endofbody(int indent = 2)
    {
        ofs << ";" << std::endl;
    }

    void write_body()
    {
        int depth = 0;
        opt_str node = buffer.front();
        buffer.pop_front();

        // special formatting for *root*
        if (node.has_value()) {
            write_root(*node);
        }
        while (!buffer.empty()) {
            node = buffer.front();
            buffer.pop_front();

            if (node.has_value()) {
                ++depth;
                write_node(*node, depth);
            }
            // Last node was a leaf (but not the last one)
            else if (!buffer.empty()) {
                write_endofbranch(depth);
                --depth;
            }
        }

        write_endofbody();
    }

    std::string whitespace(int indent) const
    {
        return std::string(indent, ' ');
    }
};

}
#endif // __DFS_H_
