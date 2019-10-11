#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N> class NoRepetido;
template <class N> class NoInexistente;
template <class N> class ArestaRepetida;

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo() {
        nos = {};
    }

    ~Grafo() {
        for (int i = 0; i < nos.size(); i++) {
            free(nos.at(i));
        }
    }

    Grafo & inserirNo(const N &dados) {
        for (int i = 0; i < nos.size(); i++) {
            if (nos.at(i)->info == dados)
                throw NoRepetido<N>(dados);
        }
        No<N,A>* novo_no = new No<N,A>(dados);
        nos.push_back(novo_no);
        return *this;
    }

    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val) {
        int pos_i = -1;
        int pos_f = -1;

        for (int i = 0; i<nos.size(); i++) {
            // encontra no inicial
            if (nos.at(i)->info == inicio) {
                pos_i = i;
            } else if (nos.at(i)->info == fim) { // encontra no final
                pos_f = i;
            }
        }

        if (pos_i == -1)
            throw NoInexistente<N>(inicio);
        else if (pos_f == -1)
            throw NoInexistente<N>(fim);

        // verifica se aresta é repetida
        for (int j = 0; j < nos.at(pos_i)->arestas.size(); j++){
            if (nos.at(pos_i)->arestas.at(j).destino == nos.at(pos_f))
                throw ArestaRepetida<N>(inicio, fim);
        }

        Aresta<N,A> nova_a = Aresta<N,A>(nos.at(pos_f), val);

        nos.at(pos_i)->arestas.push_back(nova_a);

        return *this;
    }

    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);

    int numArestas(void) const {
        int num = 0;
        for (int i = 0; i < nos.size(); i++) {
            num += nos.at(i)->arestas.size();
        }
        return num;
    };

    int numNos(void) const {
        return nos.size();
    };

    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


template <class N>
class ArestaRepetida {
public:
    N inicio, fim;
    ArestaRepetida(N i, N f) {
        inicio = i;
        fim = f;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.inicio << " , " << ar.fim; return out; }