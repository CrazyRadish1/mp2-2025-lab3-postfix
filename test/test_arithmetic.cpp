#include <gtest.h>
#include "arithmetic.h"

void ResetArrays(double* v, bool* s) {
    for (int i = 0; i < 256; i++) s[i] = false;
}

TEST(Arithmetic, can_calculate_add) {
    Arithmetic expr("2+2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 4.0);
}

TEST(Arithmetic, can_calculate_sub) {
    Arithmetic expr("5-3");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 2.0);
}

TEST(Arithmetic, can_calculate_mul) {
    Arithmetic expr("4*3");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 12.0);
}

TEST(Arithmetic, can_calculate_div) {
    Arithmetic expr("10/2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 5.0);
}

TEST(Arithmetic, can_calculate_pow) {
    Arithmetic expr("2^3");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 8.0);
}

TEST(Arithmetic, can_calculate_priority_simple) {
    Arithmetic expr("2+2*2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 6.0);
}

TEST(Arithmetic, can_calculate_brackets) {
    Arithmetic expr("(2+2)*2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 8.0);
}

TEST(Arithmetic, can_calculate_nested_brackets) {
    Arithmetic expr("((2+3)*2)/2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 5.0);
}

TEST(Arithmetic, can_handle_unary_minus) {
    Arithmetic expr("-5 + 2");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), -3.0);
}

TEST(Arithmetic, can_handle_unary_minus_inside) {
    Arithmetic expr("5 + (-2)");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 3.0);
}

TEST(Arithmetic, can_handle_float_numbers) {
    Arithmetic expr("1.5 + 2.5");
    double v[256]; bool s[256]; ResetArrays(v, s);
    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 4.0);
}

TEST(Arithmetic, can_handle_single_variable) {
    Arithmetic expr("x + 5");
    double v[256]; bool s[256]; ResetArrays(v, s);

    v['x'] = 10.0; s['x'] = true;

    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 15.0);
}

TEST(Arithmetic, can_handle_multiple_variables) {
    Arithmetic expr("a + b");
    double v[256]; bool s[256]; ResetArrays(v, s);

    v['a'] = 2.0; s['a'] = true;
    v['b'] = 3.5; s['b'] = true;

    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 5.5);
}

TEST(Arithmetic, can_reuse_variable) {
    Arithmetic expr("x * x");
    double v[256]; bool s[256]; ResetArrays(v, s);

    v['x'] = 3.0; s['x'] = true;

    EXPECT_DOUBLE_EQ(expr.Calculate(v, s), 9.0);
}

TEST(Arithmetic, throws_on_division_by_zero) {
    Arithmetic expr("5/0");
    double v[256]; bool s[256]; ResetArrays(v, s);
    ASSERT_ANY_THROW(expr.Calculate(v, s));
}

TEST(Arithmetic, throws_on_unmatched_brackets_closing) {
    Arithmetic expr("(5+5))");
    double v[256]; bool s[256]; ResetArrays(v, s);
    ASSERT_ANY_THROW(expr.Calculate(v, s));
}

TEST(Arithmetic, throws_on_unmatched_brackets_opening) {
    Arithmetic expr("((5+5)");
    double v[256]; bool s[256]; ResetArrays(v, s);
    ASSERT_ANY_THROW(expr.Calculate(v, s));
}

TEST(Arithmetic, throws_on_empty_string) {
    Arithmetic expr("");
    double v[256]; bool s[256]; ResetArrays(v, s);
    ASSERT_ANY_THROW(expr.Calculate(v, s));
}

TEST(Arithmetic, throws_on_incorrect_symbols) {
    Arithmetic expr("5 $ 5");
    double v[256]; bool s[256]; ResetArrays(v, s);
    ASSERT_ANY_THROW(expr.Calculate(v, s));
}