#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    srand((int) time(0));
    numPresentes = rand() % 5 + 1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual = 0;
    prox_saida = 0;
    srand((int) time(0));
    prox_chegada = rand() % 20 + 1;
    clientes_atendidos = 0;
}

//a alterar
void Balcao:: proximoEvento()
{
    if (prox_chegada <= prox_saida || prox_saida == 0) {
        tempo_atual += prox_chegada;
        prox_saida -= prox_chegada;
        this->chegada();
    } else if (prox_saida <= prox_chegada) {
        tempo_atual += prox_saida;
        prox_chegada -= prox_saida;
        this->saida();
    }
}

//a alterar
void Balcao::chegada()
{
    Cliente chega;
    srand((int) time(0));
    prox_chegada = rand() % 20 + 1;
    if (clientes.empty()) {
        prox_saida = tempo_atual + tempo_embrulho * chega.getNumPresentes();
    }
    clientes.push(chega);
    cout << "tempo= " << tempo_atual << endl << "chegou novo cliente com " << chega.getNumPresentes() << " presentes" << endl;
}

//a alterar
void Balcao::saida()
{
    Cliente sair;
    try {
        sair = this->getProxCliente();
    } catch (FilaVazia) {
        throw FilaVazia();
    }
    clientes.pop();
    clientes_atendidos++;
    prox_saida = tempo_atual + tempo_embrulho * clientes.front().getNumPresentes();
    cout << "tempo= " << tempo_atual << endl << "saiu cliente com " << sair.getNumPresentes() << " presentes" << endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
    out << "Clientes atendidos: " << b1.clientes_atendidos << endl;
    out << "Clientes em espera: " << b1.clientes.size();
    return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if (clientes.empty()) {
        throw FilaVazia();
    }
    return clientes.front();
}

      
