#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "random.h"
//#include <cmath>

using namespace std;

Random setted_random(){

    Random rnd;

// Fixing random seed to allow reproducibility

    int seed[4];
    int p1, p2;

// Reading of the primes for seed impostation from file "Primes"

    ifstream Primes("Primes");
    if (Primes.is_open()){
        Primes >> p1 >> p2;
    }
    else {
        cerr << "PROBLEM: Unable to open Primes" << endl;
    }
    Primes.close();

//  Fixing the seed in random
// The seed.in file is basically:
//      RANDOMSEED	0000 0000 0000 0001
// but can be changed to accomodate other seed


    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while( !input.eof() ){
            input >> property;
            if ( property == "RANDOMSEED"){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd.SetRandom( seed, p1 , p2 );           //call of the function to set the seed
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

// Now that I setted the random seed I can generate the
// same (pseudo)random sequence every time I lounch the 
// program.

    return rnd;
    
}

int main(){

    Random rnd;
    rnd = setted_random();

    //PROVA DELL'ALGORITMO, DA ELIMINARE

    // int N= 1000;
    // double vec_ran_exp[N];

    // for( int i = 0 ; i < N ; i++){
    //     vec_ran_exp[i] = rnd.CaLo(3, 10);
    // }

    // ofstream myfile;
    // myfile.open("data.txt");
    // for (int i=0; i<N ; i++ ) {
    //     myfile << vec_ran_exp[i] << endl;
    // }
    // myfile.close();

    //FINE PROVA ALGORITMO

    // x_i = variabile dandom distribuita linearmente , esponenzialmente , CL
    // S_N = sommma di 1000 variabili x_i della stessa distribuzione 

    int N[] = {1 , 2 , 10 , 100};
    int n_sample = 10000;
    string s[] = { "Lin" , "Exp" , "C_L"};
    string name_file;
    string file_ext = ".txt";
    double S_N = 0;
    double summ;

    //declaration of mean ando others quantity for the distribution
    double lambda = 1;
    double C_L_mu = 0;
    double C_L_Gamma = 1;



    ofstream myfile;

    //the strange expression is because sizeof(N) return the size in byte of
    //the array, so it has to be divided by the size of the data type it contain.
    for( int n=0 ; n < int (sizeof(N) / sizeof(int)) ; n++ ){  

        name_file = s[0] + to_string(N[n]) + file_ext ;        //declaration of name of file in the fation Lin #number_summed .txt
        myfile.open( name_file );

        for (int i = 0 ; i < n_sample ; i++ ) {
            summ = 0;

            for (int j = 0 ; j<N[n] ; j++ ) {
                summ = summ + rnd.Rannyu();     //summing in N[n] random variables
            }
            S_N = summ / N[n];

            myfile << S_N << endl;      //writing the result in the file
        }
        
        myfile.close();                 //closure of the file 

    }


    //the strange expression is because sizeof(N) return the size in byte of
    //the array, so it has to be divided by the size of the data type it contain.
    for( int n=0 ; n < int (sizeof(N) / sizeof(int)) ; n++ ){  

        name_file = s[1] + to_string(N[n]) + file_ext ;        //declaration of name of file in the fation Expo #number_summed .txt
        myfile.open( name_file );

        for (int i = 0 ; i < n_sample ; i++ ) {
            summ = 0;

            for (int j = 0 ; j<N[n] ; j++ ) {
                summ = summ + rnd.Expo(lambda);     //summing in N[n] random variables
            }
            S_N = summ / N[n];

            myfile << S_N << endl;      //writing the result in the file
        }
        
        myfile.close();                 //closure of the file 
    }


    //the strange expression is because sizeof(N) return the size in byte of
    //the array, so it has to be divided by the size of the data type it contain.
    for( int n=0 ; n < int (sizeof(N) / sizeof(int)) ; n++ ){  

        name_file = s[2] + to_string(N[n]) + file_ext ;        //declaration of name of file in the fation CaLo #number_summed .txt
        myfile.open( name_file );

        for (int i = 0 ; i < n_sample ; i++ ) {
            summ = 0;

            for (int j = 0 ; j<N[n] ; j++ ) {
                summ = summ + rnd.CaLo(C_L_mu, C_L_Gamma);     //summing in N[n] random variables
            }
            S_N = summ / N[n];

            myfile << S_N << endl;      //writing the result in the file
        }
        
        myfile.close();                 //closure of the file 
    }

    return 0;
}