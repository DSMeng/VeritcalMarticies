/*
Program Name: Vertical Matrix 
Date: 2022 - 6 - 3
Author: David Mengele
*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const unsigned SIZE = 20;
const unsigned DISPLAY = 12;

bool readMatrix(int [][SIZE], unsigned&, unsigned&, ifstream&);
void display(int [][SIZE], unsigned, unsigned);
void displaySums(int [][SIZE], unsigned, unsigned, int[SIZE]);
void symmetryCheck(int[], unsigned, unsigned);
void sortMatrix(int [][SIZE], unsigned, unsigned);

int main(){
    unsigned height, width;
    int matrix[SIZE][SIZE], sums[SIZE];

    string filename = "matrixes.txt";
    ifstream infile;

    cout << setprecision(3) << showpoint << fixed;

    infile.open(filename, ios::in);
    if(infile.fail()){
        cout << "File " << filename << " could not be opened." << endl;
        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();    
        exit(1); 
    }

    do{
        if(readMatrix(matrix, height, width, infile))
            break;

        cout << "Input: " << endl;
        display(matrix, height, width);
        displaySums(matrix, height, width, sums);
        symmetryCheck(sums, height, width);
        sortMatrix(matrix, height, width);
        cout << "Sorted: " << endl;
        display(matrix, height, width);

        cout << endl << "Press the enter enter key to continue..." << endl; cin.ignore(); cin.get();
    }while(true);

    return 0;
}

//This function reads the matrixes.txt files
bool readMatrix(int matrix[][SIZE], unsigned& height, unsigned& width, ifstream& infile){

    if(!(infile >> height))
        return true;
    infile >> width;

    for(unsigned row = 0; row < height; row++)
        for(unsigned col = 0; col < width; col++)
            infile >> matrix[row][col];

    return(false);
}

//displays the matrix 
void display(int matrix [][SIZE], unsigned height, unsigned width){
    for(unsigned row = 0; row < height; row++){
        for(unsigned col = 0; col < width; col++)
            cout << setw(DISPLAY) << matrix[row][col];
        cout << endl;
    }   
}

//displays the sum of the different columns
void displaySums(int matrix[][SIZE], unsigned height, unsigned width, int sums[SIZE]){
    for(unsigned col = 0; col < width; col++)
        sums[col] = 0;

    for(unsigned col = 0; col < width; col++)
        for(unsigned row = 0; row < height; row++)
            sums[col] += matrix[row][col];

        cout << "Sums: " << endl;
        for(unsigned col = 0; col < width; col++)
            cout << setw(DISPLAY) << sums[col];
        cout << endl << endl; 

    return;
}

//Checks for vertical additive symmetry 
void symmetryCheck(int sums[], unsigned height, unsigned width){
    cout << "Vertical additive symmetry: " << endl;

    for(unsigned col = 0; col < width / 2; col++){
        float sumLeft = 0, sumRight = 0;
        sumLeft += sums[col];
        sumRight += sums[width - col - 1];

        if(sumLeft != sumRight){
            cout << "No" << endl << endl;
            return;
        }
    }
    cout << "Yes" << endl << endl;
    return;

}

//Uses bubble sort to sort the matrixes.txt
void sortMatrix(int matrix[][SIZE], unsigned height, unsigned width){
    for(unsigned row = 0; row < height; row++)
        for(unsigned col = 0; col < width - 1; col++)
            for(unsigned seek = 0; seek < (width - col - 1); seek++)
                if(matrix[row][seek] > matrix[row][seek + 1]){
                    int temp = matrix[row][seek];
                    matrix[row][seek] = matrix[row][seek + 1];
                    matrix[row][seek + 1] = temp; 
                }
}
