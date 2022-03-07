#include <iostream>
#include <chrono>
#include "weights_layer_out_ours/fc_weights.h"
#include "params.h"
#include "layers.h"
#include "weights_layer_out_ours/conv_weights.h"

int main() {

    auto start = std::chrono::steady_clock::now();

    /* ######################################### FC TEST #########################################*/

    float input[FLATTEN_SIZE];
    float fc_out[FC_ACT_SIZE];
    float fc_ref[FC_ACT_SIZE];

    int i;
    int correct_values = 0, total_values = 0;


    FILE* flatten_content = fopen("/home/federico/CLionProjects/cnn-xilinx/c/weights_layer_out_ours/flatten_out.txt","r");
    if(flatten_content == NULL)
    {
        printf("Couldn't open ../../../../ref/flatten_py.out");
        exit(1);
    }

    FILE* fc_content = fopen("/home/federico/CLionProjects/cnn-xilinx/c/weights_layer_out_ours/dense_out.txt","r");
    if(fc_content == NULL)
    {
        printf("Couldn't open ../../../../ref/fc_py.out");
        exit(1);
    }


    for(i = 0; i < FLATTEN_SIZE; i++)
        fscanf(flatten_content,"%f,",&input[i]);

    for(i = 0; i < FC_ACT_SIZE; i++)
        fscanf(fc_content,"%f,",&fc_ref[i]);


    fc(fc_out, input, fc_weights, fc_bias);


    printf("Checking FC Layer ...\n");

    for(i = 0; i < FC_ACT_SIZE; i++)
    {
        total_values++;
        if(fc_out[i] - fc_ref[i] > eps || fc_ref[i] - fc_out[i] > eps)
        {
            if(correct_values + 1 == total_values)
                printf("Missmatch in FC check\n");
        }
        else
            correct_values++;
    }
    printf("DONE: %d out of %d are correct\n\n", correct_values, total_values);

/* ######################################### POOL TEST #########################################*/

//    float pool_out[P_SIZE * P_SIZE * P_CHANNELS];
//    float pool_ref[P_SIZE][P_SIZE][P_CHANNELS];
//    float image[A_SIZE * A_SIZE * A_CHANNELS];
//    float a;
//
//    int i,j,k;
//    int correct_values = 0, total_values = 0;
//    //hls::stream<float24_t> out("output_stream");
//    //hls::stream<float24_t> in("input_stream");
//
//    FILE* conv_content = fopen("/home/federico/CLionProjects/cnn-xilinx/c/weights_layer_out_ours/conv2d_out.txt","r");
//    if(conv_content == NULL)
//    {
//        printf("Couldn't open ../../../../ref/conv_py.out");
//        exit(1);
//    }
//
//    FILE* pool_content = fopen("/home/federico/CLionProjects/cnn-xilinx/c/weights_layer_out_ours/max_pooling2d_out.txt","r");
//    if(pool_content == NULL)
//    {
//        printf("Couldn't open ../../../../ref/pool_py.out");
//        exit(1);
//    }
//
//
//        for(i = 0; i < A_SIZE; i++)
//            for(j = 0; j < A_SIZE; j++)
//                for(k = 0; k < A_CHANNELS; k++)
//            {
//                fscanf(conv_content,"%f,",&a);
//                image[i * A_SIZE * A_CHANNELS + j * A_CHANNELS + k] = (float)a;
//            }
//
//        for(i = 0; i < P_SIZE; i++)
//            for(j = 0; j < P_SIZE; j++)
//                for(k = 0; k < P_CHANNELS; k++)
//            {
//                fscanf(pool_content,"%f,",&a);
//                pool_ref[i][j][k] = (float) a;
//            }
//
//    /// Send stream
////    for(i = 0 ; i < A_SIZE * A_SIZE * A_CHANNELS; i++)
////        in<<image[i];
//
//    //pool(out, in);
//    pool(pool_out, image);
//
//    /// Receive stream
////    for(i = 0 ; i < P_SIZE * P_SIZE * P_CHANNELS; i++)
////        out>>pool_out[i];
//
//    printf("Checking POOL  ...\n");
//
//    for(k = 0; k < P_CHANNELS; k++)
//        for(i = 0; i < P_SIZE; i++)
//            for(j = 0; j < P_SIZE; j++)
//            {
//                total_values++;
//                if(pool_out[i * P_SIZE * P_CHANNELS + j * P_CHANNELS + k] - pool_ref[i][j][k] > eps || pool_ref[i][j][k] - pool_out[i * P_SIZE * P_CHANNELS + j * P_CHANNELS + k] > eps)
//                {
//                    if(correct_values + 1 == total_values)
//                        printf("Missmatch in POOL check\n");
//                }
//                else
//                    correct_values++;
//            }
//    printf("DONE: %d out of %d are correct\n\n", correct_values, total_values);



/* ######################################### CONV TEST #########################################*/
//    float conv_out[A_SIZE * A_SIZE * A_CHANNELS];
//    float conv_ref[A_SIZE][A_SIZE][A_CHANNELS];
//
//    int i,j,k;
//
//    float a;
//
//    conv(conv_out,image, conv_weights, conv_bias);
//
////    for(i = 0 ; i < A_SIZE * A_SIZE * A_CHANNELS; i++)
////        out>>conv_out[i];
//
//    FILE* conv_content = fopen("/home/federico/CLionProjects/cnn-xilinx/c/weights_layer_out_ours/conv2d_out.txt","r");
//    if(conv_content == NULL)
//    {
//        printf("Couldn't open ../../../../ref/conv_py.out");
//        exit(1);
//    }
//
//
//        for(i = 0; i < A_SIZE; i++)
//            for(j = 0; j < A_SIZE; j++)
//                for(k = 0; k < A_CHANNELS; k++)         // TODO SECONDO ME QUESTO è quello più interno
//            {fscanf(conv_content,"%f,",&a);
//                conv_ref[i][j][k] = (float)a;}
//    int correct_values = 0, total_values = 0;
//
//    printf("Checking CONV Layer ...\n");
//
//    for(k = 0; k < A_CHANNELS; k++)
//        for(i = 0; i < A_SIZE; i++)
//            for(j = 0; j < A_SIZE; j++)
//            {
//                total_values++;
//                if(conv_out[i* A_SIZE* A_CHANNELS + j*A_CHANNELS + k] - conv_ref[i][j][k] > eps || conv_ref[i][j][k] - conv_out[i* A_SIZE* A_CHANNELS + j*A_CHANNELS + k] > eps)
//                {
//                    if(correct_values + 1 == total_values)
//                        printf("Missmatch in CONV1 check\n");
//                }
//                else
//                    correct_values++;
//            }
//    printf("DONE: %d out of %d are correct\n\n", correct_values, total_values);
//
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "EXECUTION TIME: " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    return 0;
}
