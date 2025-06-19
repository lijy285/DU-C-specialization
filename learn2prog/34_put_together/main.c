#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char *filename, kvarray_t *kvPairs){
  //create a new counts to store
  counts_t * c = createCounts();
  //open for reading
  FILE * f = fopen(filename, "r");
  if(f == NULL){
    fprintf(stderr, "couldn't open the file");
    freeCounts(c); // couldn't open
    return NULL;
  }

  //Read line by line
  char * line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f)>= 0){
    char * newline = strchr(line, '\n');
    if(newline != NULL)
      * newline = '\0';
    //current key value
    char * value = lookupValue(kvPairs, line);
    //add
    addCount(c, value);
  }
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc < 3){
    fprintf(stderr, "Usage:  key_val\n");
    return EXIT_FAILURE;
}
//read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if(kv == NULL)
    return EXIT_FAILURE;

  int had_error = 0;
 //count from 2 to argc (call the number you count i)
  for(int i = 2; i < argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL){
      had_error = 1;
      continue; //continue to next file
    }
      //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL){
      perror("cannot open the output file for writing");
      had_error = 1;
      free(outName);
      freeCounts(c);
      continue; // to next file
    }

    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
   
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }


 //free the memory for kv
  freeKVs(kv);
  if(had_error)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
