#ifndef GROUP_H
#define GROUP_H
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class Group
{
public:
friend std::ostream &operator<<(std::ostream &os, const Group &c){
     os << c.ID << " " << c.Group_Name << " " << c.Member << std::endl;
     return os;
}
    Group();
    Group(std::string i, std::string g, std::string m);
public:


std::string ID;
std::string Group_Name;
std::string Member;
std::vector<size_t> vector_Member;

void set_Group_ID(std::string i);
void set_Group_Name(std::string Group_Name);
void set_Member(std::string Member);

std::string get_Group_ID();
std::string get_Group_Name();
std::string get_Member();

void read_XML_Member2Vector(std::string m);

};

#endif // GROUP_H
