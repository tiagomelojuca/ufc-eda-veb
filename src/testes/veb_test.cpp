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

    printf("%s\n", veb.trace().c_str());
}

TEST(veb_test, edge_cases)
{
    ufc::eda::core::veb veb;

    veb.inclui(1);
    veb.inclui(1);

    veb.inclui(5);
    veb.inclui(10);
    veb.inclui(10);

    veb.inclui(10);
    veb.inclui(10);

    veb.inclui(3);
    veb.inclui(7);

    printf("%s\n", veb.trace().c_str());
}

TEST(veb_test, complex_stress_test)
{
    ufc::eda::core::veb veb;

    veb.inclui(15);
    EXPECT_EQ(veb.min(), 15);
    EXPECT_EQ(veb.max(), 15);

    veb.inclui(7);
    EXPECT_EQ(veb.min(), 7);
    EXPECT_EQ(veb.max(), 15);

    veb.inclui(22);
    EXPECT_EQ(veb.min(), 7);
    EXPECT_EQ(veb.max(), 22);

    veb.inclui(3);
    EXPECT_EQ(veb.min(), 3);
    EXPECT_EQ(veb.max(), 22);

    veb.inclui(15);

    veb.inclui(31);
    EXPECT_EQ(veb.max(), 31);

    veb.inclui(12);

    veb.inclui(1);
    EXPECT_EQ(veb.min(), 1);

    veb.inclui(31);
    veb.inclui(7); 

    veb.inclui(255);
    EXPECT_EQ(veb.max(), 255);

    veb.inclui(256);
    EXPECT_EQ(veb.max(), 256);

    veb.inclui(257);
    EXPECT_EQ(veb.max(), 257);

    veb.inclui(511);
    EXPECT_EQ(veb.max(), 511);

    veb.inclui(1023);
    EXPECT_EQ(veb.max(), 1023);

    veb.inclui(1024);
    EXPECT_EQ(veb.max(), 1024);

    veb.inclui(1025);
    EXPECT_EQ(veb.max(), 1025);

    veb.inclui(8);
    veb.inclui(9);
    veb.inclui(10);
    veb.inclui(11);
    veb.inclui(13);
    veb.inclui(14);
    veb.inclui(16);

    veb.inclui(2048);
    EXPECT_EQ(veb.max(), 2048);

    veb.inclui(4096);
    EXPECT_EQ(veb.max(), 4096);

    veb.inclui(8192);
    EXPECT_EQ(veb.max(), 8192);

    veb.inclui(16384);
    EXPECT_EQ(veb.max(), 16384);

    veb.inclui(65535);
    EXPECT_EQ(veb.max(), 65535);

    veb.inclui(65536);
    EXPECT_EQ(veb.max(), 65536);

    veb.inclui(65537);
    EXPECT_EQ(veb.max(), 65537);

    veb.inclui(4294967294);
    EXPECT_EQ(veb.max(), 4294967294);

    EXPECT_EQ(veb.sucessor(1), 3);
    EXPECT_EQ(veb.sucessor(3), 7);
    EXPECT_EQ(veb.sucessor(7), 8);
    EXPECT_EQ(veb.sucessor(8), 9);
    EXPECT_EQ(veb.sucessor(9), 10);
    EXPECT_EQ(veb.sucessor(10), 11);
    EXPECT_EQ(veb.sucessor(11), 12);
    EXPECT_EQ(veb.sucessor(12), 13);
    EXPECT_EQ(veb.sucessor(13), 14);
    EXPECT_EQ(veb.sucessor(14), 15);
    EXPECT_EQ(veb.sucessor(15), 16);
    EXPECT_EQ(veb.sucessor(16), 22);
    EXPECT_EQ(veb.sucessor(22), 31);
    EXPECT_EQ(veb.sucessor(31), 255);
    EXPECT_EQ(veb.sucessor(255), 256);
    EXPECT_EQ(veb.sucessor(256), 257);
    EXPECT_EQ(veb.sucessor(257), 511);
    EXPECT_EQ(veb.sucessor(511), 1023);
    EXPECT_EQ(veb.sucessor(1023), 1024);
    EXPECT_EQ(veb.sucessor(1024), 1025);
    EXPECT_EQ(veb.sucessor(1025), 2048);
    EXPECT_EQ(veb.sucessor(2048), 4096);
    EXPECT_EQ(veb.sucessor(4096), 8192);
    EXPECT_EQ(veb.sucessor(8192), 16384);
    EXPECT_EQ(veb.sucessor(16384), 65535);
    EXPECT_EQ(veb.sucessor(65535), 65536);
    EXPECT_EQ(veb.sucessor(65536), 65537);
    EXPECT_EQ(veb.sucessor(65537), 4294967294);
    EXPECT_EQ(veb.sucessor(4294967294), ufc::eda::core::veb::inf);

    EXPECT_EQ(veb.sucessor(2), 3);
    EXPECT_EQ(veb.sucessor(4), 7);
    EXPECT_EQ(veb.sucessor(6), 7);
    EXPECT_EQ(veb.sucessor(17), 22);
    EXPECT_EQ(veb.sucessor(30), 31);
    EXPECT_EQ(veb.sucessor(32), 255);
    EXPECT_EQ(veb.sucessor(258), 511);
    EXPECT_EQ(veb.sucessor(512), 1023);
    EXPECT_EQ(veb.sucessor(1026), 2048);
    EXPECT_EQ(veb.sucessor(4097), 8192);

    // 1 -> 3 -> 7 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12 -> 13 -> 14 -> 15 ->
    // 15 -> 16 -> 22 -> 31 -> 31 -> 255 -> 256 -> 257 -> 511 -> 1,023 ->
    // 1,024 -> 1,025 -> 2,048 -> 4,096 -> 8192 -> 16384
    printf("%s\n", veb.trace().c_str());
}

