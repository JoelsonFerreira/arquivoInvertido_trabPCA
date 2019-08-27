typedef struct arv
{
    char chave[100];
    int quant;
    struct arv *esq;
    struct arv *dir;
    int altura;
} avl;

int calculo(avl *raiz)
{
    int altEsq = 0, altDir = 0;
    if (raiz->dir != NULL)
        altDir = raiz->dir->altura;
    if (raiz->esq != NULL)
        altEsq = raiz->esq->altura;
    return altEsq - altDir;
}

avl *rotacaoDir(avl *raiz)
{
    avl *aux = raiz;
    raiz = aux->esq;
    aux->esq = raiz->dir;
    raiz->dir = aux;
    if (aux != NULL)
    {
        if (aux->esq != NULL && aux->dir != NULL)
            aux->altura = (aux->esq->altura > aux->dir->altura) ? aux->esq->altura + 1 : aux->dir->altura + 1;
        else if (aux->esq != NULL)
            aux->altura = aux->esq->altura + 1;
        else if (aux->dir != NULL)
            aux->altura = aux->dir->altura + 1;
        else
            aux->altura = 1;
    }
    if (raiz != NULL)
    {
        if (raiz->esq != NULL && raiz->dir != NULL)
            raiz->altura = (raiz->esq->altura > raiz->dir->altura) ? raiz->esq->altura + 1 : raiz->dir->altura + 1;
        else if (raiz->esq != NULL)
            raiz->altura = raiz->esq->altura + 1;
        else if (raiz->dir != NULL)
            raiz->altura = raiz->dir->altura + 1;
        else
            raiz->altura = 1;
    }
    return raiz;
}

avl *rotacaoEsq(avl *raiz)
{
    avl *aux = raiz;
    raiz = aux->dir;
    aux->dir = raiz->esq;
    raiz->esq = aux;
    if (aux != NULL)
    {
        if (aux->esq != NULL && aux->dir != NULL)
            aux->altura = (aux->esq->altura > aux->dir->altura) ? aux->esq->altura + 1 : aux->dir->altura + 1;
        else if (aux->esq != NULL)
            aux->altura = aux->esq->altura + 1;
        else if (aux->dir != NULL)
            aux->altura = aux->dir->altura + 1;
        else
            aux->altura = 1;
    }
    if (raiz != NULL)
    {
        if (raiz->esq != NULL && raiz->dir != NULL)
            raiz->altura = (raiz->esq->altura > raiz->dir->altura) ? raiz->esq->altura + 1 : raiz->dir->altura + 1;
        else if (raiz->esq != NULL)
            raiz->altura = raiz->esq->altura + 1;
        else if (raiz->dir != NULL)
            raiz->altura = raiz->dir->altura + 1;
        else
            raiz->altura = 1;
    }
    return raiz;
}

avl *casos(avl *raiz)
{
    if (raiz == NULL)
        return NULL;
    if (calculo(raiz) == 2 && calculo(raiz->esq) == -1)
    {
        raiz->esq = rotacaoEsq(raiz->esq);
        raiz = rotacaoDir(raiz);
        return raiz;
    }
    if (calculo(raiz) == -2 && calculo(raiz->dir) == 1)
    {
        raiz->dir = rotacaoDir(raiz->dir);
        raiz = rotacaoEsq(raiz);
        return raiz;
    }
    if (calculo(raiz) == 2)
    {
        raiz = rotacaoDir(raiz);
        return raiz;
    }
    if (calculo(raiz) == -2)
    {
        raiz = rotacaoEsq(raiz);
        return raiz;
    }
    return raiz;
}

void print(avl *raiz)
{
    if (raiz == NULL)
        return;
    cout << raiz->chave << " - " << raiz->altura << endl;
    cout << "esquerda\n";
    print(raiz->esq);
    cout << "direita\n";
    print(raiz->dir);
    cout << "volta\n";
}

avl *inserir(avl *raiz, char chave[100])
{
    if (raiz == NULL)
    {
        raiz = (avl *)malloc(sizeof(avl));
        strcpy(raiz->chave, chave);
        raiz->altura = 1;
        raiz->quant = 1;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    else if (strcmp(chave, raiz->chave) == 0)
    {
        raiz->quant++;
    }
    else if (strcmp(chave, raiz->chave) < 0)
    {
        raiz->esq = inserir(raiz->esq, chave);
        if (raiz->esq != NULL)
        {
            if (raiz->dir == NULL)
            {
                raiz->altura = 1 + raiz->esq->altura;
            }
            else
            {
                raiz->altura = 1 + raiz->esq->altura;
            }
        }
        if (raiz->altura == 2 || raiz->altura == -2)
            raiz = casos(raiz);
    }
    else if (strcmp(chave, raiz->chave) > 0)
    {
        raiz->dir = inserir(raiz->dir, chave);
        if (raiz->dir != NULL)
        {
            if (raiz->esq == NULL)
            {
                raiz->altura = 1 + raiz->dir->altura;
            }
            else
            {
                raiz->altura = 1 + raiz->dir->altura;
            }
        }
        if (calculo(raiz) == 2 || calculo(raiz) == -2)
        {
            raiz = casos(raiz);
        }
    }
    return raiz;
}

void removerNo(avl **raiz)
{
    if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
    {
        free(*raiz);
        *raiz = NULL;
        return;
    }
    if ((*raiz)->esq == NULL || (*raiz)->dir == NULL)
    {
        if ((*raiz)->dir == NULL)
        {
            avl *aux = (*raiz);
            (*raiz) = (*raiz)->esq;
            free(aux);
        }
        else
        {
            avl *aux = (*raiz);
            (*raiz) = (*raiz)->dir;
            free(aux);
        }
        return;
    }
    if ((*raiz)->esq != NULL && (*raiz)->dir != NULL)
    {
        avl *aux = (*raiz)->dir;
        avl *pai = *raiz;
        while (aux->esq != NULL)
        {
            pai = aux;
            aux = aux->esq;
        }
        avl *aux2 = aux;
        if (pai != *raiz)
            pai->esq = NULL;
        aux = aux2->dir;
        if ((*raiz)->dir != aux2)
            aux2->dir = (*raiz)->dir;
        aux2->esq = (*raiz)->esq;
        free(*raiz);
        *raiz = aux2;
        return;
    }
}

avl *remover(avl *raiz, char chave[100])
{
    if (raiz == NULL)
    {
        return NULL;
    }
    if (strcmp(raiz->chave, chave) == 0)
    {
        removerNo(&raiz);
    }
    else if (strcmp(chave, raiz->chave) < 0)
    {
        raiz->esq = remover(raiz->esq, chave);
    }
    else if (strcmp(chave, raiz->chave) > 0)
    {
        raiz->dir = remover(raiz->dir, chave);
    }

    if (raiz != NULL)
    {
        if (raiz->esq != NULL && raiz->dir != NULL)
            raiz->altura = (raiz->esq->altura > raiz->dir->altura) ? raiz->esq->altura + 1 : raiz->dir->altura + 1;
        else if (raiz->esq != NULL)
            raiz->altura = raiz->esq->altura + 1;
        else if (raiz->dir != NULL)
            raiz->altura = raiz->dir->altura + 1;
        else
            raiz->altura = 1;
        if (calculo(raiz) == 2 || calculo(raiz) == -2)
        {
            raiz = casos(raiz);
        }
    }

    return raiz;
}

avl *buscar(avl *raiz, char chave[100])
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else if (strcmp(chave, raiz->chave) < 0)
    {
        return buscar(raiz->esq, chave);
    }
    else if (strcmp(chave, raiz->chave) > 0)
    {
        return buscar(raiz->dir, chave);
    }
    else if (strcmp(chave, raiz->chave) == 0)
    {
        return raiz;
    }
    return raiz;
}

void libera(avl *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    else if (raiz->dir == NULL && raiz->esq == NULL)
    {
        free(raiz);
        return;
    }
    else
    {
        if (raiz->esq != NULL)
            libera(raiz->esq);
        if (raiz->dir != NULL)
            libera(raiz->dir);
    }
}

void inicializaAVL(avl *raiz[], int quant)
{
    for (int i = 0; i < quant; i++)
    {
        raiz[i] = NULL;
    }
}

avl *getMin(avl *raiz)
{
    if (raiz->esq == NULL)
        return raiz;
    return getMin(raiz->esq);
}

void criaArqInv(avl *raiz[], int quant)
{
    FILE *arq = fopen("arquivo_invetido.txt", "w");

    for (int i = 0; i < quant; i++)
    {
        while (raiz[i] != NULL)
        {
            avl *aux = getMin(raiz[i]);
     
            fprintf(arq, "%s (%d;%d)", aux->chave, aux->quant, i + 1);
     
            for (int j = i + 1; j < quant; j++)
            {
                avl *auxBus = buscar(raiz[j], aux->chave);
                if (auxBus != NULL)
                {
                    fprintf(arq, ", (%d;%d)", auxBus->quant, j + 1);
     
                    raiz[j] = remover(raiz[j], auxBus->chave);
                }
            }
            fprintf(arq, "\n");
     
            raiz[i] = remover(raiz[i], aux->chave);
        }
        // cout << "Arquivo doc" << i + 1 << ".txt finalizado.\n";
    }

    fclose(arq);
}