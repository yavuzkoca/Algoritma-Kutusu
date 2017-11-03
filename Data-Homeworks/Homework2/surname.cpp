/* @Author
 * Student Name: Gizem Ece Avsar
 * Student ID : 040140303
 * Date: 30/10/2017
 */

//compilation command: g++ -std=c++11 surname.cpp

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "surnamemap.h"
#include "surnamemap.cpp"

using namespace std;


int main(){
    
    surnameMap* new_map;
    new_map = new surnameMap;
    char choose;
    char exit;
    
    bool terminate = false;
    cout << "Welcome to the e-mail address application! This application assigns new e-mail addresses to ITU's new students." << endl;
    cout << "Warning: this program is case sensitive." << endl;
    
    while(!terminate){
        
        cout << endl << endl;
        cout << "Please enter a key: \n C to create the list \n A to add the students automatically from a text file. Please check the file name or path inside the code (line 356 in surnamemap.cpp). (only English characters are accepted) \n M to add students manually \n L to list all the students \n U to update the information of a student \n D to delete a student \n S to delete a surname \n F to keep a copy of the student records in a text file \n E to exit."<< endl;
        cin >> choose;
        
        switch(choose){
                
            case 'A' : case 'a':
                new_map->read_file();
                break;
                
            case 'M' : case 'm':
                new_map->add_from_screen();
                break;
                
            case 'L' : case 'l':
                new_map->list_map_to_screen();
                break;
                
            case 'C' : case 'c':
                new_map->dummy_create();
                break;
                
            case 'D' : case 'd':
                new_map->delete_on_screen(1);
                break;
                
            case 'S' : case 's':
                new_map->delete_on_screen(2);
                break;
                
            case 'U': case 'u':
                new_map->update_on_screen();
                break;
                
            case 'F' : case 'f':
                new_map->list_map_to_file();
                break;
                
            case 'E' : case 'e':
                cout << "Are you sure that you want to exit? y/n" << endl;
                cin >> exit;
                if(exit=='y' || exit=='Y') {
                    new_map->delete_everything();
                    terminate = true;
                }
                
        }
        
    }
    
    return 0;
    
}
