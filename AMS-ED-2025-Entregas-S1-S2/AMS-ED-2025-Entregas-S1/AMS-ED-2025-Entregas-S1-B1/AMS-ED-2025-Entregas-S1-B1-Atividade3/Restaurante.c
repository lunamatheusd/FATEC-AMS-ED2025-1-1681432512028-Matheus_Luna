/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: << Manipulacao de Array com ponteiro >>                    */
/*                                                                                  */
/*                                Autor: Matheus David Carbone Luna                 */
/*                                                                  Data:06/03/2025 */
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

Pedido* criar_lista() {
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

void inserir_pedido(Pedido** lista, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = criar_pedido(numero, nome_cliente, descricao, quantidade, status);
    if (novo_pedido == NULL) return;

    if (*lista == NULL) {
        *lista = novo_pedido;
    } else {
        Pedido* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo_pedido;
    }
}

Pedido* obter_pedido(Pedido* lista, int numero) {
    Pedido* temp = lista;
    while (temp != NULL) {
        if (temp->numero_pedido == numero) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

void liberar_lista(Pedido* lista) {
    Pedido* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

StatusPedido ler_status() {
    int status;
    printf("Digite o status do pedido (0 - PENDENTE, 1 - EM_PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
    scanf("%d", &status);
    if (status >= 0 && status <= 3) {
        return (StatusPedido)status;
    }
    printf("Status inválido! Considerando como PENDENTE.\n");
    return PENDENTE;
}

void editar_pedido(Pedido* lista, int numero) {
    Pedido* pedido = obter_pedido(lista, numero);
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

void remover_pedido(Pedido** lista, int numero) {
    Pedido* atual = *lista;
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
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Pedido %d removido com sucesso!\n", numero);
}


int main() {
    Pedido* lista_pedidos = criar_lista();
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
        printf("5. Sair\n");
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
                inserir_pedido(&lista_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;

            case 2:
                printf("Digite o número do pedido para exibir: ");
                scanf("%d", &numero);
                Pedido* pedido = obter_pedido(lista_pedidos, numero);
                if (pedido != NULL) {
                    printf("Pedido %d: %s - %s - %d - Status: %d\n", pedido->numero_pedido, pedido->nome_cliente, pedido->descricao_prato, pedido->quantidade, pedido->status);
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;
                
            case 3:
            printf("Digite o número do pedido para editar: ");
            scanf("%d", &numero);
            editar_pedido(lista_pedidos, numero);
            break;
            
            case 4:
            printf("Digite o número do pedido para remover: ");
            scanf("%d", &numero);
            remover_pedido(&lista_pedidos, numero);
            break;

            case 5:
                liberar_lista(lista_pedidos);
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}