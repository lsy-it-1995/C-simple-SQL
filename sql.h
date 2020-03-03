#ifndef SQL_H
#define SQL_H
#include <iostream>
#include "table.h"
#include <vector>
#include <string>
#include "parser.h"
#include <locale>
#include "../../../Documents/CS8(assignment)/StackandQueue/queue.h"
#include "../../../Documents/CS8(assignment)/STokenizer/stokenizer.h"
#include <fstream>

using namespace std;

class sql
{
public:
    sql(){}
    sql(string l)
    {
        str = l;
    }
    //find tablename
    void run()
    {
        //        instruction();
        take_string();
        bool debug = false;
        do
        {
            if(debug) cout<<"str: "<<str<<endl;
            MMap<string, string> ptree;
            Parser p(str);

            if(debug) cout<<"before anything in run"<<endl;
            if(debug) cout<<"str: "<<str<<endl;

            if(p.every_case(ptree))
            {
                if(debug) cout<<"ptree[COMMAND_str][0]: "<<ptree[COMMAND_str][0]<<endl;
                if(ptree[COMMAND_str][0]=="print")
                {
                    string tablename;
                    tablename = ptree[TABLE_str][0];
                    if(tablelist.contains(tablename))
                    {
                        bool debug_print = false;
                        if(debug_print) cout<<"successful in print case in sql"<<endl;
                        tablelist[tablename].print_table();
                        //                        tablelist[tablename].print_table(tablename);
                    }
                    else
                    {
                        cout<<"please load the tablename before you print"<<endl;
                    }
                }
                else if(ptree[COMMAND_str][0]=="create")
                {
                    bool debug_command = false;
                    if(debug_command) cout<<"parser run is true"<<endl;

                    if(debug_command) cout<<"parser tree: "<<endl<<ptree;
                    if(debug_command) cout<<"true after p.create_case"<<endl;
                    if(debug_command) cout<<"success on crerate case"<<endl;
                    string temp_table_name;
                    vector<string> v;

                    if(debug_command) cout<<"inside the temp.contains table str"<<endl;

                    temp_table_name = ptree[TABLE_str][0];

                    if(debug_command) cout<<"temp table name" <<temp_table_name<<endl;

                    v = ptree.get(CREATE_FIELDNAME_str);

                    if(debug_command) cout<<"v: "<<v<<endl;
                    //tablelist[temp_table_name] = table(temp_table_name, v); //table(fieldname,v);
                    tablelist.insert(temp_table_name,table(temp_table_name,v));

                    //                        if(debug_command) cout<<"printing :"<<endl;
                    if(debug_command) cout<<"completed create"<<endl;
                    cout<<"completed created"<<endl;
                }
                else if(ptree[COMMAND_str][0]=="insert")
                {
                    string tablename = ptree[TABLE_str][0];

                    //insert record into table
                    if(tablelist.contains(tablename))
                    {
                        bool debug_insert = true;
                        if(debug_insert) cout<<"INSERT: parser run is true"<<endl;

                        if(debug_insert) cout<<"tablenam: "<<tablename<<endl;
                        vector<string> fieldlist;
                        fieldlist = ptree.get(INSERT_FIELDLIST_str);
                        if(debug_insert) cout<<"fieldlist: "<<fieldlist<<endl;
                        tablelist[tablename].insert(fieldlist);
                        cout<<"inserted completed"<<endl;
                    }
                    else
                    {
                        cout<<"tabelelist doesn't found the file. please load"<<endl;
                    }
                }
//                else if(ptree[COMMAND_str][0]=="store")
//                {
//                    bool debug = false;
//                    string tablename = ptree[TABLE_str][0];
//                    if(tablelist.contains(tablename))
//                    {
//                        if(debug) cout<<"find out the table"<<endl;
//                        tablelist[tablename].store();
//                        if(debug) cout<<"store completed"<<endl;
//                        cout<<"stored completed"<<endl;
//                    }
//                    else
//                    {
//                        cout<<"please load the table first before you store"<<endl;
//                    }
//                }
                else if(ptree[COMMAND_str][0]=="load")
                {
                    string tablename = ptree[TABLE_str][0];
                    if(debug) cout<<"tablename: "<<tablename<<endl;
                    if(file_exists(tablename.c_str()))
                    {
                        tablelist.insert(tablename,table(tablename));
                        cout<<"load completed"<<endl;
                    }
                    else
                    {
                        cout<<"failed on loading a file because the file doesn't existed"<<endl;
                    }
                }
                else if(ptree[COMMAND_str][0]=="drop")
                {
                    bool debug_drop = false;
                    string str = ptree[TABLE_str][0];
                    if(debug_drop) cout<<"str: "<<str<<endl;
                    if(tablelist.contains(str))
                    {
                        tablelist[str].delete_table(str);
                        tablelist.erase(str);

                        cout<<"drop completed"<<endl;
                    }
                    else
                    {
                        cout<<"the file doesn't loaded yet, it can't be dropped!"<<endl;
                    }

                }
                else if(ptree[COMMAND_str][0]=="select")
                {
                    if(ptree.contains(TABLE_str))
                    {
                        string tablename;
                        tablename = ptree.get(TABLE_str)[0];
//                        if(ptree.contains(ASTERISK_str))
//                        {
//                            tablelist[tablename]
//                        }
//                        else
                       {
                        vector<string> fieldlist;

                        string fieldname;
                        string op;
                        string value;
                        fieldlist = ptree.get(field_list_str);
                        fieldname = ptree.get(comparision_str)[0];
                        op = ptree.get(OP_str)[0];
                        value = ptree.get(value_str)[0];
                        if(debug) cout<<"v: "<<fieldlist<<endl;
                        if(debug) cout<<"field name: "<<fieldname<<endl;
                        if(debug) cout<<"op: "<<op<<endl;
                        if(debug) cout<<"value: "<<value<<endl;
                        if(debug) cout<<"after setting up the value"<<endl;
                        tablelist[tablename].select_table(fieldlist,fieldname,op,value);
                        if(debug) cout<<"t.select table is all good"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"your table didn't loaded yet! please create first"<<endl;
                    }
                }
                else
                {
                    cout<<"failed command"<<endl;
                }
            }
        }while(take_string());
    }


    void instruction()
    {
        cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;

        ifstream f("Guideline.txt");
        string line;
        if(f.is_open())
        {
            while(!f.eof())
            {
                getline (f,line);
                cout << line << endl;
            }
        }
        f.close();
    }
    bool take_string()
    {
        cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
        cout<<"Command: ";
        getline(cin,str);
        string convert;
        locale loc;
        for(string::size_type i=0;i<str.length();++i)
        {
            convert[i]=tolower(str[i],loc);
            //            cout<<convert[i]<<" ";
            convert += convert[i];
        }

        str = convert;
        bool debug = false;
        if(debug)
        {
            cout<<"convert: "<<convert<<endl;
            cout<<"str: "<<str<<endl;

        }

        return !str.empty();
    }
private:
    Map<string, table> tablelist;
    string str;

};
#endif // SQL_H
