#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100
//TRABALHO CRIPTOGRAFIA E DECRIPTOGRAFIA

void matriz_a(int matriz[2][2]);
void carac_para_num(char frase[],int vet[],int *tamanho);
void frase_para_matriz(int matriz_inteiros[2][MAX],int tamanho, int vet[]);
void matriz_para_frase(int matriz_decodif[2][50],int tamanho, int vet_decodif[]);
void num_para_carac(char frase[],int vet_decodif[],int *tamanho);

int main()
{
    char frase[MAX];
    int tamanho=0,vet[MAX], i, j, determinante, inteiros, matriz_inv[2][2], matriz[2][2], matriz_codif[2][50], k, matriz_inteiros[2][MAX], matriz_decodif[2][50], vet_decodif[MAX];

    // Para escrever a frase.
    printf("Digite uma frase: ");
    fgets(frase,MAX,stdin);
    frase[strcspn(frase,"\n\r")]=0;

     // Troca caracteres por inteiros
    carac_para_num(frase,vet,&tamanho);

    // Colocar a frase dentro de uma matriz 2xMAX.
    frase_para_matriz(matriz_inteiros,tamanho,vet);
    printf("\n");

    srand(time(NULL));

    // Gerando a matriz A e sua inversa
        do{

    // Chamamento da função da matriz A
    matriz_a(matriz);

    // Cálculo do determinante
    determinante = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);

        if(determinante != 0 && matriz[0][0] % determinante == 0 && matriz[0][1] % determinante == 0 && matriz[1][0] % determinante == 0 && matriz[1][1] % determinante == 0){
            inteiros = 1;
        }
        else{
            inteiros = 0;
        }
    }while(inteiros == 0);

        // Formação da matriz inversa
        matriz_inv[0][0] =  matriz[1][1]/determinante;
        matriz_inv[0][1] = -matriz[0][1]/determinante;
        matriz_inv[1][0] = -matriz[1][0]/determinante;
        matriz_inv[1][1] =  matriz[0][0]/determinante;

    // Impressão da Matriz A
    printf("Matriz A:\n");
    for(i=0; i<2; i++){
        for(j=0; j<2; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Impressão da matriz inversa
    printf("Matriz inversa de A:\n");
    for(i=0; i<2; i++){
        for(j=0; j<2; j++){
            printf("%d ", matriz_inv[i][j]);
        }
        printf("\n");
    }

    // Multiplicação da matriz A pela matriz de caracteres
    printf("\n");
    for(i=0; i<2; i++){
        for(j=0; j<tamanho/2; j++){
            matriz_codif[i][j] = 0;
            for(k=0; k<2; k++){
                matriz_codif[i][j] += matriz[i][k] * matriz_inteiros[k][j];
            }
        }
    }
    printf("Criptografia:\n");
    for(i=0; i<2; i++){
        for(j=0; j<tamanho/2; j++){
            printf("%d ", matriz_codif[i][j]);
        }
        printf("\n");
    }

    for(i=0; i<2; i++){
        for(j=0; j<tamanho/2; j++){
            matriz_decodif[i][j] = 0;
            for(k=0; k<2; k++){
                matriz_decodif[i][j] += matriz_inv[i][k] * matriz_codif[k][j];
            }
        }
    }
    printf("\nDecriptografia:\n");

    for(i=0; i<2; i++){
        for(j=0; j<tamanho/2; j++){
            printf("%d ", matriz_decodif[i][j]);
        }
        printf("\n");
    }

    matriz_para_frase(matriz_decodif,tamanho,vet_decodif);

    num_para_carac(frase,vet_decodif,&tamanho);


    return 0;
}

// Função para criação da matriz A
void matriz_a(int matriz[2][2]){
    int i, j;

    // São pegos os numeros aleatorios menores que 500.
    for(i=0; i<2; i++){
        for(j=0; j<2; j++){
            matriz[i][j] = rand() % 500;
        }
    }
}

// Funçao de troca de caracteres para numeros.
void carac_para_num(char frase[],int vet[],int *tamanho){
    int i;
    // Faz o tamanho receber a quantidade de letras da frase.
    (*tamanho)=strlen(frase);
    printf("Tamanho inicial: %d\n",*tamanho);

    // Troca os vazios por espaco.
    for( i=0; i<(*tamanho); i++){
        if(frase[i] == ' '){
            frase[i] = '#';
        }
    }

    // Caso o numero de caracteres for impar, adiciona um hashtag no final para ficar par.
    if((*tamanho) % 2 == 1){
        frase[(*tamanho)]='#';
        (*tamanho)++;
    }

    printf("Tamanho: %d\n",*tamanho);
    printf("Frase com #: %s\n",frase);

    // Letras minusculas para maiusculas.
    for(i=0;i<*tamanho;i++){
        if((frase[i])>='a' && (frase[i])<='z'){
            frase[i]= toupper(frase[i]);
        }
    }
    printf("\n");

    // Transforma letras em numeros.
    for(i=0;i<*tamanho;i++){
        if(frase[i]!=',' && frase[i]!='#' && frase[i]!='.'){
            vet[i]=(frase[i]) - 64;
        }
    }
    printf("\n");

    // Transformar '.','#' e ',' em numeros.
    for(i=0;i<*tamanho;i++){
        switch(frase[i]){
            case '.':
                vet[i]=27;
                break;
            case '#':
                vet[i]=29;
                break;
            case ',':
                vet[i]=28;
                break;
            default:
                break;
        }
    }

    // Mostra o que tem dentro de vet[].
    printf("Caracteres convertidos para numeros:\n");
    for(i=0;i<*tamanho;i++){
        printf("%d ",vet[i]);
    }
}

// Função matriz dos caracteres
void frase_para_matriz(int matriz_inteiros[2][MAX],int tamanho,int vet[]){
    int i,j,k;

    printf("\n");

    k=0;
    printf("\nMatriz dos caracteres convertidos em numeros:\n");
    for(i=0;i<2;i++){
        for(j=0;j<(tamanho/2);j++){
            matriz_inteiros[i][j] = vet[k];
            k++;
            printf("%d ", matriz_inteiros[i][j]);
        }
        printf("\n");
    }
}

//Função matriz para frase.
void matriz_para_frase(int matriz_decodif[2][50],int tamanho,int vet_decodif[]){
    int i,j,k;

    //Transforma matriz em vetor.
    k=0;
    for(i=0;i<2;i++){
        for(j=0;j<(tamanho/2);j++){
            vet_decodif[k] = matriz_decodif[i][j];
            k++;
        }
    }
    printf("\nFrase no vetor:\n");

    //Mostra o vetor.
    for(k=0;k<tamanho;k++){
        printf("%d ",vet_decodif[k]);
    }
}
//Função numeros para caracteres.
void num_para_carac(char frase_decodif[],int vet_decodif[],int *tamanho){
    int i;

    // Transforma numeros em '.','#' e ','.
    for(i=0;i<*tamanho;i++){
        switch(vet_decodif[i]){
            case 27:
                frase_decodif[i]='.';
                break;
            case 29:
                frase_decodif[i]='#';
                break;
            case 28:
                frase_decodif[i]=',';
                break;
            default:
                break;
        }
    }

    // Transforma numeros em letras.
    for(i=0;i<*tamanho;i++){
        if(vet_decodif[i]!=27 && vet_decodif[i]!=28 && vet_decodif[i]!=29){
            frase_decodif[i]=vet_decodif[i] + 64;
        }
    }
    printf("\n");

     // Troca os vazios por espaco.
    for( i=0; i<(*tamanho); i++){
        if(frase_decodif[i] == '#'){
            frase_decodif[i] = ' ';
        }
    }

    for(i=0;i<*tamanho;i++){
        if((frase_decodif[i])>='a' && (frase_decodif[i])<='z' && frase_decodif[i]){
            frase_decodif[i]= toupper(frase_decodif[i]);
        }
    }

    printf("\nFrase inicial:\n");
    //Mostra a frase inicial.
    for(i=0;i<*tamanho;i++){
        printf("%c",frase_decodif[i]);
    }
}
