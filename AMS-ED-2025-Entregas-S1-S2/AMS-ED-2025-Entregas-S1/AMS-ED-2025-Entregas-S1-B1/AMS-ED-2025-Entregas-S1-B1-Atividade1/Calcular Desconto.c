/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int Calcular(int XVal, int XDesc) {
    return XVal - (XVal * XDesc/100);
}

int main() {
    int Val, Desc, Total;
    int *XVal;
    int *XDesc;
    int *XTotal;
    
    XVal = &Val;
    XDesc = &Desc;
    XTotal = &Total;
    
    printf("Digite o valor do produto: \n");
    scanf("%d", XVal);
    
    printf("Digite a porcentagem do desconto: \n");
    scanf("%d", XDesc);
    
    *XTotal = Calcular(*XVal, *XDesc);
    printf("Valor original do produto: %d\n", *XVal);
    printf("Porcentagem do desconto: %d\n", *XDesc);
    printf("Valor total do produto: %d\n", *XTotal);
    
    return 0;
}