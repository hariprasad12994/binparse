#include "binparse.hpp"
#include <array>
#include <iostream>
#include <iomanip>


auto main(void) -> int {
  using u32 = unsigned int;
  using Message = Fields<
    FieldEntry<"header", u32>,
    FieldEntry<"payload", std::array<char, 10>>
  >;

  Message test_message;
  get<"header">(test_message) = 0xDEADBEEF;
  std::cout << std::hex << get<"header">(test_message) << '\n';

  return 0;
}
