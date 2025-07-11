#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H

#include <cstdint>
namespace BigDecimal {
  class BigDecimal {
    public:
      BigDecimal();
      BigDecimal(int num); 
      BigDecimal(double num); 
      BigDecimal(const BigDecimal& num);
      bool operator==(const BigDecimal& other) const; 
      bool operator==(const int& other) const; 
      BigDecimal operator-() const;
      
      BigDecimal& operator=(const BigDecimal& other);
      BigDecimal operator+(const BigDecimal& other) const;
      BigDecimal operator-(const BigDecimal& other) const;
      BigDecimal operator*(const BigDecimal& other) const;
      BigDecimal operator/(const BigDecimal& other) const;
      bool isnan() const;
      void normalize();
      static int8_t compare(const BigDecimal &a, const BigDecimal &b);
      bool operator<(const BigDecimal &b) const;
      bool operator<=(const BigDecimal &b) const;
      bool operator>(const BigDecimal &b) const;
      bool operator>=(const BigDecimal &b) const;
      bool operator!=(const BigDecimal &b) const;
      
      BigDecimal max(const BigDecimal &b) const;
      BigDecimal min(const BigDecimal &b) const;

      uint64_t layer;
      double magnitude;
      int8_t sign;

  };
}

#endif
