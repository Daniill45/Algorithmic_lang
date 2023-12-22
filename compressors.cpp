
#include "compressor.h"
#include "pipes.h"
#include "validation.h"
#include<string>
using namespace std;
string Compressor::type="КC";
int Compressor::total=0;
string name;
    int manufact;
    int manufact_in_work;
    double efficiency;
void Compressor::init(string new_name,int new_manuf,int new_working_manuf,double new_effic){
    name=new_name;
    manufact=new_manuf;
    manufact_in_work=new_working_manuf;
    efficiency=new_effic;
}
string* Compressor::get_name() {
    return &name;
}
int Compressor::get_manufact() const{
    return manufact;
}
int Compressor::get_manufact_in_work() const{
    return manufact_in_work;
}
double Compressor::get_efficiency() const{
    return efficiency;
}
int Compressor::getid() const {
      return id;
}
void Compressor::set_manufact_in_work(int new_manuf_in_work){
    manufact_in_work=new_manuf_in_work;
} 
Compressor::Compressor()
{   
      
      total++;           
      id = total;           
}
ostream& operator << (ostream& out, const Compressor& cs)
{
	out << cs.type << "\n"<< cs.name<< "\n" <<cs.manufact<< "\n"<<cs.manufact_in_work<< "\n"<<cs.efficiency<<endl;
	return out;
}
istream& operator>>(istream& in, Compressor& cs)
{
    int manufact;
    double effic;
    int manufat_in_work;
    string input_name;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(in, input_name);

    if (!in) {
        cout << "Error reading input_name from file." << endl;
        return in;
    }
    in >> manufact >>  manufact_in_work>>effic;
    cs.init(input_name, manufact, manufact_in_work, effic);

    return in;
}

void create_CS(unordered_map<int,Compressor> &cs_map)
{
    string name;
    cout << "Введите название кс:" << endl;
    cin >> ws;
    int manufact;
    int manufact_in_work;
    double effic;
    getline(cin, name);
    logUserAction(name);
    cout << "Введите количество цехов:" << endl;
    is_valid(manufact, 0, 1000000);
    cout << "Введите количество цехов в работе:" << endl;
    is_valid(manufact_in_work, 0, manufact);
    cout << "Введите эффективность:" << endl;
    is_valid(effic, 0.0, 100.0);
    Compressor cs;
    cs.init(name, manufact, manufact_in_work, effic);
    cs_map.insert({cs.getid(),cs});
}


void find_cs(unordered_map<int,Compressor> &cs_map,list<int> &indexes){
    string input_name;
    cout<<"Название для поиска(-1 чтобы пропустить):"<<endl;
    cin >> ws;
    getline(cin,input_name);
    logUserAction(input_name);
    int manufact_in_work = -1;
    cout << "Введите количество цехов в работе для поиска(-1 чтобы пропустить):" << endl;
    is_valid( manufact_in_work,-1,100000);
    Compressor cs;
    for(auto it=cs_map.begin();it!=cs_map.end();it++) {
        cs=it->second;
        if((input_name=="-1"|| *cs.get_name()==input_name)&&(manufact_in_work==-1 || cs.get_manufact_in_work()==manufact_in_work)){
            indexes.push_back(it->first);
        }
    }
}
void show_cs(unordered_map<int,Compressor> &cs_map,list<int> index){

    Compressor cs;
    int flag=0;
    for (int ind:index){
        flag=1;
        cs=cs_map[ind];
        cout << endl;
        cout << "Тип:" << cs.type << endl;
        cout << "Название:" << *cs.get_name() << endl;
        cout << "Количество цехов:" << cs.get_manufact() << endl;
        cout << "Количество цехов в работе:" << cs.get_manufact_in_work()<< endl;
        cout << "Эффективность:" <<cs.get_efficiency()  << endl;
    }
    if (flag==0){
        cout<<"Не нашлось КС..."<<endl;
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
        is_valid(if_delete, bool(0), bool(1));
        if (if_delete){
            cs_map.erase(ind);
        }
    }
}

void edit_cs(unordered_map<int,Compressor> &cs_map)
{
    list<int> indexes;
    int user_input;
    find_cs(cs_map,indexes);
    Compressor edited_cs;
    for (int ind : indexes){
        list <int> l= {ind};
        show_cs(cs_map,l);
        cout << "Введите количество цехов в работе" << endl;
        edited_cs=cs_map[ind];
        is_valid(user_input, 0, edited_cs.get_manufact());
        edited_cs.set_manufact_in_work(user_input);
        cs_map[ind]=edited_cs;
    }
}
void pocket_edit_cs(unordered_map<int,Compressor> &cs_map)
{
    int index;
    list<int> indexes;
    int user_input;
    find_cs(cs_map,indexes);
    Compressor edited_cs;
    show_cs(cs_map,indexes);
    int min_manuf=1e9;
    for (int ind : indexes){
        edited_cs=cs_map[ind];
        if (edited_cs.get_manufact()<min_manuf){
            min_manuf=edited_cs.get_manufact();
        }
    }
    cout << "Введите количество цехов в работе:" << endl;
    is_valid(user_input, 0, min_manuf);
    for (int ind : indexes){
        edited_cs=cs_map[ind];
        edited_cs.set_manufact_in_work(user_input);
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
        f<<it->second;
    }
    
    f.close();
}



