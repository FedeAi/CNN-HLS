//
// Created by federico on 28/02/22.
//

#ifndef CNN_XILINX_PARAMS_H
#define CNN_XILINX_PARAMS_H

#define FLATTEN_SIZE		5408

#define FC_WEIGHTS_H		5408
#define FC_WEIGHTS_W		10
#define FC_BIAS_SIZE		10
#define FC_ACT_SIZE		10
#define eps 0.00002

#define A_SIZE				26
#define A_CHANNELS			32


#define P_SIZE				13
#define P_CHANNELS			32
#define P_KERNEL_SIZE		2
#define P_STRIDE			2 // this is the same of kernel size ( not real stride )

#define IMAGE_SIZE 			28
#define IMAGE_CHANNELS		1

#define CONV_KERNEL_SIZE 	3
#define CONV_CHANNELS 		1
#define CONV_FILTERS 		32
#define CONV_BIAS_SIZE 		32
#define CONV_STRIDE 		1




#endif //CNN_XILINX_PARAMS_H
