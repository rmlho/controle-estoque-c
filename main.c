//gcc main.c -o main && ./main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 200
#define MAX_CATEGORIAS 6
#define MAX_CODIGO 9999

struct Produto {
    int codigo;
    char nome[100];
    int categoria;
    int quantDisponivel;
    int quantMinima;
    float valorUnitario;
    int situacao;
};

/* NOTA: codigo usa 4 digitos inteiros
categoria de 1 a 6  
 1. Materia de escritório
 2. Material de limpeza
 3. Equipamentos
 4. Componentes eletrônicos
 5. Ferramentas
 6. Acessórios

e a situacao tambem em inteiros 

 1. ATIVO
 2. INDISPONIVEL
 3. DESCONTINUADO
*/

//Cabeçalho das funções do sistema {

//Funções de menu do sistema:
void exibirMenu(void);
void exibirMenuRelatorios(void);
void menuRelatorios(struct Produto estoque[], int total);

//Funções de cadastro, alteração e exclusão:
void cadastrarProduto(struct Produto estoque[], int *total);
void alterarProduto(struct Produto estoque[], int total);
void excluirProduto(struct Produto estoque[], int *total);
void codigoExiste(struct Produto estoque[], int total);
int buscarIndicePorCodigo(struct Produto estoque[], int total, int codigo);

//Funções de entrada/saída:
void registrarEntrada(struct Produto estoque[], int total);
void registrarSaida(struct Produto estoque[], int total);

//Funções de consulta do sistema:
void consultarPorNome(struct Produto estoque[], int total);
void consultarPorCategoria(struct Produto estoque[], int total);
void consultarPorSituacao(struct Produto estoque[], int total);
void listarTodos(struct Produto estoque[], int total);
void listarAbaixoDoMinimo(struct Produto estoque[], int total);
void listarSemEstoque(struct Produto estoque[], int total);

//Funções de ordenação do sistema:
void ordenarPorNome(struct Produto estoque[], int total);
void ordenarPorQuantidade(struct Produto estoque[], int total);
void ordenarPorValor(struct Produto estoque[], int total);

//Funções de pesistência de dados:
void salvarDados(struct Produto estoque[], int total);
void carregarDados(struct Produto estoque[], int *total);

//Funções de relatórios do sistema:
void relatorioGeral(struct Produto estoque[], int total);
void relatorioValorPorProduto(struct Produto estoque[], int total);
void relatorioValorTotalEstoque(struct Produto estoque[], int total);
void relatorioMaiorValorUnitario(struct Produto estoque[], int total);
void relatorioMaiorValorArmazenado(struct Produto estoque[], int total);
void relatorioPorCategoria(struct Produto estoque[], int total);

//Funções de validação do sistema:
int validarNome(char nome[]);
int validarCodigo(int codigo);
int validarProdutoAtivo(int situacao);
int validarValorUnitario(float valorUnitario);
int validarCategoria(int categoria);
int validarQuantidadeMinima(int quantMinima);
int validarQuantidadeInicial(int quantDisponivel);
int validarExclusao(int quantDisponivel);
int validarLimiteProdutos(int total);
int validarQuantidadeOperacao(int quantDisponivel);
int validarEstoqueSuficiente(int quantDisponivel, int quantSaida);

// }

int main(void) {
    struct Produto estoque[MAX_PRODUTOS];
    int total = 0;
    int opcao = 0;

    carregarDados(estoque, &total);

    while (opcao != 16) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                cadastrarProduto(estoque, &total);
                break;

            case 2:
                codigoExiste(estoque, total);
                break;

            case 3:
                consultarPorNome(estoque, total);
                break;

            case 4:
                consultarPorCategoria(estoque, total);
                break;

            case 5:
                listarTodos(estoque, total);
                break;

            case 6:
                alterarProduto(estoque, total);
                break;

            case 7:
                excluirProduto(estoque, &total);
                break;

            case 8:
                registrarEntrada(estoque, total);
                break;

            case 9:
                registrarSaida(estoque, total);
                break;

            case 10:
                listarAbaixoDoMinimo(estoque, total);
                break;

            case 11:
                listarSemEstoque(estoque, total);
                break;

            case 12:
                consultarPorSituacao(estoque, total);
                break;

            case 13:
                menuRelatorios(estoque, total);
                break;

            case 14:
                salvarDados(estoque, total);
                break;

            case 15:
                carregarDados(estoque, &total);
                break;

            case 16:
                salvarDados(estoque, total);
                return 0;

            default:
                printf("Insira uma opção entre 1 e 16!\n");
                break;
        }
    }


    return 0;
}

void exibirMenu(void) {
    printf("\n");
    printf("------------ Controle de Estoque ------------");
    printf("\n[1] Cadastrar produto");
    printf("\n[2] Consultar produto pelo código");
    printf("\n[3] Consultar produto pelo nome");
    printf("\n[4] Consultar produtos por categoria");
    printf("\n[5] Listar todos os produtos");
    printf("\n[6] Alterar dados de um produto");
    printf("\n[7] Excluir ou descontinuar um produto");
    printf("\n[8] Registrar entrada");
    printf("\n[9] Registrar saída");
    printf("\n[10] Consultar produtos com estoque abaixo do mínimo");
    printf("\n[11] Consultar produtos sem estoque");
    printf("\n[12] Consultar produtos temporariamente indisponíveis");
    printf("\n[13] Apresentar relatórios");
    printf("\n[14] Salvar as informações");
    printf("\n[15] Recuperar as informações armazenadas anteriormente");
    printf("\n[16] Encerrar o sistema\n");
    printf("\n");
}

void exibirMenuRelatorios(void) {
    printf("-=-=-=-=-=-= Relatorios -=-=-=-=-=-=\n");
    printf("[0] Voltar ao menu\n");
    printf("[1] Relatório geral\n");
    printf("[2] Relatório de produtos com estoque abaixo do mínimo\n");
    printf("[3] Relatório produto sem estoque\n");
    printf("[4] Relatório por nome\n");
    printf("[5] Relatório por quantidade\n");
    printf("[6] Relatorio por valor\n");
    printf("[7] Relatório por produto e valor\n");
    printf("[8] Valor total do estoque\n");
    printf("[9] Maior valor unitário\n");
    printf("[10] Maior valor armazenado\n");
    printf("[11] Relatório por categoria\n");
    printf("\n");
}

void menuRelatorios(struct Produto estoque[], int total) {
    int opcao = 1;

    while (opcao != 0) {
        exibirMenuRelatorios();
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                break;

            case 1:
                relatorioGeral(estoque, total);
                break;
                
            case 2:
                listarAbaixoDoMinimo(estoque, total);
                break;

            case 3:
                listarSemEstoque(estoque, total);
                break;

            case 4:
                ordenarPorNome(estoque, total);
                break;

            case 5:
                ordenarPorQuantidade(estoque, total);
                break;

            case 6:
                ordenarPorValor(estoque, total);
                break;

            case 7:
                relatorioValorPorProduto(estoque, total);
                break;

            case 8:
                relatorioValorTotalEstoque(estoque, total);
                break;

            case 9:
                relatorioMaiorValorUnitario(estoque, total);
                break;

            case 10:
                relatorioMaiorValorArmazenado(estoque, total);
                break;

            case 11:
                relatorioPorCategoria(estoque, total);
                break;

            default:
                printf("Opção inválida");
                break;
        }
    }    
}

int validarNome(char nome[]) {
    if (nome == NULL) {
        return 0;
    }

    for (int i = 0; nome[i] != '\0'; i++) {
        if (isalpha(nome[i])) { 
            return 1; 
        }
    }
  
    return 0; 
}

int validarCodigo(int codigo) {
    if (codigo < 1000 || codigo > MAX_CODIGO) {
        return 0;
    }

    return 1;
}

int validarValorUnitario(float valorUnitario) {
    if (valorUnitario > 0) {
        return 1;
    }

    return 0;
}

int validarProdutoAtivo(int situacao) {
    if (situacao == 1) {
        return 1;
    }

    return 0;
}

int validarCategoria(int categoria) {
    if (categoria > 0 && categoria <= MAX_CATEGORIAS) {
        return 1;
    }

    return 0;
}

int validarQuantidadeMinima(int quantMinima) {
    if (quantMinima < 0) {
        return 0;
    }

    return 1;
}

int validarQuantidadeInicial(int quantDisponivel) {
    if (quantDisponivel < 0) {
        return 0;
    }

    return 1;
}

int validarExclusao(int quantDisponivel) {
    if (quantDisponivel == 0) {
        return 1;
    }

    return 0;
}

int validarLimiteProdutos(int total) {
    if (total >= MAX_PRODUTOS) {
        return 0;
    }

    return 1;
}

int validarQuantidadeOperacao(int quantDisponivel) {
    if (quantDisponivel > 0) {
        return 1;
    }
    return 0;
}

int validarEstoqueSuficiente(int quantDisponivel, int quantSaida) {
    if (quantSaida > quantDisponivel) {
        return 0;
    }

    return 1;
}

void cadastrarProduto(struct Produto estoque[], int *total) {

    if (!validarLimiteProdutos(*total)) {
        printf("Erro: limite de %d produtos atingido!\n", MAX_PRODUTOS);
        return;
    }

    int codigo;
    char nome[100];
    int categoria;
    int quantDisponivel;
    int quantMinima;
    float valorUnitario;
    
    printf("--- CADASTRO DE PRODUTO ---\n");
    printf("Categorias: 1. Material de escritorio; 2. Material de limpeza; 3. Equipamentos; 4. Componentes eletrônicos; 5. Ferramentas; 6. Acessórios\n");
    printf("\n");

    printf("Codigo de 4 digitos: ");
    scanf("%d", &codigo);
    while (getchar() != '\n');

    if (!validarCodigo(codigo)) {
        printf("Erro: coódigo deve ter 4 digitos!\n");
        return;
    } 

    if (buscarIndicePorCodigo(estoque, *total, codigo) != -1) {
        printf("Erro: codigo ja cadastrado!\n");
        return;
    }

    printf("Nome: ");
    fgets(nome, 100, stdin);

    if (!validarNome(nome)) {
        printf("Erro: nome nao pode ser vazio!\n");
        return; // Ou voltar para o menu
    }

    printf("Categoria (codigo numerico): ");
    scanf("%d", &categoria);

    if (!validarCategoria(categoria)) {
        printf("Erro: categoria invalida!\n");
        return;
    }

    printf("Quantidade inicial: ");
    scanf("%d", &quantDisponivel);

    if (!validarQuantidadeInicial(quantDisponivel)) {
        printf("Erro: quantidade inicial nao pode ser negativa!\n");
        return;
    }

    printf("Quantidade minima: ");
    scanf("%d", &quantMinima);

    if (!validarQuantidadeMinima(quantMinima)) {
        printf("Erro: quantidade minima nao pode ser negativa!\n");
        return;
    }

    printf("Valor unitario: ");
    scanf("%f", &valorUnitario);
    while (getchar() != '\n');


    if (!validarValorUnitario(valorUnitario)) {
        printf("Erro: valor unitario deve ser maior que zero!\n");
        return;
    }

    estoque[*total].codigo = codigo;
    strcpy(estoque[*total].nome, nome);
    estoque[*total].categoria = categoria;
    estoque[*total].quantDisponivel = quantDisponivel;
    estoque[*total].quantMinima = quantMinima;
    estoque[*total].valorUnitario = valorUnitario;
    estoque[*total].situacao = 1; // 1 = ativo

    (*total)++;

    printf("\nProduto cadastrado com sucesso!\n\n");
}

int buscarIndicePorCodigo(struct Produto estoque[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void codigoExiste(struct Produto estoque[], int total) {
    int codigo;
    printf("Digite o codigo do produto que deseja buscar:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, total, codigo);

    if (indice != -1) {
        printf("\n--- Produto Encontrado ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Categoria (Cod): %d\n", estoque[indice].categoria);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("Qtd Minima: %d\n", estoque[indice].quantMinima);
        printf("Valor Unitario: R$ %.2f\n", estoque[indice].valorUnitario);

        if (estoque[indice].situacao == 1) {
            printf("Situacao: Ativo\n");
        } else if (estoque[indice].situacao == 2) {
            printf("Situacao: Temporariamente Indisponivel\n");
        } else {
            printf("Situacao: Descontinuado\n");
        }
        printf("--------------------------\n\n");
    } else {
        printf("\nNenhum produto cadastrado com o codigo %d.\n\n", codigo);
    }
}

void alterarProduto(struct Produto estoque[], int total) {
    int codigo;

    printf("Digite o codigo do produto que deseja alterar:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, total, codigo);

    if (indice != -1) {
        printf("\n--- Dados Atuais do Produto ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Categoria (Cod): %d\n", estoque[indice].categoria);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("Qtd Minima: %d\n", estoque[indice].quantMinima);
        printf("Valor Unitario: R$ %.2f\n", estoque[indice].valorUnitario);
        printf("Situacao: %d\n", estoque[indice].situacao);
        printf("-------------------------------\n\n");

        char confirmacao;
        printf("Deseja realmente alterar os dados deste produto? (s/n): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 's' || confirmacao == 'S') {

            char novoNome[100];
            printf("\nDigite o novo nome do produto: ");
            scanf(" %99[^\n]", novoNome);
            if (!validarNome(novoNome)) {
                printf("Erro: nome nao pode ser vazio! Alteracao cancelada.\n");
                return;
            }

            int novaCategoria;
            printf("Informe a nova categoria (Codigo numerico): ");
            scanf("%d", &novaCategoria);
            if (!validarCategoria(novaCategoria)) {
                printf("Erro: categoria invalida! Alteracao cancelada.\n");
                return;
            }

            int novaQuantMinima;
            printf("Informe a nova quantidade minima recomendada: ");
            scanf("%d", &novaQuantMinima);
            if (!validarQuantidadeMinima(novaQuantMinima)) {
                printf("Erro: quantidade minima nao pode ser negativa! Alteracao cancelada.\n");
                return;
            }

            float novoValor;
            printf("Informe o novo valor unitario: R$ ");
            scanf("%f", &novoValor);
            if (!validarValorUnitario(novoValor)) {
                printf("Erro: valor unitario deve ser maior que zero! Alteracao cancelada.\n");
                return;
            }

            int novaSituacao;
            printf("Informe a nova situacao (1-Ativo, 2-Indisponivel, 3-Descontinuado): ");
            scanf("%d", &novaSituacao);
            if (novaSituacao < 1 || novaSituacao > 3) {
                printf("Erro: situacao invalida! Alteracao cancelada.\n");
                return;
            }

            strcpy(estoque[indice].nome, novoNome);
            estoque[indice].categoria = novaCategoria;
            estoque[indice].quantMinima = novaQuantMinima;
            estoque[indice].valorUnitario = novoValor;
            estoque[indice].situacao = novaSituacao;

            printf("\nProduto alterado com sucesso!\n");
        } else {
            printf("\nAlteracao cancelada.\n");
        }
    } else {
        printf("\nNenhum produto encontrado com o codigo %d.\n", codigo);
    }
}

void excluirProduto(struct Produto estoque[], int *total) {
    int codigo;

    printf("Digite o codigo do produto que deseja excluir:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, *total, codigo);

    if (indice != -1) {
        printf("\n--- Dados do Produto ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("------------------------\n\n");

        if (!validarExclusao(estoque[indice].quantDisponivel)) {
            printf("Erro: A exclusao nao pode ser realizada. Ainda existem %d unidades em estoque.\n", estoque[indice].quantDisponivel);
        } else {
            char confirmacao;

            printf("O produto possui 0 unidades em estoque. Deseja realmente exclui-lo definitivamente? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S') {

                for (int i = indice; i < (*total) - 1; i++) {
                    estoque[i] = estoque[i + 1];
                }

                (*total)--;

                printf("\nProduto excluido definitivamente com sucesso!\n");
            } else {
                printf("\nExclusao cancelada.\n");
            }
        }
    } else {
        printf("\nNenhum produto encontrado com o codigo %d.\n", codigo);
    }
}

void listarTodos(struct Produto estoque[], int total) {
    int count = 0;
    int i;

    puts("----------------------------------------\n");
    for (i = 0; i < total; i++) {
        printf("Código - %d\n", estoque[i].codigo);
        printf("Nome - %s\n", estoque[i].nome);
        printf("Categoria - %d\n", estoque[i].categoria);
        printf("Quantidade - %d\n", estoque[i].quantDisponivel);
        printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
        printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
        printf("Situação - %d\n", estoque[i].situacao);
        printf("\n");
        puts("----------------------------------------\n");
        count++;
    }

    if (count == 0) {
        printf("Nenhum produto foi cadastrado\n");
    }
}

void listarAbaixoDoMinimo(struct Produto estoque[], int total) {
    int i;
    int count = 0;

    for (i = 0; i < total; i++) {
        if (estoque[i].quantDisponivel < estoque[i].quantMinima) {
            printf("Código - %d\n", estoque[i].codigo);
            printf("Nome - %s\n", estoque[i].nome);
            printf("Categoria - %d\n", estoque[i].categoria);
            printf("Quantidade - %d\n", estoque[i].quantDisponivel);
            printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
            printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
            printf("Situação - %d\n", estoque[i].situacao);
            puts("----------------------------------------\n");
            count++;
        }
    }

     if (count == 0) {
        printf("Nenhum produto abaixo do mínimo\n");
    }    
}

void listarSemEstoque(struct Produto estoque[], int total) {
    int i;
    int count = 0;

    for (i = 0; i < total; i++) {
        if (estoque[i].quantDisponivel == 0) {
            printf("Código - %d\n", estoque[i].codigo);
            printf("Nome - %s\n", estoque[i].nome);
            printf("Categoria - %d\n", estoque[i].categoria);
            printf("Quantidade - %d\n", estoque[i].quantDisponivel);
            printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
            printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
            printf("Situação - %d\n", estoque[i].situacao);
            puts("----------------------------------------\n");
            count++;
        }
    }

    if (count == 0) {
        printf("Nenhum produto sem estoque\n");
    }
}

void registrarEntrada(struct Produto estoque[], int total) {
    int aux = 0;
    int quantRecebida;
    int indice;
    int codigo;

    printf("\n");
    printf("------------ REGISTRANDO ENTRADA ------------\n");
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);

    indice = buscarIndicePorCodigo(estoque ,total ,codigo);

    if (indice == -1) {
        printf("Produto não existe no estoque!\n");
        return;
    }

    if (!validarProdutoAtivo(estoque[indice].situacao)) {
        printf("Esse produto não está ativo!\n");
        return;
    }

    printf("Informe a quantidade recebida do produto: ");
    scanf("%d", &quantRecebida);

    if (!validarQuantidadeOperacao(quantRecebida)) {
        printf("A quantidade DEVE ser maior que zero!\n");
        return;
    }

    aux = estoque[indice].quantDisponivel;
    estoque[indice].quantDisponivel += quantRecebida;

    printf("\n");
    printf("-------------------------------------------\n");
    printf("\n");
    printf("%s\n", estoque[indice].nome);
    printf("Quantidade anterior: %d\n", aux);
    printf("Quantidade recebida: %d\n", quantRecebida);
    printf("Nova quantidade disponivel: %d\n", estoque[indice].quantDisponivel);
    printf("\n");
}

void registrarSaida(struct Produto estoque[], int total) {
    int aux = 0;
    int quantSaida;
    int indice;
    int codigo;

    printf("\n");
    printf("------------ REGISTRANDO SAIDA ------------\n");
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);

    indice = buscarIndicePorCodigo(estoque ,total ,codigo);

    if (indice == -1) {
        printf("Produto não existe no estoque!\n");
        return;
    }

    if (!validarProdutoAtivo(estoque[indice].situacao)) {
        printf("Esse produto não está ativo!\n");
        return;
    }

    printf("Informe a quantidade de retirada do produto: ");
    scanf("%d", &quantSaida);

    if (!validarQuantidadeOperacao(quantSaida)) {
        printf("A quantidade DEVE ser maior que zero!\n");
        return;
    }

    if (!validarEstoqueSuficiente(estoque[indice].quantDisponivel ,quantSaida)) {
        printf("Quantidade insuficiente para retirada!\n");
        return;
    }

    aux = estoque[indice].quantDisponivel;
    estoque[indice].quantDisponivel -= quantSaida;

    printf("\n");
    printf("-------------------------------------------\n");
    printf("\n");
    printf("%s\n", estoque[indice].nome);
    printf("Quantidade anterior: %d\n", aux);
    printf("Quantidade retirada: %d\n", quantSaida);
    printf("Nova quantidade disponivel: %d\n", estoque[indice].quantDisponivel);
    printf("\n");
}

void ordenarPorNome(struct Produto estoque[], int total) {
    struct Produto copia[MAX_PRODUTOS];

    for (int i = 0; i < total; i++) {
        copia[i] = estoque[i];
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                struct Produto temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < total; i++) {
        printf("%s\n", copia[i].nome);
    }
}

void ordenarPorQuantidade(struct Produto estoque[], int total) {
    struct Produto copia[MAX_PRODUTOS];
    char ordem;

    for (int i = 0; i < total; i++) {
        copia[i] = estoque[i];
    }

    printf("Informe '+' para crescente ou '-' para decrescente: \n");
    scanf(" %c", &ordem);

    if (ordem == '+') {
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (copia[j].quantDisponivel > copia[j + 1].quantDisponivel) {
                    struct Produto temp = copia[j];
                    copia[j] = copia[j + 1];
                    copia[j + 1] = temp;
                }
            }
        }
    } else if (ordem == '-') {
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (copia[j].quantDisponivel < copia[j + 1].quantDisponivel) {
                    struct Produto temp = copia[j];
                    copia[j] = copia[j + 1];
                    copia[j + 1] = temp;
                }
            }
        }
    } else {
        printf("Resposta invalida!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d\n", copia[i].quantDisponivel);
    }
}

void ordenarPorValor(struct Produto estoque[], int total) {
    struct Produto copia[MAX_PRODUTOS];
    char ordem;

    for (int i = 0; i < total; i++) {
        copia[i] = estoque[i];
    }

    printf("Informe '+' para crescente ou '-' para decrescente: \n");
    scanf(" %c", &ordem);

    if (ordem == '+') {
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (copia[j].valorUnitario > copia[j + 1].valorUnitario) {
                    struct Produto temp = copia[j];
                    copia[j] = copia[j + 1];
                    copia[j + 1] = temp;
                }
            }
        }
    } else if (ordem == '-') {
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (copia[j].valorUnitario < copia[j + 1].valorUnitario) {
                    struct Produto temp = copia[j];
                    copia[j] = copia[j + 1];
                    copia[j + 1] = temp;
                }
            }
        }
    } else {
        printf("Resposta invalida!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%.2f\n", copia[i].valorUnitario);
    }
}

void carregarDados(struct Produto estoque[], int *total) {
    FILE *pArquivo = fopen("estoque.txt", "r");

    if (pArquivo == NULL) {
        printf("Nenhum dado salvo anteriormente. Iniciando vazio.\n");
        return;
    }

    *total = 0;

    while (fscanf(pArquivo, "%d;%99[^;];%d;%d;%d;%f;%d\n",
                   &estoque[*total].codigo,
                   estoque[*total].nome,
                   &estoque[*total].categoria,
                   &estoque[*total].quantDisponivel,
                   &estoque[*total].quantMinima,
                   &estoque[*total].valorUnitario,
                   &estoque[*total].situacao) == 7) {
        (*total)++;
    }

    fclose(pArquivo);
    printf("%d produtos carregados com sucesso.\n", *total);
}

void salvarDados(struct Produto estoque[], int total) {
    FILE *pArquivo = fopen("estoque.txt", "w");
    int i;

    if (pArquivo == NULL) {
        printf("Falha ao abrir arquivo!\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(pArquivo, "%d;%s;%d;%d;%d;%.2f;%d\n",
                estoque[i].codigo,
                estoque[i].nome,
                estoque[i].categoria,
                estoque[i].quantDisponivel,
                estoque[i].quantMinima,
                estoque[i].valorUnitario,
                estoque[i].situacao);
    }

    fclose(pArquivo);
}

void consultarPorNome(struct Produto estoque[], int total) {
    char nome_busca[100];
    int encontrou = 0;

    printf("Digite o nome (ou parte dele) que deseja buscar (sem espacos):\n");
    scanf(" %99[^\n]", nome_busca);

    printf("\n--- Resultados da Busca ---\n");

    for (int i = 0; i < total; i++) 
    {
        int contem_texto = 0;
        
        
        for (int j = 0; estoque[i].nome[j] != '\0' && contem_texto == 0; j++) 
        {
            int k = 0;
            
            
            while (nome_busca[k] != '\0' && estoque[i].nome[j + k] == nome_busca[k]) 
            {
                k++;
            }
            
            
            if (nome_busca[k] == '\0') 
            {
                contem_texto = 1; 
            }
        }

        
        if (contem_texto == 1) 
        {
            printf("Codigo: %d\n", estoque[i].codigo);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Categoria (Cod): %d\n", estoque[i].categoria);
            printf("Qtd Disponivel: %d\n", estoque[i].quantDisponivel);
            printf("Qtd Minima: %d\n", estoque[i].quantMinima);
            printf("Valor Unitario: R$ %.2f\n", estoque[i].valorUnitario);
            
            if (estoque[i].situacao == 1) {
                printf("Situacao: Ativo\n");
            } else if (estoque[i].situacao == 2) {
                printf("Situacao: Temporariamente Indisponivel\n");
            } else {
                printf("Situacao: Descontinuado\n");
            }
            printf("---------------------------\n");
            
            encontrou = 1;
        }
    }

    if (encontrou == 0) 
    {
        printf("Nenhum produto encontrado contendo o texto \"%s\".\n", nome_busca);
    }
    printf("\n");
}

void consultarPorCategoria(struct Produto estoque[], int total) {
    int categoria_busca;
    int encontrou = 0;

    printf("Digite o codigo numerico da categoria que deseja buscar:\n");
    scanf("%d", &categoria_busca);

    printf("\n--- Produtos da Categoria %d ---\n", categoria_busca);

    
    for (int i = 0; i < total; i++) 
    {
        
        if (estoque[i].categoria == categoria_busca) 
        {
            printf("Codigo: %d\n", estoque[i].codigo);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Categoria (Cod): %d\n", estoque[i].categoria);
            printf("Qtd Disponivel: %d\n", estoque[i].quantDisponivel);
            printf("Qtd Minima: %d\n", estoque[i].quantMinima);
            printf("Valor Unitario: R$ %.2f\n", estoque[i].valorUnitario);
            
            
            if (estoque[i].situacao == 1) {
                printf("Situacao: Ativo\n");
            } else if (estoque[i].situacao == 2) {
                printf("Situacao: Temporariamente Indisponivel\n");
            } else {
                printf("Situacao: Descontinuado\n");
            }
            printf("-------------------------------\n");
            
            
            encontrou = 1;
        }
    }

    
    if (encontrou == 0) 
    {
        printf("Nenhum produto cadastrado na categoria %d.\n", categoria_busca);
    }
    printf("\n");
}

void consultarPorSituacao(struct Produto estoque[], int total) 
{
    int situacao_busca;
    int encontrou = 0;

    printf("Digite o codigo da situacao que deseja buscar:\n");
    printf("1 - Ativo\n");
    printf("2 - Temporariamente Indisponivel\n");
    printf("3 - Descontinuado\n");
    printf("Opcao: ");
    scanf("%d", &situacao_busca);

    printf("\n--- Resultados da Busca (Situacao: %d) ---\n", situacao_busca);

    
    for (int i = 0; i < total; i++) 
    {
        
        if (estoque[i].situacao == situacao_busca) 
        {
            printf("Codigo: %d\n", estoque[i].codigo);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Categoria (Cod): %d\n", estoque[i].categoria);
            printf("Qtd Disponivel: %d\n", estoque[i].quantDisponivel);
            printf("Qtd Minima: %d\n", estoque[i].quantMinima);
            printf("Valor Unitario: R$ %.2f\n", estoque[i].valorUnitario);
            
            
            if (estoque[i].situacao == 1) {
                printf("Situacao: Ativo\n");
            } else if (estoque[i].situacao == 2) {
                printf("Situacao: Temporariamente Indisponivel\n");
            } else {
                printf("Situacao: Descontinuado\n");
            }
            printf("-------------------------------\n");
            
            encontrou = 1;
        }
    }

    if (encontrou == 0) 
    {
        printf("Nenhum produto encontrado com a situacao %d.\n", situacao_busca);
    }
    printf("\n");
}

void relatorioGeral(struct Produto estoque[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- RELATORIO GERAL ---\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: %d | Nome: %s | Categoria: %d | Qtd: %d | Minimo: %d | Valor: R$ %.2f | Situacao: %d\n",
               estoque[i].codigo, estoque[i].nome, estoque[i].categoria,
               estoque[i].quantDisponivel, estoque[i].quantMinima,
               estoque[i].valorUnitario, estoque[i].situacao);
    }
    printf("-------------------------\n");
}

void relatorioValorPorProduto(struct Produto estoque[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- RELATORIO: VALOR POR PRODUTO ---\n");
    for (int i = 0; i < total; i++) {
        float valorTotalProduto = estoque[i].quantDisponivel * estoque[i].valorUnitario;
        printf("Codigo: %d | Nome: %s | Qtd: %d | Valor Unit.: R$ %.2f | Valor Total: R$ %.2f\n",
               estoque[i].codigo, estoque[i].nome, estoque[i].quantDisponivel,
               estoque[i].valorUnitario, valorTotalProduto);
    }
    printf("------------------------------------\n");
}

void relatorioValorTotalEstoque(struct Produto estoque[], int total) {
    float totalEstoque = 0.0f;
    for (int i = 0; i < total; i++) {
        totalEstoque += estoque[i].quantDisponivel * estoque[i].valorUnitario;
    }

    printf("\n--- VALOR TOTAL DO ESTOQUE ---\n");
    printf("Valor Total em Estoque: R$ %.2f\n", totalEstoque);
    printf("-------------------------------\n");
}

void relatorioMaiorValorUnitario(struct Produto estoque[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    float maior = estoque[0].valorUnitario;
    for (int i = 1; i < total; i++) {
        if (estoque[i].valorUnitario > maior) {
            maior = estoque[i].valorUnitario;
        }
    }

    printf("\n--- PRODUTO(S) COM MAIOR VALOR UNITARIO (R$ %.2f) ---\n", maior);
    for (int i = 0; i < total; i++) {
        if (estoque[i].valorUnitario == maior) {
            printf("Codigo: %d | Nome: %s | Categoria: %d | Qtd: %d | Valor Unit.: R$ %.2f\n",
                   estoque[i].codigo, estoque[i].nome, estoque[i].categoria,
                   estoque[i].quantDisponivel, estoque[i].valorUnitario);
        }
    }
    printf("------------------------------------------------------\n");
}

void relatorioMaiorValorArmazenado(struct Produto estoque[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    float maiorValorArmazenado = estoque[0].quantDisponivel * estoque[0].valorUnitario;
    for (int i = 1; i < total; i++) {
        float valorArmazenado = estoque[i].quantDisponivel * estoque[i].valorUnitario;
        if (valorArmazenado > maiorValorArmazenado) {
            maiorValorArmazenado = valorArmazenado;
        }
    }

    printf("\n--- PRODUTO(S) COM MAIOR VALOR ARMAZENADO (R$ %.2f) ---\n", maiorValorArmazenado);
    for (int i = 0; i < total; i++) {
        float valorArmazenado = estoque[i].quantDisponivel * estoque[i].valorUnitario;
        if (valorArmazenado == maiorValorArmazenado) {
            printf("Codigo: %d | Nome: %s | Qtd: %d | Valor Unit.: R$ %.2f | Valor Total Armazenado: R$ %.2f\n",
                   estoque[i].codigo, estoque[i].nome, estoque[i].quantDisponivel,
                   estoque[i].valorUnitario, valorArmazenado);
        }
    }
    printf("--------------------------------------------------------\n");
}

void relatorioPorCategoria(struct Produto estoque[], int total) {
    const char *nomesCategorias[MAX_CATEGORIAS] = {
        "Material de escritorio",
        "Material de limpeza",
        "Equipamentos",
        "Componentes eletronicos",
        "Ferramentas",
        "Acessorios"
    };

    printf("\n--- RELATORIO POR CATEGORIA ---\n");
    for (int cat = 1; cat <= MAX_CATEGORIAS; cat++) {
        int qtdProdutos = 0;
        int qtdUnidades = 0;
        float valorTotalCat = 0.0f;

        for (int i = 0; i < total; i++) {
            if (estoque[i].categoria == cat) {
                qtdProdutos++;
                qtdUnidades += estoque[i].quantDisponivel;
                valorTotalCat += estoque[i].quantDisponivel * estoque[i].valorUnitario;
            }
        }

        printf("Categoria %d (%s):\n", cat, nomesCategorias[cat - 1]);
        printf("  - Qtd. de tipos de produtos: %d\n", qtdProdutos);
        printf("  - Total de unidades: %d\n", qtdUnidades);
        printf("  - Valor total acumulado: R$ %.2f\n", valorTotalCat);
        printf("----------------------------------------\n");
    }
}
