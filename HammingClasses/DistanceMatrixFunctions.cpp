#include "DistanceMatrixFunctions.h"

using namespace std;


double DistanceMatrixDistance(double** distanceMatrix, double item1, double item2) {

    int driver = 0;
    int left = 0;

    if (item1 >= item2) {//driver the smallest to also work with the instructions
        driver = item2;
        left = item1;
    }
    else {
        driver = item1;
        left = item2;
    }
    return distanceMatrix[driver][left];


    /*inputFile.clear();      //restart
    inputFile.seekg(0, ios::beg);   //data file back from start

    string line;
    string pointStr;
    string GARBAGE;

    inputFile >> GARBAGE;    //read "@metric space"      //NOT NEEDED IF PARAMETERS WORKING
    inputFile >> GARBAGE;    //read "matrix"
    inputFile >> GARBAGE;	//read @item

    int driver = 0;
    int left = 0;

    if (item1 >= item2) {
        driver = item2;
        left = item1;
    }
    else {
        driver = item1;
        left = item2;
    }
    //cout << "BEFORE MAIN GELINE : "  <<genericStr<< endl;
    //cin >> genericStr;
    getline(inputFile, GARBAGE);
    for (int i = 0; i < driver; i++) {
        getline(inputFile, line);
    }
    stringstream linestream(line);
    for (int i= 0 ; i< left; i++ ) {
            getline(linestream, pointStr, '\t');
    }
    return strtod(pointStr.c_str(), NULL);*/
}

void quickSort(double* myArray, int first, int last ){
    int pivot;
    if(first < last){
        pivot = parition(myArray, first, last);
        quickSort(myArray, first, pivot-1);
        quickSort(myArray, pivot+1, last);
    }
}

int parition(double* myArray, int first, int last){
    int  piv = first;
    int pivot = myArray[first];

    for(int i = first+1 ; i <= last ; i++){
        if(myArray[i] <= pivot)
        {
            swap(myArray[i], myArray[piv]);
            piv++;
        }
    }

    swap(myArray[piv], myArray[first]);

    return piv;
}


void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}


