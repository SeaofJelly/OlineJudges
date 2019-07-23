#include <stdio.h>

int main()
{
	int n,j,temp;
	scanf ("%d",&n);
	int a[n];
	for (int u = 0;u < n;u++)
	{
		scanf("%d",&a[u]);
	}
	for (int i = 0;i < n;i++)
	{
		temp = a[i];
		j = i - 1;
		for(;j >= 0;--j)
		{
			if (a[j] > temp)
			{
				a[j+1] = a[j];
			}
			else
			break;
		}
		a[j+1] = temp;
	}
	for (int o = 0; o < n;o++)
	{
		printf("%d\t",a[o]);
	}
	return 0;
}
