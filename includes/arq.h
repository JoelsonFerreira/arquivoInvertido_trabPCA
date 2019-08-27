#include <conio.h>

#define STOP_TAM 17
#define CARACTERES_LIXO 13

typedef struct
{
    int quant, arq;
} bus;

/* palavras ignoradas */
char stopWords[STOP_TAM][100] = {
    "e",
    "ou",
    "ate",
    "de",
    "em",
    "a",
    "ante",
    "apos",
    "para",
    "sem",
    "por",
    "tras",
    "sobre",
    "sob",
    "entre",
    "entao",
    "esta"
};

/* caracteres ignorados */
char caractereRuim[CARACTERES_LIXO] = {
    '.',
    '!',
    '?',
    ',',
    '(',
    ')',
    '[',
    ']',
    '\\',
    '/',
    '\'',
    '"',
    '-'
};

void swap(bus *a, bus *b)
{
    bus t = *a;
    *a = *b;
    *b = t;
}

int partition(bus arr[], int low, int high)
{
    int pivot = arr[high].quant;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].quant <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(bus arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int printBus(bus arr[], bus arr2[], char palavra1[], char palavra2[], int quant, int e1_ou2)
{
    int printou = 0;

    for (int i = quant; arr[i].quant != 0; i--)
    {
        if (e1_ou2 == 1)
        {
            for (int j = quant; arr2[j].quant != 0; j--)
            {
                if (arr2[j].arq == arr[i].arq)
                {
                    cout << "[ARQUIVO " << arr2[j].arq << "]" << endl;
                    cout << "\t- " << arr[i].quant << " ocorrencias de " << palavra1 << endl;
                    cout << "\t- " << arr2[j].quant << " ocorrencias de  " << palavra2 << endl
                         << endl;
                    printou = 1;
                    break;
                }
            }
        }
        else if (e1_ou2 == 2)
        {
            if (i == quant)
            {
                cout << "[" << palavra1 << "]" << endl;
            }
            cout << "\t" << arr[i].quant << " ocorrencias no arquivo " << arr[i].arq << endl;
            printou = 1;
        }
        else
        {
            cout << arr[i].quant << " ocorrencias no arquivo " << arr[i].arq << endl;
            printou = 1;
        }
    }

    for (int i = quant; e1_ou2 == 2 && arr2[i].quant != 0; i--)
    {
        if (i == quant)
        {
            cout << "[" << palavra2 << "]" << endl;
        }
        cout << "\t" << arr2[i].quant << " ocorrencias no arquivo " << arr2[i].arq << endl;
        printou = 1;
    }

    return printou;
}

bool verificaC(char caractere)
{
    for (int i = 0; i < CARACTERES_LIXO; i++)
    {
        if (caractere == caractereRuim[i])
        {
            return true;
        }
    }
    return false;
}

void puxa(char *palavra, int i)
{
    for (; palavra[i] != '\0'; i++)
    {
        palavra[i] = palavra[i + 1];
    }
}

void consertaPalavra(char palavra[])
{
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        // if(palavra[i]>='A' && palavra[i]<='Z')
        // {
        // palavra[i] += 32;
        // }
        palavra[i] = tolower(palavra[i]);
        if (verificaC(palavra[i]) && palavra[i + 1] == '\0')
        {
            palavra[i] = '\0';
            return;
        }
        else if (verificaC(palavra[i]))
        {
            puxa(palavra, i);
        }
    }
}

bool verificaStop(char *palavra)
{
    for (int i = 0; i < STOP_TAM; i++)
    {
        if (strcmp(palavra, stopWords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

avl *leArq(char *nomeArq, avl *raiz)
{
    FILE *arq = fopen(nomeArq, "r");
    if (arq == NULL)
    {
        cout << "O arquivo " << nomeArq << " nao foi encontrado.\n";
        return NULL;
    }

    char novo[100] = "";

    while (fscanf(arq, "%s", novo) && strcmp(novo, "") != 0)
    {
        consertaPalavra(novo);
        if (!verificaStop(novo))
        {
            raiz = inserir(raiz, novo);
        }
        strcpy(novo, "");
    }

    fclose(arq);

    return raiz;
}

char menu(char *op)
{
    cout << "\t[b] Buscar\n";
    cout << "\t[i] Inserir novo arquivo\n";
    cout << "\t[s] Sair\n";
    cout << "Opcao: ";

    *op = getch();

    system("cls");

    return *op;
}

int e_ou(char *palavra1, char *palavra2)
{
    char aux[100];
    int i = 0;
    int e1_ou2 = 0;

    for (i = 0; palavra1[i] != '\0'; i++)
    {
        palavra1[i] = tolower(palavra1[i]);
        palavra2[i] = tolower(palavra2[i]);
        if (palavra1[i - 1] == ' ' && palavra1[i] == 'e' && palavra1[i + 1] == ' ')
        {
            strncpy(aux, palavra1, i - 1);
            aux[i - 1] = '\0';
            i += 2;
            e1_ou2 = 1;
            break;
        }
        else if (palavra1[i - 1] == ' ' && palavra1[i] == 'o' && palavra1[i + 1] == 'u' && palavra1[i + 2] == ' ')
        {
            strncpy(aux, palavra1, i - 1);
            aux[i - 1] = '\0';
            i += 3;
            e1_ou2 = 2;
            break;
        }
    }
    if (e1_ou2)
    {
        for (int j = 0; palavra1[i - 1] != '\0'; i++, j++)
        {
            palavra2[j] = palavra1[i];
            palavra1[i] = tolower(palavra1[i]);
            palavra2[j] = tolower(palavra2[j]);
        }
        strcpy(palavra1, aux);
    }
    return e1_ou2;
}

int buscaPalavra(avl *raiz[], int quant)
{
    char palavra[100], aux[100];
    int palavra_quantArqs = 0, palavra_quantArqs2 = 0;
    ;
    bus *b = (bus *)calloc(sizeof(bus), quant);
    bus *b2 = (bus *)calloc(sizeof(bus), quant);

    cout << "Digite a palavra buscada[e/ou]: ";
    scanf(" %[^\n]", palavra);

    int e1_ou2 = e_ou(palavra, aux);

    system("cls");

    for (int i = 0; i < quant; i++)
    {
        avl *busca = buscar(raiz[i], palavra);
        if (busca != NULL)
        {
            b[palavra_quantArqs].quant = busca->quant;
            b[palavra_quantArqs].arq = i + 1;
            palavra_quantArqs++;
        }
        if (e1_ou2)
        {
            avl *busca2 = buscar(raiz[i], aux);
            if (busca2 != NULL)
            {
                b2[palavra_quantArqs2].quant = busca2->quant;
                b2[palavra_quantArqs2].arq = i + 1;
                palavra_quantArqs2++;
            }
        }
    }

    quickSort(b, 0, quant - 1);
    quickSort(b2, 0, quant - 1);

    int foi = printBus(b, b2, palavra, aux, quant - 1, e1_ou2);

    if (!foi)
    {
        cout << "Nenhuma ocorrencia encontrada!" << endl;
    }

    free(b);
    free(b2);

    return palavra_quantArqs;
}

avl *insereArq(char *nomeArq, avl *raiz[], int quant)
{
    if (quant < QUANT_ARQ)
    {
        raiz[quant] = leArq(nomeArq, raiz[quant]);
        return raiz[quant];
    }
    else
    {
        cout << "Desculpe, ja estamos com muitos arquivos!\n";
    }
    return NULL;
}
