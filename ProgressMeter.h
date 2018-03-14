#ifndef PROGRESS_METER_H
#define PROGRESS_METER_H
#include <iostream>
#include <cmath>

using namespace std;

void printProgress(float progress) {
    if (progress > 1.0) return;

    unsigned width = 100;

    cout << "[";
    unsigned pos = width * progress;

    for (unsigned count = 0; count < width; ++count) {
        if (count <= pos) cout << "#";
        //else if (count == pos) cout << ">";
        else cout << "-";
    }
    cout << "] ";
    cout << roundf(progress * 10000) / 100 << "%        \r";
    cout.flush();

    if (progress == 1.0) 
        cout << endl << endl << "Done." << endl;
}

#endif
