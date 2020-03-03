#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
#include <iostream>
using namespace std;

//Record
static const int MAX = 10;

//common
const int INITIAL_COL = 0;

const string SPACE_str = " ";
const string COMMAND_str = "command";
const string TABLE_str = "table list";
const string value_str = "value";

//select
const string ASTERISK_str = "*";
const string OP_str = "op";
const string comparision_str = "fieldname";
const string field_list_str = "field list";
const string where_str = "where";
const string AND_OR_str = "and / or";

//make_select_table
const int INITIAL_ROW = 0;
const int SELECT_ROW = 1;
const int FIELD_NAME_ROW = 13;
//const int AND_OR_ROW = 14;
const int COMMA_ROW = 14;
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

//get_select_map
const int SELECT_COL =1;
const int FROM_COL = 2;
const int STR_COL =3; // str/value, fieldname or tablename
const int WHERE_COL = 4;
const int OPERATOR_COL = 5;
const int QUOTATION_COL = 6;
const int AND_OR_COL = 7;
const int COMMA_COL = 8;
const int ASTERISK_COL = 9;

//make_print_table
const int PRINT_ROW = 1;
const int PRINT_COL = 1;
const int PRINT_TABLE_ROW = 2;
const int PRINT_TABLE_COL = 2;

//make_drop_table
const int DROP_ROW = 1;
const int DROP_COL = 1;
const int DROP_TABLE_ROW = 2;
const int DROP_TABLE_COL = 2;

//make_load_table
const int LOAD_ROW = 1;
const int LOAD_COL = 1;
const int LOAD_TABLE_ROW = 2;
const int LOAD_TABLE_COL = 2;

//store
const int STORE_ROW = 1;
const int STORE_COL = 1;
const int STORE_TABLE_ROW = 2;
const int STORE_TABLE_COL = 2;

//create
const int CREATE_ROW = 1;
const int CREATE_TABLE_ROW =2;
const int CREATE_FIELDNAME_ROW = 3;
const int CREATE_DATATYPE_ROW = 4;
const int CREATE_COMMA_ROW = 5;

const int CREATE_COL = 1;
const int CREATE_str_COL = 2;
const int CREATE_TABLE_COL = 3;
const int CREATE_COMMA_COL = 4;

const string CREATE_FIELDNAME_str = "fieldname";
const string CREATE_DATATYPE_str = "datatype";

//insert into
const string INSERT_FIELDLIST_str = "field list";
const int INSERT_ROW = 1;
const int INSERT_TABLENAME_ROW = 2;
const int INSERT_VALUE_ROW = 3;
const int INSERT_COMMA_ROW = 4;

const int INSERT_COL = 1;
const int INSERT_STR_COL = 2;
const int INSERT_COMMA_COL = 3;

//const string insert_str = "insert";



//
//const string WHERE_str = "where";
//const string quoto_str = "'";
//const string OR_str = "or";
//const string COMMA_str = ",";
//const string SPACE_str = " ";
//const string FROM_str = "from";



//-----

#endif // CONSTANT_H
