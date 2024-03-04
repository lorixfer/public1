/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

float error(float AV1, float AV2, int n){

	if(n==0)
		return 0;
	else
		return sqrt( (AV1- (AV2)*(AV2) )/ n );

}
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();


   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;


int N_blocks = 50; //numero blocchi (i blocchi sono intesi in una maniera diversa da quelli che intende il prof)
int N_trows = 200; //numero lanci per ogni blocco
float summ = 0;
float summ2 = 0; //somma dei quadrati
float provvisoria;
float ave_block[N_blocks];
float ave2_block[N_blocks];

//qua costruisco gli array ave_block e ave2_block dove ho 
//il valore medio e il valore medio dei quadrati dei vadi blocchi
//ovvero sessioni di N_trowa lanci.


   for(int j = 0 ; j < N_blocks ; j++){
   
        for(int i = 0 ; i < N_trows ; i++){
        	provvisoria = rnd.Rannyu();
            summ = summ + provvisoria;
            summ2 = summ2 + provvisoria*provvisoria;
        }
        ave_block[j] = summ / N_trows;
        ave2_block[j] = summ2 / N_trows;
		summ = 0;
      summ2=0;
   } 

//ora prendo gli array ave_block e ave2_block e calcolo la media cumulativa e 
//l'errore sulla media cumulativa.
   
   float sum_ave_prog = 0;
   float sum_ave2_prog = 0;
   float ave_prog[N_blocks];
   float ave2_prog[N_blocks];
   float error_prog[N_blocks];
   
   	for(int i = 0; i < N_blocks; i++){
   	
   			sum_ave_prog = sum_ave_prog + ave_block[i];
   			cout << " ---" << ave_block[i] << endl;
   			sum_ave2_prog = sum_ave2_prog + ave2_block[i];
   			
   			
   			ave_prog[i] = sum_ave_prog / (i+1);
   			ave2_prog[i] = sum_ave2_prog / (i+1);
   			error_prog[i] = error ( ave_prog[i], ave_prog[i], i);
   			
   		cout << "media cumulativa " << ave_prog[i] << endl;
   		cout << "media quadra cumulativa " << ave2_prog[i] << endl;
   		cout << "errore sulla media " << error_prog[i] << endl;
   		cout << i << endl;
   		
   		}
   
   
   rnd.SaveSeed();
   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
