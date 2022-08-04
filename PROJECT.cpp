#include<iostream>
#include<fstream>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<dos.h>
#include<ctype.h>
#include<conio.h>
using namespace std;
//The Menu class is there Which display the options
class Menu
{
public:
    void showmenu(void);
private:
    void closemenu(void);
} ;
//This displays all the Customer A/c
class Display_Record
{
public:
    void Add_details(long int,char name[30],char Add[60],float );
    void Display_customer(void);
    void Delete_AC(long int);
    void Update_Bal(int,float);//float as in Rs
    void Update_customer(void);
    int Last_AC(void);
    int AC_exists(long int);
    float Get_Bal(long int);
    int Get_Record(int);
    void Display(long int);
    void Display_List(void);
    char *GetName(long int);
    char *GetAddress(long int);
    int Ac_num;
    char Name[50],Address[80];
    float Bal;
};
// this class all Transaction related details
class AC_Transactions
{
public:
    void New_Ac(void);
    void Close_Ac(void);
    void Display_Ac(void);
    void Transaction(void);
    void Delete_Ac(long int);
    void Add_Details(int,int,int,int,char,char Type_transaction[15],float,float,float);
    int Date_differ(int,int,int,int,int,int);
    float Get_Interest(long int,float);
    void Display(long int);
    void Show_Ac(long int);
   long int Account_number;
   char TranType[10];
   int DD,MM,YY;
   char Transactions;
   float Interest,Amount,Bal;
   static float Cal_Interest;
   void Show_Interest(void);
};
void Menu::showmenu(void)
{
 char choice;
 while(1)
 {
//lrscr();
        cout<<"\n\t\t\t\t --- Welcome To the Banking System Application ---\t\t\n";
        cout<<"**************************************************************"<<endl<<endl;
        cout<<"\t\t\t\tChoice from Following Options :\t\t\t"<<endl;
        cout<<"\t\t\t-------------------------------------\t\t\t"<<endl;
        cout<<"\t 1 : Open an Account\t"<<endl;
        cout<<"\t 2 : View an Account\t"<<endl;
        cout<<"\t 3 : Show All Accounts\t"<<endl;
        cout<<"\t 4 : Make a Transaction\t"<<endl;
        cout<<"\t 5 : Calculate Interest\t"<<endl;
        cout<<"\t 6 : Close an Account\t"<<endl;
        cout<<"\t 7 : Exit\t\t\t"<<endl;
        cout<<"\t\t Make a Choice \t\t"<<endl;
        choice=getchar();
        if(choice=='1')
        {
            AC_Transactions objAT;
            objAT.New_Ac();
        }
        else if(choice=='2')
        {
          AC_Transactions objAT;
          objAT.Display_Ac();
        }
        else if(choice=='3')
        {
         Display_Record objDr;
         objDr.Display_customer();
        }
        else if (choice=='4')
        {
            AC_Transactions objAT;
            objAT.Transaction();
        }
        else if(choice=='5')
        {
            AC_Transactions objAt;
            objAt.Show_Interest();
        }
        else if(choice=='6')
        {
         closemenu();
        }
        else if (choice=='7')
        {
            cout<<"\n\t\t Thanks for Using this Application,Please Press any key to Exit\t\t"<<endl;
            getch();
            break;
        }
 }
}
void Menu::closemenu(void)
{
    char Choice;
    while(1)
    {
//      clrscr();
         cout<<"\t\t Close Menu \t\t"<<endl;
         cout<<"\t******************\t"<<endl;
         cout<<"\t\t 1 : Close/Delete Account \t\t"<<endl;
         cout<<"\t\t 0 : Exit From this Menu \t\t"<<endl;
         cout<<"\t\t\t Select Anyone \t\t\t\t"<<endl;
         Choice=getche();
         if(Choice=='1')
         {
             AC_Transactions objAt1;
             objAt1.Close_Ac();
             break;
         }
         else if(Choice=='0')
         {
             cout<<"\t\t\t -- You have Entered 0 to Go back to the previous Menu --\t\t\t"<<endl;
             getch();
             break;
         }
    }
}
//LastAccount() returns the last account number from the record.dat file
int Display_Record ::Last_AC(void)
{
    fstream filename;
    filename.open("newrecords.dat", ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char*)this,sizeof(Display_Record)));
    {count=Ac_num;}
    filename.close();
    return(count);
}
//Get_Record() returns the record number from new_records.dat file when banking staff enters the ac number
int Display_Record::Get_Record(int RetriveAC_num)
{
    fstream filename;
    filename.open("newrecods.dat",ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char*)this,sizeof(Display_Record)))
    {
        count++;
        if(RetriveAC_num==Ac_num)
        {
            break;
        }
    }
    filename.close();
    return(count);
}
//display method display all the dedtails of Account number from the newrecord.dat File
void Display_Record::Display(long int Retrive_AC)
{
    int record;
    record=Get_Record(Retrive_AC);
    fstream filename;
    filename.open("newrecord.dat",ios::in);
    filename.seekg(0,ios::end);
    int location;
    location =(record)*sizeof(Display_Record);
    filename.seekp(location);

     while(filename.read((char*)this,sizeof(Display_Record)))
     {
         if(Retrive_AC==Ac_num)
         {
             cout<<"\t\t Account Number : \t\t"<<Ac_num<<endl;
             cout<<"\t\t Name : \t\t"<<Name<<endl;
             cout<<"\t\t Address : \t\t"<<Address<<endl;
             cout<<"\t\t Balance : \t\t"<<Bal<<endl;
             break;
         }
     }
    filename.close();
}
//get_name() returns trhe Account holder name From newrecord.dat file
char *Display_Record::GetName(long int Retrive_Ac)
{
   fstream filename;
   filename.open("newrecords.dat",ios::in);
filename.seekg(0,ios::beg);
 char Retrive_cust_name[30];

 while(filename.read((char*)this,sizeof(Display_Record)))
 {
     if(Ac_num==Retrive_Ac)
     {
         strcpy(Retrive_cust_name,Name);
     }

 }
 filename.close();
    return(Retrive_cust_name);
}
//get_Address()returns the address of the account holder from the newrecord.dat file
char *Display_Record::GetAddress(long int Retrive_AC)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    char Retrive_address[60];
    while(filename.read((char*)this,sizeof(Display_Record)))
    {
        if(Ac_num==Retrive_AC)
        {
            strcpy(Retrive_address,Address);
        }
    }
    filename.close();
    return(Retrive_address);
}
//Get_Bal() returns the balance of account holder from newrecords.dat file
float Display_Record::Get_Bal(long int Retrive_AC)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    float Balance;
    while(filename.read((char*)this,sizeof(Display_Record)))
    {
        if(Ac_num==Retrive_AC)
        {
            Balance=Bal;
        }
    }
    filename.close();
    return(Balance);
}
//Account_exots() checks whether the ac exists or not
int Display_Record::AC_exists(long int Retrive_AC)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char*)this,sizeof(Display_Record)))
    {
        if(Ac_num==Retrive_AC)
        {
            count=1;
            break;
        }
    }
    filename.close();
    return(count);
}
//display_list() shows the output of all the account in proper format for choice 3
void Display_Record::Display_List()
{
    cout<<endl<<endl;
    int day,month,year;
    /*struct date dateval;
    getdate(&dateval);
    day=dateval.DD;
    month=dateval.MM;
    year=datetval.YY;
    cout<<"\t\t Date : \t\t"<<day<<" / "<<month<<" / "<<year<<endl;
    cout<<setw(80)<<"----------------------------------"<<endl;*/
    cout<<setw(23)<<"ACCOUNT NUMBER";
    cout<<setw(23)<<"NAME OF PERSON";
    cout<<setw(23)<<"BALANCE";
    cout<<setw(80)<<"----------------------------------"<<endl;
}
//Display_customer() shows all account holders frm newrecord.dat file
void Display_Record::Display_customer()
{
   // clrscr();
    int len1;
    int row=8,check;
    fstream filename;
    FILE * pFILE;
    pFILE=fopen("newrecord.dat","r");
    if(pFILE==NULL)
    {
        cout<<"\t NO ACCOUNT EXISTS ,Please Go Back to Previous Step \t"<<endl;
        getch();
        return;
    }
    else
        {
            Display_List();
            filename.open("newrecords.dat",ios::in);
            filename.seekg(0,ios::beg);
            while(filename.read((char*)this,sizeof(Display_Record)))
            {
              check=0;
              cout.fill(' ');
              cout<<setw(20);
              cout.setf(ios::right,ios::adjustfield);
              cout<<Ac_num;
              cout.fill(' ');
              cout<<setw(25);
              cout.setf(ios::internal,ios::adjustfield);
              cout<<Name;
              cout<<setw(23);
              cout.setf(ios::right,ios::adjustfield);
              cout<<Bal<<"\n";
              row++;
              if(row==23)
              {
                  check=1;
                  row=8;
                  cout<<"\n\n Continue the Application \n\n ";
                  getch();
                  //clrscr();
                  Display_List();
              }

            }
        }
        filename.close();
        if(!check)
        {
            cout<<"\n\n Continue the Application \n\n";
            getch();
        }
}
//ADD Details in the newrecords.dat file
void Display_Record::Add_details(long int Retrive_AC,char Cus_Name[30],char Retrive_Add[60],float Balance)
{
    Ac_num=Retrive_AC;
    strcpy(Name,Cus_Name);
    strcpy(Address,Retrive_Add);
    Bal=Balance;
    fstream filename;
    filename.open("newrecords.dat",ios::out|ios::app);
    filename.write((char*)this,sizeof(Display_Record));
    filename.close();
}
// delete_AC here we will delete the perticular record frm newrecords.dat file
void Display_Record::Delete_AC(long int Retrive_AC)
{
 fstream filename;
 filename.open("newrecords.dat",ios::in);
 fstream temp;
 temp.open("calculation.txt",ios::out);
 filename.seekg(0,ios::beg);
 while(!filename.eof())
 {
     filename.read((char*)this,sizeof(Display_Record));
     if(filename.eof())
     {
         break;
     }
     if(Ac_num!=Retrive_AC)
     {
         temp.write((char*)this,sizeof(Display_Record));
     }
    filename.close();
    temp.close();
 }
}
//Update the Balance of the Ac holder After The Transaction done
void Display_Record::Update_Bal(int Retrive_AC,float Balance)
{
    int Record;
    Record=Get_Record(Retrive_AC);
    fstream filename;
    filename.open("newrecords.dat",ios::out|ios::ate);
    Bal=Balance;
    int Location;
    Location=(Record-1)*sizeof(Display_Record);
    filename.seekp(Location);
    filename.write((char*)this,sizeof(Display_Record));
    filename.close();
}
//Add Details() Adds the details of Transactions in Transcation.dat File
/*void AC_Transactions::Add_Details(long int Retrive_AC,int Day,int Month,int Year,char T_Trans,char Type_Transc[10],float interest_Accurde,float T_Amt,float Balance)
{
    fstream filename;
    filename.open("Transacation.dat", ios::app);
    Account_number=Retrive_AC;
    DD=Day;
    MM=Month;
    YY=Year;
    Transactions=T_Trans;
    strcpy(TranType,Type_Transc);
    Interest=interest_Accurde;
    Amount=T_Amt;
    Bal=Balance;
    filename.write((char*)this,sizeof(AC_Transactions));
    filename.close();
}*/
//Delete AC method Deletes the record of Transaction frm Transaction.dat file
void AC_Transactions::Delete_Ac(long int Retrive_AC)
{
 fstream filename;
 filename.open("Transaction.dat",ios::in);
 fstream temp;
 temp.open("Calculations.txt",ios::out);
filename.seekg(0,ios::beg);
while(!filename.eof())
{
 filename.read((char*)this,sizeof(AC_Transactions));
 if(filename.eof())
 {
     break;
 }
/* if(Ac_num != Retrive_AC)
 {
     temp.write((char*)this,sizeof(AC_Transactions));
 }
}
filename.close();
temp.close();

filename.open("Transaction.dat",ios::out);
temp.open("Calculations.txt",ios::in);
temp.seekg(0,ios::beg);
while(!temp.eof())
{
    temp.read((char*)this,sizeof(AC_Transactions));
    if(temp.eof())
    {
        break;
    }
    filename.write((char*)this,sizeof(AC_Transactions));
}
filename.close();
temp.close();
}*/
// new_AC() add new record in the newrecord.dat file and Transaction.dat file
void AC_Transactions :: New_Ac(void)
{
  char choice;
  int i,check;
  clrscr();
  Display_Record newrecord;
  cout<<"\t\t Please Enter '0' to GO Back to previous Menu \t\t"<<endl<<endl;
  cout<<"\t\t ------------------------------------------- \t\t"<<endl;
  cout<<"\t\t Open a New Bank Account \t\t"<<endl;
  cout<<"\t\t ******************************* \t\t"<<endl;
  int Day,Month,Year;
  struct date date_val;
  getdata(&date_val);
  Day=date_val.DD;
  Month=date_val.MM;
  Year=date_val.YY;
  long int Retrive_AC;
  Retrive_AC=newrecord.Last_AC();
  Retrive_AC++;

  if(Retrive_AC==1)
  {
   newrecord.Add_details(Retrive_AC," ABHISHEK "," Raipur ",1.1);
   newrecord.Delete_AC(Retrive_AC);
   Add_Details(Retrive_AC,1,1,1997,'D',"Default Value",1.1,1.1,1.1);
   Delete_Ac(Retrive_AC);
  }
  char Retrive_Cust_Name[30],Trans_AC[10],Retrive_Add[60];
  float T_Balance,Bal;
  cout<<"\t\t Date : "<<DD<<"  Month : "<<MM<<"  Year : "<<YY<<endl<<endl;
  cout"\t\t\t ACCOUNT NUMBER : \t\t\t"<<Retrive_AC<<endl;

  do
  {
      cout<<"\n\n Please Enter the Name of the Account Holder\t\n";
      check=1;
      gets(Retrive_Cust_Name);
      if(Retrive_Cust_Name[0]=='0')
      {
        cout<<"\t\t\t ** INVALID Customer Name ** \t\t\t "<<endl;
        getch();
        return();
      }
      strupr(Retrive_Cust_Name);
      if(strlen(Retrive_Cust_Name)==0||strlen(Retrive_Cust_Name)>30)
      {
          check=0;
          cout<<"\t\t\t Customer Name is Either Blank Or Exceeding the Limit \t\t\t"<<endl;
          getch();
      }
  }
  while(!check);

  do
  {
   cout<<"\nPlease Enter the Account holder's Address\n";
   check=1;
   gets(Retrive_Add);
   if(Retrive_Add[0]=='0')
   {
       cout<<"\t\t\t *** INVALID CUSTOMER ADDRESS *** \t\t\t";
       getch();
       return();
   }
   strupr(Retrive_Add);
   if(strlen(Retrive_Add)<1||strlen(Retrive_Add)>60)
   {
       check=0;
       cout<<"\t\t\t Customer Address is Either Blank Or Exceeding the Limit \t\t\t"<<endl;
       getch();
   }
  }
  while(!check);

  do
  {
      char chr_verif_per[30];
      cout<<"\t\t\t Please Enter the Name of the Verified Person of the Account Holder \t\t\t"<<endl;
      check=1;
      gets(chr_verif_per);
      if(chr_verif_per[0]=='0')
      {
          cout<<"\t\t\t *** INVALID VERIFYING PERSON NAME *** \t\t\t";
          getch();
          return();
      }
      strupr(chr_verif_per);
      if(strlen(chr_verif_per)<1||strlen(chr_verif_per)>30)
      {
          check=0;
          cout<<"\t\t\t Verifying Person is not Found Or Greater than the Limit \t\t\t"<<endl;
          getch();
      }
      }
      while(!check);
    do
    {
        cout<<"\n Please Enter the Deposit Amount while Opening new Account \n";
        check=1;
        gets(Trans_AC);
        T_Balance=atof(Trans_AC);
        Bal=T_Balance;
        if(strlen(Trans_AC)<1)
        {
            cout<<"\t\t\t *** INVALID TRANSACTION VALUE *** \t\t\t"<<"\n Exiting from Current Menu"<<endl;
            getch();
            return();
        }
        if(Bal<1000)
        {
            check=0;
            cout<<"\t\t\t The Minimum Deposit Amount Should be 1000 \t\t\t"<<"\n Please Try Again"<<endl;
            getch();
        }
    }
    while(!check);

    do
    {
        cout<<"\n Do you want to save the Record\n"<<"* Yes\n"<<"* No"<<endl;
        choice=getche();
        choice=toupper(choice);
    }
    while(choice!='N'&& choice!='Y');
    if(choice=='N'|| choice=='n');
    {
        cout<<"The Customer Account is not Created, Please continue with application\n";
        getch();
        return();
    }
    float t_Amt,Interest_Accrude;
    t_Amt=Bal;
    Interest_Accrude=0.0;
    char T_Trans,Type_Trans[10];
    T_Trans='D';
    strcpy(Type_Trans," ");

    newrecord.Add_details(Retrive_AC,Retrive_Cust_Name,Retrive_Add,Bal);
    Add_Details(Retrive_AC,DD,MM,YY,T_Trans,Type_Trans,Interest_Accrude,t_Amt,Bal);
    cout<<"\n The New Account is Successfully Created !!! "<<endl;
    cout<<" Please Continue with the Application...."<<endl;
    getch();
}
//Show_AC() formats the Display of Records From Transaction.dat file for a perticular AC
void AC_Transactions::Show_Ac(long int Retrive_AC)
{
    cout<<" "<<endl<<endl;
    int day,month,Year;
    struct date date_val;
    getdata(&date_val);
    day=date_val.DD;
    month=date_val.MM;
    Year=date_val.YY;
    cout<<"Date : "<<day<<"/"<<month<<"/"<<Year<<endl;
   cout<<"\tACCOUNT NUMBER :\t"<<Retrive_AC;
   Display_Record newRAC;

   char Retrive_cust_name[30];
   strcpy(Retrive_cust_name,newRAC.GetName(Retrive_AC));
   char Retrive_Add[60];
   strcpy(Retrive_Add,newRAC.GetAddress(Retrive_AC));
   cout<<setw(25)<<endl;
   cout<<"\t ACCOUNT HOLDERS NAME \t"<<Retrive_cust_name<<"\nADDRESS :\t"<<Retrive_Add<<endl;
   cout<<setw(80)<<"\n -------------------------------------------------------------------\n";
   cout<<setw(10)<<"Dated";
   cout<<setw(12)<<"Details";
   cout<<setw(12)<<"Deposited";
   cout<<setw(15)<<"Withdrawn";
   cout<<setw(12)<<"         ";
   cout<<setw(10)<<"Balance";
   cout<<setw(80)<<"\n -------------------------------------------------------------------\n";
}
//Display_AC() Displays the Record from transaction.dat file
void AC_Transactions::Display_Ac(void)
{
    clrscr();
    char T_AC[10];
    long int Trans_AC,Retrive_AC_num;
    Display_Record obj2;
    cout<<" Press '0' to Go back to the Previous Menu "<<endl;
    cout<<"  Please Enter Account Number you want to View  "<<endl;
    gets(T_AC);
    Trans_AC=atoi(Trans_AC);
    if(Retrive_AC_num==0)
    {
        cout<<"  You have pressed '0' to Exit  "<<endl;
        getch();
        return();
    }
    clrscr();
    Display_Record newrecord;
    AC_Transactions AA;
    int Row=8,check;
    fstream filename;
    FILE* pFILE;
    pFILE=fopen("newrecords.dat",r);
    if(pFILE==NULL)
    {
        cout<<"  **NO Such Account EXISTS,Please Create a new One**  "<<endl;
        getch();
        return();
    }
    else if(newrecord.AC_exists(Retrive_AC_num))
    {
        cout<<"\t\n ***ACCOUNT DOESN'T EXISTS*** \t\n";
        getch();
        return();
    }
    else
        {
            Show_Ac(Retrive_AC_num);
            filename.open("Transaction.dat",ios::in);

            while(filename.read((char*)this,sizeof(AC_Transactions)))
            {
                if(AC_num==Retrive_AC_num)
                {
                    check=0;
                    cout<<setw(3)<<DD<<" / "<<MM<<" / "<<YY;
                    cout<<setw(10)<<TranType;
                    if(Transaction=='D')
                    {
                        cout.setf(ios::right,ios::adjustfield);
                        cout<<setw(15);
                        cout<<Amount;
                        cout<<setw(20);
                        cout<<" ";
                    }
                    else
                    {
                        cout.setf(ios::right,ios::adjustfield);
                        cout<<setw(25);
                        cout<<Amount;
                        cout<<setw(10);
                        cout<<" ";
                    }
                    cout<<setw(15);
                    cout.setf(ios::right,ios::adjustfield);
                    cout<<Bal<<endl;
                    Row++;

                    if(Row==23)
                    {
                        check=1;
                        Row=8;
                        cout<<"\t ** Please Continue with the Application ** \t"<<endl;
                        getch();
                        clrscr();
                        Show_Ac(Retrive_AC_num);
                    }

            }
            }
    }
    filename.close();
    if(!check)
    {
        cout<<"\n\n Press any Key to continue with the Application \n"<<endl;
        getch();
    }
}
// Date_differ() will differ the date between the two dates
int AC_Transactions::Date_differ(int Day,int Month,int Year,int Day1,int Month1,int Year1)
{
 static int MonthArray[]={31,28,31,30,31,30,31,31,30,31,30,31};
 //MonthArray for storing the no. of days in each array
 int Days=0;
 while(Day !=Day1||Month !=Month1||Year !=Year1)
 {
     // Checking Two Dates in a month or year differs and incrementing the no. of days
     Days++;
     Day++;
     if(Day>Month[Month-1])
     {
       Day=1;
       Month++;
     }
     if(Month>12)
     {
         Month=1;
         Year++;
     }

 }
 return(Days);
}
//Get_Interest() cal the Interest on bal from the transcation.dat file
float AC_Transactions::Get_Interest(long int Retrive_AC,float Bal)
{
    fstream filename;
    filename.open("Transaction.dat",ios::in);
    Display_Record newrecord;
    filename.seekg(0,ios::beg);
    int day1,month1,year1,month_day;
    while(filename.read((char*)this,sizeof(AC_Transactions)));
    {
        if(AC_num==Retrive_AC)
        {
            day1=DD;
            month1=MM;
            year1=YY;
            Bal=newRAC.Get_Bal(Retrive_AC);
            break;
        }
    }
    int day2,month2,year2;
    struct date date_val;
    get_data(&date_val);
    day2=get_val.DD;
    month2=get_val_MM;
    year2-get_val.YY;
    float Interest_Accured=0.0;
    int Year_Differ=year2-year1;

    if((year2<year1)||(year2==year1 && month2<month1)||(year2==year1 && month2==month1 && day2<day1))
    {
      return(Interest_Accured);
    }
    month_day=Date_differ(day1,month1,year1,day2,month2,year2);
    int months;
    if(month_day>=30)
    {
        months=month_day/30;
    }
    else
    {
        months=month_day/30;
    }
    if(Interest_Accured==0 && Year_Differ==1)
    {
        Interest_Accured=((Bal*0.5)/100)*(months);
    }
    else if(Year_Differ >1 && Year_Differ<25 && Interest_Accured==0)
    {
        Interest_Accured=((Bal*0.5)/100)*(months);
    }
    else
    {
        Interest_Accured=0;
    }
    filename.close();
    return(Interest_Accured);
}
// Method for generating interest and updation of balance and add_details
 void AC_Transactions::Show_Interest(void)
 {
     clrscr();
     char T_AC[10];
     int Trans_AC,Retrive_AC,check;
     cout<<strupr("\n\t\t\t\t\t **IMPORTANT INFORMATION** : \nInterest should be Generated only once in a Year\n\n\t\t If you have already generated Interest,Please Ignore that Account\n\n\t\t\t\t THANK YOU!!\n");
     cout<<"\n\n Press '0'to Go back to Previous Menu \n\n";
     cout<<"\n To View the Transaction of ACCOUNT ,Please Enter the ACCOUNT NUMBER : \n\n";
     gets(T_AC);
     Trans_AC=atoi(T_AC);
     Retrive_AC=Trans_AC;
     if(Retrive_AC==0)
     {
         return();
     }
     clrscr();
     Display_Record newREC;
     if(!newREC.AC_exists(Retrive_AC))
     {
         cout<<"\nACCOUNT doesn't Exists\n"<<endl;
         getch();
         return();
     }
     cout<<"Press'0'to Go back to Previous Menu\n"<<endl;
     cout<<"\t\t Please Enter the ACCOUNT NUMBER to generate Interest\n\n";
     cout<<"--------------------------------------------------------------\n";
     int Day,Month,Year;
     struct Date Date_val;
      getdate(&Date_Val);
      Day=Date_val.DD;
      Month=Date_val.MM;
      Year=Date_val.YY;
      cout<<"Date"<<Day<<"/"<<Month<<"/"<<Year<<endl;
      cout<<"ACCOUNT NUMBER : "<<Retrive_AC<<endl;
      char Retrive_cust_name[30];
      char Address[60];
      float Balance;
      strcpy(Retrive_cust_name,newREC.GetName(Retrive_AC));
      strcpy(Address,newRECa.GetAddress(Retrive_AC));
      Balance=newREC.Get_BAl(Retrive_AC);
      cout<<"Customer Name : "<<Retrive_cust_name<<endl;
      cout<<"Customer Address : "<<Address<<endl;
      cout<<"Bank Balance : "<<Balance<<endl;
      float Interest_Accured;
      Intrest_Accured=Get_Interest(Retrive_AC,Balance);
      cout<<"\n\t\t\t Interest Generated : "<<Interest_Accured<<endl;
      getch();
      Balance=Balance+Interest_Accured;
      Display_Record obj2;
      // Updating the balance after(added the interest once in year)
      obj2.Update_Bal(Retrive_AC,Balance);
      // Adding Interest as a Deposit when it is generated in a Year
      Add_Details(Retrive_AC,Day,Month,Year,'D',"INTEREST",Interest_Accured,Interest_Accured,Balance);
 }
 //This Method Does all the Deposit/withdran in transaction.dat file
 void AC_Transactions::Transaction(void)
 {
     clrscr();
     char T_AC[10];
     int Trans_AC,Retrive_AC,check;
     cout<<"\n\n Press '0'to Go back to Previous Menu \n\n";
     cout<<"\n To View the Transaction of ACCOUNT ,Please Enter the ACCOUNT NUMBER : \n\n";
     gets(T_AC);
     Trans_AC=atoi(T_AC);
     Retrive_AC=Trans_AC;
     if(Retrive_AC==0)
     {
         return();
     }
     clrscr();
     Display_Record newREC;
     if(!newREC.AC_exists(Retrive_AC))
     {
         cout<<"\nACCOUNT doesn't Exists\n"<<endl;
         getch();
         return();
     }
     cout<<"Press'0'to Go back to Previous Menu\n"<<endl;
     cout<<"\t\t Make Correct Entry for Transaction Below : \t\t";
     cout<<"--------------------------------------------------------------\n";
     int Day,Month,Year;
     struct Date Date_val;
      getdate(&Date_Val);
      Day=Date_val.DD;
      Month=Date_val.MM;
      Year=Date_val.YY;
      cout<<"Date"<<Day<<"/"<<Month<<"/"<<Year<<endl;
      cout<<"ACCOUNT NUMBER : "<<Retrive_AC<<endl;
      char Retrive_cust_name[30];
      char Address[60];
      float Balance;
      float Interest_Accured=0.0;
      strcpy(Retrive_cust_name,newREC.GetName(Retrive_AC));
      strcpy(Address,newRECa.GetAddress(Retrive_AC));
      Balance=newREC.Get_BAl(Retrive_AC);
      cout<<"Customer Name : "<<Retrive_cust_name<<endl;
      cout<<"Customer Address : "<<Address<<endl;
      cout<<"Bank Balance : "<<Balance<<endl;
      char transDetails,Type_Trans[10],TM[10];
      float T_Amount,T_AMT;

      do
      {
          cout<<"Please Enter D or W for withdrawl of Amount"<<endl;
          transDetails=getche();
          if(transDetails=='0')
          {
            cout<<"You have pressed '0' to Exit"<<endl;
            getch();
            return();
          }
          transDetails=toupper(transDetails);
      }
      while(transDetails != 'W'&& transDetails !='D')

      do
      {
          cout<<"\n The Transaction type is\n1)Cash\n  or\n2)Cheque\n";
          check=1;
          cout<<"(Cash/Cheque)";
          gets(Type_Trans);
          strupr(Type_Trans);
          if(Type_Trans[0]=='0')
          {
              cout<<"\n\n You have '0' to Exit \n"<<endl;
              getch();
              return();
          }
          if(strlen(Type_Trans)<1 || (strcmp(Type_Trans,"CASH") && (strcmp(Type_Trans,"CHEQUE")))
          {
              check=0;
              cout<<"\n The Transaction is INVALID,Please enter Either Cash or Cheque"<<endl;
              getch();
          }
        } while(!check);

          do
          {
              cout<<"\n Please Enter the Transaction Amount \n"<<endl;
              check=1;
              cout<<" Amount : RS.";
              gets();
              T_AMT=atof(TM);
              T_Amount=T_AMT;
              if(T_Amount<1 || (TransDetails=='W '&& T_Amount>Balance))
                 {
                  check=0;
                    cout<<"\n Either Amount is not a Numeric value or \n It is Blank or\n You are trying to withdraw more than in the Account-----\n)";
                    getch();
                 }
          }
          while(!check);
          char choice;
          do
          {
              cout<<"\n Save the Changes made in the Transaction Details ?(Yes/No):";
              choice=getche();
              choice=toupper(choice);
          }
          while(choice!='N' || choice !='Y');
          if(choice=='N' || choice=='n')
          {
              cout<<"The Transaction is not Saved "<<endl;
              getche();
              return();
          }
          if(tansDetails=='D')
          {
              cout<<" \n The Amount is  Deposited in the Bank Account"<<endl;
              getch();
              Balance=Balance+T_Amount;
          }
          else
          {
              cout<<"\nThe Amount is Withdrawn from the Bank Account"<<endl;
              getch();
              Balance=Balance-T_Amount;
          }
          newREC.Update_Bal(Retrive_AC,Balance);
          //Adding record details for transaction to be done and saving in the file
          Add_Details(Retrive_AC,Day,Month,Year,transDetails,Type_Trans,Interest_Accured,T_Amount,Balance);
      }
//This method deletes the account from both dat files
void AC_Transactions::Close_Ac(void)
{
  clrscr();
     char T_AC[10];
     int Trans_AC,Retrive_AC;
     cout<<"\n\n Press '0'to Go back to Previous Menu \n\n";
     cout<<"\nPlease Enter the ACCOUNT NUMBER you want to Close\n";
     gets(T_AC);
     Trans_AC=atoi(T_AC);//changing AC number to integer type
     Retrive_AC=Trans_AC;
        clrscr();
        Display_Record newREC;
     if(!newREC.AC_Exists(Retrive_AC)
     {
         cout<<"\t\n You have Entered INVALID ACCOUNT NUMBER \t\n";
         cout<<"\nPlease Try Again"<<endl;
         getch();
         return();
     }

     cout<<"Press'0'to Go back to Previous Menu\n"<<endl;
     cout<<"\t** Closing the ACCOUNT **\t"<<endl;
     cout<<"--------------------------------------------------------------\n";
     int Day,Month,Year;
     struct Date Date_val;
      getdate(&Date_Val);
      Day=Date_val.DD;
      Month=Date_val.MM;
      Year=Date_val.YY;
      cout<<"Date"<<Day<<"/"<<Month<<"/"<<Year<<endl;
      char choice;
      newREC.Display(Retrive_AC);

          do
          {
              cout<<"\n Are you Sure to close this ACCOUNT ?(YES/NO)"<<endl;
              choice=getche();
              choice=toupper(choice);
          }
          while(choice!='N' || choice !='Y');
          if(choice=='N' || choice=='n')
          {
              cout<<"The ACCOUNT is not Closed "<<endl;
              getch();
              return();
          }
          newREC.Delete_AC(Retrive_AC);
          Delete_Ac(Retrive_AC);
          cout<<"\n\n \t\t\t Record Deleted Successfully"<<endl;
          cout<<"Please Continue with the Application...."<<endl;
          getch();
}
          //The Login Method checks for the user name and Password for accessing the banking application
          int Login(void)
          {

              char Username[9],ch;
              char Username1[]="Banking";
              int i=0;
              char a,b[9],pass[]="TATA_HILL";
              cout<<endl<<endl;
              cout<<"\n\t\t Login to the Banking Application\t\t\n";
              cout<<"*********************************************";
              cout<<endl<<"\n Please Enter the Username :"<<endl;
              cin>>Username;
              cout<<"\n\n Please Enter the Passcode to Authenticate yourself\n"<<endl;
              fflush(stdin);
              do
              {
                  ch=getch();
                  if(isalnum(ch))
                  {
                      b[i]=ch;
                      cout<<"*";
                      i++;
                  }
                  else if(ch=='\r')
                  {
                    b[i]='\0';
                  }
                  else if(ch=='\b')
                  {
                      i-;
                      cout<<"\b\b";
                  }
                }
                while(ch!='\r');
                b[i]='\0';
                fflush(stdin);
               if((strcmp(b,pass)==0)&& (strcmp(Username1,Username)==0))
               {
                   cout<<"\n\n \t You have Entered Successfully \n\n";
                   return(1);
               }
               else
               {
                   cout<<"\n\n Incorrect Username or Passcode\n";
                   return(0);
               }
              }

void main(void)
{
 clrscr();
 int val,ch ;
 a:val=login();
 if(val==0)
 {
     cout<<"\n\t  Want to try again ? \t\n";
     cout<<"\t   1) Try Again \n 2)Exit \t\n");
     cout<<"\n\t Enter your choice and press Enter \t\n";
     cin>>ch;
     if(ch==1)
     {
         clrscr();
         goto a;
     }
     else
     {
         exit(0);
     }
 }
 Menu obj;
 obj.showmenu();
}
