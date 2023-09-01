#include<stdio.h>
#include<stdlib.h>

//Since we are calculating matrix determinants in this file we are assuming all matrices are Square
void freeMatrix(int** matrix,int n);

int** createMatrix(FILE* fp, int dim){
    int** matrix = malloc(sizeof(int*)*dim); //matrix is just an array of pointers to arrays
    for(int i = 0;i < dim;i++){
        int* temp = malloc(sizeof(int)*dim); //for each index of ptr array (rows), allocate an equal size array for columns
        for(int j = 0;j < dim;j++){
            int num;
            fscanf(fp,"%d\t",&num); //Scan in value from file
            temp[j] = num;
        }
        matrix[i] = temp;
        fscanf(fp,"\n"); //Skip over newline character
    }
    return matrix;
}


void printMatrix(int** arr, int dim){
    for(int i = 0;i < dim;i++){
        for(int j = 0;j < dim;j++){
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }
}

int** getSubMatrix(int** origMatrix,int n,int rowToDel,int colToDel){ //n is dimension of original matrix
    //Need to be able to get submatrix by deletign ith and jth row and column for determinant calculations
    int** subMatrix = malloc(sizeof(int*)*(n-1));
    int currRow = 0;
    int currCol = 0;
    for (int i = 0;i < n;i++){
        int* row = malloc(sizeof(int)*(n-1));
        for(int j = 0;j < n;j++){
            if(j != colToDel){
                row[currCol] = origMatrix[i][j];
                currCol = currCol+1;
            }
        }
        if(i != rowToDel){
            subMatrix[currRow] = row;
            currRow = currRow+1;
        }
        else{
            free(row);
        }
        currCol = 0;
    }

    return subMatrix;
}


int getDeterminant(int** matrix,int n){
    if (n==1){
        return matrix[0][0];
    }
    if (n==2){
        int ad = matrix[0][0]*matrix[1][1];
        int bc = matrix[0][1]*matrix[1][0];
        return (ad-bc);
    } //These are our base cases
    else{
        int determinant = 0;
        int sign = 1;
        int* changeSign = &sign;
        for(int i = 0;i < n;i++){
            int coeff = matrix[0][i];
            int** subMatrix = getSubMatrix(matrix,n,0,i);
            int term = sign*getDeterminant(subMatrix,n-1)*coeff;
            determinant = determinant+term;
            *changeSign = *changeSign * (-1);
            freeMatrix(subMatrix,n-1);
        }
        return determinant;
    }
}

void freeMatrix(int** matrix, int n){
    for(int i = 0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
}



int main(int argc,char* argv[]){

    FILE* fp = fopen(argv[1],"r");
    int dim;
    fscanf(fp,"%d\n",&dim);
    int** Matrix = createMatrix(fp,dim);
    printf("%d\n",getDeterminant(Matrix,dim));

    freeMatrix(Matrix,dim);
    fclose(fp);

    return EXIT_SUCCESS;
}