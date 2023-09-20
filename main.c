#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "function.c"



int main()
{
    setlocale(LC_ALL, "portuguese");

    int opc;

    do
    {
        printf("----MENU----\n");
        printf("------------\n");
        printf("1. Produtos|\n2. Vendas  |\n3. Sair    |\n");
        printf("------------\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            Produtos();
            break;
        case 2:
            Vendas();
            break;
        case 3:
            return 0;
        default:
            printf("\nOpcao invalida, digite novamente!\n");
            break;
        }
    }
    while (opc < 1 || opc > 3 || opc != 3);


    return 0;
}
