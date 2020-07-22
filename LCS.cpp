#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int max(int a, int b){// Utility function to get max of 2 integers
    if (a > b)
        return a;
    else
        return b;
}

int lcs_it(int **C, string X, string Y, int m, int n ) { // return the length of LCS. parameters(Pointer to 2d matrix, 2 strings, 2 length of strings)
    C[m + 1][n + 1]; //setting size of 2d matrix
    for (int i = 0; i <= m; i++) { //fill in 2d matrix by comparing the 2 strings
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                C[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                C[i][j] = C[i - 1][j - 1] + 1;
            else
                C[i][j] = max(C[i - 1][j], C[i][j - 1]);
        }
    }
    cout << "String x = " << X << endl;
    cout << "String y = " << Y << endl;
    return C[m][n];
}

string backtrack(int **C, string X, string Y, int o, int p){ //looks through the matrix, fills in array and return string
    int index = C[o][p];
    char lcs[index+1];    // Create a character array to store the lcs string
    int i = o, j = p;
    while (i > 0 && j > 0)    // one by one store characters in lcs[]
    {
        if (X[i-1] == Y[j-1])// If current character in X and Y are same, then current character is part of LCS
        {
            lcs[index-1] = X[i-1]; // Put current character in result
            i--; j--; index--;
        }
        else if (C[i-1][j] > C[i][j-1])// If not same, then find the larger of two and go in the direction of larger value
            i--;
        else
            j--;
    }
    return lcs;
}

int lcs_it_test(string X, string Y, int m, int n ) { // same method as above but creates a local matrix for storage
    int L[m + 1][n + 1]; // create local 2d matrix
    for (int i = 0; i <= m; i++) { // fill in matrix
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L[m][n];
}

int lcs_re(string X, string Y, int m, int n) { // recursive method to find lcs
    if (( m == 0 ) || ( n == 0 )) // if any string is empty return 0
        return 0;
    else if ( X[m] == Y[n])
        return 1 + lcs_re(X, Y, m-1, n-1);
    else
        return max(lcs_re(X, Y, m, n-1), lcs_re(X, Y, m-1, n));
}

int main() {
    string tempInput;

    cout << "Part 1:" << endl; cout << endl;
    cout << "input first string" << endl;
    cin >> tempInput; // declaring array
    char X[tempInput.length() + 1 ]; // creating array to store string
    strcpy(X, tempInput.c_str()); // copy string to array

    cout << "input second string" << endl;    // repeat for second string
    cin >> tempInput;
    char Y[tempInput.length() + 1 ];
    strcpy(Y, tempInput.c_str());

    const int xLength = strlen(X); // set array length
    const int yLength = strlen(Y);

    int **C=new int*[xLength+1]; // creating pointer to 2d matrix
    for (int i=0; i<xLength+1;++i)
        C[i]=new int [yLength+1];

    int len=lcs_it(C ,X, Y, xLength, yLength); // fill in matrix comparing the 2 strings and store LCS length
    cout << "Length of LCS is: " << len << endl;

    tempInput = backtrack(C, X, Y, xLength, yLength); // store string that the method returns
    cout << "Longest Common sequence is: " << tempInput << endl; cout << endl;

    cout << "Part 2:" << endl; cout << endl;
    string xString = "ACCGTCTTAGCGATCAACACATTTAACAACGCGCCGCACCCCCCGTCAAACGAGCTTTTGGGCTCTTGTCCTTTTACAAGCTTCACGACGCATA"
                     "CAGCCTTGATCAACGGTTTGATCTGTCTCCCTTCAGCTGGCTTTAAAGGACATACATATGAAGGCCTTAATAAGGTCCGGGAACTCCACATATTC"
                     "GGTACTGGGCAAACCCCATGAACCACCTCAACATGAAGAGTCCGAGGACTCTCACGATCCACCAATGCAGATCGGAACTGTGCGATCGCGTAATGA"
                     "GCCGAGTACTTGGTTTGTGTTTAGGTTATGGGGGCCGGGAGCCGGTTCAATATAAGGAAGTAGTTGCAGATTAGTTGTTGCGAACGGTCATAAATTT"
                     "GATGGGTAAACGTGAACTTAACAAACCGTGATAGCTAATCCTATGCATCCCTTACGTGGATCGACTCGAGTACCCAGGTGAACCGACTACTTGATAA"
                     "CCGGAAATCGCGGTATAAAAGCGCTCACGGTCAGGAGATATACCTCCAAGCAGTAGTCTTTCTGAGCCTAGAGTAGTAAATTACAGGGACGATGTCT"
                     "TTTACCGAGGCAACATTTTATTGAGAATCACATGAGGCACAGGTAAAGGCGACATCACGATCGAGATCAACCCCTACTTGTTCAAAACATTGAGAAC"
                     "CAGCTCTGTTTTGGAACCTAGAAAGATAACGCATCCGCTTGATATTCCACGGCTTGTCCCTCTTGTGCGGTCCATCTATCGGAGTTTCCTCCGATACG"
                     "ACCCGCAATGTTTCCAGGCGTACGGTACTTTATGAATACACTCGCGCTGTAACCTGTTATGTGAAACACACACGACAGAGCTTCGCGTGGGCCCAGC"
                     "GACCCGGTAATACTACATCACCGCACACGACCTCGAGCAGTCTTTGCCGGCGTCCGTAAGTAGTCTAAAGTTGTGTTGATGCTTGGGGTTAAAGCTA"
                     "AATCGTCCGCAGAATACGACTCTCATCCCAAT";
    string yString = "ACCCGCACGCGCTTTGGTCTAGATTCTAGCTCCAACTTGCCTGCTAGATACTCTGTTAAAAGATGGTTTTACAACCCCCTCCTCTGTCCCTGGGGTA"
                     "TTATATAATACGTCGGATAGTCAGGTACAAATACAAGTGGGTGGGAATACTTTTCCTCGGATCCTAGACCACGGATTACTGCGTGGTTGACAAGAGTC"
                     "GGCCCGGAGGGAAACGTGAAGGTTAGTGCAATTAAAGTCTCTAATGTGAAGCCTCCGCGAAGCGAGGAGTTTCTGAGATCGAGTACTATTTAGAGTTC"
                     "GAAATCACGGCTTAACCTCACTGCCACGCATAACTTGCCGGCAATCCAGTTTTGCAACGATACTTAATTTGTGCAGCTCATCTTTGCTGTCCAGAAAT"
                     "AGAGCTAGTCGATCTCATCTTGCGGGTAGCCAGAAGTCCTACCGTCTCCTCCATGTAGCTTAAAAATTTCGGTGAGGATCAAAAATGATAAACGTGAC"
                     "AGGTAAGCTCCTACGTCTATCCTATGACCCCCGCGGCAGAATAGGTTGGTAGTGTTAGTGCGTGAGCTGGTAGAATAGAGCACACTTAGGGAAACGGG"
                     "AACCGTTATGTAGGGCTGCGACACACAAAAAAGTGTTCGTTGGTAAGCTGCCTCTCCACTAAACAGGATTTCTCTGGATGATCCCATCGAAGCAAGTT"
                     "ACGCACCACGCCGAGGCGGACCCTGGTACTAGCTGCCCCCCCCTTTATGGGGCGCTCGTACATCAAGATGATCGCGGACTCAACCTGATTACGAGTTG"
                     "TCCAAGTAGTCCAGGGTAAGAGAAACTGGAGAGA";
/* This code is for testing the trial time*/
    cout << "Enter trial time for iterative version (less than min(|X|, |Y|))" << endl;
    int temp;
    cin >> temp;
    for ( int i = 1; i <= temp; i++) { // loop for testing method time from 1-user input
        int start_s = clock();
        int len = lcs_it_test(xString, yString, i, i);
        int stop_s = clock();
        clog << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
    }
    cout << "Enter trial time for recursive version (less than 20)" << endl;
    cin >> temp;
    for ( int i = 1; i <= temp; i++){ // loop for testing method time from 1-user input
        int start_s = clock();
        int len = lcs_re(xString, yString, i, i );
        int stop_s = clock();
        clog << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    }
    return 0; // end main
}