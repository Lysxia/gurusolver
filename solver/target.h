#ifndef TARGET_H
#define TARGET_H

#define BUFF_SIZE 16

typedef double num;

const num Guru;

typedef struct
{
  num p, // Conversion probability
      e, // Efficiency
      w; // Work
} Target;

num utility(const Target, const num);

num guru_time(Target**, const int);

void rand_target(Target*, int);

void print_targets(const Target*, const int);

#endif
