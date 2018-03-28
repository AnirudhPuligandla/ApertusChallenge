#include <QCoreApplication>

#include <iostream>
#include <stdlib.h>
#include "lodepng.h"
#include <fstream>
#include <QDebug>
#include <QDir>
#include <stdint.h>
#include <math.h>
#include "debayer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Class to handle debayering of input data
    DeBayer deBayer;

    // Call function to separate the channels from data
    deBayer.extractChannels();

    //call function to save the channels as separate PNG files using lodePNG
    deBayer.savePng();

    return 0;
}
