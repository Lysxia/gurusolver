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

#define T_NUM 9

  int try;

  for (try = 0 ; try < 10000 ; try++)
  {
    rand_target(tgt, T_NUM);

    naive_det(tgt, tgt2, T_NUM);

    int i;

    for (i = 1 ; i < T_NUM ; i++)
      if (utility(tgt2[i], Guru) > utility(tgt2[0], Guru))
        break;

    if (i < T_NUM)
    {
      print_targets(tgt, T_NUM);
      printf("%f\n", guru_time(tgt,T_NUM));

      print_targets(tgt2, T_NUM);
      printf("%f\n***\n\n", guru_time(tgt2,T_NUM));
    }
  }

  return 0;
}
