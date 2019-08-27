#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define QUANT_ARQ 30

#include "./includes/avl.h"
#include "./includes/arq.h"

int main()
{
    avl *raiz[QUANT_ARQ];       //cada avore representa um arquivo e cada no uma palavra
    int quant = 20;             //
    char nomeArq[100], op;      //nome dos arquivos da pasta dados

    inicializaAVL(raiz, QUANT_ARQ);


    /* carrega os arquivos nas arvores */
    for (int i = 0; i < quant; i++)
    {
        sprintf(nomeArq, "dados/doc%d.txt", i + 1);
        raiz[i] = leArq(nomeArq, raiz[i]);
    }

    /* busca palavras nos arquivos (busca uma palavra ou duas com o sistema de e/ou) */
    while (menu(&op) != 's')
    {
        switch (op)
        {
        case 'b':
            buscaPalavra(raiz, quant);
            break;
        case 'i':
            char novoArq[100];
            cout << "Digite o nome do novo arquivo: ";
            cin >> novoArq;
            raiz[quant] = insereArq(novoArq, raiz, quant);
            quant++;
        default:
            break;
        }

        cout << endl;
        system("pause");
        system("cls");
    }

    criaArqInv(raiz, quant);

    for (int i = 0; i < quant; i++)
    {
        libera(raiz[i]);
    }

    return 0;
}