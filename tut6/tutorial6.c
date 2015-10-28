#include <tutorial6.h>

int factorial(int val)
{
	if (val == 0)
	{
		return 1;
	} else {
		return val * factorial(val - 1);
	}
}