#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <ctype.h>

using namespace std;

/**
  * @desc		为进程名或者文件名做转义
  *
  * Parameter: string & str
  *	
  * Returns:	success 0, failed -1
*/
int convert_proc_name(string &str)
{
	string proc_path = str;
	string proc_name;
	bool found = false;

	std::string::size_type pos = str.rfind("/");
	if (pos != std::string::npos)
	{
		proc_name = str.substr(pos + 1);
		
		for (string::size_type s_pos = 0; s_pos != proc_name.size();)
		{
			if (isalnum(proc_name[s_pos]))
			{
				++s_pos;
				continue;
			} else
			{
				found = true;
				proc_name.insert(s_pos, "\\");
				s_pos += 2;
			}
		}
	} else
	{
		return -1;
	}
	if (found)
	{
		str.replace(pos + 1, proc_name.size(),  proc_name);
	} 

	return 0;	
}


int main()
{
	std::string path = "/p###ing";	

	convert_proc_name(path);
  	
	std::string cmd = path + "www.google.com.hk";

	if (execl("/bin/sh", "sh", "-c", cmd.c_str(), (char *)0) == -1)
	{
		cout << "failed " << endl;
	} else
	{
		cout << "success " << endl;
	}

	return 0;	
}
