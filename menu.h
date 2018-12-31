#ifndef MENU_H
#define MENU_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <tr1/memory>
#include "Group.h"
#include "Components.h"
class menu{

public:

    std::string file_address{""};
    size_t Components_ID = 0;
    size_t Group_ID = 0;
    std::vector<std::tr1::shared_ptr<Components>> _Components;
    std::vector<Group> _Groups;
    
    int undo_add_Component{0};
    int undo_delete_Component_no_Group{0};
    int undo_delete_Component_have_Group{0};
    int undo_create_Group{0};
    int undo_edit_Type{0};
    int undo_edit_Name{0};
    
    int redo_add_Component{0};
    int redo_delete_Component_no_Group{0};
    int redo_delete_Component_have_Group{0};
    int redo_create_Group{0};
    int redo_edit_Type{0};
    int redo_edit_Name{0};
    
    
    
    int undo_id_to_edit{0};// To store the undoing of component' ID
    
    Components undo_Components;
    Group undo_Group;


menu() { 
}
~menu() {std::cout << "Good Bye!\n";}


int get_int(std::string error_msg);
int get_int(int low, int high, std::string msg, std::string error_msg);

std::string Type_inner(int tag);
std::string XML_analysis_name(std::string line);
std::string XML_analysis_value(std::string line);
std::string get_file_address();
bool find_zero_slash(std::string str);
size_t  get_Components_ID();
size_t  get_Group_ID();



void skip_to_int(std::string error_msg);
void create_XML_file();
void load_XML_file();
void add_components( int tag );
void delete_components( );
void create_group( );
void add_member_to_group();
void save_XML_file_components( );
void set_file_address(std::string str);
void Display_current_components( );
void set_Components_ID(std::size_t id);
void set_Group_ID(std::size_t id);
void display( );
void Components_display( );
void Group_display( );
void edit(int num);
void reset_undo_redo();//when do different job, we should reset all the state of the undo and redo

void redo();
void undo();


};

#endif // MENU_H
