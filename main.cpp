#include "include/PvZlevely.h"

int main()
{
	console::SetTitle("Plants vs. Zombies");
	int request=0;
	for(;;)
	{
		cout<<"Kterou uroven chcete hrat?"<<endl;
		cin>>request;
		if(request==0)
		{
			break;
		}
		try
		{
			Level(request);
		}
		catch(const char* msg)
		{
			cout<<msg<<endl;
		}
	}
	return 0;
}
