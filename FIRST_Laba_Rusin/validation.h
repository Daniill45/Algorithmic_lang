#include <string>
#include <iostream>
#include <fstream>
const int empty_strings = 1000;
const double inf=1e123;
template <typename T>
void logUserAction(T& action) {
    ofstream logfile("log_actions.log", ios::app);
    if (logfile.is_open()) {
        logfile << action << "\n";
        logfile.close();
    } else {
        cerr << "Ошибка открытия файла для логирования.\n";
    }
}
template <typename T1,typename T2,typename T3>
void is_valid(T1 &varible,T2 a,T3 b)
{

    while (!(cin >> varible) || (varible < a) || (varible > b) || (cin.peek() != '\n'))
    {
        logUserAction(varible);
        cout << "Ошибка: Введите корректное значение: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    logUserAction(varible);

}




