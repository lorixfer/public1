
#include "random.h"
#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;

double funct(double x){
    return (M_PI/2) *cos((M_PI * x) / 2);
}

int main(){

    Random rnd;

    //settaggio del seed nella variabile Random rnd
    //  2892 2587
    //  0000 0000 0000 0001

    int p1 = 2892;
    int p2 = 2587;
    int seed[] = {0000 , 0000 , 0000 , 0001};
    rnd.SetRandom( seed, p1 , p2 );

    //inizio esercizio
    //Calcolo integrale 
    // pi/2 cos(pi x /2)    in dx from 0 to 1

    int N = 10000;  //numero di punti sui quali farò la media
    double summ = 0;
    double summ_err = 0;
    double ran;
    double integral;
    double error;

    for(int i = 0 ; i < N ; i++){
        ran = rnd.Rannyu();
        summ = summ + funct(ran);
        summ_err = summ_err + ( pow(funct(ran) , 2 ) -1 );
    }

    integral = summ / double(N);
    error = summ_err / sqrt(double(N) );

   cout << "il valore stimato dell'integrale è: " << integral << endl;
   cout << "l'errore stimato è:   " << error <<endl;

   //calcolo l'integrale usando l'importance sempling

   

    return 0;
}