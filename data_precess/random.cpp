
#include "stdafx.h"

void DoRandom(double miu, double sigma, double min, double max)
{
	double dValue[40];
	double dValue1[40];
	srand(GetTickCount());
	for (int i = 0; i < 40; i++)
	{
		dValue[i] = AverageRandom(min, max);
		dValue1[i] = NormalRandom(miu, sigma, min, max);
			}
}

double AverageRandom(double min, double max)
{
	int minInteger = (int)(min * 10000);
	int maxInteger = (int)(max * 10000);
	int randInteger = rand()*rand();
	int diffInteger = maxInteger - minInteger;
	int resultInteger = randInteger % diffInteger + minInteger;
	return resultInteger / 10000.0;
}
double Normal(double x, double miu, double sigma) //概率密度函数
{
	return 1.0 / sqrt(2 * M_PI) /sigma * exp(-1 * (x - miu)*(x - miu) / (2 * sigma*sigma));
}
double NormalRandom(double miu, double sigma, double min, double max)//产生正态分布随机数
{
	double x;
	double dScope,miu_max;
	double y;
	miu_max = Normal(miu, miu, sigma)*10000;
	do
	{
		x = AverageRandom(min, max);
		y = Normal(x, miu, sigma);
		dScope = AverageRandom(0.0, miu_max)/10000;
	} while (dScope > y);
	return x;
}