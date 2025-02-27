#include <iostream>
#include "OverallClass/Overall.h"
#include "User/UserAnalysis.h"

int main()
{
	UserAnalysis User;
	User.start();
	while (1)
	{
		OverallTimer()->Sleep(1000);
	}
	return 0;
}