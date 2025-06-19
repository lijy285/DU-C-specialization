#include <stdio.h>
#include <stdlib.h>

//create a new matrix of the rotate one, then copy it to the origin
void rotate(char matrix[10][10]){
  char new[10][10];
  for(int row = 0; row < 10; row++){
    for(int col = 0; col < 10; col++){
      //      new[row][col] = matrix[col][9-row];
      new[col][9-row]=matrix[row][col];
    }
  }

  for(int row = 0; row<10; row++){
    for(int col = 0; col < 10; col++){
      matrix[row][col]=new[row][col];
    }
  }
}
