#include <stdio.h>
#include "../header/core_system.h"





int main(int argc, char **argv)
{
	system_setup();

	double time = system_real_time();

	print_system_policy();

	printf("Time: %f\n", time);


	return 0;
}
