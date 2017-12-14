#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

struct Number{
    char* number;
    Number* next;
    Number();
};

Number::Number(){
    number = new char[80];
    next = nullptr;
}

struct Node{
    char* name;
    Number* head;
    int number_count;
    Node* right;
    Node* left;
    Node();
    ~Node();
    void add_number(Number*);
    void delete_number();
    void list_numbers();
    void print_numbers();
};

Node::Node(){
    left = right = nullptr;
    head = nullptr;
    name = new char[80];
    number_count = 0;
}

Node::~Node(){
    delete name;
    delete head;
}

void Node::add_number(Number* new_number){
    if(!head){
        head = new_number;
        number_count++;
        return;
    }
    Number* iter = head;
    while(iter->next) iter = iter->next;
    iter->next = new_number;
    number_count++;
}

void Node::print_numbers(){
    if(!head){
        cout << "No numbers exist!" << endl;
        return;
    }
    else{
        int i = 0;
        Number* iter = head;
        for(int i = 0; i<number_count; i++){
            cout << "\t" << i+1 << " " << iter->number << endl;
            iter = iter->next;
        }
    }
}

struct Tree{
    Node* root;
    int node_count;
    Tree();
    void insert_sorted_node(Node*);
    void insert_node(Node*, int);
    void remove_tree(Node*);
    void print_preorder(Node*);
    void print_postorder(Node*);
    void print_inorder(Node*);
    void print_tree_connections(Node*);
    Node* search_tree(char*);
    bool delete_node(char*);
    void update_node(char*);
    int find_num_nodes(Node*);
    int find_depth(Node*);
    int find_leaves(Node*);
    void add_person();
    void add_number();
};

Tree::Tree(){
    root = nullptr;
    node_count = 0;
}

void Tree::insert_sorted_node(Node* n){
    if(!root){
        root = n;
        node_count++;
        return;
    }
    bool added = false;
    Node* iter = root;
    while(iter && !added){
        if(strcmp(n->name, iter->name) < 0){
            if(iter->left) iter = iter->left;
            else{
                iter->left = n;
                added = true;
                node_count++;
            }
        }
        else if(strcmp(n->name, iter->name) > 0){
            if(iter->right) iter = iter->right;
            else{
                iter->right = n;
                added = true;
                node_count++;
            }
        }
        else{
            cout << "Two same names cannot be added!" <<  endl;
        }
    }
}

Node* Tree::search_tree(char* searched){
    Node *iter, *temp;
    temp = root;
    queue<Node*> traversed;
    if(temp){
        if(strcmp(temp->name, searched) == 0) return temp;
        else traversed.push(temp);
    }
    while(!traversed.empty()){
        iter = traversed.front();
        if(iter->left){
            if(strcmp(iter->left->name, searched) == 0) return iter->left;
            else traversed.push(iter->left);
        }
        if(iter->right){
            if(strcmp(iter->right->name, searched) == 0) return iter->right;
            else traversed.push(iter->right);
        }
        traversed.pop();
    }
    return nullptr;
}

//This function has a meaning with the old removal method which is in the
//comments below.

/*Node* copy_data(Node* copied){
    Node* new_node = new Node;
    *new_node = *copied;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}*/

bool Tree::delete_node(char* deleted){
    
    //Asagidaki fonksiyon slaytlardaki remove metodunun BST ozelligini
    //bozacagi dusunulerek yazildi ancak silinecek olan node'un parent
    //nodelarinin duruma gore left veya right node'larını null'a esitleme
    //sorunu handle'lanmadigi icin calismadi. Gelistirmeye acik.
    
    //The code snippet below is designed just in case the remove method in
    //lecture notes may ruin the BS structure of the tree. However, it does
    //not handle the exception where the left or/and right pointers of the
    //parent nodes may need to take null value after
    //removal. It is open for further developments.
    
    /*//////////////////////////////////////////////////////*/
    
    /*Node* found = search_tree(deleted);
    if(!found){
        cout << "Name cannot be found!" << endl;
        return false;
    }
    queue<Node*> kept;
    Node *iter, *temp, *l, *r;
    l = found->left;
    r = found->right;
    delete found;
    if(l){
        iter = l;
        kept.push(iter);
        while(!kept.empty()){
            iter = kept.front();
            if(iter->left) kept.push(iter->left);
            if(iter->right) kept.push(iter->right);
            temp = copy_data(kept.front());
            kept.pop();
            insert_sorted_node(temp);
        }
    }
    if(r){
        iter = r;
        kept.push(iter);
        while(!kept.empty()){
            iter = kept.front();
            if(iter->left) kept.push(iter->left);
            if(iter->right) kept.push(iter->right);
            temp = copy_data(kept.front());
            kept.pop();
            insert_sorted_node(temp);
        }
    }
    return true;*/
    
    /*//////////////////////////////////////////////////////*/
    
    Node* temp = search_tree(deleted);
    
    if(!temp){
        cout << "Name cannot be found!" << endl;
        return false;
    }
    else{
        Node *traverse, *parent;
        traverse = parent = root;
        bool found = false;
        char direction = 'k';
        while(traverse && !found){
            int comparison = strcmp(deleted, traverse->name);
            if(comparison < 0){
                parent = traverse;
                direction = 'l';
                traverse = traverse->left;
            }
            else if(comparison > 0){
                parent = traverse;
                direction = 'r';
                traverse = traverse->right;
            }
            else found = true;
        }
        if(found){
            if(traverse->left == nullptr && traverse->right == nullptr){
                delete traverse;
                switch (direction) {
                    case 'l':
                        parent->left = nullptr;
                        break;
                    case 'r':
                        parent->right = nullptr;
                        break;
                    default:
                        root = nullptr;
                        break;
                }
            }
            else if(traverse->left==nullptr){
                Node* temp = traverse;
                traverse = traverse->right;
                delete temp;
                switch (direction) {
                    case 'l':
                        parent->left = traverse;
                        break;
                    case 'r':
                        parent->right = traverse;
                        break;
                    default:
                        root = traverse;
                        break;
                }
            }
            else if(traverse->right==nullptr){
                Node* temp = traverse;
                traverse = traverse->left;
                delete temp;
                switch (direction) {
                    case 'l':
                        parent->left = traverse;
                        break;
                    case 'r':
                        parent->right = traverse;
                        break;
                    default:
                        root = traverse;
                        break;
                }
            }
            else{
                Node* sub_root = traverse->right;
                while(sub_root->left) sub_root = sub_root->left;
                sub_root->left = traverse->left;
                switch (direction) {
                    case 'l':
                        parent->left = traverse->right;
                        break;
                    case 'r':
                        parent->right = traverse->right;
                        break;
                    default:
                        root = traverse->right;
                        break;
                }
                delete traverse;
            }
        }
    }
    return true;
}

void Tree::update_node(char* updated){
    Node* searched = search_tree(updated);
    if(!searched){
        cout << "Record not found!" << endl;
        return;
    }
    Node* new_node = new Node;
    Number* iter = searched->head;
    for(int i = 0; i<searched->number_count; i++){
        Number* new_number = new Number;
        strcpy(new_number->number, iter->number);
        new_node->add_number(new_number);
        iter = iter->next;
    }
    char* new_name = new char[80];
    cout << "Enter the new name: " << endl;
    cin >> new_name;
    strcpy(new_node->name, new_name);
    delete_node(updated);
    insert_sorted_node(new_node);
}

void Tree::remove_tree(Node* r){
    if(r){
        remove_tree(r->left);
        remove_tree(r->right);
        delete[] r;
    }
    node_count = 0;
}

void Tree::print_inorder(Node* p){
    if(p){
        print_inorder(p->left);
        cout << p->name << endl;
        p->print_numbers();
        print_inorder(p->right);
    }
}

void Tree::print_preorder(Node* p){
    if(p){
        cout << p->name << " ";
        p->print_numbers();
        print_preorder(p->left);
        print_preorder(p->right);
    }
}

void Tree::print_postorder(Node* p){
    if(p){
        print_postorder(p->left);
        print_postorder(p->right);
        cout << p->name << " ";
        p->print_numbers();
    }
}

int Tree::find_num_nodes(Node* n){ return node_count; }

int Tree::find_depth(Node* d){
    if(!d) return 0;
    else{
        int l = find_depth(d->left);
        int r = find_depth(d->right);
        if(r>l) return ++r;
        else return ++l;
    }
}

int Tree::find_leaves(Node* l){
    if(!l) return 0;
    else if(!(l->left || l->right)) return 1;
    else return find_leaves(l->left) + find_leaves(l->right);
}


void Tree::print_tree_connections(Node* p){
    if (!p) return;
    cout << p->name << endl;
    if(p->right){
        cout << p->name << " -> R -> ";
        print_tree_connections(p->right);
    }
    else if(p->left){
        cout << p->name << " -> L -> ";
        print_tree_connections(p->left);
    }
}

void Tree::add_person(){
    char* name = new char[80];
    char* number = new char[80];
    cout << "Enter the name: " << endl;
    cin >> name;
    cout << "Enter the number: " << endl;
    cin >> number;
    Node* new_person = new Node;
    Number* new_number = new Number;
    strcpy(new_number->number, number);
    strcpy(new_person->name, name);
    new_person->add_number(new_number);
    insert_sorted_node(new_person);
}

void Tree::add_number(){
    char* name = new char[80];
    cout << "Enter the name that you want to add numbers of: " << endl;
    cin >> name;
    Node* temp = search_tree(name);
    if(!temp){
        cout << "Record not found!" << endl;
        return;
    }
    char* number = new char[80];
    cout << "Enter the number: " << endl;
    cin >> number;
    Number* new_number = new Number;
    strcpy(new_number->number, number);
    temp->add_number(new_number);
}

Tree* new_tree;


void update_from_screen(){
    char* updated = new char[80];
    cout << "Enter the name that is going to be updated: " << endl;
    cin >> updated;
    new_tree->update_node(updated);
}

void delete_from_screen(){
    char* deleted = new char[80];
    cout << "Enter the name that is going to be deleted: " << endl;
    cin >> deleted;
    new_tree->delete_node(deleted);
}

void search_from_screen(){
    char* searched = new char[80];
    cout << "Enter the name that is going to be searched: " << endl;
    cin >> searched;
    Node* temp = new_tree->search_tree(searched);
    if(!temp){
        cout << "No records found!" << endl;
        return;
    }
    else{
        cout << temp->name << endl;
        temp->print_numbers();
    }
}


int main() {
    new_tree = new Tree;
    cout << "Welcome to the Binary Tree Application!" <<  endl;
    bool terminate = true;
    int choose = 0;
    char term_char;
    while(terminate){
        cout << "\nChoose one: \n1 to add person \n2 to add number to a particular person \n3 to update person \n4 to delete person \n5 search person \n6 to print \n-1 to exit." <<  endl <<  endl;
        cin >> choose;
        switch (choose) {
            case 1:
                new_tree->add_person();
                break;
                
            case 2:
                new_tree->add_number();
                break;
                
            case 3:
                update_from_screen();
                break;
                
            case 4:
                delete_from_screen();
                break;
                
            case 5:
                search_from_screen();
                break;
                
            case 6:
                new_tree->print_inorder(new_tree->root);
                break;
               
                
            case -1:
                cout << "Are you sure? y/n" <<  endl;
                cin >> term_char;
                if(term_char == 'y'){
                    new_tree->remove_tree(new_tree->root);
                    terminate = false;
                    return 0;
                }
                
            default:
                cout << "Invalid choice!" <<  endl;
        }
    }
    
    return 0;
}

