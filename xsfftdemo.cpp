/* 
    This is a bit of a demo app in that this will take the FFT of a file that contains a column vector of
    elements.  This function does not care how many elements are in the input file.
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "xsfft.h"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned long dataLength = 100;
    xsComplex *data = (xsComplex *)calloc(dataLength, sizeof(xsComplex));

    srand(0);
    xsComplex *dataIterator = data;
    for(unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex, ++dataIterator) {
        //dataIterator->set(1.0, 0.0);
        //dataIterator->set((rand() % USHRT_MAX) - SHRT_MAX, 0.0);
        //dataIterator->set(sin(2.0 * xsPI * (double)signalIndex), 0.0);
        if (signalIndex < 100) {
            dataIterator->set((double)signalIndex, 0.0);
        } else {
            dataIterator->set(0.0, 0.0);
        }
        cout << dataIterator->real() << "\n";
    }

    xsCoerceDataRadix2(data, &dataLength);
    bool success = xsFFT(data, dataLength);
    
    if (success) {
        cout << "\n\nFFT WIN!!\n\n";
    } else {
        cout << "\n\nFFT FAIL...\n\n";
    }
    
    dataIterator = data;
    for(long freqIndex = 0; freqIndex < dataLength; ++freqIndex, ++dataIterator) {
        cout << dataIterator->real() << "\n";
    }
    
    success = xsIFFT(data, dataLength);
    
    if (success) {
        cout << "\n\nIFFT WIN!!\n\n";
    } else {
        cout << "\n\nIFFT FAIL...\n\n";
    }
    
    dataIterator = data;
    for(unsigned long freqIndex = 0; freqIndex < dataLength; ++freqIndex, ++dataIterator) {
        cout << dataIterator->real() << "\n";
    }

    free(data);

    return success ? 0 : -1;
}
