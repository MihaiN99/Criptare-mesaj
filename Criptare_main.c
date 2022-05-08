#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generare_cheie(int cheie[])
{
    cheie[1] = -99; // valoarea elementului 1
    for(int i=2; i<=128; i++) // parcurg fiecare element din cheie
        if(cheie[i-1] == -10) //daca ajung la -10, trec direct la valoarea 10
            cheie[i] = 10;
        else cheie[i] = cheie[i-1] + 1; // cheia ia valoarea elementului precedent +1
}
void citire_cheie(int cheie[])
{
    FILE *f;
    f = fopen("cheie.txt", "r");
    for(int i=1; i<=128; i++) // parcurg fiecare element
    {
        int x;
        fscanf(f, "%d", &x); // citesc un element din cheie
        cheie[i] = x;
    }
}

void criptare(int cheie[])
{

    char s[100001];
    FILE *f;
    FILE *g;
    if(!(f = fopen("sursa.txt", "r"))) printf("Eroare fisier 1");
    if(!(g = fopen("output.txt", "w"))) printf("Eroare fisier 2");
    while(!feof(f))
    {
        fgets(s,100001,f);
        if(s[0] != NULL) //  daca sirul contine elemente
        {
            for(int i=0; i<strlen(s); i++)
                if(s[i]!='\n') // daca nu-i sfarsit de paragraf
                {
                    int nr = (int) s[i];
                    fprintf(g, "%d", cheie[nr]); // afisez nr corespunzator pozitiei din cheie
                }
                else
                    fprintf(g, " ");
        }
        memset(s, NULL, 10001); // face sirul s null
    }
    fclose(f);
    fclose(g);
}

int to_number(char z, char c) // functie pentru transformarea literei in cifra
{
    int x = (int)(z - '0') * 10 + (int)(c - '0'); // transformam cu ajutorul codului ascii
    return x;
}

void decriptare(int cheie[])
{
    FILE *f;

    f = fopen("output.txt", "r");
    char s[1000001];

    while(!feof(f))
    {
        fgets(s,100001,f);
        if(s[0] != NULL) // daca sirul contine elemente
        {
            int i = 0; // declaram o pozitie
            int nr;
            while(i<strlen(s))
                if(s[i]==' ')
                {
                    printf("\n");
                    i++;
                }
                else
                {
                    if(s[i]=='-') //daca elementul este negativ
                    {
                        nr = to_number(s[i+1], s[i+2]); // il atribuim unui numar
                        nr = -1 * nr; // il inmultim cu -1 pentru a-l face pozitiv
                        i+=3; // incrementam i cu 3, fiindca este format din - si 2 numere
                    }
                    else
                    {
                        nr = to_number(s[i], s[i+1]); // daca numarul este pozitiv, facem acelasi lucru
                        i+=2; // incrementam i cu 2
                    }
                    for(int j=1; j<=128; j++) //  caut in cheie ce pozitie are valoarea numarului
                        if(cheie[j] == nr)
                        {
                            char c = j;
                            printf("%c", c); // afisez elementul cu codul ascii
                        }
                }
            memset(s, NULL, 100001); // face sirul s null
        }
    }
    fclose(f);
}

int main()
{    // program principal + meniu
    int cheie[128];
    char ans;
    int answ;
    int over = 0;
    printf("Doriti sa folosesti cheia generata automat? Y/N\n");
    scanf("%c", &ans);
    if(ans == 'y' || ans == 'Y')
        generare_cheie(cheie);
    else
        citire_cheie(cheie);

    while(over != 1)
    {
        system("cls");
        printf("1.Criptare mesaj\n2.Decriptare mesaj\n3.Exit\n");
        scanf("%d", &answ);
        switch(answ)
        {
        case 1:
            system("cls");
            criptare(cheie);
            printf("\n Mesajul a fost criptat!");
            _getch();
            break;
        case 2:
            system("cls");
            decriptare(cheie);
            _getch();
            break;
        default:
            over = 1;
            break;
        }
    }
    return 0;
}
