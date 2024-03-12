#include <iostream>
#include <fstream>
#include <ostream>
//#include <string>
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

    int N= 100000;
    double vec_ran_exp[N];

    for( int i = 0 ; i < N ; i++){
        vec_ran_exp[i] = rnd.CaLo(3, 1);
    }

    ofstream myfile;
    myfile.open("data.txt");
    for (int i=0; i<N ; i++ ) {
        myfile << vec_ran_exp[i] << endl;
    }
    myfile.close();

    return 0;
}