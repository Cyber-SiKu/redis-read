//
// Created by siku on 2024/3/14.
//

#include <map>
#include "sds.h"

namespace Sds {

    char SdsBase::GetFlags() const { return flags_; }

    SdsBase::SdsBase(char flags, ssize_t initLen, const char *init) : flags_(flags) {
        char *buf = nullptr;
        if (init == SDS_NOINIT) {
            // buf = bullptr
        } else {
            buf = new char[initLen + 1];
        }
        if (init == nullptr) {
            std::memset(buf, 0 , initLen+1);
        }

        if (initLen != 0 && init != nullptr) {
            std::memcpy(buf, init, initLen);
        }
    }

    Sds *Sds::SdsEmpty() {
        return SdsNewLen("", 0);
    }

    Sds *Sds::SdsNewLen(const void *init, ssize_t initlen) {
        void *sh;
        Sds *s;
        if (initlen < 0) {
            initlen = -initlen;
        }
        SDS_TYPE type = SdsReqType(initlen);
        // SDS_TYPE_5 不太适用于追加的类型，而空字符串被创建通常都用于追加
        if (type == SDS_TYPE_5 && initlen == 0) {
            type = SDS_TYPE_8;
        }
        int hdrLen = SdsHdrSize(type);
        s = GetSds(type, initlen);
        if (s == nullptr) {
            return nullptr;
        }
        return s;
    }

    SDS_TYPE Sds::SdsReqType(ssize_t string_size) {
        if (string_size < 0) {
            string_size = -string_size;
            if (string_size < SDS_TYPE_REFCOUNTED_VALUE) {
                return SDS_TYPE_REFCOUNTED;
            }
        }

        if (string_size < SDS_TYPE_5_VALUE) {
            return SDS_TYPE_5;
        }
        if (string_size < SDS_TYPE_8_VALUE) {
            return SDS_TYPE_8;
        }
        if (string_size < SDS_TYPE_16_VALUE) {
            return SDS_TYPE_16;
        }
#if (LONG_MAX == LLONG_MAX)
        if (string_size < SDS_TYPE_32_VALUE) {
            return SDS_TYPE_32;
        }
        return SDS_TYPE_64;
#else
        return SDS_TYPE_32;
#endif
    }

    int Sds::SdsHdrSize(SDS_TYPE type) {
        static const std::map<SDS_TYPE, int> sizeMap = {
                {SDS_TYPE_5,          sizeof(SdsHdr5)},
                {SDS_TYPE_8,          sizeof(SdsHdr8)},
                {SDS_TYPE_16,         sizeof(SdsHdr16)},
                {SDS_TYPE_32,         sizeof(SdsHdr32)},
                {SDS_TYPE_64,         sizeof(SdsHdr64)},
                {SDS_TYPE_REFCOUNTED, sizeof(SdsHdrRefCount)}
        };

        auto it = sizeMap.find(static_cast<const SDS_TYPE>(type & SDS_TYPE_MASK));
        if (it != sizeMap.end()) {
            return it->second;
        }

        return 0;
    }

    Sds::Sds(const char *buf) : buf_(const_cast<char *>(buf)) {}

    char *Sds::GetBuf() {
        return buf_;
    }

    Sds *Sds::GetSds(SDS_TYPE type, ssize_t initLen) {
        static const std::map<SDS_TYPE, std::function<Sds *(char, ssize_t)>> constructorMap = {
                {SDS_TYPE_5,          [](char flags, ssize_t len) { return new SdsHdr5(flags, len); }},
                {SDS_TYPE_8,          [](char flags, ssize_t len) { return new SdsHdr8(flags, len); }},
                {SDS_TYPE_16,         [](char flags, ssize_t len) { return new SdsHdr16(flags, len); }},
                {SDS_TYPE_32,         [](char flags, ssize_t len) { return new SdsHdr32(flags, len); }},
                {SDS_TYPE_64,         [](char flags, ssize_t len) { return new SdsHdr64(flags, len); }},
                {SDS_TYPE_REFCOUNTED, [](char flags, ssize_t len) { return new SdsHdrRefCount(flags, len); }}
        };

        auto it = constructorMap.find(type);
        if (it != constructorMap.end()) {
            return it->second(0, initLen);
        }

        return nullptr;
    }
}  // namespace Sds