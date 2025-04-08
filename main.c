#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void Ucitaj(int *pr, int nn)

int main()
{
    int izbor, n;
    int r[MAX];
    int *pr = &r[0];

    printf("1. unos podataka preko tipkovnice\n2. unos podataka iz datoteke\nOdaberite: ");
    scanf("%d", &izbor);

    if(izbor == 1)
    {
        printf("Koliko elementa zelite ucitati: ");
        scanf("%d", &n);
        Ucitaj(&r[0], n);
    }
    return 0;
}

void Ucitaj(int *pr, int nn)
{
    int i;
    for(i = 0; i < nn; i++)
    {
        scanf("%d", pr+i);
    }
}
