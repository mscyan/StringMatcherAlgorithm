#include <iostream>
#include <math.h>
#define q 13
using namespace std;
int Rabin_Karp_String_Matcher(string T, string P)
{
	int m = P.length();
	int k = T.length() - m;
	int result = 0;
	for (int i = 0; i < m; i++)
	{
		result = (int)(P[i]) - 48 + 10 * result;
	}
	cout << result << endl;
	result = result%q;
	int temp_result = 0;
	for (int i = 0; i < k; i++)
	{
		if(i==0)
			for (int j = 0; j < m; j++)
				temp_result = 10 * temp_result + T[i + j] - 48;
		else 
		{
			temp_result = 10 * (temp_result - (pow(10, m - 1))*(T[i - 1] - 48)) - 48 + T[i + m - 1];
		}
		cout << temp_result << endl;
		if (temp_result % q == result)
		{
			bool ind = true;
			for (int j = 0; j < m; j++)
			{
				if (T[i + j] != P[j])
					ind = false;
			}
			if (ind)
				return i;
		}
	}
	return -1;
}
int main()
{
	string T = "124411123124113412";
	string P = "1241";
	int index = Rabin_Karp_String_Matcher(T, P);
	cout << index << endl;

	system("pause");
	return 0;
}
// t(s+1) = 10*(t(s) - 10^(m-1)*T[s+1])+T[s+m+1]