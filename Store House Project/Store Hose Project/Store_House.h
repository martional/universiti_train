#pragma once
#include "information.h"
#include <string>
class Store_House :
	public Information 
{

private: 
	char name_Product[12];  // name kala
	int number_Product; //tedad voroodi
	int Initial;  //mojoodi avvaliyeh
	int total;  //total= meghdar avvaliyeh + voroodi
	char Shelves [8];  //makan gharar giri kala


public:
	int search_Product(); //barresi aya kala tarif shode va get max , min
	int search_storehouse();//baresi aya anbar ba name voroodi vojood darad
	void GetInformation();//get store house information
	void Import_Product();//Import any product in store house
	void Export_Product();//Export any product in store house
	void ShowInformation();//show product what in store house
	

	Store_House(void);
	~Store_House(void);
};

