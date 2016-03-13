#include "Product.h"
#include"Store_House.h"
#include"Buyer_Seller.h"
#include <iostream>
using namespace std;

void menu()
{
	Product base1;
	Buyer_Seller base2;
	Store_House base3;

	
	cout <<"************************************************************"<<endl
		 <<"*Enter 1 for define Product OR Store House OR Buyer/Seller:*"<<endl
		 <<"*Enter 2 for Import OR Export from store houses:           *"<<endl
		 <<"*Enter 2 for The information stored:                       *"<<endl
		 <<"*Enter 3 foe exit:                                         *"<<endl      
		 <<"************************************************************"<<endl<<endl<<endl;
	
	int M;
	cin >> M;
	if (M==1)
	{
	cout <<"********************************************************\n"
		 <<"*Enter 1 for define Product defined : 	        	   *\n"
		 <<"*Enter 2 for define store house:                       *\n"
		 <<"*Enter 3 for define Buyer/Seller:                      *\n" 
		 <<"********************************************************\n\n\n\n\n";
	cin >> M;
	if (M==1)
	{
		base1.GetInformation();
		menu();
	}
	else if(M==2)
	{
		base3.GetInformation();
		menu();
	}
	
	else if (M==3)
	{
		base2.GetInformation();
		menu();
	}
	}

	else if(M==2)
	{
	cout <<"*************************************************\n"
		 <<"*Enter 1 for Import product :                   *\n"
		 <<"*Enter 2 for Export product:                    *\n" 
		 <<"*************************************************\n\n\n\n\n";
	cin >> M;

	if (M==1)
	{
		base3.Import_Product();
		menu();
	}
	else if(M==2)
	{
		base3.Export_Product();
		menu();
	}
	}

	else if(M==3)
	{
	cout <<"********************************************************************\n"
		 <<"*Enter 1 for show Product defined : 	                		   *\n"
		 <<"*Enter 3 for show phone number and address Buyer/Seller:           *\n" 
		 <<"*Enter 2 for show How many product in any defined store house:     *\n"
		 <<"********************************************************************\n\n\n\n\n";
	cin >> M;
	if (M==1)
	{
		base1.Showinformation();
		menu();
	}
	else if(M==2)
	{
		base2.showinformation();
		menu();
	}
	
	else if (M==3)
	{
		base3.ShowInformation();
		menu();
	}
	
}	else if (M==4)
	{
		exit(1);
	}
	else
	{
		cout <<"The number you entered not valid!!!\n\n";
		menu();
	}
}

int main()
{
	menu();
	

return 0;
}