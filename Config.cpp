#include "pch.h"

gchar* model_read_abc(char * filename, gsize*size, GError**err)
{
	GFile*gfile;
	char *etag;
	gchar*data = NULL;
	GError *gerror = NULL;
	g_return_val_if_fail(err == NULL || *err == NULL, NULL);
	gfile = g_file_new_for_commandline_arg(filename);
	if (!g_file_load_contents(gfile, (GCancellable*)NULL, &data, size, &etag, &gerror)) {
		g_propagate_error(err, gerror);
		return NULL;
	}
	g_object_unref(gfile);
	return data;
}
int model_load_abc(Config &config, gchar*data, gsize size, GError**err)
{
	GKeyFile*gkf;
	GError *gerror = NULL;
	gchar*str, **strlist;
	gsize length;
	int *ilist, ii, j, jj, k, kk;
	double *dlist, dval;
	int retval = 0;
	g_return_val_if_fail(err == NULL || *err == NULL, 1);
	gkf = g_key_file_new();
	if (!g_key_file_load_from_data(gkf, (const gchar*)data, size, G_KEY_FILE_NONE, &gerror)) {
		g_propagate_error(err, gerror);
		return 1;
	}
	if ((ii = g_key_file_get_integer(gkf, "data", "count_thread", &gerror)) != 0 || gerror == NULL) {
		config.count_thread = ii;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	if ((str = g_key_file_get_string(gkf, "data", "name_exe_file", &gerror)) != 0 || gerror == NULL) {
		config.name_exe_file = str;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	if ((str = g_key_file_get_string(gkf, "data", "name_command_exe_file", &gerror)) != 0 || gerror == NULL) {
		config.name_command_exe_file = str;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	if ((str = g_key_file_get_string(gkf, "data", "param_command_exe_file", &gerror)) != 0 || gerror == NULL) {
		config.param_command_exe_file = str;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	if ((dval = g_key_file_get_double(gkf, "data", "eps", &gerror)) != 0 || gerror == NULL) {
		config.eps = dval;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	if ((ii = g_key_file_get_integer(gkf, "data", "t", &gerror)) != 0 || gerror == NULL) {
		config.t = ii;
		if (gerror != NULL) g_clear_error(&gerror);
	}
	else {
		g_debug("%s", gerror->message);
		g_clear_error(&gerror);
	}
	g_key_file_free(gkf);
	return retval;
}


int read_config_file_abc(Config & config, GError **err)
{
	int ret_val = 0;
	gchar*data = NULL;
	gsize size;
	GError *gerror = NULL;
	g_return_val_if_fail(err == NULL || *err == NULL, 1);
	if ((data = model_read_abc(config.name_ini_file, &size, &gerror)) == NULL) {
		g_propagate_error(err, gerror);
		return 1;
	}
	ret_val = model_load_abc(config, data, size, &gerror);
	if (ret_val == 1) {
		g_propagate_error(err, gerror);
		ret_val = 1;
	}
	g_free(data);
	return ret_val;
}

gchar* model_read_deep(gchar*filename, gsize*size, GError**err)
{
	GFile*gfile;
	char *etag;
	gchar*data = NULL;
	GError *gerror = NULL;
	g_return_val_if_fail(err == NULL || *err == NULL, NULL);
	gfile = g_file_new_for_commandline_arg(filename);
	if (!g_file_load_contents(gfile, (GCancellable*)NULL, &data, size, &etag, &gerror)) {
		g_propagate_error(err, gerror);
		return NULL;
	}
	g_object_unref(gfile);
	return data;
}
int model_load_deep(Config &config, gchar*data, gsize size, Thetha &thetha,  GError**err)
{
	GKeyFile*gkf;
	GError *gerror = NULL;
	gchar*str, **strlist;
	gsize length;
	int *ilist, ii, j, jj, k, kk;
	double *dlist, dval;
	int retval = 0;
	g_return_val_if_fail(err == NULL || *err == NULL, 1);
	gkf = g_key_file_new();
	if (!g_key_file_load_from_data(gkf, (const gchar*)data, size, G_KEY_FILE_NONE, &gerror)) {
		g_propagate_error(err, gerror);
		return 1;
	}
	char str_lambda[1000];
	//std::cout << "HERE_inside_2" << std::endl;

	sprintf(str_lambda, "%i", (int)thetha.lambda);

	char* res_string_lambda = new char[strlen(str_lambda) + strlen("penalty;readpenalty;2;2;") + 2];//2 - ; and '\0'
	strcpy(res_string_lambda, "penalty;readpenalty;2;2;");
	strcat(res_string_lambda, str_lambda);
	strcat(res_string_lambda, ";");
	g_key_file_set_string(gkf, "default_target", "l1_pen", res_string_lambda);

	char str_n[10];
	char str_l[10];

	sprintf(str_n, "%i", thetha.n);
	sprintf(str_l, "%i", thetha.l);
	//std::cout << "HERE_inside_3" << std::endl;
/*
	std::cout << strlen(str_n) << std::endl;
	std::cout << strlen(str_l) << std::endl;
	std::cout << strlen(config.name_command_exe_file) << std::endl;
	std::cout << strlen(config.param_command_exe_file) << std::endl;
*/
	char* res_string_n_l = new char[strlen(str_n) + strlen(str_l) + strlen(config.name_command_exe_file) +  strlen(config.param_command_exe_file) + 20];
//	std::cout << "HERE_inside_3_1" << std::endl;

	strcpy(res_string_n_l, "");
	strcat(res_string_n_l, config.name_command_exe_file);
	strcat(res_string_n_l, " -P 1 -N ");
	strcat(res_string_n_l, str_n);
	strcat(res_string_n_l, " -L ");
	strcat(res_string_n_l, str_l);
	strcat(res_string_n_l, " ");
	strcat(res_string_n_l, config.param_command_exe_file);
	strcat(res_string_n_l, "\0");
//	std::cout << "HERE_inside_3_2" << std::endl;

	g_key_file_set_string(gkf, "default_model", "command", res_string_n_l);
//	std::cout << "HERE_inside_4" << std::endl;


	int count_sym = thetha.n * thetha.l + thetha.n + thetha.n * 18 + 5 + 2;// numbers have more 
	char* default_model_str = new char[(count_sym*4)+count_sym+1];//���� ������ ������ ����� ������ �������� - ������
	char str_parts[10];
	char parts[10];
	//parts
	sprintf(str_parts, "%i", count_sym);
	strcpy(parts, "");
	strcat(parts, "x;");
	strcat(parts, str_parts);
	strcat(parts, ";");
	g_key_file_set_string(gkf, "default_model", "parts", parts);
	//mask
	strcpy(default_model_str, "");
	for (int i = 0; i < count_sym; i++)
		strcat(default_model_str, "0;");
	g_key_file_set_string(gkf, "default_model", "mask", default_model_str);
	//params
	strcpy(default_model_str, "");
	for (int i = 0; i < thetha.n * thetha.l; i++)
		strcat(default_model_str, "200;");
	for(int i = 0; i < thetha.n + thetha.n * 18; i++)
		strcat(default_model_str, "5;");
	for (int i = 0; i < 5 + 2; i++)
	{
		if(i == 0)
		    strcat(default_model_str, "16;");
		else
			strcat(default_model_str, "7;");
	}
	g_key_file_set_string(gkf, "default_model", "parms", default_model_str);
	//std::cout << "HERE_inside_5" << std::endl;

	//dparams
	strcpy(default_model_str, "");
	for (int i = 0; i < thetha.n * thetha.l; i++)
		strcat(default_model_str, "200;");
	for (int i = 0; i < thetha.n + thetha.n * 18; i++)
		strcat(default_model_str, "5.5;");
	for (int i = 0; i < 5 + 2; i++)
	{
		if (i == 0)
			strcat(default_model_str, "16.5;");
		else
			strcat(default_model_str, "7.1;");
	}
	g_key_file_set_string(gkf, "default_model", "dparms", default_model_str);


	//lbound
	strcpy(default_model_str, "");
	for (int i = 0; i < thetha.n * thetha.l; i++)
		strcat(default_model_str, "0;");
	for (int i = 0; i < thetha.n + thetha.n * 18; i++)
		strcat(default_model_str, "-10;");
	for (int i = 0; i < 5 + 2; i++)
	{
		if (i == 0)
			strcat(default_model_str, "15;");
		if (i == 1)
			strcat(default_model_str, "0;");
		if (i == 2)
			strcat(default_model_str, "6;");
		if (i == 3)
			strcat(default_model_str, "1;");
		if (i == 4)
			strcat(default_model_str, "0;");
		if (i == 5)
			strcat(default_model_str, "1;");
		if (i == 6)
			strcat(default_model_str, "1;");
	}
	g_key_file_set_string(gkf, "default_model", "lbound", default_model_str);

	//hbound
	strcpy(default_model_str, "");
	for (int i = 0; i < thetha.n * thetha.l; i++)
		strcat(default_model_str, "1924;");
	for (int i = 0; i < thetha.n + thetha.n * 18; i++)
		strcat(default_model_str, "10;");
	for (int i = 0; i < 5 + 2; i++)
	{
		if (i == 0)
			strcat(default_model_str, "30;");
		if (i == 1)
			strcat(default_model_str, "15;");
		if (i == 2)
			strcat(default_model_str, "15;");
		if (i == 3)
			strcat(default_model_str, "15;");
		if (i == 4)
			strcat(default_model_str, "20;");
		if (i == 5)
			strcat(default_model_str, "100;");
		if (i == 6)
			strcat(default_model_str, "7.5;");
	}
	g_key_file_set_string(gkf, "default_model", "hbound", default_model_str);
	//tweak
	strcpy(default_model_str, "");
	for (int i = 0; i < count_sym; i++)
		strcat(default_model_str, "1;");
	g_key_file_set_string(gkf, "default_model", "tweak", default_model_str);

	//limited
	strcpy(default_model_str, "");
	for (int i = 0; i < count_sym; i++)
		strcat(default_model_str, "1;");
	g_key_file_set_string(gkf, "default_model", "limited", default_model_str);

	//scale
	strcpy(default_model_str, "");
	for (int i = 0; i < count_sym; i++)
		strcat(default_model_str, "1;");
	g_key_file_set_string(gkf, "default_model", "scale", default_model_str);

	//partype
	strcpy(default_model_str, "");
	for (int i = 0; i < thetha.n * thetha.l; i++)
		strcat(default_model_str, "1;");
	for (int i = 0; i < thetha.n + thetha.n * 18; i++)
		strcat(default_model_str, "0;");
	for (int i = 0; i < 5 + 2; i++)
	{
		strcat(default_model_str, "0;");
	}
//	std::cout << "HERE_inside_6" << std::endl;

	g_key_file_set_string(gkf, "default_model", "partype", default_model_str);
	g_key_file_save_to_file(gkf, config.name_ini_file, &gerror);
	g_key_file_free(gkf);
	delete[] res_string_lambda;
	delete[]  res_string_n_l;
	delete[] default_model_str;

	return retval;
}


int read_config_file_deep(Config &config, Thetha &thetha, GError **err)
{
	int ret_val = 0;
	gchar*data = NULL;
	gsize size;
	GError *gerror = NULL;
	g_return_val_if_fail(err == NULL || *err == NULL, 1);
	if ((data = model_read_deep(config.curr_ini_file, &size, &gerror)) == NULL) {
		g_propagate_error(err, gerror);
		return 1;
	}
//	std::cout << "HERE_inside1" << std::endl;

	ret_val = model_load_deep(config, data, size, thetha, &gerror);
	if (ret_val == 1) {
		g_propagate_error(err, gerror);
		ret_val = 1;
	}
	g_free(data);
	return ret_val;
}

void prepare_deep_file(Config &config, Thetha &thetha)
{
	GError *gerror = NULL;
	create_curr_deep_ini_file(config, &gerror);
	read_config_file_deep(config, thetha, &gerror);
}

void print_param_and_error(const double *error, const Posterior &posterior)//���������� �� c++
{
	FILE * f_n = fopen("PARAM_N.txt", "w");
	FILE * f_l = fopen("PARAM_L.txt", "w");
	FILE * f_lambda = fopen("PARAM_LAMBDA.txt", "w");
	FILE * f_error = fopen("ERROR.txt", "w");

	for (int i = 0; i < N; i++)
	{
		fprintf(f_n, "%d\n", posterior.thetha[i].n);

		fprintf(f_l, "%d\n", posterior.thetha[i].l);

		fprintf(f_lambda, "%f\n", posterior.thetha[i].lambda);

		fprintf(f_error, "%f\n", error[i]);

	}
}
gchar * create_curr_deep_ini_file(Config &config, GError **err)//���������� �� c++
{
	gint fhandle;
	const gchar *tmpl = NULL;
	gchar *name_used = NULL;
	GError *gerror = NULL;
	GString*file_contents;
	g_return_val_if_fail(err == NULL || *err == NULL, NULL);
	if ((fhandle = g_file_open_tmp(tmpl, &name_used, &gerror)) == -1) {
		g_propagate_error(err, gerror);
		return NULL;
	}
	config.curr_ini_file = name_used;
	//close(fhandle);
	FILE * f = fopen(name_used, "w");
	int i = 0, j = 0;
	char ch;
	FILE * source, *target;
	source = fopen(config.name_ini_file, "r");
	if (source == NULL)
	{
		printf("Press any key to exit...Not default file\n");
		exit(EXIT_FAILURE);
	}
	target = fopen(config.curr_ini_file, "w");

	if (target == NULL)
	{
		fclose(source);
		printf("Press any key to exit...\n");
		exit(EXIT_FAILURE);
	}
	
	while ((ch = fgetc(source)) != EOF)
		fputc(ch, target);

	//printf("File copied successfully.\n");

	fclose(source);
	fclose(target);
	return NULL;
}