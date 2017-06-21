#pragma once
// MEMORY SAFE DELETE // #### DO NOT DELETE #### //
#define TK_SAFE_ARRAY_DELETE(p_)\
{                               \
    if(p_ != nullptr)           \
    {                           \
        delete[] p_;            \
        p_ = nullptr;           \
    }                           \
}
#define TK_SAFE_DELETE(p_)		\
{                               \
    if(p_ != nullptr)           \
    {                           \
        delete p_;				\
        p_ = nullptr;           \
    }                           \
}