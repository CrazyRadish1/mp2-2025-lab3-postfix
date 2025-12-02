#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack) {
    ASSERT_NO_THROW(TStack<int> s(10));
}

TEST(TStack, can_create_stack_with_default_size) {
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_push_element) {
    TStack<int> s(10);
    ASSERT_NO_THROW(s.Push(5));
}

TEST(TStack, can_pop_element) {
    TStack<int> s(10);
    s.Push(5);
    EXPECT_EQ(s.Pop(), 5);
}

TEST(TStack, can_check_top_element) {
    TStack<int> s(10);
    s.Push(5);
    EXPECT_EQ(s.Top(), 5);
    EXPECT_FALSE(s.IsEmpty());
}

TEST(TStack, throws_when_pop_from_empty) {
    TStack<int> s(10);
    ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, throws_when_top_from_empty) {
    TStack<int> s(10);
    ASSERT_ANY_THROW(s.Top());
}

TEST(TStack, can_clear_stack) {
    TStack<int> s(10);
    s.Push(5);
    s.Clear();
    EXPECT_TRUE(s.IsEmpty());
}

TEST(TStack, can_resize_automatically) {
    TStack<int> s(1);
    s.Push(1);
    ASSERT_NO_THROW(s.Push(2));
    EXPECT_EQ(s.Top(), 2);
}

TEST(TStack, can_copy_stack) {
    TStack<int> s1(10);
    s1.Push(5);
    TStack<int> s2(s1);
    EXPECT_EQ(s2.Pop(), 5);
    EXPECT_EQ(s1.Top(), 5);
}