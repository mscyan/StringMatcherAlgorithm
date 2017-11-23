#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <string>
using namespace std;
int returned_state(const string &P, char c,int q)
{
	string new_string(P, 0, q);
	new_string += c;
	int k = P.length();
	//判断p中连续前k个字符可以作为new_string的后缀
	

	return k ;
}
//对模式P建立状态转移函数
vector<map<int,char>> function_delta(const string &P,const string &charset)
{
	vector<map<int, char>> delta(P.length() + 1);
	int m = P.length();
	int q0 = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < charset.length(); j++)
		{
			int k = returned_state(P, charset[j],q0);
			delta[i][charset[j]] = k;
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
		q0 = delta[i][T[i]];
		if (q0 == P.length())
		{
			return i;
		}
	}
	return -1;
}

//
bool is_subset(const string& P, size_t k, size_t q, char c)
{
	//P = ababaca	q={0,...,P.length()}	c={a,b,c}
	string new_string(P, 0, q);
	new_string = new_string + c;
	/// q = 0 -> q++
	/// a		b		c
	/// aa		ab		ac
	/// aba		abb		abc
	/// abaa	abab	abac
	///	ababa	ababb	ababc
	/// ababaa	ababab	ababac
	/// ababaca	ababacb	ababacc
	for (int i = 0; i != k; ++i)
		if (P[i] != new_string[q + 1 - k + i])
			return false;

	return true;
}
//计算转移函数delta(q,a);
vector<map<char, size_t>> compute_transition_function(const string& P, const string& charac_set)
{
	size_t m = P.size();
	vector<map<char, size_t>> delta(m + 1);

	for (size_t q = 0; q <= m; q++) //q代表着状态
		for (size_t i = 0; i != charac_set.size(); ++i)
		{
			size_t k;// = std::min(m, q + 1);
			if (m <= (q + 1))
				k = m;
			else
				k = q + 1;
			while (!is_subset(P, k, q, charac_set[i]))
				k--; //确定k以使得字符串"P[0...k-1]"是字符串"P[0..q-1]+charac_set[i]"的后缀；

			delta[q][charac_set[i]] = k;
		}
	return delta;
}

//将模式P与文本T匹配，输入模式P在文本T中出现的位置。
void finite_automation_matcher(const string& P, const string& T, const string& charac_set)
{
	size_t q = 0;
	auto delta = compute_transition_function(P, charac_set);

	size_t m = P.size();
	for (size_t i = 0; i != T.size(); ++i)
	{
		q = delta[q][T[i]];

		if (q == m)
			cout << i + 2 - m << endl;
			/*cout << "the pattern starts to occur from the " << i + 2 - m << "th character of Text" << endl;*/
	}
}
int main()
{
	string T = "ababacaabab";
	string P = "aca";
	string s = "abc";
	
	
	finite_automation_matcher(P, T, s);

	cout << endl;
	system("pause");
	return 0;
}
