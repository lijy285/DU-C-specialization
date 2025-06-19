#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //DEFINE ME                                                                                 
  char * name; // name of the count
  int count; // the count value
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME    
  one_count_t * counts; // array of counts
  int array_size; // number of counts
  int unknown_count; // count for unknown names                                                                             
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
