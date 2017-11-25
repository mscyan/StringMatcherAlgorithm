#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <string>
using namespace std;
bool is_substring(const string &P,char c,int q,int k)
{
	string new_string(P, 0, q);
	new_string = new_string + c;
	for (int i = 0; i < k; i++)
	{
		if (P[i] != new_string[q+1-k+i])
			return false;
	}
	return true;
}
vector<map<char,int>> function_delta(const string &P,const string &charset)
{
	int m = P.length();
	vector<map<char,int>> delta(m + 1);
	for (int q = 0; q <= m; q++)
	{
		for (int j = 0; j < charset.length(); j++)
		{
			int k = q+1;
			while (!is_substring(P, charset[j], q, k))
			{
				k--;
			}
			delta[q][charset[j]] = k;
		}
	}
	return delta;
}
int FiniteAutomataMatcher(const string &T, const string &P,const string &charset)
{
	auto delta = function_delta(P,charset);
	int q0 = 0;
	for (int i = 0; i < T.length(); i++)
	{
		q0 = delta[q0][T[i]];
		if (q0 == P.length())
		{
			//此时，i是匹配到最后一位时的位置，所以要减去P的长度加一，以此获取初始位匹配位
			return i-P.length()+1;
		}
	}
	return -1;
}
int main()
{
	string T = "ababacaabab";
	string P = "caaba";
	string s = "abc";
	
	int a = FiniteAutomataMatcher(T, P, s);
	cout << a << endl;
	cout << endl;
	system("pause");
	return 0;
}
