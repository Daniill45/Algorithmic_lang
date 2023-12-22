

#include "pipes.h"
#include "validation.h"
#include "compressor.h"

using namespace std;

//Логи только цифрами которые вводит пользователь
//для функции валидации передавать напрямую аргумент
// логи со всеми действиями пользователя за 1 сессию
// все в прайват
// 



void load_data(unordered_map<int,Pipeline> &pipe_map,unordered_map<int,Compressor> &cs_map)
{   
    string file_name;
    cout << "Введите имя файла на загрузку: ";
    cin >> file_name;
    logUserAction(file_name);
    ifstream in(file_name);
    if (in.is_open())
    {
        while (true)

        {   
            string f;
            in>>f;
            if (f=="КC"){
                Compressor cs;
                if (in >> cs){ 
                    cs_map.insert({cs.getid(),cs});
                }else{
                    break;
                }
            }
            else if (f=="Труба")
            {
                Pipeline pipe;
                if (in >> pipe){ 
                    pipe_map.insert({pipe.getid(),pipe});
                }else{
                    break;
                }
            }
            else{break;}
                
            }
        }
    in.close();
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
                logUserAction(file_name);
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
