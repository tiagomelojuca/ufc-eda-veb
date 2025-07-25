#ifndef VEB_H_
#define VEB_H_

#include <cstdint>
#include <string>

#define _MAXINT 2147483647

namespace ufc
{
namespace eda
{
namespace core
{

class veb
{
public:
    using word_t = int32_t;
    constexpr static const word_t inf = _MAXINT;

    veb() = default;
    ~veb() = default;

    void inclui(word_t chave)
    {
    }

    void remove(word_t chave)
    {
    }

    word_t sucessor(word_t chave) const
    {
        return -1;
    }

    word_t predecessor(word_t chave) const
    {
        return -1;
    }

    std::string to_string() const
    {
        return "veb_as_string";
    }
};

}
}
}

#endif // VEB_H_
