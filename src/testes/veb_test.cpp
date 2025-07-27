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
