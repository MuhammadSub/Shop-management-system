//The Header files used for this project/
 #include <iostream>      
 #include <fstream>            
 #include <string.h>           
 #include <stdlib.h>           
 #include <conio.h>            
 #include <ctype.h>            
 #include <math.h>             
 #include <windows.h>          
//#######################################

#define sice 100

using namespace std;


void prntchbych(char a[], int siz) 
{
    for (int i = 0; i < siz; ++i)
    {
        cout << a[i];
        Sleep(50);
    }
    cout << endl << endl;
}


// Print The Intro of the Project
void intro()
{
    char head[] = "\n\t\t\t\tCOMPUTER Programing PROJECT FOR 2nd Semester";
    char topic[] = "\tProject: Saintary And Paint Shop Management System";
    char names[] = "\n\tNames :- Muhammad Subhan \n\tReg no. :- 20-CP-77";
    char standard[] = "\tCourse:- Computer Programing";
    cout << head << endl;
    cout << names << endl;
    cout << standard << endl;
    cout << topic << endl;
    cout<<"\n\t";
	system("pause");
}

//Display the Progressbar after print the intro of the project
void progressbar()
{
	// Start the progress bar from 0
    float progress = 0.0;
    while(progress <= 1.1)
    {
        int barwidth = 70;
        cout << "\t[";
        int pos = barwidth * progress;
        for (int i = 0; i < barwidth; ++i)
        {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        } 
        cout << "]" << int(progress * 100.0) << "%\r"; //ending the progressbar to 100
        cout.flush();
        progress += 0.10;
        Sleep(100); //sleeping time of screen or set the speed of progressbar
    }
    cout << endl;
}

/*This function checks for the file stores.dat 
which is essential for the functioning of this program 
where, I save,delete or update the info of the product*/

void integritycheck()  
{
    system("cls");
    cout << "\n\t\t\t\tMuhammad Subhan Saintary and Paint STORE\n\n\tLoading all required files..." << endl;
    progressbar();
    ifstream ifs("stores.dat", ios::binary|ios::in);
    if (!ifs)
    {
        cout << endl << "\tFile stores.dat not found. Creating new file!!!" << endl;
        system("pause");
        ifs.close();
        ofstream ofs("stores.dat", ios::binary|ios::out);
        ofs.close();
        return;
    }
    cout << endl << "\tAll files successfully loaded!! Initiating application...";
    cout<<"\n\t";
    system("pause");
}

int STRING_TO_INT(char *a)  //Function to convert a number in a character array into integer
{
    int siz=strlen(a),ret,b=(siz-1),c,retu=0;
    for(int i=0; b>=0; i++)
    {
        c=(a[i]-'0');
        ret=c*(pow(10,b));
        if(b!=0&&b%2==0)
        {
            ret+=1;
        }
        retu=retu+ret;

        b--;
    }
    return retu;
}

void INT_TO_STRING(int x,char *str)  //Function to reverse the above process
{
    char str9[sice];
    int temp=x;
    int cnt=0;
    while(temp/10)
    {
        cnt++;
        temp/=10;
    }
    cnt++;
    for(int i=cnt-1; i>=0; i--)
    {
        str9[i]=(x%10)+48;
        x/=10;
    }
    str9[cnt]='\0';
    strcpy(str,str9);
}

int menucust(char lis[][80], const char title[], int siz, char price[][80], char qnty[][80], int *ret)  //A function to create the item selection menu for the customer
{
    int position = 1, i = 0, total = 0;
    char ttl[50];
    strcpy(ttl, title);
    strcat(ttl, " Selection Menu: ");
    char marker[siz];
    int quantity[siz];
    char input;
    for (int i = 0; i <= siz; ++i)
    {
        quantity[i] = 0;
    }
    do
    {
        total = 0;
        for (i = 0; i <= siz; ++i)
        {
            total += quantity[i] * STRING_TO_INT(price[i]);
        }
        system("cls");
        for (i = 0; i <= siz; ++i)
        {
            marker[i] = '\0';
        }
        cout << "\n\tBuy anything as much as you like... as long as the required amount is in stock!!" << endl;
        cout << "\n\t" << ttl << "\n\n";
        marker[position - 1] = '>';
        for (i = 0; i < siz; ++i)
        {
            if (STRING_TO_INT(qnty[i]) == 0)
            {
                cout <<"\t"<< marker[i] << " " << lis[i] << " " << "(Rs. " << price[i] << ")" << " : " << quantity[i] << "\n\t  Sorry!! The product is out of stock! Please try later. Sorry for the inconvenience..." << endl;
            }
            else
            {
                cout <<"\t"<< marker[i] << " " << lis[i] << " " << "(Rs. " << price[i] << ")" << " : " << quantity[i] << endl;
            }
        }
        cout <<"\n\tTotal is: " << total<<"\n\n";
        cout <<"\n\tPress UP, DOWN and LEFT, RIGHT to toggle between selected products and increase or decrease the amount to buy" << "\n\trespectively and press the ENTER KEY to confirm your selection..." << endl;
        input = toupper(getch());
        if (input == 72)
        {
            if (position == 1)
            {
                position = siz;
                continue;
            }
            else
            {
                --position;
            }
        }
        else if (input == 80)
        {
            if (position == siz)
            {
                position = 1;
                continue;
            }
            else
            {
                ++position;
            }
        }
        else if (input == 75)
        {
            if (quantity[position - 1] != 0)
            {
                quantity[position - 1] -= 1;
            }
        }
        else if (input == 77)
        {
            if (quantity[position - 1] < STRING_TO_INT(qnty[position - 1]))
            {
                quantity[position - 1] += 1;
            }
        }
        else
        {
            continue;
        }
    }
    while(input != 13);
    for (int i = 0; i < siz; ++i)
    {
        ret[i] = quantity[i];
    }
    system("cls");
    cout << "\n\tYour bill is: " << endl ;
    for (int i = 0; i < siz; ++i)
    {
        if (quantity[i] != 0)
        {
            cout << "\n\t" << lis[i] << " : " << quantity[i] ;
        }
    }
    cout << "\n\tTotal amount: Rs." << total << endl;
    cout << "\n\tAre you sure that you want to buy these?? (Y/N): ";
    char ol;
    ol = getch();
    if (ol == 'n' || ol == 'N')
    {
        cout << " \n\tTransaction cancelled";
        cout << "\n\t";
        system("pause");
        return -1;
    }
    ofstream ofs("Bill.txt", ios::out);
    ofs << "\n\tYour bill is: " << endl;
    for (int i = 0; i < siz; ++i)
    {
        if (quantity[i] != 0)
        {
            ofs << "\n\t" << lis[i] << " : " << quantity[i] ;
        }
    }
    ofs << "\n\tTotal amount: Rs." << total << endl;
    ofs.close();
    cout << endl;
    progressbar();
    cout <<"\n\tBill generated successfully!" << "\n\t";
    system("pause");
    system("cls");
    cout << "\n\n\n\tThanks for shopping here!" << "\n\t";
    system("pause");
    return 0;
}

int menu(char lis[][80], const char title[], int siz) //A function to create most of the menus in the application
{
    int position = 1, i = 0;
    char ttl[50];
    strcpy(ttl, title);
    strcat(ttl, " Selection Menu: ");
    char marker[siz + 1];
    char input;
    do
    {
        system("cls");
        for (i = 0; i <= siz; ++i)
        {
            marker[i] = '\0';
        }
        cout << "  " << ttl << endl;
        marker[position - 1] = '>';
        cout<<"\n";
        for (i = 0; i < siz; ++i)
        {
            cout <<"\t"<< marker[i] << " " << lis[i] << endl;
        }
        cout <<"\t"<< marker[i] << " Exit" << endl;
        cout << "\n\t Press UP and DOWN to move the cursor and press the ENTER KEY to select your option..." << endl;
        input = toupper(getch());
        if (input == 72)
        {
            if (position == 1)
            {
                position = siz + 1;
                continue;
            }
            else
            {
                --position;
            }
        }
        else if (input == 80)
        {
            if (position == siz + 1)
            {
                position = 1;
                continue;
            }
            else
            {
                ++position;
            }
        }
        else
        {
            continue;
        }
    }
    while(input != 13);
    return position;
}

class newproduct  //The class that defines how an item is stored in the file 'stores.dat'
{
    char pnumber[80],pqty[80],pprice[80];
    char pname[80],pdescription[100];
    char n[7][80];

public:
    newproduct()
    {
        strcpy(n[0], "Product Number: ");
        strcpy(n[1], "Product Name: ");
        strcpy(n[2], "Product Quantity: ");
        strcpy(n[3], "Price per piece: ");
        strcpy(n[4], "Product Description: ");
        strcpy(n[5], "Confirm Selection!!! ");
    }
    void newentry()
    {
        int x = 0;
        while(x == 0)
        {
            switch (menu(n, "\n\tNew Product Info", 6))
            {
            case 1 :
                system("cls");
                cin >> pnumber;
                strcpy(n[0], "Product Number: ");
                strcat(n[0], pnumber);
                break;
            case 2 :
                system("cls");
                cin >> pname;
                strcpy(n[1], "Product Name: ");
                strcat(n[1], pname);
                break;
            case 3 :
                system("cls");
                cin >> pqty;
                strcpy(n[2], "Product Quantity: ");
                strcat(n[2], pqty);
                break;
            case 4 :
                system("cls");
                cin >> pprice;
                strcpy(n[3], "Price per piece: ");
                strcat(n[3], pprice);
                break;
            case 5 :
                system("cls");
                cin >> pdescription;
                strcpy(n[4], "Product Description: ");
                strcat(n[4], pdescription);
                break;
            case 6 :
                x += 1;
                break;
            case 7 :
                exit(0);
            default :
                break;
            }
        }
    }

    void changentry()
    {
        int x = 0;
        while(x == 0)
        {
            switch (menu(n, "\n\tNew Product Info ", 6))
            {
            case 1 :
                system("cls");
                cin >> pnumber;
                strcpy(n[0], "Product Number: ");
                strcat(n[0], pnumber);
                break;
            case 2 :
                system("cls");
                cin >> pname;
                strcpy(n[1], "Product Name: ");
                strcat(n[1], pname);
                break;
            case 3 :
                system("cls");
                cin >> pqty;
                strcpy(n[2], "Product Quantity: ");
                strcat(n[2], pqty);
                break;
            case 4 :
                system("cls");
                cin >> pprice;
                strcpy(n[3], "Price per piece: ");
                strcat(n[3], pprice);
                break;
            case 5 :
                system("cls");
                cin >> pdescription;
                strcpy(n[4], "Product Description: ");
                strcat(n[4], pdescription);
                break;
            case 6 :
                x += 1;
                break;
            case 7 :
                exit(0);
            default :
                break;
            }
        }
    }

    void displayproduct()
    {
        system("cls");
        cout<<"\n\tYour details are as follows\n"
            <<"\t____________\n";

        cout<<"\tProduct Number: "<<pnumber<<endl
            <<"\tProduct Name: "<<pname<<endl
            <<"\tProduct Quantity: "<<pqty<<endl
            <<"\tPrice per piece: "<<pprice<<endl
            <<"\tProduct Description: "<<pdescription<<"\n\t";
    }

    void updqty(char *a)
    {
        strcpy(pqty, a);
    }

    char *num()
    {
        return(pnumber);
    }

    char *name()
    {
        return(pname);
    }

    char *qty()
    {
        return(pqty);
    }

    char *price()
    {
        return(pprice);
    }

    char *desc()
    {
        return(pdescription);
    }
};

void update()
{
    char temp[20][80];
    int k=0,ret;
    ifstream fin("stores.dat",ios::in|ios::binary);
    newproduct A;
    while(fin.read((char *)&A,sizeof(newproduct)))
    {
        strcpy(temp[k++],A.num());
    }
    fin.close();
    ret=menu(temp,"\n\t Product no.",k);
    if (ret == k + 1)
    {
        exit(0);
    }
    fstream fs("stores.dat", ios::binary|ios::in|ios::out);
    fs.seekg(0);
    int il;
    for (int i = 1; i <= ret; ++i)
    {
        il = fs.tellg();
        fs.read((char*)&A,sizeof(newproduct));
    }
    A.changentry();
    fs.seekp(il);
    if(fs.write((char*)&A, sizeof(newproduct)))
    {
        system("cls");
        cout <<"\n\tUpdating records." << endl;
        progressbar();
        cout << "\n\tRECORD UPDATED SUCCESSFULLY!!\n\t";
        system("pause");
    }
    fs.close();
}

void custsplash()
{
    cout << "\n\t\t\t\tWELCOME TO Muhammad Subhan Paint STORE!!!\n\t";
    system("pause");
    system("cls");
    newproduct ob;
    int cnt = 0;
    ifstream ifs("stores.dat", ios::binary|ios::in);
    char temp0[10][80], temp1[10][80], temp2[10][80], tmp3[40];
    while (ifs.read((char*)&ob, sizeof(newproduct)))
    {
        strcpy(temp0[cnt], ob.price());
        strcpy(temp1[cnt], ob.name());
        strcpy(temp2[cnt], ob.qty());
        ++cnt;
    }
    ifs.close();
    int arr[20], il, desc;
    desc = menucust(temp1, " Products", cnt, temp0, temp2, arr);
    if (desc== -1)
    {
        return;
    }
    fstream fs("stores.dat", ios::binary|ios::in|ios::out);
    for (int i = 0; i < cnt; ++i)
    {
        il = fs.tellg();
        fs.read((char*)&ob, sizeof(newproduct));
        INT_TO_STRING(STRING_TO_INT(ob.qty()) - arr[i], tmp3);
        ob.updqty(tmp3);
        fs.seekp(il);
        fs.write((char*)&ob, sizeof(newproduct));
    }
    fs.close();
}

void disp()
{
    char tmp[10][80];
    ifstream ifs("stores.dat", ios::binary|ios::in);
    newproduct ol;
    int cnt = 0;
    while(ifs.read((char*)&ol,sizeof(newproduct)))
    {
        strcpy(tmp[cnt], ol.num());
        ++cnt;
    }
    ifs.close();
    int x = menu(tmp, " Product no.", cnt);
    if (x == cnt + 1)
    {
        exit(0);
    }
    cnt = 0;
    ifs.open("stores.dat", ios::binary|ios::in);
    while(cnt < x)
    {
        ifs.read((char*)&ol,sizeof(newproduct));
        ++cnt;
    }
    ifs.close();
    ol.displayproduct();
    system("pause");
}

void delprdct()
{
    char tmp[10][80];
    ifstream ifs("stores.dat", ios::binary|ios::in);
    newproduct one, two;
    int cnt = 0;
    while(ifs.read((char*)&one,sizeof(newproduct)))
    {
        strcpy(tmp[cnt], one.num());
        ++cnt;
    }
    ifs.close();
    int x = menu(tmp, "\n\tProduct no.", cnt);
    if (x == cnt + 1)
    {
        exit(0);
    }
    ofstream ofs("tmp.dat", ios::binary|ios::out);
    ifs.open("stores.dat", ios::binary|ios::in);
    cnt = 1;
    while(ifs.read((char*)&one,sizeof(newproduct)))
    {
        if (cnt != x)
        {
            ofs.write((char*)&one,sizeof(newproduct));
        }
        ++cnt;
    }
    ifs.close();
    ofs.close();
    ifs.open("stores.dat", ios::binary|ios::in);
    for (int i = 1; i <= x; ++i)
    {
        ifs.read((char*)&two,sizeof(newproduct));
    }
    system("cls");
    ifs.close();
    two.displayproduct();
    cout << "\n\tDo you want to delete this record??? (Press y for yes and n for no): ";
    char ch;
    ch = getch();
    if (ch == 'y')
    {
        remove("stores.dat");
        rename("tmp.dat", "stores.dat");
        system("cls");
        cout << "\n\tDeleting from records" << endl;
        progressbar();
        cout << "\n\tProduct Deleted successfully!\n\t";
        system("pause");
    }
    else
    {
        remove("tmp.dat");
    }
}

void newprdct()
{
    ofstream fout("stores.dat",ios::app|ios::binary);
    ifstream fin("stores.dat",ios::in|ios::binary);
    newproduct c, A;
    A.newentry();
    while(!fin.eof())
    {
        fin.read((char*)&c,sizeof(c));
        if(strcmp(A.num(), c.num()) == 0)
        {
            cout<<"Product with the same product number already exists. Try again!!!\n\t";
            system("pause");
            system("cls");
            return;
        }

    }
    fin.close();
    fout.write((char*)&A,sizeof(A));
    system("cls");
    cout << "\n\tEntering newly entered record" << endl;
    progressbar();
    cout << "\n\tNew Product Entered Successfully.\n\t";
    fout.close();
    system("pause");
    system("cls");
}

void adminmenu()
{
    char func[5][80];
    strcpy(func[0], "New Product");
    strcpy(func[1], "Update Existing Data");
    strcpy(func[2], "Delete Data");
    strcpy(func[3], "Display Information");
    while(true)
    {
        switch (menu(func, "\n\tAdmin Operation", 4))
        {
        case 1 :
            system("cls");
            newprdct();
            break;
        case 2 :
            system("cls");
            update();
            break;
        case 3 :
            system("cls");
            delprdct();
            break;
        case 4 :
            system("cls");
            disp();
            break;
        case 5 :
        	system("cls");
        	exit(0);
            break;
        default :
            break;
        }
    }
}

class start
{
public:
    char members[2][80];
    start()
    {
        strcpy(members[0], "Administrator");
        strcpy(members[1], "Customer");
        while(true)
        {
            switch (menu(members, "\n\tType of User", 2))
            {
            case 1 :
                system("cls");
                adminlogin();
                break;
            case 2 :
                system("cls");
                custlogin();
                break;
            case 3 :
                exit(0);
                break;
            default :
                break;
            }
        }
    }

    void custlogin()
    {
        system("cls");
        custsplash();
    }

    int adminlogin()
    {
        char str[80],ch;
        int k=0;
        cout<<"\n\n\n\tEnter password:";
        while(ch!=13)
        {
            ch=getch();
            if(ch=='\b'&&k!=0)
            {
                cout<<"\b";
                cout<<" ";
                cout<<"\b" ;
                k--;
                continue;
            }
            if(ch!='\b')
            {
                cout<<"*";
                str[k++]=ch;
            }
        }
        str[k-1]='\0';
        system("cls");
        if(strcmp(str,"Subhan786@")==0)
        {
            cout<<"\n\n\n\tACCESS GRANTED\n\t";
            system("pause");
            system("cls");
            adminmenu();
        }
        else
        {
            cout<<"\n\n\n\tACCESS DENIED\n\t";
            system("pause");
            system("cls");
            return 0;
        }
        system ("pause");
        system("cls");
        return 0;
    }
};


int main()
{
    system("color f0");
    intro();
    integritycheck();
    start();
    return 0;
}
