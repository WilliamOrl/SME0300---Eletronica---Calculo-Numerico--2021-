#include <stdio.h>
#include <stdlib.h>


//Funções do programa
void bisection(int n, double A0,double B0,int e, int MAXITER,int ind);
void print(double* Xk,double* Fx, double A0, double B0, int max, int caso, int ind);


//Inicio
int main() {   
    int n = 0, max = 0, e = 0 , ind = 0;
    double a0 = 0, b0 = 0; 
  
   
    while (1)
    {
     ind++;   
     printf("Para encerar o programa Digite o Grau da funcao como 0\n");
     printf("Digite o grau da funcao: ");
     scanf("%d",&n);
     if(n==0)
        return 0;

     printf("Digite o valor de A0: ");
     scanf("%lf",&a0);
    
     printf("Digite o valor de B0: ");
     scanf("%lf",&b0);    
    
     printf ("Digite o Maxitermo: ");
     scanf("%d",&max);
    
     printf("Digite o erro 'e' talque erro = 10^-e: ");
     scanf("%d",&e);

     bisection(n, a0, b0, e, max, ind);
    }
    return 0;
}


//============================================================
//                  Função de Bisseção
//============================================================

void bisection(int n, double A0,double B0,int e, int MAXITER,int ind){

    int F[n];
    int i,j, max;
    double prod= 0, erro; 
    double respA = 0, respB = 0, respx = 0, resp = 0;
    double x[2];
    long int parada;
    double minerro = 1;
    
    //dados para ser printado
    double A,B;
    double* Xk;
    double* Fx;

    A = A0;
    B = B0; 

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


    //Teste da Variavel A
    for (i=0; i<=n; i++){    
        if(i==0){
            respA = F[i];
        }else{
             for(j=0; j<i; j++){       
                if(j==0)
                 prod = A0;
             
                 if (j!=0){
                prod = prod*A0;
                 }
             }
        respA = respA + F[i]*prod;
        } 
    }

    if (respA == 0){
        Fx = malloc(1*sizeof(double));
        Fx[0]= respA;
        print(Xk,Fx,A,B,max,1,ind);
        return;
    }
    

    //Teste da Variavel B
    for (i=0; i<=n; i++){    
        if(i==0){
            respB = F[i];
        }else{
             for(j=0; j<i; j++){       
                if(j==0)
                 prod = B0;
             
                 if (j!=0){
                prod = prod*B0;
                 }
             }
        respB = respB + F[i]*prod;
        } 
    }

    if (respB == 0){
        Fx = malloc(1*sizeof(double));
        Fx[0]= respB;
        print(Xk,Fx,A,B,max,2,ind);
        return;
    }


    // Multiplicando f(a) * f(b)
    resp = respA*respB;
    if(resp>0){
        print(Xk,Fx,A,B,max,0,ind);
        return;
    }


    //Aplicando o método de bisseção
    x[0]= 0, x[1]= 0; 
    prod = 0;
    max = 0;
    erro = 0;

    do{    
         x[1]= x[0];
         max ++;
         x[0] = (A0 + B0)/2;
         
         //Teste da Variavel X 
            for (i=0; i<=n; i++){    
              if(i==0){
              respx = F[i];
              }else{
                 for(j=0; j<i; j++){       
                      if(j==0)
                      prod = x[0];
            
                       if (j!=0){
                         prod = prod*x[0];
                        }
                      }
                 respx = respx + F[i]*prod;
                } 
              }
         
         if(max==1){
            Xk = malloc(1*sizeof(double));            
            Fx = malloc(1*sizeof(double));   
         }else{
            Xk = realloc(Xk,max*sizeof(double));            
            Fx = realloc(Fx,max*sizeof(double));  
         }
         
         Xk[max-1] = x[0];
         Fx[max-1] = respx;
         

        parada = respx*1000000;

         // Se encontrar a raiz de X
         if (parada == 0){ 
             print(Xk,Fx,A,B,max,3,ind);
             return;
         }
        
         //Testando em Relação a A0 
         resp = respx*respA;
         if(resp<0){  // Caso o  A0*x seja menor que 0
            respB = respx;
            B0 = x[0];
         }else{ // Caso o  B0*x seja menor que 0
            respA = respx;
            A0 = x[0];
         }
       
         erro = (x[0]-x[1])/x[0];
    
         if(erro<0)
            erro = -erro;
         
        
    }while (max<=MAXITER && erro > minerro); 
    
    print(Xk,Fx,A,B,max,3,ind);
    return;
}


//============================================================
//                  Criação do .txt
//============================================================

void print(double* Xk,double* Fx, double A0, double B0, int max, int caso, int ind){

    int i;  
    char nome[30];
    FILE *pont_arq;
    
    //abrindo o arquivo
    printf("Criando Arquivo...\n");
    sprintf(nome,"Bissecao<%d>.txt",ind);
   
    pont_arq = fopen(nome, "w");


    if(pont_arq==NULL){
        printf("Falha ao Gerar o Arquivo");
        return;
    }
  
    //Nome e Numero
    fputs("Vitor Ferreira Paschoal n°11215532 \nWilliam Carrara Orlato n°1180091\n\n",pont_arq);

    //Adicionando os Dados no Arquivo
    fprintf(pont_arq,"A0 = %.6lf\nB0 = %.8lf\n\n",A0,B0);
    
    
    switch (caso)
    {
     case (0): //Não há raiz
        fprintf(pont_arq, "Nao ha raiz entre os dois numeros\n");
        break;
    
     case (1): //A0 é raiz
        fprintf(pont_arq, "A0 é a raiz da função\n");
        fprintf(pont_arq,"      x           Fx           erro\n");
        fprintf(pont_arq,"A0: %.6lf  %.8lf   0.00000000\n",A0,Fx[0]);
        break;
    
     case (2): //B0 é raiz
        fprintf(pont_arq, "B0 é a raiz da função\n");
        fprintf(pont_arq,"      x           Fx           erro\n");
        fprintf(pont_arq,"B0: %.6lf  %.6lf   0.000000\n",B0,Fx[0]);
        break;
    
     case (3): //Método da Bisseção
        fprintf(pont_arq,"      x         Fx         erro\n");
        for(i=0;i<max;i++){
            if(Fx[i]<0)
                Fx[i] = Fx[i]*-1;
           fprintf(pont_arq,"x(%d): %.6lf  %.6lf   %.6lf\n",i,Xk[i],Fx[i],Fx[i]-Fx[max]);
        }
        break;
    
    default:
        break;
    }
    
    // fechando arquivo
    fclose(pont_arq);

    printf("Arquivo Gerado com Sucesso\n\n\n");
    return;
}