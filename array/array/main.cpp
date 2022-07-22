//
//  main.cpp
//  array
//
//  Created by jason on 20/07/2022.
//

#include <iostream>
#include<fstream>
#define num 176009
#define numAfterClean 175561
using namespace std;
#include<ctime>

struct Array
{
    string* arr;
    int size;

    Array()
    {
        arr = nullptr;
        size = 0;
    }

    Array(int newSize)
    {
        size = newSize;
        arr = new string[size];
    }

    string& operator[](const int& index)
    {
        return arr[index];
    }
    
    int partition(const int& start, const int& end)
    {
        int mid = (end + start) / 2;
        string pivot = arr[mid];

        swap(arr[mid], arr[start]);

        int last = start + 1;

        for (int i = start + 1; i <= end; i++)
        {
            if (arr[i] < pivot)
                swap(arr[last++], arr[i]);
        }

        swap(arr[start], arr[last - 1]);

        return last - 1;
    }

    void quick(const int& start, const int& end)
    {
        if (start < end)
        {
            int pivot = partition(start, end);
            quick(start, pivot - 1);
            quick(pivot + 1, end);
        }
    }

    void quick()
    {
        quick(0, size - 1);
    }
    
    void add(Array &arr, string newLine)
    {
        arr.size++;
        arr[arr.size - 1] = newLine; // push_back or append
        
        //sort
        arr.quick();
    }
    
    void remove(Array &arr, int removePos)
    {
        for (int i = removePos; i < arr.size - 1; ++i)
            arr[i] = arr[i + 1];
        arr.size --;
    }
    
    ~Array()
    {
        if (arr)
            delete[] arr;
    }
    
};

void OutFileFromArray(fstream &out, Array &a)
{
    for (int i = 1; i < a.size; i++) {
        int firstLetter = int(a[i][0]);
        if (
            (firstLetter <= 122 && firstLetter >= 97)
            ||
            (firstLetter <= 90 && firstLetter >= 65)
            )
            out << a[i];
        else
        {
            continue;
        }
    }
}

int binarySearch(Array &arr, int l, int r, string x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
  
        // If the element is present at the middle
        // itself
        string traversal = arr[mid].substr(0, arr[mid].find(','));
        if (traversal == x)
            return mid;
  
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (traversal > x)
            return binarySearch(arr, l, mid - 1, x);
  
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
  
    // We reach here when element is not
    // present in array
    return -1;
}

string Input()
{
    string input;
    cout << "\nInput : ";
    getline (cin, input);
    
    return input;
}

int main() {
    clock_t start, end;
    start = clock();
//Load
    Array arr(num);
    std::fstream in("/Users/jason/Downloads/19127517/19127517/OPTED-Dictionary.csv");
    if (in)
    {
        for (int i=0; i<num; i++)
        {
            getline(in, arr[i], '\n');
        }
    }in.close();
    
    arr.quick();
//Search
    cout<< "SEARCHING..";
    string lookUp = Input();
    int pos = binarySearch(arr, 0, num - 1, lookUp);
    (pos == -1)
            ? cout << "Element is not present in array"
            : cout<< arr[pos];
//Add
    cout<< "ADDING..";
    string lineUWannaInsert = Input();
    arr.add(arr, lineUWannaInsert);
//Delete
    cout<< "DELETING..";
    string wordUWannaDelete = Input();
    int removePos = binarySearch(arr, 0, arr.size - 1, wordUWannaDelete);
    arr.remove(arr, removePos);
//Edit
    string edit = Input();
    int posEdit = binarySearch(arr, 0, num - 1, edit);
    arr[posEdit] = edit;
//Save
    cout<< "SAVING..";
    fstream outt("/Users/jason/Downloads/array/array/array.csv");
    if (outt)
        OutFileFromArray(outt, arr);
    outt.close();
    
    end = clock();
    cout << (double(end - start) * 1000) / double(CLOCKS_PER_SEC)<<endl;
    return 0;
}
