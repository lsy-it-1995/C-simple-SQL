#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "../../../Documents/CS8(assignment)/STokenizer/statemachine.h"
#include "constant.h"
#include "../../../Documents/CS8(assignment)/map_and_multi_maps/mmap.h"
#include "../../../Documents/CS8(assignment)/map_and_multi_maps/map.h"
#include "../../../Documents/CS8(assignment)/STokenizer/stokenizer.h"
#include "locale"

//https://www.youtube.com/watch?v=89kfIbnfNH4

using namespace std;


class Parser
{
public:
    Parser(string l)
    {
        bool debug = false;
        make_queue_of_strings(l);
        clear();
        //        print_table(table);
    }

    //    void duplicated_queue(Queue<string> &copy)
    //    {
    //        bool debug = false;
    //        _map.clear();
    //        if(debug) cout<<"in duplicated queue"<<endl;
    //        if(debug) cout<<"myq: "<<myq<<endl;
    //        copy = myq;
    //        if(debug) cout<<"copy: "<<copy<<endl;
    //    }
    void make_queue_of_strings(string l)
    {
        bool debug = false;
        s = STokenizer(l);
        Token t;
        s >> t;
        while(!s.done())
        {
            input.push_back(t.token_str());
            t = Token();
            s>>t;
        }
        input.push_back(t.token_str());
        //        if(debug) cout<<"size of myq: "<<myq.size()<<endl;
    }
    void clear()
    {
        _map.clear();
    }
    void print_queue()
    {
        for(size_t i = 0 ; i < input.size();i++)
            cout<<input[i]<<" "<<endl;
    }
    bool every_case(MMap<string, string> &ptree)
    {
        bool debug = false;
        if(debug) cout<<"every case "<<endl;
        if(print_case(ptree))
        {
            if(debug) cout<<"in print"<<endl;
            return true;
        }
        if(create_case(ptree))
        {
            if(debug) cout<<"in create"<<endl;
            return true;
        }
        if(select_case(ptree))
        {
            if(debug) cout<<"in select"<<endl;
            return true;
        }
        if(load_case(ptree))
        {
            if(debug) cout<<"in load"<<endl;
            return true;
        }
        if(store_case(ptree))
        {
            if(debug) cout<<"in store"<<endl;
            return true;
        }
        if(drop_table_case(ptree))
        {
            if(debug) cout<<"in drop"<<endl;
            return true;
        }
        if(insert_into_case(ptree))
        {
            return true;
        }
        cout<<"wrong command"<<endl;
        return false;

    }
    bool  print_case(MMap<string, string> &_mmap)
    {
        bool debug = false;
        if(debug) cout<<"in print case"<<endl;
        string temp;
        make_print_table(table);
        get_print_map();
        int row = INITIAL_ROW;
        int col = 0;
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        if(input[new_pos]!="print")
            return false;
        else
        {

            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(temp!=SPACE_str)
                {
                    col = get_print_col(temp);
                    row = table[row][col];
                    switch (row)
                    {
                    case PRINT_ROW:
                        _mmap[COMMAND_str] += temp;
                        break;
                    case PRINT_TABLE_ROW:
                        _mmap[TABLE_str] += temp;
                        break;
                    default:
                        break;
                    }
                }

            }
        }

        return (is_success(table,row))?true:false;
    }
    bool create_case(MMap<string, string> &_mmap)
    {
        //create table tablename fieldname1 datatype1, fieldname2, datatype2, etc
        bool debug = false;
        make_create_table(table);
        get_create_map();
        string temp;
        int row = INITIAL_ROW;
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        if(input[new_pos]!="create")
        {
            return false;
        }
        else
        {
            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(debug) cout<<"temp: "<<temp<<endl;

                if(temp!=SPACE_str)
                {
                    int col = get_create_col(temp);

                    row = table[row][col];
                    if(debug) cout<<"row: "<<row<<endl;
                    if(debug) cout<<"col: "<<col<<endl;
                    switch (row)
                    {
                    case CREATE_ROW:
                        _mmap[COMMAND_str] += temp;
                        if(debug) cout<<"state: "<<row<<endl;
                        if(debug)cout<<"create row"<<endl;
                        break;
                    case CREATE_TABLE_ROW:
                        _mmap[TABLE_str] += temp;
                        if(debug) cout<<"state: "<<row<<endl;
                        if(debug) cout<<"create table row"<<endl;
                        break;
                    case CREATE_FIELDNAME_ROW:
                        _mmap[CREATE_FIELDNAME_str] += temp;
                        if(debug) cout<<"state: "<<row<<endl;
                        if(debug) cout<<"fieldname: "<<temp<<endl;
                        break;
                    case CREATE_DATATYPE_ROW:
                        _mmap[CREATE_DATATYPE_str] += temp;
                        if(debug) cout<<"state: "<<row<<endl;
                        if(debug) cout<<"datatype row"<<endl;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        if(debug) cout<<"mmap: "<<endl<<_mmap<<endl;
        return (is_success(table,row))?true:false;
    }

    bool load_case(MMap<string, string> &_mmap)
    {
        //load tablename
        bool debug = false;
        if(debug) cout<<"load case"<<endl;
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        make_load_table(table);
        string temp;
        get_load_map();
        int row = INITIAL_ROW;
        if(input[new_pos]!="load")
            return false;
        else
        {
            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                if(debug) cout<<"in while loop"<<endl;

                temp = input[i];
                if(temp!=SPACE_str)
                {
                    int col = get_load_col(temp);
                    row = table[row][col];
                    if(debug) cout<<"temp: "<<temp<<endl;
                    if(debug) cout<<"row: "<<row<<endl;
                    if(debug) cout<<"col: "<<col<<endl;
                    if(debug) cout<<"new row: "<<row<<endl;

                    switch (row) {
                    case LOAD_ROW:
                        if(debug) cout<<"here in load row"<<endl;
                        _mmap[COMMAND_str] += temp;
                        break;
                    case LOAD_TABLE_ROW:
                        if(debug) cout<<"load table row"<<endl;
                        _mmap[TABLE_str] += temp;
                        break;
                    default:
                        break;
                    }
                }
            }

        }
        if(debug) cout<<endl<<_mmap;
        return (is_success(table,row))?true:false;
    }
    bool store_case(MMap<string, string> &_mmap)
    {
        bool debug = false;
        if(debug) cout<<"in store case"<<endl;
        //store tablename
        make_store_table(table);
        string temp;
        get_store_map();
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        int row = INITIAL_ROW;
        if(input[new_pos]!="store")
        {
            return false;
        }
        else
        {
           for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(temp!=SPACE_str)
                {
                    int col = get_store_col(temp);
                    row = table[row][col];
                    switch (row)
                    {
                    case STORE_ROW:
                        _mmap[COMMAND_str]+= temp;
                        break;
                    case STORE_TABLE_ROW:
                        _mmap[TABLE_str] += temp;
                    default:
                        break;
                    }
                }
            }
        }
        return (is_success(table,row))?true:false;
    }
    bool drop_table_case(MMap<string, string> &_mmap)
    {
        bool debug = false;
        if(debug) cout<<"in drop case"<<endl;
        //drop tablename
        make_drop_table(table);
        string temp;
        get_drop_map();
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        int row = INITIAL_ROW;
        if(input[new_pos]!="drop")
            return false;
        else
        {
            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(temp!=SPACE_str)
                {
                    int col = get_drop_col(temp);
                    row = table[row][col];

                    switch (row)
                    {
                    case DROP_ROW:
                        _mmap[COMMAND_str] += temp;
                        break;
                    case DROP_TABLE_ROW:
                        _mmap[TABLE_str] += temp;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        return (is_success(table,row))?true:false;
    }
    bool insert_into_case(MMap<string, string> &_mmap)
    {
        //insert into tablename stuff1, stuff2, stuff3 ...
        bool debug = false;
        if(debug) cout<<"inside insert into"<<endl;
        string temp;
        int col = 0 ;
        int row = INITIAL_ROW;
        get_insert_into_map();
        make_insert_into_table(table);
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        if(input[new_pos]!="insert")
        {
            return false;
        }
        else
        {
            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(temp!= SPACE_str)
                {
                    col = get_insert_into_col(temp);
                    row = table[row][col];
                    if(debug) cout<<"temp: "<<temp<<endl;
                    if(debug) cout<<"col: "<<col<<endl;
                    if(debug) cout<<"row: "<<row<<endl;

                    switch(row)
                    {

                    case INSERT_ROW:
                        _mmap[COMMAND_str] += temp;
                        break;
                    case INSERT_TABLENAME_ROW:
                        _mmap[TABLE_str] += temp;
                        break;
                    case INSERT_VALUE_ROW:
                        _mmap[INSERT_FIELDLIST_str] += temp;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        if(debug) cout<<"123"<<endl<<_mmap;

        return (is_success(table,row))?true:false;
    }
    bool select_case(MMap<string, string> &_mmap)
    {
        //select fieldname from tablename where fieldname2 = "value"
        //select * from tablename where fieldname2 = "value" (* = all)
        make_select_table(table);
        bool debug = false;
        bool debug_outside_switch = false;
        if(debug_outside_switch) cout<<"in select case"<<endl;
        string temp;
        int col = 0;
        int row = INITIAL_ROW;
        get_select_map();
        if(debug_outside_switch)  cout<<"so far so good"<<endl;
        size_t new_pos =0;
        while(input[new_pos]==SPACE_str)
            new_pos++;
        if(input[new_pos]!="select")
        {
            return false;
        }
        else
        {
            for(size_t i = new_pos ; i < input.size() ; i++)
            {
                temp = input[i];
                if(temp!=SPACE_str)
                {
                    col = get_select_col(temp);
                    row = table[row][col];
                    if(debug_outside_switch) cout<<"temp: "<<temp<<endl;
                    if(debug_outside_switch) cout<<"col: "<<col<<endl;
                    if(debug_outside_switch) cout<<"row: "<<row<<endl;
                    switch(row)
                    {
                    case SELECT_ROW:
                        _mmap[COMMAND_str]+=temp;
                        if(debug) cout<<"mmap in COMMAND_str: "<<endl<<_mmap;
                        break;

                        //                case AND_OR_ROW_2:
                        //                    _mmap[AND_str] +=temp;
                        //                    if(debug) cout<<"mmap in AND_str: "<<endl<<_mmap<<endl;
                        //                    break;
                    case OPERATOR_ROW:
                        _mmap[OP_str] += temp;
                        if(debug) cout<<"mmap in OP_str: "<<endl<<_mmap;
                        break;
                    case FIELD_NAME_ROW:
                        _mmap[field_list_str] += temp;
                        if(debug) cout<<"mmap in value_str: "<<endl<<_mmap;
                        break;
                    case FIELD_NAME_ROW_2:
                        _mmap[comparision_str] += temp;
                        if(debug) cout<<"mmap in value_str: "<<endl<<_mmap;
                        break;
                    case VALUE_ROW:
                        _mmap[value_str] += temp;
                        break;
                    case AND_OR_ROW_2:
                        _mmap[AND_OR_str]+= temp;
                        break;
                    case TABLE_NAME_ROW:
                        _mmap[TABLE_str] += temp;
                        if(debug) cout<<"mmap in value_str: "<<endl<<_mmap;
                        break;
                    case ASTERISK_ROW:
                        _mmap[ASTERISK_str] += temp;
                        break;
                    case WHERE_ROW:
                        _mmap[where_str] += "yes";
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        if(debug_outside_switch) cout<<"123"<<endl<<_mmap;
        return (is_success(table,row))?true:false;
    }

    /*
const int INITIAL_ROW = 0;
const int SELECT_ROW = 1;
const int FIELD_NAME_ROW = 13;
const int AND_OR_ROW = 14;
const int COMMA_ROW = 15;

const int ASTERISK_ROW = 2;
const int FROM_ROW = 3;
const int TABLE_NAME_ROW = 4;
const int WHERE_ROW = 5;

const int FIELD_NAME_ROW_2 = 6;
const int OPERATOR_ROW = 7;
const int QUOTATION_ROW_1 = 8;
const int VALUE_ROW = 9;
const int QUOTATION_ROW_2 = 10;

const int COMMA_ROW_2 = 12;
const int AND_OR_ROW_2 = 11;
 */

private:
    int table[MAX_ROWS][MAX_COLUMNS];
    STokenizer s;
    vector<string> input;
    Map<string,int> _map;

    void get_insert_into_map()
    {
        clear();
        _map["insert"] = INSERT_COL;
        _map["into"] = INSERT_COL;
        _map[","] = INSERT_COMMA_COL;
    }

    void make_insert_into_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        //insert into tablename 'value' ;
        init_table(table);
        mark_fail(table,INSERT_ROW);
        mark_fail(table, INSERT_TABLENAME_ROW);
        mark_success(table,INSERT_VALUE_ROW);
        mark_fail(table, INSERT_COMMA_ROW);
        mark_cell(INITIAL_ROW, table, INSERT_COL, INSERT_ROW);
        mark_cell(INSERT_ROW, table, INSERT_COL, INSERT_ROW);
        mark_cell(INSERT_ROW, table, INSERT_STR_COL, INSERT_TABLENAME_ROW);
        mark_cell(INSERT_TABLENAME_ROW, table, INSERT_STR_COL, INSERT_VALUE_ROW);
        mark_cell(INSERT_VALUE_ROW, table, INSERT_COMMA_COL, INSERT_COMMA_ROW);
        mark_cell(INSERT_COMMA_ROW, table, INSERT_STR_COL, INSERT_VALUE_ROW);
    }
    int get_insert_into_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        else
        {
            return INSERT_STR_COL;
        }
    }
    int get_create_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        else
        {
            if(debug) cout<<"create str col"<<CREATE_str_COL<<endl;
            return CREATE_str_COL;
        }
    }
    void get_create_map()
    {
        clear();
        _map["create"] = CREATE_COL;
        _map["table"] = CREATE_COL;
        _map[","]  = CREATE_COMMA_COL;

    }
    void make_create_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,CREATE_ROW);
        mark_fail(table,CREATE_TABLE_ROW);
        mark_fail(table, CREATE_FIELDNAME_ROW);
        mark_success(table,CREATE_DATATYPE_ROW);
        mark_fail(table,CREATE_COMMA_ROW);
        mark_cell(INITIAL_ROW,table,CREATE_COL,CREATE_ROW);
        mark_cell(CREATE_ROW,table,CREATE_COL,CREATE_ROW);
        mark_cell(CREATE_ROW,table,CREATE_str_COL,CREATE_TABLE_ROW);
        mark_cell(CREATE_TABLE_ROW,table,CREATE_str_COL,CREATE_FIELDNAME_ROW);
        mark_cell(CREATE_FIELDNAME_ROW,table,CREATE_str_COL,CREATE_DATATYPE_ROW);
        mark_cell(CREATE_DATATYPE_ROW,table,CREATE_COMMA_COL,CREATE_COMMA_ROW);
        mark_cell(CREATE_COMMA_ROW,table,CREATE_str_COL,CREATE_FIELDNAME_ROW);
    }
    int get_store_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        {
            return STORE_TABLE_COL;
        }
    }
    void get_store_map()
    {
        clear();
        _map["store"] = STORE_COL;
    }
    void make_store_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,STORE_ROW);
        mark_success(table,STORE_TABLE_ROW);
        mark_cell(INITIAL_ROW,table,STORE_COL,STORE_ROW);
        mark_cell(STORE_ROW,table,STORE_TABLE_COL,STORE_TABLE_ROW);

    }
    int get_load_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        else
        {
            return LOAD_TABLE_COL;
        }
    }
    void get_load_map()
    {
        clear();
        _map["load"] = DROP_COL;
    }

    void make_load_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,LOAD_ROW);
        mark_success(table,LOAD_TABLE_ROW);
        mark_cell(INITIAL_ROW,table,LOAD_COL,LOAD_ROW);
        mark_cell(LOAD_ROW,table,LOAD_TABLE_COL,LOAD_TABLE_ROW);
    }

    int get_drop_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        else
        {
            return DROP_TABLE_COL;
        }
    }
    void get_drop_map()
    {
        clear();
        _map["drop"] = DROP_COL;
    }
    void make_drop_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,DROP_ROW);
        mark_success(table,DROP_TABLE_ROW);
        mark_cell(INITIAL_ROW,table,DROP_COL,DROP_ROW);
        mark_cell(DROP_ROW,table,DROP_TABLE_COL,DROP_TABLE_ROW);
        mark_cell(DROP_TABLE_ROW,table,DROP_TABLE_COL,-1);
    }

    int get_print_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string, int> (str)))
        {
            if(debug) cout<<"map str: "<<_map[str]<<endl;
            return _map[str];
        }
        else
        {
            return PRINT_TABLE_COL;
        }
    }

    void get_print_map()
    {
        clear();
        _map["print"] = PRINT_COL;
    }

    void make_print_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,PRINT_COL);
        mark_success(table,PRINT_TABLE_ROW);
        mark_cell(INITIAL_ROW,table,PRINT_COL,PRINT_ROW);
        mark_cell(PRINT_ROW,table,PRINT_TABLE_COL,PRINT_TABLE_ROW);
        mark_cell(PRINT_TABLE_ROW,table,PRINT_TABLE_COL,-1);
    }
    int get_select_col(string str)
    {
        bool debug = false;
        if(_map.contains(Pair<string,int> (str)))
        {
            if(debug) cout<<"map str" << _map[str]<<endl;
            return _map[str];
        }
        else
        {
            if(debug) cout<<"other in get int "<<endl;
            return STR_COL;
        }
    }
    void get_select_map()
    {
        /*
        const int SELECT_COL =1;
        const int FROM_COL = 2;
        const int STR_COL =3; // str/value, fieldname or tablename
        const int WHERE_COL = 4;
        const int OPERATOR_COL = 5;
        const int QUOTATION_COL = 6;
        const int AND_OR_COL = 7;
        const int COMMA_COL = 8;
        const int ASTERISK_COL = 9;
         */
        clear();
        _map["select"] = SELECT_COL;
        _map["*"] = ASTERISK_COL;
        _map["from"] = FROM_COL;
        _map["where"] = WHERE_COL;
        _map[","] = COMMA_COL;
        _map["<"] = OPERATOR_COL;
        _map[">"] = OPERATOR_COL;
        _map["="] = OPERATOR_COL;
        _map["<="] = OPERATOR_COL;
        _map["<="] = OPERATOR_COL;
        _map["!="] = OPERATOR_COL;
        _map["and"] = AND_OR_COL;
        _map["or"] = AND_OR_COL;
        _map["'"] = QUOTATION_COL;

    }
    void make_select_table(int table[MAX_ROWS][MAX_COLUMNS])
    {
        /*
        const int SELECT_COL =1;
        const int FROM_COL = 2;
        const int STR_COL =3; // str/value, fieldname or tablename
        const int WHERE_COL = 4;
        const int OPERATOR_COL = 5;
        const int QUOTATION_COL = 6;
        const int AND_OR_COL = 7;
        const int COMMA_COL = 8;
        const int ASTERISK_COL = 9;
         */

        /*
    const int INITIAL_ROW = 0;
    const int SELECT_ROW = 1;
    const int FIELD_NAME_ROW = 13;
   //` const int AND_OR_ROW = 14;
    const int COMMA_ROW = 15;

    const int ASTERISK_ROW = 2;
    const int FROM_ROW = 3;
    const int TABLE_NAME_ROW = 4;
    const int WHERE_ROW = 5;

    const int FIELD_NAME_ROW_2 = 6;
    const int OPERATOR_ROW = 7;
    const int QUOTATION_ROW_1 = 8;
    const int VALUE_ROW = 9;
    const int QUOTATION_ROW_2 = 10;

    const int COMMA_ROW_2 = 12;
    const int AND_OR_ROW_2 = 11;
     */
        init_table(table);
        mark_fail(table,INITIAL_ROW);
        mark_fail(table,SELECT_ROW);
        mark_fail(table,FIELD_NAME_ROW);
        //        mark_fail(table,AND_OR_ROW);
        mark_fail(table,COMMA_ROW);
        mark_fail(table,ASTERISK_ROW);
        mark_fail(table,FROM_ROW);
        mark_success(table,TABLE_NAME_ROW);
        mark_fail(table,WHERE_ROW);
        mark_fail(table,FIELD_NAME_ROW_2);
        mark_fail(table,OPERATOR_ROW);
        mark_fail(table,QUOTATION_ROW_1);
        mark_fail(table,VALUE_ROW);
        mark_success(table,QUOTATION_ROW_2);
        mark_fail(table,COMMA_ROW_2);
        mark_fail(table, AND_OR_ROW_2);

        mark_cell(INITIAL_ROW,table,SELECT_COL,SELECT_ROW);
        mark_cell(SELECT_ROW,table, ASTERISK_COL,ASTERISK_ROW);
        mark_cell(SELECT_ROW,table, STR_COL,FIELD_NAME_ROW);
        mark_cell(ASTERISK_ROW,table,FROM_COL,FROM_ROW);
        mark_cell(FROM_ROW,table,STR_COL,TABLE_NAME_ROW);
        mark_cell(TABLE_NAME_ROW,table,WHERE_COL,WHERE_ROW);
        mark_cell(WHERE_ROW,table,STR_COL,FIELD_NAME_ROW_2);
        mark_cell(FIELD_NAME_ROW_2,table,OPERATOR_COL,OPERATOR_ROW);
        mark_cell(OPERATOR_ROW,table,QUOTATION_COL,QUOTATION_ROW_1);
        mark_cell(QUOTATION_ROW_1,table,STR_COL,VALUE_ROW);
        mark_cell(VALUE_ROW,table,QUOTATION_COL,QUOTATION_ROW_2);
        mark_cell(QUOTATION_ROW_2,table,AND_OR_COL,AND_OR_ROW_2);
        mark_cell(QUOTATION_ROW_2,table,COMMA_COL,COMMA_ROW_2);
        mark_cell(AND_OR_ROW_2,table,STR_COL,FIELD_NAME_ROW_2);
        mark_cell(COMMA_ROW_2,table,AND_OR_COL,AND_OR_ROW_2);

        mark_cell(FIELD_NAME_ROW,table,FROM_COL,FROM_ROW);
        //        mark_cell(FIELD_NAME_ROW,table,AND_OR_COL,AND_OR_ROW);
        mark_cell(FIELD_NAME_ROW,table,COMMA_COL,COMMA_ROW);
        //        mark_cell(AND_OR_ROW,table,STR_COL,FIELD_NAME_ROW);
        mark_cell(COMMA_ROW,table,STR_COL,FIELD_NAME_ROW);
        //        mark_cell(COMMA_ROW,table,AND_OR_COL,AND_OR_ROW);


    }
};

#endif // PARSER_H
