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
} usuario;

//Fila de espera por livro.
typedef struct FilaEspera
{
	char NomeUsuario[TAM];
	int Tam;
	struct FilaEspera *prox;
} Livros;

//Lista de livros
struct Livro
{
	char Nome[TAM];
	int Disponivel;
	int Codigo;
	char Locatario[TAM];
	Livros *Fila;
	struct Livro *prox;
};

int FilaEsperaVazia(Livros *Fila)
{
	if (Fila->prox == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Livros *AlocaFilaEspera(Livro *StatusLivro)
{
	Livros *Novo = (Livros *)malloc(sizeof(Livros));
	if (!Novo)
	{
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
	{
		strcpy(Novo->NomeUsuario, StatusLivro->Locatario);
		Novo->Tam = 1;
		Novo->prox = NULL;
		return Novo;
	}
}

void InsereFilaEspera(Livros *Fila, Livro *StatusLivro)
{
	Livros *Novo = AlocaFilaEspera(StatusLivro);
	Novo->prox = NULL;

	if (FilaEsperaVazia(Fila))
	{
		Fila = Novo;
	}
	else
	{
		Livros *tmp = Fila;

		while (tmp->prox != NULL)
		{
			tmp = tmp->prox;
		}
		tmp->prox = Novo;
	}
	Fila->Tam++;
}

Livros *RetiraFilaEspera(Livros *Fila)
{
	if (Fila->prox == NULL)
	{
		printf("Fila ja esta vazia\n");
		return NULL;
	}
	else
	{
		Livros *tmp = Fila->prox;
		Fila->prox = tmp->prox;
		Fila->Tam--;
		return tmp;
	}
}

void LiberaFilaEspera(Livros *Fila)
{
	if (Fila->prox != NULL)
	{
		Livros *ProxLivros, *Atual;

		Atual = Fila->prox;
		while (Atual != NULL)
		{
			ProxLivros = Atual->prox;
			free(Atual);
			Atual = ProxLivros;
		}
	}
}

usuario *AlocaCodigo(int cod)
{
	usuario *Novo = (usuario *)malloc(sizeof(usuario));
	if (!Novo)
	{
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
	{
		Novo->CodigoLivro = cod;
		return Novo;
	}
}

//cria lista de livro na lista
Livro *CriarLivro(char *LivroNome, int Cod)
{
	int i;
	Livro *Resultado = (Livro *)malloc(sizeof(Livro));
	strcpy(Resultado->Nome, LivroNome);
	Resultado->Codigo = Cod;
	Resultado->Disponivel = 1;
	Resultado->prox = NULL;
	return Resultado;
}

//insere na lista de livro da lista
Livro *InserirLivro(Livro *AnalLivro, Livro *Temp)
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

//Buscar usuario

Livro *busca_r(char *x, Livro *le)
{
	if (le == NULL)
		return NULL;
	if (strcmp(x, le->Locatario))
		return le;
	return busca_r(x, le->prox);
}

//Solicita Livros, para certo usuario.
void *SolicitarLivro(Livro *AnalLivro, EmprestimoLivro *PilhaUsuario)
{
	Livro *StatusLivro = AnalLivro;
	Livro *Temp;
	EmprestimoLivro *Emprestimo = PilhaUsuario;
	char NomeLivro[TAM];
	char NomeUsuario[TAM];

	strcpy(NomeUsuario, StatusLivro->Locatario);

	if (StatusLivro->Disponivel)
	{
		Emprestimo = AlocaCodigo(AnalLivro->Disponivel);
		StatusLivro->Disponivel = 0;
		printf("Pegou o livro");
	}
	else
	{
		strcpy(StatusLivro->Fila->NomeUsuario, NomeUsuario);
		printf("Livro ocupado");
	}
	return 0;
}

//incompleto falta entregar o Livros conforme a ordem da pilha. //devolve livro, de certo usuario.
void *DevolverLivro(Livro *AnalLivro, EmprestimoLivro *PilhaUsuario)
{
	Livro *StatusLivro = AnalLivro;
	EmprestimoLivro *Emprestimo = PilhaUsuario;
	char EntregarLivro[TAM];
	int i;

	if (StatusLivro->Fila != NULL)
	{
		//devera ser entregado para o primeiro usuário da Fila de espera.
		strcpy(EntregarLivro, StatusLivro->Fila->NomeUsuario);
		StatusLivro->Fila = StatusLivro->Fila->prox;
		printf("Devolveu e foi para o proximo da fila, %s", StatusLivro->Fila->NomeUsuario);
	}
	else
	{
		//definir o status do livro para Disponivelonivel.
		StatusLivro->Disponivel = 1;
		printf("Devolveu e esta disponivel");
	}
	RetiraFilaEspera(StatusLivro->Fila);
	return 0;
}

void Opcoes(Livro *ListaLivros, Livro *Temp)
{
	Temp = ListaLivros;
	usuario *Usuario;
	int Selecionar;
	char NomeLivro[TAM];
	char NomeUsuario[TAM];

	// getchar();
	// scanf("%[A-Z a-z]", &ListaLivros->Locatario);
	printf("Insira o nome de usuario: ");
	scanf("%[A-Z a-z]", NomeUsuario);

	printf("\n1 - Criar usuario\n2 - Procurar usuario\n");
	scanf("%d", &Selecionar);
	switch (Selecionar)
	{
	case 1:
		strcpy(ListaLivros->Locatario, NomeUsuario);
		InsereFilaEspera(ListaLivros->Fila, ListaLivros);
		break;

	default:
		busca_r(NomeUsuario, Temp);
		break;
	}

	printf("\n1 - Solicitar livro\n2 - Devolver livro\nOpcao: ");
	scanf("%i", &Selecionar);
	switch (Selecionar)
	{
		//solicitar o livro.
	case 1:
		printf("Digite o Nome do livro: ");
		getchar();
		scanf("%[A-Z a-z]", &NomeLivro);
		Temp = BuscarLivro(ListaLivros, NomeLivro);
		SolicitarLivro(Temp, Usuario);
		break;

	//devolver livro.
	//não está funcional ainda.
	case 2:
		// printf("Digite o Nome do livro: ");
		// getchar();
		// scanf("%[A-Z a-z]", &NomeLivro);
		// Temp = BuscarLivro(ListaLivros, NomeLivro);
		DevolverLivro(Temp, Usuario);
		break;

	default:
		break;
	}
	printf("\nTentar Novamente?\n1 - Sim\n2 - Não\n");
	scanf("%i", &Selecionar);
	switch (Selecionar)
	{
	case 1:
		Opcoes(ListaLivros, Temp);
		break;

	default:
		break;
	}
}

void Menu()
{
	typedef Livro bib;
	bib *ListaLivros = NULL;
	bib *Temp = CriarLivro((char *)"Codigo Limpo", 001);

	ListaLivros = InserirLivro(ListaLivros, Temp);

	//selecionar usuario
	ListaLivros->Fila = (Livros *)malloc(sizeof(Livros));
	ListaLivros->Fila->prox = NULL;

	Opcoes(ListaLivros, Temp);
}

int main()
{
	Menu();

	return 0;
}