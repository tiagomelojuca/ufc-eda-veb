#ifndef VEB_H_
#define VEB_H_

#include <cstdint>
#include <string>

#define _MAXWORD 0xFFFFFFFF

namespace ufc
{
namespace eda
{
namespace core
{

class veb
{
public:
    using word_t  = uint32_t;
    constexpr static const size_t word_size = 32;
    constexpr static const word_t inf = _MAXWORD;

    using hword_t = uint16_t;
    constexpr static const size_t hword_size = 16;

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

private:
    hword_t cluster(word_t palavra)
    {
        return palavra >> hword_size;
    }
    hword_t indice(word_t palavra)
    {
        return palavra & ((1 << hword_size) - 1);
    }
    word_t palavra(hword_t cluster, hword_t indice)
    {
        return (cluster << hword_size) | indice;
    }
};

}
}
}

#endif // VEB_H_
