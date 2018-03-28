#include "debayer.h"
#include "lodepng.h"

DeBayer::DeBayer()
{
    // Get the dimensions of data
    width = 4096;
    height = 3092;
    imageDims = width*height;

    // read RAW input stream
    ifstream myData("portrait-gainx2-offset2047-20ms-02.raw12", ifstream::binary);

    // convert to 8-bit in buffer
    myData.seekg(0, myData.end);
    length = myData.tellg();
    myData.seekg(0, myData.beg);

    myBuffer = new uint8_t[length];
    myData.read((char *)myBuffer, length);
    myData.close();

    channelLength = imageDims/4;

    // Initialize arrays
    channelR = new uint8_t[channelLength];
    channelG1 = new uint8_t[channelLength];
    channelG2 = new uint8_t[channelLength];
    channelB = new uint8_t[channelLength];

    myArray = new uint8_t[imageDims];
}

void DeBayer::extractChannels()
{
    int j = 0;
    for (long long index = 0; index < length; index += 3)
    {
        myArray[j]   = myBuffer[index];
        myArray[j+1] = ((myBuffer[index+1] & 0x0F) << 4) | (myBuffer[index+2] >> 4);
        j+=2;
    }

    // Extract the 4 channels

    // odd rows contain GB channels and even rows contain RG channels
    int gbCount = 0, rgCount = 0;
    for (long long index = 0; index < imageDims; index += 2)
    {
        if ((index % (width*2)) < width)
        {
            channelR[rgCount] = myArray[index];
            channelG1[rgCount] = myArray[index + 1];
            rgCount++;
        }
        else
        {
            channelG2[gbCount] = myArray[index];
            channelB[gbCount] = myArray[index + 1];
            gbCount++;
        }
    }
}

void DeBayer::savePng()
{
    //qDebug() << "Saving";
    //Save the channels as individual grayscale PNG images
    lodepng::encode("Red.png", channelR, width/2, height/2, LCT_GREY);
    lodepng::encode("Green1.png", channelG1, width/2, height/2, LCT_GREY);
    lodepng::encode("Green2.png", channelG2, width/2, height/2, LCT_GREY);
    lodepng::encode("Blue.png", channelB, width/2, height/2, LCT_GREY);
}
