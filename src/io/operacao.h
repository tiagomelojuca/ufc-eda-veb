#ifndef OPERACAO_H_
#define OPERACAO_H_

#include <string>

namespace ufc
{
namespace eda
{
namespace io
{

struct op
{
    enum class tipo { INCLUSAO, REMOCAO, SUCESSAO, PREDECESSAO, IMPRESSAO };

    op(tipo tipoOperacao, int param = -1)
        : tipoOperacao(tipoOperacao), param(param) {}

    bool operator==(const op& outra) const {
        return tipoOperacao == outra.tipoOperacao && param == outra.param;
    }

    std::string to_string() const
    {
        std::string str;

        if (tipoOperacao == tipo::INCLUSAO)
        {
            str += "INC";
        }
        else if (tipoOperacao == tipo::REMOCAO)
        {
            str += "REM";
        }
        else if (tipoOperacao == tipo::SUCESSAO)
        {
            str += "SUC";
        }
        else if (tipoOperacao == tipo::PREDECESSAO)
        {
            str += "PRE";
        }
        else if (tipoOperacao == tipo::IMPRESSAO)
        {
            str += "IMP";
        }

        if (param != -1)
        {
            str += " ";
            str += std::to_string(param);
        }

        return str;
    }

    tipo tipoOperacao;
    int param = -1;
};

}
}
}

#endif // OPERACAO_H_
