#include <iostream>
#include <string>
using namespace std;

struct lagu{
    string judul;
    string penyanyi;
};

struct Node{
    lagu data;
    Node* prev;
    Node* next;
};

bool judulTersedia(const Node* head, const string& judul){
    const Node* temp = head;
    while(temp != nullptr){
        if(temp->data.judul == judul){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool tambahAkhir(Node*& head, Node*& tail, const lagu& data){
    if(judulTersedia(head, data.judul)){
        return false;
    }
    
    Node* newNode = new Node{data, nullptr, nullptr};

    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    return true;
}

Node* cariJudul(Node* head, const string & judul){
    Node* temp = head;
    while(temp != nullptr){
        if(temp->data.judul == judul){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool hapusJudul(Node*& head, Node*& tail, const string& judul){
    Node* target = cariJudul(head, judul);
    if(target == nullptr){
        return false;
    }

    if(target == head && target == tail){
        head = nullptr;
        tail = nullptr;
    }else if(target == head){
        head = head->next;
        head->prev = nullptr;
    }else if(target == tail){
        tail = tail->prev;
        tail->next = nullptr;
    }else{
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    
    delete target;
    return true;
}

void tampilMaju(const Node* head){
    if(head == nullptr){
        cout<<"Tidak ada lagu terdaftar \n";
        return;
    }
    
    const Node* temp = head;
    int no = 1;
    cout<<"Daftar lagu (maju) \n";
    while(temp != nullptr){
        cout<<no++<<".Judul :"<<temp->data.judul<<endl;
        cout<<"Penyanyi : "<<temp->data.penyanyi<<endl;
        temp = temp->next;
    }
}

void tampilMundur(const Node* tail){
    if(tail == nullptr){
        cout<<"Tidak ada lagu terdaftar \n";
        return;
    }
    
    const Node* temp = tail;
    int no = 1;
    cout<<"Daftar lagu (mundur) \n";
    while(temp != nullptr){
        cout<<no++<<".Judul :"<<temp->data.judul<<endl;
        cout<<"Penyanyi : "<<temp->data.penyanyi<<endl;
        temp = temp->prev;
    }
}

int jumlahData(const Node* head){
    int count = 0;
    const Node* temp = head;
    while(temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

void clear(Node*& head, Node*& tail){
    Node* temp = head;
    while(temp != nullptr){
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

int main(){
    Node* head = nullptr;
    Node* tail = nullptr;
    int pilihan;

    do{
        system("cls");
        cout<<"1. Tambah Lagu \n";
        cout<<"2. Tampilkan Maju \n";
        cout<<"3. Tampilkan Mundur \n";
        cout<<"4. Cari Lagu \n";
        cout<<"5. Hapus Lagu \n";
        cout<<"6. Jumlah Lagu \n";
        cout<<"7. Keluar \n";
        cout<<"pilihan : "; 
        cin>>pilihan;
        cin.ignore();

        switch(pilihan){
            case 1:{ 
                system("cls");
                lagu n;
                cout<<"Masukkan judul lagu : ";
                getline(cin, n.judul);
                cout<<"Masukkan nama penyanyi : ";
                getline(cin, n.penyanyi);
                cout<<endl;

                if(tambahAkhir(head, tail, n)){
                    cout<<"lagu berhasil ditambahkan \n";
                }else{
                    cout<<"lagu tersebut sudah ada di daftar lagu \n";
                }
                cout<<endl;
                system("pause");
                break;
            }

            case 2:{
                system("cls");
                tampilMaju(head);
                cout<<endl;
                system("pause");
                break;
            }

            case 3:{
                system("cls");
                tampilMundur(tail);
                system("pause");
                cout<<endl;
                break;
            } 

            case 4:{
                system("cls");
                string judul;
                cout<<"Judul lagu yang dicari : ";
                getline(cin, judul);
                
                Node* ketemu = cariJudul(head, judul);
                if(ketemu != nullptr){
                    cout<<"Lagu ditemukan \n";
                    cout<<"Judul    : "<<ketemu->data.judul<<endl;
                    cout<<"Penyanyi : "<<ketemu->data.penyanyi<<endl;
                }else{
                    cout<<"Lagu tidak ditemukan \n";
                }
                cout<<endl;
                system("pause");
                break;
            }
                
            case 5:{
                system("cls");
                string judul;
                cout<<"Judul yang ingin dihapus : ";
                getline(cin, judul);
                
                if(hapusJudul(head, tail, judul)){
                    cout<<"Lagu berhasil dihapus \n";
                }else{
                    cout<<"Lagu tidak ditemukan \n";
                }
                cout<<endl;
                system("pause");
                break;
            }

            case 6:{
                system("cls");
                cout<<"Jumlah total lagu : "<<jumlahData(head)<<endl;
                cout<<endl;
                system("pause");
                break;
            }

            case 7:{
                system("cls");
                cout<<"anda telah keluar \n";
                cout<<endl;
                system("pause");
                break;
            }

            default:{
                cout<<"input tidak valid \n";
                break;
            }
        }
    }while(pilihan != 7);

    clear(head, tail);
    return 0;
}