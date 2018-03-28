#ifndef DEBAYER_H
#define DEBAYER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdint.h>
#include <math.h>
#include "lodepng.h"
#include <QDebug>

using namespace std;

class DeBayer
{
    uint32_t width;             //Width of RAW image
    uint32_t height;            //Height of RAW data
    uint32_t imageDims;         // width*height
    uint32_t length;            // Length of RAW data stream
    uint8_t * myBuffer;         // Buffer to store data on memory
    uint8_t * myArray;          // Array to store the data for processing
    uint32_t channelLength;     // length of each channel

    uint8_t * channelR, * channelG1, * channelG2, * channelB;   //arrays to store individual channels

public:
    DeBayer();
    // Function to extract individual channels RGGB
    void extractChannels();
    // Function to save channels as gray-scale PNG images
    void savePng();
};

#endif // DEBAYER_H
