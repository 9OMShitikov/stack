//
// Created by Oleg on 20.12.2018.
//

#include "my_stack.h"
#include "my_stack.cpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST (stack, Push_Back_and_Back) {
    my_stack <int> arr;
    for (int i = 0; i < 100; ++i) {
        arr.push_back (i);
        ASSERT_EQ(i, arr.back());
    }
}

TEST (stack, Pop_Back) {
    my_stack <int> arr;
    for (int i = 0; i < 100; ++i) {
        arr.push_back (i);
        ASSERT_EQ (i, arr.back());
    }
    for (int i = 0; i < 99; ++i) {
        arr.pop_back ();
        ASSERT_EQ (98 - i, arr.back());
    }
}

TEST (stack, Size) {
    my_stack <int> arr;
    ASSERT_EQ (0, arr.size());
    for (int i = 1; i <= 100; ++i) {
        arr.push_back (i);
        ASSERT_EQ (i, arr.size());
    }
    for (int i = 99; i >= 0; --i) {
        arr.pop_back ();
        ASSERT_EQ (i, arr.size());
    }
}