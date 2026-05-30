#include "../include/Monom.h"

#include <gtest.h>
#include <string>



// ========== Конструкторы ==========

TEST(Monom, can_create_monom_from_degrees) {
    ASSERT_NO_THROW(Monom m(3.5, 2, 1, 0));
}

TEST(Monom, can_create_monom_from_key) {
    ASSERT_NO_THROW(Monom m(3.5, 210));
}

TEST(Monom, constructor_from_degrees_calculates_key_correctly) {
    Monom m(2.5, 3, 4, 5);
    EXPECT_EQ(m.getKey(), 345);  // 3*100 + 4*10 + 5 = 345
    EXPECT_EQ(m.getDegX(), 3);
    EXPECT_EQ(m.getDegY(), 4);
    EXPECT_EQ(m.getDegZ(), 5);
}

TEST(Monom, constructor_from_key_sets_correct_degrees) {
    Monom m(1.5, 321);
    EXPECT_EQ(m.getKey(), 321);
    EXPECT_EQ(m.getDegX(), 3);
    EXPECT_EQ(m.getDegY(), 2);
    EXPECT_EQ(m.getDegZ(), 1);
}

TEST(Monom, zero_degrees_are_handled_correctly) {
    Monom m(5.0, 0, 0, 0);
    EXPECT_EQ(m.getKey(), 0);
    EXPECT_EQ(m.getDegX(), 0);
    EXPECT_EQ(m.getDegY(), 0);
    EXPECT_EQ(m.getDegZ(), 0);
}

// ========== Геттеры ==========

TEST(Monom, getCoeff_returns_coefficient) {
    Monom m(4.2, 1, 2, 3);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 4.2);
}

TEST(Monom, getKey_returns_key) {
    Monom m(1.0, 1, 2, 3);
    EXPECT_EQ(m.getKey(), 123);
}

TEST(Monom, getDegX_returns_degree_of_x) {
    Monom m(1.0, 5, 2, 1);
    EXPECT_EQ(m.getDegX(), 5);
}

TEST(Monom, getDegY_returns_degree_of_y) {
    Monom m(1.0, 2, 6, 1);
    EXPECT_EQ(m.getDegY(), 6);
}

TEST(Monom, getDegZ_returns_degree_of_z) {
    Monom m(1.0, 2, 1, 7);
    EXPECT_EQ(m.getDegZ(), 7);
}

// ========== multiplyByConst ==========

TEST(Monom, multiplyByConst_multiplies_coefficient) {
    Monom m(3.0, 1, 1, 1);
    m.multiplyByConst(2.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 6.0);
}

TEST(Monom, multiplyByConst_with_zero_sets_coefficient_to_zero) {
    Monom m(5.0, 1, 1, 1);
    m.multiplyByConst(0.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 0.0);
}

TEST(Monom, multiplyByConst_with_negative_changes_sign) {
    Monom m(3.0, 1, 1, 1);
    m.multiplyByConst(-2.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), -6.0);
}

// ========== addToCoeff ==========

TEST(Monom, addToCoeff_adds_to_coefficient) {
    Monom m(3.0, 1, 1, 1);
    m.addToCoeff(2.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 5.0);
}

TEST(Monom, addToCoeff_with_negative_reduces_coefficient) {
    Monom m(3.0, 1, 1, 1);
    m.addToCoeff(-1.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.0);
}

TEST(Monom, addToCoeff_can_make_coefficient_zero) {
    Monom m(3.0, 1, 1, 1);
    m.addToCoeff(-3.0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 0.0);
}

// ========== operator== ==========

TEST(Monom, operator_equal_returns_true_for_same_key) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m1 == m2);
}

TEST(Monom, operator_equal_returns_false_for_different_keys) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(2.0, 1, 2, 4);
    EXPECT_FALSE(m1 == m2);
}

// ========== operator< ==========

TEST(Monom, operator_less_returns_true_when_key_smaller) {
    Monom m1(1.0, 1, 0, 0);  // key = 100
    Monom m2(1.0, 2, 0, 0);  // key = 200
    EXPECT_TRUE(m1 < m2);
}

TEST(Monom, operator_less_returns_false_when_key_greater) {
    Monom m1(1.0, 2, 0, 0);  // key = 200
    Monom m2(1.0, 1, 0, 0);  // key = 100
    EXPECT_FALSE(m1 < m2);
}

TEST(Monom, operator_less_returns_false_when_keys_equal) {
    Monom m1(1.0, 1, 2, 3);
    Monom m2(1.0, 1, 2, 3);
    EXPECT_FALSE(m1 < m2);
}

// ========== parse (статический метод) ==========

TEST(Monom, parse_parses_simple_number) {
    Monom m = Monom::parse("5");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 5.0);
    EXPECT_EQ(m.getKey(), 0);
}

TEST(Monom, parse_parses_negative_number) {
    Monom m = Monom::parse("-3");
    EXPECT_DOUBLE_EQ(m.getCoeff(), -3.0);
    EXPECT_EQ(m.getKey(), 0);
}

TEST(Monom, parse_parses_decimal_number) {
    Monom m = Monom::parse("2.5");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.5);
    EXPECT_EQ(m.getKey(), 0);
}

TEST(Monom, parse_parses_x_without_degree) {
    Monom m = Monom::parse("x");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    EXPECT_EQ(m.getKey(), 100);  // x^1 y^0 z^0
}

TEST(Monom, parse_parses_x_with_degree) {
    Monom m = Monom::parse("x^3");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    EXPECT_EQ(m.getKey(), 300);
}

TEST(Monom, parse_parses_coefficient_with_variable) {
    Monom m = Monom::parse("2x^3");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.0);
    EXPECT_EQ(m.getKey(), 300);
}

TEST(Monom, parse_parses_negative_coefficient_with_variable) {
    Monom m = Monom::parse("-2x^3");
    EXPECT_DOUBLE_EQ(m.getCoeff(), -2.0);
    EXPECT_EQ(m.getKey(), 300);
}

TEST(Monom, parse_parses_multiple_variables) {
    Monom m = Monom::parse("3x^2y^1z^4");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 3.0);
    EXPECT_EQ(m.getKey(), 214);  // 2*100 + 1*10 + 4 = 214
}

TEST(Monom, parse_parses_variables_without_degree) {
    Monom m = Monom::parse("xy");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    EXPECT_EQ(m.getKey(), 110);  // x^1 y^1 z^0
}

TEST(Monom, parse_parses_xyz_combination) {
    Monom m = Monom::parse("2xyz");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.0);
    EXPECT_EQ(m.getKey(), 111);
}

TEST(Monom, parse_parses_variables_in_different_order) {
    Monom m = Monom::parse("y^2z^3");
    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    EXPECT_EQ(m.getDegX(), 0);
    EXPECT_EQ(m.getDegY(), 2);
    EXPECT_EQ(m.getDegZ(), 3);
}

TEST(Monom, parse_throws_on_empty_token) {
    ASSERT_ANY_THROW(Monom::parse(""));
}

TEST(Monom, parse_throws_on_invalid_character) {
    ASSERT_ANY_THROW(Monom::parse("2a^3"));
}

TEST(Monom, parse_throws_on_invalid_format) {
    ASSERT_ANY_THROW(Monom::parse("^2"));
}

TEST(Monom, parse_throws_on_missing_digit_after_caret) {
    ASSERT_ANY_THROW(Monom::parse("x^"));
}