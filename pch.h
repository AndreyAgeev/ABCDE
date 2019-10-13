// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#ifndef PCH_H
#define PCH_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Config.h"
#include <random>

#include "Model.h"
#include "Sampling.h"

#include "ABCDE_SSM.h"
#include "DE.h"

#define DEEP_FILE "deep_test.ini"
#define OUT_DEEP_FILE "deep_test.ini-deep-output"
#define N 50
#define NORM 0
#define EXPON 1
#define NORM_WITH_PARAM 2
#define ERROR_MODE -1
#define LOFFSET log((double)RAND_MAX)
// TODO: add headers that you want to pre-compile here

#endif //PCH_H
