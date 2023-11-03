#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int empty_strings = 1000;
const double inf = 1e123;

struct Pipeline
{
    string name = "";
    double length = 0;
    double diametr = 0;
    bool in_repair = false;
};

struct Compressor
{
    string name = "";
    int manufact = 0;
    int manufact_in_work = 0;
    double efficiency = 0;
};
template <typename T1, typename T2, typename T3>
void is_valid(T1 &varible, T2 a, T3 b)
{

    while (!(cin >> varible) || (varible < a) || (varible > b) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное значение: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
}

void create_pipe(Pipeline &pipe)
{
    string name;
    double lenght = -1;
    double diametr = -1;
    bool in_repair = 1;
    cout << "Введите название трубы:" << endl;
    cin >> ws;
    getline(cin, name);
    cout << "Введите длину:" << endl;
    is_valid(lenght, 0.0, double(inf));
    cout << "Введите диаметр:" << endl;
    is_valid(diametr, 0.0, double(inf));
    cout << "Введите 1 если труба в ремонте, иначе 0:" << endl;
    is_valid(in_repair, bool(0), bool(1));
    pipe.name = name;
    pipe.length = lenght;
    pipe.diametr = diametr;
    pipe.in_repair = in_repair;
}
void create_CS(Compressor &cs)
{
    string name;
    int manufact = -1;
    int manufact_in_work = -1;
    double effic = -1;
    cout << "Введите название кс:" << endl;
    cin >> ws;
    getline(cin, name);
    cs.name = name;
    cout << "Введите количество цехов:" << endl;
    is_valid(manufact, 0, inf);
    cout << "Введите количество цехов в работе:" << endl;
    is_valid(manufact_in_work, 0, manufact);
    cout << "Введите эффективность:" << endl;
    is_valid(effic, 0.0, 100.0);
    cs.manufact = manufact;
    cs.manufact_in_work = manufact_in_work;
    cs.efficiency = effic;
}

void edit_pipe(Pipeline &pipe)
{
    bool in_repair;
    if (pipe.name.empty())
    {
        cout << "Труба не нашлась..." << endl;
    }
    else
    {
        cout << "Введите 1 если труба в ремонте, иначе 0" << endl;
        is_valid(in_repair, 0, 1);
        pipe.in_repair = in_repair;
    }
}
void edit_cs(Compressor &station)
{

    int manufact_in_work;

    if (station.name.empty())
    {
        cout << "Компрессорная станция не нашлась" << endl;
    }
    else
    {
        cout << "Введите количество цехов в работе:" << endl;
        is_valid(manufact_in_work, 0, station.manufact);
        station.manufact_in_work = manufact_in_work;
    }
}
void show_pipe(Pipeline &pipe)
{
    if (!pipe.name.empty())
    {
        cout << endl;
        cout << "Трубопровод:" << endl;
        cout << "Название:" << pipe.name << endl;
        cout << "Длина:" << pipe.length << endl;
        cout << "Диаметр:" << pipe.diametr << endl;
        cout << "На ремонте:" << (pipe.in_repair ? "Да" : "Нет") << endl;
    }
}
void show_station(Compressor &station)
{
    if (!station.name.empty())
    {
        cout << endl;
        cout << "Компрессорная станция:" << endl;
        cout << "Название:" << station.name << endl;
        cout << "Количество цехов:" << station.manufact << endl;
        cout << "Количество цехов в работе:" << station.manufact_in_work << endl;
        cout << "Эффективность:" << station.efficiency << endl;
    }
}
void save_pipe(Pipeline &pipe, string file_name)
{

    ofstream f(file_name, ios::app);

    if (!f)
    {
        cout << "Ошибка открытия файла для сохранения: " << file_name << endl;
        return;
    }
    if (!pipe.name.empty())
    {
        f << "Трубопровод:\n";
        f << pipe.name << "\n";
        f << pipe.length << "\n";
        f << pipe.diametr << "\n";
        f << pipe.in_repair << "\n";
    }
    f.close();
}
void save_compressor(Compressor &station, string file_name)
{
    ofstream f(file_name, ios::app);

    if (!f)
    {
        cout << "Ошибка открытия файла для сохранения: " << file_name << endl;
        return;
    }
    if (!station.name.empty())
    {
        f << "КС:\n";
        f << station.name << "\n";
        f << station.manufact << "\n";
        f << station.manufact_in_work << "\n";
        f << station.efficiency << "\n";
    }

    f.close();
    cout << "Данные сохранены в файл: " << file_name << endl;
}

void load_data(Pipeline &pipe, Compressor &station)
{
    string file_name;
    cout << "Введите имя файла на загрузку: ";
    cin >> file_name;
    ifstream f(file_name);
    if (!f)
    {
        cout << "Ошибка открытия файла на загрузку: " << file_name << endl;
        return;
    }

    string line;
    while (getline(f, line))
    {
        if (line == "Трубопровод:")
        {
            f >> pipe.name >> pipe.length >> pipe.diametr >> pipe.in_repair;
            f.ignore(empty_strings, '\n');
        }
        else if (line == "КС:")
        {
            f >> station.name >> station.manufact >> station.manufact_in_work >> station.efficiency;
            f.ignore(empty_strings, '\n');
        }
    }
    f.close();
    cout << "Данные загружены из файла: " << file_name << endl;
}

void Menu()
{
    cout << "1-Добавить трубу" << endl
         << "2-Добавить КС" << endl
         << "3-Просмотр всех объектов" << endl
         << "4-Редактировать трубу" << endl
         << "5-Редактировать КС" << endl
         << "6-Сохранить" << endl
         << "7-Загрузить" << endl
         << "0-Выход" << endl;
}
int main()
{
    int MODE = 0;
    Pipeline pipe;
    Compressor station;
    while (1)
    {
        Menu();
        is_valid(MODE, 0, 7);
        if (MODE != 0)
        {
            switch (MODE)
            {
            case 1:
            {
                create_pipe(pipe);
                break;
            }
            case 2:
            {
                create_CS(station);
                break;
            }
            case 3:
            {
                show_pipe(pipe);
                show_station(station);
                if ((pipe.name.empty()) && (station.name.empty()))
                {
                    cout << "Ничего не нашлось..." << endl;
                }
                break;
            }
            case 4:
            {
                edit_pipe(pipe);
                break;
            }
            case 5:
            {
                edit_cs(station);
                break;
            }
            case 6:
            {
                string file_name;
                cout << "Введите имя файла на сохранение: ";
                cin >> file_name;
                save_compressor(station, file_name);
                save_pipe(pipe, file_name);
                break;
            }
            case 7:
            {
                load_data(pipe, station);
                break;
            }
            }
        }
        else
        {
            break;
        }
    }

    return 0;
};
