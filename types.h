#ifndef TYPE
#define TYPE

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double *** data;     //c * h * w
	int c,h,w;

}tensor;

typedef struct
{
	double **** kernel;   //out_channels * in_channels * filter_size * filter*size
	int filter_size,in_channels,out_channels;

}conv2d_filter;

#endif