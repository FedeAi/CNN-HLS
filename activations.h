//
// Created by federico on 28/02/22.
//

#ifndef CNN_XILINX_ACTIVATIONS_H
#define CNN_XILINX_ACTIVATIONS_H

float relu(float a)
{
    return a > 0 ? a : 0;
}

#endif //CNN_XILINX_ACTIVATIONS_H
