#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <cstring>
using namespace std;

struct cont{
    char username[200],parola[200];
};

struct biblioteca{
    char titlu[200],autor[200],editura[200];
    int anpublic;
    long long codISBN;
};

int k=0,nr_persoane,nr_carti,n1,n2;
char c,a[200],b[200];
cont utilizator[200];
biblioteca carte[200],carte2[200],aux;

HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

void radiere_spatii(char s[200]){
    char s1[200]="";
    char *p;
    int ok=0;
    p=strtok(s," ");
    while(p!=NULL){
        strcat(s1,p);
        p=strtok(NULL," ");
        ok++;
    }
    s[strlen(s1)]='\0';
    for(int k=0;k<strlen(s1);k++)
        s[k]=s1[k];
    return;
}

void litere_mici(char s[200]){
    for(int i=0;i<strlen(s);i++){
        if(s[i]>='A' && s[i]<='Z')
            s[i]=s[i]+'a'-'A';
    }
    return;
}

void citire(cont utilizator[200],int &nr_persoane){
    ifstream f1("Utilizatori.txt");
    int k=0;
    while(!f1.eof()){
        k++;
        f1.getline(utilizator[k].username,22);
        f1.getline(utilizator[k].parola,22);
    }
    nr_persoane=k;
    f1.close();
    return;
}

void adugare_ut(int &nr_persoane,cont utilizator[200]){
    for(int i=1;i<=75;i++)
        cout<<"~";
    cout<<endl;
    nr_persoane++;
    SetConsoleTextAttribute(color,14);
    cout<<"Introduce-ti numele si parola pe care doriti sa le aveti"<<endl<<endl;
    SetConsoleTextAttribute(color,228);
    cout<<"Username:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin>>utilizator[nr_persoane].username;
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"Parola:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin>>utilizator[nr_persoane].parola;
    for(int i=1;i<nr_persoane;i++)
        if(strcmp(utilizator[nr_persoane].username,utilizator[i].username)==0){
            SetConsoleTextAttribute(color,78);
            cout<<endl<<"Va rugam alegeti alt nume deoarece acesta este folosit de un alt utilizator"<<endl;
            SetConsoleTextAttribute(color,14);
            nr_persoane--;
            for(int i=1;i<=75;i++)
                cout<<"~";
            cout<<endl;
            return;
        }
    cout<<endl<<"Contul a fost creat cu success!"<<endl;
    for(int i=1;i<=75;i++)
        cout<<"~";
    cout<<endl;
    return;
}

void citire_carti(biblioteca carte[200],int &nr_carti){
    ifstream f2("Carti.txt");
    f2>>nr_carti;
    f2.get();
    for(int k=1;k<=nr_carti;k++){
        f2.getline(carte[k].titlu,200);
        f2.getline(carte[k].autor,200);
        f2.getline(carte[k].editura,200);
        f2>>carte[k].anpublic;
        f2>>carte[k].codISBN;
        f2.get();
    }
    f2.close();
    return;
}

void afisare_generica(biblioteca carte[200],int nr_carti,int k,int ok){
    int i,spatiere=30;
    SetConsoleTextAttribute(color,ok);
    cout<<endl<<carte[k].titlu;
    for(i=1;i<=spatiere-strlen(carte[k].titlu);i++)
        cout<<".";
    cout<<carte[k].autor;
    for(i=1;i<=spatiere-strlen(carte[k].autor);i++)
        cout<<".";
    cout<<carte[k].editura;
    for(i=1;i<=spatiere-strlen(carte[k].editura);i++)
        cout<<".";
    cout<<carte[k].anpublic;
    SetConsoleTextAttribute(color,14);
    cout<<endl;
    return;
}

void afisare_carti(biblioteca carte[200], int nr_carti){
    int i=1,spatiere=25;
    system("CLS");
    SetConsoleTextAttribute(color,176);
    cout<<"Titlu";
    for(i=1;i<=spatiere-strlen("Titlu")+1;i++)
            cout<<" ";
    cout<<"Autor";
    for(i=1;i<=spatiere-strlen("Autor")+1;i++)
            cout<<" ";
    cout<<"Editura";
    for(i=1;i<=spatiere-strlen("Editura")+1;i++)
            cout<<" ";
    cout<<"An publicare";
    for(i=1;i<=spatiere-strlen("An punlicare")+1;i++)
            cout<<" ";
    cout<<"Cod ISBN     "<<endl;
    SetConsoleTextAttribute(color,11);
    for(i=1;i<=117;i++){
        cout<<"~";
    }
    cout<<endl;
    SetConsoleTextAttribute(color,14);
    int ok=0;
    for(int k=1;k<=nr_carti;k++){
        if(ok==0){
            SetConsoleTextAttribute(color,11);
            ok=1;
        }
        else{
            SetConsoleTextAttribute(color,176);
            ok=0;
        }
        cout<<endl<<carte[k].titlu;
        for(i=1;i<=spatiere-strlen(carte[k].titlu);i++)
            cout<<" ";
        cout<<"|";
        cout<<carte[k].autor;
        for(i=1;i<=spatiere-strlen(carte[k].autor);i++)
            cout<<" ";
        cout<<"|";
        cout<<carte[k].editura;
        for(i=1;i<=spatiere-strlen(carte[k].editura);i++)
            cout<<" ";
        cout<<"|";
        cout<<carte[k].anpublic;
        for(i=1;i<=spatiere-4;i++)
            cout<<" ";
        cout<<"|";
        cout<<carte[k].codISBN;
    }
    SetConsoleTextAttribute(color,11);
    return;
}

void afisare_cronologica(biblioteca carte[200],int nr_carti){
    biblioteca aux;
    int ok=0,i;
    do{
        ok=0;
        for(int k=1;k<nr_carti;k++)
            if(carte[k].anpublic>carte[k+1].anpublic){
                aux=carte[k];
                carte[k]=carte[k+1];
                carte[k+1]=aux;
                ok=1;
            }
    }while(ok!=0);
    for(k=1;k<=nr_carti;k++)
        afisare_generica(carte,nr_carti,k,144);
    return;
}

void sortare_alfabetica(biblioteca carte[200],int nr_carti){
    biblioteca aux;
    for(int i=1;i<nr_carti;i++)
        for(int j=i;j<=nr_carti;j++)
            if(strcmp(carte[i].titlu,carte[j].titlu)==1){
                aux=carte[i];
                carte[i]=carte[j];
                carte[j]=aux;
            }
    return;
}

void adaugare_carte(biblioteca carte[200],biblioteca carte2[200],int &nr_carti){
    nr_carti++;
    cin.get();
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"Titlu:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin.getline(carte[nr_carti].titlu,200);
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"Autor:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin.getline(carte[nr_carti].autor,200);
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"Editura:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin.getline(carte[nr_carti].editura,200);
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"An Publicare:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin>>carte[nr_carti].anpublic;
    cin.get();
    SetConsoleTextAttribute(color,228);
    cout<<endl<<"Cod ISBN:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin>>carte[nr_carti].codISBN;
    int i=1;
    while(i<nr_carti){
        if(carte[i].codISBN==carte[nr_carti].codISBN){
            nr_carti--;
            SetConsoleTextAttribute(color,228);
            cout<<"Exista in biblioteca o carte cu acest cod ISBN"<<endl;
            afisare_generica(carte,nr_carti,i,206);
            return;
        }
        i++;
    }
    carte2[nr_carti]=carte[nr_carti];
    radiere_spatii(carte2[nr_carti].titlu);
    radiere_spatii(carte2[nr_carti].autor);
    radiere_spatii(carte2[nr_carti].editura);
    litere_mici(carte2[nr_carti].titlu);
    litere_mici(carte2[nr_carti].autor);
    litere_mici(carte2[nr_carti].editura);
    cin.get();
    return;
}

void cautare_titlu(biblioteca carte2[200],biblioteca carte[200],int nr_carti){
    SetConsoleTextAttribute(color,228);
    cout<<"\nNume carte:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    char p[100];
    cin.get();
    cin.getline(p,100);
    litere_mici(p);
    radiere_spatii(p);
    int gasit=0;
    for(int k=1;k<=nr_carti;k++){
        if(strstr(carte2[k].titlu,p)!=NULL){
            gasit++;
            afisare_generica(carte,nr_carti,k,32);
        }
    }
    cout<<endl<<"Au fost gasite ";
    SetConsoleTextAttribute(color,228);
    cout<<gasit;
    SetConsoleTextAttribute(color,14);
    cout<<" rezultate"<<endl;
    return;
}

void cautare_autor(biblioteca carte2[200],biblioteca carte[200],int nr_carti){
    SetConsoleTextAttribute(color,228);
    cout<<"\nNume autor:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    char p[100];
    cin.get();
    cin.getline(p,100);
    radiere_spatii(p);
    litere_mici(p);
    int gasit=0;
    for(int k=1;k<=nr_carti;k++){
        if(strstr(carte2[k].autor,p)!=NULL){
            gasit++;
            afisare_generica(carte,nr_carti,k,160);
        }
    }
    cout<<endl<<"Au fost gasite ";
    SetConsoleTextAttribute(color,228);
    cout<<gasit;
    SetConsoleTextAttribute(color,14);
    cout<<" rezultate"<<endl;
    return;
}

void cautare_editura(biblioteca carte2[200],biblioteca carte[200],int nr_carti){
    SetConsoleTextAttribute(color,228);
    cout<<"\nNume Editura:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    char p[100];
    cin.get();
    cin.getline(p,100);
    radiere_spatii(p);
    litere_mici(p);
    int gasit=0;
    for(int k=1;k<=nr_carti;k++){
        if(strstr(carte2[k].editura,p)!=NULL){
            gasit++;
            afisare_generica(carte,nr_carti,k,95);
        }
    }
    cout<<endl<<"Au fost gasite ";
    SetConsoleTextAttribute(color,228);
    cout<<gasit;
    SetConsoleTextAttribute(color,14);
    cout<<" rezultate"<<endl;
    return;
}

void design_titlu(){
    SetConsoleTextAttribute(color,228);
    for(int i=1;i<=74;i++)
        cout<<" ";
    cout<<endl;
    cout<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"          @                 @                                           ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"  #####   #  #####   #      #   ####   #######  ######   #####   ####   ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"  #    #  #  #    #  #      #  #    #     #     #       #       #    #  ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"  #####   #  #####   #      #  #    #     #     ######  #       ######  ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"  #    #  #  #    #  #      #  #    #     #     #       #       #    #  ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    cout<<"  #####   #  #####   #####  #   ####      #     ######   #####  #    #  ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl<<" ";
    SetConsoleTextAttribute(color,78);
    for(int i=1;i<=72;i++)
        cout<<" ";
    SetConsoleTextAttribute(color,228);
    cout<<" "<<endl;
    SetConsoleTextAttribute(color,228);
    for(int i=1;i<=74;i++)
        cout<<" ";
    cout<<endl<<endl;
    return;
}

void meniu_principal(char y[200],int z,int k,int ok,int ok1,int ok2){
    SetConsoleTextAttribute(color,11);
    for(int i=1;i<=ok1;i++)
        cout<<" ";
    SetConsoleTextAttribute(color,ok);
    cout<<y;
    SetConsoleTextAttribute(color,ok2);
    for(int i=1;i<=z-strlen(y)-1;i++)
        cout<<".";
    cout<<k<<endl;
    return;
}

void scriere_in_fisier_carti(biblioteca carte[200],int nr_carti){
    ofstream g2("Carti.txt");
    g2<<nr_carti;
    for(k=1;k<=nr_carti;k++){
        g2<<endl<<carte[k].titlu;
        g2<<endl<<carte[k].autor;
        g2<<endl<<carte[k].editura;
        g2<<endl<<carte[k].anpublic;
        g2<<endl<<carte[k].codISBN;
    }
    g2.close();
    return;
}

void stergere_carte(biblioteca carte[200],biblioteca carte2[200],int &nr_carti){
    long long z;
    int i=1;
    SetConsoleTextAttribute(color,228);
    cout<<"Cod ISBN:";
    SetConsoleTextAttribute(color,14);
    cout<<" ";
    cin>>z;
    while(z!=carte[i].codISBN && i<=nr_carti){
        i++;
    }
    if(i==nr_carti+1){
        SetConsoleTextAttribute(color,78);
        cout<<endl<<"Nu exista carte cu codul ISBN introdus";
        SetConsoleTextAttribute(color,14);
        cout<<endl;
    }
    else{
        cout<<endl<<"Aceasta carte a fost stearsa:";
        afisare_generica(carte,nr_carti,i,78);
        while(i<nr_carti){
            carte[i]=carte[i+1];
            carte2[i]=carte2[i+1];
            i++;
        }
        nr_carti--;
    }
    return;
}

void ajutor(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"\n-----------------------------------------------------Ajutor-------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),228);
    ifstream f("Help.txt");
    char rand[256];
    while(f.getline(rand,256))
        cout<<rand<<'\n';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"------------------------------------------------------------------------------------------------------------------------";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    f.close();
}


int main(){
    citire(utilizator,nr_persoane);
    citire_carti(carte,nr_carti);
    do{
        for(int i=1;i<=nr_carti;i++){
            carte2[i]=carte[i];
            radiere_spatii(carte2[i].titlu);
            radiere_spatii(carte2[i].autor);
            radiere_spatii(carte2[i].editura);
        }
        for(int i=1;i<=nr_carti;i++){
            litere_mici(carte2[i].titlu);
            litere_mici(carte2[i].autor);
            litere_mici(carte2[i].editura);
        }
        design_titlu();

        SetConsoleTextAttribute(color,14);
        char x[200]="APLICATIE PERMIS DE BIBLIOTECA";
        int z = strlen(x);
        for(int i=1;i<=36-z/2;i++)
            cout<<" ";
        SetConsoleTextAttribute(color,228);
        cout<<x<<endl<<endl;

        meniu_principal("ACCESARE CONT",z,0,78,36-z/2,14);
        meniu_principal("CREEARE CONT",z,1,78,36-z/2,14);
        meniu_principal("SCHIMBARE PAROLA",z,2,78,36-z/2,14);
        meniu_principal("AJUTOR",z,3,78,36-z/2,14);
        meniu_principal("EXIT",z,4,78,36-z/2,14);

        SetConsoleTextAttribute(color,14);
        cout<<endl<<"Alege o optiune: ";
        cin>>n1;
        cout<<endl;
        switch(n1){
            case 0:{
                char a[200],b[200];
                SetConsoleTextAttribute(color,228);
                cout<<"Username:";
                SetConsoleTextAttribute(color,14);
                cout<<" ";
                cin>>a;
                SetConsoleTextAttribute(color,228);
                cout<<endl<<"Parola:";
                SetConsoleTextAttribute(color,14);
                cout<<" ";
                cin>>b;
                int validare_user=0,admin=0;
                if(strcmp(a,utilizator[1].username)==0 && strcmp(b,utilizator[1].parola)==0){
                    admin=1;
                    system("CLS");
                         do{
                         sortare_alfabetica(carte2,nr_carti);
                         for(int i=1;i<=nr_carti;i++)
                             for(int j=i;j<=nr_carti;j++)
                                 if(carte2[i].codISBN==carte[j].codISBN){
                                     aux=carte[i];
                                     carte[i]=carte[j];
                                     carte[j]=aux;
                                 }
                         SetConsoleTextAttribute(color,11);
                         cout<<"Buna Ziua, ";
                         SetConsoleTextAttribute(color,112);
                         cout<<utilizator[1].username<<endl<<endl;
                         cout<<"Ce optiune doriti sa alegeti?"<<endl<<endl;
                         SetConsoleTextAttribute(color,14);
                         meniu_principal("LISTA CARTI",40,0,112,1,11);
                         meniu_principal("CAUTARE CARTE",40,1,128,1,11);
                         meniu_principal("CAUTARE AUTOR",40,2,112,1,11);
                         meniu_principal("CAUTARE EDITURA",40,3,128,1,11);
                         meniu_principal("SORTARE CRONOLOGICA",40,4,112,1,11);
                         meniu_principal("ADAUGARE CARTE",40,5,128,1,11);
                         meniu_principal("STERGERE CARTE",40,6,112,1,11);
                         meniu_principal("LOG OUT",40,7,128,1,11);
                         cout<<endl;
                         SetConsoleTextAttribute(color,112);
                         cout<<"Alege o optiune:";
                         SetConsoleTextAttribute(color,14);
                         cout<<" ";
                         cin>>n2;
                            switch(n2){
                                case 0:{
                                    afisare_carti(carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\n\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 1:{
                                    cautare_titlu(carte2,carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 2:{
                                    cautare_autor(carte2,carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 3:{
                                    cautare_editura(carte2,carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 4:{
                                    afisare_cronologica(carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 5:{
                                    adaugare_carte(carte,carte2,nr_carti);
                                    scriere_in_fisier_carti(carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                case 6:{
                                    stergere_carte(carte,carte2,nr_carti);
                                    scriere_in_fisier_carti(carte,nr_carti);
                                    SetConsoleTextAttribute(color,11);
                                    cout<<"\nApasa Enter...";
                                    c=_getch();
                                    break;
                                }
                                default:
                                    break;
                            }system("CLS");
                         }while (n2!=7);
                }
                else{
                    for(int k=1;k<=nr_persoane;k++)
                        if(strcmp(a,utilizator[k].username)==0 && strcmp(b,utilizator[k].parola)==0)
                            validare_user=k;
                    if(validare_user==0){
                        SetConsoleTextAttribute(color,78);
                        cout<<"\nNumele contului sau parola sunt gresite!";
                        SetConsoleTextAttribute(color,14);
                        cout<<"\nApasa o tasta";
                        c=_getch();

                    }
                    else{
                         system("CLS");
                         citire_carti(carte,nr_carti);
                         do{
                         sortare_alfabetica(carte2,nr_carti);
                         for(int i=1;i<=nr_carti;i++)
                             for(int j=i;j<=nr_carti;j++)
                                 if(carte2[i].codISBN==carte[j].codISBN){
                                     aux=carte[i];
                                     carte[i]=carte[j];
                                     carte[j]=aux;
                                 }
                         cout<<"Bine ati venit, ";
                         SetConsoleTextAttribute(color,206);
                         cout<<utilizator[validare_user].username<<endl<<endl;
                         cout<<"Ce optiune doriti sa alegeti?"<<endl<<endl;
                         SetConsoleTextAttribute(color,14);
                         meniu_principal("LISTA CARTI",40,0,206,1,14);
                         meniu_principal("CAUTARE CARTE",40,1,78,1,14);
                         meniu_principal("CAUTARE AUTOR",40,2,206,1,14);
                         meniu_principal("CAUTARE EDITURA",40,3,78,1,14);
                         meniu_principal("SORTARE CRONOLOGICA",40,4,206,1,14);
                         meniu_principal("LOG OUT",40,5,78,1,14);
                         cout<<endl;
                         SetConsoleTextAttribute(color,206);
                         cout<<"Alege o optiune:";
                         SetConsoleTextAttribute(color,14);
                         cout<<" ";
                         cin>>n2;
                            switch(n2){
                                case 0:{
                                    afisare_carti(carte,nr_carti);
                                    cout<<"\nApasa Enter...";
                                    SetConsoleTextAttribute(color,14);
                                    c=_getch();
                                    break;
                                }
                                case 1:{
                                    cautare_titlu(carte2,carte,nr_carti);
                                    cout<<"\nApasa Enter...";
                                    SetConsoleTextAttribute(color,14);
                                    c=_getch();
                                    break;
                                }
                                case 2:{
                                    cautare_autor(carte2,carte,nr_carti);
                                    cout<<"\nApasa Enter...";
                                    SetConsoleTextAttribute(color,14);
                                    c=_getch();
                                    break;
                                }
                                case 3:{
                                    cautare_editura(carte2,carte,nr_carti);
                                    cout<<"\nApasa Enter...";
                                    SetConsoleTextAttribute(color,14);
                                    c=_getch();
                                    break;
                                }
                                case 4:{
                                    afisare_cronologica(carte,nr_carti);
                                    cout<<"\nApasa Enter...";
                                    SetConsoleTextAttribute(color,14);
                                    c=_getch();
                                    break;
                                }
                            }system("CLS");
                         }while (n2!=5);
                    }
                }
                break;
            }
            case 1:{
                adugare_ut(nr_persoane,utilizator);
                ofstream g1("Utilizatori.txt");
                g1<<utilizator[1].username<<endl;
                g1<<utilizator[1].parola;
                for(k=2;k<=nr_persoane;k++){
                    g1<<endl<<utilizator[k].username;
                    g1<<endl<<utilizator[k].parola;
                }
                cout<<"\nApasati o tasta...";
                c=_getch();
                break;
            }
            case 2:{
                char a[200],b[200];
                for(int i=1;i<=75;i++)
                    cout<<"~";
                cout<<endl;
                SetConsoleTextAttribute(color,228);
                cout<<"Username:";
                SetConsoleTextAttribute(color,14);
                cout<<" ";
                cin>>a;
                SetConsoleTextAttribute(color,228);
                cout<<endl<<"Vechea parola:";
                SetConsoleTextAttribute(color,14);
                cout<<" ";
                cin>>b;
                int validare_user=0;
                for(int k=1;k<=nr_persoane;k++)
                    if(strcmp(a,utilizator[k].username)==0 && strcmp(b,utilizator[k].parola)==0)
                        validare_user=k;
                if(validare_user==0){
                    SetConsoleTextAttribute(color,78);
                    cout<<endl<<"Numele contului sau parola sunt gresite!"<<endl;
                    SetConsoleTextAttribute(color,14);
                }
                else{
                    SetConsoleTextAttribute(color,228);
                    cout<<"\nIntroduce-ti noua parola:";
                    SetConsoleTextAttribute(color,14);
                    cout<<" ";
                    cin>>utilizator[validare_user].parola;
                    }
                for(int i=1;i<=75;i++)
                    cout<<"~";
                cout<<endl;
                cout<<"\nApasati o tasta...";
                c=_getch();
                break;
            }
            case 3:{
                ajutor();
                cout<<"\nApasati o tasta...";
                c=_getch();
                break;
            }
       } system("CLS");
    }while(n1!=4);
    ofstream g1("Utilizatori.txt");
    g1<<utilizator[1].username<<endl;
    g1<<utilizator[1].parola;
    for(k=2;k<=nr_persoane;k++){
        g1<<endl<<utilizator[k].username;
        g1<<endl<<utilizator[k].parola;
    }
    g1.close();
    return 0;
}

