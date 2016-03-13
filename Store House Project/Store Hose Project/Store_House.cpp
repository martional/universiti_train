#include "Store_House.h"
#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#define NULL 0
using namespace std;

Store_House::Store_House(void)
{
	//meghdar dehi avvaliyeh
	number_Product = NULL;
	Initial=NULL;
	total=NULL;
}
	

void Store_House::GetInformation()
{
	//get information
	cout << "Enter name of store house \n";
	cin >> name;

	cout << "Enter phone number of your store house: \n";
	cin >> phonenumber ;
	
	cout << "Enter enter address of your store house: \n";
	cin >> address;

	//greftan tayid az karbar
	cout<< "___________________________________\n\n"

			<< "-----------------------------------\n";
		cout<< "name: "<< name << endl
			<< "phonenumber: "<<phonenumber <<endl
			<< "address: " << address << endl;
			
		cout<< "-----------------------------------\n"
			<< "____________________________________\n\n";


		int i = Question_sure();
		if (i==-1)
		{
			GetInformation();
		}

		else{
		string txt;
		txt = ".txt";
		ofstream file1("Store House.txt",ios::app);//open file for append
		ofstream file2(name + txt,ios::app);//open file for append
		file2<<name<<endl;
		file1<<name<<endl;
		file2<<phonenumber<<endl;
		file1<<phonenumber<<endl;
		file2<<address<<endl;
		file1<<address<<endl;
		file2<<"----------------------------------------------"<<endl;
		file1<<"----------------------------------------------"<<endl;
		cout <<"successful save! \n";
		file2.close();//close files
		file1.close();
		}
}


int Store_House::search_storehouse()
{
	string storehouse = string(name);
	string txt;
	txt = ".txt";
	string line;
	ifstream file(storehouse + txt,ios::in);//open file for read
	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file,line);
			if (name_Product == line)
			{
				getline(file,line);
				int n = atoi(line.c_str());
				Initial = n;
				return 1;// dar in soorat voroodi ra be avalieh ezafe
			}
		}
		file.close();//close file
		return 0;// dar in soorat  nam va tedad voodi ra save kon
	}

	else
	{
		return -1;// error va dadan peygham monasb
	}
}

int Store_House::search_Product()
{
	
	Product base;
	string line;
	ifstream file("Product.txt",ios::in);//open file for read
	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file,line);
			if (line == name_Product)
			{
				getline(file,line);
				getline(file,line);
				base.max_product = atoi(line.c_str());//get min from file
				getline(file,line);
				base.max_product = atoi(line.c_str());//get max from file
				return(1);//anbar tarif shode dar in soorat edame import / export
			}		
		}
	file.close();	
	}
	return(-1);//print anbar tarif nashode
	
}

void Store_House::Import_Product()
{
	//get information
	Product base;
	cout << "Enter name of store house you want enter to: \n";
	cin >> name;
	cout << "Enter Product name: \n";
	cin >> name_Product;
	cout << "Enter How many Product you want enter: \n";
	cin >> number_Product;
	cout << "Enter your Product shelve: \n";
	cin >> Shelves;
	//gereftan meghdar bazgashti tavabe
	int j = search_Product();
	int i = search_storehouse();
	if (j == -1 || i==-1)
	{
		//error ba peygham monaseb
		if (j==-1)
		{
			cout << "The product "<< name_Product <<  " not define !!! \a\n";
		} 
		else
		{
			cout << "Store House "<< name << " not define !!! \a\n";
		}
		Import_Product();
	}
	
	else if (i==0)
	{
		
		string txt;
		txt = ".txt";
		ofstream file(name + txt,ios::app);//open file for read
		file<<name_Product<<endl;
		file<<number_Product<<endl;

		file<<"---------------------------------------------\n"<<endl;
		cout <<"successful save! \n";

		file.close();
	}

	else
	{
		total = number_Product + Initial;
		if (base.max_product> total)
		{
			cout << "Number of your product More from max!!! \n\n\a ";
		}
		
		string txt;
		txt=".txt";
		string house=name + txt;
		const char* home = (house.c_str());//chon tabe remove const char migirad
		string line;
		ifstream file1(name + txt,ios::in);//open file for read
		ofstream file2("no\test.txt",ios::app);//open file for append
		if(file1.is_open())
		{
			while(!file1.eof())
			{
				getline(file1,line);
				file2 << line<< endl;
				if (name_Product == line)
				{
					getline(file1,line);
					file2 << total<<endl;

				}
			}
		}
	cout <<"successful save! \n";
	file1.close();
	file2.close();
	remove(home);//pak kardan
	rename("test.txt",home);//taghyir esm
	}
}

void Store_House::Export_Product()
{
	Product base;
	cout << "Enter name of store house you want enter to: \n";
	cin >> name;
	cout << "Enter Product name: \n";
	cin >> name_Product;
	cout << "Enter number of Product you want Export: \n";
	cin >> number_Product;
	
	int j = search_Product();//daryaft meghdar bazgashti tavabe
	int i = search_storehouse();
	if (j == -1 || i==-1)
	{
		//suitable error 
		if (j==-1)
		{
			cout << "The product "<< name_Product <<  " not define !!! \a\n";
		} 
		else
		{
			cout << "Store House "<< name << " not define !!! \a\n";

		}
	cout << "\n\n Try again.\n\n ";
	Export_Product();
	}

	else if (i==0)
	{
		cout << " The Store House " << name << " havent any " << name_Product << endl;
		Export_Product();
	}
	else
	{
		total = Initial - number_Product;
		if (base.min_product < total)
		{
			cout << "Number of your product under min!!! \n\n\a ";
		}
	
		string txt;
		txt=".txt";
		string house=name + txt;
		const char* home = (house.c_str());//chon tabe romove cont char daryat mikoad
		string line;
		ifstream file1(name + txt,ios::in);//open file for read
		ofstream file2("test.txt",ios::app);//open file for a append
		if(file1.is_open())
		{
			while(!file1.eof())
			{
				getline(file1,line);
				file2 << line<< endl;
				if (name_Product == line)
				{
					getline(file1,line);
					file2 << total<<endl;

				}
			}
		}
	cout <<"successful save! \n";
	file1.close();
	file2.close();//close files
	remove(home);
	rename("test.txt",home);
	}
}

void Store_House::ShowInformation()
{
	//get
	cout << "Enter name of store house you want show: \n";
	cin >> name;
	int i = 0;
	string storehouse = string(name);
	string txt;
	txt = ".txt";
	string line;
	ifstream file(storehouse + txt,ios::in);//open file for reed
	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file,line);
			if (i < 3)
			{
				//print for user
				cout<< "-----------------------------\n" 
				<< "| Name of store house: " << line <<" |" << endl;
				i++;
				getline(file,line);
				cout<< "| Phone number: " << line << " |" <<endl;
				i++;
				getline(file,line);
				cout<< "| Address: " << line << " |" <<endl;
				i++;
				getline(file,line);
				getline(file,line);
				cout<< "-----------------------------\n";
			}
	cout << "| Name of  product: " << line <<" |" << endl;
	getline(file,line);
	cout << "| Number of store house: " << line <<" |" << endl<<endl;
	getline(file,line);
	
			
		}
	}
file.close();

}

Store_House::~Store_House()
{

}


