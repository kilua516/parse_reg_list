#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

extern int parse_addr_val(string reg_addr, int &reg_addr_val);
extern int parse_name_bitrange(string reg_fname, string &reg_name, int &st_bit, int &ed_bit);
extern int parse_busrange(string reg_bits, int &bus_st_bit, int &bus_ed_bit);
extern int parse_defval(string reg_def, int &reg_def_val);

int main(int argc, char *argv[])
{
    ifstream reglist;
    ofstream verilog;
    string regline;

    string reg_addr;
    string reg_fname;
    string reg_bits;
    string reg_def;
    string reg_attr;

    string reg_name;
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
        reg_fname = reg_element[1];
        reg_bits = reg_element[2];
        reg_def  = reg_element[3];
        reg_attr = reg_element[4];

        parse_addr_val(reg_addr, reg_addr_val);
        parse_name_bitrange(reg_fname, reg_name, reg_st_bit, reg_ed_bit);
        parse_busrange(reg_bits, reg_bus_st_bit, reg_bus_ed_bit);
        parse_defval(reg_def, reg_def_val);

        cout << "0x" << hex << reg_addr_val << "\t"
             << reg_name << dec << "[" << reg_ed_bit << ":" << reg_st_bit << "]" << "\t"
             << reg_bus_ed_bit << ":" << reg_bus_st_bit << "\t"
             << "'h" << hex << reg_def_val  << "\t"
             << reg_attr << endl;
    }

    reglist.close();
    verilog.close();

    return 0;
}

int parse_addr_val(string reg_addr, int &reg_addr_val)
{
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

    return 0;
}

int parse_name_bitrange(string reg_fname, string &reg_name, int &st_bit, int &ed_bit)
{
    int pre_bracket_pos;
    int post_bracket_pos;
    int colon_pos;
    stringstream regstr;
    string str;

    pre_bracket_pos = reg_fname.find("[");
    if (pre_bracket_pos == string::npos)
    {
        reg_name = reg_fname;
        st_bit = 0;
        ed_bit = 0;
    }
    else
    {
        post_bracket_pos = reg_fname.find("]");
        colon_pos = reg_fname.find(":");
        reg_name = reg_fname.substr(0, pre_bracket_pos);
        str = reg_fname.substr(pre_bracket_pos+1, colon_pos-pre_bracket_pos);
        regstr.str(str);
        regstr >> ed_bit;
        str = reg_fname.substr(colon_pos+1, post_bracket_pos-colon_pos);
        regstr.clear();
        regstr.str(str);
        regstr >> st_bit;
    }

    return 0;
}

int parse_busrange(string reg_bits, int &bus_st_bit, int &bus_ed_bit)
{
    int colon_pos;
    stringstream regstr;
    string str;

    colon_pos = reg_bits.find(":");

    if (colon_pos == string::npos)
    {
        regstr.str(reg_bits);
        regstr >> bus_st_bit;
        bus_ed_bit = bus_st_bit;
    }
    else
    {
        str = reg_bits.substr(0, colon_pos);
        regstr.str(str);
        regstr >> bus_ed_bit;
        str = reg_bits.substr(colon_pos+1, reg_bits.length()-colon_pos-1);
        regstr.clear();
        regstr.str(str);
        regstr >> bus_st_bit;
    }

    return 0;
}

int parse_defval(string reg_def, int &reg_def_val)
{
    return parse_addr_val(reg_def, reg_def_val);
}
