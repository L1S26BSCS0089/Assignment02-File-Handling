/* Name: Mustafa Ismail
 * Reg No     : L1S26BSCS0089
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
// FIX 1: fstream header was missing so ifstream and ofstream is not known to the compiler
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: the check was wrong, it was printing error when file is open, need not sign here
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: first line Code Qty Price is header and it was not skip, so reading go wrong from start
    inFile.ignore(100, '\n');

    // FIX 4: plain ofstream delete the old lines of reorder.txt, so ios::app is added to keep them
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 5: total was int so the decimal part is lost every time, it must be double
    double total = 0;

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: endl was missing so all low items come in one line in reorder.txt
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
