## O que foi Feito:
Usuário poder solicitar livros.<br>
Sistema analisa se o livro esta diponivel.(Lista)<br>
    Caso diponivel:<br>
        ir em uma pilha de emprestimo de livros daquele usuário.(Pilha)<br>
        mudar o status do livro para indisponivel.<br>
    Caso indisponivel:<br>
        Entrar na fila de espera de usuário daquele livro.(Fila)<br>
Quando o livro ser devolvido<br>
    Caso exista fila de espera de usuário:<br>
        devera ser entregado para o primeiro usuário da fila de espera.<br>
    caso não exista:<br>
        mudar o status do livro para disponivel.<br>

Nas informações do empréstimo do livro, deverá conter o código do livro, quantos dias de empréstimo.<br>
Quando o usuário for devolver os livros, deverão ser devolvidos conforme a ordem da pilha. 
