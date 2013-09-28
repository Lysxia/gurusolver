#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "target.h"
#include "opt_naive.h"

int main(int argc, char** argv)
{
  srand(time(NULL));

  Target tgt[BUFF_SIZE];

  rand_target(tgt, BUFF_SIZE);

#define T_NUM 8

  Target *t[T_NUM];

  int i;

  for (i = 0 ; i < T_NUM ; i++)
    t[i] = &(tgt[i]);

  print_targets(tgt, T_NUM);

  printf("%f\n", guru_time(t,T_NUM));

  printf("Start\n");
  fflush(stdout);

  naive_det(t, T_NUM);

  printf("Done\n");
  fflush(stdout);

  Target tgt2[T_NUM];

  for (i = 0 ; i < T_NUM ; i++)
    tgt2[i] = *t[i];

  print_targets(tgt2, T_NUM);

  printf("%f\n", guru_time(t,T_NUM));

  return 0;
}
