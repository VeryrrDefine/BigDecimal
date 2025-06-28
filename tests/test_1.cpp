#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>
#include "bigdecimal/header.h"
#define dec BigDecimal::BigDecimal
class BigDecimalTest : public  ::testing::Test {
  protected:
    void SetUp() override {
      // 每个测试前的初始化代码
    }
    
    void TearDown() override {
      // 每个测试后的清理代码
    }
    
};

TEST(BigDecimalTest, ConstructedNoArgumentsNormaly) {
  dec decimal = *new dec();
  EXPECT_EQ(0, decimal.layer);
};

TEST(BigDecimalTest, IntegerConstructor) {
  dec decimal(9);

  EXPECT_EQ(1, decimal.sign);
  EXPECT_EQ(9.0, decimal.magnitude);
  dec decimal2(0);
  EXPECT_EQ(0, decimal2.sign);
  EXPECT_EQ(0, decimal2.magnitude);
};

TEST(BigDecimalTest, DoubleConstructor) {
  dec decimal(9.0);
  EXPECT_EQ(9.0, decimal.magnitude);
  dec decimal2(-11.0);
  EXPECT_EQ(11.0, decimal2.magnitude);
  EXPECT_EQ(-1, decimal2.sign);
};
TEST(BigDecimalTest, EqualsNumbers) {
  dec decimal(0.0);
  dec decimal2(0);
  EXPECT_TRUE(decimal==decimal2);
};
TEST(BigDecimalTest, AddTwoNumber) {
  dec decimal(9.0);
  dec decimal2(8.0);
  dec decimal3 = decimal+decimal2;
  
  EXPECT_EQ(17.0, decimal3.magnitude);
};

TEST(BigDecimalTest, AddTwoNumberWithNegatives) {
  dec decimal(9.0);
  dec decimal2(-8.0);
  dec decimal3 = decimal+decimal2;
  
  EXPECT_EQ(1.0, decimal3.magnitude);
};
TEST(BigDecimalTest, AddTwoNumberWithNegatives2) {
  dec decimal(-9.0);
  dec decimal2(-8.0);
  dec decimal3 = decimal+decimal2;
  EXPECT_EQ(-1, decimal3.sign);
  EXPECT_EQ(17.0, decimal3.magnitude);
};
TEST(BigDecimalTest, SubTwoNumber) {
  dec decimal1(3.0);
  dec decimal2(5.0);

  dec decimal3 = decimal2-decimal1;
  dec decimal4 = decimal1-decimal2;

  EXPECT_EQ(2, decimal3.magnitude);
  EXPECT_EQ(2, decimal4.magnitude);
  EXPECT_EQ(1, decimal3.sign);
  EXPECT_EQ(-1, decimal4.sign);

};
TEST(BigDecimalTest, NegateNumber) {
  dec decimal1(1145.14);
  dec decimal2(0);
  dec decimal3(-1919.810);

  dec decimal4 = -decimal1;
  dec decimal5 = -decimal2;
  dec decimal6 = -decimal3;

  EXPECT_EQ(-1, decimal4.sign);
  EXPECT_EQ(0, decimal5.sign);
  EXPECT_EQ(1, decimal6.sign);
};

TEST(BigDecimalTest, Equals) {
  EXPECT_TRUE(*new BigDecimal::BigDecimal(0) == 0);
  EXPECT_TRUE(*new BigDecimal::BigDecimal(1) == 1);
}

TEST(BigDecimalTest, MultiplyNumber) {
  dec decimal1(0);
  dec decimal2(33);
  dec decimal3(-14);
  dec decimal4(114514);

  dec decimal5 = decimal2 * decimal4;
  dec decimal6 = decimal1 * decimal2;
  dec decimal7 = decimal3 * decimal4;
  dec decimal8 = decimal3 * decimal3;
  EXPECT_EQ(3778962, decimal5.magnitude);
  EXPECT_EQ(1, decimal5.sign);
  
  EXPECT_EQ(0, decimal6.magnitude);
  EXPECT_EQ(0, decimal6.sign);
  EXPECT_EQ(1603196, decimal7.magnitude);
  EXPECT_EQ(-1, decimal7.sign);
  EXPECT_EQ(196, decimal8.magnitude);
  EXPECT_EQ(1, decimal8.sign);
};

TEST(BigDecimalTest, DivideNumber) {
  dec decimal1(0);
  dec decimal2(33);
  dec decimal3(-14);
  dec decimal4(114514);

  dec decimal5 = decimal2 / decimal4;
  dec decimal7 = decimal3 / decimal4;
  dec decimal8 = decimal3 / decimal3;
  EXPECT_EQ(33.0/114514.0, decimal5.magnitude);
  EXPECT_EQ(1, decimal5.sign);
  
  EXPECT_EQ(14.0/114514, decimal7.magnitude);
  EXPECT_EQ(-1, decimal7.sign);
  EXPECT_EQ(1, decimal8.magnitude);
  EXPECT_EQ(1, decimal8.sign);

  EXPECT_THROW(decimal3/decimal1, std::invalid_argument); 
};

TEST(BigDecimalTest, LayerConvertion) {
  dec decimal1(3000000);
  dec decimal2(4000000000.00);

  dec decimal3 = decimal1*decimal2;

  EXPECT_NEAR(6.0+9.0+log10(3.0)+log10(4.0), decimal3.magnitude, 0.00001);
  EXPECT_EQ(1, decimal3.layer);
};

TEST(BigDecimalTest, ConstructorLayerConvertion) {
  dec decimal1(1.00e100);

  EXPECT_EQ(100, decimal1.magnitude);
  EXPECT_EQ(1, decimal1.layer);
};

TEST(BigDecimalTest, FirstLayerConvertion) {
  dec decimal1(9.30e15);
  dec decimal2(2.78e16);

  dec decimal3 = decimal1+decimal2;
  EXPECT_EQ(1, decimal3.layer);
  EXPECT_NEAR(log10(9.30e15+2.78e16), decimal3.magnitude, 0.00001);
};

TEST(BigDecimalTest, Comparsion) {
  dec decimal1(344);
  dec decimal2(122);
  dec decimal3(0);
  dec decimal4(-114);
  dec decimal5(-1.00e16);
  dec decimal6(1.554e16);

  EXPECT_TRUE(decimal5<decimal4);
  EXPECT_TRUE(decimal5<decimal3);
  EXPECT_TRUE(decimal5<decimal2);
  EXPECT_TRUE(decimal4<decimal2);
  EXPECT_TRUE(decimal3<decimal1);
  EXPECT_TRUE(decimal1<decimal6);
  EXPECT_TRUE(decimal5<decimal6);
}
