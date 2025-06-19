#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  if (c == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }
  c->counts = NULL; // Initialize the counts array to NULL
  c->array_size = 0; // Initialize the size of the counts array to 0
  c->unknown_count = 0; // Initialize the unknown count to 0
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  // Check if the name already exists in the counts array
  for (int i = 0; i < c->array_size; i++) {
    if (strcmp(c->counts[i].name, name) == 0) {
      c->counts[i].count++;
      return;
    }
  }
  // If the name does not exist, we need to add it
  c->array_size++;
  one_count_t * new_arr = realloc(c->counts, (c->array_size) * sizeof(one_count_t));
  if (new_arr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  c->counts = new_arr; // Update the counts array to the new memory location
  c->counts[c->array_size-1].name = strdup(name); // Duplicate the name string
  if (c->counts[c->array_size-1].name == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  c->counts[c->array_size-1].count = 1; // Initialize the count to 1
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c == NULL || outFile == NULL) {
    fprintf(stderr, "Invalid counts or output file\n");
    return;
  }
  for (int i = 0; i < c->array_size; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i].name, c->counts[i].count);
  }
  if(c->unknown_count > 0) 
    fprintf(outFile, "<unknown>: %d\n", c->unknown_count);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c == NULL) {
    return; // Nothing to free
  }
  // Free each name in the counts array
  for (int i = 0; i < c->array_size; i++) {
    free(c->counts[i].name); // Free each name string
  }
  free(c->counts); // Free the counts array itself
  free(c); // Free the counts_t struct
  return;
}
