/* Name: Mustafa Ismail
 * Reg No     : L1S26BSCS0089
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int pick;

    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> pick)) {
            break;
        }

        if (pick == 1) {
            char cat[20];
            int amt;
            cout << "Enter category: ";
            cin >> cat;
            cout << "Enter amount: ";
            cin >> amt;
            if (amt <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream book("expenses.txt", ios::app);
                book << cat << " " << amt << endl;
                book.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (pick == 2) {
            char names[100][20];
            int vals[100];
            int rows = 0;
            ifstream book("expenses.txt");
            while (rows < 100 && book >> names[rows] >> vals[rows]) {
                rows++;
            }
            book.close();

            if (rows == 0) {
                cout << "No expenses yet." << endl;
            }
            else {
                int grand = 0, big = 0;
                for (int r = 0; r < rows; r++) {
                    cout << r + 1 << ". " << names[r] << " " << vals[r] << endl;
                    grand = grand + vals[r];
                    if (vals[r] > vals[big]) {
                        big = r;
                    }
                }
                cout << "Total spent: " << grand << endl;
                cout << "Largest expense: " << names[big] << " (" << vals[big] << ")" << endl;
            }
        }
        else if (pick == 3) {
            char want[20], cur[20];
            int amt, hits = 0, sum = 0;
            cout << "Enter category: ";
            cin >> want;
            ifstream book("expenses.txt");
            while (book >> cur >> amt) {
                if (strcmp(cur, want) == 0) {
                    hits++;
                    sum = sum + amt;
                }
            }
            book.close();

            if (hits == 0) {
                cout << "No expenses found for " << want << endl;
            }
            else {
                cout << "Expenses in " << want << ": " << hits << endl;
                cout << "Total for " << want << ": " << sum << endl;
            }
        }
        else if (pick == 4) {
            ofstream book("expenses.txt");
            book.close();
            cout << "All expenses cleared." << endl;
        }
        else if (pick == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    } while (pick != 5);

    return 0;
}
