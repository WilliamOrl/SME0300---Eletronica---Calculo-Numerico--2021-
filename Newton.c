#include <stdio.h>
#include <stdlib.h>

//Funções do programa
void newton(int n, double X0, int e, int MAXITER, int ind);
void print(double* Xk,double* Fx,double* devFx, double X0, int max, int ind);


//Inicio
int main() {   
    int n, max, e, ind=0;
    double x0; 

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
    
     printf ("Digite o Maxitermo: ");
     scanf("%d",&max);
    
     printf("Digite o erro 'e' talque erro = 10^-e: ");
     scanf("%d",&e);

     newton(n, x0, e, max,ind);
    }

    
    
    return 0;
}


//============================================================
//                  Função de Newton
//============================================================

void newton(int n, double X0, int e, int MAXITER, int ind){

    int F[n];
    int i,j, max;
    double prod= 0, erro; 
    double respdevx = 0, respx = 0;
    double x[2];
    long int parada;
    double minerro = 1;
    
    //dados para ser printado
    
    double* Xk;
    double* Fx;
    double* devFx;
    

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

    //Aplicando o método de Newton
    x[0] = X0;
    x[1]= 0; 
    prod = 0;
    max = 0;
    erro = 0;
    
    do{    
        respx = 0;
        respdevx =0;
        x[1]= x[0];
        max ++;
        
         
        //Calculo do Fx
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

        //Calculo da Derivada de Fx
        for (i=0; i<=n; i++){    
            if(i==0){
            respdevx = 0;
            }else{
                for(j=0; j<i-1; j++){       
                    if(j==0)
                        prod = x[0];
            
                    if (j!=0){
                         prod = prod*x[0];
                    }
                }
                 
                if(i==1){
                        respdevx = F[i];
                }else{
                        respdevx = respdevx + F[i]*prod*(i);       
                }       
              } 
        }


        //Calculando o método de Newton
        x[0] = x[0] - (respx/respdevx);

        //Alocando os valores na memória para serem escritos  
        if(max==1){
            Xk = malloc(1*sizeof(double));
            Fx = malloc(1*sizeof(double));  
            devFx = malloc(1*sizeof(double));               
        }else{
            Xk = realloc(Xk,max*sizeof(double));            
            Fx = realloc(Fx,max*sizeof(double));  
            devFx = realloc(devFx,max*sizeof(double));  
        }
                  
        Xk[max-1] = x[0];
        Fx[max-1] = respx;
        devFx[max-1] = respdevx;
        

        // Se encontrar a raiz de X
        parada = respx*1000000;
        if (parada == 0){ 
            print(Xk,Fx,devFx,X0,max,ind);
            return;
        }


        //Caso não encontre a raiz
        erro = (x[0]-x[1])/x[0];
        if(erro<0)
            erro = -erro;
    
    }while (max<=MAXITER && erro > minerro);
    
    print(Xk,Fx,devFx,X0,max,ind);
    return;
}


//============================================================
//                  Criação do .txt
//============================================================

void print(double* Xk,double* Fx,double* devFx,double X0, int max, int ind){

    int i;  
    char nome[30];
    FILE *pont_arq;
    
    //abrindo o arquivo
    printf("Criando Arquivo...\n");
    sprintf(nome,"Newton<%d>.txt",ind);
   
    pont_arq = fopen(nome, "w");

    if(pont_arq==NULL){
        printf("Falha ao Gerar o Arquivo");
        return;
    }
  
    //Nome e Numero
    fputs("Vitor Ferreira Paschoal n°11215532 \nWilliam Carrara Orlato n°1180091\n\n",pont_arq);

    //Adicionando os Dados no Arquivo
    fprintf(pont_arq,"x(0) = %.6lf\n\n\n",X0); 
    
    //Escrevendo Xk, Fx e Fx' no aquivo
    fprintf(pont_arq,"      x          Fx         Fx'        erro\n");
    for(i=0;i<max;i++){
        if(Fx[i]<0)
            Fx[i] = Fx[i]*-1;
        fprintf(pont_arq,"x(%d): %.6lf   %.6lf   %.6lf   %.6lf\n",i+1,Xk[i],Fx[i],devFx[i],Fx[i]-Fx[max]);
    }
   
    // fechando arquivo
    fclose(pont_arq);

    printf("Arquivo Gerado com Sucesso\n\n\n");
    return;
}