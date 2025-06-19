#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 10

void rotate(char matrix[DIM][DIM]) {
  char new[DIM][DIM];
  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM; col++) {
      new[col][DIM - 1 - row] = matrix[row][col];
    }
  }

  for (int row = 0; row < DIM; row++) {
    for (int col = 0; col < DIM; col++) {
      matrix[row][col] = new[row][col];
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *inputFile = fopen(argv[1], "r");
  if (inputFile == NULL) {
    perror("Error opening input file");
    return EXIT_FAILURE;
  }

  char matrix[DIM][DIM];
  char buffer[DIM + 2]; // Accommodate 10 chars, newline, and null terminator.

  for (int i = 0; i < DIM; i++) {
    if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
      fprintf(stderr, "Error: File does not contain %d lines.\n", DIM);
      fclose(inputFile);
      return EXIT_FAILURE;
    }

    // Remove trailing newline, if it exists
    buffer[strcspn(buffer, "\n")] = '\0';

    // Now, check if the length is exactly 10
    if (strlen(buffer) != DIM) {
      fprintf(stderr, "Error: Line %d does not contain exactly %d characters.\n", i + 1, DIM);
      fclose(inputFile);
      return EXIT_FAILURE;
    }

    strncpy(matrix[i], buffer, DIM);
  }

  //if fgetc does not return EOF, the file is too long
  if(fgetc(inputFile)!=EOF){
    fprintf(stderr, "Error: File has more than 10 lines.\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }
  fclose(inputFile);

  rotate(matrix);

  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
