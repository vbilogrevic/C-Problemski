#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
 
#define MAX 100 
 
void Ucitaj(float *pr, int nn); // Prototip funkcije  za ucitavanje izmjerenih rezultata 
float Aritmeticka(float *pr, int nn); // Prototip funkcije za racunanje aritmeticke sredine 
float Standarna(float *pr, int nn, float arit); // Prototip funkcije za racunanje standardne devijacije 
void Ispisdat(FILE *pOpen, float arit, float apso, float rela, float post, float stand, float rasopm, float rasop2); // Funkcija za 

 
int main(void) 
{ 
    // Definicija varijabli 
    int n; 
    float rn, arit, apso, rela, post, stand, rsopm, rsop2; 
 
    // Definicija polja i inicijalizacija pokazivaca na prvu prvu adresu polja 
    float r[MAX]; 
    float *pr = &r[0]; 
 
    FILE *pOpen = fopen("rezultati.txt", "w"); 
    if(pOpen == NULL) 
    { 
        printf("Greska pri otvaranju!\n"); 
        exit(1); 
    } 
 
    // Komunikacija s korisnikom i unos nazivne vrijednosti otpornika 
    do{ 
        printf("Nazivna vrijednost otpornika (Rn) u Ohmima: "); 
        scanf("%f", &rn); 
        if(rn <= 0) 
            printf("Vrijednost ne moze biti 0 ili negativan broj\n"); 
    }while(rn <= 0); 
 
    printf("\nBroj mjerenja je ogranicen na 100!\n"); 
 
    // Komunikacija s korisnikom i unos broja mjerenja 
    do{ 
        printf("Broj mjerenja (n): "); 
        scanf("%d", &n); 
        if(n > MAX || n < 1) 
            printf("Unijeli ste neogovarajuci broj mjerenja, ponovite!\n"); 
    }while(n > MAX || n < 1); 
 
 
    Ucitaj(&r[0], n); // Poziv funkcija za ucitavananje izmjerenih vrijednosti 
    arit = Aritmeticka(&r[0], n); // Funkcija za racunanje aritmeticke sredine 
    apso = fabs(rn - arit); // Racunanje apsolutne pogreske mjerenja 
    rela = apso / rn; // Racunanje relativne pogreske mjerenja 
    post = rela * 100; // Racunanje postotne pogreske mjerenja 
    stand = Standarna(&r[0], n, arit); // Varijabli stand se prirodaje vrijednost izracunata funkcijom standardne devijacije 
    rsopm = stand / arit; // Racunanje relativno standardno odstupanje pojedinacnih mjerenja (koeficijent) 
    rsop2 = rsopm * 100; // Racunanje relativno standardno odstupanje pojedinacnih mjerenja (postotak) 
     
    printf("\n"); 
     
    // Komunikacija s korisnikom i ispis dobivenih vrijednosti na zaslon 
    printf("R-= %.2f mOhm = %.4f ohm\n", arit*1000, arit);  
    printf("pa= %.2f mOhm = %.4f ohm\n", apso*1000, apso); 
    printf("p= %.4f\n", rela);  
    printf("p%= %.2f %%\n", post); // Ispis u datoteku 
    printf("s= %.2f mOhm = %.7f\n", stand*1000, stand);  
    printf("vc= %.5f\n", rsopm);  
    printf("s%= %.3f %%\n", rsop2);  
 
    Ispisdat(pOpen, arit, apso, rela, post, stand, rsopm, rsop2); // Poziv funkcije za ispis u datoteku 
    fclose(pOpen); 
 
    printf("\nPritisnite enter za izlaz...");
    getchar();
    getchar();
 
    return 0; 
} 
 
// Funkcija za ucitavananje izmjerenih vrijednosti 
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
 
// Funkcija za racunanje aritmeticke sredine 
float Aritmeticka(float *pr, int nn) 
{ 
    float suma = 0; 
    int i; 
    for(i = 0; i < nn; i++) 
        suma += *(pr+i); 
    return suma / nn; 
} 
 
// Funkcija za racunanje standardne devijacije 
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
 
// Funkcija za ispit u datoteku 
void Ispisdat(FILE *pOpen, float arit, float apso, float rela, float post, float stand, float rsopm, float rsop2) 
{ 
    fprintf(pOpen, "R-= %.2f mOhm = %.4f ohm\n", arit*1000, arit); // Ispis u datoteku 
    fprintf(pOpen, "pa= %.2f mOhm = %.4f ohm\n", apso*1000, apso); // Ispis u datoteku 
    fprintf(pOpen, "p= %.4f\n", rela); // Ispis u datoteku 
    fprintf(pOpen, "p%= %.2f %%\n", post); // Ispis u datoteku 
    fprintf(pOpen, "s= %.2f mOhm = %.7f\n", stand*1000, stand); // Ispis u datoteku 
    fprintf(pOpen, "vc= %.5f\n", rsopm); // Ispis u datoteku 
    fprintf(pOpen, "s%= %.3f %%\n", rsop2); // Ispis u datoteku 
}
