#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <time.h>
#include "Lan.h"


int main(int argc, char* argv[])
{
	srand(time(NULL));

	LanInit();
	


	#pragma omp parallel sections num_threads(3)
	{
		#pragma omp section
		{
			LanUpdateBots();
		}
		#pragma omp section
		{
			LanPlayerAcceptor();
		}
		#pragma omp section
		{
			char buff[256];

			while (1)
			{
			//	printf("server:");
			//	scanf("%s", &buff);

				//printf("you enter: %s\n", buff);
			}
		}
	}
	

	return 0;
}

