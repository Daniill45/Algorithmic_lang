#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2) {
        ofstream myfile;
        myfile.open ("error.txt",ofstream::app);
        myfile << "Error message!\n";
        myfile.close();
        return 1;
    }

    string name = argv[1];

    cout << "Hello, " << name << endl;

    return 0;
}
