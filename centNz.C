#include <iostream>

{
Int_t n=5;
Double_t x[n], y[n];

for (Int_t i=0; i<n; i++) {
y[i]=i+1;
}
x[0]=2994/1820;
x[1]=2282/1430;
x[2]=5985/805;
x[3]=2063/267;
x[4]=469/65.4;
x[5]=74/10.7;

TGraph *gr  = new TGraph(n,x,y);
   TCanvas *c1 = new TCanvas("c1","Graph Draw Options",
                             200,10,600,400);
 gr->Draw("AC*");

}



























