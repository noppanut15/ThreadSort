#include <iostream>
#include <thread>
#include <vector>
#define MAX_ELEMENTS 1000000
using namespace std;

const char *inputFile = "unsorted_data.txt";
const char *outputFile = "sorted_data.txt";

void merge(vector<int>& vec, int start, int mid, int end)
{
    vector<int> one (vec.begin() + start, vec.begin() + mid + 1);
    vector<int> two (vec.begin() + mid + 1, vec.begin() + end + 1);

    int a = 0;
    int b = 0;
    int index = start;
    while (a < one.size() && b < two.size())
    {
        if (one[a] < two[b])
            vec[index ++] = one[a ++];
        else 
            vec[index ++] = two[b ++];
    }

    // merge the left-over elements
    while (a < one.size())
        vec[index ++] = one[a ++];
    while (b < two.size())
        vec[index ++] = two[b ++];
}

void merge_sort(vector<int>& vec, int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    // multi-thread version
    thread first(merge_sort, ref(vec), start, mid);
    thread second(merge_sort, ref(vec), mid + 1, end);
    first.join();
    second.join();

    /*
    // single-thread version
    merge_sort(vec, start, mid);
    merge_sort(vec, mid + 1, end); 
    */

    merge(vec, start, mid, end);
}

int getNumberOfLinesInFile(const char *fileName){

    FILE *fp;                           // File Pointer

    int i = 0, lines = 0, temp;
    char ch;

    fp = fopen (fileName, "r");
    while ( fscanf (fp, "%d", &temp) != EOF ) { lines++; }
    fclose (fp);
    return lines;
}

int main()
{
    int a[MAX_ELEMENTS];
    int i;
    int numberOfElements = getNumberOfLinesInFile(inputFile);

    // Fetch records form a Database file to the program memory
    FILE *fp;   // File Pointer

    fp = fopen (inputFile, "r");
    i = 0;
    while ( fscanf (fp, "%d", &a[i]) != EOF ) { i++; }
    fclose (fp);

    vector<int> vec(a, a + numberOfElements);
    merge_sort(vec, 0, numberOfElements - 1);

    for (int i = 0; i < numberOfElements; i ++)
        cout << vec[i] << endl;

    return 0;
}