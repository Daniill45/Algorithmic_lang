#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
using namespace std;

class Compressor
{   
    public:
    static int total;
    int id;
    string name;
    int manufact;
    int manufact_in_work;
    double efficiency;
    static string type;
    int getid() ;
    Compressor();
};

void create_CS(unordered_map<int,Compressor> &cs_map);
void find_cs(unordered_map<int,Compressor> &cs_map,list<int> &indexes);
void show_cs(unordered_map<int,Compressor> &cs_map,list<int> index);
void del_cs(unordered_map<int,Compressor> &cs_map);
void edit_cs(unordered_map<int,Compressor> &cs_map);
void pocket_edit_cs(unordered_map<int,Compressor> &cs_map);
void save_cs(unordered_map<int,Compressor> &cs_map, string file_name);
#endif // COMPRESSOR_H