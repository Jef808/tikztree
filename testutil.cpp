// -*- c++ -*-

#include <iostream>

#include "dfs.hpp"
#include "testutil.hpp"

namespace tikz {
namespace test {

    bool TestClass::test_dfs_store()
    {
        std::array<TreeIn::opt_str, 10> res_expected_arr { { std::make_optional("John"),
            std::make_optional("Kirk"),
            std::make_optional("Alan"),
            std::nullopt,
            std::make_optional("Alice"),
            std::nullopt,
            std::nullopt,
            std::make_optional("Bob"),
            std::nullopt,
            std::nullopt } };
        auto res_expected = TreeOut::buf_t();
        for (const auto& s : res_expected_arr) {
            res_expected.push_back(s);
        }

        // John --|-- Kirk --|-- Alan
        //        |          |-- Alice
        //        |-- Bob

        auto root = init();

        auto tikz_out = TreeOut();
        auto* res = tikz_out.get_buffer();
        auto tikz_in = TreeIn(*root, res);

        std::cerr << "Expected buffer : ";
        for (const auto& s : res_expected_arr) {
            if (s.has_value()) {
                std::cerr << "'" << *s << "\", ";
            } else {
                std::cerr << "\"\", ";
            }
            std::cerr << std::endl;
        }

        std::cerr << "Result buffer : ";
        for (const auto& s : *res) {
            if (s.has_value()) {
                std::cerr << '"' << *s << "\", ";
            } else {
                std::cerr << "\"\", ";
            }
            std::cerr << std::endl;
        }

        bool success = *res == res_expected;

        return success;
    }

    bool TestClass::test_write()
    {
        auto* root = init();

        auto _out = TreeOut();
        auto _in = TreeIn(*root, _out.get_buffer());

        _out.write("tikztree.tex");

        return true;
    }

    bool TestClass::test_bigger_tree()
    {
        auto* root = init();

        auto depth1 = root->get_children()[1];
        auto depth2 = depth1->add_child("Johannes");
        auto depth3 = depth2->add_child("Livia");
        depth3->add_child("Sophia");
        depth3->add_child("Johnathan");
        depth3->add_child("Charles");
        depth3->add_child("Nathan");

        auto _out = TreeOut();
        auto _in = TreeIn(*root, _out.get_buffer());

        _out.write("tikztree.tex");

        return true;
    }

} // namespace test

} //namespace tikz
