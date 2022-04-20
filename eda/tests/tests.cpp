#define UNITTEST

#include "eda/vfs/vfs.hpp"
#include "eda/vfs/path.hpp"
#include "eda/core/std.h"
#include "eda/core/errors.hpp"
#include "eda/tests/test_utils.hpp"
#include "eda/core/eda_type_traits.h"
#include "eda/core/config_parser.h"
#include <catch2/catch_test_macros.hpp>

using namespace std;

TEST_CASE("Test path parser", "[pathparser]")
{
    eda_path::P_Parser p("/a/b/c");

    REQUIRE(p.has_next() == true);
    REQUIRE(p.next() == "a");
    REQUIRE(p.next() == "b");
    REQUIRE(p.next() == "c");
    REQUIRE(p.has_next() == false);

    p = eda_path::P_Parser("/");
    REQUIRE(p.has_next() == false);

    p = eda_path::P_Parser("/a");
    REQUIRE_THROWS_AS(p.peek(), eda::EDA_Exception);
}

TEST_CASE("Test Path Tree Node", "[path_tree_node]")
{
    // Test constructor
    eda::Path_Tree_Node n("token");
    REQUIRE(n.get_parent() == nullptr);

    eda::Path_Tree_Node parent("root");
    eda::Path_Tree_Node child_1("asd");
    eda::Path_Tree_Node child_2("zxc");

    eda::Path_Tree_Node n2("token", parent);

    // Test copy constructor
    eda::Path_Tree_Node n3 = n2;
    REQUIRE(n3.get_parent() == n2.get_parent());

    eda::Path_Tree_Node n3c("n3c");
    n3.insert_child(n3c);

    cout << n3.children.size() << "|" << n2.children.size() << endl;

    eda::Path_Tree_Node &n3c_find = n3.find("n3c");
    REQUIRE(!n3c_find.is_null_node());

    n3c_find = n2.find("n3c");
    REQUIRE(n3c_find.is_null_node());
}

TEST_CASE("Test insert path", "[insert_path]")
{
    eda::Path_Tree_Node root;
    root.insert_path("/a/b/c");
    root.insert_path("/a/b/d");
    root.insert_path("/");
    vector<string> l1 = root.list_children_token();
    REQUIRE(l1 == vector<string>{"a"});

    vector<string> l2 = root.children[0].list_children_token();
    REQUIRE(l2 == vector<string>{"b"});

    vector<string> l3 = root.children[0].children[0].list_children_token();
    REQUIRE(l3 == vector<string>{"c", "d"});
}

TEST_CASE("Test type trait", "[Type_trait]")
{
    eda_core::Y_Float f;
    eda_core::Y_Err e;
    eda_core::Y_Object o;
    REQUIRE(eda_core::instance_of<eda_core::Y_Float>(&f) == true);
    REQUIRE(eda_core::instance_of<eda_core::Y_Err>(&e));
    REQUIRE(!eda_core::instance_of<eda_core::Y_Err>(&f));
    REQUIRE(eda_core::instance_of<eda_core::Y_Object>(&e));

    unique_ptr<eda_core::Y_Object> p = make_unique<eda_core::Y_Map>(eda_core::Y_Map{});
    REQUIRE(!eda_core::instance_of<eda_core::Y_Map>(p.get()));
    REQUIRE(eda_core::p_instance_of<eda_core::Y_Map>(p.get()));
}

TEST_CASE("Test yaml parsing", "[Yaml parsing]")
{
    eda_core::Y_Object yo;
#ifdef TEST_ROOT
#define concat(F, S) F S
    cout << concat(TEST_ROOT, "/test.yaml") << endl;
    yo = eda_core::parse_yaml(concat(TEST_ROOT, "/test.yaml"));

#endif
    cout<<yo.map.size()<<endl;

}
