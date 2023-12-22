#ifndef PIPES_H
#define PIPES_H
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

class Pipeline

{ 
private:
    int id;
    static int total;
    bool in_repair;
    string name;
    double length;
    double diametr;
public:
    static string type;
    int getid();
    Pipeline();
    void init(string new_name,double new_length,double new_diametr,bool new_in_repair);
    string* get_name() ;
    double get_length() const;
    double get_diametr() const;
    bool get_in_repair() const;
    void set_in_repair(int new_in_repair);
    friend std::ostream& operator << (std::ostream& out, const Pipeline& pipe);
	friend std::istream& operator >> (std::istream& in, Pipeline& pipe);
};

void create_pipe(unordered_map<int,Pipeline> &pipe_map);
void find_pipe(unordered_map<int,Pipeline> &pipe_map,list<int> &indexes);
void show_pipe(unordered_map<int,Pipeline> &pipes,list<int> index);
void del_pipe(unordered_map<int,Pipeline> &pipe_map);
void edit_pipe(unordered_map<int,Pipeline> &pipe_map);
void pocket_edit_pipe(unordered_map<int,Pipeline> &pipe_map);
void save_pipe(unordered_map<int,Pipeline> &pipe_map, string file_name);
#endif // PIPES_H