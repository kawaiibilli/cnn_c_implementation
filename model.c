#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "layers.c"


tensor* forward(tensor * in)
{
	


	conv2d_filter * layer1 = get_filter(9,3,64);
	conv2d_filter *layer2 = get_filter(1,64,32);
	conv2d_filter *layer3 = get_filter(5,32,3);
	
	tensor_details(in,"input");
	tensor* out = convolution_2d(in,layer1,0,1);
	tensor_details(out, "layer1 out");
	relu(out);
	
	tensor* out2 = convolution_2d(out,layer2,0,1);
	tensor_details(out2, "layer2 out");
	relu(out2);

	tensor * out3 = convolution_2d(out2,layer3,0,1);
	tensor_details(out3, "layer3 out");

	return out3;
}