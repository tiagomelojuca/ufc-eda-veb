#ifndef HTBL_H_
#define HTBL_H_

#include <vector>
#include <unordered_map>

namespace ufc
{
namespace eda
{
namespace core
{

template <typename chave_t, class valor_t>
class htbl
{
private:
    struct noh_t
    {
        chave_t  chave =       0;
        valor_t* valor = nullptr;
        noh_t* proximo = nullptr;
    };

    enum class operacao_t { no_op, table_doubling, table_halving };

public:
    htbl() : htbl(4) {};

    htbl(size_t m) : _m(m)
    {
        _T = std::vector<noh_t*>(m, nullptr);
    }

    ~htbl()
    {
        for (noh_t* noh : _T)
        {
            while (noh != nullptr)
            {
                noh_t* proximo = noh->proximo;
                delete noh->valor;
                delete noh;
                noh = proximo;
            }
        }
    }

    valor_t* busca(chave_t k)
    {
        valor_t* valor_buscado = nullptr;
    
        const size_t hash = hash_universal(k);
        const noh_t* noh = _T[hash];

        while (noh != nullptr)
        {
            if (noh->chave == k)
            {
                valor_buscado = noh->valor;
                break;
            }

            noh = noh->proximo;
        }

        return valor_buscado;
    }

    void inclui(chave_t k, valor_t* v)
    {
        if (_n == _m)
        {
            rehash(operacao_t::table_doubling);
        }

        const size_t hash = hash_universal(k);

        auto novo_noh = new noh_t;
        novo_noh->chave = k;
        novo_noh->valor = v;

        noh_t* noh_cabeca = _T[hash];
        if (noh_cabeca != nullptr)
        {
            novo_noh->proximo = noh_cabeca;
        }
        else
        {
            _n++;
        }

        _T[hash] = novo_noh;
    }

    void remove(chave_t k)
    {
        const size_t hash = hash_universal(k);

        noh_t* anterior = nullptr;
        noh_t* corrente = _T[hash];

        while (corrente != nullptr)
        {
            if (corrente->chave == k)
            {
                break;
            }

            anterior = corrente;
            corrente = corrente->proximo;
        }

        if (corrente != nullptr)
        {
            if (anterior != nullptr)
            {
                anterior->proximo = corrente->proximo;
            }
            else
            {
                _T[hash] = corrente->proximo;
                if (corrente->proximo == nullptr)
                {
                    _n--;
                }
            }

            delete corrente->valor;
            delete corrente;
        }

        if (4 * _n <= _m)
        {
            rehash(operacao_t::table_halving);
        }
    }

private:
    void rehash(operacao_t op)
    {
        const std::vector<noh_t*> T = _T;

        const size_t delta = 2;
        if (op == operacao_t::table_doubling)
        {
            _m *= delta;
        }
        else if (op == operacao_t::table_halving)
        {
            _m /= delta;
        }

        _n = 0;
        _T.clear();
        _T.reserve(_m);
        _T.assign(_m, nullptr);

        for (noh_t* noh : T)
        {
            while (noh != nullptr)
            {
                noh_t* proximo = noh->proximo;
                inclui(noh->chave, noh->valor);
                delete noh;
                noh = proximo;
            }
        }
    }

    size_t hash_universal(chave_t k) const
    {
        uint64_t ak = static_cast<uint64_t>(_a) * static_cast<uint64_t>(k);
        uint64_t akb = (ak + _b) % _p;

        return static_cast<size_t>(akb % _m);
    }

    static constexpr uint64_t _p = 4294967311u;
    static constexpr uint32_t _a = 2654435761u;
    static constexpr uint32_t _b = 1123456789u;

    size_t _m = 4;
    size_t _n = 0;
    std::vector<noh_t*> _T;
};

}
}
}

#endif // HTBL_H_
