/*
ID: daniel25
TASK: concom
LANG: C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NCOM 101

int owns[NCOM][NCOM];
int controls[NCOM][NCOM];


void
addcontroller(int i, int j)
{
    int k;

    if(controls[i][j])
        return;

    controls[i][j] = 1;


    for(k=0; k<NCOM; k++)
        owns[i][k] += owns[j][k];


    for(k=0; k<NCOM; k++)
        if(controls[k][i])
            addcontroller(k, j);


    for(k=0; k<NCOM; k++)
        if(owns[i][k] > 50)
            addcontroller(i, k);
}


void
addowner(int i, int j, int p)
{
    int k;


    for(k=0; k<NCOM; k++)
        if(controls[k][i])
            owns[k][j] += p;


    for(k=0; k<NCOM; k++)
        if(owns[k][j] > 50)
            addcontroller(k, j);
}

int
main()
{
    FILE *fin, *fout;
    int i, j, n, a, b, p;

    fin = fopen("concom.in", "r");
    fout = fopen("concom.out", "w");
    assert(fin != NULL && fout != NULL);

    for(i=0; i<NCOM; i++)
        controls[i][i] = 1;

    fscanf(fin, "%d", &n);
    for(i=0; i<n; i++) {
        fscanf(fin, "%d %d %d", &a, &b, &p);
        addowner(a, b, p);
    }

    for(i=0; i<NCOM; i++)
        for(j=0; j<NCOM; j++)
            if(i != j && controls[i][j])
                fprintf(fout, "%d %d\n", i, j);

    exit(0);
}