#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <string>
#include <vector>

#include "core/veb.h"
#include "io/file_writer.h"
#include "io/operacao.h"

namespace ufc
{
namespace eda
{
namespace io
{

class executor
{
public:
    executor(const std::string& arquivo_saida)
        : arquivo_saida(arquivo_saida) {}

    void enfila(const ufc::eda::io::op& op)
    {
        _operacoes.push_back(op);
    }

    void executa()
    {
        ufc::eda::io::file_writer fwriter(arquivo_saida);

        for (const ufc::eda::io::op& op : _operacoes)
        {
            executa(fwriter, op);
        }
    }

private:
    void executa(ufc::eda::io::file_writer& fwriter, const ufc::eda::io::op& op)
    {
        fwriter << op;

        if (op.tipoOperacao == ufc::eda::io::op::tipo::INCLUSAO)
        {
            veb.inclui(op.param);
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::REMOCAO)
        {
            veb.remove(op.param);
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::SUCESSAO)
        {
            std::string str_sucessor = "INF";

            const int sucessor = veb.sucessor(op.param);
            if (sucessor != ufc::eda::core::veb::inf)
            {
                str_sucessor = std::to_string(sucessor);
            }

            fwriter << str_sucessor << "\n";
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::PREDECESSAO)
        {
            std::string str_predecessor = "INF";

            const int predecessor = veb.predecessor(op.param);
            if (predecessor != ufc::eda::core::veb::inf)
            {
                str_predecessor = std::to_string(predecessor);
            }

            fwriter << str_predecessor << "\n";
        }
        else if (op.tipoOperacao == ufc::eda::io::op::tipo::IMPRESSAO)
        {
            fwriter << veb.to_string() << "\n";
        }
    }

    std::string arquivo_saida;
    ufc::eda::core::veb veb;
    std::vector<op> _operacoes;
};

}
}
}

#endif // EXECUTOR_H_
