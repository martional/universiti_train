#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#define NULL 0 // tarif null
using namespace std;

Product::Product(void)
{
	//meghdar dehi avalieh
	min_product = NULL;
	max_product = NULL; 
	price_unit = NULL;
	int total = NULL;
	
	
}

void Product::GetInformation() 
{
		//get product information	
		cout << "Enter name of Product: \n";
		cin >> name;
		
		cout << "Enter how many min of save of this Product: \n";
		cin >> min_product;
	
		cout << "Enter how many max of save of this Product: \n";
		cin >> max_product;
	
		cout << "Enter price per unit of your Product: \n";
		cin >> price_unit;
	
	
		cout << "size of your Product: \n";
		cin >> size;
		//gereftan tayid az karbar
		cout<< "___________________________________\n\n"

			<< "-----------------------------------\n";
		cout<< "name: "<< name << endl
			<< "min: " << min_product << endl
			<< "max: " << max_product << endl
			<< "price per unit: " << price_unit << endl
			<< "size: " << size << endl;
		cout<< "-----------------------------------\n"
			<< "____________________________________\n";
		
		
		int i = Question_sure();
		if (i==-1)
		{
			GetInformation();
		}

		else{
			ofstream file("Product.txt",ios::app);// open file for append
			file<<name<<endl;
			file<<total<<endl;
			file<<price_unit <<endl;
			file<<min_product<<endl;
			file<<max_product<<endl;
			file<<size<<endl;
			file<<"----------------------------------------------"<<endl;
			cout <<"successful save! \n";

	file.close();
		}
}

void Product::Showinformation()
{
	string line;
	ifstream file("Product.txt",ios::in);//open file for read
	if(file.is_open())
	{
		cout<< "********************************;\n";
		while(!file.eof())
		{
			getline(file,line);
			{
				//print information
				cout<< "-----------------------------\n" 
				<< "| Name of product: " << line <<" |" << endl;
				
				getline(file,line);
				getline(file,line);
				cout<< "| price per unit of product: " << line << " |" <<endl;
			
				getline(file,line);
				cout<< "| min of product: " << line << " |" <<endl;
				
				getline(file,line);
				cout<< "| max of product: " << line << " |" <<endl;
				
				getline(file,line);
				cout<< "| size: " << line << " |" <<endl;
				
				getline(file,line);
				getline(file,line);
				cout<< "-----------------------------\n";
			}	
		}
	}
	cout<< "********************************\n\n\n\n";
file.close();

}


Product::~Product(void)
{

}








