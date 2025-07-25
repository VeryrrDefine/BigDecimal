#include <cmath>
#include <gtest/gtest.h>
#include "bigdecimal/header.h"
#define dec BigDecimal::BigDecimal
class BigDecimalTest2 : public  ::testing::Test {
  protected:
    void SetUp() override {
      // 每个测试前的初始化代码
    }
    
    void TearDown() override {
      // 每个测试后的清理代码
    }
    
};

TEST(BigDecimalTest2, MultiplyNumberCrossLayer) {
  dec decimal1(1e16);
  dec decimal2(5);
  dec decimal3(1e14);
  dec decimal4(62903342);
  
  dec decimal5 = decimal1*decimal2;
  dec decimal6 = decimal3*decimal4;
  EXPECT_EQ(16+log10(5), decimal5.magnitude);
  EXPECT_EQ(1, decimal5.layer);
  
  EXPECT_EQ(14+log10(62903342), decimal6.magnitude);
  EXPECT_EQ(1, decimal5.layer);
};
