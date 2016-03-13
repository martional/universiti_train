#pragma once
#include "information.h"
class Buyer_Seller :
	public Information
{

private:
	char mobilenumber[15]; //mobile number of buyer


public:
	void GetInformation(); // for get buyer information
	void showinformation();//for show buyer information
	Buyer_Seller(void);
	~Buyer_Seller(void);
};

