#include "Buyer_Seller.h"
#include <iostream>
#include <fstream>
#include <string>
#define NULL 0
using namespace std;


Buyer_Seller::Buyer_Seller(void)
{
	
}

void Buyer_Seller::GetInformation()
{
	//get buyer information
	cout << "Enter name of buyer/seller \n";
	cin >> name;

	cout << "Enter phone number of your buyer/seller: \n";
	cin >> phonenumber ;
	
	cout << "Enter enter mobile of our buyer/seller: \n";
	cin >> mobilenumber;

	cout << "Enter enter address of our buyer/seller: \n";
	cin >> address;

	//gereftan tayid az karbar
	cout<< "___________________________________\n\n"

	<< "-----------------------------------\n";
	cout<< "name: "<< name << endl
	<< "phonenumber: "<<phonenumber <<endl
	<< "mobilenumber: " << address << endl
	<< "address: " << address << endl;
			
	cout<< "-----------------------------------\n"
	<< "____________________________________\n";

	int i = Question_sure();
	if (i==-1)
	{
		GetInformation();
	}
	// save information in file
	else{
		ofstream file("phonebook.txt",ios::app);  //open file for append
		file<<name<<endl;
		file<<phonenumber<<endl;
		file<<address<<endl;
		file<<"----------------------------------------------"<<endl;
		cout <<"successful save! \n\n\n";


	file.close();//close file
		}
}

void Buyer_Seller::showinformation()
{
string line;
	ifstream file("phonebook.txt",ios::in);//open file for read
	if(file.is_open())
	{
		cout<< "********************************;\n";
		while(!file.eof())
		{
			getline(file,line);
			{
				//print information
				cout<< "-----------------------------\n" 
				<< "| Name of Buyer/Seller: " << line <<" |" << endl;
	
				getline(file,line);
				cout<< "| Phone numbber of Buyer/Seller: " << line << " |" <<endl;
			
				getline(file,line);
				cout<< "|  Address of Buyer/Seller: " << line << " |" <<endl;
				
				getline(file,line);
				cout<< "-----------------------------\n";
			}	
		}
	}
	cout<< "********************************\n\n\n\n";
file.close();//close file
}


Buyer_Seller::~Buyer_Seller(void)
{
}
