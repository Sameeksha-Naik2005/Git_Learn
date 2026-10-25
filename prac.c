#include <stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<time.h>
#include<mpi.h>


int main(int argc,char **argv){
    int rank,size,a[100],b[100];
    int n=100;
    

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&s);

    if(n%s){
        if(rank==0){
        printf("___");
        }
        MPI_Finalize();
        return 0;
    }
    int k=n/s;
    if(rank==0){
        for(int i=0;i<n;i++)a[i]=i+1;
    }
    MPI_Scatter(a,k,MPI_INT,b,k,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<k;i++)b[i]*=2;
    MPI_Gather(b,k,MPI_INT,a,k,MPI_INT,0,MPI_COMM_WORLD);
    
    if(rank==0){
        for(int i=0;i<n;i++)
        printf(" %d ",a[i]);
    }
    MPI_Finalize();
    return 0;
    

}