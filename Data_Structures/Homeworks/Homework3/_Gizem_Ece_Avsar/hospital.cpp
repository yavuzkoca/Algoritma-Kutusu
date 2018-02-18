/* @Author
 * Student Name: <Gizem Ece AVSAR>
 * Student ID : <040140303>
 * Date: <10.12.2017>
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int RED = 1; //minimum treatment times for particular codes. RED is not used due to the structure of the algorithm. however it is still kept for conventional reasons.
const int YELLOW = 2;
const int GREEN = 3;
int TIME = 0; //the counter for time.

struct patient{
    string code, name;
    int arrival, treatment; //arrival and treatment times.
    patient* next; //queue is going to be kept as a linked list.
    patient(); //default constructor
    void fill_the_information(string, string, int, int); //this function initializes the data of the brand new patient struct. it has similar functionalities with constructors.
};

patient::patient(){ 
    next = nullptr;
    arrival = treatment = 0;
}

void patient::fill_the_information(string n, string c, int a, int t){
    name = n;
    code = c;
    arrival = a;
    treatment = t;
}

struct queue{
    patient* front; //front and...
    patient* back; //...back pointers.
    int number_of_patients;
    queue(); //def. constructor
    ~queue(); //destructor
    void enqueue(patient*); //usual queue methods.
    patient* dequeue();
    bool is_empty();
};

queue::queue(){
    front = back = nullptr;
    number_of_patients = 0;
}

queue::~queue(){
    patient* deleted = front;
    while(front){
        front = front->next;
        delete deleted;
    }
    //cout << "destructor called" << endl;
}

void queue::enqueue(patient* np){
    if(is_empty()){ //if the queue is empty, then both front and back pointers are going to point to the single new comer.
        front = back = np;
    }
    else{ //pushes from the back...
        patient* temp = back;
        temp->next = np;
        back = np;
    }
    number_of_patients++;
}

patient* queue::dequeue(){//...pops from the front.
    if(is_empty()){
        return nullptr;
    }
    else if(number_of_patients==1){ //to be able to handle the back pointer becoming a null pointer if the queue is completely dequeued.
        patient* temp = front;
        front = back = nullptr;
        number_of_patients--;
        temp->next = nullptr;
        return temp;
    }
    else{ //dequeues from the front.
        patient* temp = front;
        front = front->next;
        temp->next = nullptr;
        number_of_patients--;
        return temp;
    }
}

bool queue::is_empty(){
    return (number_of_patients==0);
}

queue *general, *red, *yellow, *green; //queues and the doctor pointer are kept global as a matter of simplicity.
patient* doctor;

void general_queue_filler(){ //file handler
    ifstream file;
    file.open("patientsInfo.txt");
    if(!file.is_open()){ //error
        cerr << "File cannot be opened! Please check the file path or name inside the code." << endl;
        return;
    }
    string line, header;
    getline(file, header); //takes the header first. it is assumed that the input file is going to have a header.
    while(getline(file, line)){
        stringstream ss(line); //initializes the stringstream object.
        patient* new_patient = new patient; //creates a dynamic new patient.
        string name, code;
        int arrival, treatment;
        ss >> name >> arrival >> treatment >> code; //parses the line ignoring the whitespaces.
        new_patient->fill_the_information(name, code, arrival, treatment); //initialized the new patient.
        general->enqueue(new_patient); //general queue holds ALL the patients in the beginning.
    }
    file.close();
}

void general_queue_distributer(){ //then they are distributed to the related queues with respect to the equality between their arrival times and the global time counter. this function is going to be called in every single change of the time.
    if(general->is_empty()) return;
    else{
        while(!general->is_empty() && general->front->arrival == TIME){
            if(general->front->code == "RED") red->enqueue(general->dequeue());
            else if(general->front->code == "YELLOW") yellow->enqueue(general->dequeue());
            else green->enqueue(general->dequeue());
        }
    }
}

inline bool queues_are_empty(){ //returns true if all the queues are empty. (=hospital is empty)
    return red->is_empty() && yellow->is_empty() && green->is_empty() && general->is_empty();
}

void simulation(){
    bool deleted;
    while(!queues_are_empty()){ //while there are patients in the hospital (no matter where they are)
        deleted = false; //this is going to be used to flag the removal of a patient.
        patient* doctor; //this pointer holds the data of the currently taken patient.
        if(!red->is_empty()){ //when red coded patients exist
            doctor = red->dequeue(); //take the first
            cout << ++TIME << ". time slot: " << doctor->name << endl; //give treatment.
            general_queue_distributer(); //time is increased: distribute patients to the colored queues from the general queue.
            doctor->treatment--; //decrease the general treatment time by 1.
            if(doctor->treatment==0) delete doctor; //if the general treatment time became zero, delete the patient. if a patient makes this statement true, then 1 time slot was enough to end his/her general treatment time.
            else{
                doctor->code = "YELLOW"; //if the treatment is not over, change the code and...
                yellow->enqueue(doctor);//...enqueue the patient to the yellow (less important) queue.
            }
        }
        else if(!yellow->is_empty()){ //if the red one is empty, then it's skipped in the loop.
            doctor = yellow->dequeue(); //take the first
            for(int i = 0; i<YELLOW; i++){ //count the time until the minimum treatment time of the yellow code (which is 2).
                cout << ++TIME << ". time slot: " << doctor->name << endl; //give treatment
                general_queue_distributer(); //time is increased: distribute patients to the colored queues from the general queue.
                doctor->treatment--; //decrease the general treatment time by 1.
                if(doctor->treatment==0){//if the general treatment time became zero, delete the patient. if a patient makes this statement true, then 1 or 2 time slots were enough to end his/her general treatment time.
                    delete doctor;
                    deleted = true; //a flag is kept since there's a possibility to reach the deleted pointer later...
                    break;
                }
            }
            if(!deleted){ //...in this condition.
                doctor->code = "GREEN"; //if the treatment is not over, change the code and...
                green->enqueue(doctor);//...enqueue the patient to the green (the least important) queue.
            }
        }
        else if(!green->is_empty()){ //if the red and green ones are empty, they are skipped.
            doctor = green->dequeue();//take the first.
            for(int i = 0; i<GREEN; i++){ //count the time until the minimum treatment time of the green code (which is 3).
                cout << ++TIME << ". time slot: " << doctor->name << endl; //give treatment.
                general_queue_distributer(); //time is increased: distribute patients to the colored queues from the general queue.
                doctor->treatment--; //decrease the general treatment time by 1.
                if(doctor->treatment==0){//if the general treatment time became zero, delete the patient. if a patient makes this statement true, then 1, 2 or 3 time slots were enough to end his/her general treatment time.
                    delete doctor;
                    deleted = true;
                    break;
                }
            }
            if(!deleted) green->enqueue(doctor); //if the treatment is still not over, enqueue this patient to the green code.
            
        }
        else{ //there were no patients at that time in colored queues. but the general queue was not empty. hence, the doctor is vacant until the next new coming patients.
            cout << ++TIME << ". time slot: doctor is vacant" << endl;
            general_queue_distributer();
        }
    }
}

int main(){
    general = new queue; //create new dynamic queues.
    red = new queue;
    yellow = new queue;
    green = new queue;
    general_queue_filler(); //function calls
    general_queue_distributer(); //first distribution is made for T=0.
    simulation(); //hospital simulation
    delete general; //deallocate memory.
    delete red;
    delete yellow;
    delete green;
    return 0;
}
