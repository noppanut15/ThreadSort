#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>

using namespace std;

const char *inputFile = "unsorted_data.txt";

void alignment(){
    printf("\t");
}

void bubble_sort(int threadId, vector<int>& vec){
    printf("\tThread[%d]‐‐started\n", threadId);
    sleep(2);
    int temp;
    int start = 0;
    int end = vec.size();
    for(int i = start; i < end; i++){
        for(int j = start; j < end - i - 1; j++){
            if(vec[j] > vec[j + 1]){
                temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
    printf("\t\t\t\tThread[%d]‐‐finished\n", threadId);
}

int getNumberOfLinesInFile(const char *fileName){

    FILE *fp;                           

    int i = 0, lines = 0, temp;
    char ch;

    fp = fopen (fileName, "r");
    while ( fscanf (fp, "%d", &temp) != EOF ) { lines++; }
    fclose (fp);
    return lines;
}

void printOneTwoSeparate(vector<int>& one, vector<int>& two){
    alignment();
    cout<< "[  ";
    for (int i = 0; i < one.size(); i++)
        cout << one[i] << " ";
    cout<<" ]\t";
    cout<< "[  ";
    for (int i = 0; i < two.size(); i++)
        cout << two[i] << " ";
    cout<<" ]";
    cout<<endl;
}

void printTheValues(vector<int>& vec){
    alignment();
    cout<< "[  ";
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout<<" ]";
    cout<<endl;
}

int main()
{
    int i, j;
    int start, mid, end;
    int numberOfElements = getNumberOfLinesInFile(inputFile);
    int a[numberOfElements];

    // -- Fetch data from an input file to the program memory -----------------------------
    FILE *fp;
    fp = fopen (inputFile, "r");
    i = 0;
    while ( fscanf (fp, "%d", &a[i]) != EOF ) { i++; }
    fclose (fp);
    // ------------------------------------------------------------------------------------

    start = 0;
    mid = numberOfElements / 2;
    end = numberOfElements - 1;
    vector<int> vec(a, a + numberOfElements);                   // Store an array on a vector
    printf("Unsorted Data:\n"); printTheValues(vec);

    // -- Separate values -----------------------------------------------------------------
    vector<int> one (vec.begin() + start, vec.begin() + mid);
    vector<int> two (vec.begin() + mid, vec.begin() + end + 1);
    printf("\nSTEP 1: Separate a list:\n"); printOneTwoSeparate(one, two);

    // -- Sort the separated values -------------------------------------------------------
    printf("\nSTEP 2: Simultaneously sort the separated values:\n");
    thread first(bubble_sort, 1, ref(one));
    thread second(bubble_sort, 2, ref(two));
    first.join();
    second.join();
    printf("The result:\n"); printOneTwoSeparate(one, two);    

    // -- Merge the sorting result --------------------------------------------------------
    printf("\nSTEP 3: Merge the results:\n");
    i = 0;
    j = 0;
    int index = start;
    while (i < one.size() && j < two.size())
    {
        if (one[i] < two[j])
            vec[index ++] = one[i ++];
        else 
            vec[index ++] = two[j ++];
    }
    // merge the left-over elements
    while (i < one.size())
        vec[index ++] = one[i ++];
    while (j < two.size())
        vec[index ++] = two[j ++];

    // -- Print the result ----------------------------------------------------------------
    printTheValues(vec);
    // ------------------------------------------------------------------------------------

    return 0;
}