#include <iostream>
#include <string>
#include <vector>
#include "Components.h"
#include "Group.h"
#include "menu.h" 

using namespace std;

int main(){  

    menu n;
    
    int lock_1 = 1;
    int lock_2 = 1;
    int lock_3 = 1;
    
    
    do{
        std::cout << "Welcome\n[1] Graphical Modeling System\n[2] Exit\n>";
        int num = n.get_int(1, 2, " ", "Option not exist , please select again");
        if(num == 1){
            do{
                std::cout << "\nGraphical Modeling System\n[1] Load a XML record\n[2] Save a XML record\n[3] Add component\n[4] Edit\n[5] Delete\n[6] Group\n[7] Redo\n[8] Undo\n[9] Display current table\n[10] Back to Welcome menu\n>";
                int num1 = n.get_int(1, 10, " ", "Option not exist , please select again");
                
                if(num1 == 1){
                    n.load_XML_file( ); 
                }
                else if (num1 == 2){
                    n.save_XML_file_components();
                 
                }
                else if (num1 == 3){
                        std::cout << "\nSelect component type\n[1]Cube [2]Pyramid [3]Sphere [4]Line\n> ";
                        int num4 =  n.get_int(1, 4, "", "Option not exist , please select again");
                        n.add_components( num4 );
                }
                else if (num1 == 4){
                		std::cout << "\nInput component ID:\n> ";
                		int num;
                		cin >> num;
                		n.edit(num);
				}
				else if (num1 == 5){
                  		n.delete_components( );
                }
                else if (num1 == 6){
                   	do{
						cout << "\nGroup\n[1] Create group\n[2] Add member to a group\n[3] Exit\n> ";
                        int num4 =  n.get_int(1, 3, " ", "Option not exist , please select again");
                        if(num4 == 1){
                        	n.create_group();
						}else if(num4 == 2){
							n.add_member_to_group();	
						}else{
							lock_3 = 0;
						}
						
                    }while(lock_3);
                    lock_3 = 1;                       
                   		
                }
                else if (num1 == 7){
                    n.redo();
                }
                else if (num1 == 8){
                    n.undo();
                    
                }
                else if (num1 == 9){
                    n.Display_current_components();
                }
                else if (num1 == 10){
                     lock_2 = 0;
                }
            }while(lock_2);
            
        }
        else if (num == 2){
            lock_1 = 0;
        }
       
    }while(lock_1);
    
    
	return 0;
}

