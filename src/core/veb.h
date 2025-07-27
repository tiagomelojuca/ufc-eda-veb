#ifndef VEB_H_
#define VEB_H_

#include <unordered_map>

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
    using word_t = uint32_t;
    constexpr static const size_t word_size = 32;
    constexpr static const word_t inf = _MAXWORD;

    veb() : veb(word_size)
    {
    }

    veb(size_t tamanho_palavra)
    {
        if (tamanho_palavra >= 1)
        {
            _tamanho_palavra      = tamanho_palavra;
            _tamanho_meia_palavra = tamanho_palavra >> 1;

            _resumo = new veb(_tamanho_meia_palavra);
        }
        else
        {
            _tamanho_palavra      = 0;
            _tamanho_meia_palavra = 0;

            _resumo = nullptr;
        }

        _min = inf;
        _max = inf;
    }

    ~veb()
    {
        for (auto&& it : _clusters)
        {
            delete it.second;
        }

        delete _resumo;
    }

    word_t min() const
    {
        return _min;
    }

    word_t max() const
    {
        return _max;
    }

    bool valido() const
    {
        return _resumo != nullptr;
    }

    void inclui(word_t x)
    {
        if (_min == inf)
        {
            _min = _max = x;
        }
        else if (x != _min)
        {
            if (x < _min)
            {
                troca(x, _min);
            }

            if (x > _max)
            {
                _max = x;
            }

            const word_t c = cluster(x);
            const word_t i = indice(x);
            veb* cluster = veb_no_cluster(c);

            if (cluster->valido())
            {
                if (cluster->min() == inf)
                {
                    _resumo->inclui(c);
                }

                cluster->inclui(i);
            }
        }
    }

    void remove(word_t x)
    {
    }

    word_t sucessor(word_t x)
    {
        if (!valido() || x >= _max)
        {
            return inf;
        }

        if (x < _min)
        {
            return _min;
        }

        const word_t c = cluster(x);
        const word_t i = indice(x);
        veb* cluster = veb_no_cluster(c);

        if (i < cluster->max())
        {
            return palavra(c, cluster->sucessor(i));
        }

        const word_t c_linha = _resumo->sucessor(c);
        if (c_linha == inf)
        {
            return _max;
        }

        return palavra(c_linha, veb_no_cluster(c_linha)->min());
    }

    word_t predecessor(word_t x) const
    {
        return -1;
    }

    std::string to_string() const
    {
        return "veb_as_string";
    }

private:
    word_t cluster(word_t palavra) const
    {
        return palavra >> _tamanho_meia_palavra;
    }
    word_t indice(word_t palavra) const
    {
        return palavra & ((1 << _tamanho_meia_palavra) - 1);
    }
    word_t palavra(word_t cluster, word_t indice) const
    {
        return (cluster << _tamanho_meia_palavra) | indice;
    }

    veb* veb_no_cluster(word_t c)
    {
        veb* _veb_no_cluster = nullptr;

        if (valido())
        {
            auto it = _clusters.find(c);
            if (it != _clusters.end())
            {
                _veb_no_cluster = it->second;
            }
            else
            {
                _veb_no_cluster = new veb(_tamanho_meia_palavra);
                _clusters[c] = _veb_no_cluster;
            }
        }

        return _veb_no_cluster;
    }

    void troca(word_t& v1, word_t& v2)
    {
        const word_t tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    size_t _tamanho_palavra;
    size_t _tamanho_meia_palavra;

    word_t _min;
    word_t _max;
    veb* _resumo;
    std::unordered_map<word_t, veb*> _clusters;
};

}
}
}

#endif // VEB_H_
