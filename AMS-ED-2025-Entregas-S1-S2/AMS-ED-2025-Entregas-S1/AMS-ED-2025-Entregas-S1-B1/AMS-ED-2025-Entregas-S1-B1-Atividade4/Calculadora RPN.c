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
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    double itens[MAX];
    int topo;
} Pilha;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return (p->topo == -1);
}

int cheia(Pilha* p) {
    return (p->topo == MAX - 1);
}

void push(Pilha* p, double dado) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = dado;
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    return p->itens[p->topo--];
}

double top(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    return p->itens[p->topo];
}

void calcular_rpn(char* expressao) {
    Pilha* p = criar_pilha();
    char* token = strtok(expressao, " ");
    double op1, op2;
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
        } else {
            op2 = pop(p);
            op1 = pop(p);
            switch (token[0]) {
                case '+': push(p, op1 + op2); break;
                case '-': push(p, op1 - op2); break;
                case '*': push(p, op1 * op2); break;
                case '/': 
                    if (op2 == 0) {
                        printf("Erro: Divisão por zero!\n");
                        exit(EXIT_FAILURE);
                    }
                    push(p, op1 / op2);
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }
    printf("Resultado: %.2f\n", pop(p));
    free(p);
}

int main() {
    char expressao[MAX];
    printf("Digite a expressão RPN: ");
    fgets(expressao, MAX, stdin);
    expressao[strcspn(expressao, "\n")] = 0;
    calcular_rpn(expressao);
    return 0;
}
