#include <TF1.h>
#include <fstream>

void AngDistr(){
    TF1* fun = new TF1("AngularDistr", "TMath::Power(TMath::Cos(x), 2)*TMath::Sin(x)", 0., TMath::Pi());

    std::ofstream file;
    file.open("./geant4-exercises/Brooklyn2024/angDist.dat");

    for(double x = 0.; x < TMath::Pi(); x += 0.01){
        if(x <= TMath::Pi()/2.)
            file << "/gps/hist/point " << x << " " << fun->Eval(x) << std::endl; 
        else
            file << "/gps/hist/point " << x << " " << "0." << std::endl; 
    }   
    file.close();
} 