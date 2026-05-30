#include "../include/Polynomial.h"
#include "../include/List.h"

#include <gtest.h>
#include <string>

// ========== Конструкторы ==========

TEST(Polynomial, can_create_empty_polynomial) {
    ASSERT_NO_THROW(Polynomial p);
}

// ========== addMonom ==========

TEST(Polynomial, addMonom_adds_single_monom) {
    Polynomial p;
    Monom m(3.5, 2, 1, 0);
    p.addMonom(m);
    
    Polynomial expected;
    expected.addMonom(Monom(3.5, 2, 1, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, addMonom_combines_like_terms) {
    Polynomial p;
    Monom m1(3.0, 2, 1, 0);
    Monom m2(2.0, 2, 1, 0);
    p.addMonom(m1);
    p.addMonom(m2);
    
    Polynomial expected;
    expected.addMonom(Monom(5.0, 2, 1, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, addMonom_ignores_zero_coefficient) {
    Polynomial p;
    Monom m(0.0, 2, 1, 0);
    p.addMonom(m);
    
    Polynomial expected;
    
    EXPECT_EQ(p, expected);
}

// ========== parse ==========

TEST(Polynomial, parse_parses_simple_polynomial) {
    Polynomial p = Polynomial::parse("3x^2y + 2z - 5");
    
    Polynomial expected;
    expected.addMonom(Monom(3.0, 2, 1, 0));
    expected.addMonom(Monom(2.0, 0, 0, 1));
    expected.addMonom(Monom(-5.0, 0, 0, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, parse_parses_polynomial_without_spaces) {
    Polynomial p = Polynomial::parse("3x^2y+2z-5");
    
    Polynomial expected;
    expected.addMonom(Monom(3.0, 2, 1, 0));
    expected.addMonom(Monom(2.0, 0, 0, 1));
    expected.addMonom(Monom(-5.0, 0, 0, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, parse_parses_polynomial_with_only_constant) {
    Polynomial p = Polynomial::parse("5");
    
    Polynomial expected;
    expected.addMonom(Monom(5.0, 0, 0, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, parse_parses_polynomial_with_negative_coefficients) {
    Polynomial p = Polynomial::parse("-2x + 3");
    
    Polynomial expected;
    expected.addMonom(Monom(-2.0, 1, 0, 0));
    expected.addMonom(Monom(3.0, 0, 0, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, parse_parses_polynomial_with_leading_minus) {
    Polynomial p = Polynomial::parse("-x^2 + 2x - 1");
    
    Polynomial expected;
    expected.addMonom(Monom(-1.0, 2, 0, 0));
    expected.addMonom(Monom(2.0, 1, 0, 0));
    expected.addMonom(Monom(-1.0, 0, 0, 0));
    
    EXPECT_EQ(p, expected);
}

TEST(Polynomial, parse_throws_on_invalid_input) {
    ASSERT_ANY_THROW(Polynomial::parse("invalid"));
}

TEST(Polynomial, parse_throws_on_missing_monom_after_minus) {
    ASSERT_ANY_THROW(Polynomial::parse("3x + "));
}

// ========== add ==========

TEST(Polynomial, add_two_empty_polynomials_returns_empty) {
    Polynomial a, b;
    Polynomial c = Polynomial::add(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, add_polynomial_with_empty_returns_original) {
    Polynomial a;
    a.addMonom(Monom(3.0, 2, 1, 0));
    
    Polynomial b;
    Polynomial c = Polynomial::add(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(3.0, 2, 1, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, add_with_empty_polynomial) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    Polynomial b;
    
    Polynomial c = Polynomial::add(a, b);
    Polynomial expected;
    expected.addMonom(Monom(2.0, 1, 0, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, add_combines_like_terms) {
    Polynomial a, b;
    a.addMonom(Monom(3.0, 2, 1, 0));
    b.addMonom(Monom(2.0, 2, 1, 0));
    
    Polynomial c = Polynomial::add(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(5.0, 2, 1, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, add_cancels_opposite_terms) {
    Polynomial a, b;
    a.addMonom(Monom(3.0, 2, 1, 0));
    b.addMonom(Monom(-3.0, 2, 1, 0));
    
    Polynomial c = Polynomial::add(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

// ========== subtract ==========

TEST(Polynomial, subtract_two_empty_polynomials_returns_empty) {
    Polynomial a, b;
    Polynomial c = Polynomial::subtract(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, subtract_empty_from_empty) {
    Polynomial a, b;
    Polynomial c = Polynomial::subtract(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, subtract_polynomial_from_itself_returns_empty) {
    Polynomial a;
    a.addMonom(Monom(3.0, 2, 1, 0));
    a.addMonom(Monom(2.0, 1, 0, 0));
    
    Polynomial c = Polynomial::subtract(a, a);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, subtract_with_empty_polynomial) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    Polynomial b;
    
    Polynomial c = Polynomial::subtract(a, b);
    Polynomial expected;
    expected.addMonom(Monom(2.0, 1, 0, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, subtract_works_correctly) {
    Polynomial a, b;
    a.addMonom(Monom(5.0, 2, 1, 0));
    b.addMonom(Monom(3.0, 2, 1, 0));
    
    Polynomial c = Polynomial::subtract(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(2.0, 2, 1, 0));
    
    EXPECT_EQ(c, expected);
}

// ========== multiplyByConst ==========

TEST(Polynomial, multiplyByConst_zero_returns_empty) {
    Polynomial a;
    a.addMonom(Monom(3.0, 2, 1, 0));
    
    Polynomial c = Polynomial::multiplyByConst(a, 0.0);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiplyByConst_on_empty_polynomial) {
    Polynomial a;
    Polynomial c = Polynomial::multiplyByConst(a, 5.0);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiplyByConst_one_returns_original) {
    Polynomial a;
    a.addMonom(Monom(3.0, 2, 1, 0));
    
    Polynomial c = Polynomial::multiplyByConst(a, 1.0);
    
    Polynomial expected;
    expected.addMonom(Monom(3.0, 2, 1, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiplyByConst_negative_flips_signs) {
    Polynomial a;
    a.addMonom(Monom(3.0, 2, 1, 0));
    a.addMonom(Monom(2.0, 1, 0, 0));
    
    Polynomial c = Polynomial::multiplyByConst(a, -1.0);
    
    Polynomial expected;
    expected.addMonom(Monom(-3.0, 2, 1, 0));
    expected.addMonom(Monom(-2.0, 1, 0, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiplyByConst_with_fraction) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    Polynomial c = Polynomial::multiplyByConst(a, 0.5);
    
    Polynomial expected;
    expected.addMonom(Monom(1.0, 1, 0, 0));
    
    EXPECT_EQ(c, expected);
}

// ========== multiply ==========

TEST(Polynomial, multiply_empty_by_anything_returns_empty) {
    Polynomial a, b;
    b.addMonom(Monom(3.0, 2, 1, 0));
    
    Polynomial c = Polynomial::multiply(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiply_by_empty_polynomial) {
    Polynomial a, b;
    a.addMonom(Monom(2.0, 1, 0, 0));
    
    Polynomial c = Polynomial::multiply(a, b);
    Polynomial expected;
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiply_monom_by_monom) {
    Polynomial a, b;
    a.addMonom(Monom(2.0, 2, 1, 0));
    b.addMonom(Monom(3.0, 1, 0, 1));
    
    Polynomial c = Polynomial::multiply(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(6.0, 3, 1, 1));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiply_throws_when_degree_exceeds_9) {
    Polynomial a, b;
    a.addMonom(Monom(1.0, 9, 0, 0));
    b.addMonom(Monom(1.0, 1, 0, 0));
    
    ASSERT_ANY_THROW(Polynomial::multiply(a, b));
}

TEST(Polynomial, multiply_handles_like_terms) {
    Polynomial a, b;
    a.addMonom(Monom(2.0, 1, 1, 0));
    b.addMonom(Monom(3.0, 1, 1, 0));
    
    Polynomial c = Polynomial::multiply(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(6.0, 2, 2, 0));
    
    EXPECT_EQ(c, expected);
}

TEST(Polynomial, multiply_two_binoms) {
    Polynomial a, b;
    a.addMonom(Monom(1.0, 1, 0, 0));
    a.addMonom(Monom(1.0, 0, 0, 0));
    b.addMonom(Monom(1.0, 1, 0, 0));
    b.addMonom(Monom(-1.0, 0, 0, 0));
    
    Polynomial c = Polynomial::multiply(a, b);
    
    Polynomial expected;
    expected.addMonom(Monom(1.0, 2, 0, 0));
    expected.addMonom(Monom(-1.0, 0, 0, 0));
    
    EXPECT_EQ(c, expected);
}

// ========== checkDegreeLimit ==========

TEST(Polynomial, checkDegreeLimit_returns_true_for_valid_degrees) {
    Polynomial p;
    p.addMonom(Monom(1.0, 5, 3, 2));
    EXPECT_TRUE(p.checkDegreeLimit());
}

TEST(Polynomial, checkDegreeLimit_returns_true_for_empty_polynomial) {
    Polynomial p;
    EXPECT_TRUE(p.checkDegreeLimit());
}

// ========== print ==========

TEST(Polynomial, print_empty_polynomial_prints_zero) {
    Polynomial p;
    ASSERT_NO_THROW(p.print());
}

TEST(Polynomial, print_polynomial_with_one_monom) {
    Polynomial p;
    p.addMonom(Monom(3.5, 2, 1, 0));
    ASSERT_NO_THROW(p.print());
}

TEST(Polynomial, print_polynomial_with_negative_coefficient) {
    Polynomial p;
    p.addMonom(Monom(-2.0, 1, 0, 0));
    ASSERT_NO_THROW(p.print());
}

TEST(Polynomial, print_polynomial_with_constant_term) {
    Polynomial p;
    p.addMonom(Monom(5.0, 0, 0, 0));
    ASSERT_NO_THROW(p.print());
}

// ========== Копирование и присваивание ==========

TEST(Polynomial, copy_constructor) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    a.addMonom(Monom(3.0, 0, 0, 1));
    
    Polynomial b(a);
    
    EXPECT_EQ(b, a);
    
    a.addMonom(Monom(5.0, 0, 0, 0));
    EXPECT_NE(b, a);
}

TEST(Polynomial, assignment_operator) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    a.addMonom(Monom(3.0, 0, 0, 1));
    
    Polynomial b;
    b = a;
    
    EXPECT_EQ(b, a);
    
    a.addMonom(Monom(5.0, 0, 0, 0));
    EXPECT_NE(b, a);
}

TEST(Polynomial, self_assignment) {
    Polynomial a;
    a.addMonom(Monom(2.0, 1, 0, 0));
    
    a = a;
    
    Polynomial expected;
    expected.addMonom(Monom(2.0, 1, 0, 0));
    
    EXPECT_EQ(a, expected);
}

// ========== Комплексные тесты ==========

TEST(Polynomial, complex_operations_sequence) {
    Polynomial a, b;
    
    a.addMonom(Monom(2.0, 2, 1, 0));
    a.addMonom(Monom(3.0, 0, 0, 1));
    
    b.addMonom(Monom(1.0, 2, 1, 0));
    b.addMonom(Monom(-1.0, 0, 0, 1));
    
    Polynomial expectedSum;
    expectedSum.addMonom(Monom(3.0, 2, 1, 0));
    expectedSum.addMonom(Monom(2.0, 0, 0, 1));
    
    Polynomial expectedDiff;
    expectedDiff.addMonom(Monom(1.0, 2, 1, 0));
    expectedDiff.addMonom(Monom(4.0, 0, 0, 1));
    
    Polynomial expectedMulConst;
    expectedMulConst.addMonom(Monom(4.0, 2, 1, 0));
    expectedMulConst.addMonom(Monom(6.0, 0, 0, 1));
    
    Polynomial sum = Polynomial::add(a, b);
    Polynomial diff = Polynomial::subtract(a, b);
    Polynomial mulConst = Polynomial::multiplyByConst(a, 2.0);
    
    EXPECT_EQ(sum, expectedSum);
    EXPECT_EQ(diff, expectedDiff);
    EXPECT_EQ(mulConst, expectedMulConst);
}

TEST(Polynomial, parse_and_operations_integration) {
    Polynomial a = Polynomial::parse("2x^2y + 3z");
    Polynomial b = Polynomial::parse("x^2y - z");
    
    Polynomial expectedSum;
    expectedSum.addMonom(Monom(3.0, 2, 1, 0));
    expectedSum.addMonom(Monom(2.0, 0, 0, 1));
    
    Polynomial expectedDiff;
    expectedDiff.addMonom(Monom(1.0, 2, 1, 0));
    expectedDiff.addMonom(Monom(4.0, 0, 0, 1));
    
    Polynomial sum = Polynomial::add(a, b);
    Polynomial diff = Polynomial::subtract(a, b);
    
    EXPECT_EQ(sum, expectedSum);
    EXPECT_EQ(diff, expectedDiff);
}