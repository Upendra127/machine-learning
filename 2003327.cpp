#include <iostream>
#include<fstream>
#include<limits.h>
#include<stdio.h>
using namespace std;

int main() {

//In this loop that we have written down we are using file handling to get input into the file.
    int M, N;
    ifstream input;
    input.open("input.txt",ios::in);
    input>>M>>N; // taking input into the file.
    int A[M][N];
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        input>>A[i][j];
    }

    input.close();
//We are going to calculate the sub matrix in  this code.
    int submatrix[M][N], sum;
    for(int i=0; i<M; i++)
    {
        sum=0; // intialising the variable.
        for(int j=N-1; j>=0; j--)
        {
            sum = sum + A[i][j]; //using the series sum logic here for the sum.
            submatrix[i][j] = sum;
        }
    }
//This particular code block we are using to calculate T and Ts
    int T[M][2*N], Ts[M][N], sum2 = INT_MAX, index;
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            T[i][2*j+1] = N-1;
        }
    }

    for(int j=0; j<N; j++)
    {
        sum2 = 0;
        for(int i=0; i<M; i++)
        {
           int index;
           if(submatrix[i][j] + sum2 < submatrix[i][j])
           sum2 = sum2 + submatrix[i][j];
           else
           {
               sum2 = submatrix[i][j];
               index = i;
           }

           T[i][2*j] = index;
           Ts[i][j] = sum2;
        }
    }
//Here we are declaring the sub matrix for part 3 and part 4.

    sum=0;
    int N_submatrix[N][M][N];

    for(int k=0; k<N; k++)
    {
        for(int i=0; i<M; i++)
        {
            for(int j=0; j<N; j++)
            N_submatrix[k][i][j] = 0;
        }
    }
    for(int k=0; k<N; k++)
    {
        for(int i=0; i<M; i++)
        {
            for(int j=k; j>=0; j--)
            {
                sum = sum + A[i][j];
                N_submatrix[k][i][j] = sum;
            }
            sum = 0;
        }
    }
//calculating S and s

    sum=0;
    int S[M][2*N], N_min = INT_MAX, l_final, s=INT_MAX, min = INT_MAX;
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            for(int k=j; k<N; k++)
            {
                for(int l=i; l>=0; l--)
                {
                    sum = sum + N_submatrix[k][l][j];
                    if(sum<min)
                    {
                        min = sum;
                        l_final = l;
                    }
                }

                if(N_min>min)
                {
                    S[i][2*j] = l_final;
                    S[i][2*j+1] = k;
                    N_min = min;
                }
                sum = 0;
                min = INT_MAX;
            }
            if(s>N_min)
            s = N_min;
            N_min = INT_MAX;
        }
    }

//This will get us write the thing in output file

    ofstream output;
    output.open("output.txt",ios::out);

//we will print through this

    output<<M<<"  "<<N<<printf("\n");
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        output<<T[i][2*j]<<','<<T[i][2*j+1]<<"  ";
        output<<printf("\n");
    }
    output<<"--   --    --    --    --    --    -"<<printf("\n");

//Printing Ts

    output<<M<<"  "<<N<<printf("\n");
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        output<<Ts[i][j]<<"  ";
        output<<printf("\n");
    }
    output<<"--   --    --    --    --    --    -"<<printf("\n");

//Printing S

    output<<M<<"  "<<N<<printf("\n");
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        output<<S[i][2*j]<<','<<S[i][2*j+1]<<"  ";
        output<<printf("\n");
    }
    output<<"-   --    --    --    --    --    -"<<printf("\n");

//Printing s

    output<<s;

    output.close();

    return 0;
}
