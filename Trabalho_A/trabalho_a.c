#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO_CSV "dados_a.csv"

typedef struct Node {
    int codigo;
    char nome[60];
    char categoria[40];
    int quantidade;
    float preco;
    struct Node *proximo; 
} Produto;

Produto *inicio = NULL;
int total = 0;

void menu();
void inserirProduto();
void listarProdutos();
void buscarCodigo();
void buscarNome();
void editarProduto();
void excluirProduto();
void salvarCSV();
void carregarCSV();
void estatisticas();
Produto* localizarCodigo(int codigo);
void limparBuffer();
void pausa();
void liberarLista(); 

int main(){
    int opcao;
    carregarCSV();
    do{
        menu();
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        switch(opcao){
            case 1:
                inserirProduto();
                break;
            case 2:
                buscarCodigo();
                break;
            case 3:
                buscarNome();
                break;
            case 4:
                editarProduto();
                break;
            case 5:
                excluirProduto();
                break;
            case 6:
                listarProdutos();
                break;
            case 7:
                estatisticas();
                break;
            case 8:
                salvarCSV();
                break;
            case 9:
                carregarCSV();
                break;
            case 0:
                salvarCSV();
                liberarLista(); 
                printf("\nDados salvos!\n");
                printf("Programa encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
        if(opcao != 0)
            pausa();
    } while(opcao != 0);
    return 0;
}

void menu(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("\n========================================");
    printf("\n      CONTROLE DE ESTOQUE");
    printf("\n========================================");
    printf("\nProdutos cadastrados: %d", total);
    printf("\n\n1  - Inserir Produto");
    printf("\n2  - Buscar por Codigo");
    printf("\n3  - Buscar por Nome");
    printf("\n4  - Editar Produto");
    printf("\n5  - Excluir Produto");
    printf("\n6  - Listar Produtos");
    printf("\n7  - Estatisticas");
    printf("\n8  - Salvar CSV");
    printf("\n9  - Carregar CSV");
    printf("\n0  - Sair");
    printf("\n========================================");
}

Produto* localizarCodigo(int codigo){
    Produto *atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual; 
        }
        atual = atual->proximo; 
    }
    return NULL; 
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausa(){
    printf("\n\nPressione ENTER para continuar...");
    getchar();
}

void inserirProduto(){
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) {
        printf("\nErro: Sem memória disponível!\n");
        return;
    }
    printf("\n=========== NOVO PRODUTO ===========\n");
    printf("Codigo: ");
    scanf("%d", &novo->codigo);
    limparBuffer();
    if(localizarCodigo(novo->codigo) != NULL){
        printf("\nJa existe um produto com esse codigo!\n");
        free(novo); 
        return;
    }
    printf("Nome: ");
    fgets(novo->nome, 60, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';
    printf("Categoria: ");
    fgets(novo->categoria, 40, stdin);
    novo->categoria[strcspn(novo->categoria, "\n")] = '\0';
    do{
        printf("Quantidade: ");
        scanf("%d", &novo->quantidade);
        if(novo->quantidade < 0)
            printf("Quantidade invalida!\n");
    } while(novo->quantidade < 0);
    do{
        printf("Preco: ");
        scanf("%f", &novo->preco);
        if(novo->preco < 0)
            printf("Preco invalido!\n");
    } while(novo->preco < 0);
    limparBuffer();
    novo->proximo = NULL;
    if (inicio == NULL || inicio->codigo > novo->codigo) {
        novo->proximo = inicio;
        inicio = novo;
    } 
    else {
        Produto *atual = inicio;
        while (atual->proximo != NULL && atual->proximo->codigo < novo->codigo) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    total++;
    printf("\nProduto cadastrado com sucesso!\n");
}

void listarProdutos(){
    if(inicio == NULL){
        printf("\nNao existem produtos cadastrados!\n");
        return;
    }
    printf("\n==============================================================\n");
    printf("%-8s %-25s %-18s %-10s %-10s\n", "Codigo", "Nome", "Categoria", "Qtd", "Preco");
    printf("==============================================================\n");
    Produto *atual = inicio;
    while (atual != NULL) {
        printf("%-8d %-25s %-18s %-10d R$ %-8.2f\n",
            atual->codigo, atual->nome, atual->categoria, atual->quantidade, atual->preco);
        atual = atual->proximo;
    }
    printf("==============================================================\n");
}

void buscarCodigo(){
    int codigo;
    if(inicio == NULL){
        printf("\nLista vazia!\n");
        return;
    }
    printf("\nCodigo: ");
    scanf("%d", &codigo);
    limparBuffer();
    Produto *pos = localizarCodigo(codigo);
    if(pos == NULL){
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\n=========== PRODUTO ===========");
    printf("\nCodigo.....: %d", pos->codigo);
    printf("\nNome.......: %s", pos->nome);
    printf("\nCategoria..: %s", pos->categoria);
    printf("\nQuantidade.: %d", pos->quantidade);
    printf("\nPreco......: R$ %.2f", pos->preco);
}

void buscarNome(){
    char nome[60];
    int encontrou = 0;
    if(inicio == NULL){
        printf("\nLista vazia!\n");
        return;
    }
    printf("\nDigite nome: ");
    fgets(nome, 60, stdin);
    nome[strcspn(nome, "\n")] = 0;
    printf("\nResultados:\n");
    Produto *atual = inicio;
    while (atual != NULL) {
        if(strstr(atual->nome, nome) != NULL){
            encontrou = 1;
            printf("\n---------------------------");
            printf("\nCodigo.....: %d", atual->codigo);
            printf("\nNome.......: %s", atual->nome);
            printf("\nCategoria..: %s", atual->categoria);
            printf("\nQuantidade.: %d", atual->quantidade);
            printf("\nPreco......: R$ %.2f", atual->preco);
        }
        atual = atual->proximo;
    }
    if(!encontrou) printf("\nencontrou produto encontrado.\n");
}

void editarProduto(){
    int codigo;
    if(inicio == NULL){
        printf("\nNao existem produtos cadastrados!\n");
        return;
    }
    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    limparBuffer();
    Produto *pos = localizarCodigo(codigo);
    if(pos == NULL){
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\n======= EDITANDO PRODUTO =======");
    printf("\nNome atual: %s", pos->nome);
    printf("\nNovo nome: ");
    fgets(pos->nome, 60, stdin);
    pos->nome[strcspn(pos->nome, "\n")] = '\0';
    printf("Categoria atual: %s", pos->categoria);
    printf("\nNova categoria: ");
    fgets(pos->categoria, 40, stdin);
    pos->categoria[strcspn(pos->categoria, "\n")] = '\0';
    do{
        printf("Nova quantidade: ");
        scanf("%d", &pos->quantidade);
        if(pos->quantidade < 0) printf("Quantidade invalida!\n");
    } while(pos->quantidade < 0);
    do{
        printf("Novo preco: ");
        scanf("%f", &pos->preco);
        if(pos->preco < 0) printf("Preco invalido!\n");
    } while(pos->preco < 0);
    limparBuffer();
    printf("\nProduto atualizado com sucesso!\n");
}

void excluirProduto(){
    int codigo;
    char resposta;
    if(inicio == NULL){
        printf("\nLista vazia!\n");
        return;
    }
    printf("\nCodigo do produto: ");
    scanf("%d", &codigo);
    limparBuffer();
    Produto *atual = inicio;
    Produto *anterior = NULL;
    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL){
        printf("\nProduto nao encontrado!\n");
        return;
    }
    printf("\nProduto encontrado: %s", atual->nome);
    printf("\nDeseja realmente excluir? (S/N): ");
    scanf("%c", &resposta);
    limparBuffer();
    if(resposta != 'S' && resposta != 's'){
        printf("\nOperacao cancelada!\n");
        return;
    }
    if (anterior == NULL) {
        inicio = atual->proximo; 
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual); 
    total--;
    printf("\nProduto removido com sucesso!\n");
}

void salvarCSV(){
    FILE *arquivo = fopen(ARQUIVO_CSV, "w");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo para salvar os dados!\n");
        return;
    }
    fprintf(arquivo, "Codigo;Nome;Categoria;Quantidade;Preco\n");
    Produto *atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%s;%d;%.2f\n",
                atual->codigo, atual->nome, atual->categoria, atual->quantidade, atual->preco);
        atual = atual->proximo;
    }
    fclose(arquivo);
    printf("\nDados salvos em '%s' com sucesso!\n", ARQUIVO_CSV);
}

void carregarCSV(){
    FILE *arquivo = fopen(ARQUIVO_CSV, "r");
    char linha[200];
    if(arquivo == NULL) return;
    liberarLista(); 
    total = 0; 
    if(fgets(linha, sizeof(linha), arquivo) == NULL){
        fclose(arquivo);
        return;
    }
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        Produto *novo = (Produto*) malloc(sizeof(Produto));
        if (novo == NULL) break;
        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, "\r")] = '\0';
        char *token = strtok(linha, ";");
        if(token != NULL) novo->codigo = atoi(token);
        token = strtok(NULL, ";");
        if(token != NULL) strcpy(novo->nome, token);
        token = strtok(NULL, ";");
        if(token != NULL) strcpy(novo->categoria, token);
        token = strtok(NULL, ";");
        if(token != NULL) novo->quantidade = atoi(token);
        token = strtok(NULL, ";");
        if(token != NULL) novo->preco = atof(token);
        novo->proximo = NULL;
        if (inicio == NULL) {
            inicio = novo;
        } else {
            Produto *atual = inicio;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novo;
        }
        total++;
    }
    fclose(arquivo);
    printf("\nDados carregados com sucesso! (%d produtos importados)\n", total);
}

void estatisticas(){
    int totalItens = 0;
    float valorTotalEstoque = 0;
    if(inicio == NULL){
        printf("\nNao ha dados suficientes para gerar estatisticas!\n");
        return;
    }
    Produto *atual = inicio;
    Produto *maior = inicio;
    Produto *menor = inicio;
    while (atual != NULL) {
        totalItens += atual->quantidade;
        valorTotalEstoque += (atual->quantidade * atual->preco);
        if(atual->preco > maior->preco) maior = atual;
        if(atual->preco < menor->preco) menor = atual;
        atual = atual->proximo;
    }
    printf("\n================ ESTATISTICAS DE ESTOQUE ================\n");
    printf("Total de produtos unicos cadastrados: %d\n", total);
    printf("Quantidade total de itens fisicos...: %d unidades\n", totalItens);
    printf("Valor financeiro total investido....: R$ %.2f\n", valorTotalEstoque);
    printf("---------------------------------------------------------\n");
    printf("Produto mais CARO: %s (R$ %.2f)\n", maior->nome, maior->preco);
    printf("Produto mais BARATO: %s (R$ %.2f)\n", menor->nome, menor->preco);
    printf("=========================================================\n");
}

void liberarLista() {
    Produto *atual = inicio;
    while (atual != NULL) {
        Produto *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio = NULL;
}