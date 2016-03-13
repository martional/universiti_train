#pragma once
#include "information.h"
#include <iostream>
using namespace std;

class Product :
	public Information
{

private:
	int price_unit; // gheymat har vahed kala
	char size [8]; // size kala
	int min_product;//min kala yi ke bayad dar anbar bemanad
	int max_product;//max kala yi ke bayad dar anbar bemanad
	int total;//total= meghdar avvaliyeh + voroodi
	
public:
	friend class Store_House; //in class ba class Store_House friend ast
	void GetInformation();//for get product information
	void Showinformation();// for show product information
	

	Product (void);
	~Product (void);
};











