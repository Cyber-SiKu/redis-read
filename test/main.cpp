#include <iostream>

#include "fmt/format.h"
#include "sds.h"
#include "sds/sds.h"

int main() {
    Sds::SdsHdr<uint8_t> s;
    std::cout << int(s.GetFlags()) << std::endl
              << fmt::format("size of Sds: {}. size of char*: {}", sizeof(Sds::Sds), sizeof(char *));
    return 0;
}
