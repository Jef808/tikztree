#include "tikzfmt.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct Data {
    int id;
    string label;

    Data()
        : id(0)
        , label("")
    {}
    Data(int _id, string _label)
        : id(_id)
        , label(_label)
    {}
    string to_s() const {
        return to_string(id);
    }
};

class Node {
public:
    using node_sptr = shared_ptr<Node>;

    Node()
        : data(Data())
        , children()
    {}

    Node(Data _data)
        : data(_data)
        , children()
    {}
    const Node& add_child(Data d) const
    {
        return *children.emplace_back(make_shared<Node>(d));
    }
    std::vector<node_sptr>& get_children() const
    {
        return children;
    }
    const Data& get_data() const
    {
        return data;
    }
    std::string to_s() const
    {
        return data.to_s();
    }

private:
    Data data;
    mutable vector<node_sptr> children;
};

int main()
{
    auto* root = new Node(Data(0, "ROOT"));
    auto labels = vector<string>{{ "0", "1", "2", "3", "4", "5", "6", "7", "8" }};
    auto node_data = vector<Data>(9, Data());
    auto nodes = vector<Node>(9, Node());
    auto node_s = vector<string>(9, string());

    std::transform(cbegin(labels), cend(labels), begin(node_data), [i=-1](const auto& s) mutable {
        return Data(++i, s);
    });

    std::transform(cbegin(node_data), cend(node_data), begin(nodes), [](auto& node_d){
        return Node(node_d);
    });

    std::transform(cbegin(nodes), cend(nodes), begin(node_s), [](const auto& node) {
        return node.to_s();
    });

    for (int i=0; i<4; ++i) {
        root->add_child(node_data[i]);
    }

    auto node1 = root->get_children()[1].get();
    node1->add_child(node_data[4]);
    node1->add_child(node_data[5]);
    auto node6 = &node1->add_child(node_data[6]);

    node6->add_child(node_data[7]);
    node6->add_child(node_data[8]);


    auto tree = tikztree<Node>::get_tikz_tree(root);

    tikztree<Node>::write_tikz_file("tikz_test.tex", std::move(tree));
}
