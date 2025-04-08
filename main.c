#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
 
#define MAX 100 
 
void Ucitaj(float *pr, int nn); 
float Aritmeticka(float *pr, int nn); 
float Standarna(float *pr, int nn, float arit); 
void Ispisdat(FILE *pOpen, float arit, float apso, float rela, float post, float stand, float rasopm, float rasop2); 

 
int main(void) 
{ 
    int n; 
    float rn, arit, apso, rela, post, stand, rsopm, rsop2; 
 
    float r[MAX]; 
    float *pr = &r[0]; 
 
    FILE *pOpen = fopen("rezultati.txt", "w"); 
    if(pOpen == NULL) 
    { 
        printf("Greska pri otvaranju!\n"); 
        exit(1); 
    } 
 
 
    do{ 
        printf("Nazivna vrijednost otpornika (Rn) u Ohmima: "); 
        scanf("%f", &rn); 
        if(rn <= 0) 
            printf("Vrijednost ne moze biti 0 ili negativan broj\n"); 
    }while(rn <= 0); 
 
    printf("\nBroj mjerenja je ogranicen na 100!\n"); 
 
    
    do{ 
        printf("Broj mjerenja (n): "); 
        scanf("%d", &n); 
        if(n > MAX || n < 1) 
            printf("Unijeli ste neogovarajuci broj mjerenja, ponovite!\n"); 
    }while(n > MAX || n < 1); 
 
 
    Ucitaj(&r[0], n); 
    arit = Aritmeticka(&r[0], n);
    apso = fabs(rn - arit); 
    rela = apso / rn; 
    post = rela * 100; 
    stand = Standarna(&r[0], n, arit); 
    rsopm = stand / arit; 
    rsop2 = rsopm * 100; 
     
    printf("\n"); 
     
    
    printf("R-= %.2f mOhm = %.4f ohm\n", arit*1000, arit);  
    printf("pa= %.2f mOhm = %.4f ohm\n", apso*1000, apso); 
    printf("p= %.4f\n", rela);  
    printf("p%= %.2f %%\n", post); 
    printf("s= %.2f mOhm = %.7f\n", stand*1000, stand);  
    printf("vc= %.5f\n", rsopm);  
    printf("s%= %.3f %%\n", rsop2);  
 
    Ispisdat(pOpen, arit, apso, rela, post, stand, rsopm, rsop2);
    fclose(pOpen); 
 
    printf("\nPritisnite enter za izlaz...");
    getchar();
    getchar();
 
    return 0; 
} 
 

void Ucitaj(float *pr, int nn) 
{ 
    int i; 
    printf("\nUnesite mjerne rezultate (Ri) u mOhmima\n"); 
    for(i = 0; i < nn; i++) 
    { 
        printf("%d. element: ", i+1); 
        scanf("%f", pr + i); 
        *(pr+i) = *(pr+i) / 1000; 
        while(*(pr+i) < 0) 
        { 
            printf("Pogresan unos "); 
            scanf("%f", pr+i); 
            *(pr+i) = *(pr+i) / 1000;
                    } 
    } 
} 
 

float Aritmeticka(float *pr, int nn) 
{ 
    float suma = 0; 
    int i; 
    for(i = 0; i < nn; i++) 
        suma += *(pr+i); 
    return suma / nn; 
} 
 

float Standarna(float *pr, int nn, float arit) 
{ 
    float suma = 0; 
    int i; 
    for(i = 0; i < nn; i++) 
    { 
        suma += pow((*(pr+i) -  arit), 2); 
    } 
    float ss = sqrt(suma/(nn-1)); 
    return ss; 
} 
 

void Ispisdat(FILE *pOpen, float arit, float apso, float rela, float post, float stand, float rsopm, float rsop2) 
{ 
    fprintf(pOpen, "R-= %.2f mOhm = %.4f ohm\n", arit*1000, arit); 
    fprintf(pOpen, "pa= %.2f mOhm = %.4f ohm\n", apso*1000, apso); 
    fprintf(pOpen, "p= %.4f\n", rela); 
    fprintf(pOpen, "p%= %.2f %%\n", post); 
    fprintf(pOpen, "s= %.2f mOhm = %.7f\n", stand*1000, stand); 
    fprintf(pOpen, "vc= %.5f\n", rsopm); 
    fprintf(pOpen, "s%= %.3f %%\n", rsop2); 
}
