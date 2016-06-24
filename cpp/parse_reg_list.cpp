#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

extern int parse_addr(string reg_addr);

int main(int argc, char *argv[])
{
    ifstream reglist;
    ofstream verilog;
    string regline;

    string reg_addr;
    string reg_name;
    string reg_bits;
    string reg_def;
    string reg_attr;

    int reg_addr_val;
    int reg_st_bit;
    int reg_ed_bit;
    int reg_bus_st_bit;
    int reg_bus_ed_bit;
    int reg_def_val;

    reglist.open(argv[1]);
    verilog.open(argv[2]);

    getline(reglist, regline);

    while (getline(reglist, regline))
    {
        int start_pos;
        int end_pos;
        string reg_element[5];

        start_pos = 0;
        for (int i = 0; i < 5; i++)
        {
            end_pos = regline.find(",", start_pos);
            reg_element[i] = regline.substr(start_pos, end_pos-start_pos);
            start_pos = end_pos + 1;
        }
        if (reg_element[0] != "")
        {
            reg_addr = reg_element[0];
        }
        reg_name = reg_element[1];
        reg_bits = reg_element[2];
        reg_def  = reg_element[3];
        reg_attr = reg_element[4];

        reg_addr_val = parse_addr(reg_addr);

        cout << "0x" << hex << reg_addr_val << "\t"
             << reg_name << "\t"
             << reg_bits << "\t"
             << reg_def  << "\t"
             << reg_attr << endl;
    }

    reglist.close();
    verilog.close();

    return 0;
}

int parse_addr(string reg_addr)
{
    int reg_addr_val;
    int hex_id_pos;
    int strlen;
    stringstream regstr;

    strlen = reg_addr.length();

    hex_id_pos = reg_addr.find("0x");
    if (hex_id_pos == string::npos)
    {
        hex_id_pos = reg_addr.find("0X");
    }
    if (hex_id_pos == string::npos)
    {
        hex_id_pos = reg_addr.find("'h");
    }
    if (hex_id_pos == string::npos)
    {
        hex_id_pos = reg_addr.find("'H");
    }
    if (hex_id_pos != string::npos)
    {
        reg_addr = reg_addr.substr(hex_id_pos+2, strlen-hex_id_pos-2);
        regstr.str(reg_addr);
        regstr >> hex >> reg_addr_val;
    }
    else
    {
        regstr.str(reg_addr);
        regstr >> reg_addr_val;
    }

    return reg_addr_val;
}
