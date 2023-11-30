

#include "pipes.h"
#include "validation.h"
#include "compressor.h"

using namespace std;

//Логи только цифрами которые вводит пользователь
//для функции валидации  напрямую аргумент
//



void load_data(unordered_map<int,Pipeline> &pipe_map,unordered_map<int,Compressor> &cs_map)
{
    string file_name;
    cout << "Введите имя файла на загрузку: ";
    cin >> file_name;
    ifstream f(file_name);
    if (!f)
    {
        cerr << "Ошибка открытия файла на загрузку: " << file_name << endl;
        return;
    }
    pipe_map.clear();
    cs_map.clear();
    string line;
    Pipeline pipe;
    while (getline(f, line)) {
        if (line == "Трубопровод:") {
            Pipeline pipe;
            f >> ws;
            getline(f, line);
            pipe.name=line;
            //double length;
            //f >> length;
            //pipe.length=length;
            f >>pipe.length;
            //double diameter;
            //f >> diameter;
            //pipe.diametr=diameter;
            f >> pipe.diametr;
            //bool under_repair;
            //f >> under_repair;
            //pipe.in_repair=under_repair;
            f >> pipe.in_repair;
            pipe_map.insert({pipe.getid(),pipe});
            f.ignore(empty_strings, '\n');
        }else if (line == "КС:"){
            Compressor cs;
            f >> ws;
            getline(f, line);
            cs.name=line;
            //int manufact;
            //f >> manufact;
            //cs.manufact=manufact;
            f>>cs.manufact;
            //int manufact_in_work;
            //f >> manufact_in_work;
            //cs.manufact_in_work=manufact_in_work;
            f >> cs.manufact_in_work;
            //bool effic;
            //f >> effic;
            //cs.efficiency=effic;
            f >> cs.efficiency;
            cs_map.insert({cs.getid(),cs});
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
         << "8-Удалить трубу" << endl
         << "9-Удалить кс" << endl
         << "10-Пакетное редактирование кс" << endl
         << "11-Пакетное редактирование трубы" << endl
         << "0-Выход" << endl;
}

int main()
{   
    int MODE = 0;
    unordered_map<int, Pipeline> pipe_map;
    unordered_map<int, Compressor> cs_map;
    string action;
    while (1)
    {
        Menu();
        is_valid(MODE,0,11);
        if (MODE != 0)
        {
            switch (MODE)
            {
            case 1:
            {
                action = "1";
                logUserAction(action);
                create_pipe(pipe_map);
                break;
            }
            case 2:
            {
                action = "2";
                logUserAction(action);
                create_CS(cs_map);
                break;
            }
            case 3:
            {   
                action = "3";
                logUserAction(action);
                list<int> pipe_indexes;
                for(auto it=pipe_map.begin();it!=pipe_map.end();it++) {
                    pipe_indexes.push_back(it->first);
                } 
                list<int> cs_indexes;
                for(auto it=cs_map.begin();it!=cs_map.end();it++) {
                    cs_indexes.push_back(it->first);
                }
                show_pipe(pipe_map,pipe_indexes);
                show_cs(cs_map,cs_indexes);
                break;
            }
            case 4:

            {
                action = "4";
                logUserAction(action);
                edit_pipe(pipe_map);
                break;
            }
            case 5:
            {
                action = "5";
                logUserAction(action);
                edit_cs(cs_map);
                break;
            }
            case 6:
            {      
                action = "6";
                logUserAction(action);
                string file_name;
                cout << "Введите имя файла на сохранение: ";
                cin >> file_name;
                save_cs(cs_map,file_name);
                save_pipe(pipe_map,file_name);
                break;
            }
            case 7:
            {
                action = "7";
                logUserAction(action);
                load_data(pipe_map,cs_map);
                break;
            }
            case 8:{
                action = "8";
                logUserAction(action);
                del_pipe(pipe_map);
                break;
            }
            case  9:{
                action = "9";
                logUserAction(action);
                del_cs(cs_map);
                break;
            }
            case 10:{
                action = "10";
                logUserAction(action);
                pocket_edit_cs(cs_map);
                break;
            }
            case 11:{
                action = "11";
                logUserAction(action);
                pocket_edit_pipe(pipe_map);
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
