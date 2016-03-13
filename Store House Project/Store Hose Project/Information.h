#pragma once
#include <string>
class Information
{


protected:
	char name[20];  // moshtarak beyn tamam kelas haye farzand
	char address[50]; //moshtarak beyn store house va buyer_seller
	char phonenumber[15]; //moshtarak beyn store house va buyer_seller
	 

	 
public:
	int Question_sure();   // in tabe baraye soli ast ke dar tamam farzand ha hast
	virtual void GetInformation()=0; //in tabe virtual tarif shode va dar hameye fazand ha badaneh tarif shode

	Information(void);
	~Information(void);
};

