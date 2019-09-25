#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = lotacao;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    auto pos = find_if(clientes.begin(), clientes.end(), [&](const InfoCartao& c){return c.nome == nome;});
    if (pos == clientes.end())
        return -1;
    else
        return pos - clientes.begin();
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() < numMaximoClientes) {
        InfoCartao novoCliente;
        novoCliente.nome = nome;
        novoCliente.presente = false;
        clientes.push_back(novoCliente);
        return true;
    } else
        return false;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1)
        return false;
    if (clientes.at(pos).presente)
        return false;
    if (vagas == 0)
        return false;
    clientes.at(pos).presente = true;
    vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || clientes.at(pos).presente)
        return false;
    clientes.erase(clientes.begin() + pos);
    return true;
}

bool ParqueEstacionamento::sair(const string &nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || not clientes.at(pos).presente)
        return false;
    clientes.at(pos).presente = false;
    vagas++;
    return true;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}