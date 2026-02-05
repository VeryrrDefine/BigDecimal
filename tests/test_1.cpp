#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>
#include "bigdecimal/header.h"

using Decimal2 = BigDecimal::BigDecimal;

class Decimal2Test : public ::testing::Test {
protected:
  void SetUp() override {
    // 每个测试前的初始化代码
  }

  void TearDown() override {
    // 每个测试后的清理代码
  }
};

TEST_F(Decimal2Test, DefaultConstructor) {
  Decimal2 decimal;
  EXPECT_EQ(0, decimal.layer);
}

TEST_F(Decimal2Test, IntegerConstructor) {
  Decimal2 decimal(9);
  EXPECT_EQ(1, decimal.sign);
  EXPECT_EQ(9.0, decimal.magnitude);

  Decimal2 zero(0);
  EXPECT_EQ(0, zero.sign);
  EXPECT_EQ(0, zero.magnitude);
}

TEST_F(Decimal2Test, DoubleConstructor) {
  Decimal2 decimal(9.0);
  EXPECT_EQ(9.0, decimal.magnitude);

  Decimal2 negative(-11.0);
  EXPECT_EQ(11.0, negative.magnitude);
  EXPECT_EQ(-1, negative.sign);
}

TEST_F(Decimal2Test, EqualityOperator) {
  EXPECT_TRUE(Decimal2(0.0) == Decimal2(0));
  EXPECT_TRUE(Decimal2(1) == 1);
  EXPECT_FALSE(Decimal2(1) == Decimal2(2));
}

TEST_F(Decimal2Test, Addition) {
  Decimal2 decimal1(9.0);
  Decimal2 decimal2(8.0);
  Decimal2 result = decimal1 + decimal2;
  EXPECT_EQ(17.0, result.magnitude);
}

TEST_F(Decimal2Test, AdditionWithNegatives) {
  EXPECT_EQ(Decimal2(1.0), Decimal2(9.0) + Decimal2(-8.0));
  EXPECT_EQ(Decimal2(-17.0), Decimal2(-9.0) + Decimal2(-8.0));
}

TEST_F(Decimal2Test, Subtraction) {
  Decimal2 decimal1(3.0);
  Decimal2 decimal2(5.0);

  EXPECT_EQ(Decimal2(2.0), decimal2 - decimal1);
  EXPECT_EQ(Decimal2(-2.0), decimal1 - decimal2);
}

TEST_F(Decimal2Test, Negation) {
  EXPECT_EQ(Decimal2(-1145.14), -Decimal2(1145.14));
  EXPECT_EQ(Decimal2(0), -Decimal2(0));
  EXPECT_EQ(Decimal2(1919.810), -Decimal2(-1919.810));
}

TEST_F(Decimal2Test, Multiplication) {
  Decimal2 decimal2(33);
  Decimal2 decimal3(-14);
  Decimal2 decimal4(114514);

  EXPECT_EQ(Decimal2(3778962), decimal2 * decimal4);
  EXPECT_EQ(Decimal2(0), Decimal2(0) * decimal2);
  EXPECT_EQ(Decimal2(-1603196), decimal3 * decimal4);
  EXPECT_EQ(Decimal2(196), decimal3 * decimal3);
}

TEST_F(Decimal2Test, Division) {
  Decimal2 decimal2(33);
  Decimal2 decimal3(-14);
  Decimal2 decimal4(114514);

  EXPECT_DOUBLE_EQ(33.0 / 114514.0, (decimal2 / decimal4).magnitude);
  EXPECT_DOUBLE_EQ(14.0 / 114514.0, (decimal3 / decimal4).magnitude);
  EXPECT_EQ(Decimal2(1), decimal3 / decimal3);

  EXPECT_THROW(decimal3 / Decimal2(0), std::invalid_argument);
}

TEST_F(Decimal2Test, LayerConversion) {
  Decimal2 decimal1(3000000);
  Decimal2 decimal2(4000000000.00);
  Decimal2 result = decimal1 * decimal2;

  EXPECT_NEAR(6.0 + 9.0 + log10(3.0) + log10(4.0), result.magnitude, 1e-5);
  EXPECT_EQ(1, result.layer);
}

TEST_F(Decimal2Test, LargeNumberConstructor) {
  Decimal2 decimal(1.00e100);
  EXPECT_EQ(100, decimal.magnitude);
  EXPECT_EQ(1, decimal.layer);
}

TEST_F(Decimal2Test, ComparisonOperators) {
  EXPECT_TRUE(Decimal2(-1.00e16) < Decimal2(-114));
  EXPECT_TRUE(Decimal2(-1.00e16) < Decimal2(0));
  EXPECT_TRUE(Decimal2(-114) < Decimal2(122));
  EXPECT_TRUE(Decimal2(0) < Decimal2(344));
  EXPECT_TRUE(Decimal2(344) < Decimal2(1.554e16));

  // 测试所有比较运算符
  Decimal2 a(10), b(20), c(10);
  EXPECT_TRUE(a < b);
  EXPECT_TRUE(a <= b);
  EXPECT_TRUE(a <= c);
  EXPECT_TRUE(a == c);
  EXPECT_TRUE(b > a);
  EXPECT_TRUE(b >= a);
  EXPECT_TRUE(b != a);
}

TEST_F(Decimal2Test, EdgeCases) {
  // 测试边界条件
  EXPECT_NO_THROW(Decimal2(std::numeric_limits<double>::max()));
  EXPECT_NO_THROW(Decimal2(std::numeric_limits<double>::min()));
  EXPECT_NO_THROW(Decimal2(std::numeric_limits<double>::epsilon()));
}