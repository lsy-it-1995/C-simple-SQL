#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <string>

#include <cstring>
#include <vector>
#include "constant.h"

using namespace std;
class Record{
public:
    Record(){
        record[0][0] = NULL;
        count = 0;
    }

    Record(vector<string> two_D)
    {
        bool debug = true;

        for(size_t i = 0; i < MAX;i++)
        {

            if(i<two_D.size())
                strcpy(record[i],two_D[i].c_str());
            else
            {
                record[i][0] = NULL;
            }
        }

        count = two_D.size();
    }
    long write(fstream &outs);
    long read(fstream& ins, long recno);
    int size()
    {
        bool debug = true;
        if(debug)
            cout<<"count: "<<count<<endl;
        return MAX*MAX;
    }
    string getRecord();
    string get(int pos1);
    //    vector<string> operator [](int index)
    //    {
    //        string temp(record[index]);
    //        return temp;
    //    }
    string operator [](int index)
    {
        bool debug = false;
        if(debug)
            cout<<"in record operator []"<<endl;
        string temp(record[index]);


        if(debug)
        {
            cout<<"index: "<<index<<endl;
            cout<<"r[index]"<<record[index]<<endl;
            cout<<"end of record operator []"<<endl;
        }
        return temp;
    }

    friend ostream& operator<<(ostream& outs, const Record& r);
private:
    size_t count = 0;
    char record[MAX][MAX];
};

bool file_exists(const char filename[]);

void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);
void deletefile(string name);

string Record::get(int pos1)
{
    bool debug = false;
    if(debug)
        cout<<"in get record"<<endl;
    string temp(record[pos1]);
    if(debug)
    {
        cout<<"record[pos1]: "<<record[pos1]<<endl;
        cout<<"in get record"<<endl;
        cout<<"pos1: "<<pos1<<endl;
        cout<<"temp: "<<temp<<endl;
        cout<<"--------------"<<endl;
    }

    return temp;
}

long Record::write(fstream &outs){
    //write to the end of the file.
    const bool debug = false ;

        long pos = outs.tellp();
        if(debug)
            cout<<"pos in write record: "<<pos<<endl;
        outs.write(&record[0][0], sizeof(record));

        if(debug) cout<<"count: "<<count<<endl;
        return pos;
}
long Record:: read(fstream &ins, long recno){
    bool debug = false;

    long pos = recno * sizeof(record);
    if(debug) cout<<"pos: "<<pos<<endl;
    ins.seekg(pos, ios_base::beg);

    ins.read(&record[0][0], sizeof(record));

    return ins.gcount();
}
ostream& operator<<(ostream& outs, const Record& r)
{
    const bool debug = false;
    if(debug) cout<<"count in opereator record"<<r.count<<endl;
    for(int i =0 ; i < MAX;i++)
    {
        if(r.record[i][0]!=NULL)
            outs<<r.record[i]<<"\t";
    }
    if(debug) cout<<"not here"<<endl;
    return outs;
}

//-------------------------------------------------

void deletefile(string name)
{
    fstream f;
    remove(name.c_str());
}
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename, ios::out |std::fstream::in | std::fstream::binary );
    if (ff.fail())
    {
        if (debug) cout<<"file_exists: File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists: File DOES exist: "<<filename<<endl;
    return true;
}

void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if(debug)
    {
        cout<<"name: "<<filename<<endl;

    }
    if (!file_exists(filename)){
        f.open(filename, ios::app|std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    }
    else{
        f.open (filename, std::fstream::in | std::fstream::out| std::fstream::binary);
        if (f.fail()){
            cout<<"feile open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[]){
    f.open (filename, ios::app |std::fstream::out| std::fstream::binary);
    if (f.fail())
    {
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }

}

string Record::getRecord()
{
    string myRecord(&record[0][0], sizeof(record));

    return myRecord;
}

#endif // RECORD_H
