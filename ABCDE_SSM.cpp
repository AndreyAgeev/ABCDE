// ABCDE_SSM.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

int main()
{
	srand((unsigned)time(NULL));
	GError *gerror = NULL;
	Posterior posterior;
	initial_init_posterior(&posterior);
	Thetha prev_thetha;
	Thetha curr_thetha;
	int i = 0, t;
	double eps;
	Config config;
	double * real_data;
	gchar  filename[] = { 'a', '.', 'i', 'n','i',0 };//argv[0]
	read_config_file_abc(&config, filename, &gerror);
	curr_thetha = generate_vector_param(NORM_WITH_PARAM);
	real_data = read_real_data();//argv[1];
	double *X = (double*)malloc(sizeof(double) * (sizeof(real_data) / sizeof(real_data[0])));
	t = config.t;
	eps = config.eps;
	for (i = 0; i < N; i++)
	{
		do
		{
		    curr_thetha = generate_vector_param(NORM_WITH_PARAM);
		    prepare_deep_file(config, curr_thetha);
		    X = Model(SSM, config.name_exe_file, config.name_deep_ini_file);
     	} while (distance(X, real_data, MEAN_ERROR) > config.eps);
		posterior.thetha[i] = curr_thetha;
		posterior.w[i] = 1.0 / (double)N;
	}
	for (t; t < 5; t++)
	{
		for (i = 0; i < N; i++)
		{

			//if (rand() < 0.05)//ошибка со значениями возможно из за rand() c double
		//	{
			//	mutation(&posterior);//TO DO
		//	}
		//	else
		//	{
			//	crossover(&posterior);//TO DO
		//	}
	//		do
	//		{
			prev_thetha = get_prev_iter_with_probabilities(&posterior);
			curr_thetha = generate_vector_param(NORM_WITH_PARAM, &curr_thetha);
			//X = Model(EXPON, curr_thetha);

//		} while (distance(X, example_dist, MEAN_ERROR) > eps);
			posterior.thetha[i] = curr_thetha;
			posterior.w[i] = get_new_probabilities(&posterior, curr_thetha);
		}
	}
	free(X);
	free(real_data);
	return 0;
}
