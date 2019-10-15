// ABCDE_SSM.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

int main()
{
	srand((unsigned)time(NULL));
	double * example_dist = Model(EXPON, 0.5);
	int t = 2;
	double eps = 0.05;
	Posterior posterior;
	initial_init_posterior(&posterior);
	write_to_file(example_dist, "exponential_param_0_and_5.txt");	
	double *X = (double*)malloc(sizeof(double) * N);
	double *Y = example_dist;
	double prev_thetha;
	double curr_thetha;
	int i = 0;
	for (i = 0; i < N; i++)
	{
		do
		{
			curr_thetha = prior_distribution(NORM);//prior
			X = Model(EXPON, curr_thetha);
	//		std::cout << curr_thetha << std::endl;
	//		std::cout << distance(X, example_dist, MEAN_ERROR) << std::endl;
		} while (distance(X, example_dist, MEAN_ERROR) > eps);
		posterior.thetha[i] = curr_thetha;
		posterior.w[i] = 1.0 / (double)N;
	}
	//std::cout << "FINISH" << std::endl;
//	for(i = 0; i < N; i++)
//		std::cout << posterior.thetha[i] << std::endl;
    double var = variancy(&posterior);//ANOTHER VALUE
//	std::cout << var << std::endl;
//	return 0;
	for (t; t < 5; t++)
	{
		std::cout << "iter" << std::endl;

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
			do
			{
			//	std::cout << "BEGIN DO" << std::endl;

				prev_thetha = get_prev_iter_with_probabilities(&posterior);//WHICH THETHA MUST BE CHANGE (I MEAN WHAT i - maybe current i in cycle, or i - what we get for change)
		//		std::cout << prev_thetha << std::endl;
				
				curr_thetha = prev_thetha + prior_distribution(NORM_WITH_PARAM, prev_thetha, var);//getNormalSampleWithParam(prev_thetha, var);
		//		std::cout << curr_thetha << std::endl;
		     //	std::cout << curr_thetha << std::endl;
		//		std::cout << "BEGIN 2" << std::endl;

				X = Model(EXPON, curr_thetha);
			//	std::cout << "BEGIN 3" << std::endl;

				//
				//write_deep_config(DEEP_FILE, curr_thetha);
				//запуска deep с этим файлом
				//X = read_deep_output(OUT_DEEP)

			} while (distance(X, example_dist, MEAN_ERROR) > eps);
			std::cout << "BEGIN 4" << std::endl;

			posterior.thetha[i] = curr_thetha;
			std::cout << "BEGIN 5" << std::endl;

			posterior.w[i] = get_new_probabilities(&posterior, var);/////////NEGATIVE VALUE
			std::cout << posterior.w[i] << std::endl;
			std::cout << "BEGIN 6" << std::endl;

		}
		var = variancy(&posterior);
		std::cout << var << std::endl;

	}
	write_to_file(posterior.thetha, "final_res.txt");
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
