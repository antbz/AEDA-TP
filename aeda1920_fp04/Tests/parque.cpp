#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a implementar -- SOLVED
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    vector<string> nomes;
    for (int i = 0; i < clientes.size(); i++) {
        nomes.push_back(clientes.at(i).nome);
    }
    return sequentialSearch(nomes, nome);
}

//a implementar -- SOLVED
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if (pos == -1) {
        throw ClienteNaoExistente(nome);
    }
    return clientes.at(pos).frequencia;
}



// a alterar/atualizar ? -- SOLVED
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ? -- SOLVED
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ? -- SOLVED
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ? -- SOLVED
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

bool InfoCartao::operator<(const InfoCartao &right) {
    if (this->frequencia > right.frequencia) {
        return true;
    } else if (this->frequencia == right.frequencia && this->nome < right.nome) {
        return true;
    }
    return false;
}

// a implementar -- SOLVED
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}

bool cmpICNome(const InfoCartao &left, const InfoCartao &right) {
    return (left.nome < right.nome);
}

// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(), clientes.end(), cmpICNome);
}

// a implementar -- SOLVED
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;
    ordenaClientesPorFrequencia();
    for (int i = 0; i < clientes.size(); i++) {
        if (clientes.at(i).frequencia >= n1 && clientes.at(i).frequencia <= n2)
            nomes.push_back(clientes.at(i).nome);
    }
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    for (int i = 0; i < pe.getClientes().size(); i++) {
        os << "Nome: " <<  pe.getClientes().at(i).nome << endl;
        os << "Presente: " <<  pe.getClientes().at(i).presente << endl;
        os << "Frequencia: " <<  pe.getClientes().at(i).frequencia << endl;
    }
    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    if (p >= clientes.size() || p < 0)
        throw PosicaoNaoExistente(p);
    info = clientes.at(p);
    return info;
}

// EXCECAO ClienteNaoExistente
ClienteNaoExistente::ClienteNaoExistente(string nome) {
    this->nome = nome;
}

string ClienteNaoExistente::getNome() const {
    return nome;
}

ostream &operator<<(std::ostream out, const ClienteNaoExistente &cne) {
    out << "Cliente não existente: " << cne.getNome();
    return out;
}

//EXCECAO PosicaoNaoExistente
PosicaoNaoExistente::PosicaoNaoExistente(int pos) {
    this->pos = pos;
}

int PosicaoNaoExistente::getValor() const {
    return pos;
}

ostream& operator<<(std::ostream out, const PosicaoNaoExistente &pne) {
    out << "Posição não existente: " << pne.getValor();
    return out;
}
