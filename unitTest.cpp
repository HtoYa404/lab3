#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp>
#include <sstream>
#include "header.hpp"

bool isTesting = true;
void cin_em(string em_in){
    stringstream input;
    input.str(em_in);
    cin.clear();
    cin.rdbuf(input.rdbuf());
}

TEST_CASE("test the calculations") {
    SECTION("check for throws with invalid data"){
        REQUIRE_THROWS(f_one(-5, 0));
        REQUIRE_THROWS(f_two(-6, 0));
    }
    SECTION("check with valid numbers"){
        CHECK_NOTHROW(f_one(-6, -5) == 1863);
        CHECK_NOTHROW(f_two(0, 4) == 1.56);
    }
}

TEST_CASE("testing for various user inputs"){
    SECTION("y/n checks"){
        cin_em("y");
        CHECK_NOTHROW(ask("y"));
        cin_em("n");
        CHECK_NOTHROW(!ask("n"));
        cin_em("q");
        REQUIRE_THROWS(ask("false input"));
    }
    SECTION("testing user`s input"){
        cin_em("1");
        CHECK_NOTHROW(monkeyInput("") == 1);
        cin_em("1.1");
        CHECK_NOTHROW(monkeyInput("") == 1.1);
        cin_em("1,1");
        CHECK_NOTHROW(monkeyInput("") == 1.1);
    }
}
/*TEST_CASE("non passble test"){
    REQUIRE(1 == 0);
}*/