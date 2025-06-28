#include <algorithm>
#include <cstdint>
#include <cmath>
#include <stdexcept>

#define MAX_SAFE_INTEGER 9007199254740991.00

namespace BigDecimal {
class BigDecimal {
public:
  BigDecimal();
  BigDecimal(int num);
  BigDecimal(double num);
  BigDecimal(const BigDecimal &num);
  bool operator==(const BigDecimal &other) const;
  bool operator==(const int &other) const;

  BigDecimal operator-() const;

  BigDecimal &operator=(const BigDecimal &other);
  BigDecimal operator+(const BigDecimal &other) const;
  BigDecimal operator-(const BigDecimal &other) const;
  BigDecimal operator*(const BigDecimal &other) const;
  BigDecimal operator/(const BigDecimal &other) const;

  bool operator<(const BigDecimal &b) const;
  bool operator<=(const BigDecimal &b) const;
  bool operator>(const BigDecimal &b) const;
  bool operator>=(const BigDecimal &b) const;
  bool operator!=(const BigDecimal &b) const;

  bool isnan() const;

  void normalize();
  
  static int8_t compare(const BigDecimal &a, const BigDecimal &b);

  uint64_t layer;
  double magnitude;
  int8_t sign;
};

double log10add(double x, double y) {
  /*
   * 10^x+10^y=10^z(x>=y)
   * t=fl(x)
   * log10(10^(x-t)+10^(y-t))+t
   * */
  double t = floor(std::max(x, y));
  return t + log10(pow(10, x - t) + pow(10, y - t));
}

BigDecimal::BigDecimal() {
  layer = 0;
  magnitude = 0.0;
  sign = 0;
}

BigDecimal::BigDecimal(int num) {
  if (num > 0) {
    sign = 1;
    layer = 0;
    magnitude = num;
  } else if (num == 0) {
    layer = 0;
    sign = 0;
    magnitude = 0;
  } else {
    layer = 0;
    sign = -1;
    magnitude = -num;
  }
  normalize();
}

BigDecimal::BigDecimal(double num) {
  if (num > 0) {
    sign = 1;
    layer = 0;
    magnitude = num;
  } else if (num == 0) {
    layer = 0;
    sign = 0;
    magnitude = 0;
  } else {
    layer = 0;
    sign = -1;
    magnitude = -num;
  }
  normalize();
}

BigDecimal::BigDecimal(const BigDecimal &num) {
  layer = num.layer;
  sign = num.sign;
  magnitude = num.magnitude;
  normalize();
}

void BigDecimal::normalize() {
  if (magnitude < 0) {
    magnitude = -magnitude;
    sign = -sign;
  }
  else if (magnitude == 0)
    sign = 0;
  if (::isnan(magnitude)) {
    sign = 0;
    layer = 0;
  }
  if (magnitude > MAX_SAFE_INTEGER) {
    layer++;
    magnitude = log10(magnitude);
  }
}

bool BigDecimal::isnan() const { return ::isnan(this->magnitude); }

BigDecimal BigDecimal::operator-() const {
  BigDecimal result = *this;
  result.sign = -result.sign;
  return result;
}

bool BigDecimal::operator==(const BigDecimal &other) const { 
  return this->layer == other.layer 
    && this->magnitude == other.magnitude 
    && this->sign == other.sign;
}

bool BigDecimal::operator==(const int &other) const {
  BigDecimal decimal = *new BigDecimal(other);
  return *this == decimal;
}
bool BigDecimal::operator<(const BigDecimal &other) const {
  return BigDecimal::compare(*this, other) > 0;
}
bool BigDecimal::operator<=(const BigDecimal &other) const {
  return BigDecimal::compare(*this, other) >=0;
}
bool BigDecimal::operator>(const BigDecimal &other) const {
  return BigDecimal::compare(*this, other) <0;
}
bool BigDecimal::operator>=(const BigDecimal &other) const {
  return BigDecimal::compare(*this, other) <= 0;
}
bool BigDecimal::operator!=(const BigDecimal &other) const {
  return BigDecimal::compare(*this, other) != 0;
}
BigDecimal &BigDecimal::operator=(const BigDecimal &other) {
  if (this != &other) {
    this->layer = other.layer;
    this->magnitude = other.magnitude;
    this->sign = other.sign;
  }
  return *this;
}

BigDecimal BigDecimal::operator+(const BigDecimal &other) const {
  if (*this == 0)
    return *new BigDecimal(other);
  if (other == 0)
    return *new BigDecimal(*this);
  
  BigDecimal result(1);
  
  if (this->sign == other.sign) {
    result.magnitude = this->magnitude + other.magnitude;

    result.sign = other.sign;
  } else if (this->sign == 1 && other.sign == -1)
    result.magnitude = this->magnitude - other.magnitude;
  else if (this->sign == -1 && other.sign == 1)
    return other + *this;
  result.normalize();
  return result;
}

BigDecimal BigDecimal::operator-(const BigDecimal &other) const {
  BigDecimal result = (*this) + (-other);
  result.normalize();
  return result;
}

BigDecimal BigDecimal::operator*(const BigDecimal &other) const {
  BigDecimal result(0);
  if (*this == 0)
    return result;
  if (other == 0)
    return result;
  result.magnitude = this->magnitude * other.magnitude;
  result.sign = this->sign * other.sign;
  result.normalize();
  return result;
}

BigDecimal BigDecimal::operator/(const BigDecimal &other) const {
  BigDecimal result(0);
  if (other == 0)
    throw std::invalid_argument("Cannot divide by zero.");
  if (*this == 0)
    return result;
  result.sign = this->sign * other.sign;
  result.magnitude = this->magnitude / other.magnitude;

  result.normalize();
  return result;
}

/*
 * a<b  => >0
 * a==b => 0
 * a>b  => <0
 */
int8_t BigDecimal::compare(const BigDecimal &a, const BigDecimal &b) {
  if (a.sign != b.sign) {
    return b.sign-a.sign;
  }
  if (a.sign == 0 && b.sign == 0) return 0;
  else if (a.sign == -1 && b.sign == -1) return BigDecimal::compare(-b, -a);
  
  if (a.layer != b.layer) return a.layer > b.layer ? -1 : 1;
  if (a.magnitude != b.magnitude) return a.magnitude > b.magnitude ? -1 : 1;
  return 0;
}

} // namespace BigDecimal
  //
