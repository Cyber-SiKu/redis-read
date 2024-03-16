//
// Created by siku on 2024/3/14.
//

#ifndef REDIS_READ_SDS_H
#define REDIS_READ_SDS_H

#include <type_traits>
#include <print>

namespace Sds {
    class SdsBase;

    template<class T>
    class SdsHdr;

    using SdsHdr5 = SdsBase;
    using SdsHdr8 = SdsHdr<uint8_t>;
    using SdsHdr16 = SdsHdr<uint16_t>;
    using SdsHdr32 = SdsHdr<uint32_t>;
    using SdsHdr64 = SdsHdr<uint64_t>;

    enum SDS_TYPE {
        SDS_TYPE_5 = 0,
        SDS_TYPE_8 = 1,
        SDS_TYPE_16 = 2,
        SDS_TYPE_32 = 3,
        SDS_TYPE_64 = 4,
        SDS_TYPE_REFCOUNTED = 5,
    };

    constexpr ssize_t SDS_TYPE_5_VALUE = 1 << 5;
    constexpr ssize_t SDS_TYPE_8_VALUE = 1 << 8;
    constexpr ssize_t SDS_TYPE_16_VALUE = 1 << 16;
    constexpr ssize_t SDS_TYPE_32_VALUE = 1ll << 32;
    constexpr ssize_t SDS_TYPE_REFCOUNTED_VALUE = 1 << 16;

    constexpr unsigned SDS_TYPE_MASK = 7; // 0x111

    constexpr char* SDS_NOINIT = "SDS_NOINIT";

    class Sds {
    protected:
        char *buf_;
    public:
        explicit Sds(const char *buf = "\0");

        void SetBuf(char *buf) {
            buf_ = buf;
        }

        char *GetBuf();


    public:
        static Sds* SdsEmpty();

        /* Create a new Sds string with the content specified by the 'init' pointer
         * and 'initlen'.
         * If NULL is used for 'init' the string is initialized with zero bytes.
         * If SDS_NOINIT is used, the buffer is left uninitialized;
         *
         * The string is always null-termined (all the Sds strings are, always) so
         * even if you create an Sds string with:
         *
         * mystring = sdsnewlen("abc",3);
         *
         * You can print the string with printf() as there is an implicit \0 at the
         * end of the string. However the string is binary safe and can contain
         * \0 characters in the middle, as the length is stored in the Sds header. */
        static Sds* SdsNewLen(const void *init, ssize_t initlen);

        static SDS_TYPE SdsReqType(ssize_t string_size);

        static int SdsHdrSize(SDS_TYPE type);

        static Sds *GetSds(SDS_TYPE type, ssize_t initLen);
    };

    class __attribute__ ((__packed__)) SdsBase : public Sds {
    protected:
        char flags_;

    public:
        explicit SdsBase(char flags = 0, ssize_t initLen = 0, const char * init = nullptr);

        char GetFlags() const;
    };

    template<class T>
    class __attribute__ ((__packed__)) SdsHdr : public SdsBase {
    protected:
        T len_;
        T alloc_;

    public:
        template<typename std::enable_if<std::is_same<T, uint8_t>::value ||
                                         std::is_same<T, uint16_t>::value ||
                                         std::is_same<T, uint32_t>::value ||
                                         std::is_same<T, uint64_t>::value>::type * =
        nullptr>
        explicit SdsHdr(char flags = 0, ssize_t initLen = 0) : SdsBase(flags, initLen), len_(initLen) {}
    };

    class SdsHdrRefCount : public SdsBase {
    protected:
        uint64_t len_;
        uint16_t refCount_;
    public:
        SdsHdrRefCount(char flags, ssize_t initLen): SdsBase(flags, initLen), len_(initLen) {}
    };

}  // namespace Sds

#endif  // REDIS_READ_SDS_H
