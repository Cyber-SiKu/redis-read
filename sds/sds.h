//
// Created by siku on 2024/3/14.
//

#ifndef REDIS_READ_SDS_H
#define REDIS_READ_SDS_H

#include <type_traits>

namespace sds {
    class SdsBase {
    protected:
        char flags_;
        char *buf_;
    public:
        explicit SdsBase(char flags = 0, char*buf_ = nullptr);
        char *GetBuf();
        char GetFlags() const;
    };

    template<class T>
    class Sdshdr: public SdsBase{
    protected:
        T len_;
        T alloc_;
    public:
        template<typename std::enable_if<std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value ||
                                         std::is_same<T, uint32_t>::value ||
                                         std::is_same<T, uint64_t>::value>::type * = nullptr>
        Sdshdr() {}

    };
using Sds = char*;
} // sds


#endif //REDIS_READ_SDS_H
