# MD2 (Message Digest 2):

O algoritmo de hash MD2 (Message Digest 2) é uma função criptográfica de hash desenvolvida por Ronald Rivest em 1989. É considerada uma das primeiras iterações da família MD, que inclui também o MD4, MD5 e MD6. No entanto, devido a algumas fraquezas de segurança, o MD2 não é mais amplamente usado e foi considerado obsoleto.

O MD2 (Message Digest 2) é projetado para produzir um valor hash de 128 bits (16 bytes) para uma entrada de tamanho arbitrário. Ele opera em blocos de 16 bytes e faz uso de várias tabelas de substituição predefinidas. O algoritmo executa uma série de transformações em cada bloco de dados, incluindo permutações, operações de substituição e deslocamentos bitwise.

Uma das principais fraquezas do MD2 (Message Digest 2) é sua vulnerabilidade à colisão e pré-imagem. Colisão ocorre quando duas entradas diferentes produzem o mesmo valor hash, enquanto pré-imagem se refere à capacidade de encontrar uma entrada específica para um determinado hash. Essas vulnerabilidades foram exploradas e demonstradas por ataques práticos, tornando o MD2 inadequado para aplicações que requerem segurança robusta.

Devido a essas fraquezas, o MD2 (Message Digest 2) foi amplamente substituído por algoritmos de hash mais seguros, como o SHA-1 (Secure Hash Algorithm 1) e posteriormente o SHA-256 (Secure Hash Algorithm 256 bits). Esses algoritmos são amplamente usados em aplicações criptográficas modernas, como assinaturas digitais e autenticação de dados.

Em resumo, o MD2 (Message Digest 2) foi um algoritmo de hash desenvolvido na década de 1980, mas suas vulnerabilidades de segurança levaram à sua obsolescência. É recomendado utilizar algoritmos de hash mais modernos e seguros, como os da família SHA.

# Funcionamento:

O algoritmo MD2 opera em blocos de 16 bytes e produz um resumo de 128 bits (16 bytes) para uma mensagem de entrada de comprimento arbitrário. Abaixo está um pseudocódigo básico que descreve o funcionamento do algoritmo MD2:

1. Inicializar as variáveis de estado:
   - state[0..255]: uma matriz de 256 bytes.
   - checksum[0..15]: uma matriz de 16 bytes para o valor do checksum.
   - buffer[0..15]: uma matriz de 16 bytes para armazenar os blocos de entrada.

2. Preparar a mensagem de entrada:
   - Adicionar preenchimento (padding) ao final da mensagem para garantir que tenha um comprimento múltiplo de 16 bytes. Se a mensagem já tiver um comprimento múltiplo de 16, adicionar um bloco adicional de 16 bytes preenchidos com o valor 16.

3. Processar os blocos da mensagem:
   - Para cada bloco de 16 bytes na mensagem:
   - Copiar o bloco para o buffer.
   - Atualizar o estado utilizando o buffer e o estado atual.

4. Finalizar o cálculo do resumo:
   - Adicionar o valor do checksum ao estado.
   - Atualizar o estado utilizando o valor do checksum e o estado atual.

5. Obter o resumo final:
   - O resumo final é composto pelos primeiros 16 bytes do estado.

É importante destacar que esse pseudocódigo é uma versão simplificada e não leva em consideração certos detalhes técnicos. Além disso, como o MD2 foi considerado inseguro devido a vulnerabilidades conhecidas, não é recomendado utilizá-lo em aplicações modernas que exigem alta segurança criptográfica. Recomenda-se o uso de algoritmos mais recentes e seguros, como SHA-256 ou SHA-3.

# implementação:

Vou explicar detalhadamente o algoritmo de hash MD2 implementado em C.

O algoritmo MD2 é um algoritmo de hash criptográfico que gera um valor hash de 128 bits (16 bytes) para uma determinada mensagem de entrada. Aqui está uma explicação passo a passo do código fornecido:

1. Primeiro, são incluídas as bibliotecas necessárias para o programa: `<stdio.h>` para entrada e saída, `<stdlib.h>` para alocação de memória, e `<string.h>` para manipulação de strings e memória.

2. São definidas algumas constantes relacionadas ao algoritmo MD2:
   - `MD2_BLOCK_SIZE` define o tamanho do bloco de entrada em bytes, que é 16 bytes (128 bits) para o MD2.
   - `MD2_DIGEST_SIZE` define o tamanho do hash de saída em bytes, que também é 16 bytes para o MD2.

3. Em seguida, é declarada a estrutura `MD2_CTX`, que representa o estado interno do algoritmo MD2. Ela contém os seguintes campos:
   - `state[48]`: o estado interno do algoritmo MD2.
   - `checksum[16]`: um checksum utilizado durante o processamento.
   - `buffer[16]`: um buffer para armazenar os blocos de entrada.
   - `digest[16]`: o valor hash MD2 final.

4. A matriz `sbox` é declarada. Ela é uma tabela de substituição de 256 bytes utilizada durante a transformação do algoritmo MD2.

5. A função `md2_transform` é definida. Ela executa a transformação principal do algoritmo MD2. Essa função é chamada internamente pelo algoritmo MD2 para processar os blocos de entrada. Ela recebe como argumento um ponteiro para a estrutura `MD2_CTX` que contém o estado atual do algoritmo.

6. A função `md2_init` é definida. Ela inicializa a estrutura `MD2_CTX` com valores iniciais, zerando todos os campos.

7. A função `md2_update` é definida. Ela é responsável por atualizar o estado interno do algoritmo MD2 com os blocos de entrada fornecidos. Ela recebe como argumento o ponteiro para a estrutura `MD2_CTX`, um ponteiro para os dados de entrada (`data`) e o tamanho dos dados de entrada (`length`).

8. A função `md2_final` é definida. Ela é chamada para finalizar o processamento do algoritmo MD2, executando as últimas transformações e gerando o valor hash MD2 final. Ela recebe como argumento o ponteiro para a estrutura `MD2_CTX`.

9. A função `md2` é definida. Ela é a função principal que realiza o cálculo do hash MD2 para uma mensagem de entrada. Ela recebe como argumentos um ponteiro para os dados de entrada (`message`), o tamanho dos dados de entrada (`length`) e um ponteiro para o buffer que irá armazenar o hash MD2 gerado (`digest`).

10. A função `main` é definida. Ela é a função principal do programa. Nela, o usuário é solicitado a digitar a mensagem de entrada.

11. A função `fgets` é usada para ler a mensagem digitada pelo

 usuário e armazená-la na variável `message`. É importante notar que o tamanho máximo da mensagem é limitado a 256 caracteres.

12. O comprimento da mensagem é verificado e, se houver uma quebra de linha no final, ela é removida.

13. A função `md2_init` é chamada para inicializar a estrutura `MD2_CTX` com valores iniciais.

14. A função `md2_update` é chamada para processar os dados de entrada fornecidos pela mensagem.

15. A função `md2_final` é chamada para finalizar o cálculo do hash MD2 e gerar o valor de hash final.

16. O hash MD2 é exibido na tela, convertido em formato hexadecimal.

17. O programa é encerrado com o valor de retorno 0.

Espero que esta explicação detalhada ajude a compreender o funcionamento do algoritmo de hash MD2 implementado em C. Se tiver mais dúvidas, sinta-se à vontade para perguntar.
