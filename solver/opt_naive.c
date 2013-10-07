#include <stdio.h>
#include "target.h"
#include "opt_naive.h"

typedef struct List List;

struct TList {
  int hd_id;
  num hd_time;
  TList *tl;
};

#define BUFF_2SIZE 65536

TList tlbuff[BUFF_2SIZE];
num probabuff[BUFF_2SIZE][BUFF_SIZE];
num powerbuff[BUFF_2SIZE][BUFF_SIZE];
num sumbuf[BUFF_SIZE];

void naive_det_(Target*, int*, int, int, const int);
void update_col(Target, int);
void reset_list(int);

num naive_det(Target* t, int* permu, const int n)
{
  naive_det_(t, permu, 0, 0, n);

  return tlbuff[0].hd_time;
}

void naive_det_(Target* t, int* permu, int i, int s, const int n)
{
  if (i < n)
  {
    int j;
    int x = permu[i], id;
    num time = 1./0;

    for (j = i ; j < n ; j++)
    {
      permu[i] = permu[j];
      permu[j] = x;

      int s_ = s | 1 << permu[i];

      if (tlbuff[s_] == NULL)
        naive_det_(t, permu, i+1, s_, n);

      num tgt_time = 

      permu[j] = permu[i];
    }

    t[n-1] = t[i];
    t[i] = tgt;
  }
}

void update_col(Target tgt, const int j)
{
  if (j == 0)
  {
    probabuff[0][0] = 1 - tgt.p;
    probabuff[1][0] = tgt.p;

    powerbuff[0][0] = tgt.e;
    return;
  }
  else
  {
    int i, d = 1 << j, k, l;
    num sum_ = 0;

    powerbuff[0][j] = tgt.e;

    for (i = 1, l = 0, d = 1 ; l < j ; l++, d <<= 1)
      for (k = 0 ; k < d ; k++)
        powerbuff[i++][j] = tgt.e + powerbuff[k][l];

    for (i = 0 ; i < d; i++)
    {
      probabuff[i][j] = (1 - tgt.p) * probabuff[i][j-1];
      probabuff[i+d][j] = tgt.p * probabuff[i][j-1];

      sum_ += probabuff[i][j-1] * powerbuff[i][j];
    }

    sum[j] = tgt.p * sum_ + (1 - tgt.p) * sum[j-1];
  }
}

void reset_list(int p)
{
  int i;
  for (i = 0 ; i < p ; i++)
    tlbuff[i].hd_id = NULL;
}

// Quick hack
void search(Target** t, const int n, Target* tgt, int field, num min, num max, num tolerance)
{
  while (max-min > tolerance)
  {
    num mid = (max + min) / 2;

    switch (field)
    {
      case 0:
        tgt->p = mid;
        break;
      case 1:
        tgt->e = mid;
        break;
      default:
        tgt->w = mid;
    }

    naive_det(t, n);

    switch (field)
    {
      case 0:
      case 1:
        if (t[0] == tgt)
          max = mid;
        else
          min = mid;
        break;
      default:
        if (t[0] == tgt)
          min = mid;
        else
          max = mid;
    }
  }
}
