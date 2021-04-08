#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void citire_date_intrare(int ***a, int *m, int *n)
{
    int i,j;
    FILE *f1=fopen("date.in.txt", "r");
    if(f1==NULL)
        {
            printf("Eroare la deschiderea fisierului f1!");
            exit(1);
        }
    fscanf(f1, "%d %d", m, n);
    (*a)=malloc((*m)*sizeof(int *));
    for(i=0;i<(*m);i++)
        (*a)[i]=malloc((*n)*sizeof(int));
    for(i=0;i<(*m);i++)
        for(j=0;j<(*n);j++)
            fscanf(f1, "%d", &(*a)[i][j]);
    fclose(f1);
}

void afisare_date_iesire(int **a, int m, int n)
{
    int i, j;
    FILE *f2 = fopen("date.out.txt", "w");
    if(f2==NULL)
        {
            printf("Eroare la deschiderea fisierului f2!");
            exit(1);
        }
    for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
                fprintf(f2,"%u ", a[i][j]);
            fprintf(f2,"\n");
        }
    fclose(f2);
}



void umplere(int **a, int nr_col, int sus, int jos)
{
    int i,j;
    if(sus==jos)
    {
        int st=-1, dr=-1;
        for(i=0;i<nr_col-1;i++)
            if(a[sus][i]==1&&a[sus][i+1]==0) //daca avem 1 si 0 am gasit stanga
            {
                st=i+1;
                break;
            }
        for(i=st;i<nr_col-1;i++)
           if(a[sus][i]==0&&a[sus][i+1]==1) //daca am gasit un interval de forma 0 si 1 am gasit dreapta
            {
                dr=i;
                break;
            }
        if(st>0&&dr>=st) //daca avem stanga si dreapta umplem cu 1 - uri
           for(i=st;i<=dr;i++)
                a[sus][i]=1;
    }
    else if(sus<jos) //daca nu am ajuns la linia din mijlocul matricei continuam sa impartim
    {
        int m=(sus+jos)/2;
        umplere(a,nr_col,sus,m);
        umplere(a,nr_col,m+1,jos);
    }
    else return;
}

int main()
{
    int M, N, i, j;
    int **a;
    citire_date_intrare(&a,&M,&N);
    //clock_t start = 0, end = 0;
    //double cpu_time_used;
    //start = clock();
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    umplere(a, N, 0, M-1);
    //end = clock();
    //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-7;
    printf("Time measured: %.25f seconds.\n", elapsed);
    afisare_date_iesire(a,M,N);
    for(i=0;i<M;i++)
        free(a[i]);
    free(a);
    //printf("%.25f", cpu_time_used);
    printf("Program compiled succesfully!");
    return 0;
}
