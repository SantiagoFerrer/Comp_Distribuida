#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define quantidadeTaylor 1000


int main(int argc, char **argv){
        int *comecoLocal, *fimLocal, quantidadeLocal;
        int idProcesso, quantidadeProcessos;
        double resultadoLocal = 0, resultadoTotal = 0;
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&quantidadeProcessos);
        MPI_Comm_rank(MPI_COMM_WORLD,&idProcesso);
        quantidadeLocal = quantidadeTaylor/quantidadeProcessos;
        comecoLocal = calloc(1,sizeof(MPI_INT));
        fimLocal = calloc(1,sizeof(MPI_INT));
        if(idProcesso == 0){
                for (int i = 1; i < quantidadeProcessos; i++){
                        int comeco = quantidadeLocal * i;
                        int fim = quantidadeLocal + comeco;
                        if (fim > 1000){
                                fim = 1000;
                        }
            MPI_Send(&comeco, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&fim, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
                *comecoLocal = quantidadeLocal * idProcesso + 1;
                *fimLocal = quantidadeLocal + *comecoLocal;
        }
        else{
                MPI_Recv(comecoLocal, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(fimLocal, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for (int t = *comecoLocal; t <= *fimLocal; t++)
        {
                double n = t;
                resultadoLocal += 1/n;
        }

    MPI_Send(&resultadoLocal, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

        if(idProcesso == 0){
                resultadoTotal = resultadoLocal;
                for(int i = 1; i < quantidadeProcessos; i++){
                        MPI_Recv(&resultadoLocal, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        resultadoTotal += resultadoLocal;
                }
                printf("Resultado da série de Taylor com %d elementos: %f", quantidadeTaylor, resultadoTotal);
        }
        MPI_Finalize();
        return 0;
}
