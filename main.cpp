/**
 * Prof: Marcelo Caniato Renhe
 * Aluno: Thiago do Vale Cabral
 * Matrícula: 201965220A
 * Email: thiago.cabral@ice.ufjf.br
 * */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int tam_tabela;
int total_entradas;
int sondagem;
std::vector<int> entradas;

typedef long long (*HashFunction)(long long, int);

/**
 * Funções Hash
 * */
long long div(long long chave, int capacidade)
{
    return abs(chave % capacidade);
}

long long mult(long long chave, int capacidade)
{
    double result = chave * 0.6317981;
    long long parteInteira = result;
    result -= parteInteira;
    return abs(floor(capacidade * result));
}

long long minhaHash(long long chave, int capacidade)
{
    return (long long)sqrt(chave) % capacidade;
}

/**
 * Classe Registro
 * */
template <class T>
class Registro
{
public:
    long long chave;
    T valor;
    bool ativo = true;
};

/**
 * Classe TabelaHash
 * */
template <class T>
class TabelaHash
{
private:
    Registro<T> **elementos;
    int capacidade;

public:
    int colisoes;
    HashFunction hash;

    TabelaHash<T>(HashFunction hash, int cap = 100)
    {
        this->elementos = new Registro<T> *[cap];
        this->hash = hash;
        this->capacidade = cap;
        this->colisoes = 0;
        for (int i = 0; i < cap; i++)
        {
            elementos[i] = NULL;
        }
    }

    ~TabelaHash()
    {
        for (int i = 0; i < this->capacidade; ++i)
        {
            Registro<T> *atual = this->elementos[i];
            delete atual;
        }
        delete[] this->elementos;
    }

    void insere(long long chave, T valor)
    {
        int offset = 0;
        long long chaveHash;
        while (true)
        {
            if (sondagem == 1)
            {
                chaveHash = this->hash(chave + offset, capacidade);
            }
            else if (sondagem == 2)
            {
                long long h1 = this->hash(chave, capacidade);
                long long h2 = 1 + this->hash(chave, 3);
                chaveHash = this->hash(h1 + (offset * h2), capacidade);
            }
            else
            {
                cout << sondagem;
                exit(1);
            }

            try
            {
                if (this->elementos[chaveHash] == NULL)
                {
                    this->elementos[chaveHash] = new Registro<T>;
                    this->elementos[chaveHash]->chave = chave;
                    this->elementos[chaveHash]->valor = valor;
                    return;
                } else if(!this->elementos[chaveHash]->ativo) {
                    this->elementos[chaveHash]->chave = chave;
                    this->elementos[chaveHash]->valor = valor;
                    return;
                }
                else
                {
                    this->colisoes++;
                }
            }
            catch (const char &e)
            {
                cerr << e << endl;
            }
            offset++;
        }
    }

    T recupera(long long chave)
    {
        int offset = 0;
        long long chaveHash;
        while (true)
        {
            if (sondagem == 1)
            {
                chaveHash = this->hash(chave + offset, capacidade);
            }
            else if (sondagem == 2)
            {
                long long h1 = this->hash(chave, capacidade);
                long long h2 = 1 + this->hash(chave, 3);
                chaveHash = this->hash(h1 + offset * h2, capacidade);
            }
            else
            {
                cout << sondagem;
                exit(1);
            }

            try
            {
                if (this->elementos[chaveHash] != NULL and this->elementos[chaveHash]->chave == chave and this->elementos[chaveHash]->ativo)
                {
                    return this->elementos[chaveHash]->valor;
                }
            }
            catch (const char &e)
            {
                cerr << e << endl;
            }
            offset++;
        }
    }

    void altera(long long chave, T valor)
    {
        int offset = 0;
        long long chaveHash;
        while (true)
        {
            if (sondagem == 1)
            {
                chaveHash = this->hash(chave + offset, capacidade);
            }
            else if (sondagem == 2)
            {
                long long h1 = this->hash(chave, capacidade);
                long long h2 = 1 + this->hash(chave, 3);
                chaveHash = this->hash(h1 + offset * h2, capacidade);
            }
            else
            {
                cout << sondagem;
                exit(1);
            }

            try
            {
                if (this->elementos[chaveHash] != NULL and this->elementos[chaveHash]->chave == chave and this->elementos[chaveHash]->ativo)
                {
                    this->elementos[chaveHash]->valor = valor;
                    return;
                }
            }
            catch (const char &e)
            {
                cerr << e << endl;
            }
            offset++;
        }
    }

    void remove(long long chave)
    {
        int offset = 0;
        long long chaveHash;
        while (true)
        {
            if (sondagem == 1)
            {
                chaveHash = this->hash(chave + offset, capacidade);
            }
            else if (sondagem == 2)
            {
                long long h1 = this->hash(chave, capacidade);
                long long h2 = 1 + this->hash(chave, 3);
                chaveHash = this->hash(h1 + offset * h2, capacidade);
            }
            else
            {
                cout << sondagem;
                exit(1);
            }

            try
            {
                if (this->elementos[chaveHash] != NULL and this->elementos[chaveHash]->chave == chave and this->elementos[chaveHash]->ativo)
                {
                    this->elementos[chaveHash]->ativo = false;
                }
            }
            catch (const char &e)
            {
                cerr << e << endl;
            }
            offset++;
        }
    }

    void percorre()
    {
        Registro<T> *atual;
        cout << "!--------------------!" << endl;
        for (int i = 0; i < this->capacidade; i++)
        {
            atual = this->elementos[i];
            if (atual != NULL && atual->ativo)
                cout << i << ":"
                     << " {CHAVE:[" << atual->chave << "] VALOR:[" << atual->valor << "]}" << endl;
        }
        cout << "!--------------------!" << endl;
    }
};

void lerArquivo(std::istream &arquivo)
{
    std::string linha;

    std::getline(arquivo, linha);
    std::stringstream ssin(linha);
    std::vector<std::string> array;
    std::string result;

    while (std::getline(ssin, result, ' '))
    {
        array.push_back(result);
    }

    tam_tabela = std::stoi(array[0]);
    total_entradas = std::stoi(array[1]);
    sondagem = std::stoi(array[2]);

    while (std::getline(arquivo, linha))
    {
        int valor = std::stoi(linha);
        entradas.push_back(valor);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Faltando um arquivo de entrada!" << std::endl;
        exit(1);
    }

    const char *entrada = argv[1];
    std::ifstream arquivo_entrada(entrada);
    lerArquivo(arquivo_entrada);
    arquivo_entrada.close();

    TabelaHash<int> tabelaDiv(div, tam_tabela);
    for (int i = 0; i < total_entradas; i++)
    {
        tabelaDiv.insere(entradas[i], entradas[i]);
    }
    tabelaDiv.percorre();

    cout << "!==COLISOES==!" << endl;
    cout << "DIVISAO: " << tabelaDiv.colisoes << endl;
    return 0;
}