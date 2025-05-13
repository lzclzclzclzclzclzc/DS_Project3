
#include "ClosedHashTable.h"
#include <iostream>
using namespace std;

int main() {
    int data[] = { 15, 21, 29, 35, 37, 40, 43, 50, 55, 64, 66, 72, 81, 90, 95, 100 };
    const int n = sizeof(data) / sizeof(data[0]);

    ClosedHashTable<int, int> linearTable(17, 1, LINEAR);
    ClosedHashTable<int, int> quadraticTable(17, 1, QUADRATIC);

    for (int i = 0; i < n; ++i) {
        linearTable.Insert(data[i]);
        quadraticTable.Insert(data[i]);
    }

    int linearProbes = 0, quadProbes = 0;

    cout << "Linear Probing Search Process:" << endl;
    for (int i = 0; i < n; ++i) {
        int probes = 0;
        linearTable.Search(data[i], &probes);
        linearProbes += probes;
        cout << "Searching for " << data[i] << ", Probes: " << probes << endl;
    }

    cout << "\nQuadratic Probing Search Process:" << endl;
    for (int i = 0; i < n; ++i) {
        int probes = 0;
        quadraticTable.Search(data[i], &probes);
        quadProbes += probes;
        cout << "Searching for " << data[i] << ", Probes: " << probes << endl;
    }

    cout << "\\nTotal Probe Comparison:" << endl;
    cout << "Total Probes (Linear): " << linearProbes << endl;
    cout << "Total Probes (Quadratic): " << quadProbes << endl;

    return 0;
}
