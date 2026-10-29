/* Name: Mustafa Ismail
 * Reg No     : L1S26BSCS0089
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int dy = 0, mo = 0, yr = 0;
    char sl;
    inFile >> dy >> sl >> mo >> sl >> yr;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    ofstream slip("receipts.txt");
    cout << "Parking report for " << dy << "/" << mo << "/" << yr << endl;
    slip << "Receipts for " << dy << "/" << mo << "/" << yr << endl;

    char tag[15], kind, colon, topTag[15] = "";
    int inH, inM, outH, outM;
    int seen = 0, cars = 0, bikes = 0, earned = 0, longest = -1;

    while (seen < 30 && inFile >> tag >> kind >> inH >> colon >> inM >> outH >> colon >> outM) {
        int span = (outH * 60 + outM) - (inH * 60 + inM);
        int billed = (span + 59) / 60;
        if (billed == 0) {
            billed = 1;
        }

        int fee;
        const char* label;
        if (kind == 'C') {
            fee = billed * 100;
            label = "Car";
            cars++;
        }
        else {
            fee = billed * 40;
            label = "Bike";
            bikes++;
        }

        cout << tag << " " << label << " " << span / 60 << " h " << span % 60 << " min Fee: " << fee << endl;
        slip << tag << " " << fee << endl;

        earned = earned + fee;
        if (span > longest) {
            longest = span;
            strcpy(topTag, tag);
        }
        seen++;
    }
    inFile.close();
    slip.close();

    if (seen == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << seen << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << earned << endl;
    cout << "Longest stay: " << topTag << " (" << longest / 60 << " h " << longest % 60 << " min)" << endl;
    return 0;
}
