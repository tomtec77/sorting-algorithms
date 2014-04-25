/*
 * @file random.c
 * @brief Functions for random number generation.
 * @author Tomas E. Tecce
 * @date 2012-11-29
 */
#include "random.h"

unsigned int SeedX, SeedY, SeedZ, SeedC;


/**
 * @fn KISS
 * @brief KISS reliable random number generator by G. Marsaglia (1999)
 * @return An @a unsigned @a int in the range [0,UINT_MAX]
 */
unsigned int KISS(void)
{
  unsigned long long t, a = 698769069ULL;

  SeedX = 69069*SeedX+12345;
  SeedY ^= (SeedY<<13); SeedY ^= (SeedY>>17); SeedY ^= (SeedY<<5);
  t = a*SeedZ+SeedC; SeedC = (t>>32);
  return SeedX+SeedY+(SeedZ=t);
}


/**
 * @fn rndnum
 * @brief Uses KISS to generate floating point random numbers between 0
 * and 1.
 * @return A @a double in the range [0,1]
 */
double rndnum(void)
{
  unsigned int KISS();

  /* The value 4294967296 is the maximum value for @a unsigned @a int in
     both 32- and 64-bit architectures */
  //return KISS() / 4294967296.0;
  return (double)KISS() / UINT_MAX;
}


/**
 * @fn gaussdev
 * @brief Generate Gaussian deviates with mean 0 and stdev 1, using the
 * Box-Mueller transform
 * @return A @a double drawn from a Gaussian with mean 0 and stdev 1
 */
double gaussdev(void)
{
  double x, y, r;

  do {
    x = 2.0*rndnum() - 1.0;
    y = 2.0*rndnum() - 1.0;
    r = x*x + y*y;
  } while (r == 0.0 || r >= 1.0);

  r = sqrt((-2.0*log(r))/r);

  return x*r;
}


/**
 * @fn rnd_setup
 * @brief Random number generator warm-up. Also sets the seed values
 * @param x First seed for the RNG
 * @param y Second seed for the RNG
 * @param z Third seed for the RNG
 */
void rnd_setup(unsigned int x, unsigned int y, unsigned int z)
{
  int i;
  double r,s;

  if (x == 0)
	  SeedX = 123456789;
  else
	  SeedX = x;

  if (y == 0)
	  SeedY = 362436000;
  else
	  SeedY = y;

  if (z == 0)
	  SeedZ = 521288629;
  else
	  SeedZ = z;

  SeedC = 7654321;

  /* Run the RNGs 5000 times to warm them up */
  for (i = 0; i < 5000; i++) {
    r = rndnum();
    s = gaussdev();
  }
  return;
}


/**
 * @fn devrand
 * @brief Return a random 32-bit integer from /dev/urandom for use as
 * random number seed
 * @return A random @a unsigned @a int
 */
unsigned int devrand(void)
{
  int fn;
  unsigned int r;

  fn = open("/dev/urandom", O_RDONLY);
  if (fn == -1) {
    fprintf(stderr, "Error (devrand): failed to open /dev/urandom\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  if (read(fn, &r, 4) != 4) {
    fprintf(stderr, "Error (devrand): failed to read from /dev/urandom\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  close(fn);

  return r;
}
