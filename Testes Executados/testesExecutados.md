# Relatório de Testes - Projeto Matrizes Esparsas


| **ID** | **Funcionalidade**             | **Entrada/Comando**                                 | **Resultado Esperado**                                                                 | **Resultado Obtido**                | **Status** |
|--------|--------------------------------|-----------------------------------------------------|----------------------------------------------------------------------------------------|-------------------------------------|------------|
| TC001  | Criação da Matriz              | `create 5 5`                                        | Nova matriz esparsa de 5x5 criada com sucesso                                          | Matriz criada conforme esperado     | Sucesso    |
| TC002  | Inserção de Elemento           | `update 0 1 1 5.0`                                    | Elemento 5.0 inserido na posição (1,1)                                                 | Elemento inserido com sucesso       | Sucesso    |
| TC003  | Recuperação de Elemento        | Chamada ao método `get(1,1)`                        | Valor 5.0 retornado                                                                    | Valor retornado corretamente        | Sucesso    |
| TC004  | Impressão da Matriz            | `show 0`                                            | Exibição da matriz com os elementos inseridos e zeros para posições não definidas        | Matriz exibida conforme esperado    | Sucesso    |
| TC005  | Soma de Matrizes               | `sum 0 1` (matrizes de índices 0 e 1)                | Matriz resultante com a soma elemento a elemento das duas matrizes                     | Soma realizada corretamente         | Sucesso    |
| TC006  | Multiplicação de Matrizes      | `multiply 0 1` (matrizes com dimensões compatíveis)  | Matriz resultante com a multiplicação das matrizes                                     | Multiplicação realizada corretamente| Sucesso    |
| TC007  | Leitura de Arquivo             | `read mtx.txt`                                      | Matriz carregada a partir do arquivo "mtx.txt"; dados importados conforme o conteúdo do arquivo | Dados importados conforme esperado  | Sucesso/Erro* |
| TC008  | Limpeza de Matriz              | `clear 0`                                           | Matriz do índice 0 limpa, removendo todos os elementos armazenados                     | Matriz limpa conforme esperado      | Sucesso    |
| TC009  | Apagar Todas as Matrizes       | `erase`                                             | Todas as matrizes removidas e memória liberada                                         | Operação realizada com sucesso      | Sucesso    |
| TC010  | Comando de Ajuda               | `help`                                              | Exibição de um painel de ajuda com a listagem de comandos e suas funções                 | Painel de ajuda exibido             | Sucesso    |
| TC011  | Encerramento do Programa       | `exit`                                              | Programa finalizado sem erros                                                          | Programa encerrado                  | Sucesso    |

## Algumas imagens de saídas dos testes:
![TC001](image.png)
![TC002](image-1.png)
![TC003](image-2.png)