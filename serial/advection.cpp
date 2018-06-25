///////////////////////////////////////////////////////////////
// A 2d advection code made to practice implementation of 
// OpenMP. My first reall c++ code so be gentle.
// Author: Isaac Meyer icmeyer@mit.edu                        
//////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string>
#include <sstream>
#include <exception>
#include <omp.h>
using namespace std;

double gauss2d(double x,double y,double x0,
               double y0,double sigmax,double sigmay){
    double xterm = pow(x-x0,2)/2/pow(sigmax,2);
    double yterm = pow(y-y0,2)/2/pow(sigmay,2);
    double val = exp(-(xterm+yterm));
    return val;
}

double lax(double up, double down, double left, double right, double center,
           double deltat, double deltax, double U, double V){
    //Function to evaluate the n+1 term for a cell in the lax method
    //U:x velocity, V:y velocity
    double firstterm = 0.25*(up+down+left+right);
    double alpha=deltat/2/deltax;
    double secondterm = alpha*(U*(right-left)+V*(up-down));
    double val = firstterm-secondterm;
    return val;
}

int main(int argc, char* argv[]){
    double start_time = omp_get_wtime();
    int N=atof(argv[1]); int NT=atof(argv[2]); double L=atof(argv[3]);
    double T=atof(argv[4]); double U=atof(argv[5]); double V=atof(argv[6]);
    float cold[400][400]; //Using knowledge of array size, bad!
    float cnew[400][400];
    float deltax = L/N;
    float deltay = deltax;
    float deltat = T/NT;

    /* Check Courant Stability */
    if (deltat > deltax/pow(2*U*U+2*V*V,0.5)){
        perror("Stability condition not met");
        throw exception();
    }

    /* Initialize cold as gaussian */
    float sigmax = 0.25*L; float sigmay = 0.25*L;
    float x0 = L/2; float y0 = L/2;
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            float x = deltax*i+0.5*deltax;
            float y = deltay*j+0.5*deltay;
            cold[i][j] = gauss2d(x,y,x0,y0,sigmax,sigmay);
        }
    }

    for (int n=0;n<NT;n++){
        cout << "Step " << n << "/" << NT <<endl;
        /* Write to file */
        if (n%100 == 0){ //Control write frequency
            stringstream fname;
            fname << "array_" << setw(4) << setfill('0') << n;
            ofstream myfile (fname.str().c_str());
            if (myfile.is_open()){
                for (int i=0;i<N;i++) {
                    for (int j=0;j<N;j++) {
                        myfile << cold[i][j] << " ";
                        if (j == N-1){
                            myfile << endl;
                        }
                    }
                }
            }
            else cout << "Unable to open file";
        }

        /*Update c to n+1 */
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                /*Apply periodic boundary conditions*/
                int u,d,l,r;
                l = i-1; r=i+1; u=j+1; d=j-1;
                if (u == N){l=0;}
                if (d == -1){d=N-1;}
                if (l == -1){l=N-1;}
                if (r == N){r=0;}
                double up,down,left,right,center;
                up=cold[i][u]; down=cold[i][d]; left=cold[l][j];
                right=cold[r][j]; center = cold[i][j];
                /* Update values */
                cnew[i][j]=lax(up,down,left,right,center,deltat,deltax,U,V);
            }
        }

        /*Swap references*/
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                cold[i][j]=cnew[i][j];
            }
        }

    }
    double time = omp_get_wtime() - start_time;
    ofstream myfile ("performance_serial");
    if (myfile.is_open()){
        myfile << "Serial took "<< time;
    }
    else cout << "Unable to open file";
}
        







