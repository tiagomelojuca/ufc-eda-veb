#ifndef VEB_H_
#define VEB_H_

#include <functional>
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

    bool valido() const
    {
        return _resumo != nullptr;
    }

    word_t min() const
    {
        return _min;
    }

    word_t max() const
    {
        return _max;
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
        veb* cluster_alvo = nullptr;
        word_t c = inf;
        word_t i = inf;

        if (x == _min)
        {
            c = _resumo->_min;
            if (c == inf)
            {
                _min = inf;
                return;
            }

            cluster_alvo = veb_no_cluster(c);
            i = cluster_alvo->_min;

            x = palavra(c, i);
            _min = x;
        }

        if (cluster_alvo == nullptr)
        {
            c = cluster(x);
            i = indice(x);
            cluster_alvo = veb_no_cluster(c);
        }

        if (cluster_alvo->valido())
        {
            cluster_alvo->remove(i);

            if (cluster_alvo->_min == inf)
            {
                _resumo->remove(c);

                delete _clusters.find(c)->second;
                _clusters.erase(c);
            }

            if (_resumo->_min == inf)
            {
                _max = _min;
            }
            else
            {
                const word_t c_linha = _resumo->_max;
                _max = palavra(c_linha, veb_no_cluster(c_linha)->_max);
            }
        }
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

        const word_t sucessor_no_cluster = cluster->sucessor(i);
        if (sucessor_no_cluster != inf)
        {
            const word_t _sucessor = palavra(c, sucessor_no_cluster);
            return _sucessor <= _max ? _sucessor : _max;
        }

        const word_t c_linha = _resumo->sucessor(c);
        if (c_linha == inf)
        {
            return _max;
        }

        const word_t _sucessor = palavra(c_linha, veb_no_cluster(c_linha)->min());
        return _sucessor <= _max ? _sucessor : _max;
    }

    word_t predecessor(word_t x)
    {
        if (!valido() || x <= _min)
        {
            return inf;
        }

        if (x > _max)
        {
            return _max;
        }

        const word_t c = cluster(x);
        const word_t i = indice(x);
        veb* cluster = veb_no_cluster(c);

        const word_t predecessor_no_cluster = cluster->predecessor(i);
        if (predecessor_no_cluster != inf)
        {
            return palavra(c, predecessor_no_cluster);
        }

        const word_t c_linha = _resumo->predecessor(c);
        if (c_linha == inf)
        {
            return _min;
        }

        return palavra(c_linha, veb_no_cluster(c_linha)->max());
    }

    void for_each(std::function<void(word_t)> callback)
    {
        word_t it = min();
        while (it != inf)
        {
            callback(it);
            it = sucessor(it);
        }
    }

    void reverse_for_each(std::function<void(word_t)> callback)
    {
        word_t it = max();
        while (it != inf)
        {
            callback(it);
            it = predecessor(it);
        }
    }

    std::string to_string()
    {
        std::string str;

        if (valido())
        {
            str += "Min: ";
            str += std::to_string(min());
            str += ", ";

            _resumo->for_each([this, &str](word_t c) {
                str += "C[";
                str += std::to_string(c);
                str += "]: ";

                veb& cluster = *veb_no_cluster(c);
                if (cluster.valido())
                {
                    cluster.for_each([this, c, &str](word_t i) {
                        str += std::to_string(palavra(c, i));
                        str += ", ";
                    });
                }
                else {
                    str += "cluster_invalido";
                }
            });

            if (str.back() == ' ')
            {
                str.erase(str.length() - 2);
            }
        }
        else {
            str += "veb_invalida";
        }

        return str;
    }

    std::string cadeia_sucessores()
    {
        std::string str = "";

        for_each([&str](word_t it) {
            str += std::to_string(it);
            str += " -> ";
        });

        if (str != "")
        {
            str.erase(str.length() - 4);
        }

        return str;
    }

    std::string cadeia_predecessores()
    {
        std::string str = "";

        reverse_for_each([&str](word_t it) {
            str += std::to_string(it);
            str += " -> ";
        });

        if (str != "")
        {
            str.erase(str.length() - 4);
        }

        return str;
    }

    std::string trace()
    {
        std::string str;

        str += "veb::trace()\n";
        str += "    .:. visao_nivel_inicial  : ";
        str += to_string();
        str += "\n";
        str += "    .:. cadeia_sucessores    : ";
        str += cadeia_sucessores();
        str += "\n";
        str += "    .:. cadeia_predecessores : ";
        str += cadeia_predecessores();
        str += "\n";

        return str;
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
