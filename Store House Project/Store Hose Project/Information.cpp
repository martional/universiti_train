#include "Information.h"
#include <string>
#include <iostream>
using namespace std;

Information::Information(void)
{
	

}


int Information::Question_sure()
{
	//gereftan tayid az karbar
	cout << "Are you shure your inputs are true? \n"
		<<"1- Yes \n"
		<<"2- No \n";
		string i;
		cin >> i ;
		if (i == "No" || i== "no" || i=="n" || i=="2")
		{
			return -1;
		}
		else if (i == "Yes" || i== "yes" || i=="y" || i=="1")
		{
			return 1;
		}
}


Information::~Information(void)
{
}
