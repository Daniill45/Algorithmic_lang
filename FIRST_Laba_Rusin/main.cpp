#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int empty_strings = 1000;

struct Pipeline
{
    string name = "NO_NAME";
    double length = 0;
    double diametr = 0;
    bool in_repair = false;
};

struct Compressor
{
    string name = "NO_NAME";
    int manufact = 0;
    int manufact_in_work = 0;
    double efficiency = 0;
};
void pipe_validation(double result[])
{
    double lenght = -1;
    double diametr = -1;
    bool in_repair = true;
    cout << "Введите длину:" << endl;
    while (!(cin >> lenght) || (lenght <= 0) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное значение длины: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    cout << "Введите диаметр:" << endl;
    while (!(cin >> diametr) || (diametr <= 0) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное значение диаметра: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    cout << "Введите 1 если труба в ремонте, иначе 0:" << endl;
    while (!(cin >> in_repair) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное значение: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    result[0] = lenght;
    result[1] = diametr;
    result[2] = in_repair;
}
void cs_validation(double result2[])
{
    int manufact = -1;
    int manufact_in_work = -1;
    double effic = -1;
    cout << "Введите количество цехов:" << endl;
    while (!(cin >> manufact) || (manufact <= 0) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное количество цехов: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    cout << "Введите количество цехов в работе:" << endl;
    while (!(cin >> manufact_in_work) || (cin.peek() != '\n') || (manufact_in_work < 0) || (manufact_in_work > manufact))
    {
        cout << "Ошибка: Введите корректное количество цехов в работе: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    cout << "Введите эффективность:" << endl;
    while (!(cin >> effic) || (effic < 0) || (effic > 100) || (cin.peek() != '\n'))
    {
        cout << "Ошибка: Введите корректное значение эффективности: ";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }
    result2[0] = manufact;
    result2[1] = manufact_in_work;
    result2[2] = effic;
}
void create_pipe(vector<Pipeline> &pipes)
{
    double results[3];
    Pipeline tmp_pipe;
    cout << "Введите название трубы:" << endl;
    cin >> tmp_pipe.name;
    pipe_validation(results);
    tmp_pipe.length = results[0];
    tmp_pipe.diametr = results[1];
    tmp_pipe.in_repair = results[2];

    pipes.push_back(tmp_pipe);
}
void create_CS(vector<Compressor> &stations)
{
    double results[3];
    Compressor cs;
    cout << "Введите название кс:" << endl;
    cin >> cs.name;
    cs_validation(results);
    cs.manufact = results[0];
    cs.manufact_in_work = results[1];
    cs.efficiency = results[2];

    stations.push_back(cs);
}
void edit_pipe(vector<Pipeline> &pipes)
{
    string input_name;
    cout << "Введите название трубы:" << endl;
    cin >> input_name;
    bool in_repair;
    int flag = 0;
    for (Pipeline &i : pipes)
    {
        if (i.name == input_name)
        {
            flag = 1;
            cout << "Введите 1 если труба в ремонте, иначе 0:" << endl;
            while (!(cin >> in_repair) || (cin.peek() != '\n'))
            {
                cout << "Ошибка: Введите корректное значение: ";
                cin.clear();
                cin.ignore(empty_strings, '\n');
            }
            i.in_repair = in_repair;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "Труба не нашлась..." << endl;
    }
}
void edit_cs(vector<Compressor> &stations)
{
    string input_name;
    cout << "Введите название КС:" << endl;
    cin >> input_name;
    int flag = 0;
    int manufact_in_work;
    for (Compressor &i : stations)
    {
        if (i.name == input_name)
        {
            flag = 1;
            cout << "Введите количество цехов в работе:" << endl;
            while (!(cin >> manufact_in_work) || (cin.peek() != '\n') || (manufact_in_work < 0) || (manufact_in_work > i.manufact))
            {
                cout << "Ошибка: Введите корректное значение: ";
                cin.clear();
                cin.ignore(empty_strings, '\n');
            }
            i.manufact_in_work = manufact_in_work;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "НПС не нашлась" << endl;
    }
}
void show_all(vector<Compressor> &stations, vector<Pipeline> &pipes)
{
    if (!stations.empty())
    {
        cout << "КС:" << endl;
    }
    for (Compressor i : stations)
    {
        cout << endl;
        cout << "Название:" << i.name << endl;
        cout << "Количество цехов:" << i.manufact << endl;
        cout << "Количество цехов в работе:" << i.manufact_in_work << endl;
        cout << "Эффективность:" << i.efficiency << endl;
    }
    if (!pipes.empty())
    {
        cout << endl;
        cout << "Трубопроводы:" << endl;
    }
    for (Pipeline i : pipes)
    {
        cout << endl;
        cout << "Название:" << i.name << endl;
        cout << "Длина:" << i.length << endl;
        cout << "Диаметр:" << i.diametr << endl;
        cout << "На ремонте:" << (i.in_repair ? "Да" : "Нет") << endl;
    }
    if (pipes.empty() && stations.empty())
    {
        cout << "Ничего не нашлось..." << endl;
    }
}
void save_data(const vector<Pipeline> &pipes, const vector<Compressor> &stations)
{
    string file_name;
    cout << "Введите имя файла на сохранение: ";
    cin >> file_name;
    ofstream f(file_name);

    if (!f)
    {
        cout << "Ошибка открытия файла для сохранения: " << file_name << endl;
        return;
    }

    for (const Pipeline &i : pipes)
    {
        f << "Трубопровод:\n";
        f << i.name << "\n";
        f << i.length << "\n";
        f << i.diametr << "\n";
        f << i.in_repair << "\n";
    }
    for (const Compressor &j : stations)
    {
        f << "КС:\n";
        f << j.name << "\n";
        f << j.manufact << "\n";
        f << j.manufact_in_work << "\n";
        f << j.efficiency << "\n";
    }

    f.close();
    cout << "Данные сохранены в файл: " << file_name << endl;
}

void load_data(vector<Pipeline> &pipes, vector<Compressor> &stations)
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
    pipes.clear();
    stations.clear();
    string line;

    while (getline(f, line))
    {
        if (line == "Трубопровод:")
        {
            Pipeline pipe;
            f >> pipe.name >> pipe.length >> pipe.diametr >> pipe.in_repair;
            pipes.push_back(pipe);
            f.ignore(empty_strings, '\n');
        }
        else if (line == "КС:")
        {
            Compressor cs;
            f >> cs.name >> cs.manufact >> cs.manufact_in_work >> cs.efficiency;
            stations.push_back(cs);
            f.ignore(empty_strings, '\n');
        }
    }
    f.close();
    cout << "Данные загружены из файла: " << file_name << endl;
}

int check_valid_int()
{
    int MODE;
    while (!(cin >> MODE) || (cin.peek() != '\n') || (MODE > 7) || (MODE < 0))
    {
        cout << "Ошибка: Введите корректное значение:";
        cin.clear();
        cin.ignore(empty_strings, '\n');
    }

    return MODE;
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
    vector<Pipeline> pipes;
    vector<Compressor> stations;
    while (1)
    {
        Menu();
        int MODE = check_valid_int();
        if (MODE != 0)
        {
            switch (MODE)
            {
            case 1:
            {
                create_pipe(pipes);
                break;
            }
            case 2:
            {
                create_CS(stations);
                break;
            }
            case 3:
            {
                show_all(stations, pipes);
                break;
            }
            case 4:
            {
                edit_pipe(pipes);
                break;
            }
            case 5:
            {
                edit_cs(stations);
                break;
            }
            case 6:
            {
                save_data(pipes, stations);
                break;
            }
            case 7:
            {
                load_data(pipes, stations);
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
