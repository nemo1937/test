#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int uptime(std::string &up_time)
{
	FILE *fp = popen("uptime", "r");
	
	if (! fp)
	{
		perror("fail popen\n");
		return -1;
	}

	char buf[512] = {0};
	while (fgets(buf, 512, fp) != NULL)
	{
		cout << buf << endl;	
		char day[10] = {0};
		char sys_time[20] = {0};
		char running[20] = {0};
		char uptime[20] = {0};
		char time_unit[20] = {0}; 
		char digtal[10] = {0};
		char user[10] = {0};

		sscanf(buf, "%s %s %s %s %s %s %s", 
			    	day, sys_time, running, uptime, time_unit, digtal, user);
		up_time = uptime;
		up_time += time_unit;
		cout << "up_time " << up_time << endl;
	}

	pclose(fp);

	return 0;
}

int main()
{
	std::string up_time;
	uptime(up_time);

	return 0;
}
