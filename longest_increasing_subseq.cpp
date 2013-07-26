#include <iostream>

using namespace std;

int LIS(int A[], int len)
{
	int *d = new int[len];

	int longest_sub = 1;

	d[0] = 1; 

	for (int i = 0; i < len; i++)
	{
		d[i] = 1;

		for (int j = 0; j < i; j++)
		{
			if (A[i-1] <= A[i] && d[j] + 1 > d[i])
			{
				d[i] = d[j] + 1;
			}
		}

		if (d[i] > longest_sub)
		{
			longest_sub = d[i];
		}
	}


	delete [] d;

	return longest_sub;
}

int main()
{
	int A[] = {5, 3, 4, 8, 6, 7};

	int ls = LIS(A, 6);

	cout << "********************************" << endl;

	std::cout << ls << std::endl;

	return 0;
}

