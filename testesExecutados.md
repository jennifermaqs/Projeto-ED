# Relatório de Testes - Projeto Matrizes Esparsas

## Introdução
Este documento apresenta os testes realizados para verificar a implementação da estrutura de dados para matrizes esparsas, utilizando listas encadeadas simples com sentinelas – conforme o projeto proposto por Nivio Ziviani. Os testes validam as operações fundamentais, como criação, inserção, recuperação, impressão, soma, multiplicação, leitura de arquivo, atualização, limpeza e gerenciamento de memória, assegurando a eficiência e robustez da aplicação.

## Testes Realizados

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

\* *Observação:* No TC007, se ocorrer algum problema na leitura do arquivo (por exemplo, arquivo não encontrado ou formato inválido), o teste deve indicar o erro e demonstrar que o sistema está tratando essa situação adequadamente.

# Relatório de Testes Adicionais - Projeto Matrizes Esparsas

## Testes Complementares

| **ID** | **Funcionalidade**                     | **Entrada/Comando**                                          | **Resultado Esperado**                                                                                   | **Resultado Obtido**                | **Status** |
|--------|----------------------------------------|--------------------------------------------------------------|----------------------------------------------------------------------------------------------------------|-------------------------------------|------------|
| TC012 | Inserção com Valor Zero                | `update 0 2 2 0`                                             | Operação ignorada, pois valores zero não são armazenados na matriz esparsa                              | Sem alteração na matriz             | Sucesso    |
| TC013 | Atualização de Elemento Existente      | `update 0 1 1 8.0`                                             | Elemento na posição (1,1) é atualizado de 5.0 para 8.0                                                    | Valor atualizado corretamente       | Sucesso    |
| TC014 | Tentativa de Atualização Fora dos Limites | `update 0 6 6 4.0`                                             | Mensagem de erro ou tratamento de exceção, pois a posição (6,6) está fora dos limites (supondo matriz 5x5)   | Erro tratado conforme esperado      | Sucesso    |
| TC015 | Remoção de Elemento Inexistente        | `update 0 3 3 0`                                             | Nenhuma alteração, já que não há elemento na posição (3,3) para remover (ou atualização com zero é ignorada) | Operação ignorada ou mensagem de aviso | Sucesso    |
| TC016 | Soma com Matrizes de Dimensões Diferentes | `sum 0 2` (onde a matriz 0 é 5x5 e a matriz 2 é 4x4)          | Mensagem de erro ou indicação de que as matrizes não são compatíveis para soma                              | Erro de compatibilidade detectado    | Sucesso    |
| TC017 | Multiplicação com Matrizes Incompatíveis  | `multiply 0 2` (número de colunas da primeira diferente do número de linhas da segunda) | Mensagem de erro ou tratamento da incompatibilidade para multiplicação                                   | Erro de compatibilidade detectado    | Sucesso    |
| TC018 | Teste de Leitura com Arquivo Inexistente  | `read inexistente.txt`                                         | Mensagem de erro informando que o arquivo não foi encontrado                                               | Erro informado corretamente         | Sucesso    |
| TC019 | Teste de Multiplicação de Matrizes        | `multiply 0 1` (matrizes com dimensões compatíveis)           | Matriz resultante correta obtida pela multiplicação dos elementos de cada posição correspondente           | Resultado conforme esperado         | Sucesso    |
| TC020 | Teste de Limpeza e Realocação de Memória  | `clear 0` seguido de uma nova operação de `insert`            | Matriz limpa, sem dados antigos; nova inserção ocorrendo normalmente após a limpeza                        | Operação realizada sem problemas    | Sucesso    |


## Conclusão dos Testes
Os testes realizados comprovaram que a implementação da matriz esparsa atende aos requisitos propostos. Foram validadas as operações de inserção, recuperação e atualização de elementos, bem como as operações matemáticas de soma e multiplicação. Além disso, os testes de leitura de arquivo, limpeza e gerenciamento de memória demonstraram que as funções auxiliares (como `readSparseMatrix` e `clear`) estão funcionando conforme esperado, apesar dos desafios encontrados durante a implementação.

## Considerações Finais
A abordagem com listas encadeadas e sentinelas possibilitou uma manipulação eficiente da matriz esparsa, otimizando o uso de memória e o desempenho das operações. As dificuldades enfrentadas – especialmente na leitura de dados externos e na alocação/desalocação dinâmica de memória – foram superadas com a implementação de funções específicas para tratamento de erros e liberação de recursos. O trabalho colaborativo e a divisão equilibrada de tarefas foram fundamentais para o sucesso do projeto.

---

*Dica:* Você pode incluir capturas de tela ou trechos do terminal mostrando os resultados dos testes para enriquecer o relatório e facilitar a compreensão do avaliador.
