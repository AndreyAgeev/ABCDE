// ABCDE_SSM.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	GError *gerror = NULL;
	Posterior posterior;
	Thetha prev_thetha;
	Thetha curr_thetha;
	int i = 0, t = 0;
	Config config;
	bool print_trace = false;
	if (argc < 2)
	{
		cout << "Error! Check your command line" << endl;
		return 0;
	}
	else if (argc == 3)
	{
		cout << argv[2] << endl;

		if (argv[2][0] == 'p')
			print_trace = true;
		else
		{
			cout << "Error! Check your command line" << endl;
			return 0;
		}
	}
	char * filename = argv[1];
	if (print_trace == true)
		cout << filename << endl;
	config.name_ini_file = filename;
	initial_init_posterior(&posterior);
	read_config_file_abc(config, &gerror);
	if (print_trace == true)
	{
		cout << config.name_command_exe_file << endl;
		cout << config.name_exe_file << endl;
		cout << config.eps << endl;
	}

	double * error = new double[N];
	for (i = 0; i < N; i++)
	{
		do
		{
			if (print_trace == true)
				std::cout << "HERE0" << endl;
			curr_thetha = generate_vector_param(NORM_WITH_PARAM);
			if (print_trace == true)
			{
				std::cout << "Take this param ";
				std::cout << curr_thetha.n << " ";
				std::cout << curr_thetha.l << std::endl;
				std::cout << curr_thetha.lambda << std::endl;
			}
			if (print_trace == true)
				std::cout << "HERE1" << endl;
			prepare_deep_file(config, curr_thetha);//this we use default deep file
			if (print_trace == true)
				std::cout << "HERE2" << endl;
			if (print_trace == true)
				std::cout << "curr_name " << config.curr_ini_file << std::endl;
			
			error[i] = Model(SSM, config.name_exe_file, config.curr_ini_file);
			if (print_trace == true)
				std::cout << "error_" << i << "= " << error[i] << std::endl;
		} while (error[i] > config.eps);
		if (print_trace == true)
			std::cout << "THIS PARAM WE TAKE AND ERROR_" << i << "= " << error[i] << std::endl;

		posterior.thetha[i] = curr_thetha;
		posterior.w[i] = 1.0 / (double)N;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "HERE_STARTED" << endl;
	std::cout << config.t << endl;

	double alpha, psi, sigma_psi;
	for (t = 0; t < config.t; t++)
	{
		if (print_trace == true)
		    std::cout << "HERE_STARTED" << endl;

		for (i = 0; i < N; i++)
		{

			if (rand() < 0.05)////////////////////////
			{
				if (print_trace == true)
					std::cout << "HERE1" << endl;

				curr_thetha = mutation(&posterior, i);
			}
			else
			{
				if (print_trace == true)
					std::cout << "HERE2" << endl;

				curr_thetha = crossover(&posterior, i);
			}
			if (print_trace == true)
				std::cout << "HERE3" << endl;

			prepare_deep_file(config, curr_thetha);
			error[i] = Model(SSM, config.name_exe_file, config.name_ini_file);
			if (print_trace == true)
				std::cout << "HERE4" << endl;

			sigma_psi = prior_distribution(EXPON, 0.005);
			if (print_trace == true)
				std::cout << sigma_psi << endl;

			psi = prior_distribution(NORM_WITH_PARAM, error[i], sigma_psi);
			if (print_trace == true)
				std::cout <<psi << endl;

			alpha = ((prior_distribution(NORM_WITH_PARAM, curr_thetha.n, SIGMA) *  prior_distribution(NORM_WITH_PARAM, curr_thetha.l, SIGMA) *  prior_distribution(NORM_WITH_PARAM, curr_thetha.lambda, SIGMA)) * psi) / ((prior_distribution(NORM_WITH_PARAM, posterior.thetha[i].n, SIGMA) *  prior_distribution(NORM_WITH_PARAM, posterior.thetha[i].l, SIGMA) *  prior_distribution(NORM_WITH_PARAM, posterior.thetha[i].lambda, SIGMA)) * psi);
			if (print_trace == true)
				std::cout << alpha << endl;

			if (alpha > 1)
			{
				if (print_trace == true)
					std::cout << "YES" << endl;

				posterior.thetha[i] = curr_thetha;
				posterior.w[i] = get_new_probabilities(&posterior, curr_thetha);
			}
		}
	}
	print_param_and_error(error, posterior);
	delete[]error;
	delete[]posterior.thetha;
	delete[]posterior.w;
	return 0;
}
