/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    return criancas;
}

// a implementar
string Jogo::escreve() const
{
    string res = "";
    for (auto it = criancas.begin(); it != criancas.end(); it++) {
        res += it->escreve() + "\n";
    }
    return res;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    list<Crianca> copia_criancas = criancas;
    unsigned n_palavras = numPalavras(frase);
    auto it = copia_criancas.begin();
    while (copia_criancas.size() > 1) {
        for (int i = 1; i < n_palavras; i++) {
            it++;
            if (it == copia_criancas.end())
                it = copia_criancas.begin();
        }
        it = copia_criancas.erase(it);
        if (it == copia_criancas.end())
            it = copia_criancas.begin();
    }
    *c1 = *copia_criancas.begin();
    return *c1;
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res = criancas;
    auto it = res.begin();
    while (it != res.end()) {
        if (it->getIdade() <= id)
            it = res.erase(it);
        else
            it++;
    }
    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas = l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
	if (criancas.size() != j2.criancas.size())
        return false;
	auto it1 = criancas.begin();
	auto it2 = j2.criancas.begin();
    while (it1 != criancas.end()) {
        if (*it1 == *it2) {
            it1++;
            it2++;
            continue;
        }
        return false;
	}
    return true;
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    list<Crianca> copy = criancas;
    for (int i = 0; i < criancas.size(); i++) {
        auto it = copy.begin();
        int pos = rand()%(criancas.size() - i);
        advance(it, pos);
        res.push_back(*it);
        copy.erase(it);
    }
    return res;
}
