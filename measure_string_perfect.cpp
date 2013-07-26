#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

int perfect(std::string &s)
{
	int count_ch[26] = {0};

	std::string::iterator it = s.begin();
	for ( ; it != s.end(); it++ )
	{
		char ch = *it;
		if (! isalpha(ch))
		{
			continue;
		}

		if (isupper(ch))
		{
			ch += 32;	
		}

		std::cout << ch << std::endl;

		switch (ch)
		{
			case 'a':
			{
			      ++count_ch[0];
				  break;
			}
			case 'b':
			{
				++count_ch[1];
				break;
			}
			case 'c':
			{
				++count_ch[2];
				break;
			}
			case 'd':
			{
				++count_ch[3];
				break;
			}
			case 'e':
			{
				++count_ch[4];
				break;
			}
			case 'f':
			{
				++count_ch[5];
				break;
			}
			case 'g':
			{
				++count_ch[6];
				break;
			}
			case 'h':
			{
				++count_ch[7];
				break;
			}
			case 'i':
			{
				++count_ch[8];
				break;
			}
			case 'j':
			{
				++count_ch[9];
				break;
			}
			case 'k':
			{
				++count_ch[10];
				break;
			}
			case 'l':
			{
				++count_ch[11];
				break;
			}
			case 'm':
			{
				++count_ch[12];
				break;
			}
			case 'n':
			{
				++count_ch[13];
				break;
			}
			case 'o':
			{
				++count_ch[14];
				break;
			}
			case 'p':
			{
				++count_ch[15];
				break;
			}
			case 'q':
			{
				++count_ch[16];
				break;
			}
			case 'r':
			{
				++count_ch[17];
				break;
			}
			case 's':
			{
				++count_ch[18];
				break;
			}
			case 't':
			{
				++count_ch[19];
				break;
			}
			case 'u':
			{
				++count_ch[20];
				break;
			}
			case 'v':
			{
				++count_ch[21];
				break;
			}
			case 'w':
			{
				++count_ch[22];
				break;
			}
			case 'x':
			{
				++count_ch[23];
				break;
			}
			case 'y':
			{
				++count_ch[24];
				break;
			}
			case 'z':
			{
				++count_ch[25];
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	// bubble_sort
	for (int i = 25; i > 0; i--)
	{
		for (int j = 25; j > 25 - i; j--)
		{
			if (count_ch[j] > count_ch[j-1])
			{
				int tmp = count_ch[j];
				count_ch[j] = count_ch[j-1];
				count_ch[j-1] = tmp;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < 26; i++)
	{
		if (count_ch[i] > 0)
		{
			sum += count_ch[i] * (26 - i);	
		}
	}

	return sum;
}

int main()
{
	std::string str = "adddb";
	int sum = perfect(str);

	std::cout << "sum: " << sum << std::endl;

	return 0;
}
