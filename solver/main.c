#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "target.h"
#include "opt_naive.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  init_buff();

  Target tgt[BUFF_SIZE], tgt2[BUFF_SIZE];

  rand_target(tgt, BUFF_SIZE);

#define T_NUM 8

  print_targets(tgt, T_NUM);

  printf("%f\n", guru_time(tgt,T_NUM));

  printf("Start\n");
  fflush(stdout);

  naive_det(tgt, tgt2, T_NUM);

  printf("Done\n");
  fflush(stdout);

  print_targets(tgt2, T_NUM);

  printf("%f\n", guru_time(tgt2,T_NUM));

  return 0;
}
