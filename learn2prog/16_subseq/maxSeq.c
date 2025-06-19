#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n){
  if(n==0)
    return 0;
  if (n==1)
    return 1;
  size_t maxlen = 1;
  size_t curlen = 1;
  for(size_t i = 0; i < n; i++){
    if(array[i]>array[i-1]){
      curlen++;
      if(curlen > maxlen)
	maxlen = curlen;
    }else{
      curlen = 1;
    }
  }
  return maxlen;
}














































































