/*
 * random.h
 */
#ifndef RANDOM_H_
#define RANDOM_H_

#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

extern unsigned int SeedX, SeedY, SeedZ, SeedC;

unsigned int devrand(void);
double       gaussdev(void);
unsigned int KISS(void);
void         rnd_setup(unsigned int, unsigned int, unsigned int);
double       rndnum(void);

#endif /* RANDOM_H_ */
