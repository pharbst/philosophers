#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int			j[256];
pthread_t	t[256];

void	thread_func(int threadnum)
{
	while (j[threadnum]++ < 100000)
	{
		printf("thread_func %d\n", threadnum);
		fflush(stdout);
	}
}

int main()
{
	for (int i = 0; i < 128; i++)
	{
		j[i] = 0;
		pthread_create(&t[i], NULL, (void *)thread_func, (void *)i);
	}
	sleep(10);
	pthread_cancel(t[0]);
	pthread_cancel(t[1]);
	pthread_cancel(t[2]);
	pthread_cancel(t[3]);
	pthread_cancel(t[4]);
	pthread_cancel(t[5]);
	pthread_cancel(t[6]);
	pthread_cancel(t[7]);
	pthread_cancel(t[8]);
	pthread_cancel(t[9]);
	pthread_cancel(t[10]);
	pthread_cancel(t[11]);
	pthread_cancel(t[12]);
	pthread_cancel(t[13]);
	pthread_cancel(t[14]);
	pthread_cancel(t[15]);
	pthread_cancel(t[16]);
	pthread_cancel(t[17]);
	pthread_cancel(t[18]);
	pthread_cancel(t[19]);
	pthread_cancel(t[20]);
	pthread_cancel(t[21]);
	pthread_cancel(t[22]);
	pthread_cancel(t[23]);
	pthread_cancel(t[24]);
	pthread_cancel(t[25]);
	pthread_cancel(t[26]);
	pthread_cancel(t[27]);
	pthread_cancel(t[28]);
	pthread_cancel(t[29]);
	pthread_cancel(t[30]);
	pthread_cancel(t[31]);
	pthread_cancel(t[32]);
	pthread_cancel(t[33]);
	pthread_cancel(t[34]);
	pthread_cancel(t[35]);
	pthread_cancel(t[36]);
	pthread_cancel(t[37]);
	pthread_cancel(t[38]);
	pthread_cancel(t[39]);
	pthread_cancel(t[40]);
	pthread_cancel(t[41]);
	pthread_cancel(t[42]);
	pthread_cancel(t[43]);
	pthread_cancel(t[44]);
	pthread_cancel(t[45]);
	pthread_cancel(t[46]);
	pthread_cancel(t[47]);
	pthread_cancel(t[48]);
	pthread_cancel(t[49]);
	pthread_cancel(t[50]);
	pthread_cancel(t[51]);
	pthread_cancel(t[52]);
	pthread_cancel(t[53]);
	pthread_cancel(t[54]);
	pthread_cancel(t[55]);
	pthread_cancel(t[56]);
	pthread_cancel(t[57]);
	pthread_cancel(t[58]);
	pthread_cancel(t[59]);
	pthread_cancel(t[60]);
	pthread_cancel(t[61]);
	pthread_cancel(t[62]);
	pthread_cancel(t[63]);
	pthread_cancel(t[64]);
	pthread_cancel(t[65]);
	pthread_cancel(t[66]);
	pthread_cancel(t[67]);
	pthread_cancel(t[68]);
	pthread_cancel(t[69]);
	pthread_cancel(t[70]);
	pthread_cancel(t[71]);
	pthread_cancel(t[72]);
	pthread_cancel(t[73]);
	pthread_cancel(t[74]);
	pthread_cancel(t[75]);
	pthread_cancel(t[76]);
	pthread_cancel(t[77]);
	pthread_cancel(t[78]);
	pthread_cancel(t[79]);
	pthread_cancel(t[80]);
	pthread_cancel(t[81]);
	pthread_cancel(t[82]);
	pthread_cancel(t[83]);
	pthread_cancel(t[84]);
	pthread_cancel(t[85]);
	pthread_cancel(t[86]);
	pthread_cancel(t[87]);
	pthread_cancel(t[88]);
	pthread_cancel(t[89]);
	pthread_cancel(t[90]);
	pthread_cancel(t[91]);
	pthread_cancel(t[92]);
	pthread_cancel(t[93]);
	pthread_cancel(t[94]);
	pthread_cancel(t[95]);
	pthread_cancel(t[96]);
	pthread_cancel(t[97]);
	pthread_cancel(t[98]);
	pthread_cancel(t[99]);
	pthread_cancel(t[100]);
	pthread_cancel(t[101]);
	pthread_cancel(t[102]);
	pthread_cancel(t[103]);
	pthread_cancel(t[104]);
	pthread_cancel(t[105]);
	pthread_cancel(t[106]);
	pthread_cancel(t[107]);
	pthread_cancel(t[108]);
	pthread_cancel(t[109]);
	pthread_cancel(t[110]);
	pthread_cancel(t[111]);
	pthread_cancel(t[112]);
	pthread_cancel(t[113]);
	pthread_cancel(t[114]);
	pthread_cancel(t[115]);
	pthread_cancel(t[116]);
	pthread_cancel(t[117]);
	pthread_cancel(t[118]);
	pthread_cancel(t[119]);
	pthread_cancel(t[120]);
	pthread_cancel(t[121]);
	pthread_cancel(t[122]);
	pthread_cancel(t[123]);
	pthread_cancel(t[124]);
	pthread_cancel(t[125]);
	pthread_cancel(t[126]);
	pthread_cancel(t[127]);

	sleep(3);
	for (int i = 0; i < 128; i++)
	{
		printf("thread %3d j = %d\n", i, j[i]);
	}
	int i = 0;
	int max = j[0];
	int max_index = 0;
	int min = j[0];
	int min_index = 0;
	while (j[i] > 0)
	{
		if (j[i] > max)
		{
			max = j[i];
			max_index = i;
		}
		if (j[i] < min)
		{
			min = j[i];
			min_index = i;
		}
		i++;
	}
	printf("max = %d in thread %d, min = %d in thread %d\ndiff = %d\n", max, max_index, min, min_index, max - min);
	return (0);
}

// int main()
// {
// 	for (int i = 0; i < 20; i++)
// 	{
// 		pthread_create(&t[i], NULL, (void *)thread_func, (void *)i);
// 	}
// 	sleep(1);
// 	for (int i = 0; i < 30; i++)
// 	{
// 		pthread_cancel(t[i]);
// 	}
// 	printf("done\n");
// 	sleep(30);
// 	for (int i = 0; i < 20; i++)
// 		printf("j[%d] = %d\n", i, j[i]);
// 	return 0;
// }