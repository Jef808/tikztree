// -*- c++ -*-

#include "dfs.hpp"
#include "testutil.hpp"
#include <iostream>

using namespace tikz;
using namespace test;

int main()
{
    auto test = TestClass();

    bool all_pass = true;
    bool res = true;

    // Run test_dfs_store
    res = test.test_dfs_store();
    if (res == false) {
        std::cerr << "Test dfs_store failed!" << std::endl;
    }

    // Run test_write
    res = test.test_write();

    if (res == false) {
        std::cerr << "Test write failed!" << std::endl;
    }

    // Run test_bigger_tree
    res = test.test_bigger_tree();
    if (res == false) {
        std::cerr << "Test bigger tree failed!" << std::endl;
    }

    // Give total results.
    if (res == true) {
        std::cout << "All tests passed!" << std::endl;
    }

    return 0;
}
