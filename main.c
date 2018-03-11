#include <stdio.h>
#include <stdlib.h>
#include "model.c"

int main()
{
	tensor * image = get_tensor(255,255,3);
	tensor * output = forward(image);

	return EXIT_SUCCESS;
}