#define CATCH_CONFIG_MAIN 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "header.hpp"
bool isTesting = true;
TEST_CASE("calculation`s benchmark"){
    BENCHMARK("f_one x: -6, n:-5"){
        return f_one(-6,-5);
    };
    BENCHMARK("f_one x: -10, n:10"){
        return f_one(-10, 10);
    };
    BENCHMARK("f_two x: -5, n: 4"){
        return f_two(-5,4);
    };
    BENCHMARK("f_two x: 10, n: 10"){
        return f_two(10,10);
    };
}