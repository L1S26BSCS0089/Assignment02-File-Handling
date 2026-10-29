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
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n = 0;
    inFile >> n;
    if (n > 30) {
        cout << "Too many students!" << endl;
        return 1;
    }
    inFile.ignore(100, '\n');

    ofstream award("scholarship.txt");
    char nm[30], topNm[30] = "";
    double gpa, sum = 0, best = -1;
    int got = 0, eligible = 0;

    for (int k = 0; k < n; k++) {
        if (!inFile.getline(nm, 30, ',')) {
            break;
        }
        if (!(inFile >> gpa)) {
            break;
        }
        inFile.ignore(100, '\n');

        cout << "[" << nm << "] CGPA: " << gpa << endl;
        got++;
        sum = sum + gpa;

        if (gpa >= 3.5) {
            award << nm << "," << gpa << endl;
            eligible++;
        }
        if (gpa > best) {
            best = gpa;
            strcpy(topNm, nm);
        }
    }
    inFile.close();
    award.close();

    if (got < n) {
        cout << "Warning: only " << got << " of " << n << " records found." << endl;
    }
    if (got == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << got << endl;
    cout << "Average CGPA: " << sum / got << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topNm << " (" << best << ")" << endl;
    return 0;
}
