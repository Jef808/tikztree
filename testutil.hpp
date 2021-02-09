// -*- c++ -*

#ifndef __TESTUTIL_H_
#define __TESTUTIL_H_

#include <string>
#include <vector>
#include "dfs.hpp"

namespace tikz {

    namespace test {

class NodeTest
{
public:
    NodeTest(const std::string& _val)
        : value(_val)
        , children()
    {}

    ~NodeTest()
    {
        for (auto child : children)
        {
            if (child->children.empty())
            {
                delete child;
            }
            else
            {
                child->~NodeTest();
            }
        }
        children.clear();
    }

    NodeTest* add_child(std::string child_string)
    {
        children.emplace_back(new NodeTest(child_string));
        return children.back();
    }
    std::vector<NodeTest*> get_children() const
    {
        return children;
    }
    operator std::string() const
    {
        return value;
    }
private:

     std::string value;
     std::vector<NodeTest*> children;
};

class TestUtil {

    // John --|-- Kirk --|-- Alan
    //        |          |-- Alice
    //        |-- Bob
public:
    NodeTest* _root;

    TestUtil()
        : _root(nullptr)
    {
        reset();
    }

    ~TestUtil()
    {
        delete _root;
        _root = nullptr;
    }

    NodeTest* reset()
    {
        _root = new NodeTest("John");

        _root->add_child("Kirk");
        _root->add_child("Bob");

        _root->get_children()[0]->add_child("Alan");
        _root->get_children()[0]->add_child("Alice");

        return _root;
    }
};

class TestClass {

public:
    TestClass()
        : test()
    {
    }

    bool test_dfs_store();
    bool test_write();
    bool test_bigger_tree();

private:
    TestUtil test;

    NodeTest* init()
    {
        return test.reset();
    }
};

}
}

#endif // __TESTUTIL_H_
