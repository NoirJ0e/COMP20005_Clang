#include <stdio.h>
long long int factorial(double n)
{
  long long int result = 1;
  if (n < 170)
  {
    for (long long int i = 1; i <= n; i++)
    {
      result *= i;
    }
    return result;
  }
  else
  {
    n = n / 1000.0;
    for (double i = 0.001; i <= n; i += 0.001)
    {
      result *= i;
    }
    return result;
  }
}

int main()
{
  printf("%lld", factorial(170));
}
