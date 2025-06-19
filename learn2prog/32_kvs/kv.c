#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

//parseLine: parse a line into a kvpair_t struct
kvpair_t * parseLine(char * line, const char delim) {
    //find the delimiter in the line
    char * eq_ptr = strchr(line, delim);
    if (eq_ptr == NULL) {
        fprintf(stderr, "Error: No delimiter '%c' found in line: %s\n", delim, line);
        return NULL; // No delimiter found
    }
    //isolate the key by placing a null terminator at the delimiter
    *eq_ptr = '\0';

    char *key = line; // the key is the start of the line
    char *value = eq_ptr + 1; // the value is after the delimiter
    //trim leading and trailing whitespace from key and value
    char *newline_ptr = strchr(value, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0'; // remove newline character
    }

    //allocate memory for the kvpair_t struct
    kvpair_t * pair = malloc(sizeof(*pair));
    if (pair == NULL) {
        perror("Failed to allocate memory for kvpair_t");
        return NULL; // Memory allocation failed
    }
    //allocate memory for the key and value strings
    pair->key = malloc(strlen(key) + 1);
    if (pair->key == NULL) {
        perror("Failed to allocate memory for key");
        free(pair);
        return NULL; // Memory allocation failed
    }
    pair->value = malloc(strlen(value) + 1);
    if (pair->value == NULL) {
        perror("Failed to allocate memory for value");
        free(pair->key);
        free(pair);
        return NULL; // Memory allocation failed
    }
    //copy the key and value into the kvpair_t struct
    strcpy(pair->key, key);
    strcpy(pair->value, value);
    return pair; // Return the populated kvpair_t struct
}

kvarray_t * readKVs(const char * fname) {
  // open the file                                                                            
  FILE *f = fopen(fname, "r");
  if(f == NULL){
    perror("could not open the file'\n");
    return NULL;
  }

  //allocate the main kvarray_t struct                                                        
  kvarray_t * kv_array = malloc(sizeof(* kv_array));
  if(kv_array==NULL){
    perror("failed to allocate memory for kvarray");
    fclose(f);
    return NULL;
  }
  kv_array->pairs = NULL; // initialize pairs to NULL
  kv_array->num_pairs = 0;

  //read the file line by line                                                                
  char * line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f)>=0){
    //parse the line into kv pairs                                                            
    kvpair_t * current_pair = parseLine(line, '=');
    if (current_pair == NULL)
      continue; // skip the empty line.                                                       
    kv_array->num_pairs++;
    kv_array->pairs = realloc(kv_array->pairs, kv_array->num_pairs*sizeof(*kv_array->pairs));
    if (kv_array->pairs == NULL) {
      perror("Failed to allocate memory for pairs");
      free(current_pair->key);
      free(current_pair->value);
      free(current_pair);
      fclose(f);
      return NULL; // Memory allocation failed
    }
    kv_array->pairs[kv_array->num_pairs - 1] = *current_pair; // add the new pair to the array
    free(current_pair); // free the temporary pair after adding it to the array
  }
  //clean up
    free(line);
    fclose(f);
    //return the populated kvarray_t struct
    return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  if(pairs == NULL) {
    return; // nothing to free                                                                
  }
  //free each kvpair_t in the pairs array
  for (size_t i = 0; i < pairs->num_pairs; i++) {
    free(pairs->pairs[i].key);   // free the key string
    free(pairs->pairs[i].value); // free the value string
  }
  //free the pairs array itself
  free(pairs->pairs);
  //free the kvarray_t struct
  free(pairs);
}
void printKVs(kvarray_t * pairs) {
  if(pairs == NULL) {
    printf("No key-value pairs to print.\n");
    return; // nothing to print                                                                
  }
  //print each kvpair_t in the pairs array
  for (size_t i = 0; i < pairs->num_pairs; i++) {
    printf("key = '%s' value ='%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    if (pairs == NULL || key == NULL) {
        return NULL; // No pairs or key provided
    }

    //search for the key in the pairs array
    {
        for (size_t i = 0; i < pairs->num_pairs; i++) {
            if (strcmp(pairs->pairs[i].key, key) == 0) {
                return pairs->pairs[i].value; // return the value if the key matches
            }
        }
    }
    return NULL; // key not found
    
}
