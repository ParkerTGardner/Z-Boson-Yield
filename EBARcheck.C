#include <iostream>

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

const Int_t NBINS = 7;
Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 260};


void EBARcheck()
{


TH1::SetDefaultSumw2(kTRUE);
//canvas building
TCanvas* c1 = new TCanvas("c1", "", 1000, 500); 
c1->Divide(2,1);

TFile *f2 = new TFile("NtrkofflineHistogram_pPb8TeV.root", "read");

c1->cd(1);
TH1D* hOriginalBin = (TH1D*) f2->Get("hmult");
hOriginalBin->GetXaxis()->SetRangeUser(0,500);
hOriginalBin->Draw();


c1->cd(2);
hOriginalBin->Draw("E");

}
