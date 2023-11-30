#ifndef PIPES_H
#define PIPES_H
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

class Pipeline

{   private:
    int id;
    static int total;
    public:
    bool in_repair;
    static string type;
    string name;
    double length;
    double diametr;
    int getid();
    Pipeline();
};

void create_pipe(unordered_map<int,Pipeline> &pipe_map);
void find_pipe(unordered_map<int,Pipeline> &pipe_map,list<int> &indexes);
void show_pipe(unordered_map<int,Pipeline> &pipes,list<int> index);
void del_pipe(unordered_map<int,Pipeline> &pipe_map);
void edit_pipe(unordered_map<int,Pipeline> &pipe_map);
void pocket_edit_pipe(unordered_map<int,Pipeline> &pipe_map);
void save_pipe(unordered_map<int,Pipeline> &pipe_map, string file_name);
#endif // PIPES_H