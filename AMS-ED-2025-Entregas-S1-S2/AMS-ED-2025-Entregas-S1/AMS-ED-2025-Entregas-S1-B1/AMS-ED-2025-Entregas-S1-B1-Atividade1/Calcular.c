/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <ctype.h>

void Calcular(int* XVal, int* XDesc, int*XTotal) {
    *XTotal = *XVal - ((*XVal) * (*XDesc)/100);
}

int main() {
    char opc;
    int Val, Desc, Total;
    
    
    int 
        *XVal = &Val,
        *XDesc =  &Desc,
        *XTotal = &Total;
    
 
    
    printf("Digite o valor do produto: \n");
    scanf("%d", XVal);
    
    do{
        while (getchar() != '\n');
        printf("Deseja aplicar desconto no valor do produto? [s/n]\n");
        opc = tolower(getchar());
        
        switch(opc){
            case 's':
                //printf("SIM");
                
                printf("Digite a porcentagem do desconto: \n");
                scanf("%d", XDesc);
                
                
                break;
            
           /* case 'n':
                
                break; */
                
            default:
                printf("Coloque entre 's' e 'n'.\n");
                break;
        }
        if(opc == 's' || opc == 'n') break;
       
    }
    while(opc != 's' || opc != 'n');
    Calcular(XVal, XDesc, XTotal);
    
    printf("Valor original do produto: %d\n", *XVal);
    printf("Porcentagem do desconto: %d\n", *XDesc);
    printf("Valor total do produto: %d\n", *XTotal);
    
    /*
    printf("Digite a porcentagem do desconto: \n");
    scanf("%d", XDesc);
    
    *XTotal = Calcular(*XVal, *XDesc);
    printf("Valor original do produto: %d\n", *XVal);
    printf("Porcentagem do desconto: %d\n", *XDesc);
    printf("Valor total do produto: %d\n", *XTotal);
    
    return 0; */
}