#include <iostream>
using namespace std;

int mgs(double *t,int s,int e)
{	
	int mid = (s+e) / 2;
	int l1 = mid - s + 1 , l2 = e - mid , lp = 0 , rp = 0 ;
	double l[l1] , r[l2] ;
	for (int i = s , f = 0 ; f < l1 ; f ++ , i ++ )
	l[ f ] = t [ i ] ;
	for (int i = mid + 1 , f = 0 ; f < l2 ; f ++ , i ++ )
	r[ f ] = t [ i ] ;
	while (lp < l1 && rp < l2)
	{
		if (l[lp] > r[rp]){
			t[s] = r[rp];
			rp++;
		}
		else
		{
			t[s] = l[lp];
			lp++;
		}
		s++;
	}
	if ( lp < l1 )
	{
		for (int i = lp , j = s ; i < l1 ; s ++ , i ++)
		t[s] = l[i];
	}
	else
	{
		for (int i = rp , j = s ; i < l2 ; s ++ , i ++)
		t[s] = r[i];
	}
	return 0;
}

int mg(double *t,int s,int e)
{	
	int mid = (s+e)/2 ;
	if (e == s)
	return 0;
	mg(t,s,mid);
	mg(t,mid+1,e);  // when s==e+1, the length of the block is 2, where the split should continue no more.
	mgs(t,s,e);     // so when s==e+1, the next time is all return derectly, as the recursion ends up here;
	return 0;
}

int main()
{
	int n , i = 0;
	cin >> n;
	double t[n] ;
	for (; i < n ; i ++)
	cin >> t[i];
	mg(t,0,i-1);
	for (int o = 0; o < i ; o ++){
		cout << t[o] << "\t" << o+1 << endl ;
	}
	return 0;
}


// Other Condition
/* 
 #include <iostream>
 
 using namespace std;
 
 void merge(int*arr, int p, int q, int r)
 {
     int n1 = q - p + 1;
     int n2 = r - q;
 
     int* L = new int[n1];
     int* R = new int[n2];
 
     for(int i = 0; i < n1; i++)
     {
         L[i] = arr[p + i];
     }
     for(int j = 0; j < n2; j++)
     {
         R[j] = arr[q + j + 1];
     }
 
     int i = 0;
     int j = 0;
     int k = p;
 
     while((i < n1) && (j < n2))
     {
         if(L[i] <= R[j])
         {
             arr[k] = L[i];
             i++;
         }
         else
         {
             arr[k] = R[j];
             j++;
         }
         k++;
     }
 
     if (i < n1)
     {
         for(; i < n1; i++, k++)
         {
             arr[k] = L[i];
         }
     }
     if (j < n2)
     {
         for(; j < n2; j++, k++)
         {
             arr[k] = R[j];
         }
     }
 }
 
 void mergesort(int* arr, int p, int r)
 {
     int q = 0;
     if(p < r)
     {
         q = (p + r) / 2;
         mergesort(arr, p, q);
         mergesort(arr, q + 1, r);
         merge(arr, p, q, r);
     }
 }
 
 int main()
 {
     int a[] = {5, 2, 4, 7, 1, 3, 2, 6};
     mergesort(a, 0, 7);
     for(int i = 0; i < 8; i++)
     {
         cout << a[i] << " ";
     }
     cout << endl;
     return 0;
 } */
