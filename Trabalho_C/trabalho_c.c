#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX 10
#define CLEAR "clear"

typedef struct{
    int senha;
    char tipo;
    char horario[20];
} Atendimento;

// FILA NORMAL (simples)
Atendimento filaNormal[MAX];
int inicioNormal = 0;
int fimNormal = 0;
int qtdNormal = 0;

// FILA PREFERENCIAL (circular)
Atendimento filaPref[MAX];
int inicioPref = 0;
int fimPref = 0;
int qtdPref = 0;

// Contadores das senhas
int senhaNormal = 1;
int senhaPref = 1;

// Regra: 2 normais para 1 preferencial
int contadorNormal = 0;

// Protótipos
void esperar();
void gerarNormal();
void gerarPreferencial();
void chamarSenha();
void mostrarFilas();
void buscarSenha();
void cancelarSenha();
void salvarCSV();
void carregarCSV();

int main(){

    int op;

    carregarCSV();

    do{

        system(CLEAR);

        printf("===================================\n");
        printf("     ATENDIMENTO BANCARIO\n");
        printf("===================================\n");
        printf("1 - Gerar senha Normal\n");
        printf("2 - Gerar senha Preferencial\n");
        printf("3 - Chamar proxima senha\n");
        printf("4 -Mostrar filas\n");
        printf("5 - Buscar senha\n");
        printf("6 - Cancelar senha\n");
        printf("7 - Salvar CSV\n");
        printf("8 - Carregar CSV\n");
        printf("9 - Sair\n");
        printf("===================================\n");
        printf("Escolha: ");
        scanf("%d",&op);
        getchar();

        switch(op){

            case 1:
                system(CLEAR);
                gerarNormal();
                esperar();
                break;

            case 2:
                system(CLEAR);
                gerarPreferencial();
                esperar();
                break;

            case 3:
                system(CLEAR);
                chamarSenha();
                esperar();
                break;

            case 4:
                system(CLEAR);
                mostrarFilas();
                esperar();
                break;

            case 5:
                system(CLEAR);
                buscarSenha();
                esperar();
                break;

            case 6:
                system(CLEAR);
                cancelarSenha();
                esperar();
                break;

            case 7:
                system(CLEAR);
                salvarCSV();
                esperar();
                break;

            case 8:
                system(CLEAR);
                carregarCSV();
                printf("\nFilas carregadas!\n");
                esperar();
                break;

            case 9:
                salvarCSV();
                printf("\nPrograma encerrado!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                esperar();
        }

    }while(op!=9);

    return 0;
}

void esperar(){
    sleep(5);
}

void gerarNormal(){

    if(qtdNormal == MAX){
        printf("\nFila normal cheia!\n");
        return;
    }

    filaNormal[fimNormal].senha = senhaNormal++;
    filaNormal[fimNormal].tipo = 'N';

    time_t t = time(NULL);
    strftime(filaNormal[fimNormal].horario,20,"%H:%M:%S",localtime(&t));

    printf("\nSenha gerada: N%d\n",filaNormal[fimNormal].senha);
    printf("Horario: %s\n",filaNormal[fimNormal].horario);

    fimNormal++;
    qtdNormal++;
}

void gerarPreferencial(){

    if(qtdPref == MAX){
        printf("\nFila preferencial cheia!\n");
        return;
    }

    filaPref[fimPref].senha = senhaPref++;
    filaPref[fimPref].tipo = 'P';

    time_t t = time(NULL);
    strftime(filaPref[fimPref].horario,20,"%H:%M:%S",localtime(&t));

    printf("\nSenha gerada: P%d\n",filaPref[fimPref].senha);
    printf("Horario: %s\n",filaPref[fimPref].horario);

    fimPref = (fimPref + 1) % MAX;
    qtdPref++;
}
void chamarSenha(){

    // Regra: 2 normais para cada 1 preferencial

    if(qtdNormal == 0 && qtdPref == 0){
        printf("\nNao ha senhas na fila!\n");
        return;
    }

    // Atende preferencial após 2 normais
    if((contadorNormal >= 2 && qtdPref > 0) || qtdNormal == 0){

        printf("\n====================\n");
        printf("CHAMANDO SENHA P%d\n", filaPref[inicioPref].senha);
        printf("Horario de chegada: %s\n", filaPref[inicioPref].horario);

        inicioPref = (inicioPref + 1) % MAX;
        qtdPref--;
        contadorNormal = 0;

        return;
    }

    if(qtdNormal > 0){

        printf("\n====================\n");
        printf("CHAMANDO SENHA N%d\n", filaNormal[inicioNormal].senha);
        printf("Horario de chegada: %s\n", filaNormal[inicioNormal].horario);

        inicioNormal++;
        qtdNormal--;
        contadorNormal++;
    }

}

void mostrarFilas(){

    int i;

    printf("\n=========== FILA NORMAL ===========\n");

    if(qtdNormal == 0)
        printf("Fila vazia.\n");
    else{

        for(i = inicioNormal; i < fimNormal; i++){

            printf("N%d - %s\n",
                   filaNormal[i].senha,
                   filaNormal[i].horario);
        }
    }

    printf("\n======= FILA PREFERENCIAL =======\n");

    if(qtdPref == 0)
        printf("Fila vazia.\n");
    else{

        for(i=0;i<qtdPref;i++){

            int pos = (inicioPref+i)%MAX;

            printf("P%d - %s\n",
                   filaPref[pos].senha,
                   filaPref[pos].horario);
        }
    }

}

void buscarSenha(){

    char tipo;
    int senha;

    printf("Digite o tipo (N/P): ");
    scanf(" %c",&tipo);

    printf("Digite o numero da senha: ");
    scanf("%d",&senha);

    if(tipo=='N' || tipo=='n'){

        for(int i=inicioNormal;i<fimNormal;i++){

            if(filaNormal[i].senha==senha){

                printf("\nSenha encontrada!\n");
                printf("Horario: %s\n",filaNormal[i].horario);
                return;
            }

        }

    }else{

        for(int i=0;i<qtdPref;i++){

            int pos=(inicioPref+i)%MAX;

            if(filaPref[pos].senha==senha){

                printf("\nSenha encontrada!\n");
                printf("Horario: %s\n",filaPref[pos].horario);
                return;
            }

        }

    }

    printf("\nSenha nao encontrada.\n");

}

void cancelarSenha(){

    char tipo;
    int senha;

    printf("Tipo da senha (N/P): ");
    scanf(" %c",&tipo);

    printf("Numero da senha: ");
    scanf("%d",&senha);

    if(tipo=='N' || tipo=='n'){

        int achou=-1;

        for(int i=inicioNormal;i<fimNormal;i++){

            if(filaNormal[i].senha==senha){

                achou=i;
                break;
            }

        }

        if(achou==-1){

            printf("\nSenha nao encontrada.\n");
            return;

        }

        for(int i=achou;i<fimNormal-1;i++)
            filaNormal[i]=filaNormal[i+1];

        fimNormal--;
        qtdNormal--;

        printf("\nSenha cancelada!\n");

    }else{

        int achou=-1;

        for(int i=0;i<qtdPref;i++){

            int pos=(inicioPref+i)%MAX;

            if(filaPref[pos].senha==senha){

                achou=pos;
                break;
            }

        }

        if(achou==-1){

            printf("\nSenha nao encontrada.\n");
            return;

        }

        while(achou!=fimPref){

            int prox=(achou+1)%MAX;
            filaPref[achou]=filaPref[prox];
            achou=prox;
        }

        fimPref=(fimPref-1+MAX)%MAX;
        qtdPref--;

        printf("\nSenha cancelada!\n");

    }

}
void salvarCSV(){

    FILE *arq = fopen("senhas.csv","w");

    if(arq==NULL){

        printf("\nErro ao abrir arquivo!\n");
        return;

    }

    fprintf(arq,"tipo,senha,horario\n");

    // Salva fila normal
    for(int i=inicioNormal;i<fimNormal;i++){

        fprintf(arq,"%c,%d,%s\n",
                filaNormal[i].tipo,
                filaNormal[i].senha,
                filaNormal[i].horario);

    }

    // Salva fila preferencial
    for(int i=0;i<qtdPref;i++){

        int pos=(inicioPref+i)%MAX;

        fprintf(arq,"%c,%d,%s\n",
                filaPref[pos].tipo,
                filaPref[pos].senha,
                filaPref[pos].horario);

    }

    fclose(arq);

    printf("\nArquivo salvo com sucesso!\n");

}

void carregarCSV(){

    FILE *arq=fopen("senhas.csv","r");

    if(arq==NULL)
        return;

    char linha[100];

    // Ignora o cabeçalho
    fgets(linha,100,arq);

    // Reinicia as filas
    inicioNormal=0;
    fimNormal=0;
    qtdNormal=0;

    inicioPref=0;
    fimPref=0;
    qtdPref=0;

    senhaNormal=1;
    senhaPref=1;

    while(fgets(linha,100,arq)){

        Atendimento a;

        sscanf(linha,"%c,%d,%19[^\n]",
               &a.tipo,
               &a.senha,
               a.horario);

        if(a.tipo=='N'){

            filaNormal[fimNormal]=a;
            fimNormal++;
            qtdNormal++;

            if(a.senha>=senhaNormal)
                senhaNormal=a.senha+1;

        }else{

            filaPref[fimPref]=a;
            fimPref=(fimPref+1)%MAX;
            qtdPref++;

            if(a.senha>=senhaPref)
                senhaPref=a.senha+1;

        }

    }

    fclose(arq);

}
