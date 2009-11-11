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
    for(unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex) {
        if (signalIndex < 100) {
            (data + signalIndex)->set((double)signalIndex, 0.0);
        } else {
            (data + signalIndex)->set(0.0, 0.0);
        }
        cout << (data + signalIndex)->real() << endl;
    }

    xsCoerceDataRadix2(data, &dataLength);
    
    cout << "-------------------------------FFT---------------------------------------" << endl;
    
    bool success = xsFFT(data, dataLength);
    for(long freqIndex = 0; freqIndex < dataLength; ++freqIndex) {
        cout << (data + freqIndex)->real() << endl;
    }
    
    cout << "-------------------------------IFFT--------------------------------------" << endl;
    
    success = xsIFFT(data, dataLength);
    for(unsigned long freqIndex = 0; freqIndex < dataLength; ++freqIndex) {
        cout << (data + freqIndex)->real() << endl;
    }
    
    cout << "--------------------------Interpolation----------------------------------" << endl;
    
    for(unsigned long signalIndex = 0; signalIndex < dataLength; ++signalIndex) {
        if (signalIndex < 100) {
            (data + signalIndex)->set((double)signalIndex, 0.0);
        } else {
            (data + signalIndex)->set(0.0, 0.0);
        }
        cout << (data + signalIndex)->real() << endl;
    }
    
    xsInterpolateWithFactor2(data, &dataLength);
    for(unsigned long dataIndex = 0; dataIndex < dataLength; ++dataIndex) {
        cout << (data + dataIndex)->real() << endl;
    }

    free(data);

    return success ? 0 : -1;
}
