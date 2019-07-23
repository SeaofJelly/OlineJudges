#include <iostream>
using namespace std;
int main()
{
	int f,n,r,m,l = 0,t = 0;
	cin >> n;int a[n];r = n-1;
	for(int i = 0; i < n ; i++)
	cin >> a[i];
	cin >> f;
	while (l <= r)
	{
		m = (r - l) / 2 + l;
		cout << "m:" << m << "r:" << r << "l:" << l << "\n";
		if (a[m] > f)
		r = m-1;
		else
		if (a[m] < f)
		l = m+1;
		else
		{
			m++;
			t = 1;
			cout << "Found : a[" << m << "]" << endl;
			break;
		}
	}
	if (!t)
	return -9527;
	return 0;
}
