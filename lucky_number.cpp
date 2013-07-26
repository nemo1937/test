#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

bool lucky_number(int n)
{
	int prime[13] = { 2, 3, 5, 7, 11 ,13, 17, 19, 
				   23, 29, 31, 37, 39 } ;

	int n1 = n;
	int sum1 = 0;
	int sum2 = 0;

	while (n1 > 0)
	{
		sum1 += n1 % 10;		
		n1 /= 10;
	}

	bool lucky = true;

	if (sum1 == 1)
	{
		lucky = false;
		goto end;
	}

	for (int i = 0; i < 13; i ++ )
	{
		if (sum1 == prime[i])
		{
			break;
		}

		if (sum1 % prime[i] == 0)
		{
			lucky = false;
			goto end;
		}

		if (sum1 / 2 < prime[i])
		{
			break;	
		}
	}
	
	while (n > 0)
	{
		int t = n % 10;
		n /= 10;
		
		sum2 = sum2 + t * t;
	}

	for (int i = 0 ; i < 13; i ++ )
	{
		if (sum2 == prime[i])
		{
			goto end;
		}

		if (sum2 % prime[i] == 0)
		{
			lucky = false;
			goto end;
		}

		if (sum2 / 2 < prime[i])
		{
			goto end;
		}
	}

end:
	return lucky;
}

int main()
{

	int count_lucky = 0;
	
	for (int i = 1; i < 10000000; i ++)
	{
		if (lucky_number(i))
		{
			std::cout << i << std::endl;
			++ count_lucky; 
		}
	}

	std::cout << "count_lucky is : " << count_lucky << std::endl;
	
	Sleep(9000);

	return 0;
}
