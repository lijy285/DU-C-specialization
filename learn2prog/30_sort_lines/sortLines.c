#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

//handle the stream and malloc
void processStream(FILE * f){
  char ** lines = NULL;
  //buffer
  char * currLine = NULL;
  //buffer size
  size_t linecap = 0;
  //line count;
  size_t i = 0;

  //Reading lines from the file line by line
  while(getline(&currLine, &linecap, f)>=0){
    //our line should bigger by one pointer than the current line
    lines = realloc(lines, (i+1)*sizeof(*lines));
    //check if allocation success
    if(lines == NULL){
      perror("realloc failed.\n");
      exit(EXIT_FAILURE);
    }
    //store the new read line's pointer
    lines[i] = currLine;

    //reset the buffer
    currLine = NULL;
    i++;
  }
  //free memory
  free(currLine);

  sortData(lines, i);

  for(size_t j= 0; j<i; j++){
    printf("%s", lines[j]);

    //free memory for the getline
    free(lines[j]);
  }
  free(lines);
}


int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if(argc == 1)
    processStream(stdin);


  //one or more command lines
  for(int i = 1; i < argc; i++){
    FILE * f = fopen(argv[i], "r");

    if(f==NULL){
      fprintf(stderr, "Could not open file.\n");
      return EXIT_FAILURE;
    }

    processStream(f);
    fclose(f);

  }
  return EXIT_SUCCESS;
}
