#include<iostream>
using namespace std;



void print_poly(int* poly,int order_)
{
    string ans="";
    int order = order_-2;
    bool flag=false;
    bool flag2 =false;


    for(int i=0;i<order_-1;i++)
    {

        if(order==0)
        {
            if(poly[i]!=0)
            {

                ans+="+"+to_string(poly[i]);

                flag = true;
            }

        }
        else if(order ==1)
        {
            if(poly[i]!=0)
            {
                if(poly[i] == 1)
                {
                    ans+="+X";
                }
                else if(poly[i] == -1)
                {
                    ans+="-X";
                }
                else
                {
                    ans+="+"+to_string(poly[i])+"X";
                }



                flag = true;
            }

        }
        else
        {
            if(poly[i]!=0)
            {
                if(poly[i] == 1)
                {
                    ans+="+X"+ to_string(order);
                }
                else if(poly[i] == -1)
                {
                    ans+="-X";
                }
                else
                {
                    ans+="+"+to_string(poly[i])+"X"+ to_string(order);
                }



                flag = true;
            }
        }
        order--;


    }

    for(int i=1;i<ans.size();i++)
    {
        if(ans[i]=='+')
        {
            cout<<" + ";
        }
        else
        {
            cout<<ans[i];
        }
    }




    if(flag)
    {
        cout<<" = "<<poly[order_-1]<<endl;

    }
    else
    {
        cout<<0<<endl;
    }




}


void sum_poly(int* poly1 , int* poly2 , int order1,int order2)
{
//    cout<<"debugging here"<<endl;
//    for(int i=0;i<order1+2;i++)
//    {
//        cout<<"i: "<<i<<"   :  "<<poly1[i]<< endl;
//    }
//    cout<<"====================================="<<endl;
//    for(int i=0;i<order2+2;i++)
//    {
//        cout<<"i: "<<i<<"   :  "<<poly2[i]<< endl;
//    }
    int maxi = max(order1,order2)+2;
    int* poly = new int(maxi);
    int mini = min(order1,order2);

    for(int i=0;i<abs(order2-order1);i++)
    {
        if(order1>order2)
        {
            poly[i] = poly1[i];
        }
        else if(order1<order2)
        {
            poly[i] = poly2[i];
        }
    }

    if(order1>order2)
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i+order1-order1] = poly1[i+(order1-order2)]+poly2[i];

        }
    }
    else if(order1<order2)
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i+(order2-order1)] = poly1[i]+poly2[i+(order2-order1)];

        }
    }
    else
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i] = poly1[i]+poly2[i];

        }
    }

//    for(int i=0;i<maxi;i++)
//    {
//        cout<<poly[i]<<' ';
//    }

    cout<<"Sum of polynomials: ";
    print_poly(poly,maxi);

}


void diff_poly(int* poly1 , int* poly2 , int order1,int order2)
{
//    cout<<"debugging here"<<endl;
//    for(int i=0;i<order1+2;i++)
//    {
//        cout<<"i: "<<i<<"   :  "<<poly1[i]<< endl;
//    }
//    cout<<"====================================="<<endl;
//    for(int i=0;i<order2+2;i++)
//    {
//        cout<<"i: "<<i<<"   :  "<<poly2[i]<< endl;
//    }
    int maxi = max(order1,order2)+2;
    int* poly = new int(maxi);
    int mini = min(order1,order2);

    for(int i=0;i<abs(order2-order1);i++)
    {
        if(order1>order2)
        {
            poly[i] = poly1[i];
        }
        else if(order1<order2)
        {
            poly[i] = -poly2[i];
        }
    }

    if(order1>order2)
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i+(order1-order1)] = poly1[i+(order1-order2)]-poly2[i];

        }
    }
    else if(order1<order2)
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i+(order2-order1)] = poly1[i]-poly2[i+(order2-order1)];

        }
    }
    else
    {
        for(int i=0;i<mini+2;i++)
        {
            poly[i] = poly1[i]-poly2[i];

        }
    }
//    for(int i=0;i<maxi;i++)
//    {
//        cout<<poly[i]<<' ';
//    }

    cout<<"Difference of polynomials: ";
    print_poly(poly,maxi);



}











int main()
{
    int order_1st,order_2nd;
    cout<<"Order of first polynomial: "<<endl;
    cin>>order_1st;

    int* poly_1 = new int[order_1st+2];
    for(int i=order_1st+1;i>=0;i--)
    {
        cin>>poly_1[i];
    }

    cout<<"Order of second polynomial: "<<endl;
    cin>>order_2nd;
    int* poly_2 = new int[order_2nd+2];

    for(int i=order_2nd+1;i>=0;i--)
    {
        cin>>poly_2[i];
    }

//    for(int i=0;i<order_1st+2;i++)
//    {
//        cout<<poly_1[i]<<' ';
//    }

    print_poly(poly_1,order_1st+2);
    cout<<endl;
    print_poly(poly_2,order_2nd+2);

    sum_poly(poly_1,poly_2,order_1st,order_2nd);
    diff_poly(poly_1,poly_2,order_1st,order_2nd);


    delete[] poly_1;
    delete[] poly_2;



}