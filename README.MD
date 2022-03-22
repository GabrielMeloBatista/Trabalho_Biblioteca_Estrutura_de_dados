## O que foi Feito:
Usuário poder solicitar livros.
Sistema analisa se o livro esta diponivel.(Lista)
    Caso diponivel:
        ir em uma pilha de emprestimo de livros daquele usuário.(Pilha)
        mudar o status do livro para indisponivel.
    Caso indisponivel:
        Entrar na fila de espera de usuário daquele livro.(Fila)
Quando o livro ser devolvido
    Caso exista fila de espera de usuário:
        devera ser entregado para o primeiro usuário da fila de espera.
    caso não exista:
        mudar o status do livro para disponivel.

Nas informações do empréstimo do livro, deverá conter o código do livro, quantos dias de empréstimo.
Quando o usuário for devolver os livros, deverão ser devolvidos conforme a ordem da pilha. 
