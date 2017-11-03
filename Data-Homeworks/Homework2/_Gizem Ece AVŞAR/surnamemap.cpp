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
#include "surnamenode.h"
#include "studentinfo.h"

using namespace std;

void surnameMap::create_list(){
    
    if(!is_created_before){
        head = nullptr;
        surname_count = 0;
        is_created_before = true;
    }
    
}

void surnameMap::dummy_create(){} //this is a dummy create function to be used in the menu while "create" option is used. since I have already created the list while adding contents, there's no need to create the list explicitly. in addition, creating the list while adding contents is safer.

void surnameMap::add_surname(studentInfo* nsn){
    
    if(!is_created_before) create_list();
    surnameNode* new_surname;
    surnameNode* iter;
    iter = head;
    bool flag = false;
    new_surname = new surnameNode;
    strcpy(new_surname->surname,nsn->surname);
    
    
    if(!head){                                              //if the list is empty.
        
        head = new_surname;
        new_surname->next = new_surname;
        surname_count++;
        return;
        
    }
    
    else{
        
        for(int i=0; i<surname_count; i++){                 //checks if the surname exists.
            if(strcmp(new_surname->surname,iter->surname) == 0)
                flag = true;
            
            iter = iter->next;
        }
        
        
        if(!flag){                                          //if it doesn't exist, adds it.
            
            iter = head;
            
            if(iter->next == iter){                    //if the new comer is going to be the second surname in the list.
                
                if(strcmp(iter->surname, new_surname->surname)>0){
                    
                    iter->next = new_surname;
                    new_surname->next = iter;
                    head = new_surname;
                    surname_count++;
                    return;
                    
                }
                
                else{
                    
                    iter->next = new_surname;
                    new_surname->next = iter;
                    surname_count++;
                    return;
                    
                }
            }
            
            
            if(strcmp(head->surname, new_surname->surname)>0){      //check if it is lower than head.
                
                for(int i = 0; i<surname_count-1; i++)
                    iter = iter->next;
                new_surname->next = head;
                iter->next = new_surname;
                head = new_surname;
                surname_count++;
                return;
                
            }
            
            else{
                
                bool is_added = false;
                iter = head;
                
                for(int i = 0; i<surname_count-1; i++){
                    
                    if(strcmp(new_surname->surname, iter->next->surname)<0){ //new comer is lower than the others
                        
                        new_surname->next = iter->next;
                        iter->next = new_surname;
                        is_added = true;
                        surname_count++;
                        return;
                        
                    }
                    
                    iter = iter->next;
                }
                
                if(!is_added){ //new comer is the highest.
                    
                    new_surname->next = head;
                    iter->next = new_surname;
                    surname_count++;
                    return;
                    
                }
                
            }
            
        }
        
    }
    
}

char* surnameMap::email_generator(char* name, char* surname){
    
    surnameNode* iter;
    iter = head;
    char* new_email = new char[80];
    char* n = new char[80];
    char* sn = new char[80];
    int number_of_chars = 0;
    
    strcpy(n, name);
    strcpy(sn, surname);
    
    
    for(int i = 0; i<surname_count; i++){ //iterating the circular list to find the matching surname node.
        
        if(strcmp(sn, iter->surname)==0) break;
        iter = iter->next;
        
    }
    
    
    studentInfo* iter2 = iter->student_head; //to iterate the surnameInfo list
    
    *sn = tolower(*sn); //changes the letters into lowercase to create mail addresses.
    *n = tolower(*n);
    
    
    if(iter->student_count == 0){ //if there's no student of that surname, first comer takes only his/her surname as the mail address.
        strcpy(new_email, sn);
    }
    
    else{
        
        for(int j = 0; j<=strlen(n); j++){
            
            iter2 = iter->student_head;
            char* temp = new char[80];
            strcpy(temp, sn);
            strncat(temp, n, j); //this is for checking the existing mail addresses wrt their letters one by one. while j is increasing, first j letters of the name is concatenated with the surname...
            
            while(iter2){
                
                if(strcmp(iter2->email, temp)==0) //... and checked if it exists in the list or not. if it does, j is kept in a different int variable to be able to be used while creating a different nickname.
                    number_of_chars = j;
                
                iter2 = iter2->next;
                
            }
            
            delete[] temp; //added after the submission of this hw :(
            
        }
        
        if(number_of_chars<strlen(n))
            strcpy(new_email, strncat(sn, n, number_of_chars+1)); //first j+1 chars of the name is used.
        
        
        
        else if(number_of_chars==strlen(n)){ //if surname+name@itu shaped mail address is taken, the function starts to add numbers from 1 to 9 at the end of the nickname.
            
            string default_email(sn); //concatenating strings with numbers is easier with a string object and its methods since the + operator is overloaded for string concatenating.
            default_email += n;
            int number_of_extends = 0;
            
            for(int i = 1; i<10; i++){
                
                iter2 = iter->student_head;
                
                while(iter2){
                    
                    if(strcmp(iter2->email,(default_email + (char)(i+48)).c_str()) == 0)
                        number_of_extends = i;
                    
                    iter2 = iter2->next;
                    
                }
                
            }
            
            
            if(number_of_extends<50){
                
                string string_to_char(default_email + (char)(number_of_extends+48+1));
                strcpy(new_email, string_to_char.c_str()); //turning back to char pointer with c_str method.
                
            }
            
        }
        
    }
    
    delete[] n;
    delete[] sn;
    
    return new_email;
    
}

void surnameMap::add_student(char* n, char* sn){
    
    studentInfo* new_student;
    new_student = new studentInfo;
    strcpy(new_student->name, n);
    strcpy(new_student->surname, sn);
    add_surname(new_student);
    strcpy(new_student->email, email_generator(n, sn));
    
    surnameNode* iter;
    iter = head;
    
    for(int i = 0; i<surname_count-1; i++){
        
        if(strcmp(sn, iter->surname)==0) break;
        iter = iter->next;
        
    }
    
    if(iter->student_count==0){ //if the list is empty
        
        iter->student_head = new_student;
        iter->student_count++;
        return;
        
    }
    
    
    else{
        
        
        if(strcmp(iter->student_head->email, new_student->email)>0){ //if the new comer should be the head
            
            new_student->next = iter->student_head;
            iter->student_head->prev = new_student;
            iter->student_head = new_student;
            iter->student_count++;
            return;
            
        }
        
        else{
            
            studentInfo* iter2;
            iter2 = iter->student_head;
            bool is_added = false;
            
            for(int i = 0; i<iter->student_count-1; i++){
                
                if(strcmp(new_student->email, iter2->email)<0){ //if the nickname of the new comer is lower than the iterator different from head.
                    
                    new_student->next = iter2->next;
                    iter2->next->prev = new_student;
                    iter2->next = new_student;
                    new_student->prev = iter2;
                    iter->student_count++;
                    is_added = true;
                    return;
                    
                }
                
                iter2 = iter2->next;
                
            }
            
            if(!is_added){
                
                while(iter2->next)   //if it's the lowest, it is added to the end of the doubly linked studentInfo list.
                    iter2 = iter2->next;
                
                iter2->next = new_student;
                new_student->prev = iter2;
                iter->student_count++;
                return;
                
                
            }
            
        }
        
    }
    
}

void surnameMap::list_map_to_screen(){
    
    surnameNode* sur_iter;
    sur_iter = head;
    studentInfo* stu_iter;
    
    if(surname_count==0){
        cerr << "There's no element to list!" << endl;
        return;
    }
    
    else{
        
        for(int i = 0; i<surname_count; i++){
            
            stu_iter = sur_iter->student_head;
            
            cout << sur_iter-> surname << endl;
            
            while(stu_iter){
                
                cout << "\t" << stu_iter->name << " " << stu_iter->surname << " " << stu_iter->email << "@itu.edu.tr" << endl;
                
                stu_iter = stu_iter->next;
                
            }
            
            sur_iter = sur_iter->next;
            
        }
        
    }
    
}


void surnameMap::read_file(){
    
    ifstream file;
    file.open("dataset_wOutTurkishChars.txt");
    string line;
    string name, surname;
    
    if(!file.is_open()) cerr << "File cannot be opened. Please check the file name inside the code." << endl;
    else{
        
        while(getline(file, line)){
            
            stringstream ss;
            ss << line;
            ss >> name >> surname;
            char* new_name = new char[80];
            char* new_surname = new char[80];
            strcpy(new_name, name.c_str());
            strcpy(new_surname, surname.c_str());
            add_student(new_name, new_surname);
            delete[] new_name;
            delete[] new_surname;
            
        }
        
    }
    
    file.close();
    cout << "Successful." << endl;
    
}

void surnameMap::delete_surname(char* deleted_surname){
    
    surnameNode* iter;
    iter = head;
    surnameNode* temp;
    int counter=0;
    
    for(int i = 0; i<surname_count; i++){
        if(strcmp(deleted_surname, iter->surname)==0){
            counter++;
            break;
        }
        iter = iter->next;
    }
    
    if(counter==0){
        cerr << "There's no matching surname in the list." << endl;
        return;
    }
    
    else{
        
        if(iter==head){
            
            if(surname_count==1){
                
                studentInfo* iter2 = iter->student_head;
                
                while(iter2){
                    
                    studentInfo* temp = iter2;
                    iter2 = iter2->next;
                    delete [] temp;
                    
                }
                cout << "All students having the surname '" << deleted_surname << "' are deleted." << endl;
                delete[] head;
                surname_count--;
                cout << "Successful." << endl;
                return;
            }
            
            else{
                
                temp = head;
                
                studentInfo* iter2 = temp->student_head;
                
                while(iter2){
                    
                    studentInfo* temp2 = iter2;
                    iter2 = iter2->next;
                    delete[] temp2;
                    
                }
                cout << "All students having the surname '" << deleted_surname << "' are deleted." << endl;
                head = iter->next;
                for(int i = 0; i<surname_count-1; i++) iter = iter->next;
                iter->next = head;
                delete[] temp;
                surname_count--;
                cout << "Successful." << endl;
                return;
                
            }
            
        }
        
        else{
            
            temp = iter;
            
            studentInfo* iter2 = iter->student_head;
            
            while(iter2){
                
                studentInfo* temp2 = iter2;
                iter2 = iter2->next;
                delete [] temp2;
                
            }
            cout << "All students having the surname '" << deleted_surname << "' are deleted." << endl;
            for(int i = 0; i<surname_count-1; i++) iter = iter->next;
            iter->next = temp->next;
            delete[] temp;
            surname_count--;
            cout << "Successful." << endl;
            return;
            
            
        }
        
    }
    
}

void surnameMap::delete_student(char* deleted_surname, char* deleted_email){
    
    surnameNode* iter;
    iter = head;
    int counter = 0;
    
    for(int i = 0; i<surname_count; i++){
        if(strcmp(deleted_surname, iter->surname)==0){
            counter++;
            break;
        }
        
        iter = iter->next;
    }
    
    if(counter==0){
        cerr << "There's no matching surname in the list." << endl;
        return;
    }
    
    else{
        
        studentInfo* iter2;
        iter2 = iter->student_head;
        counter = 0;
        while(iter2){
            if(strcmp(deleted_email, iter2->email)==0){
                counter++;
                break;
            }
            iter2 = iter2->next;
        }
        
        if(counter==0){
            cerr << "There's no matching e-mail in the list." << endl;
            return;
        }
        
        else{
            
            if(iter2==iter->student_head){
                
                if(iter->student_count==1){
                    
                    iter->student_count--;
                    cout << "Student having the e-mail '" << deleted_email << "@itu.edu.tr' is deleted." << endl;
                    if(iter->student_count == 0) delete_surname(deleted_surname);
                    return;
                }
                
                else{
                    
                    iter->student_head = iter->student_head->next;
                    delete[] iter2;
                    iter->student_count--;
                    cout << "Student having the e-mail '" << deleted_email << "@itu.edu.tr' is deleted." << endl;
                    return;
                    
                }
                
            }
            
            else{
                
				if (iter2->next){
					iter2->prev->next = iter2->next;
					iter2->next->prev = iter2->prev;
					delete[] iter2;
					iter->student_count--;
					cout << "Student having the e-mail '" << deleted_email << "@itu.edu.tr' is deleted." << endl;
					return;
				}

				else{ //deleting the last element of the doubly linked list
					iter2->prev->next = nullptr;
					iter2->prev = nullptr;
					delete[] iter2;
					iter->student_count--;
					cout << "Student having the e-mail '" << deleted_email << "@itu.edu.tr' is deleted." << endl;
					return;

				}
                
            }
            
        }
        
    }
    
}

void surnameMap::update_student(char* updated_name, char* updated_surname){
    
    surnameNode* iter;
    iter = head;
    int counter = 0;
    
    for(int i = 0; i<surname_count; i++){
        if(strcmp(updated_surname, iter->surname)==0){
            counter++;
            break;
        }
        
        iter = iter->next;
    }
    
    if(counter==0){
        cerr << "There's no matching surname in the list." << endl;
        return;
    }
    
    else{
        
        studentInfo* iter2;
        iter2 = iter->student_head;
        counter = 0;
        while(iter2){
            if(strcmp(updated_name, iter2->name)==0){
                counter++;
                break;
            }
            iter2 = iter2->next;
        }
        
        if(counter==0){
            cerr << "There's no matching name in the list." << endl;
            return;
        }
        
        else{
            
            iter2 = iter->student_head;
            counter = 0;
            studentInfo* first_seen = nullptr;
            int i = 0;
            
            while(iter2){
                if(strcmp(updated_name, iter2->name)==0){
                    if(i==0) first_seen = iter2;
                    cout << i+1 << ". " << iter2->name << " " << iter2->surname << " " << iter2->email << "@itu.edu.tr" << endl;
                    i++;
                }
                iter2 = iter2->next;
            }
            
            cout << "Enter the index of the person that you want to update." << endl;
            int index = 0;
            cin >> index;
            
            if(index>i){
                
                cerr << "Input index is greater than the existing number of students named " << updated_name << "! Please try again." << endl;
                update_on_screen();
                
            }
            
            for(int i = 0; i<index-1; i++) first_seen = first_seen->next;
            
            char* new_name = new char[80];
            char* new_surname = new char[80];
            
            cout << "Enter the new name: " << endl;
            cin >> new_name;
            
            cout << "Enter the new surname: " << endl;
            cin >> new_surname;
            
            delete_student(first_seen->surname, first_seen->email);
            add_student(new_name, new_surname);
            cout << "Student who has the name " << new_name << " and the surname " << new_surname << " has been added." << endl;
            return;
        }
        
    }
    
}

void surnameMap::list_map_to_file(){
    
    surnameNode* sur_iter;
    sur_iter = head;
    studentInfo* stu_iter;
    ofstream list_file;
    list_file.open("last_surname_map.txt");
    if(!list_file){
        cerr << "Output file cannot be opened." << endl;
        return;
    }
    
    else{
        
        if(surname_count==0){
            list_file << "There's no element to list!" << endl;
            return;
        }
        
        else{
            
            for(int i = 0; i<surname_count; i++){
                
                stu_iter = sur_iter->student_head;
                
                list_file << sur_iter-> surname << endl;
                
                while(stu_iter){
                    
                    list_file << "\t" << stu_iter->name << " " << stu_iter->surname << " " << stu_iter->email << "@itu.edu.tr" << endl;
                    
                    stu_iter = stu_iter->next;
                    
                }
                
                sur_iter = sur_iter->next;
                
            }
            
        }
        
    }
    
    cout << "Successful." << endl;
    
}

void surnameMap::delete_on_screen(int choice){
    
    char* deleted_surname = new char[80];
    char* deleted_mail = new char[80];
    
    if(choice==1){
        
        cout << "Enter the surname of the student that you want to delete." << endl;
        cin >> deleted_surname;
        cout << "Enter ONLY the nickname part of the mail address of this student." << endl;
        cin >> deleted_mail;
        delete_student(deleted_surname, deleted_mail);
        delete[] deleted_surname;
        delete[] deleted_mail;
        return;
        
    }
    
    if(choice==2){
        cout << "Enter the surname that you want to delete all the students of." << endl;
        cin >> deleted_surname;
        delete_surname(deleted_surname);
        delete[] deleted_surname;
        delete[] deleted_mail;
        return;
    }
    
}

void surnameMap::update_on_screen(){
    
    char* u_name = new char[80];
    char* u_surname = new char[80];
    
    cout << "Enter the name of the student that you want to update the information of." << endl;
    cin >> u_name;
    cout << "Enter the surname of the student that you want to update the information of." << endl;
    cin >> u_surname;
    
    update_student(u_name, u_surname);
    
    delete[] u_name;
    delete[] u_surname;
    
    return;
    
}

void surnameMap::add_from_screen(){
    
    char* n_name = new char[80];
    char* n_surname = new char[80];
    
    cout << "Enter the name of the student that you want to add the information of." << endl;
    cin >> n_name;
    cout << "Enter the surname of the student that you want to add the information of." << endl;
    cin >> n_surname;
    
    add_student(n_name, n_surname);
    
    delete[] n_name;
    delete[] n_surname;
    
    cout << "Successful." << endl;
    
    return;
    
}

void surnameMap::delete_everything(){
    
    surnameNode* iter;
    iter = head;
    int bound = surname_count;
    char* temp = new char[80];
    
    for(int i = 0; i<bound; i++){
        strcpy(temp, iter->surname);
        iter = iter->next;
        delete_surname(temp);
    }
    
}
