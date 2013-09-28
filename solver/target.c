#include <stdio.h>
#include <stdlib.h>
#include "target.h"

const num Guru = 1;

num utility(const Target tgt, const num guru)
{
  return tgt.p / tgt.w * (tgt.e / (guru * (guru + tgt.e)));
}

num guru_time_(Target**, num, int, const int);

num guru_time(Target** t, const int n)
{
  return guru_time_(t, Guru, 0, n);
}

num guru_time_(Target** t, num G, int i, const int n)
{
  if (i == n)
    return 0;

  Target tgt = *t[i];
  
  return tgt.w/G +
    tgt.p       * guru_time_(t, G + tgt.e, i + 1, n) +
    (1 - tgt.p) * guru_time_(t, G, i + 1, n);
}

void rand_target(Target* t, int n)
{
  int i;
  for (i = 0 ; i < n ; i++)
  {
#define RAND1 rand()%100/100.
    t[i].p = RAND1;
    t[i].e = RAND1;
    t[i].w = rand()%100;
  }
}

void print_targets(const Target* t, const int n)
{
  int i;
  for (i = 0 ; i < n ; i++)
    printf("%7.2f", t[i].p);

  printf("\n");

  for (i = 0 ; i < n ; i++)
    printf("%7.2f", t[i].e);

  printf("\n");

  for (i = 0 ; i < n ; i++)
    printf("%7.2f", t[i].w);

  printf("\n");

  for (i = 0 ; i < n ; i++)
    printf("%7.2f", 1000*utility(t[i], Guru));

  printf("\n");
}
