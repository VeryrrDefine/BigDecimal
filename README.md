# BigDecimal
A c++ library to 

## Internal
The class `BigDecimal` 实例 has 3 non-function properties:
`uint64_t layer`, `int8_t sign` and `double magnitude`

they composite to a number `sign` * 10^10^...10^`magnitude` (there are `layer` 10^'s)

This project doesn't completed yet because I don't know how to implement it
## Usage
```cpp
#include "bigdecimal/header.h"
#include <iostream>
int main() {
  BigDecimal::BigDecimal decimal1(3);
  BigDecimal::BigDecimal decimal2(4);

  std::cout << (decimal1+decimal2).magnitude << std::endl; 
}
```
