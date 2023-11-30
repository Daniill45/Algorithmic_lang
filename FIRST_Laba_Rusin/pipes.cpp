#include "pipes.h"
#include "validation.h"
#include<string>
using namespace std;
string Pipeline::type = "Труба";
int Pipeline::total=0;
Pipeline::Pipeline()               
   {
      total++;            
      id = total;           
   }
int Pipeline::getid() {
      return id;
}

void create_pipe(unordered_map<int,Pipeline> &pipe_map)
{   
    Pipeline tmp_pipe;
    cout << "Введите название трубы:" << endl;
    cin >> ws;
    getline(cin, tmp_pipe.name);
    cout << "Введите длину:" << endl;
    is_valid(tmp_pipe.length,0.0,double(inf));
    cout << "Введите диаметр:" << endl;
    is_valid(tmp_pipe.diametr,0.0,double(inf));
    cout << "Введите 1 если труба в ремонте, иначе 0:" << endl;
    is_valid(tmp_pipe.in_repair,bool(0),bool(1));

    pipe_map.insert({tmp_pipe.getid(),tmp_pipe});
}

void find_pipe(unordered_map<int,Pipeline> &pipe_map,list<int> &indexes){
    string input_name;
    cout<<"Название для поиска(-1 чтобы пропустить):"<<endl;
    cin >> ws;
    getline(cin, input_name);
    double leng=-1;
    double diam=-1;
    int in_rep=-1;
    cout << "Введите длину для поиска(-1 чтобы пропустить):" << endl;
    is_valid(leng,-1,inf);
    cout << "Введите диаметр для поиска(-1 чтобы пропустить):" << endl;
    is_valid(diam,-1,inf);
    cout << "Введите 1 если труба в ремонте, иначе 0(-1 чтобы пропустить):" << endl;
    is_valid(in_rep,-1,1);
    Pipeline pipe;
    for(auto it=pipe_map.begin();it!=pipe_map.end();it++) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        pipe=it->second;
        if((input_name=="-1"|| pipe.name==input_name)&&(leng==-1 || pipe.length==leng)&&(diam==-1 || pipe.diametr==diam)&&(in_rep==-1 || pipe.in_repair==in_rep)){
            indexes.push_back(it->first);
        }
    }
}

void show_pipe(unordered_map<int,Pipeline> &pipes,list<int> index){

    Pipeline pipe;
    for (int ind:index){
        pipe=pipes[ind];
        cout << endl;
        cout << "Тип:" << pipe.type << endl;
        cout << "Название:" << pipe.name << endl;
        cout << "Длина:" << pipe.length << endl;
        cout << "Диаметр:" << pipe.diametr << endl;
        cout << "На ремонте:" << (pipe.in_repair ? "Да" : "Нет") << endl;
    }
}

void del_pipe(unordered_map<int,Pipeline> &pipe_map){
    list<int> indexes;
    bool if_delete=0;
    find_pipe(pipe_map,indexes);
    for (int ind : indexes){
        list <int> l= {ind};
        show_pipe(pipe_map,l);
        cout << "Введите 1 если необходимо удалить трубу, иначе 0" << endl;
        is_valid(if_delete, 0, 1);
        if (if_delete){
            pipe_map.erase(ind);
        }
    }
}

void edit_pipe(unordered_map<int,Pipeline> &pipe_map)
{
    list<int> indexes;
    bool repair;
    find_pipe(pipe_map,indexes);
    Pipeline edited_pipe;
    for (int ind : indexes){
        list <int> l= {ind};
        show_pipe(pipe_map,l);
        cout << "Введите 1 если труба в ремонте, иначе 0" << endl;
        is_valid(repair, 0, 1);
        edited_pipe=pipe_map[ind];
        edited_pipe.in_repair=repair;
        pipe_map[ind]=edited_pipe;
    }
}
void pocket_edit_pipe(unordered_map<int,Pipeline> &pipe_map)
{
    int index;
    list<int> indexes;
    bool repair;
    find_pipe(pipe_map,indexes);
    Pipeline edited_pipe;
    show_pipe(pipe_map,indexes);
    cout << "Введите 1, чтобы выставить все найденные трубы в ремонт, иначе 0" << endl;
    is_valid(repair, 0, 1);
    for (int ind : indexes){
        edited_pipe=pipe_map[ind];
        edited_pipe.in_repair=repair;
        pipe_map[ind]=edited_pipe;
    }
}

void save_pipe(unordered_map<int,Pipeline> &pipe_map, string file_name){
 
    ofstream f(file_name,ios::app);

    if (!f)
    {
        cout << "Ошибка открытия файла для сохранения: " << file_name << endl;
        return;
    }
    
    for(auto it=pipe_map.begin();it!=pipe_map.end();it++) {
        f << "Трубопровод:\n";
        f << it->second.name << "\n";
        f << it->second.length << "\n";
        f << it->second.diametr << "\n";
        f << it->second.in_repair << "\n";
    }
    
    f.close();
}