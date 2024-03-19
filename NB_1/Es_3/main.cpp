
#include "random.h"
#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;

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
    //Simulazione esperimento di Buffon

    double Length = 1;  //lunghezza dell'ago
    double Height = 1.2;   //altezza delle righe
   
    double pi = 0;

    double y_coord;         //range from -Heig
    double theta_angle;     //range from 0 to pi

    int N_trows = 10000; //numero lanci 
    int N_hit;

    N_hit = 0;

    cout << M_PI <<endl;

    for(int i = 0 ; i < N_trows ; i++){

        //genero la coordinata y e l'angolo randomicamente
        //Y_coord è generato in un range di 0, Height
        //theta_angle è generato tra 0 e pi
        y_coord = rnd.Rannyu() * Height;
        theta_angle = rnd.Rannyu() * M_PI ;
        
        cout << "y: " << y_coord <<endl;
        cout << "t: " << theta_angle <<endl;
        //controllo se il bastoncino ha intersecato la linea
        if( fabs( Height - y_coord ) < fabs( Length * sin(theta_angle) / 2 ) ){
            N_hit ++;
        }
    }
    
    pi = ( 2 * Length * N_trows) / (N_hit * Height);

    cout << "il numero di pi stimato è: " << pi <<endl;

    return 0;
}