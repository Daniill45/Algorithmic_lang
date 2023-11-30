
#include "compressor.h"
#include "pipes.h"
#include "validation.h"
#include<string>
using namespace std;
string Compressor::type="Компрессорная станция";
int Compressor::total=0;
int Compressor::getid() {
      return id;
}
Compressor::Compressor()
{
      total++;           
      id = total;           
}

void create_CS(unordered_map<int,Compressor> &cs_map)
{
    string name;
    cout << "Введите название кс:" << endl;
    cin >> ws;
    Compressor cs;
    getline(cin, cs.name);
    cout << "Введите количество цехов:" << endl;
    is_valid(cs.manufact, 0, inf);
    cout << "Введите количество цехов в работе:" << endl;
    is_valid(cs.manufact_in_work, 0, cs.manufact);
    cout << "Введите эффективность:" << endl;
    is_valid(cs.efficiency, 0.0, 100.0);
    cs_map.insert({cs.getid(),cs});
}


void find_cs(unordered_map<int,Compressor> &cs_map,list<int> &indexes){
    string input_name;
    cout<<"Название для поиска(-1 чтобы пропустить):"<<endl;
    cin >> ws;
    getline(cin,input_name);
    int manufact = -1;
    int manufact_in_work = -1;
    double effic = -1;
    cout << "Введите количество цехов для поиска(-1 чтобы пропустить):" << endl;
    is_valid(manufact,-1,inf);
    cout << "Введите количество цехов в работе для поиска(-1 чтобы пропустить):" << endl;
    is_valid( manufact_in_work,-1,inf);
    cout << "Введите эффективность для поиска (-1 чтобы пропустить):" << endl;
    is_valid(effic,-1,100);
    Compressor cs;
    for(auto it=cs_map.begin();it!=cs_map.end();it++) {
        cs=it->second;
        if((input_name=="-1"|| cs.name==input_name)&&(manufact==-1 || cs.manufact==manufact)&&(manufact_in_work==-1 || cs.manufact_in_work==manufact_in_work)&&(effic==-1 || cs.efficiency==effic)){
            indexes.push_back(it->first);
        }
    }
}
void show_cs(unordered_map<int,Compressor> &cs_map,list<int> index){

    Compressor cs;
    for (int ind:index){
        cs=cs_map[ind];
        cout << endl;
        cout << "Тип:" << cs.type << endl;
        cout << "Название:" << cs.name << endl;
        cout << "Количество цехов:" << cs.manufact << endl;
        cout << "Количество цехов в работе:" << cs.manufact_in_work << endl;
        cout << "Эффективность:" <<cs.efficiency  << endl;
    }
}


void del_cs(unordered_map<int,Compressor> &cs_map){
    list<int> indexes;
    bool if_delete=0;
    find_cs(cs_map,indexes);
    for (int ind : indexes){
        list <int> l= {ind};
        show_cs(cs_map,l);
        cout << "Введите 1 если необходимо удалить кс, иначе 0" << endl;
        is_valid(if_delete, 0, 1);
        if (if_delete){
            cs_map.erase(ind);
        }
    }
}

void edit_cs(unordered_map<int,Compressor> &cs_map)
{
    list<int> indexes;
    double effic;
    find_cs(cs_map,indexes);
    Compressor edited_cs;
    for (int ind : indexes){
        list <int> l= {ind};
        show_cs(cs_map,l);
        cout << "Введите новую эффективность" << endl;
        is_valid(effic, 0, 100);
        edited_cs=cs_map[ind];
        edited_cs.efficiency=effic;
        cs_map[ind]=edited_cs;
    }
}
void pocket_edit_cs(unordered_map<int,Compressor> &cs_map)
{
    int index;
    list<int> indexes;
    double effic;
    find_cs(cs_map,indexes);
    Compressor edited_cs;
    show_cs(cs_map,indexes);
    cout << "Введите новую эффективность" << endl;
    is_valid(effic, 0, 100);
    for (int ind : indexes){
        edited_cs=cs_map[ind];
        edited_cs.efficiency=effic;
        cs_map[ind]=edited_cs;
    }
}
void save_cs(unordered_map<int,Compressor> &cs_map, string file_name){
 
    ofstream f(file_name,ios::app);

    if (!f)
    {
        cout << "Ошибка открытия файла для сохранения: " << file_name << endl;
        return;
    }
    
    for(auto it=cs_map.begin();it!=cs_map.end();it++) {
        f << "КС:\n";
        f << it->second.name << "\n";
        f << it->second.manufact << "\n";
        f << it->second.manufact_in_work << "\n";
        f << it->second.efficiency << "\n";
    }
    
    f.close();
}



