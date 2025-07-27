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
public:
    htbl()
    {
    };

    ~htbl()
    {
    }

    valor_t* busca(chave_t k)
    {
        auto it = umap.find(k);
        if (it == umap.end())
        {
            return nullptr;
        }

        return it->second;
    }

    void inclui(chave_t k, valor_t* v)
    {
        umap[k] = v;
    }

    void remove(chave_t k)
    {
        umap.erase(k);
    }

private:
    std::unordered_map<chave_t, valor_t*> umap;
};

}
}
}

#endif // HTBL_H_
