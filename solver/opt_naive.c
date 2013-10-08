#include <stdio.h>
#include "target.h"
#include "opt_naive.h"

typedef struct TList TList;

struct TList {
  int hd_id;
  num hd_time;
  TList *tl;
};

#define BUFF_2SIZE 65536

TList tlbuff[BUFF_2SIZE];
num probabuff[BUFF_2SIZE][BUFF_SIZE];
num powerbuff[BUFF_2SIZE][BUFF_SIZE];
num sumbuff[BUFF_SIZE+1];

void naive_det_(Target*, int, int, const int);
void update_col(Target, int);
void reset_buff(int);

int permu[BUFF_SIZE];

num naive_det(Target* t, Target* u, const int n)
{
  reset_buff(1 << n);

  naive_det_(t, 0, 0, n);

  TList *l = &tlbuff[0];
  int i = 0;

  while (l != NULL)
  {
    u[i++] = t[l->hd_id];
    l = l->tl;
  }

  return tlbuff[0].hd_time;
}

void naive_det_(Target* tgt, int i, int s, const int n)
{
  if (i < n - 1)
  {
    int j;
    int x = permu[i];
    num min_time = 1./0.;
    int min_x = x, min_s;

    for (j = i ; j < n ; j++)
    {
      permu[i] = permu[j];
      permu[j] = x;

      int s_ = s | 1 << permu[i];

      if (tlbuff[s_].hd_id == -1)
      {
        update_col(tgt[permu[i]], i);
        naive_det_(tgt, i+1, s_, n);
      }

      num tgt_time = tgt[permu[i]].w * sumbuff[i] + tlbuff[s_].hd_time;

      if (tgt_time < min_time)
      {
        min_time = tgt_time;
        min_x = permu[i];
        min_s = s_;
      }

      permu[j] = permu[i];
    }

    permu[i] = x;

    tlbuff[s].hd_id = min_x;
    tlbuff[s].hd_time = min_time;
    tlbuff[s].tl = &(tlbuff[min_s]);
  }
  else if (i == n - 1)
  {
    tlbuff[s].hd_id = permu[i];
    tlbuff[s].hd_time = tgt[permu[i]].w * sumbuff[i];
    tlbuff[s].tl = NULL;
  }
}

void update_col(Target tgt, const int j)
{
  if (j == 0)
  {
    probabuff[0][0] = 1 - tgt.p;
    probabuff[1][0] = tgt.p;

    powerbuff[0][0] = Guru + tgt.e;

    sumbuff[1] = tgt.p / powerbuff[0][0] + (1 - tgt.p) / Guru;

    return;
  }
  else
  {
    int i, d, k, l;
    num sum_ = 0;

    powerbuff[0][j] = Guru + tgt.e;

    for (i = 1, l = 0, d = 1 ; l < j ; l++, d <<= 1)
      for (k = 0 ; k < d ; k++)
        powerbuff[i++][j] = tgt.e + powerbuff[k][l];

    for (i = 0 ; i < d ; i++)
    {
      probabuff[i][j] = (1 - tgt.p) * probabuff[i][j-1];
      probabuff[i+d][j] = tgt.p * probabuff[i][j-1];

      sum_ += probabuff[i][j-1] / powerbuff[i][j];
    }

    sumbuff[j+1] = tgt.p * sum_ + (1 - tgt.p) * sumbuff[j];
  }
}

/*
void test_col(void)
{
  Target tgt_test;

  tgt_test.p = 0.5;
  tgt_test.e = 0;
  tgt_test.w = 1;

  int i;

  for (i = 0 ; i < 2 ; i++)
  {
    update_col(tgt_test, i);
  }

  tgt_test.e = 1;
  update_col(tgt_test, 2);
  update_col(tgt_test, 3);

  int j;

  for (i = 0 ; i < 4 ; i++)
  {
    for (j = 0 ; j < 1 << (i + 1) ; j++)
      printf("%5.3f ", probabuff[j][i]);
    printf("\n");
  }

  printf("\n");

  for (i = 0 ; i < 4 ; i++)
  {
    for (j = 0 ; j < 1 << i ; j++)
      printf("%5.3f ", powerbuff[j][i]);
    printf("\n");
  }

  printf("\n");

  for (i = 0 ; i < 5 ; i++)
    printf("%5.3f ", sumbuff[i]);
  printf("\n");
}
*/

void init_buff(void)
{
  int i;

  for (i = 0 ; i < BUFF_SIZE ; i++)
    permu[i] = i;

  sumbuff[0] = 1 / Guru;
}

void reset_buff(int p)
{
  int i;
  for (i = 0 ; i < p ; i++)
    tlbuff[i].hd_id = -1;

  tlbuff[p-1].hd_time = 0;
}

/*
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

*/
