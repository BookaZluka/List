#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};
void show_list(Node *first) {
    Node *curr=first;
    do {
        cout<<curr->data;
        if(curr->next!=nullptr)
            cout<<",";
        curr=curr->next;
    } while (curr!=nullptr);
    cout<<endl;
}
void delete_element(Node **first,Node **last) {
    Node *current=*first;
    Node *prev=nullptr;
    int delete_element=0;
    cout<<"Введите значение элемента:"<<endl;
    cin>>delete_element;
    if(current->data==delete_element) {
        if(current==(*first) &&(*first)!=(*last)) {
            (*first)=(*first)->next;
            delete current;
            return;
        } else if(current==(*first) &&(*first)==(*last)) {
            (*first)=nullptr;
            (*last)=(*first);
            delete current;
            return;
        }
    }
    prev=current;
    current=current->next;
    while(current!=nullptr) {
        if(current->data==delete_element && current!=(*last)) {
            prev->next=current->next;
            delete current;
            return;
        } else if(current->data==delete_element && current==(*last)) {
            (*last)=prev;
            (*last)->next=nullptr;
            delete current;
            return;
        }
        prev=current;
        current=current->next;
    }
    cout<<"Список не содержит этот элемент!"<<endl;
}
void change_element(Node **first) {
    Node *current=*first;
    int element_position;
    int new_element;
    int count=0;
    cout<<"Введите позицию и значение нового элемента: "<<endl;
    cin>>element_position;
    cin>>new_element;
    while(current!=nullptr) {
        if(count==element_position) {
            current->data=new_element;
            return;
        }
        current=current->next;
        count++;
    }
    cout<<"Список не содержит этот элемент!"<<endl;
}
void find_elements(Node *first) {
    Node *current=first;
    int element=0;
    int count=0;
    bool logic_decision=false;
    cout<<"Введите элемент для поиска:"<<endl;
    cin>>element;
    while(current!=nullptr) {
        if(current->data==element) {
            cout<<count<<" ";
            logic_decision=true;
        }
        count++;
        current=current->next;
    }
    if(logic_decision==false)
        cout<<"Список не содержит этот элемент!"<<endl;
}
void list_sort(Node *first) {
    for(Node *current=first; current!=nullptr; current=current->next) {
        for(Node *current1=first; current1!=nullptr; current1=current1->next) {
            if((current->data)<(current1->data)) {
                swap(current->data,current1->data);
            }
        }
    }
}
void check_numbers(const char *argv,int *&numbers_array,int &numbers_count) {
    for(int i=0; i<strlen(argv); i++) {
        if(argv[i]>='0'&& argv[i]<='9')
            ;
        else numbers_count++;
    }
    numbers_count++;

    numbers_array=new int[numbers_count];

    for(int i=0; i<numbers_count; i++) {
        numbers_array[i]=0;
    }
    int y=0;
    for(int i=0; i<strlen(argv)+1; i++)
        if(argv[i]>='0'&&argv[i]<='9')
            numbers_array[y]=numbers_array[y]*10+argv[i]-'0';
        else y++;
}
void fill_array(int numbers_array[],int argc,char **argv) {
    for(int i=0; i<argc-1; i++)
        numbers_array[i]=atoi(argv[i+1]);
}
void fill_list(int numbers_array[],int numbers_count,Node **first,Node **last) {
    for(int i=0; i<numbers_count; i++) {
        Node *node=new Node {numbers_array[i],nullptr};
        if((*last) == nullptr) {
            (*last)=node;
            (*first)=(*last);
            continue;
        }
        (*last)->next = node;
        (*last) = node;
    }
}
void add_list(Node **first,Node **last) {
    int *numbers_array=nullptr;
    int numbers_count=0;
    string str;
    cout<<"Введите элементы:"<<endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,str);
    check_numbers(str.c_str(),numbers_array,numbers_count);
    fill_list(numbers_array,numbers_count,first,last);
}
void print_menu() {
    cout<<"Выберете операцию:"<<endl;
    cout<<"1: Распечатать список"<<endl;
    cout<<"2: Добавить элементы в список"<<endl;
    cout<<"3: Удалить элемент из списка"<<endl;
    cout<<"4: Найти позиции элементов"<<endl;
    cout<<"5: Заменить элемент на другой"<<endl;
    cout<<"6: Отсортировать элементы списка"<<endl;
    cout<<"7: Завершить работу программы"<<endl;
    cout<<endl;
}
int main(int argc,char *argv[]) {
    int *numbers_array=nullptr;
    int numbers_count=0;
    if(argc == 2) {
        check_numbers(argv[1],numbers_array,numbers_count);
    } else if(argc>2) {
        numbers_count=argc-1;
        numbers_array=new int[numbers_count];
        fill_array(numbers_array,argc,argv);
    }
    Node *last=nullptr;
    Node *first=nullptr;
    fill_list(numbers_array,numbers_count,&first,&last);
    int choice=0;
    string choice_exit;
    do {
        print_menu();
        cin>>choice;
        switch(choice) {
            case 1:
                if(first != nullptr)
                    show_list(first);
                else
                    cerr<<"Список пуст!"<<endl;
                break;
            case 2:
                add_list(&first,&last);
                break;
            case 3:
                if(first!=nullptr)
                    delete_element(&first,&last);
                else
                    cout<<"Список пуст!"<<endl;
                break;
            case 4:
                find_elements(first);
                break;
            case 5:
                change_element(&first);
                break;
            case 6:
                if(first!=nullptr)
                    list_sort(first);
                else
                    cout<<"Список пуст"<<endl;
                break;
            case 7:
                cout<<"Вы ходите выйти из программы? (yes/no)"<<endl;
                cin>>choice_exit;
                if(choice_exit =="yes" || choice_exit == "YES" || choice_exit == "Yes" || choice_exit == "Y" || choice_exit == "y")
                    cout<<"До свидания!"<<endl;
        }
        cout<<endl;
    } while(choice_exit !="yes" && choice_exit != "YES" && choice_exit != "Yes" && choice_exit != "Y" && choice_exit != "y");
    return 0;
}
