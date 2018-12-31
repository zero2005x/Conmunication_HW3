#include "Components.h"

Components::Components()
{
    ID = "";
    Components_Name= "";
    Type = "";
}

Components::Components(std::string t, std::string i, std::string n):Type{t}, ID{i},Components_Name{n}{}


std::string Components::set_Components_ID(std::string i){
    ID = i;
}
std::string Components::set_Components_Name(std::string n){
    Components_Name = n;
}
std::string Components::set_Type(std::string t){
    Type = t;
}


std::string Components::get_Components_ID(){
    return ID;
}

std::string Components::get_Components_Name(){
    return Components_Name;
}
std::string Components::get_Type(){
    return Type;
}
