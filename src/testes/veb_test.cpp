#include <gtest/gtest.h>

#include "core/veb.h"

#include <cstdio>

TEST(veb_test, dummy)
{
    ufc::eda::core::veb veb;
    veb.inclui(6);
    veb.inclui(5);
    veb.inclui(7);
    veb.inclui(8);
    veb.inclui(5);
    veb.inclui(2);
    veb.inclui(4);
    veb.inclui(4);

    uint32_t it = veb.min();
    while(it != ufc::eda::core::veb::inf)
    {
        printf("\n%u", it);
        it = veb.sucessor(it);
    }
}

TEST(veb_test, edge_cases)
{
    ufc::eda::core::veb veb;

    veb.inclui(1);
    veb.inclui(1); // caso x == _min

    veb.inclui(5);
    veb.inclui(10);
    veb.inclui(10); // caso x == _max

    veb.inclui(10);
    veb.inclui(10);

    veb.inclui(3);
    veb.inclui(7);
    
    uint32_t it = veb.min();
    while(it != ufc::eda::core::veb::inf)
    {
        printf("\n%u", it);
        it = veb.sucessor(it);
    }
}
