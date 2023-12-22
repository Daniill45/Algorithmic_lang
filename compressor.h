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
private:
    static int total;
    int id;
    string name;
    int manufact;
    double efficiency;
public:
    int manufact_in_work;
    int getid() const ;
    Compressor();
    void init(string new_name,int new_manuf,int new_working_manuf,double new_effic);
    string* get_name() ;
    int get_manufact() const;
    int get_manufact_in_work() const;
    double get_efficiency() const;
    void set_manufact_in_work(int new_manuf_in_work);
    static string type;
    //string Compressor::type="КС:";
    friend std::ostream& operator << (std::ostream& out, const Compressor& cs);
	friend std::istream& operator >> (std::istream& in, Compressor& cs);
};

void create_CS(unordered_map<int,Compressor> &cs_map);
void find_cs(unordered_map<int,Compressor> &cs_map,list<int> &indexes);
void show_cs(unordered_map<int,Compressor> &cs_map,list<int> index);
void del_cs(unordered_map<int,Compressor> &cs_map);
void edit_cs(unordered_map<int,Compressor> &cs_map);
void pocket_edit_cs(unordered_map<int,Compressor> &cs_map);
void save_cs(unordered_map<int,Compressor> &cs_map, string file_name);
#endif // COMPRESSOR_H