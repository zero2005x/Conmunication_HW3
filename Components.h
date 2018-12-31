#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <string>
#include <fstream>

class Components{
friend std::ostream &operator<<(std::ostream &os, const Components &c){
     os << c.ID << " " << c.Components_Name << " " << c.Type << std::endl;
     return os;
}

public:


std::string ID;
std::string Components_Name;
std::string Type;

Components(std::string t, std::string i, std::string n);
Components();


std::string set_Components_ID(std::string i);
std::string set_Components_Name(std::string n);
std::string set_Type(std::string t);


std::string get_Components_ID();
std::string get_Components_Name();
std::string get_Type();


};

class cube : public Components
{
public:
	cube(std::string t, std::string i, std::string n) : Components( t,  i,  n){
	};
	
};
class pyramid : public Components
{
public:
	pyramid(std::string t, std::string i, std::string n) : Components( t,  i,  n){
	};
	
};
class line : public Components
{
public:
	line(std::string t, std::string i, std::string n) : Components( t,  i,  n){
	};
	
};
class sphere : public Components
{
public:
	sphere(std::string t, std::string i, std::string n) : Components( t,  i,  n){
	};
	
};
#endif // COMPONENTS_H
