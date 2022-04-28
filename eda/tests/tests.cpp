#define UNITTEST

#include "eda/vfs/vfs.hpp"
#include "eda/vfs/path.hpp"
#include "eda/core/std.h"
#include "eda/core/errors.hpp"
#include "eda/tests/test_utils.hpp"
#include "eda/core/eda_type_traits.h"
#include "eda/core/config_parser.h"
#include "eda/core/functools.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std;

/*
    操他妈死逼的还要封到什么时候
    每天他妈操逼的核酸核酸，除了核酸就只会满嘴喷屎
    王八蛋，全家死光光
*/

TEST_CASE("Test functools", "[functools]")
{
    vector<int> src{1, 2, 3, 4, 5};
    int res = eda_core::foldl(src, eda_core::Folders<int>::plus);
    REQUIRE(res == 15);

    vector<string> str_vec{"1", "2", "3", "4", "5"};
    string str_res = eda_core::foldl(str_vec, eda_core::Folders<string>::plus);
    REQUIRE(str_res == "12345");
}

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

TEST_CASE("Test Y_Map", "[Y_Map]")
{
    using namespace eda_core;
    Y_Object yo;
    Y_Map ymap(std::move(yo));
    ymap.put("a", Y_String("b"));
    ymap.put("a", Y_String("c"));
    REQUIRE(ymap.get("a").get()->token == "c");

    /**
     * ymap is copy constructed
     * therefore yo's data is unchanged
     */
    REQUIRE(yo.map.size() == 0);
    // copy constructed
    yo = ymap;
    REQUIRE(yo.map.size() == 1);
}

TEST_CASE("Test yaml parsing", "[Yaml parsing]")
{
    eda_core::Y_Object yo;
#ifdef TEST_ROOT
#define concat(F, S) F S
    cout << concat(TEST_ROOT, "/test.yaml") << endl;
    yo = eda_core::parse_yaml(concat(TEST_ROOT, "/yaml/map.yaml"));

#endif
    REQUIRE(yo.map.size() == 2);
    eda_core::Y_Object *b = yo.map["b"].get();
    REQUIRE(b != nullptr);
    REQUIRE(b->map.size() == 4);
    REQUIRE(b->map["b1"].get()->token == "1");
    REQUIRE(b->map["b3"].get()->map.size() == 2);
}

TEST_CASE("Test map list yaml parsing", "[Yaml parsing 2]")
{
    eda_core::Y_Object yo;
    yo = eda_core::parse_yaml(concat(TEST_ROOT, "/yaml/maplist.yaml"));
    eda_core::Y_Map a{*yo.map["a"]};
    eda_core::Y_Seq b{*a.get("b").get()};

    eda_core::Y_Map b0{*b[0].get()};
    eda_core::Y_Map b1{*b[1].get()};
    eda_core::Y_Map b2{*b[2].get()};

    REQUIRE(b0.get("c").get()->token == "1");
    REQUIRE(b1.get("d").get()->token == "2");
    REQUIRE(b2.get("e").get()->map["f"].get()->map["g"].get()->token == "3");
}

TEST_CASE("Test list yaml parsing", "[Yaml parsing 3]")
{
    eda_core::Y_Object yo;
    yo = eda_core::parse_yaml(concat(TEST_ROOT, "/yaml/list.yaml"));
    eda_core::Y_Seq s{yo};
    REQUIRE(s.seq.size() == 4);
    REQUIRE(s.seq[3].get()->map["a"].get()->token == "4");
}