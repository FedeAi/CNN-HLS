#include <iostream>
#include <chrono>
#include "weights_layer_out_ours/fc_weights.h"
#include "params.h"
#include "layers.h"
#include "weights_layer_out_ours/conv_weights.h"

int main(int argc, char ** argv){

    auto start = std::chrono::steady_clock::now();

    if (argc != 2) {
        std::cout << "you must specify an image_path";
        return 0;
    }
    float conv_out[A_SIZE * A_SIZE * A_CHANNELS];
    float pool_out[P_SIZE * P_SIZE * P_CHANNELS];
    float fc_out[FC_ACT_SIZE];
    float image[28 * 28 * 1];

    // read image
    FILE* image_content  = fopen(argv[1],"r");
    if(image_content == NULL)
    {
        printf("Couldn't open %s", argv[1]);
        exit(1);
    }
    for(int i = 0; i < A_CHANNELS * A_SIZE * A_SIZE; i++)
        fscanf(image_content,"%f,",&image[i]);

    // conv layer
    conv(conv_out, image, conv_weights, conv_bias);
    // max pooling layer
    pool(pool_out, conv_out);
    // fully connected layer
    fc(fc_out, pool_out, fc_weights, fc_bias);

    // output results
    int index_max = 0; // argmax
    for(int i = 0; i < FC_ACT_SIZE; i++){
        if(fc_out[i] > fc_out[index_max]){
            index_max = i;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;


    std::cout<< std::endl <<"predicted number: "<< index_max << " probability: "<< fc_out[index_max] << std::endl;
    std::cout<<"#################################################" << std::endl;
    std::cout<<" predicted output: " << std::endl;
    for(int i = 0; i < FC_ACT_SIZE; i++){
        std::cout << "[" << i <<"]\t"<<fc_out[i] << std::endl;
    }
    std::cout<<"#################################################" << std::endl;
    std::cout << "EXECUTION TIME: " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

    return 0;
}
