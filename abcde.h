#pragma once
#include "pch.h"

class Abcde : public Model
{
public:
	enum BOUNDS_CROSSING_MODE {
		SIN = 0,
		TANH
	};
	Abcde();
	Abcde(const string& param);	
	bool accept_alpha(double alpha);
	void init_posterior();
	void act_with_config_file();
	Distribution::Thetha mutation(int index);
	double set_bounds(double x, double _lbound, double _hbound);
	Distribution::Thetha bounds(Distribution::Thetha _curr_thetha);
	Distribution::Thetha crossover(int index);
	double max_weight(double* w);
	Distribution::Thetha get_prev_iter_with_weight();
	double set_new_weight();
	Distribution::Thetha generate_vector_param(Distribution::TYPE_DISTR mode);
	void normalize_weights();
	void set_sample_dist_param();
	void update_posterior();
	double get_statistics(Parametrs::MODE _mode, double error, int i);
	string config_file;
	string deep_exe;
	Distribution::Posterior posterior;
	Distribution::Posterior new_posterior;
	Distribution::Thetha curr_thetha;
	Distribution generator;
	int t;
	int count_iter;
	int start_iter;
	int count_thread;
	double* error;
	int count_opt_param;
	vector<double> mean, std;
	vector<double> sample_mean, sample_std;
	vector<int> dtype;
	vector<double> lbound, hbound;
	double norm_error;
	int bounds_crossing_mode;
};
