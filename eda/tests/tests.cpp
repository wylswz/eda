#include "eda/vfs/vfs.hpp"
#include "eda/vfs/path.hpp"
#include "eda/core/std.h"
#include "eda/core/errors.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std;



TEST_CASE("Test path parser", "[pathparser]") {
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