/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-5                                 */
/*             Objetivo: << Restaurante utilizando Pilha >>                         */
/*                                                                                  */
/*                                Autor: Matheus David Carbone Luna                 */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct Pedido {
    int numero_pedido;
    char nome_cliente[100];
    char descricao_prato[100];
    int quantidade;
    StatusPedido status;
    struct Pedido* proximo;
} Pedido;

typedef struct {
    Pedido* topo;
} Pilha;

const char* status_para_string(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "PENDENTE";
        case EM_PREPARO: return "EM PREPARO";
        case PRONTO: return "PRONTO";
        case ENTREGUE: return "ENTREGUE";
        default: return "DESCONHECIDO";
    }
}

Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        return NULL;
    }
    pilha->topo = NULL;
    return pilha;
}

void empilhar(Pilha* pilha, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        printf("Erro ao alocar memória para novo pedido!\n");
        return;
    }
    
    novo_pedido->numero_pedido = numero;
    strcpy(novo_pedido->nome_cliente, nome_cliente);
    strcpy(novo_pedido->descricao_prato, descricao);
    novo_pedido->quantidade = quantidade;
    novo_pedido->status = status;
    novo_pedido->proximo = pilha->topo;
    
    pilha->topo = novo_pedido;
}

Pedido* obter_pedido(Pilha* pilha, int numero) {
    Pedido* atual = pilha->topo;
    while (atual != NULL) {
        if (atual->numero_pedido == numero) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover_pedido(Pilha* pilha, int numero) {
    Pedido* atual = pilha->topo;
    Pedido* anterior = NULL;
    
    while (atual != NULL && atual->numero_pedido != numero) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("Pedido não encontrado!\n");
        return;
    }
    
    if (anterior == NULL) {
        pilha->topo = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    printf("Pedido %d removido com sucesso!\n", numero);
}

void alterar_pedido(Pilha* pilha, int numero) {
    Pedido* pedido = obter_pedido(pilha, numero);
    if (pedido == NULL) {
        printf("Pedido não encontrado!\n");
        return;
    }

    printf("Editar pedido %d\n", numero);
    printf("Digite o novo nome do cliente: ");
    getchar();
    fgets(pedido->nome_cliente, sizeof(pedido->nome_cliente), stdin);
    pedido->nome_cliente[strcspn(pedido->nome_cliente, "\n")] = '\0';

    printf("Digite a nova descrição do prato: ");
    fgets(pedido->descricao_prato, sizeof(pedido->descricao_prato), stdin);
    pedido->descricao_prato[strcspn(pedido->descricao_prato, "\n")] = '\0';

    printf("Digite a nova quantidade: ");
    scanf("%d", &pedido->quantidade);

    int novo_status;
    printf("Digite o status do pedido (0 - PENDENTE, 1 - EM_PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
    scanf("%d", &novo_status);
    if (novo_status >= 0 && novo_status <= 3) {
        pedido->status = (StatusPedido)novo_status;
    } else {
        printf("Status inválido! Mantendo o status atual.\n");
    }

    printf("Pedido atualizado com sucesso!\n");
    while (getchar() != '\n');
}

void liberar_pilha(Pilha* pilha) {
    Pedido* temp;
    while (pilha->topo != NULL) {
        temp = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        free(temp);
    }
    free(pilha);
}

int main() {
    Pilha* pilha_pedidos = criar_pilha();
    int numero, quantidade, opcao;
    char nome_cliente[100], descricao_prato[100];
    StatusPedido status;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir novo pedido\n");
        printf("2. Exibir pedido\n");
        printf("3. Alterar pedido\n");
        printf("4. Remover pedido\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                getchar();
                printf("Digite o nome do cliente: ");
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';
                printf("Digite a descrição do prato: ");
                fgets(descricao_prato, sizeof(descricao_prato), stdin);
                descricao_prato[strcspn(descricao_prato, "\n")] = '\0';
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                printf("Digite o status do pedido (0 - PENDENTE, 1 - EM_PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
                scanf("%d", &status);
                empilhar(pilha_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;

            case 2:
                printf("Digite o número do pedido para exibir: ");
                scanf("%d", &numero);
                Pedido* pedido = obter_pedido(pilha_pedidos, numero);
                if (pedido != NULL) {
                    printf("Pedido %d: %s - %s - %d - Status: %s\n", pedido->numero_pedido, pedido->nome_cliente, pedido->descricao_prato, pedido->quantidade, status_para_string(pedido->status));
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;

            case 3:
                printf("Digite o número do pedido para alterar: ");
                scanf("%d", &numero);
                alterar_pedido(pilha_pedidos, numero);
                break;

            case 4:
                printf("Digite o número do pedido para remover: ");
                scanf("%d", &numero);
                remover_pedido(pilha_pedidos, numero);
                break;

            case 5:
                liberar_pilha(pilha_pedidos);
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}
