#include <stdio.h>
#include <string.h>

#define MAX 100
#define ARQUIVO "dados_b.csv"

typedef struct {
    int protocolo;
    char local[60];
    char tipo[50];
    char horario[20];
} Chamada;

int menu();
int buscarProtocolo(Chamada pilha[], int topo, int protocolo);
void registrarChamada(Chamada pilha[], int *topo);
void atenderChamada(Chamada pilha[], int *topo);
void consultarUltimaChamada(Chamada pilha[], int topo);
void buscarChamada(Chamada pilha[], int topo);
void listarChamadas(Chamada pilha[], int topo);
void salvarCSV(Chamada pilha[], int topo);
void carregarCSV(Chamada pilha[], int *topo);

int main() {
    Chamada pilha[MAX];
    int topo = -1;
    int opcao;

    carregarCSV(pilha, &topo);

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                registrarChamada(pilha, &topo);
                break;

            case 2:
                atenderChamada(pilha, &topo);
                break;

            case 3:
                consultarUltimaChamada(pilha, topo);
                break;

            case 4:
                buscarChamada(pilha, topo);
                break;

            case 5:
                listarChamadas(pilha, topo);
                break;

            case 6:
                salvarCSV(pilha, topo);
                break;

            case 7:
                carregarCSV(pilha, &topo);
                break;

            case 0:
                salvarCSV(pilha, topo);
                printf("\nPrograma encerrado. Dados salvos em CSV.\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

int menu() {
    int opcao;

    printf("\n=====================================\n");
    printf("      CHAMADAS DE EMERGENCIA\n");
    printf("=====================================\n");
    printf("1 - Registrar chamada\n");
    printf("2 - Atender chamada\n");
    printf("3 - Consultar ultima chamada\n");
    printf("4 - Buscar chamada por protocolo\n");
    printf("5 - Listar chamadas\n");
    printf("6 - Salvar em CSV\n");
    printf("7 - Carregar do CSV\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

int buscarProtocolo(Chamada pilha[], int topo, int protocolo) {
    int i;

    for (i = 0; i <= topo; i++) {
        if (pilha[i].protocolo == protocolo) {
            return i;
        }
    }

    return -1;
}

void registrarChamada(Chamada pilha[], int *topo) {
    Chamada nova;
    int posicao;

    if (*topo == MAX - 1) {
        printf("\nErro: pilha cheia. Nao e possivel registrar nova chamada.\n");
        return;
    }

    printf("\nDigite o protocolo da chamada: ");
    scanf("%d", &nova.protocolo);

    posicao = buscarProtocolo(pilha, *topo, nova.protocolo);

    if (posicao != -1) {
        printf("\nErro: ja existe uma chamada com esse protocolo.\n");
        return;
    }

    getchar();

    printf("Digite o local da ocorrencia: ");
    fgets(nova.local, 60, stdin);
    nova.local[strcspn(nova.local, "\n")] = '\0';

    printf("Digite o tipo da ocorrencia: ");
    fgets(nova.tipo, 50, stdin);
    nova.tipo[strcspn(nova.tipo, "\n")] = '\0';

    printf("Digite o horario da chamada. Exemplo: 14:30: ");
    fgets(nova.horario, 20, stdin);
    nova.horario[strcspn(nova.horario, "\n")] = '\0';

    (*topo)++;
    pilha[*topo] = nova;

    printf("\nChamada registrada com sucesso!\n");
}

void atenderChamada(Chamada pilha[], int *topo) {
    if (*topo == -1) {
        printf("\nNenhuma chamada para atender. A pilha esta vazia.\n");
        return;
    }

    printf("\nAtendendo chamada:\n");
    printf("Protocolo: %d\n", pilha[*topo].protocolo);
    printf("Local: %s\n", pilha[*topo].local);
    printf("Tipo: %s\n", pilha[*topo].tipo);
    printf("Horario: %s\n", pilha[*topo].horario);

    (*topo)--;

    printf("\nChamada atendida e removida da pilha.\n");
}

void consultarUltimaChamada(Chamada pilha[], int topo) {
    if (topo == -1) {
        printf("\nNenhuma chamada registrada. A pilha esta vazia.\n");
        return;
    }

    printf("\nUltima chamada registrada:\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Horario: %s\n", pilha[topo].horario);
}

void buscarChamada(Chamada pilha[], int topo) {
    int protocolo;
    int posicao;

    if (topo == -1) {
        printf("\nNenhuma chamada cadastrada para buscar.\n");
        return;
    }

    printf("\nDigite o protocolo que deseja buscar: ");
    scanf("%d", &protocolo);

    posicao = buscarProtocolo(pilha, topo, protocolo);

    if (posicao == -1) {
        printf("\nChamada nao encontrada.\n");
        return;
    }

    printf("\nChamada encontrada:\n");
    printf("Protocolo: %d\n", pilha[posicao].protocolo);
    printf("Local: %s\n", pilha[posicao].local);
    printf("Tipo: %s\n", pilha[posicao].tipo);
    printf("Horario: %s\n", pilha[posicao].horario);
}

void listarChamadas(Chamada pilha[], int topo) {
    int i;

    if (topo == -1) {
        printf("\nNenhuma chamada registrada.\n");
        return;
    }

    printf("\n=========== CHAMADAS NA PILHA ===========\n");
    printf("Ordem exibida: do topo para a base.\n");

    for (i = topo; i >= 0; i--) {
        printf("\nPosicao na pilha: %d\n", i);
        printf("Protocolo: %d\n", pilha[i].protocolo);
        printf("Local: %s\n", pilha[i].local);
        printf("Tipo: %s\n", pilha[i].tipo);
        printf("Horario: %s\n", pilha[i].horario);

        if (i == topo) {
            printf("Status: TOPO DA PILHA\n");
        }
    }
}

void salvarCSV(Chamada pilha[], int topo) {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar.\n");
        return;
    }

    fprintf(arquivo, "protocolo;local;tipo;horario\n");

    for (i = 0; i <= topo; i++) {
        fprintf(
            arquivo,
            "%d;%s;%s;%s\n",
            pilha[i].protocolo,
            pilha[i].local,
            pilha[i].tipo,
            pilha[i].horario
        );
    }

    fclose(arquivo);

    printf("\nDados salvos com sucesso no arquivo %s.\n", ARQUIVO);
}

void carregarCSV(Chamada pilha[], int *topo) {
    FILE *arquivo;
    char cabecalho[100];
    Chamada temp;

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        printf("\nArquivo CSV nao encontrado. Iniciando com pilha vazia.\n");
        return;
    }

    *topo = -1;

    fgets(cabecalho, 100, arquivo);

    while (
        fscanf(
            arquivo,
            "%d;%59[^;];%49[^;];%19[^\n]\n",
            &temp.protocolo,
            temp.local,
            temp.tipo,
            temp.horario
        ) == 4
    ) {
        if (*topo < MAX - 1) {
            (*topo)++;
            pilha[*topo] = temp;
        }
    }

    fclose(arquivo);

    printf("\nDados carregados com sucesso do arquivo %s.\n", ARQUIVO);
}