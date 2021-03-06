#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class reg_element
{
protected:
    int st_bit;
    int ed_bit;
    int bus_st_bit;
    int bus_ed_bit;
    string attr;
    int def_val;
public:
    int set_st_bit(int st_bit);
    int set_ed_bit(int ed_bit);
    int set_bus_st_bit(int bus_st_bit);
    int set_bus_ed_bit(int bus_ed_bit);
    int set_attr(string attr);
    int set_def_val(int def_val);
    int get_st_bit();
    int get_ed_bit();
    int get_bus_st_bit();
    int get_bus_ed_bit();
    string get_attr();
    int get_def_val();
};

class reg_base_name_item:public reg_element
{
protected:
    int addr;
public:
    int set_addr(int addr);
    int get_addr();
};

class reg_base_addr_item:public reg_element
{
protected:
    string name;
public:
    int set_name(string name);
    string get_name();
};

class reg_base_name
{
protected:
    string name;
    int sub_num;
    reg_base_name_item *item;
public:
    reg_base_name();
    reg_base_name(const reg_base_name &tmp);
    ~reg_base_name();
    reg_base_name &operator=(const reg_base_name &tmp);
    int get_sub_num();
    int set_name(string name);
    string get_name();
    int get_addr(int idx);
    string get_fname(int idx);
    string get_attr(int idx);
    int get_st_bit(int idx);
    int get_ed_bit(int idx);
    int get_bus_st_bit(int idx);
    int get_bus_ed_bit(int idx);
    int get_def_val(int idx);
    int create(string name    ,
               int addr       ,
               int st_bit     ,
               int ed_bit     ,
               int bus_st_bit ,
               int bus_ed_bit ,
               string attr    ,
               int def_val    );
    int append(int addr       ,
               int st_bit     ,
               int ed_bit     ,
               int bus_st_bit ,
               int bus_ed_bit ,
               string attr    ,
               int def_val    );
};

class reg_base_addr
{
protected:
    int addr;
    int sub_num;
    reg_base_addr_item *item;
public:
    reg_base_addr();
    reg_base_addr(const reg_base_addr &tmp);
    ~reg_base_addr();
    reg_base_addr &operator=(const reg_base_addr &tmp);
    int get_sub_num();
    int get_addr();
    string get_name(int idx);
    string get_fname(int idx);
    string get_attr(int idx);
    int get_bus_st_bit(int idx);
    int get_bus_ed_bit(int idx);
    int get_def_val(int idx);
    int create(string name    ,
               int addr       ,
               int st_bit     ,
               int ed_bit     ,
               int bus_st_bit ,
               int bus_ed_bit ,
               string attr    ,
               int def_val    );
    int append(string name    ,
               int st_bit     ,
               int ed_bit     ,
               int bus_st_bit ,
               int bus_ed_bit ,
               string attr    ,
               int def_val    );
};

int reg_element::set_st_bit(int st_bit)
{
    this->st_bit = st_bit;
    return 0;
}

int reg_element::set_ed_bit(int ed_bit)
{
    this->ed_bit = ed_bit;
    return 0;
}

int reg_element::set_bus_st_bit(int bus_st_bit)
{
    this->bus_st_bit = bus_st_bit;
    return 0;
}

int reg_element::set_bus_ed_bit(int bus_ed_bit)
{
    this->bus_ed_bit = bus_ed_bit;
    return 0;
}

int reg_element::set_attr(string attr)
{
    this->attr = attr;
    return 0;
}

int reg_element::set_def_val(int def_val)
{
    this->def_val = def_val;
    return 0;
}


int reg_element::get_st_bit()
{
    return st_bit;
}

int reg_element::get_ed_bit()
{
    return ed_bit;
}

int reg_element::get_bus_st_bit()
{
    return bus_st_bit;
}

int reg_element::get_bus_ed_bit()
{
    return bus_ed_bit;
}

string reg_element::get_attr()
{
    return attr;
}

int reg_element::get_def_val()
{
    return def_val;
}

int reg_base_name_item::set_addr(int addr)
{
    this->addr = addr;
    return 0;
}

int reg_base_name_item::get_addr()
{
    return addr;
}

int reg_base_addr_item::set_name(string name)
{
    this->name = name;
    return 0;
}

string reg_base_addr_item::get_name()
{
    return name;
}

reg_base_name::reg_base_name()
{
    name = "";
    sub_num = 0;
    item = NULL;
}

reg_base_name::reg_base_name(const reg_base_name &tmp)
{
    name = tmp.name;
    sub_num = tmp.sub_num;
    item = new reg_base_name_item[sub_num];
    for (int i = 0; i < sub_num; i++)
    {
        item[i] = tmp.item[i];
    }
}

reg_base_name::~reg_base_name()
{
    if (sub_num != 0)
    {
        delete[] item;
    }
}

reg_base_name &reg_base_name::operator=(const reg_base_name &tmp)
{
    if (this == &tmp)
    {
        return *this;
    }
    if (sub_num != 0)
    {
        delete[] item;
    }
    name = tmp.name;
    sub_num = tmp.sub_num;
    item = new reg_base_name_item[sub_num];
    for (int i = 0; i < sub_num; i++)
    {
        item[i] = tmp.item[i];
    }

    return *this;
}

int reg_base_name::get_sub_num()
{
    return sub_num;
}

int reg_base_name::set_name(string name)
{
    this->name = name;
}

string reg_base_name::get_name()
{
    return name;
}

int reg_base_name::get_addr(int idx)
{
    return item[idx].get_addr();
}

string reg_base_name::get_fname(int idx)
{
    string fname;
    stringstream str;

    if (item[idx].get_st_bit() == item[idx].get_ed_bit())
    {
        return name;
    }

    str.clear();
    str.str("");
    str << name
        << "[" << item[idx].get_ed_bit()
        << ":" << item[idx].get_st_bit()
        << "]";
    str >> fname;

    return fname;
}

string reg_base_name::get_attr(int idx)
{
    return item[idx].get_attr();
}

int reg_base_name::get_st_bit(int idx)
{
    return item[idx].get_st_bit();
}

int reg_base_name::get_ed_bit(int idx)
{
    return item[idx].get_ed_bit();
}

int reg_base_name::get_bus_st_bit(int idx)
{
    return item[idx].get_bus_st_bit();
}

int reg_base_name::get_bus_ed_bit(int idx)
{
    return item[idx].get_bus_ed_bit();
}

int reg_base_name::get_def_val(int idx)
{
    return item[idx].get_def_val();
}


int reg_base_name::create(string name    ,
                          int addr       ,
                          int st_bit     ,
                          int ed_bit     ,
                          int bus_st_bit ,
                          int bus_ed_bit ,
                          string attr    ,
                          int def_val    )
{
    if (sub_num != 0)
    {
        return 1;
    }
    this->name = name;
    this->sub_num = 1;
    this->item = new reg_base_name_item;
    this->item->set_addr(addr);
    this->item->set_st_bit(st_bit);
    this->item->set_ed_bit(ed_bit);
    this->item->set_bus_st_bit(bus_st_bit);
    this->item->set_bus_ed_bit(bus_ed_bit);
    this->item->set_attr(attr);
    this->item->set_def_val(def_val);

    return 0;
}

int reg_base_name::append(int addr       ,
                          int st_bit     ,
                          int ed_bit     ,
                          int bus_st_bit ,
                          int bus_ed_bit ,
                          string attr    ,
                          int def_val    )
{
    int insert_pos;
    reg_base_name_item *item_new;

    insert_pos = sub_num;
    for (int i = 0; i < sub_num; i++)
    {
        if ((item[i].get_addr() == addr) &&
            (item[i].get_bus_st_bit() == (bus_ed_bit+1)) &&
            (item[i].get_st_bit() == (ed_bit+1)) &&
            (item[i].get_attr() == attr))
        {
            // direct merge
            item[i].set_bus_st_bit(bus_st_bit);
            item[i].set_st_bit(st_bit);
            item[i].set_def_val((item[i].get_def_val() << (bus_ed_bit-bus_st_bit+1)) | def_val);
            return 0;
        }
        else if ((item[i].get_addr() == addr) &&
                 (item[i].get_bus_ed_bit() == (bus_st_bit-1)) &&
                 (item[i].get_ed_bit() == (st_bit-1)) &&
                 (item[i].get_attr() == attr))
        {
            // direct merge
            item[i].set_bus_ed_bit(bus_ed_bit);
            item[i].set_ed_bit(ed_bit);
            item[i].set_def_val((def_val << (item[i].get_bus_ed_bit()-item[i].get_bus_st_bit()+1)) | item[i].get_def_val());
            return 0;
        }
        else if (item[i].get_st_bit() > st_bit)
        {
            insert_pos = i;
            break;
        }
    }

    item_new = new reg_base_name_item[sub_num+1];

    for (int i = 0; i < sub_num+1; i++)
    {
        if (i < insert_pos)
        {
            item_new[i] = item[i];
        }
        else if (i == insert_pos)
        {
            int bit_overlap = 0;
            if ((i != 0) &&
                (name != "-") && 
                (item[i-1].get_addr() == addr) && 
                (st_bit <= item[i-1].get_ed_bit()))
            {
                bit_overlap = 1;
            }
            if ((i != sub_num) &&
                (name != "-") && 
                (item[i].get_addr() == addr) &&
                (ed_bit >= item[i].get_st_bit()))
            {
                bit_overlap = 1;
            }
            if (bit_overlap)
            {
                cout << "Register bits overlap! Please check the register list!" << endl;
                return 1;
            }
            item_new[i].set_addr(addr);
            item_new[i].set_st_bit(st_bit);
            item_new[i].set_ed_bit(ed_bit);
            item_new[i].set_bus_st_bit(bus_st_bit);
            item_new[i].set_bus_ed_bit(bus_ed_bit);
            item_new[i].set_attr(attr);
            item_new[i].set_def_val(def_val);
        }
        else
        {
            item_new[i] = item[i-1];
        }
    }

    delete[] item;
    item = item_new;
    sub_num++;

    return 0;
}

reg_base_addr::reg_base_addr()
{
    addr = -1;
    sub_num = 0;
    item = NULL;
}

reg_base_addr::reg_base_addr(const reg_base_addr &tmp)
{
    addr = tmp.addr;
    sub_num = tmp.sub_num;
    item = new reg_base_addr_item[sub_num];
    for (int i = 0; i < sub_num; i++)
    {
        item[i] = tmp.item[i];
    }
}

reg_base_addr::~reg_base_addr()
{
    if (sub_num != 0)
    {
        delete[] item;
    }
}

reg_base_addr &reg_base_addr::operator=(const reg_base_addr &tmp)
{
    if (this == &tmp)
    {
        return *this;
    }
    if (sub_num != 0)
    {
        delete[] item;
    }
    addr = tmp.addr;
    sub_num = tmp.sub_num;
    item = new reg_base_addr_item[sub_num];
    for (int i = 0; i < sub_num; i++)
    {
        item[i] = tmp.item[i];
    }

    return *this;
}

int reg_base_addr::get_sub_num()
{
    return sub_num;
}

int reg_base_addr::get_addr()
{
    return addr;
}

string reg_base_addr::get_name(int idx)
{
    return item[idx].get_name();
}

string reg_base_addr::get_fname(int idx)
{
    string fname;
    stringstream str;

    if (item[idx].get_st_bit() == item[idx].get_ed_bit())
    {
        return item[idx].get_name();
    }

    str.clear();
    str.str("");
    str << item[idx].get_name()
        << "[" << item[idx].get_ed_bit()
        << ":" << item[idx].get_st_bit()
        << "]";
    str >> fname;

    return fname;
}

string reg_base_addr::get_attr(int idx)
{
    return item[idx].get_attr();
}

int reg_base_addr::get_bus_st_bit(int idx)
{
    return item[idx].get_bus_st_bit();
}

int reg_base_addr::get_bus_ed_bit(int idx)
{
    return item[idx].get_bus_ed_bit();
}

int reg_base_addr::get_def_val(int idx)
{
    return item[idx].get_def_val();
}

int reg_base_addr::create(string name    ,
                          int addr       ,
                          int st_bit     ,
                          int ed_bit     ,
                          int bus_st_bit ,
                          int bus_ed_bit ,
                          string attr    ,
                          int def_val    )
{
    if (sub_num != 0)
    {
        return 1;
    }
    this->addr = addr;
    this->sub_num = 1;
    this->item = new reg_base_addr_item;
    this->item->set_name(name);
    this->item->set_st_bit(st_bit);
    this->item->set_ed_bit(ed_bit);
    this->item->set_bus_st_bit(bus_st_bit);
    this->item->set_bus_ed_bit(bus_ed_bit);
    this->item->set_attr(attr);
    this->item->set_def_val(def_val);

    return 0;
}

int reg_base_addr::append(string name    ,
                          int st_bit     ,
                          int ed_bit     ,
                          int bus_st_bit ,
                          int bus_ed_bit ,
                          string attr    ,
                          int def_val    )
{
    int insert_pos;
    reg_base_addr_item *item_new;

    insert_pos = sub_num;
    for (int i = 0; i < sub_num; i++)
    {
        if ((item[i].get_name() == name) &&
            (item[i].get_bus_st_bit() == (bus_ed_bit+1)) &&
            (item[i].get_st_bit() == (ed_bit+1)) &&
            (item[i].get_attr() == attr))
        {
            // direct merge
            item[i].set_bus_st_bit(bus_st_bit);
            item[i].set_st_bit(st_bit);
            item[i].set_def_val((item[i].get_def_val() << (bus_ed_bit-bus_st_bit+1)) | def_val);
            return 0;
        }
        else if ((item[i].get_name() == name) &&
                 (item[i].get_bus_ed_bit() == (bus_st_bit-1)) &&
                 (item[i].get_ed_bit() == (st_bit-1)) &&
                 (item[i].get_attr() == attr))
        {
            // direct merge
            item[i].set_bus_ed_bit(bus_ed_bit);
            item[i].set_ed_bit(ed_bit);
            item[i].set_def_val((def_val << (item[i].get_bus_ed_bit()-item[i].get_bus_st_bit()+1)) | item[i].get_def_val());
            return 0;
        }
        else if (item[i].get_bus_st_bit() > bus_st_bit)
        {
            insert_pos = i;
            break;
        }
    }

    item_new = new reg_base_addr_item[sub_num+1];
  
    for (int i = 0; i < sub_num+1; i++)
    {
        if (i < insert_pos)
        {
            item_new[i] = item[i];
        }
        else if (i == insert_pos)
        {
            int bit_overlap = 0;
            if ((i != 0) &&
                (bus_st_bit <= item[i-1].get_bus_ed_bit()))
            {
                bit_overlap = 1;
            }
            if ((i != sub_num) &&
                (bus_ed_bit >= item[i].get_bus_st_bit()))
            {
                bit_overlap = 1;
            }
            if (bit_overlap)
            {
                cout << "Register bits overlap! Please check the register list!" << endl;
                return 1;
            }
            item_new[i].set_name(name);
            item_new[i].set_st_bit(st_bit);
            item_new[i].set_ed_bit(ed_bit);
            item_new[i].set_bus_st_bit(bus_st_bit);
            item_new[i].set_bus_ed_bit(bus_ed_bit);
            item_new[i].set_attr(attr);
            item_new[i].set_def_val(def_val);
        }
        else
        {
            item_new[i] = item[i-1];
        }
    }

    delete[] item;
    item = item_new;
    sub_num++;

    return 0;
}

extern int parse_addr_val(string reg_addr, int &reg_addr_val);
extern int parse_name_bitrange(string reg_fname, string &reg_name, int &st_bit, int &ed_bit);
extern int parse_busrange(string reg_bits, int &bus_st_bit, int &bus_ed_bit);
extern int parse_defval(string reg_def, int &reg_def_val);

int main(int argc, char *argv[])
{
    int reg_dw = 32;
    int reg_aw = 8;
    string module = "regs";
    string io_clk = "clk";
    string io_rst_n = "rst_n";
    string io_reg_din = "reg_din";
    string io_reg_dout = "reg_dout";
    string io_reg_addr = "reg_addr";
    string io_reg_wr = "reg_wr";
    string nb_assign = "<= `RD";
    ifstream reglist;
    ofstream verilog;

    list<reg_base_name> reg_list_base_name;
    list<reg_base_addr> reg_list_base_addr;

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
        if ((reg_bus_st_bit != reg_bus_ed_bit) &&
            (reg_st_bit == 0) &&
            (reg_ed_bit == 0))
        {
            reg_ed_bit = reg_bus_ed_bit - reg_bus_st_bit;
        }

        int insert_new_reg = 0;
        if(reg_list_base_name.empty())
        {
            insert_new_reg = 1;
        }
        else
        {
            insert_new_reg = 1;
            for (list<reg_base_name>::iterator iter = reg_list_base_name.begin(); iter != reg_list_base_name.end(); ++iter)
            {
                if (iter->get_name() == reg_name)
                {
                    if (iter->get_attr(0) != reg_attr)
                    {
                        cout << "Warning! The attribute of the new register to be appended is different with the exist one" << endl;
                        cout << "  Register Name is \"" << reg_name << "\"" << endl;
                    }
                    iter->append(reg_addr_val   ,
                                 reg_st_bit     ,
                                 reg_ed_bit     ,
                                 reg_bus_st_bit ,
                                 reg_bus_ed_bit ,
                                 reg_attr       ,
                                 reg_def_val    );
                    insert_new_reg = 0;
                    break;
                }
            }
        }
        if (insert_new_reg == 1)
        {
            reg_base_name *new_reg_base_name;
            new_reg_base_name = new reg_base_name;
            if (reg_name != "-")
            {
                new_reg_base_name->create(reg_name       ,
                                          reg_addr_val   ,
                                          reg_st_bit     ,
                                          reg_ed_bit     ,
                                          reg_bus_st_bit ,
                                          reg_bus_ed_bit ,
                                          reg_attr       ,
                                          reg_def_val    );
                reg_list_base_name.push_back(*new_reg_base_name);
            }
        }

        insert_new_reg = 0;
        if(reg_list_base_addr.empty())
        {
            insert_new_reg = 1;
        }
        else
        {
            insert_new_reg = 1;
            for (list<reg_base_addr>::iterator iter = reg_list_base_addr.begin(); iter != reg_list_base_addr.end(); ++iter)
            {
                if (iter->get_addr() == reg_addr_val)
                {
                    iter->append(reg_name       ,
                                 reg_st_bit     ,
                                 reg_ed_bit     ,
                                 reg_bus_st_bit ,
                                 reg_bus_ed_bit ,
                                 reg_attr       ,
                                 reg_def_val    );
                    insert_new_reg = 0;
                    break;
                }
            }
        }
        if (insert_new_reg == 1)
        {
            reg_base_addr *new_reg_base_addr;
            new_reg_base_addr = new reg_base_addr;
            new_reg_base_addr->create(reg_name       ,
                                      reg_addr_val   ,
                                      reg_st_bit     ,
                                      reg_ed_bit     ,
                                      reg_bus_st_bit ,
                                      reg_bus_ed_bit ,
                                      reg_attr       ,
                                      reg_def_val    );
            reg_list_base_addr.push_back(*new_reg_base_addr);
        }
    }
//  for (list<reg_base_name>::iterator iter = reg_list_base_name.begin(); iter != reg_list_base_name.end(); ++iter)
//  {
//      for (int i = 0; i < iter->get_sub_num(); i++)
//      {
//          cout << iter->get_fname(i) << "\t";
//          cout << "0x" << hex << iter->get_addr(i) << dec << "\t";
//          cout << iter->get_attr(i) << "\t";
//          cout << iter->get_bus_ed_bit(i) << ":" << iter->get_bus_st_bit(i) << "\t";
//          cout << endl;
//      }
//  }

//---------------------------------------------------------------
//                    io define
//---------------------------------------------------------------
    verilog << "module " << module << "(" << endl;
    verilog << "  // bus interface" << endl;
    verilog << "  input " << io_clk << "," << endl;
    verilog << "  input " << io_rst_n << "," << endl;
    if (reg_dw > 1)
    {
        verilog << "  input [" << reg_dw-1 << ":0] " << io_reg_din << "," << endl;
        verilog << "  output [" << reg_dw-1 << ":0] " << io_reg_dout << "," << endl;
    }
    else
    {
        verilog << "  input " << io_reg_din << "," << endl;
        verilog << "  output " << io_reg_dout << "," << endl;
    }
    if (reg_aw > 1)
    {
        verilog << "  input [" << reg_aw-1 << ":0] " << io_reg_addr << "," << endl;
    }
    else
    {
        verilog << "  input " << io_reg_addr << "," << endl;
    }
    verilog << "  input " << io_reg_wr << "," << endl;
    verilog << endl;
    verilog << "  // reg interface" << endl;
    for (list<reg_base_name>::iterator iter = reg_list_base_name.begin(); iter != reg_list_base_name.end(); ++iter)
    {
        if (iter->get_name() == "-")
        {
            continue;
        }
        if (iter->get_attr(0) == "RO")
        {
            verilog << "  input ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name();
        }
        else if (iter->get_attr(0) == "W1C")
        {
            verilog << "  input ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name() << "," << endl;
            verilog << "  output ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name() << "_clr";
        }
        else if (iter->get_attr(0) == "WP")
        {
            verilog << "  output ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name();
        }
        else if (iter->get_attr(0) == "RW")
        {
            verilog << "  output ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name();
        }
        else
        {
            cout << "Invalid Register Attribute! Please Check!" << endl;
            cout << "  Register Name is \"" << iter->get_name() << "\"" << endl;
        }
        iter++;
        if (iter != reg_list_base_name.end())
        {
            verilog << ",";
        }
        verilog << endl;
        iter--;
    }

    verilog << "  );" << endl;
    verilog << endl;

//---------------------------------------------------------------
//                    address decode
//---------------------------------------------------------------
    for (list<reg_base_addr>::iterator iter = reg_list_base_addr.begin(); iter != reg_list_base_addr.end(); ++iter)
    {
        verilog << "wire wr_addr_" << hex << iter->get_addr() << " = " << io_reg_wr << " & (" << io_reg_addr << " == " << reg_aw << "'h" << iter->get_addr() << ");" << endl;
    }
    verilog << dec << endl;

//---------------------------------------------------------------
//                    write logic
//---------------------------------------------------------------
    for (list<reg_base_name>::iterator iter = reg_list_base_name.begin(); iter != reg_list_base_name.end(); ++iter)
    {
        if (iter->get_name() == "-")
        {
            continue;
        }
        if ((iter->get_attr(0) == "W1C") ||
            (iter->get_attr(0) == "WP") ||
            (iter->get_attr(0) == "RW"))
        {
            verilog << "reg ";
            if (iter->get_ed_bit(iter->get_sub_num()-1) != iter->get_st_bit(0))
            {
                verilog << "[" << iter->get_ed_bit(iter->get_sub_num()-1) << ":" << iter->get_st_bit(0) << "] ";
            }
            verilog << iter->get_name();
            if (iter->get_attr(0) == "W1C")
            {
                verilog << "_clr";
            }
            verilog << ";" << endl;
        }
        for (int i = 0; i < iter->get_sub_num(); i++)
        {
            if (iter->get_attr(i) == "W1C")
            {
                string tmp_name;
                verilog << "always @(*) begin" << endl;
                tmp_name = iter->get_name();
                iter->set_name(tmp_name+"_clr");
                if (iter->get_ed_bit(i) != iter->get_st_bit(i))
                {
                    verilog << "    " << iter->get_fname(i) << " = {" << (iter->get_ed_bit(i)-iter->get_st_bit(i)+1) << "{wr_addr_" << hex << iter->get_addr(i) << "}} & " << io_reg_din << "[" << iter->get_bus_ed_bit(i) << ":" << iter->get_bus_st_bit(i) << "];" << endl;
                }
                else
                {
                    verilog << "    " << iter->get_fname(i) << " = wr_addr_" << hex << iter->get_addr(i) << dec << " & " << io_reg_din << "[" << iter->get_bus_st_bit(i) << "];" << endl;
                }
                iter->set_name(tmp_name);
                verilog << "end" << endl;
                verilog << endl;
            }
            else if (iter->get_attr(i) == "WP")
            {
                verilog << "always @(posedge " << io_clk << " or negedge " << io_rst_n << ") begin" << endl;
                verilog << "    if (~" << io_rst_n << ")" << endl;
                verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << (iter->get_ed_bit(i)-iter->get_st_bit(i)+1) << "'h" << hex << iter->get_def_val(i) << dec << ";" << endl;
                verilog << "    else if (wr_addr_" << hex << iter->get_addr(i) << dec << ")" << endl;
                if (iter->get_ed_bit(i) != iter->get_st_bit(i))
                {
                    verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << io_reg_din << "[" << iter->get_bus_ed_bit(i) << ":" << iter->get_bus_st_bit(i) << "];" << endl;
                }
                else
                {
                    verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << io_reg_din << "[" << iter->get_bus_ed_bit(i) << "];" << endl;
                }
                verilog << "    else" << endl;
                verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << (iter->get_ed_bit(i)-iter->get_st_bit(i)+1) << "'h" << hex << iter->get_def_val(i) << dec << ";" << endl;
                verilog << "end" << endl;
                verilog << endl;
            }
            else if (iter->get_attr(i) == "RW")
            {
                verilog << "always @(posedge " << io_clk << " or negedge " << io_rst_n << ") begin" << endl;
                verilog << "    if (~" << io_rst_n << ")" << endl;
                verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << (iter->get_ed_bit(i)-iter->get_st_bit(i)+1) << "'h" << hex << iter->get_def_val(i) << dec << ";" << endl;
                verilog << "    else if (wr_addr_" << hex << iter->get_addr(i) << dec << ")" << endl;
                if (iter->get_ed_bit(i) != iter->get_st_bit(i))
                {
                    verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << io_reg_din << "[" << iter->get_bus_ed_bit(i) << ":" << iter->get_bus_st_bit(i) << "];" << endl;
                }
                else
                {
                    verilog << "        " << iter->get_fname(i) << " " << nb_assign << " " << io_reg_din << "[" << iter->get_bus_ed_bit(i) << "];" << endl;
                }
                verilog << "end" << endl;
                verilog << endl;
            }
        }
    }
//---------------------------------------------------------------
//                write logic end
//---------------------------------------------------------------

//---------------------------------------------------------------
//                    read logic
//---------------------------------------------------------------
    verilog << "reg [" << reg_dw-1 << ":0] " << io_reg_dout << ";" << endl;
    verilog << "always @(*) begin" << endl;
    verilog << "    case (" << io_reg_addr << ")" << endl;
    for (list<reg_base_addr>::iterator iter = reg_list_base_addr.begin(); iter != reg_list_base_addr.end(); ++iter)
    {
        verilog << "        " << reg_aw << "'h" << hex << iter->get_addr() << dec << ": " << io_reg_dout << " = {";
        for (int i = iter->get_sub_num()-1; i > 0; i--)
        {
            if (iter->get_name(i) == "-")
            {
                int bit_width;
                bit_width = iter->get_bus_ed_bit(i)-iter->get_bus_st_bit(i)+1;
                verilog << bit_width << "'h" << iter->get_def_val(i) << ", ";
            }
            else if ((iter->get_attr(i) == "RW") ||
                     (iter->get_attr(i) == "RO") ||
                     (iter->get_attr(i) == "W1C"))
            {
                verilog << iter->get_fname(i) << ", ";
            }
            else
            {
                int bit_width;
                bit_width = iter->get_bus_ed_bit(i)-iter->get_bus_st_bit(i)+1;
                verilog << bit_width << "'h" << iter->get_def_val(i) << ", ";
            }
        }
        if (iter->get_name(0) == "-")
        {
            int bit_width;
            bit_width = iter->get_bus_ed_bit(0)-iter->get_bus_st_bit(0)+1;
            verilog << bit_width << "'h" << iter->get_def_val(0);
        }
        else if ((iter->get_attr(0) == "RW") ||
                 (iter->get_attr(0) == "RO") ||
                 (iter->get_attr(0) == "W1C"))
        {
            verilog << iter->get_fname(0);
        }
        else
        {
            int bit_width;
            bit_width = iter->get_bus_ed_bit(0)-iter->get_bus_st_bit(0)+1;
            verilog << bit_width << "'h" << iter->get_def_val(0) << ", ";
        }
        verilog << "};" << endl;
    }
    verilog << "        default: " << io_reg_dout << " = 0;" << endl;
    verilog << "    endcase" << endl;
    verilog << "end" << endl;
    verilog << endl;
//---------------------------------------------------------------
//                read logic end
//---------------------------------------------------------------

    verilog << "endmodule" << endl;

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
