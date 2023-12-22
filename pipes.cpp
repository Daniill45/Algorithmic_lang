#include "pipes.h"
#include "validation.h"
#include<string>
using namespace std;
string Pipeline::type = "Труба";
int Pipeline::total=0;
void Pipeline::init(string new_name,double new_length,double new_diametr,bool new_in_repair){
    name=new_name;
    length=new_length;
    diametr=new_diametr;
    in_repair=new_in_repair;
}
string* Pipeline::get_name(){
    return &name;
}
double Pipeline::get_length() const{
    return length;
}
double Pipeline::get_diametr() const{
    return diametr;
}
bool Pipeline::get_in_repair() const{
    return in_repair;
}
void Pipeline::set_in_repair(int new_in_repair){
    in_repair=new_in_repair;
}
Pipeline::Pipeline()               
   {
      total++;            
      id = total;           
   }
int Pipeline::getid() {
      return id;
}
ostream& operator << (ostream& out, const Pipeline& pipe)
{
	out << pipe.type << "\n"<< pipe.name<< "\n" <<pipe.length<< "\n"<<pipe.diametr<< "\n"<<pipe.in_repair<<endl;
	return out;
}
istream& operator>>(istream& in, Pipeline& pipe)
{
    
    double lenght;
    double diametr;
    bool in_repair;
    string input_name;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(in, input_name);

    if (!in) {
        cout << "Error reading input_name from file." << endl;
        return in;
    }
    in >> lenght >>  diametr>>in_repair;
    pipe.init(input_name, lenght, diametr, in_repair);

    return in;
}
void create_pipe(unordered_map<int,Pipeline> &pipe_map)
{   
    Pipeline tmp_pipe;
    cout << "Введите название трубы:" << endl;
    cin >> ws;
    string name;
    double lenght;
    double diametr;
    bool in_repair;
    getline(cin, name);
    cout << "Введите длину:" << endl;
    is_valid(lenght,0.0,inf);
    cout << "Введите диаметр:" << endl;
    is_valid(diametr,0.0,inf);
    cout << "Введите 1 если труба в ремонте, иначе 0:" << endl;
    is_valid(in_repair,bool(0),bool(1));
    tmp_pipe.init(name,lenght,diametr,in_repair);
    pipe_map.insert({tmp_pipe.getid(),tmp_pipe});
}

void find_pipe(unordered_map<int,Pipeline> &pipe_map,list<int> &indexes){
    string input_name;
    cout<<"Название для поиска(-1 чтобы пропустить):"<<endl;
    cin >> ws;
    getline(cin, input_name);
    int in_rep=-1;
    cout << "Введите 1 если труба в ремонте, иначе 0(-1 чтобы пропустить):" << endl;
    is_valid(in_rep,-1,1);
    Pipeline pipe;
    for(auto it=pipe_map.begin();it!=pipe_map.end();it++) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        pipe=it->second;
        if((input_name=="-1"|| *pipe.get_name()==input_name)&&(in_rep==-1 || pipe.get_in_repair()==in_rep)){
            indexes.push_back(it->first);
        }
    }
}

void show_pipe(unordered_map<int,Pipeline> &pipes,list<int> index){

    Pipeline pipe;
    int flag=0;
    for (int ind:index){
        flag=1;
        pipe=pipes[ind];
        cout << endl;
        cout << "Тип:" << pipe.type << endl;
        cout << "Название:" << *pipe.get_name() << endl;
        cout << "Длина:" << pipe.get_length() << endl;
        cout << "Диаметр:" << pipe.get_diametr() << endl;
        cout << "На ремонте:" << (pipe.get_in_repair() ? "Да" : "Нет") << endl;
    }
    if (flag==0){
        cout<<"Не нашлось труб..."<<endl;
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
        is_valid(if_delete, bool(0), bool(1));
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
        is_valid(repair, bool(0), bool(1));
        edited_pipe=pipe_map[ind];
        edited_pipe.set_in_repair(repair);
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
    is_valid(repair, bool(0), bool(1));
    for (int ind : indexes){
        edited_pipe=pipe_map[ind];
        edited_pipe.set_in_repair(repair);
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
        f<<it->second;
    }
    
    f.close();
}