#include <stdio.h>
#include <stdlib.h>

//Funções do programa
void secantes(int n, double X0, double X1, int e, int MAXITER,int ind);
void print(double* Xk,double* Fx, double X0, double X1, int max,int ind);


//Inicio
int main() {   
    int n, max, e, ind;
    double x0, x1; 
    
    while (1)
    {
    
    ind++;   
    printf("Para encerar o programa Digite o Grau da funcao como 0\n");
    printf("Digite o grau da funcao: ");
    scanf("%d",&n);
    if(n==0)
        return 0;  
    
    printf("Digite o valor de X0: ");
    scanf("%lf",&x0);
    
    printf("Digite o valor de X1: ");
    scanf("%lf",&x1);

    printf ("Digite o Maxitermo: ");
    scanf("%d",&max);
    
    printf("Digite o erro 'e' talque erro = 10^-e: ");
    scanf("%d",&e);

    secantes(n, x0, x1, e, max, ind);

    }
    
    
    
    return 0;
}


//============================================================
//                  Função de Secantes
//============================================================

void secantes(int n, double X0, double X1, int e, int MAXITER,int ind){

    int F[n];
    int i,j, max;
    double prod= 0, erro; 
    double respX0 = 0,respX1 = 0,X;
    double x[2];
    long int parada;
    double minerro = 1;
    
    //dados para ser printado
    
    double* Xk;
    double* Fx;
    double* Ex;
    

    //Definindo o erro
    for(i=0;i<e;i++){
        minerro = minerro/10;
    }
    

    //Adquirindo Dados 
    printf("Diginte os N termos da equacao em sequencia partindo do ponto\n");
    printf("a + bx + cx^2 + dx^3 .... :\n");
    for (i=0; i<=n; i++){
        scanf("%d",&F[i]);
    }

    //Aplicando o das Secantes
    x[0] = X0;
    x[1]= X1; 
    prod = 0;
    max = 0;
    erro = 0;

    do{      
     max++; 
     respX0 = 0;
     respX1 = 0;


     //Calculando F(X0)
     for (i=0; i<=n; i++){    
         if(i==0){
            respX0 = F[i];
         }else{
             for(j=0; j<i; j++){       
                 if(j==0)
                    prod = x[0];
             
                 if (j!=0){
                    prod = prod*x[0];
                 }
             }
         respX0 = respX0 + F[i]*prod;
        } 
     }


     //Calculando F(X1)
     for (i=0; i<=n; i++){    
        if(i==0){
            respX1 = F[i];
        }else{
             for(j=0; j<i; j++){       
                if(j==0)
                prod = x[1];
             
                if (j!=0){
                prod = prod*x[1];
                 }
             }
        respX1 = respX1 + F[i]*prod;
        } 
     }

     //Alocando os valores na memória para serem escritos  
     if(max==1){
          Xk = malloc(1*sizeof(double));
          Fx = malloc(1*sizeof(double));      
          Ex = malloc(1*sizeof(double));   
     }else{
          Xk = realloc(Xk,max*sizeof(double));            
          Fx = realloc(Fx,max*sizeof(double));  
          Ex = realloc(Ex,max*sizeof(double));
     }

     //Calculando o método de Newton           
     X = ((respX1*x[0]) - (respX0*x[1]))/(respX1 - respX0);
     x[0]= x[1];
     x[1] = X;
     respX1 = 0;

     
     //Calculando para ver se encontrou a raiz
     for (i=0; i<=n; i++){    
        if(i==0){
            respX1 = F[i];
        }else{
             for(j=0; j<i; j++){       
                if(j==0)
                prod = x[1];
             
                if (j!=0){
                prod = prod*x[1];
                 }
             }
        respX1 = respX1 + F[i]*prod;
        } 
     }

     Xk[max-1] = X; 
     Fx[max-1] = respX1;
     Ex[max-1] = erro;
     

     // Se encontrar a raiz de X
     parada = respX1*1000000;
     if (parada == 0){ 
         print(Xk,Fx,X0,X1,max, ind);
         return;
     }


     //Caso não encontre a raiz
     erro = (x[0]-x[1])/x[0];
     if(erro<0)
        erro = -erro;
    
    }while (max<=MAXITER && erro > minerro); 
    
    print(Xk,Fx,X0,X1,max, ind);
    return;
}


//============================================================
//                  Criação do .txt
//============================================================

void print(double* Xk,double* Fx, double X0, double X1, int max,int ind){

    int i; 
    double erro;
    char nome[30]; 
    FILE *pont_arq;
    
    //abrindo o arquivo
    printf("Criando Arquivo...\n");
    sprintf(nome,"Secantes<%d>.txt",ind);
   
    pont_arq = fopen(nome, "w");


    if(pont_arq==NULL){
        printf("Falha ao Gerar o Arquivo");
        return;
    }
  
    //Nome e Numero
    fputs("Vitor Ferreira Paschoal n°11215532 \nWilliam Carrara Orlato n°1180091\n\n",pont_arq);

    //Adicionando os Dados no Arquivo
    fprintf(pont_arq,"x(0) = %.6lf\nx(1) = %.6lf\n\n\n",X0,X1); 
    
    //Escrevendo Xk, Fx e Fx' no aquivo
    fprintf(pont_arq,"      x          Fx         erro\n");
    for(i=0;i<max;i++){
        if(Fx[i]<0)
            Fx[i] = Fx[i]*-1;
        erro = Xk[i]-Xk[max-1];
        if (erro<0)
            erro= -erro;               
        fprintf(pont_arq,"x(%d): %.6lf   %.6lf   %.6lf\n",i+2,Xk[i],Fx[i],erro);
    }
   
    // fechando arquivo
    fclose(pont_arq);

    printf("Arquivo Gerado com Sucesso\n\n\n");
    return;
}