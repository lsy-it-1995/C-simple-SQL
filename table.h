#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include "record.h"
#include "../../../Documents/CS8(assignment)/B_PLUS_TREE/b_plus_tree.h"
#include "../../../Documents/CS8(assignment)/map_and_multi_maps/mmap.h"
#include "../../../Documents/CS8(assignment)/map_and_multi_maps/map.h"

using namespace std;

class table
{
public:
    table()
    {
        const bool debug = false;
        if(debug) cout<<"DEFAULT CTOR fired 1"<<endl;
        name = '/0';
        record_count = 0;
    }
    table(string inputname, vector<string> inputfields)
    {
        record_count = 0;
        name = inputname;

        for(size_t i = 0; i < inputfields.size(); i++)//know which number did i go
            field_list.insert(inputfields[i],i);
        //            field_list.get(inputfields[i]);
        for(int i = 0; i < inputfields.size(); i++)
            field_name.push_back(inputfields[i]);
        for(size_t i = 0; i < inputfields.size(); i++) //create how many columes.
            Indices.push_back(MMap<string, long>());
        fstream f;
        Record r(inputfields);

        open_fileRW(f, name.c_str());
        f.seekg(0, f.end);

        r.write(f);
        f.close();

    }
    table(string _name)
    {
        // load tablename
        //stuff to fix
        //such as previous-record can't be missed
        name = _name;
        record_count = 0;
        fstream f;
        Record r;

        if(file_exists(name.c_str())){
            open_fileRW(f,name.c_str());
            f.seekg (0, f.end);
            int length = f.tellg();
            f.seekg (0, f.beg);

            cout<<"r.size: "<<r.size()<<endl;
            cout<<"length: "<<length<<endl;
            record_count = length/r.size();
            cout<<"record_count: "<<record_count<<endl;
            int i = 0;
            r.read(f,0);

            while(r[i][0]!=NULL)
            {
                cout<<"r: "<<r[i][0]<<endl;
                field_name.push_back(r[i]);
                ++i;
            }
            cout<<"end"<<endl;
            for(unsigned int i =0; i<field_name.size(); ++i)
            {
                field_list.insert(field_name[i],i);
            }
            cout<<"fieldlist"<<field_list<<endl;
            cout<<"My size: "<<field_name.size()<<endl;
            for(int i =0 ; i < field_name.size();i++)
            {
                Indices.push_back(MMap<string, long> ());
            }
            for(long i =1; i<record_count+1; ++i)
            {
                r.read(f,i);
                for(size_t j =0; j<field_name.size(); ++j)
                {
                    string token = r[j];
                    Indices[j][token]+=i;
                }
            }
            //            for(size_t k = 0 ; k< record_count+1;k++)
            //            {
            //                cout<<"k: "<<k<<endl;
            //                cout<<Indices[k]<<endl;
            //            }
            //            cout<<"indices"<<endl<<Indices;

        }
        else
        {
            open_fileRW(f, name.c_str());
        }
        f.close();

        //        cout << "DEBUG: inside the correct constructor." << endl;
        //        if(file_exists(name.c_str()))
        //        {
        //            fstream f;
        //            Record r;
        //            char* token;
        //            char buffer[MAX*MAX];
        //            int fileSize = 0;
        //            open_fileRW(f, name.c_str());
        //            //moving position to end of file to find out file size
        //            //using this to loop how many times to read.
        //            f.seekg(0, f.end);
        //            fileSize = f.tellg();
        //            f.seekg(0, f.beg);
        ////            open_fileRW(f, name.c_str());
        //            record_count = r.read(f,record_count);
        //            strcpy(buffer, r.getRecord().c_str());
        //            token = strtok(buffer, ", ");
        //            while(token)
        //            {
        //                cout<<"token: "<<token<<endl;
        //                field_name.push_back(token);
        //                token = strtok(NULL, ", ");
        //            }
        //            //Initializing map
        //            for(size_t i = 0; i < field_name.size(); i++)
        //                field_list.push_back(field_name[i]);
        ////                field_list.get(field_name[i]);
        //            for(size_t i = 0; i < field_name.size(); i++)
        //                Indices.push_back(MMap<string, long>());
        //            cout<<"f.tellg(): "<<f.tellg()<<endl;
        //            cout<<"filesize: "<<fileSize<<endl;
        //            while(f.tellg() < fileSize)
        //            {
        //                char* token2;
        //                char buffer2[MAX*MAX];
        //                vector<string> myTokens;
        //                int howManyTokens = 0;

        //                record_count = r.read(f, record_count);
        //                strcpy(buffer2, r.getRecord().c_str());
        //                token2 = strtok(buffer2, ", ");
        //                while(token2)
        //                {
        //                    howManyTokens++; //it might be inside or outside one more time?
        //                    myTokens.push_back(token2);
        //                    token2 = strtok(NULL, ", ");
        //                }
        //                cout << "DEBUG: howManyTokens: " << howManyTokens << endl;
        //                if(howManyTokens == field_name.size())
        //                    for(int i = 0; i < field_name.size(); i++)
        //                        Indices[i].insert(field_name[i], record_count);
        //            }
        //            f.close();

    }

    void insert(vector<string> input)
    {
        record_count  ++;
        if(input.size()>Indices.size())
        {
            cout<<"your input is over the max columes"<<endl;
            exit(1);
        }
        fstream f;
        Record r(input);

        open_fileRW(f, name.c_str());
        f.seekg(0, f.end);
        r.write(f);
        f.close();
        for(size_t i = 0; i < input.size(); i++)
            field_name.push_back(input[i]);
        for(size_t i =0 ; i <input.size();i++)
        {
            Indices[i].insert(input[i],record_count);
        }
    }
    void insert_record(Record input, string inputname)
    {

        //        record_count  += MAX*MAX;
        fstream f;
        open_fileRW(f, inputname.c_str());
        f.seekg(0, f.end);
        input.write(f);
        f.close();
        //        for(size_t i = 0; i < input.size(); i++)
        //            field_name.push_back(input[i]);
        for(size_t i =0 ; i <field_name.size();i++)
        {
            Indices[i].insert(input[i],record_count);
        }
        record_count++;
    }

    table select_all(string inputname)
    {
        name = inputname;

    }
    table select_table(vector<string> fieldlist, string fieldname, string op, string value)
    {
        // select lname, fname from student where lname             =     'lee'
        //           ^     ^                        ^               ^       ^
        //           fieldlist                    fieldname        op     value
        bool debug = true;
        if(debug)
        {
            cout<<"in select table"<<endl;
            cout<<"name: "<<name<<endl;
        }
        fstream f;

        if(op == "=")
        {
            string new_table = "new_dengyu_table";
            name = new_table;
            table temp(new_table);
            open_fileRW(f,name.c_str());


            Record r;
            vector<long> grab;
            grab = Indices[field_list[fieldname]][value];
            for(size_t i = 0 ; i < grab.size();i++)
            {
                cout<<"grab[i]: "<<grab[i]<<endl;
                r.read(f,grab[i]);
                temp.insert_record(r,new_table);
            }
            cout<<endl<<"the select table is "<<endl;
            name = new_table;
            print_table();
            delete_table(new_table);

            f.close();

        }
        else if(op==">")
        {
            string new_table = "new_dayu_table";
            name = new_table;
            table temp(new_table);

            open_fileRW(f,name.c_str());

            Record r;
            vector<long> grab1;
            //            grab1 = Indices[field_list[fieldname]][value];
            vector<long> all;

            for(MMap<string, long>::Iterator it =Indices[field_list[fieldname]].upper_bound(fieldname);it!=Indices[field_list[fieldname]].end();it++)
            {
                cout<<(*it)<<endl;
                grab1+=(*it).value_list;

            }
            //            cout<<"grab1.size(): "<<grab1.size()<<endl;

            for(size_t i = 0 ; i < grab1.size();i++)
            {
                //                cout<<"grab[i]: "<<grab1[i]<<endl;
                all += grab1[i];
            }
            //            cout<<"all: "<<all<<endl;

            cout<<all.size()<<endl;
            for(size_t i =0 ; i < all.size();i++)
            {
                r.read(f,all[i]);
                cout<<"r: "<<r<<endl;
                temp.insert_record(r,new_table);
            }
            cout<<endl<<"the select table is "<<endl;
            name = new_table;
            print_table();
            delete_table(new_table);
            f.close();
        }
        else if(op =="<")
        {
            //            cout<<"in <"<<endl;
            string new_table = "new_xiaoyu_table";
            name = new_table;
            table temp(new_table);

            open_fileRW(f,new_table.c_str());

            Record r;
            vector<long> grab1;
            //            grab1 = Indices[field_list[fieldname]][value];
            vector<long> all;
            //cout<<"bubba";
            cout<<"Indices[field_list[fieldname]].begin(): "<<endl;
            //            Indices[field_list[fieldname]].printTest();
            for(MMap<string, long>::Iterator it =Indices[field_list[fieldname]].begin();it!=Indices[field_list[fieldname]].end();it++)
            {

                if((*it).key>=value)
                    break;
                cout<<"here"<<endl;
                cout<<(*it)<<endl;

                grab1+=(*it).value_list;
                cout<<"inserting ";
                cout<<(*it).value_list;
                cout<<"Your grab: "<<grab1<<endl;
            }
            cout<<"grab1.size(): "<<grab1.size()<<endl;
            for(size_t i = 0 ; i < grab1.size();i++)
            {
                cout<<"grab[i]: "<<grab1[i]<<endl;
                all += grab1[i];
            }
            //            cout<<"all: "<<all<<endl;

            cout<<all.size()<<endl;
            for(size_t i =0 ; i < all.size();i++)
            {
                r.read(f,all[i]);
                cout<<"r: "<<r<<endl;
                temp.insert_record(r,new_table);
            }
            cout<<endl<<"the select table is "<<endl;
            name = new_table;
            delete_table(new_table);

            print_table();
        }


        //            cout<<"field_list "<<endl;
        //            cout<<field_list<<endl;
        //            cout<<"field_list.size(): "<<field_list.size()<<endl;
        //            for(size_t j = 0 ; j < fieldlist.size();j++)
        //            {
        //                cout<<"j = "<<j<<endl;
        //                if(field_list.contains(fieldlist[j]))
        //                {
        //                    col.push_back(field_list[fieldlist[j]]);
        //                    //                    cout<<"col "<<col<<endl;
        //                }
        //                else
        //                {
        //                    //                    cout<<"not found when j = "<<j<<endl;
        //                }
        //            }
        //        string select = "select";
        //        return specific_table;
        //        if(op == "=")
        //        {
        //            if(debug) cout<<"=========="<<endl;
        //            if(debug) cout<<"field_list.size()"<<field_list.size()<<endl;
        //            for(size_t i = 0; i < lists.size();i++)
        //            {
        //                if(field_list[0] == Indices[i])
        //                    temp_row = i;
        //                else
        //                    temp_row = i+1;
        //            }
        //            if(debug) cout<<"temp row: "<<temp_row<<endl;

        //            v_long = Indices[temp_row][];

        //            //every rows for the value
        //            if(debug) cout<<"making v_long"<<endl;

        //            for(size_t i = 0; i < v_long.size(); i++)
        //            {
        //                r.read(f,v_long[i]);
        //                temp = r[v_long[i]];
        //                temp_insert.push_back(temp);
        //            }
        //            if(debug) cout<<"problem here"<<endl;
        //            t = table(fieldname,field_list).insert(temp_insert,fieldname);
        //            return t;
        //        }

    }

    //    void store()
    //    {
    //        fstream f;
    //        Record r(field_list);
    //        open_fileRW(f,name.c_str());
    //        cout<<"field_name: "<<field_name<<endl;

    //        r.write(f);
    //        f.close();
    //        for(size_t i =0 ; i < field_list.size(); i++)
    //        {
    //            temp_field_list;
    //            r(temp_field_list);
    //            r.write(f);
    //        }
    //    }

    void delete_table(string intname)
    {
        bool debug = false;
        if(debug) cout<<"delete table"<<endl;
        fstream f;
        f.open(intname,ios::in | ios::binary);
        if(f.fail())
        {
            cout<<"file is unable to open"<<endl;
        }
        else
        {
            f.close();
            remove(intname.c_str());
        }
    }
    bool check_table(string filename)
    {
        return file_exists(filename.c_str())?true:false;
    }
    MMap<long, string> sort_indices()
    {
        MPair<string, int> A("key",1984);
        cout<<A<<endl;
        MMap<long, string> sorted;
        int size = Indices.size(),size2;
        for (int i = 0; i < size; i++)//go thru vectors
        {
            if (!Indices[i].empty())
            {
                cout<<"Not empty!"<<endl;
                MMap<string, int> testicle;
                testicle["1984"] += 888;
                cout<<"Man's weakness: "<<testicle["1984"]<<endl;
                //                cout<<"Indices[i]: "<<Indices[i]<<endl;
                MMap<string, long>::Iterator it_theclown = Indices[i].begin();
                for (MMap<string, long>::Iterator it = Indices[i].begin(); it != Indices[i].end(); it++)//go thru mmap
                {
                    cout<<"I'm inside"<<endl;
                    size2 = (*it).value_list.size();//get number of recs
                    cout<<"Size of value_list: "<<size2<<endl;
                    for (int j = 0; j < size2; j++)//loop thru value_list
                        sorted[(*it).value_list[j]] += (*it).key;//push key into recno at index
                }
            }
        }
        cout<<"made it!"<<endl;
        return sorted;
    }
    void print_table()
    {
        fstream f;
        open_fileRW(f, name.c_str());
        Record r;
        int i = 0 ;
        while(true)
        {
            r.read(f,i);
            if(f.eof()) break;
            cout << r << endl;
            i++;
        }
        //        cout<<"print table"<<endl;
        //        MMap<long, string> sorted = sort_indices();
        //        cout<<sorted<<endl;

        //        cout<<"in print table"<<endl;
        //        cout<<"size of fieldname size"<<field_name.size()<<endl;
        //        int z = field_list.size();
        //        for(int i = z; i < field_name.size(); i++)
        //        {
        //            for(int j = 0 ; j < field_list.size();j++)
        //            {
        //                cout<<field_list[j];
        //            }
        //            cout<<endl;
        //            cout << field_name[i] << ": ";

        //        }

        //        cout << endl;
        //        cout<<"print table"<<endl;
        //        cout<<"Indices: "<<Indices.size()<<endl;
        //        for(size_t i =0 ; i < field_name.size() ;i++)
        //        {

        //        }
    }
    friend bool operator ==(const table& lhs, const table& rhs)
    {
        return lhs == rhs;
    }
    friend table operator +(const table& lhs, const table& rhs)
    {
        //probably will never get used. Needed by map
        return lhs;
    }
    friend ostream& operator <<(ostream& outs, const table& print_me)
    {
        //        print_me.print_table(print_me.name);
        return outs;
    }


private:
    string name;
    vector<string> field_name;
    Map<string,long> field_list;
    //    vector<string> field_list;
    vector<MMap<string, long> > Indices;
    long record_count;
};
#endif // TABLE_H
