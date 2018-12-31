#include "menu.h"


using namespace std;

void menu::skip_to_int(std::string error_msg){
    if(std::cin.fail()){
        std::cin.clear();
        char ch;
        while(std::cin >> ch){
            if(isdigit(ch)){
                    std::cin.unget();
                    return;
            }
            else{
                 std::cout << error_msg << std::endl;
        }
        }
    }
 else
        std::cout << " No input \n";
}

int menu::get_int(std::string error_msg){
    int n = 0, lock = 1;
   do{
        if(std::cin >> n)
           lock = 0;
        else {
            skip_to_int(error_msg);
        }
    } while(lock);
     return n;
}

int menu::get_int(int low, int high, std::string msg, std::string error_msg){
    std::cout << msg ;
    while(true){
        int n = get_int(error_msg);
        if(low <= n && n <= high)
            return n;
     
    std::cout << "Sorry, " << n << " is " << error_msg << "["<<  low << " : " << high << "] please try again\n";
    }
}

void menu::create_XML_file(){
        printf("Enter record path\n>");
        std::string path{};
        std::cin >> path;
        std::fstream i_file;
        i_file.open(path.c_str(), std::ios::in);
        if(!i_file.is_open()){
           set_file_address(path);
           std::ofstream o_file;
           o_file.open(path.c_str(), std::ios::app);
           o_file.close();
            
            std::cout << "Record loaded." << std::endl;
        }
        else {            
            if(i_file.is_open()){
                printf("Record of this path and name already exist, please select another path or record name.\n");
            }
            
        }
        i_file.close();
        return;
}

void white_space_eater(istream &fin){
    	char ch = fin.get();
    	while(ch == ' ' ){
    		ch = fin.get();
		}
		fin.unget();
}

void menu::load_XML_file( ){
      std::ifstream in_file;
    	istream&    s   = in_file;        
        std::cout << "\nEnter record path\n> ";
        std::string lines{""};
        std::cin >> lines;
        in_file.open(lines.c_str(),fstream::in);
        if (!in_file){
            std::cerr << "\nRecord of this path and name not exist, please select another path or record name." << std::endl;
        }
        else{
        	
			set_Components_ID(0);
			set_Group_ID(0);
			_Components.clear();
			_Groups.clear();
            set_file_address(lines);
            std::cout << "\nRecord loaded." << std::endl;
            int component_state = 0, group_state = 0;// 1: start  0: close
            std::string _ID, _Name, _type, _Member;
            white_space_eater(s);
            while (getline(in_file, lines)) {
                if( XML_analysis_name(lines).compare("Components") == 0 && find_zero_slash(lines)){
                    component_state = 1;
                }
                
                if( XML_analysis_name(lines).compare("Group") == 0 && find_zero_slash(lines)){
                    group_state = 1;     
                }
                
                while(component_state){
                     
                     if(XML_analysis_name(lines).compare("ID") == 0){
                         _ID = XML_analysis_value(lines);
                         break;
                     }
                    else if(XML_analysis_name(lines).compare("Name") == 0){
                         _Name = XML_analysis_value(lines);
                           break;
                     }
                    else if(XML_analysis_name(lines).compare("Type") == 0){
                         _type = XML_analysis_value(lines);
                          break;
                     }
                    else if(lines.compare("</Node>") == 0){
                      if(_type == "C")
                        _Components.push_back( std::tr1::shared_ptr <cube> (new cube(_type, _ID, _Name)) );
                      else if(_type == "P")
                        _Components.push_back( std::tr1::shared_ptr <pyramid> (new pyramid(_type, _ID, _Name)) );
                      else if(_type == "S")
                        _Components.push_back( std::tr1::shared_ptr <sphere> (new sphere(_type, _ID, _Name)) );
                      else if(_type == "L"){
                        _Components.push_back( std::tr1::shared_ptr <line> (new line(_type, _ID, _Name)) );
                      }
                      
                        break;
                    }
                    else if(lines.compare("</Components>") == 0){
                        component_state = 0;
            			set_Components_ID(stoi(_ID));
                         break;
                    }
                    else break;
                    }
                     
                
                    while(group_state){
                    
                     
                    if(XML_analysis_name(lines).compare("ID") == 0){
                         _ID = XML_analysis_value(lines);
                          break;
                     }
                    else if(XML_analysis_name(lines).compare("Name") == 0){
                         _Name = XML_analysis_value(lines);
                          break;
                     }
                    else if(XML_analysis_name(lines).compare("Member") == 0){
                         _Member = XML_analysis_value(lines);
                          break;
                     }
                    else if(lines.compare("</Node>") == 0){//XML_analysis_name(lines).compare("Node") == 0 && !find_zero_slash(lines)
                         _Groups.push_back(Group(_ID, _Name, _Member));
                          break;
                     }
                     else if(lines.compare("</Group>") == 0){
                        group_state = 0;
            			set_Group_ID(stoi(_ID));
                         break;
                     }
                     else break;
                    }
            	white_space_eater(s);
            }
           
           
           // read_XML_Member2Vector
           for(std::vector<Group>::iterator iter = _Groups.begin() ; iter != _Groups.end() ; iter ++){
               iter->read_XML_Member2Vector(iter->Member);
           };
          
        }
        in_file.close();
        return;
        
    }
    
void menu::add_components( int tag ){// Add components
        printf("\nEnter component name\n> ");
        std::string type_to_write = Type_inner(tag);
        char name[100];
        string type_name[] = {
							"Cube",
							"Pyramid",
							"Sphere",
							"Line"
							};
        cin.get();
        cin.getline(name,100);
	          if(type_to_write == "C"){
	            _Components.push_back( std::tr1::shared_ptr <cube> (new cube(type_to_write, to_string(get_Components_ID() + 1), string(name))) );
              }
	          else if(type_to_write == "P"){
	            _Components.push_back( std::tr1::shared_ptr <pyramid> (new pyramid(type_to_write, to_string(get_Components_ID() + 1), string(name))) );
                
              }
	          else if(type_to_write == "S"){
	            _Components.push_back( std::tr1::shared_ptr <sphere> (new sphere(type_to_write, to_string(get_Components_ID() + 1), string(name))) );
                
              }
	          else if(type_to_write == "L"){
	            _Components.push_back( std::tr1::shared_ptr <line> (new line(type_to_write, to_string(get_Components_ID() + 1), string(name))) );
              }
            set_Components_ID( get_Components_ID() + 1 );
            reset_undo_redo();
            undo_add_Component = 1;
        cout << "\nA component of "<< type_name[tag-1] <<" type added, name:  " << name <<","<< "ID : "<< to_string(get_Components_ID() ) <<endl;
        return;
    }
   
void menu::edit(int id_to_edit){
    bool find = 0;
    auto iter =  _Components.begin();
    for( ; iter!= _Components.end() ; ) {
      if((*iter)->get_Components_ID() == to_string(id_to_edit)){
               
        find |= 1;
        break;
      }else{
        ++iter;
      }
    }
        if(!find){
            printf("\nThe component of ID \'%d\' is not exist.\n", id_to_edit);
            return;
        }else{
            int mode = get_int(1, 3, "\nSelect item or return to menu:\n[1]\"Type\"[2]\"Name\"[3]Return to Menu\n> ", "\nOption not exist , please select again\nSelect item or return to menu:\n[1]\"type\"[2]\"Name\"[3]Return to Menu");
            if(mode == 3)
              return;
            else if(mode == 2){
				cout << "\nInput new name:\n> ";
				std::string name;
				cin >> name;
               
                undo_Components.set_Components_Name((*iter)->get_Components_Name());
              
				(*iter)->set_Components_Name(string(name));
                
				cout << "\nName edit success.\n";

                undo_id_to_edit = id_to_edit;
                reset_undo_redo();
                undo_edit_Name = 1;
                
            }
            else{//To change the Type
				auto id = (*iter)->get_Components_ID();
				auto name = (*iter)->get_Components_Name();
                auto type = (*iter)->get_Type();
				int t = get_int(1, 4, "\nSelect new type:\n[1]Cube [2]Pyramid [3]Sphere [4]Line\n> ", "\nThe type option is not exist, select again.\n\nSelect new type:\n[1]Cube [2]Pyramid [3]Sphere [4]Line");
				auto type_to_write = Type_inner(t);
				iter = _Components.erase(iter);
                
				if(type_to_write == "C"){
	            	_Components.insert(iter, std::tr1::shared_ptr <cube> (new cube(type_to_write, id, string(name))) );
                    
                }
	         	else if(type_to_write == "P"){
	            	_Components.insert(iter , std::tr1::shared_ptr <pyramid> (new pyramid(type_to_write, id, string(name))) );
                    
                }
	          	else if(type_to_write == "S"){
	            	_Components.insert(iter , std::tr1::shared_ptr <sphere> (new sphere(type_to_write, id, string(name))) );
                    
                }
	          	else if(type_to_write == "L"){
	            	_Components.insert(iter , std::tr1::shared_ptr <line> (new line(type_to_write, id, string(name))) );
                    
                }
                
                reset_undo_redo();
                undo_edit_Type = 1;
                undo_Components.set_Type(string(type));
                undo_Components.set_Components_ID(string(id));
                undo_Components.set_Components_Name(string(name));
                undo_id_to_edit = id_to_edit;
                
	            cout<<"\nType edit success.\n";
            }
        }

    }
    
void menu::delete_components( ){
        printf("\nSelect component to delete\n>");
        size_t id_to_delete;
        cin >> id_to_delete;
        
		bool find = 0;
		for(auto iter =  _Components.begin() ; iter!= _Components.end() ; ) {
			if((*iter)->get_Components_ID() == to_string(id_to_delete)){
                undo_Components.set_Components_ID((*iter)->get_Components_ID());
                undo_Components.set_Components_Name((*iter)->get_Components_Name());
                undo_Components.set_Type((*iter)->get_Type());
                
				iter = _Components.erase(iter);
				find |= 1;
				break;
			}else{
				++iter;
			}
		}
		
        if(!find){
            printf("\nThe component of ID \'%d\' is not exist.\n", id_to_delete);
           
            
            return;
        }else{
        	
			for(std::vector<Group>::iterator iter = _Groups.begin() ; iter != _Groups.end() ; iter ++){
				bool find = 0;
				for(std::vector<size_t>::iterator it = iter->vector_Member.begin() ; it != iter->vector_Member.end() ; it ++){
					if(*it == id_to_delete){
						iter->vector_Member.erase(it);
						find |= 1;
						break;
					}
				}
				if(find){
					if(iter->vector_Member.size() == 0){
						_Groups.erase(iter);
						if(iter == _Groups.end()){
							printf("break");
							break;
						}
						iter --;
						continue;
					}
					string s;
					for(std::vector<size_t>::iterator it = iter->vector_Member.begin() ; it != iter->vector_Member.end() ; it ++){
						if(it != iter->vector_Member.begin())
							s += ", ";
						s += to_string(*it);
					}
					iter->set_Member(s);
				}
                else if(!find){
                    reset_undo_redo();
                    undo_delete_Component_no_Group = 1;
                }
			}
            printf("\nThe component of ID \'%d\' has been deleted.\n", id_to_delete);        	
		}

        
    }

void menu::add_member_to_group(){
		cout << "\nEnter group ID\n> ";
		string ID;
		cin >> ID;
		
		std::vector<Group>::iterator iter;
		bool find = 0;
		for(iter = _Groups.begin() ; iter != _Groups.end(); iter ++){
			if( iter->get_Group_ID() == ID){
				find ++;
				break;
			}
		}
		
		if(!find){
			cout << "\nThe group of ID \'G" << ID << "\' is not exist. \n" ;
			return ;
		}else{
			while(1){
				cout << "\nEnter components to add\n> " ;
				size_t n;
				vector<size_t> tmp;
				vector<int> contained_v;
				vector<int> not_exist_v;
				int contained = 0;
				int not_exist = 0;
				char ch;
				do{
					cin >> n;
					tmp.push_back(n);
					bool find = 0;
					for(auto it = _Components.begin() ; it != _Components.end() ; it++ ){
						if((*it)->get_Components_ID() == to_string(n)){
							find ++;
							break;
						}
					}
					if(!find){
						not_exist ++ ;
						not_exist_v.push_back(n);
					}else{
						bool find = 0;
						for(std::vector<size_t>::iterator it = iter->vector_Member.begin() ; it != iter->vector_Member.end() ; it++ ){
							if(*it == n){
								find ++;
								break;
							}
						}
						if(find){
							contained ++;
							contained_v.push_back(n);
						}
					}
					white_space_eater(cin);
					ch = cin.get();
				}while( ch != '\n' );
				if(contained && not_exist){
					cout << "\nThe component of ID ";
					for(int i = 0 ; i < contained ; i ++){
						cout << " ¡¥" << contained_v[i] << "¡¦ ";
					}
					if(contained == 1)
						cout << " is ";
					else
						cout << " are ";
					cout << "already contained in the group \'" << iter->get_Group_Name() << "\', and the component of ID ";
					for(int i = 0 ; i < not_exist ; i ++){
						cout << " '" << not_exist_v[i] << "' ";
					}
					if(not_exist == 1)
						cout << " is ";
					else
						cout << " are ";
					cout << "not exist.\n";
				}else if(contained && !not_exist){
					cout << "\nThe component of ID ";
					for(int i = 0 ; i < contained ; i ++){
						cout << " \'" << contained_v[i] << "\' ";
					}
					if(not_exist == 1)
						cout << " is ";
					else
						cout << " are ";
					cout << "already contained in the group \'" << iter->get_Group_Name() << "\'.\n";
					
				}else if(!contained && not_exist){
					
					cout << "\nThe component of ID ";
					for(int i = 0 ; i < not_exist ; i ++){
						cout << " ¡¥" << not_exist_v[i] << "¡¦ ";
					}
					if(not_exist == 1)
						cout << " is ";
					else
						cout << " are ";
					cout << "not exist.\n";
				}else if(!contained && !not_exist){
					while(!tmp.empty()){
						iter->vector_Member.push_back(tmp.back());
						tmp.pop_back();
					}
					sort (iter->vector_Member.begin(), iter->vector_Member.end());
					string s = to_string(iter->vector_Member[0]);
					for(size_t i = 1 ; i < iter->vector_Member.size() ; i++){
						s += ", ";
						s += to_string(iter->vector_Member[i]);
					}
					iter->set_Member(s);
					break;
				}
			}
		}
		
	}

void menu::create_group(){
		cout << "\nEnter group name\n> ";
		Group g;
		char name[100];
		cin.get();
		cin.getline(name,100);
		g.set_Group_Name(string(name));
		g.set_Group_ID(to_string(get_Group_ID()+1));
		set_Group_ID(get_Group_ID()+1);
		bool lock = 1;
		do{
			cout << "\nEnter members\n> ";
			char member[100];
			cin.getline(member,100);
			g.set_Member(string(member));			
			g.read_XML_Member2Vector(string(member));
			bool check = 1;
			int id;
			for(std::vector<size_t>::iterator iter = g.vector_Member.begin() ; iter != g.vector_Member.end() ; iter++){
				bool find = 0;
				for(auto it = _Components.begin() ; it != _Components.end() ; it++){
					if(to_string(*iter) == (*it)->get_Components_ID()){
						find |= 1;
						break;
					}
				}
				if(!find){
					id = *iter;
					check &= 0;
					break;
				}
			}
			if(!check){
				printf("\nThe component of ID \'%d\' is not exist.\n",id);
				g.vector_Member.clear();
			}else{
				lock = 0;
				printf("The new group \'%s\' has been created, ID: %s, members: %s",g.get_Group_Name().c_str(),g.get_Group_ID().c_str(),g.get_Member().c_str());
                reset_undo_redo();
                undo_create_Group = 1;
                
			}
		}while(lock);
		_Groups.push_back(g);
	}
    
void menu::save_XML_file_components( ){
        std::ofstream o_file;
		string path;
		while(1){
			cout << "\nEnter path\n> ";
			cin >> path;
			o_file.open(path.c_str(), std::ios::trunc);
			if(!o_file){
				cout << "\nCannot create file, select other path to save.\n";
				continue;
			}
			break;
    	}
        vector<Components>::iterator c_iter;
        vector<Group>::iterator g_iter;
         o_file << "<GMS>" << std::endl;
          o_file << "<Components>" << std::endl;
    
           
           for(auto c_iter=_Components.begin(); c_iter != _Components.end(); c_iter++){
               
            o_file << "<Node>" << std::endl;
            o_file << "<ID>" << (*c_iter)->ID << "</ID>" << std::endl;
            o_file << "<Name>" << (*c_iter)->Components_Name << "</Name>" << std::endl;
            o_file << "<Type>" << (*c_iter)->Type << "</Type>" << std::endl;
            o_file << "</Node>" << std::endl;
               
           }
    
    o_file << "</Components>" << std::endl;
    o_file << "<Group>" << std::endl;
 
           
           for(g_iter=_Groups.begin(); g_iter < _Groups.end(); g_iter++){
               
            o_file << "<Node>" << std::endl;
            o_file << "<ID>" << g_iter->ID << "</ID>" << std::endl;
            o_file << "<Name>" << g_iter->Group_Name << "</Name>" << std::endl;
            o_file << "<Member>" << g_iter->Member << "</Member>" << std::endl;
            o_file << "</Node>" << std::endl;
               
           }
    
    o_file << "</Group>" << std::endl;
    o_file << "</GMS>" << std::endl;
          
    o_file.close();
    cout << "\nRecord saved.\n";
        
    }
    
std::string menu::Type_inner(int tag){
        std::string  Type_inner{};
          if(tag == 1) {
              Type_inner = 'C';
          }
          else if(tag == 2){
               Type_inner = 'P';
          }
          else if(tag == 3){
               Type_inner = 'S';
          }else if(tag == 4){
               Type_inner = 'L';
          }
          return Type_inner;
    }

void menu::set_file_address(std::string str){
        file_address = str;
    }
  
void menu::Components_display(){
    

      for(auto it = _Components.begin() ; it != _Components.end() ; it++){
        std::cout << "      " << (*it)->Type.substr(0, 1) << "    |    " << (*it)->ID <<"      |   " << (*it)->Components_Name << "   " << std::endl;
      }
      std::cout << std::endl;
    }
    
void menu::Group_display(){
  
    for_each(_Groups.begin(), _Groups.end(),   
        [](Group x) { std::cout << "     G"<< x.ID << "    |    " << x.Group_Name << "     |      "  << x.Member << "   " << std::endl;});
    std::cout << std::endl;
    }

void menu::Display_current_components(){            
            printf("\nComponents:\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("    Type   |    ID     |     Name\n");
            printf("-------------------------------------------------------------------------------\n");
          
            Components_display();
            
            printf("\nGroups:\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("    GID    |    Name    |    Member    |\n");
            printf("-------------------------------------------------------------------------------\n");
            
            Group_display();

            printf("-------------------------------------------------------------------------------\n");
            
        return;
    }
    
void menu::redo(){
    if(redo_add_Component == 1){
            
             if(undo_Components.Type == "C")
	            _Components.push_back( std::tr1::shared_ptr <cube> (new cube(undo_Components.Type, to_string(get_Components_ID() + 1), undo_Components.Components_Name)) );
	          else if(undo_Components.Type == "P")
	            _Components.push_back( std::tr1::shared_ptr <pyramid> (new pyramid(undo_Components.Type, to_string(get_Components_ID() + 1), undo_Components.Components_Name)) );
	          else if(undo_Components.Type == "S")
	            _Components.push_back( std::tr1::shared_ptr <sphere> (new sphere(undo_Components.Type, to_string(get_Components_ID() + 1), undo_Components.Components_Name)) );
	          else if(undo_Components.Type == "L")
	            _Components.push_back( std::tr1::shared_ptr <line> (new line(undo_Components.Type, to_string(get_Components_ID() + 1), undo_Components.Components_Name)) );
                 
            set_Components_ID( get_Components_ID() + 1 );
            undo_add_Component = 1;
        }
        
    if(redo_edit_Type == 1){
            
              auto iter  =  _Components.begin();
            
            for( ; iter!= _Components.end() ; ) {
                if((*iter)->get_Components_ID() == to_string(undo_id_to_edit)){
                    break;
                }
                else{
                    ++iter;
                }
            }       
            
            auto id = (*iter)->get_Components_ID();
            
            auto name = (*iter)->get_Components_Name();
            
            auto type_to_write_undo_Components  = (*iter)->get_Type();
            
            auto type_to_write = undo_Components.get_Type();
            
            iter = _Components.erase(iter);
            
            if(type_to_write == "C"){
	            	_Components.insert(iter, std::tr1::shared_ptr <cube> (new cube(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "P"){
                _Components.insert(iter , std::tr1::shared_ptr <pyramid> (new pyramid(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "S"){
                _Components.insert(iter , std::tr1::shared_ptr <sphere> (new sphere(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "L"){
                _Components.insert(iter , std::tr1::shared_ptr <line> (new line(type_to_write, id, string(name))) );
                    
            }
            
            undo_Components.set_Type(string(type_to_write_undo_Components));
             
             redo_edit_Type = 0;
             undo_edit_Type = 1;
        }
    
    if(redo_edit_Name == 1){
        auto iter  =  _Components.begin();
        
        for( ; iter!= _Components.end() ; ){
            if((*iter)->get_Components_ID() == to_string(undo_id_to_edit)){
                    break;
            }
            else{
                ++iter;
            }
        }

        auto name_current  = undo_Components.get_Components_Name();
        auto name_undo  = (*iter)->get_Components_Name();
        auto type = (*iter)->get_Type();
            
        iter = _Components.erase(iter);
            
        if(type == "C"){
                _Components.insert(iter, std::tr1::shared_ptr <cube> (new cube(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	    else if(type == "P"){
                _Components.insert(iter , std::tr1::shared_ptr <pyramid> (new pyramid(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	    else if(type == "S"){
	           	_Components.insert(iter , std::tr1::shared_ptr <sphere> (new sphere(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	    else if(type == "L"){
                _Components.insert(iter , std::tr1::shared_ptr <line> (new line(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
        
        undo_Components.set_Components_Name(name_undo);
       
        
        redo_edit_Name = 0;
        undo_edit_Name = 1;
        
    }
    
    if(redo_create_Group == 1){
        
        _Groups.push_back(undo_Group);
        set_Group_ID(stoi(undo_Group.get_Group_ID()) + 1 );
        redo_create_Group = 0;
        undo_create_Group = 1;
           
    }
    if(redo_delete_Component_no_Group == 1){
            
            _Components.pop_back();
            set_Components_ID( get_Components_ID() - 1 );
            undo_delete_Component_no_Group = 1;
            redo_delete_Component_no_Group = 0;
        }
}
    
void menu::reset_undo_redo(){
    undo_add_Component = 0;
    undo_delete_Component_no_Group = 0;
    undo_delete_Component_have_Group = 0;
    undo_create_Group = 0;
    undo_edit_Type = 0;
    undo_edit_Name = 0;
    
    redo_add_Component = 0;
    redo_delete_Component_no_Group = 0;
    redo_delete_Component_have_Group = 0;
    redo_create_Group = 0;
    redo_edit_Type = 0;
    redo_edit_Name = 0;
}
    
void menu::undo(){
        if(undo_add_Component == 1){
            std::vector<std::tr1::shared_ptr<Components>>::iterator it = _Components.end() - 1;
            
            undo_Components.ID = ((*it)->ID);
            undo_Components.Components_Name = ((*it)->Components_Name);
            undo_Components.Type =((*it)->Type);
            
            _Components.pop_back();
            set_Components_ID(get_Components_ID() - 1);
            undo_add_Component = 0;
            redo_add_Component = 1;
        }
        
        if(undo_edit_Type == 1){
            auto iter  =  _Components.begin();
            
            for( ; iter!= _Components.end() ; ) {
                if((*iter)->get_Components_ID() == to_string(undo_id_to_edit)){
                    break;
                }
                else{
                    ++iter;
                }
            }       
            
            auto id = (*iter)->get_Components_ID();
            
            auto name = (*iter)->get_Components_Name();
            
            auto type_to_write_undo_Components  = (*iter)->get_Type();
            
            auto type_to_write = undo_Components.get_Type();
            
            iter = _Components.erase(iter);
            
            if(type_to_write == "C"){
	            	_Components.insert(iter, std::tr1::shared_ptr <cube> (new cube(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "P"){
                _Components.insert(iter , std::tr1::shared_ptr <pyramid> (new pyramid(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "S"){
                _Components.insert(iter , std::tr1::shared_ptr <sphere> (new sphere(type_to_write, id, string(name))) );
                    
            }
            else if(type_to_write == "L"){
                _Components.insert(iter , std::tr1::shared_ptr <line> (new line(type_to_write, id, string(name))) );
                    
            }
            
            undo_Components.set_Type(string(type_to_write_undo_Components));

            undo_edit_Type = 0;
            redo_edit_Type = 1;
        }
        
        if(undo_edit_Name == 1){
            
            auto iter  =  _Components.begin();
            
            for( ; iter!= _Components.end() ; ) {
                if((*iter)->get_Components_ID() == to_string(undo_id_to_edit)){
                    break;
                }
                else{
                    ++iter;
                }
            }
            
            auto name_current  = undo_Components.get_Components_Name();
            auto name_undo  = (*iter)->get_Components_Name();
            auto type = (*iter)->get_Type();
            
            iter = _Components.erase(iter);
            
            if(type == "C"){
                _Components.insert(iter, std::tr1::shared_ptr <cube> (new cube(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	        else if(type == "P"){
                _Components.insert(iter , std::tr1::shared_ptr <pyramid> (new pyramid(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	        else if(type == "S"){
	           	_Components.insert(iter , std::tr1::shared_ptr <sphere> (new sphere(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
	        else if(type == "L"){
                _Components.insert(iter , std::tr1::shared_ptr <line> (new line(string(type), to_string(undo_id_to_edit), string(name_current))) );
                    
            }
            			
            
            undo_Components.set_Components_Name(string(name_undo));

            undo_edit_Name = 0;
            redo_edit_Name = 1;
        }
        
        if(undo_create_Group == 1){
            Group temp = _Groups.back();
            
            string id = temp.get_Group_ID();
            string name = temp.get_Group_Name();
            string member = temp.get_Member();
            temp.read_XML_Member2Vector(member);           
            
            undo_Group.set_Group_ID(id);
            undo_Group.set_Group_Name(name);
            undo_Group.set_Member(member);
            undo_Group.read_XML_Member2Vector(member);
            
            _Groups.pop_back();
            set_Group_ID(stoi(id));
            
            undo_create_Group = 0;
            redo_create_Group = 1;
        }
        
        if(undo_delete_Component_no_Group == 1){
            
            string type_to_write = undo_Components.get_Type();
            
            if(type_to_write == "C"){
	            _Components.push_back( std::tr1::shared_ptr <cube> (new cube(type_to_write, to_string(get_Components_ID() ), undo_Components.get_Components_Name())) );
              }
	          else if(type_to_write == "P"){
	            _Components.push_back( std::tr1::shared_ptr <pyramid> (new pyramid(type_to_write, to_string(get_Components_ID() ), undo_Components.get_Components_Name())) );
                
              }
	          else if(type_to_write == "S"){
	            _Components.push_back( std::tr1::shared_ptr <sphere> (new sphere(type_to_write, to_string(get_Components_ID()), undo_Components.get_Components_Name())) );
                
              }
	          else if(type_to_write == "L"){
	            _Components.push_back( std::tr1::shared_ptr <line> (new line(type_to_write, to_string(get_Components_ID() ), undo_Components.get_Components_Name())) );
              }
            
            set_Components_ID( get_Components_ID() + 1 );
            undo_delete_Component_no_Group = 0;
            redo_delete_Component_no_Group = 1;
        }
}

    
void menu::set_Components_ID(std::size_t id){
        Components_ID = id;
    }
    
void menu::set_Group_ID(std::size_t id){
        Group_ID = id;
    }
    

std::string menu::XML_analysis_name(std::string line){
        std::string tag_name{""};
        size_t start_tag_start = line.find("<");
        size_t start_tag_end = line.find(">");
        tag_name = line.substr((start_tag_start + 1), (start_tag_end - start_tag_start - 1));
        return tag_name;
    }
    
std::string menu::XML_analysis_value(std::string line){
       
        size_t start_tag_end = line.find(">");
        size_t end_tag_start = line.find("</");
        std::string tagValue = line.substr((start_tag_end + 1),(end_tag_start - start_tag_end - 1));
        return tagValue;
    }
    
std::string menu::get_file_address(){
        return file_address;
    }
      
std::size_t  menu::get_Components_ID(){
        return Components_ID;
    }
    
std::size_t  menu::get_Group_ID(){
        return Group_ID;
    }
    
bool menu::find_zero_slash(std::string str){
    int count_tag {0};
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '/')
        	count_tag++;
    }
   if(count_tag == 0)
	   return true;
   else
	   return false;
    
}
