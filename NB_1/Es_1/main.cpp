#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "random.h"
#include <cmath>

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

double error(double AV1, double AV2, int n){

	if(n==0){
      return 0;

   }
	else{
		return sqrt( (AV2- pow(AV1, 2) )/ n);
   }

}

int main(){
    
    Random rnd;
    rnd = setted_random();


//es 10.1

// dichiarazione numero di blocchi e numero di lanci per blocco
// che verranno eseguiti

    int N_blocks = 100;
    int N_trows_for_block = 1000;
    double ave_block[N_blocks];
    double ave2_block[N_blocks];
    double delta_sigma_ave_block[N_blocks];
    double delta2_sigma_ave_block[N_blocks];

//riempimento degli arrei con le medie e i quadrati delle
//medie per ogni blocco.
    
    double sum;
    double sum2;
    double provv;

    for (int i = 0 ; i < N_blocks ; i++ ){
        sum = 0;
        sum2 = 0;
        for ( int j = 0 ; j < N_trows_for_block ; j++){
            provv = rnd.Rannyu();                               //generazione variabile random
            sum = sum + provv;                                  //accumulazione valori random
            sum2 = sum2 + pow( provv-0.5 , 2 );            //accumulazione quadrati differenza random - 0.5 (ovvero la media)
        }
        ave_block[i] = sum / N_trows_for_block;                //calcolo del valore medio del blocco
        ave2_block[i] = pow( ave_block[i], 2);
        delta_sigma_ave_block[i] = sum2 / N_trows_for_block;   //array con tutte le delta sigma al quadrato
        delta2_sigma_ave_block[i] = pow( delta_sigma_ave_block[i], 2 );
    }

//calcolo della media e dell'errore cumulativi per la 
//successione dei valori di media trovati precedentemente
//per gli N_blocchi separatamente.

    double sum_ave_prog;
    double sum_ave2_prog;
    double sum_delta_segma_ave_prog;
    double sum_delta2_segma_ave_prog;
    double ave_cumul[N_blocks];
    double ave2_cumul[N_blocks];
    double error_cumul[N_blocks];
    double delta_sigma_ave_cumul[N_blocks];
    double delta2_sigma_ave_cumul[N_blocks];
    double error_cumul_delta_sigma[N_blocks];

    sum_ave_prog = 0;
    sum_ave2_prog = 0;
    sum_delta_segma_ave_prog = 0;
    sum_delta2_segma_ave_prog = 0;

    for(int i = 0 ; i < N_blocks ; i++){

        sum_ave_prog = sum_ave_prog + ave_block[i];
        sum_ave2_prog = sum_ave2_prog + ave2_block[i];
        sum_delta_segma_ave_prog = sum_delta_segma_ave_prog + delta_sigma_ave_block[i];
        sum_delta2_segma_ave_prog = sum_delta2_segma_ave_prog + delta2_sigma_ave_block[i]; 

        ave_cumul[i] = sum_ave_prog / double(i+1);
        ave2_cumul[i] = sum_ave2_prog / double(i+1);
        delta_sigma_ave_cumul[i] = sum_delta_segma_ave_prog / double(i+1);
        delta2_sigma_ave_cumul[i] = sum_delta2_segma_ave_prog / double(i+1);

        error_cumul[i] = error(ave_cumul[i], ave2_cumul[i], i);
        error_cumul_delta_sigma[i] = error( delta_sigma_ave_cumul[i] , delta2_sigma_ave_cumul[i] , i);

    }

//creation of the file data.txt with 
// #trows cumulative_avarage error_on_cumulative_avarage
//this file will be red by the programm 

    ofstream myfile;
    myfile.open("data.txt");

    for (int i=0; i<N_blocks ; i++ ) {
        myfile << N_trows_for_block*(i+1) << " " << ave_cumul[i] << " " << error_cumul[i] << endl;
    }
    myfile.close();

    ofstream myfile2;
    myfile2.open("data2.txt");

    for (int i=0; i<N_blocks ; i++ ) {
        myfile2 << N_trows_for_block*(i+1) << " " << delta_sigma_ave_cumul[i] << " " << error_cumul_delta_sigma[i] << endl;
    }
    myfile2.close();


    //now i will perform a chi-squared test to verify the linear distribution in this way
    //generation of first 10^4 preudo-random number
    //count of the number in the range (0 , 1/ 100) 
    //calculating chi-squared_1 ( n_in_range - expected )^2 / expected
    //generation of second 10^4 pseudo-random number
    //count of the number in the range (1/100 , 2/ 100)
    //calculating chi-squared_2 ( n_in_range - expected )^2 / expected
    // ----repeat the procedure for 100 times -----
    //obtaining the chi-squared by summing all the chi-squared_i.

    rnd = setted_random();

    int n_trows = 10000;
    int M_intervals = 100;
    double avarage_intervals;
    double provvisoria;
    double chi_squared = 0;
    double chi_squared_i = 0;
    double isto_chi_squared[M_intervals];
    int count;

    avarage_intervals = double(n_trows) / double(M_intervals);

    for (int i = 0 ; i < M_intervals ; i++ ) {
        count=0;
        for (int j = 0 ; j<n_trows ; j++) {
            provvisoria = rnd.Rannyu();
            if (provvisoria > double(i)/double(M_intervals) && provvisoria < double(i+1)/double(M_intervals)) {
                count++;
            }
        }

        chi_squared_i = pow(double(count) - avarage_intervals , 2) / avarage_intervals ;
        isto_chi_squared[i] = chi_squared_i ;
        chi_squared = chi_squared + chi_squared_i ;
    }
    
    ofstream myfile3;
    myfile3.open("isto_chi_squared.txt");
    for (int i = 0 ; i<M_intervals ; i++ ) {
        myfile3 << isto_chi_squared[i] << endl;
    }
    myfile3.close();


    cout << "il vlore del chiquadro calcolato è: " << chi_squared << endl;

//saveing seed (optionale)

    rnd.SaveSeed();


    return 0;
}