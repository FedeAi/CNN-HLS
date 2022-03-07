//
// Created by federico on 28/02/22.
//
#ifndef CNN_XILINX_LAYERS_H
#define CNN_XILINX_LAYERS_H

#include <vector>
#include "params.h"
#include "activations.h"


void fc(float out[], float in[], float weight[FC_WEIGHTS_H][FC_WEIGHTS_W], float bias[FC_BIAS_SIZE])
{
    float read;
    float output[FC_ACT_SIZE] = {0};
    for(int j = 0; j < FC_WEIGHTS_H; j++)
    {
        read = in[j];
        for(int i = 0; i < FC_WEIGHTS_W; i++)
        {
            output[i] += weight[j][i] * read;
        }
    }
    for(int i = 0; i < FC_WEIGHTS_W; i++)
        out[i] = relu(output[i] + bias[i]);

}

void pool(float out[], float in[])
{
    int BUFFER_SIZE = (P_SIZE*P_CHANNELS);

    int i,j,k,l,m;
    float read;
    float pool_buff[BUFFER_SIZE][1];
    int z = 0;
    for(i = 0 ; i < P_SIZE; i++)
        for(l = 0; l < P_KERNEL_SIZE; l++)
        {
            for(j = 0 ; j < P_SIZE; j++)
                for(m = 0; m < P_KERNEL_SIZE; m++)
                    for(k = 0 ; k < P_CHANNELS; k++)
                    {
                        read = in[z];
                        z++;
                        if(l == 0 && m == 0)
                            pool_buff[j*P_CHANNELS + k][0] = read;

                        else
                            pool_buff[j*P_CHANNELS + k][0] = pool_buff[j*P_CHANNELS + k][0] > read? pool_buff[j*P_CHANNELS + k][0] : read;


                        if(l == (P_KERNEL_SIZE - 1) && m == (P_KERNEL_SIZE - 1))
                            out[z] = pool_buff[j*P_CHANNELS + k][0];

                    }
            for(int skip = P_SIZE * P_STRIDE ; skip < A_SIZE; skip++)
                for(int channel = 0; channel < P_CHANNELS; channel++) {
                    //in>>read;
                    z++;
                }
        }


//    for(int skip_row = P_SIZE * P_STRIDE ; skip_row < A_SIZE; skip_row++)
//        for(int skip_col = 0 ; skip_col < A_SIZE; skip_col++)
//            for(int skip_channel = 0 ; skip_channel < A_CHANNELS; skip_channel++){
//                //in>>read;
//                z++;
//            }

}


void conv(float out[], float in[], float weight[CONV_KERNEL_SIZE][CONV_KERNEL_SIZE][CONV_CHANNELS][CONV_FILTERS], float bias[CONV_BIAS_SIZE])
{
    int BUFFER_SIZE  = (IMAGE_SIZE * IMAGE_CHANNELS * (CONV_KERNEL_SIZE -1) + CONV_KERNEL_SIZE * IMAGE_CHANNELS);
    int i,j,k,filter, contor = 0;
    float sum, placeholder;
    int row_offset, col_offset, channel_offset;
    //float conv_buff[BUFFER_SIZE];

    std::vector<float> conv_buff;

    /// DEBUG
    int attempted_reads1 = 0, reads1 = 0;
    int attempted_reads2 = 0, reads2 = 0;
    int attempted_reads3 = 0, reads3 = 0;

    int z = 0;
    /*
     * Read the initial buffer
     * */

    for(i = 0; i < BUFFER_SIZE;i++)
    {
//        attempted_reads1++;
//        if(in.empty() == 1)
//        {
//#ifndef __SYNTHESIS__
//            printf("\nInput stream is empty at \"Initial read state\"");
//#endif
//        }
//        else
//        {
            placeholder = in[z];
            z++;

            conv_buff.push_back(placeholder);
            reads1++;
//        }
    }

    conv_label5:for(i = 0; i < (IMAGE_SIZE - CONV_KERNEL_SIZE + 1); i += CONV_STRIDE)
    conv_label4:for(j = 0; j < (IMAGE_SIZE - CONV_KERNEL_SIZE + 1); j += CONV_STRIDE)
{


    conv_label3:for(filter = 0; filter < CONV_FILTERS; filter++)
{
    sum = 0;
    conv_label2:for(row_offset = 0; row_offset <CONV_KERNEL_SIZE; row_offset++)
    conv_label1:for(col_offset = 0; col_offset <CONV_KERNEL_SIZE; col_offset++)
    conv_label0:for(channel_offset = 0; channel_offset < CONV_CHANNELS; channel_offset++)
    sum += conv_buff[row_offset*IMAGE_SIZE * IMAGE_CHANNELS +  col_offset * IMAGE_CHANNELS + channel_offset] * weight[row_offset][col_offset][channel_offset][filter];
    out[z] = relu(sum + bias[filter]);
}

    if((j + CONV_STRIDE < (IMAGE_SIZE - CONV_KERNEL_SIZE + 1)))
        for(int p = 0 ; p<IMAGE_CHANNELS; p++)
        {
            attempted_reads3++;
//            if(in.empty() == 1)
//            {
//#ifndef __SYNTHESIS__
//                printf("\nInput stream is empty at \"Next element state\"");
//#endif
//            }
//            else
//            {
                reads3++;
                placeholder = in[z];
                z++;
                conv_buff.push_back(placeholder);
            }
//        }
//    else
    if((i + CONV_STRIDE < (IMAGE_SIZE - CONV_KERNEL_SIZE + 1)) && (j + CONV_STRIDE >= (IMAGE_SIZE - CONV_KERNEL_SIZE + 1)))
        for(int p = 0 ; p<CONV_KERNEL_SIZE * IMAGE_CHANNELS; p++)
        {
            attempted_reads2++;
//            if(in.empty() == 1)
//            {
//#ifndef __SYNTHESIS__
//                printf("\nInput stream is empty at \"Endline\"");
//#endif
//            }
//            else
//            {
                reads2++;
                placeholder = in[z];
                z++;
                conv_buff.push_back(placeholder);
//            }
        }


}
#ifndef __SYNTHESIS__
    printf("\n===========");
    printf("\nStatistics:");
    printf("\n===========");

    printf("\nInitial buffer atempted to read %d and succeeded %d", attempted_reads1, reads1);
    printf("\nEndline buffer atempted to read %d and succeeded %d", attempted_reads2, reads2);
    printf("\nNextelm buffer atempted to read %d and succeeded %d", attempted_reads3, reads3);
#endif

}



#endif //CNN_XILINX_LAYERS_H
