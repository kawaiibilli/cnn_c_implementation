#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define max(x,y) ((x>y)?x:y)


tensor* get_tensor(int h, int w, int c)
{
	tensor * tmp = (tensor *) malloc(sizeof(tensor));
	tmp->h = h;
	tmp->w = w;
	tmp->c = c;

	tmp->data = (double ***)malloc(sizeof(double **)*tmp->c);
	for(int i=0;i<c;i++)
	{
		tmp->data[i]=(double**)malloc(sizeof(double *) * tmp->h);
		for(int j=0;j<h;j++)
		{
			tmp->data[i][j]=(double *)malloc(sizeof(double)* tmp->w);
			for(int k=0;k<w;k++)
				tmp->data[i][j][k]=(double)(rand()%256);
		}

	}

	return tmp;
}


conv2d_filter* get_filter(int filter_size, int in_channels, int out_channels)
{
	conv2d_filter* tmp = (conv2d_filter* )malloc(sizeof(conv2d_filter));
	tmp->filter_size = filter_size;
	tmp->in_channels = in_channels;
	tmp->out_channels = out_channels;

	tmp->kernel = (double ****)malloc(sizeof(double ***)*out_channels);
	for(int i=0;i<out_channels;i++)
	{
		tmp->kernel[i]=(double ***)malloc(sizeof(double **)*in_channels);
		for(int j=0;j<in_channels;j++)
		{
			tmp->kernel[i][j] = (double **)malloc(sizeof(double *)* filter_size);
			for(int k=0;k<filter_size;k++)
			{
				tmp->kernel[i][j][k] = (double *)malloc(sizeof(double)*filter_size);
				for(int l=0;l<filter_size;l++)
					tmp->kernel[i][j][k][l]= (double) (rand()%25);
			}
		}
	}


	return tmp;

}


tensor * convolution_2d(tensor* in_fmap, conv2d_filter* filter,int padding ,int stride)
{
	int out_h = (in_fmap->h - filter->filter_size + 2*padding)/stride + 1;
	int out_w = (in_fmap->w - filter->filter_size + 2*padding)/stride + 1;
	tensor * out_fmap = get_tensor(out_h,out_w,filter->out_channels);

	for(int out_c_it=0; out_c_it<filter->out_channels; out_c_it++)
	{
		int h_pos=0;
		for(int h_it=0; h_it<((in_fmap->h - filter->filter_size + 2*padding)/stride+1); h_it+=stride)
		{
			int c_pos=0;
			for(int c_it=0; c_it<((in_fmap->c - filter->filter_size +2*padding)/stride +1);c_it+=stride)
			{
				double dot=0;
		
				for(int i=0;i<filter->in_channels;i++)
				{
					for(int j=0;j<filter->filter_size;j++)
					{
						for(int k=0;k<filter->filter_size;k++)
						{
							dot+= filter->kernel[out_c_it][i][j][k]*in_fmap->data[i][j+h_it][k+c_it];
						}
					}
				}

				out_fmap->data[out_c_it][h_pos][c_pos]=dot;
				c_pos++;
			}
			h_pos++;
		}
	}

	return out_fmap;
}

void relu(tensor* in_fmap)
{
	for(int i=0;i<in_fmap->c;i++)
		for(int j=0;j<in_fmap->h;j++)
			for(int k=0;k<in_fmap->w;k++)
				in_fmap->data[i][j][k]=max(in_fmap->data[i][j][k],0.0);


}

void tensor_details(tensor * fmap,char * str)
{
	printf("%s tensor (channels, height, width) = %d,%d,%d\n",str,fmap->c,fmap->h,fmap->w);
}
