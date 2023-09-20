#include "header.h"
void Ler()
{
    FILE* arquivo;
    arquivo = fopen("produtos.bin", "rb");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }


    fread(&indiceG,sizeof(int),1,arquivo);
    p =malloc(sizeof(itens)*indiceG);
    fread(p,sizeof(itens),indiceG,arquivo);



    fclose(arquivo); //fechando o arquivo

    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    itens estoque;

    while (fscanf(arquivo, "%d %s %d %f", &estoque.Cod, estoque.Nome, &estoque.QTDtotal, &estoque.Valor) == 4)
    {

        p = realloc(p, (indiceG + 1) * sizeof(itens));
        if (p == NULL)
        {
            printf("\nErro na realocao de memoria.\n");
            return;
        }

        p[indiceG] = estoque;
        indiceG++;
    }

    fclose(arquivo);

}

void Exibir()
{
    if (p == NULL)
    {
        Ler();
    }
    printf("\n--- Produtos Cadastrados ---\n");
    printf("Cod\tNome\tValor\tEstoque\n");

    for (int i = 0; i < indiceG; i++)
    {
        printf("%d\t%s\t%.2f\t%d\n", p[i].Cod, p[i].Nome, p[i].Valor, p[i].QTDtotal);
    }
    printf("---------------------------\n");
}


void Cadastrar() //cadastrar novos produtos.
{
    char voltar = 's';
    int tamanhodastring;
    while(voltar == 's')
    {
        p = realloc(p, (indiceG + 1) * sizeof(itens));
        printf("   --------- Adicionando Produtos ---------\n ");
        printf("\n|   Digite as informações do produto   |\n");
        printf(" Digite o Codigo: ");
        scanf("%i", &p[indiceG].Cod);
        getchar();

        while(p[indiceG].Cod <= 0)
        {
            printf("\n O codigo tem que ser maior que 0, digite novamente\n");
            scanf("%i", &p[indiceG].Cod);
            getchar();
        }

        printf(" Digite o nome: ");
        gets(p[indiceG].Nome);

        while(strlen(p[indiceG].Nome) > 25 || strlen(p[indiceG].Nome) == '\0')
        {
            printf("o tamanho do nome excedeu o limite\nOu nome do produto estar vazio \nPor favor insira novamente\n");
            gets(p[indiceG].Nome);
        }

        printf(" Digite a quantidade que vai ter no estoque: ");
        scanf("%i", &p[indiceG].QTDtotal);
        getchar();

        while(p[indiceG].QTDtotal < 0)
        {
            printf("\n A quantidade tem que ser maior que 0, digite novamente\n");
            scanf("%i", &p[indiceG].QTDtotal);
            getchar();
        }

        printf(" Digite o valor unitario do produto: ");
        scanf("%f", &p[indiceG].Valor);
        getchar();

        while(p[indiceG].Valor <= 0)
        {
            printf("\n O Valor tem que ser maior que 0, digite novamente\n");
            scanf("%f", &p[indiceG].Valor);
            getchar();
        }

        for(int i = 0; i < indiceG; i++)
        {
            if(p[indiceG].Cod == p[i].Cod)
            {
                printf("Codigo já existente, adicione outro");
                return 1;
            }
        }

        fflush(stdin);

        if (p == NULL)
        {
            printf("\n Erro na realocao de memoria");
            return;
        }
        else
        {
            //p = pnovo;
            //p[indiceG] = aux;
            indiceG++;
            printf("\n O produto foi salvo!\n");

        }

        ///Chama a função para salvar os dados;
        Salvar();

        ///Pede se quer adicionar outro produto
        printf("deseja adicionar outro produto?\n");
        scanf("%c",&voltar);
        getchar();
    }


}

void Salvar()
{
    if (p == NULL || indiceG == 0)
    {
        printf("\n Nenhum produto cadastrado.\n");
        return;
    }

    FILE* arquivo;
    arquivo = fopen("produtos.bin", "wb");

    if (arquivo == NULL)
    {
        printf("\n Erro ao abrir o arquivo.\n");
        return;
    }
    fwrite(&indiceG,sizeof(int),1,arquivo);
    fwrite(p,sizeof(itens),indiceG,arquivo);
    fclose(arquivo);


    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL)
    {
        printf("\n Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < indiceG; i++)
    {
        fprintf(arquivo, "%d %s %d %.2f\n", p[i].Cod, p[i].Nome, p[i].QTDtotal, p[i].Valor);
    }

    fclose(arquivo);

    printf("\n Produtos salvos com sucesso no arquivo.\n");
}


void Voltar()
{
    printf("Voltanto ao Menu...\n");
}

void Produtos()
{
    int opc;
    Ler();

    do
    {
        printf("\n---SUB MENU---\n");
        printf("--------------\n");
        printf("|1. Exibir    |\n");
        printf("|2. Cadastrar |\n");
        printf("|3. Atualizar |\n");
        printf("|4. Excluir   |\n");
        printf("|5. Salvar    |\n");
        printf("|6. Ler       |\n");
        printf("|7. Voltar    |\n");
        printf("--------------\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            Exibir();
            break;
        case 2:
            Cadastrar();
            break;
        case 3:
            Atualizar();
            break;
        case 4:
            Excluir();
            break;
        case 5:
            Salvar();
            break;
        case 6:
            Ler();
            break;
        case 7:
            Voltar();
            break;
        default:
            printf("Opcao invalida, digite novamente!\n");
            break;
        }
    }
    while (opc < 1 || opc > 7 || opc != 7);
}


void Atualizar()
{
    int cod = 0;
    int aux = 0;
    int i;

    printf("Selecione o Codigo do produto que deseja editar: ");
    scanf("%i", &cod);
    getchar();

    for(i=0; i<indiceG; i++)
    {
        if(cod == p[i].Cod)
        {
            printf("\nEditando Produto %d\n", p[i].Cod);
            printf("Quantidade atual: %d\n", p[i].QTDtotal);
            printf("Nova quantidade: ");
            scanf("%d", &p[i].QTDtotal);
            getchar();
            printf("Valor atual: %.2f\n", p[i].Valor);
            printf("Novo valor: ");
            scanf("%f", &p[i].Valor);
        }
    }
}

void Excluir()
{
    int cod = 0;
    int i, j;

    Exibir();

    printf("Selecione o Codigo do produto que deseja excluir: ");
    scanf("%i", &cod);
    getchar();

    for (i = 0; i < indiceG; i++)
    {
        if (cod == p[i].Cod)
        {
            printf("\nProduto %d excluido com sucesso!\n", p[i].Cod);

            // Desloca os elementos do array para excluir o produto
            for (j = i; j < indiceG - 1; j++)
            {
                p[j] = p[j + 1];
            }

            indiceG--;

            // Realoca a memória para o novo tamanho do array
            itens *pnovo = realloc(p, indiceG * sizeof(itens));
            if (pnovo == NULL)
            {
                printf("\nErro na realocao de memoria");
                return;
            }

            p = pnovo;

            Salvar();
            return;
        }
    }

    printf("\nProduto nao encontrado!\n");
}

void Vendas()
{

    menuDeVendas();
}

void menuDeVendas()
{
    char continuar = 's';
    int codigo;
    while(continuar == 's' || continuar == 'S')
    {
        printf("\n\n=====||\ MENU DE VENDAS ||=====\n\n");

        printf("\n  Codigo   Opcao              \n");
        printf("\n  1        Realizar venda           ");
        printf("\n  2        Relatorio de venda          ");
        printf("\n  3        Voltar             \n");

        printf("\nDigite o código para selecionar a opção: ");
        scanf("%d", &codigo);
        getchar();
        switch (codigo)
        {
        case 1:
            Realizarvenda();
            break;
        case 2:
            RelatorioVendas();
            break;
        case 3:
            continuar = 'n';
            break;
        default:
            printf("Opcao invalida, digite novamente!\n");
            break;
        }
    }

}
float formapag_aprazo(float subtotal);
void Realizarvenda()
{
    int i, indiceG2 =0, opc, quantidade, quantidade_estoque, cod = 0;
    float subtotal, valorunit, total;
    char continuar = 's';


    while (continuar == 's' || continuar == 'S')
    {
        Exibir();

        printf("Selecione o Código do produto que deseja vender: ");
        scanf("%i", &cod);
        getchar();

        for (i = 0; i < indiceG; i++)
        {
            if (cod == p[i].Cod)
            {
                valorunit = p[i].Valor;
                quantidade_estoque = p[i].QTDtotal;
                break;  // Encontrou o produto, interrompe o loop
            }
        }

        if (i == indiceG)
        {
            printf("Produto não encontrado.\n");
            return;  // Produto não encontrado, encerra a função
        }

        printf("Valor unitário: %.2f", valorunit);

        printf("\nInforme a quantidade que você quer: ");
        scanf("%d", &quantidade);
        getchar();

        if (quantidade > quantidade_estoque)
        {
            printf("\nSem estoque!!\n");
            return;  // Não há estoque suficiente, encerra a função
        }
        else if (quantidade <= 0)
        {
            printf("\nInsira uma quantidade válida.\n");
            return;  // Quantidade inválida, encerra a função
        }

        // Atualiza a quantidade vendida
        p[i].Vendas += quantidade;
        // Atualiza a quantidade em estoque
        p[i].QTDtotal -= quantidade;

        subtotal += quantidade * valorunit;

        printf("Seu total atualmente e de: %.2f", subtotal);


        cupom_fiscal[indiceG2].quant = quantidade;
        cupom_fiscal[indiceG2].item = p[i].Cod;
        strcpy(cupom_fiscal[indiceG2].nome, p[i].Nome);
        cupom_fiscal[indiceG2].subtotal = subtotal;
        cupom_fiscal[indiceG2].valor_unita = p[i].Valor;

        indiceG2++;

        printf("\nDeseja adicionar mais produto no carrinho ?\n");
        scanf("%c", &continuar);

    }
    printf("\nQual a forma de pagamento que você deseja?\n");
    printf("1 - À vista \t2 - A prazo\n");
    scanf("%d", &opc);
    getchar();
    switch (opc)
    {
    case 1:
        total = formapag_avista(subtotal);
        printf("\nTotal: R$%.2f\n", total);

        CupomFiscal(total, indiceG2);
        break;
    case 2:
        total = formapag_aprazo(subtotal);
        printf("\nTotal: R$%.2f\n", total);

        CupomFiscal(total, indiceG2);

        break;
    default:
        printf("Opção inválida\n");
        break;
    }
    Salvar();
}

float formapag_avista(float subtotal)
{
    float recebido, desconto, troco, descontado;
    char continuar = 's';

    printf("O total foi de %f", subtotal);
    printf("\nInforme a quantidade recebida:\n");
    scanf("%f", &recebido);
    getchar();
    while(recebido < 0)
    {
        printf("\nInforme uma quantidade válida:\n");
        scanf("%f", &recebido);
        getchar();
    }
    /// Calcula o desconto de acordo com o valor total da compra
    if (subtotal <= 50)
    {
        desconto =0.05;
    }
    else if (subtotal > 50 && subtotal < 100)
    {
        desconto = 0.10;
    }
    else
    {
        desconto = 0.18;
    }
    /// Aplica o desconto e atualiza o valor total da compra

    descontado = subtotal * desconto;
    subtotal -= descontado;

    /// Verifica se o valor recebido é suficiente para pagar a compra e calcula o troco
    while (recebido < subtotal)
    {
        printf("\nValor recebido insuficiente. Tente novamente.\n");
        scanf("%f", &recebido);
        getchar();
    }

    /// Mostra ao usuário o desconto aplicado, o valor total da compra e o troco
    if (desconto >= 0.05 && desconto <0.07)
    {
        printf("\nVocê ganhou 5%% de desconto!\n");
    }
    else if (desconto >=0.1 && desconto <0.15)
    {
        printf("\nVocê ganhou 10%% de desconto!\n");
    }
    else
    {
        printf("Você ganhou 18%% de desconto!\n");
    }


    troco = recebido - subtotal;

    printf("============================");
    printf("\nDesconto aplicado: R$%.2f\n", descontado);
    printf("\nValor total: R$%.2f\n", subtotal);
    printf("\nTroco: R$%.2f\n", troco);
    printf("============================");

    return subtotal;
}

float formapag_aprazo(float subtotal)
{
    int parcelas = 0;
    float acrescimo = 0.0;
    while (parcelas <= 0)
    {
        printf("Informe uma quantidade válida de parcelas: ");
        scanf("%d", &parcelas);
        getchar();
    }

    float total = subtotal;

    if (parcelas <= 3)
    {
        printf("O seu acréscimo é de 5%%\n");
        acrescimo = 0.05;
    }
    else if (parcelas > 3)
    {
        printf("O seu acréscimo é de 8%%\n");
        acrescimo = 0.08;
    }

    total = total + (total * acrescimo);

    printf("O total foi de %f\n", total);

    float valorPago;
    printf("Informe o valor pago: ");
    scanf("%f", &valorPago);
    getchar();

    float troco = valorPago - total;

    printf("============================");
    printf("\nAcréscimo: R$%.2f\n", total - subtotal);
    printf("\nValor total: R$%.2f\n", total);
    printf("\nTroco: R$%.2f\n", troco);
    printf("============================");

    return total;


}
void RelatorioVendas()
{
    if (p == NULL)
    {
        Ler();
    }

    printf("\n--- Relatório de Vendas ---\n");
    printf("Cod\tNome\tEstoque\tVendas\n");

    for (int i = 0; i < indiceG; i++)
    {
        printf("%d\t%s\t%d\t%d\n", p[i].Cod, p[i].Nome, p[i].QTDtotal, p[i].Vendas);
    }

    printf("---------------------------\n");
}

void CupomFiscal(float total, int indiceG2)
{
    printf("CUPOM FISCAL\n");
    for (int i = 0; i < indiceG2; i++)
    {
        printf("Item: %d\n",cupom_fiscal[i].item);
        printf("Nome: %s\n", cupom_fiscal[i].nome);
        printf("Quantidade: %d\n", cupom_fiscal[i].quant);
        printf("Preço unitário: R$%.2f\n", cupom_fiscal[i].valor_unita);
        printf("Subtotal: R$%.2f\n\n", cupom_fiscal[i].subtotal);
    }
    printf("Total: R$%.2f\n", total);

}
