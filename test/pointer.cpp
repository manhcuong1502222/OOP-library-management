#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    int n;
    cout<<"nhap n; "<<endl;
    cin>>n;

    int *p;
    p = new int[n];

    // Nhap tay cac phan tu 

    // for (int i = 0; i < n; i++)
    // {
    //    cout<<"Nhap phan tu thu n: "<<i<<endl;
    //    cin>>*(p+i);
    // }
    
    //Dung ham random
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        *(p+i) = rand()%99 + 1;
    }
    
    // int mang random vua tao

    cout<<"mang random la: "<<endl;
        for (int i = 0; i < n; i++)
    {
        cout<<*(p+i)<<"\t";
    }
    cout<<"\n";

    // mang da sap xep
    cout<<"mang da sap xep la: "<<endl;
    for (int i = 0; i < n-1; i++)
    {
    for (int j = i+1; j < n; j++)
        {
        if (*(p+i)>*(p+j))
            {
            swap(*(p+i),*(p+j));
            }
         
        }
    }
    
    // in kq
    for (int i = 0; i < n; i++)
    {
        cout<<*(p+i)<<"\t";
    }
    
    

    return 0;

}