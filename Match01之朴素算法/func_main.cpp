#include <iostream>
using namespace std;
int NaiveStringMatcher(string T, string P)
{
	for (int i = 0; i < T.length() - P.length(); i++)
	{
		bool ind = true;
		for (int j = 0; j < P.length(); j++)
		{
			if (T[i + j] != P[j])
				ind = false;
		}
		if (ind)
			return i;
	}
	return -1;
}
int main()
{
	string T = "abababbaababaaabbb";
	string P = "bba";

	int index = NaiveStringMatcher(T, P);
	cout << index << endl;

	system("pause");
	return 0;
}