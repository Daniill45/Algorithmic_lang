#include <string>
#include <iostream>
#include <fstream>
const double inf=1e123;
template <typename T>
void logUserAction(T& action) {
    ofstream logfile("log_actions.txt", ios::app);
    if (logfile.is_open()) {
        logfile << action << "\n";
        logfile.close();
    } else {
        cerr << "Ошибка открытия файла для логирования.\n";
    }
}
template <typename T>
void is_valid(T &varible,T a,T b)
{

    while (!(cin >> varible) || (varible < a) || (varible > b) || (cin.peek() != '\n'))
    {
        logUserAction(varible);
        cout << "Ошибка: Введите корректное значение: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    logUserAction(varible);

    

}




