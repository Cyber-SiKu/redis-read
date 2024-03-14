#include <iostream>
#include "sds/sds.h"

int main() {
    sds::Sdshdr<uint8_t> s;
    std::cout << int(s.GetFlags()) << std::endl;
    return 0;
}
