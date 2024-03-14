//
// Created by siku on 2024/3/14.
//

#include "sds.h"

namespace sds {

    char *SdsBase::GetBuf() {
        return buf_;
    }

    char SdsBase::GetFlags() const {
        return flags_;
    }

    SdsBase::SdsBase(char flags, char *buf):flags_(flags),buf_(buf) {

    }
} // sds