#include "Group.h"

Group::Group()
{
    ID = "";
    Group_Name= "";
    Member ="";
}


Group::Group(std::string i, std::string g, std::string m):ID{i},Group_Name{g},Member{m}{}

void Group::set_Group_ID(std::string i){
    ID = i;
    return ;
}

void Group::set_Group_Name(std::string n){
    Group_Name = n;
    return ;
}
void Group::set_Member(std::string t){
    Member = t;
    return ;
}


std::string Group::get_Group_ID(){
    return ID;
}

std::string Group::get_Group_Name(){
    return Group_Name;
}
std::string Group::get_Member(){
    return Member;
}



void Group::read_XML_Member2Vector(std::string m){
    size_t i;
    std::stringstream ss(m);
    
   while(ss >> i){
        vector_Member.push_back(i);
        if(ss.peek() == ',')
            ss.ignore();
    }

}
