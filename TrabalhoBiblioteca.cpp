#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "livros.h"

#define TAM 20

//Pilha de Livros do usuario.
typedef struct EmprestimoLivro
{
    char NomeLivro[TAM];
    int CodigoLivro;
    int DiasEmprestimo;
    struct EmprestimoLivro *prox;
} PilhaUsuario;

//Fila de espera por livro.
typedef struct Espera
{
    char NomeUsuario[TAM];
    struct Espera *prox;
} FilaEspera;

int Tam = 0;
int QtdLivros = 0;

//Lista de livros
typedef struct Livro
{
    char Nome[TAM];
    int Disponivel;
    int Codigo;
    FilaEspera *Fila;
    struct Livro *prox;
} ListaLivros;

/*  ------Pilha------    */

//verifica se a pilha esta vazia
int PilhaVazia(PilhaUsuario *Pilha)
{
    if (Pilha == NULL)
    {
        return 1;
    }
    else if (Pilha->prox == NULL)
        return 1;
    else
        return 0;
}

//Aloca pilha, não precisa adicionar na main.
PilhaUsuario *AlocaPilha(char *String)
{
    PilhaUsuario *novo = (PilhaUsuario *)malloc(sizeof(PilhaUsuario));
    if (!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        strcpy(novo->NomeLivro, String);
        novo->CodigoLivro = Tam;
        return novo;
    }
}

//Adiciona elemento
void InserirPilha(PilhaUsuario *Pilha, char *String)
{
    PilhaUsuario *novo = AlocaPilha(String);
    novo->prox = NULL;

    if (PilhaVazia(novo))
        Pilha->prox = novo;
    else
    {
        PilhaUsuario *tmp = Pilha->prox;

        while (tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    Tam++;
}

//remove da pilha
PilhaUsuario *RemovePilha(PilhaUsuario *Pilha)
{
    if (Pilha->prox == NULL)
    {
        printf("Pilha ja esta vazia\n\n");
        return NULL;
    }
    else
    {
        PilhaUsuario *ultimo = Pilha->prox,
                     *penultimo = Pilha;

        while (ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL;
        Tam--;
        return ultimo;
    }
}

/*  ------FILA------    */

//inicia fila
void inicia(FilaEspera *Fila)
{
    Fila->prox = NULL;
}

//verifica se a fila esta vazia
int FilaVazia(FilaEspera *Fila)
{
    if (Fila == NULL)
        return 1;
    else if (Fila->prox == NULL)
        return 1;
    else
        return 0;
}

//Aloca fila, não precisa colocar na main.
FilaEspera *AlocaFila()
{
    FilaEspera *novo = (FilaEspera *)malloc(sizeof(FilaEspera));
    if (!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        printf("Nome do Usuario: ");
        getchar();
        scanf("%[A-Z a-z]", &novo->NomeUsuario);
        return novo;
    }
}

//insere na fila
void InsereFila(FilaEspera *Fila)
{
    FilaEspera *novo = AlocaFila();
    novo->prox = NULL;

    if (FilaVazia(Fila))
    {
        Fila->prox = novo;
    }
    else
    {
        FilaEspera *tmp = Fila->prox;

        while (tmp->prox != NULL)
            tmp = tmp->prox;
        tmp->prox = novo;
    }
}

//remove da fila
FilaEspera *RemoveFila(FilaEspera *Fila)
{
    if (Fila == NULL)
    {
        printf("Fila ja esta vazia\n");
    }
    else if (Fila->prox == NULL)
    {
        printf("Fila ja esta vazia\n");
    }
    else
    {
        FilaEspera *tmp = Fila->prox;
        Fila->prox = tmp->prox;
        return tmp;
    }
    return NULL;
}

/*  ------Lista------    */

//cria lista de livro na lista
ListaLivros *CriarLivro(char *LivroNome, int Cod)
{
    int i;
    ListaLivros *Resultado = (ListaLivros *)malloc(sizeof(ListaLivros));
    strcpy(Resultado->Nome, LivroNome);
    Resultado->Codigo = Cod;
    Resultado->Disponivel = 1;
    Resultado->prox = NULL;
    return Resultado;
}

//insere na lista de livro da lista
ListaLivros *InserirLivro(Livro *AnalLivro, ListaLivros *Temp)
{
    Temp->prox = AnalLivro;
    AnalLivro = Temp;
    return Temp;
}

//busca na lista o livro
Livro *BuscarLivro(Livro *AnalLivro, char *NomeLivro)
{
    Livro *Temp = AnalLivro;
    while (Temp != NULL)
    {
        //se a lista for encontrada retorna o valor da lista

        if (strcmp(Temp->Nome, NomeLivro) == 0)
            return Temp;
        Temp = Temp->prox;
    }
    return NULL;
}

/*  ---------MENU---------   */

void Menu(ListaLivros *Livro, PilhaUsuario *PilhaLivros)
{
    ListaLivros *Temp = Livro;
    int Selecionar;
    char NomeLivro[TAM];

    printf("Selecionar\n1 - Solicitar livro\n2 - Devolver livro\n3 - Sair\nSelecionar: ");
    scanf("%d", &Selecionar);

    switch (Selecionar)
    {
    case 1: //Solicitar livro
        printf("Digite o nome do livro: ");
        getchar();
        scanf("%[A-Z a-z]", &NomeLivro);
        Temp = BuscarLivro(Livro, NomeLivro);
        if (Temp == NULL)
        {
            printf("Livro inexistente");
            exit(1);
        }

        if (Temp->Disponivel)
        {
            //ir em uma pilha de emprestimo de livros daquele usuário.(Pilha)
            InserirPilha(PilhaLivros, Temp->Nome);
            printf("Pegou o livro");
            Temp->Disponivel = 0;
        }
        else
        {
            //Entrar na fila de espera de usuário daquele livro.(Fila)
            InsereFila(Temp->Fila);
            printf("Livro Oculpado, entrou na fila de espera");
        }
        break;

    case 2: //Devolver livro
        //remover da pilha do usuario.
        printf("Digite o nome do livro: ");
        getchar();
        scanf("%[A-Z a-z]", &NomeLivro);
        Temp = BuscarLivro(Livro, NomeLivro);
        if (Temp == NULL)
        {
            printf("Livro inexistente");
            exit(1);
        }

        PilhaLivros = RemovePilha(PilhaLivros);
        if (Temp->Fila != NULL)
        {
            //devera ser entregado para o primeiro usuário da fila de espera.
            Temp->Fila = RemoveFila(Temp->Fila);
            printf("Livro devolvido!!\nLivro foi entregue para o(a) %s", Temp->Fila->NomeUsuario);
            InserirPilha(PilhaLivros, Temp->Nome);
        }
        else
        {
            //mudar o status do livro para disponivel.
            Temp->Disponivel = 1;
            printf("Livro devolvido!!");
        }

        break;

    case 3: //sair
        exit(1);
        break;
    default:
        printf("Invalido!!");
        break;
    }
}

void InsirirLivroBiblioteca(ListaLivros **Livro, ListaLivros **Temp, char *String)
{
    *Temp = CriarLivro(String, QtdLivros++);
    *Livro = InserirLivro(*Livro, *Temp);
}

int main()
{
    int Selecionar;
    PilhaUsuario *PilhaLivros = (PilhaUsuario *)malloc(sizeof(PilhaUsuario));
    ListaLivros *Livro = NULL;
    ListaLivros *Temp;

    InsirirLivroBiblioteca(&Livro, &Temp, (char *)"Codigo Limpo");
    //Faz com que a fila funcione
    Livro->Fila = (FilaEspera *)malloc(sizeof(FilaEspera));
    Livro->Fila->prox = NULL;

    InsirirLivroBiblioteca(&Livro, &Temp, (char *)"Codigo Fonte");
    //Faz com que a fila funcione
    Livro->Fila = (FilaEspera *)malloc(sizeof(FilaEspera));
    Livro->Fila->prox = NULL;

    InsirirLivroBiblioteca(&Livro, &Temp, (char *)"Livro");
    //Faz com que a fila funcione
    Livro->Fila = (FilaEspera *)malloc(sizeof(FilaEspera));
    Livro->Fila->prox = NULL;
    do
    {
        Menu(Livro, PilhaLivros);
        printf("\nFazer Novamente?\n\t1 - Sim\n\tOutro - Não\nSelecionar: ");
        scanf("%d", &Selecionar);
    } while (Selecionar == 1);
}