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

Pedido* criar_pilha() {
    return NULL;
}

Pedido* criar_pedido(int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        printf("Erro ao alocar memória para novo pedido!\n");
        return NULL;
    }
    
    novo_pedido->numero_pedido = numero;
    strcpy(novo_pedido->nome_cliente, nome_cliente);
    strcpy(novo_pedido->descricao_prato, descricao);
    novo_pedido->quantidade = quantidade;
    novo_pedido->status = status;
    novo_pedido->proximo = NULL;

    return novo_pedido;
}

void empilhar_pedido(Pedido** topo, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = criar_pedido(numero, nome_cliente, descricao, quantidade, status);
    if (novo_pedido == NULL) return;

    novo_pedido->proximo = *topo;
    *topo = novo_pedido;
}

Pedido* obter_pedido(Pedido* topo, int numero) {
    Pedido* temp = topo;
    while (temp != NULL) {
        if (temp->numero_pedido == numero) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

void remover_pedido(Pedido** topo, int numero) {
    Pedido* atual = *topo;
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
        *topo = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Pedido %d removido com sucesso!\n", numero);
}

void remover_todos_pedidos(Pedido** topo) {
    Pedido* temp;
    while (*topo != NULL) {
        temp = *topo;
        *topo = (*topo)->proximo;
        free(temp);
    }
    printf("Todos os pedidos foram removidos!\n");
}

void exibir_pedido(Pedido* topo, int numero) {
    Pedido* pedido = obter_pedido(topo, numero);
    if (pedido != NULL) {
        const char* status_str[] = { "PENDENTE", "EM PREPARO", "PRONTO", "ENTREGUE" };
        printf("Pedido %d: %s - %s - %d - Status: %s\n", pedido->numero_pedido, pedido->nome_cliente, pedido->descricao_prato, pedido->quantidade, status_str[pedido->status]);
    } else {
        printf("Pedido não encontrado!\n");
    }
}

void exibir_todos_pedidos(Pedido* topo) {
    if (topo == NULL) {
        printf("Não há pedidos na pilha!\n");
        return;
    }

    Pedido* temp = topo;
    const char* status_str[] = { "PENDENTE", "EM PREPARO", "PRONTO", "ENTREGUE" };
    while (temp != NULL) {
        printf("Pedido %d: %s - %s - %d - Status: %s\n", temp->numero_pedido, temp->nome_cliente, temp->descricao_prato, temp->quantidade, status_str[temp->status]);
        temp = temp->proximo;
    }
}

StatusPedido ler_status() {
    int status;
    printf("Digite o status do pedido (0 - PENDENTE, 1 - EM PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
    scanf("%d", &status);
    if (status >= 0 && status <= 3) {
        return (StatusPedido)status;
    }
    printf("Status inválido! Considerando como PENDENTE.\n");
    return PENDENTE;
}

void editar_pedido(Pedido* topo, int numero) {
    Pedido* pedido = obter_pedido(topo, numero);
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

    pedido->status = ler_status();
    printf("Pedido atualizado com sucesso!\n");
}

int main() {
    Pedido* pilha_pedidos = criar_pilha();
    int numero, quantidade;
    char nome_cliente[100], descricao_prato[100];
    StatusPedido status;
    int opcao;

    while (1) {
        printf("Menu:\n");
        printf("1. Inserir novo pedido\n");
        printf("2. Exibir pedido\n");
        printf("3. Editar pedido\n");
        printf("4. Remover pedido\n");
        printf("5. Exibir todos os pedidos\n");
        printf("6. Remover todos os pedidos\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                printf("Digite o nome do cliente: ");
                getchar();  // Para consumir o caractere de nova linha remanescente
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';  // Remove a nova linha do final
                printf("Digite a descrição do prato: ");
                fgets(descricao_prato, sizeof(descricao_prato), stdin);
                descricao_prato[strcspn(descricao_prato, "\n")] = '\0';  // Remove a nova linha do final
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                status = ler_status();
                empilhar_pedido(&pilha_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;

            case 2:
                printf("Digite o número do pedido para exibir: ");
                scanf("%d", &numero);
                exibir_pedido(pilha_pedidos, numero);
                break;

            case 3:
                printf("Digite o número do pedido para editar: ");
                scanf("%d", &numero);
                editar_pedido(pilha_pedidos, numero);
                break;

            case 4:
                printf("Digite o número do pedido para remover: ");
                scanf("%d", &numero);
                remover_pedido(&pilha_pedidos, numero);
                break;

            case 5:
                exibir_todos_pedidos(pilha_pedidos);
                break;

            case 6:
                remover_todos_pedidos(&pilha_pedidos);
                break;

            case 7:
                printf("Saindo...\n");
                remover_todos_pedidos(&pilha_pedidos);
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}
