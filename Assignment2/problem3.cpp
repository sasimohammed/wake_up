
#include<iostream>
using namespace std;

string readBinaryString()
{
    string s;
    getline(cin, s);
    string nums = "";
    for (char c:s) {
        if (c == '0' || c == '1')
        {
            nums += c;
        }
    }
    return nums;
}

int countAlternatingParts(const string& nums, int& fir_indx, int& size)
{
    int parts = 0;
    char last;
    bool flag = false;
    size = nums.size();
    for (int i=0;i<size;i++)
    {
        if (nums[i] == '0' && !flag)
        {
            flag = true;
            last = '0';
            fir_indx = i;
            parts++;
        }
        if (nums[i] != last && flag)
        {
            parts++;
            last = nums[i];
        }
    }
    return parts;
}

void convertStringToIntArray(const string& nums, int* arr)
{
    for (int i=0;i<nums.size();i++)
    {
        arr[i] = (nums[i] == '0') ?0:1;
    }
}

void computeSubarrayLengths(const int* arr, int* subarr, int fir_indx, int size, int parts)
{
    int lastt = 0;
    int indxx = 0;
    for (int i=0;i<parts;i++)
    {
        subarr[i] = 0;
    }
    for (int i=fir_indx;i<size;i++)
    {
        if (arr[i] == lastt)
        {
            subarr[indxx]++;
        }
        else
        {
            indxx++;
            subarr[indxx]++;
            lastt = arr[i];
        }
    }
}

int computeAnswer(int* subarr, int parts, int fir_indx, int k)
{
    int ptr = fir_indx;
    int ans = 0;
    bool stopped = false;
    while (ptr<parts && !stopped)
    {
        if (subarr[ptr]%k == 0)
        {
            ans += (subarr[ptr]/k);
            ptr += 2;
            continue;
        }
        else
        {
            if (ptr+2 <= parts-1)
            {
                if (subarr[ptr] <= subarr[ptr+2] && subarr[ptr+1] == k-subarr[ptr])
                {
                    ans += 2;
                    subarr[ptr+2] -= subarr[ptr];
                    ptr += 2;
                    continue;
                }
            }
        }
        stopped = true;
    }
    return stopped ? -1 : ans;
}

int main() {
    string nums = readBinaryString();
    int k;
    cin>>k;

    int fir_indx = 0, size = 0;
    int parts = countAlternatingParts(nums, fir_indx, size);

    int* arr = new int[size];
    convertStringToIntArray(nums, arr);

    int* subarr = new int[parts];

    if (parts == 1)
    {
        subarr[0]= size-fir_indx;
        if (subarr[0]%k == 0)
        {
            cout<<subarr[0]/k<<endl;
        }
        else
        {
            cout<<-1<<endl;
        }
    }
    else
    {
        computeSubarrayLengths(arr, subarr, fir_indx, size, parts);


        int result = computeAnswer(subarr, parts, fir_indx, k);
        cout << result << endl;
    }

    delete[] arr;
    delete[] subarr;
}
