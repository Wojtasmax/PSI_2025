#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int ok; //sluzy do sprawdzania co zwraca scanf, jak rowniez jako zmienna pomocnicza w funkcji fact
int fact(int n, int k){
    ok=1;
    for(int i=n;i>n-k;i--){
        ok*=i;
    }
    return ok;
}
void diff(double polynomial[],int degree, int order){
    //post factum by uniknac tylu ifow lepiej by bylo kosztem pamieci zroczniczkowany wielomian wprowadzic do osobnej tablicy
    int factorial=fact(degree,order);
    if(degree>order){
        printf("%0.10gx^%d",polynomial[0]*factorial,degree-order);
        for(int i=1;i<degree-order;i++){
            factorial*=degree-i-order+1;
            factorial/=degree-i+1;
            if(polynomial[i]){
                if(polynomial[i]>0){
                    if(degree-i-order!=1){
                        printf("+%0.10gx^%d",polynomial[i]*factorial,degree-i-order);
                    }else{
                        printf("+%0.10gx",polynomial[i]*factorial);
                    }
                }else{
                    if(degree-i-order!=1){
                        printf("%0.10gx^%d",polynomial[i]*factorial,degree-i-order);
                    }else{
                        printf("%0.10gx",polynomial[i]*factorial);
                    }
                }
            }
        }
        if(polynomial[degree-order]){
            factorial/=order+1;
            if(polynomial[degree-order]>0){
                printf("+%0.10g",polynomial[degree-order]*factorial);
            }else{
                printf("%0.10g",polynomial[degree-order]*factorial);
            }
        }
    }else if(degree==order){
        printf("staly %0.10g",polynomial[0]*factorial);
    }else printf("staly 0"); 
}
void integ(double polynomial[],double stala[],int degree, int order){
    int factorial=fact(degree+order,order);
    printf("%0.10gx^%d",polynomial[0]/factorial,degree+order);
    for(int i=1;i<=degree;i++){
        factorial/=degree-i+order+1;
        factorial*=degree-i+1;
        if(polynomial[i]){
            if(polynomial[i]>0){
                if(degree-i+order==1){
                    printf("+%0.10gx",polynomial[i]/factorial);
                }else if(degree-i+order==0){
                    printf("+%0.10g",polynomial[i]/factorial);
                }else{
                    printf("+%0.10gx^%d",polynomial[i]/factorial,degree-i+order);
                }
            }else{
                if(degree-i+order==1){
                    printf("%0.10gx",polynomial[i]/factorial);
                }else if(degree-i+order==0){
                    printf("%0.10g",polynomial[i]/factorial);
                }else{
                    printf("%0.10gx^%d",polynomial[i]/factorial,degree-i+order);
                }
            }
            
        }
    }
    for(int i=0;i<order-1;i++){
            factorial/=order-i;
        if(stala[i]){
            if(stala[i]>0){
                if(order-i-1!=1){
                    printf("+%0.10gx^%d",stala[i]/factorial,order-i-1);
                }else{
                    printf("+%0.10gx",stala[i]/factorial);
                }
            }else{
                if(order-i-1!=1){
                    printf("%0.10gx^%d",stala[i]/factorial,order-i-1);
                }else{
                    printf("%0.10gx",stala[i]/factorial);
                }
            }
            
        }
    }
    if(stala[order-1]){
        if(stala[order-1]>0){
            printf("+%0.10g",stala[order-1]);
        }else{
            printf("%0.10g",stala[order-1]);
        }
    }
}
void error(int type){
    switch(type){
        case 1:
            printf("Wprowadzono niewlasciwy typ danych. Oczekiwano liczby. Prosze sprobowac ponownie:\n");
            break;
        case 2:
            printf("Wprowadzono niewlasciwy typ danych. Oczekiwano 0 lub 1. Prosze sprobowac ponownie:\n");
            break;
        case 3:
            printf("Wprowadzono niewlasciwy typ danych. Oczekiwano liczby calkowitej. Prosze sprobowac ponownie:\n");
            break;
        case 4:
            printf("Wprowadzono niewlasciwy typ danych. Prosimy wprowadzic liczbe nieujemna:\n");
            break;
        case 5:
            printf("Wprowadzono niewlasciwy typ danych. Prosimy wprowadzic liczbe mniejsza rowna 100: ");
        default:
            printf("Do tego dojsc nie powinno. Gratulacje hakerze.\n");
    }
}
void rightscan(int *m){
    //ten scan pozwala na przyjmowanie tylko liczb
    ok=scanf("%d",m);
    while (ok == 0) {
        error(1);
        while (getchar() != '\n');
        ok = scanf("%d", m);
    }
}
void printPoly(double tab[],int n){
    if(n>=2){
    printf("%0.10gx^%d",tab[0],n);
    for(int i=1;i<n;i++){
        if(tab[i]){
            if(tab[i]>0){
                printf("+%0.10gx^%d",tab[i],n-i);
            }else{
                printf("%0.10gx^%d",tab[i],n-i);
            }
        }
    }
    if(tab[n]>0){
            printf("+%0.10g\n",tab[n]);
    }else if(tab[n]<0){
            printf("%0.10g\n",tab[n]);
    }        
    }else if(n==1){
        if(tab[1]>0){
            printf("%0.10gx+%0.10g\n",tab[0],tab[1]);
        }else if(tab[1]<0){
            printf("%0.10gx%0.10g\n",tab[0],tab[1]);
        }else{
            printf("%0.10gx\n",tab[0]);
        }
    }else{
        printf("%0.10g\n",tab[0]);
    }
}
void scanArray(double tab[],int n){
    for(int i=0;i<n;i++){
    ok=scanf("%lf",&tab[i]);
    while (ok == 0) {
    error(1);
    while (getchar() != '\n');
    ok = (scanf("%lf", &tab[i])); }
    }
}
int main(){
    int deg,pick,order; //odpowiednio: stopien wielomianu, wybor rozniczkowania czy calkowania, "rzad" rozniczkowania badz calkowania
    printf("Prosze podac stopien wielomianu: ");
    rightscan(&deg);
    while(deg>100||deg<0){
        if(deg>100){
            error(5);
        }else{
            error(4);
        }
        rightscan(&deg);
    }
    double poly[deg+1];
    while (getchar() != '\n');
    printf("Prosze podac kolejne wspolczynniki wielomianu: "); scanArray(poly,deg+1);
    printf("Prosze wybrac rodzaj operacji, 1- by rozniczkowac, 0- by calkowac: "); rightscan(&pick);
    while((pick!=1)&&(pick!=0)){
        error(2);
        rightscan(&pick);
    }
    if(!pick){
        printf("Prosze podac ilosc calkowan: ");
            rightscan(&order);  
        while(order<0){
            error(4);
            rightscan(&order);   
        }
        double stala[order];
        printf("Prosze podac kolejne stale calkowania: ");
        scanArray(stala,order);
        printf("Calkujemy wielomian: "); printPoly(poly,deg);
        printf("Otrzymujemy wielomian: "); integ(poly,stala,deg,order);
    }else {
        printf("Prosze podac rzad pochodnej: ");
        rightscan(&order);
        while(order<0){
            error(4);
            rightscan(&order);   
        }
        printf("Rozniczkujemy wielomian "); printPoly(poly,deg);
        printf("Otrzymujemy wielomian "); diff(poly,deg,order);
        //koniec :)
        //3*3727n2'u;f[3z.e]$false return \][[]]
    }
}