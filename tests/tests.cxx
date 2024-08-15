#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>


#include "objectmanager.h"


TEST_CASE("Generate numbers in sequence")
{
    ObjectManager om;
    SECTION("first"){
        auto i = GENERATE(1, 3, 5, 10, 20, 100, 1200);
        om.createRandomSeq(i);
        REQUIRE(om.getSeqFromQueue().size() == i);
    }

}

TEST_CASE("Sorting seq")
{
    ObjectManager om;
    Sequence test_seq = {Color::GREEN, Color::BLUE, Color::RED};
    Sequence ref;

    auto rule_gen = GENERATE(Rule({Color::GREEN, Color::BLUE, Color::RED}),
                      Rule({Color::RED, Color::GREEN, Color::BLUE}),
                      Rule({Color::BLUE, Color::RED, Color::GREEN})
                      );

    SECTION("RuleSorting first")
    {
        for(auto item : rule_gen)
            ref.push_back(item);
        auto result_f = om.sortSeqByRule(test_seq, rule_gen);
        REQUIRE(ref == result_f);
    }
    SECTION("RuleSorting second")
    {
        for(int iter = 0; iter < 10; iter++)
        {
            for(auto item : rule_gen)
            {
                ref.push_back(item);
            }
        }
        auto result_f = om.sortSeqByRule(ref, rule_gen);
        auto curren_rule_position = 0;
        for(auto im : result_f) {
            if(im.getColor() == rule_gen.at(curren_rule_position))
                continue;
            else if(im == rule_gen.at(curren_rule_position + 1))
                curren_rule_position++;
            else {
                REQUIRE(false);
            }
        }
        REQUIRE(true);
    }
}

