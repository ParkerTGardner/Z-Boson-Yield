#include "VertexCompositeNtuple.h"

#include <iostream>

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

const Int_t NBINS = 6;
Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190};

int findNtrkBin(const double& nTrk)
{
   for(int intrk=0; intrk<NBINS; intrk++){
      if(nTrk<edges[intrk+1] && nTrk>=edges[intrk]) return intrk;
   }
   return -1;
}

void test()
{
   TCanvas* c1 = new TCanvas("c1", "", 550, 450);
   TH1::SetDefaultSumw2(kTRUE);
   TCanvas* c2 = new TCanvas("c2", "", 550, 450);
   TCanvas* c3 = new TCanvas("c3", "", 550, 450);
   TCanvas* c4 = new TCanvas("c4", "", 1500, 450);
   c4->Divide(6,1);

   c1->cd();
   TFile *f1 = new TFile("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root");
   if(!f1->IsOpen()) std::cerr << "did not open the file" << std::endl;
   TTree* t = (TTree*) f1->Get("dimucontana/VertexCompositeNtuple");
   //const Int_t NBINS = 16;
   //Double_t edges[NBINS+1] = {0, 15, 30, 45, 60, 75, 90, 105, 120, 137, 155, 172, 190, 205, 220, 235, 240};
   VertexCompositeNtuple* vtxCand = new VertexCompositeNtuple(t);
   TH1D* hNtrkOffline = new TH1D("hNtrkOffline", "", NBINS, edges);

   TH1D* hBin[6];
for(int ih=0; ih<NBINS; ih++){
hBin[ih] = new TH1D(Form("hBin%dMD", ih), "", 30, 60, 120);
}


   long int nentries = vtxCand->GetEntries();
   std::cout << nentries << std::endl;
   long int nPassTightMuonPair=0;
   long int nPassPt =0;
   for(long int ientry=0; ientry < nentries ; ientry++){
      vtxCand->GetEntry(ientry);
      bool passCut = false;
      for(unsigned int iCand=0; iCand<vtxCand->candSize; iCand++){
          bool passTightMuonPair = vtxCand->tightMuon1[iCand] && vtxCand->tightMuon2[iCand];
          if(passTightMuonPair) nPassTightMuonPair++;
          bool passpT = vtxCand->pTD1[iCand]>20 && vtxCand->pTD2[iCand]>20;
          if(passpT && !passTightMuonPair) nPassPt++;
          bool passMass = vtxCand->mass[iCand]>60 && vtxCand->mass[iCand]<120;
          if(passTightMuonPair && passMass && passpT ) passCut = true;
          if(passCut) break;
      }
      if(passCut)
          hNtrkOffline->Fill(vtxCand->Ntrkoffline);
     
      passCut = false;
      for(unsigned int iCand=0; iCand<vtxCand->candSize; iCand++){
          int index = findNtrkBin(vtxCand->Ntrkoffline);
	  if(index==-1) continue;
          bool passTightMuonPair = vtxCand->tightMuon1[iCand] && vtxCand->tightMuon2[iCand];
          bool passpT = vtxCand->pTD1[iCand]>20 && vtxCand->pTD2[iCand]>20;
          bool passMass = vtxCand->mass[iCand]>60 && vtxCand->mass[iCand]<120;
          if(passTightMuonPair && passMass && passpT ) passCut = true;
          if(passCut)
              hBin[index]->Fill(vtxCand->mass[iCand]);
        passCut=false;
      }
   }

std::cout << nPassTightMuonPair << std::endl;
std::cout << nPassPt<< std::endl;
std::cout << hNtrkOffline->GetBinContent(6) << std::endl;
   c1->cd();
   hNtrkOffline->Scale(1./173e9);
   hNtrkOffline->Draw();
   c1->Print("hNtrkOffline.png");
  
   //Double_t binContent = hNtrkOffline->GetBinContent(1);
   for(int ih=0; ih<NBINS; ih++){
       c4->cd(ih+1);
       hBin[ih]->Draw();
   }

   c2->cd();
   TFile* f2 = new TFile("NtrkofflineHistogram_pPb8TeV.root", "read");
   TH1D* hMult = (TH1D*) f2->Get("hmult");
   //hMult->Scale(hNtrkOffline->GetMaximum()/ hMult->GetMaximum());
   TH1D *hnew = dynamic_cast<TH1D*>(hMult->Rebin(NBINS,"hnew", edges));  
  // hMult->Rebin(NBINS, "", edges);
   hnew->Scale(1.*2.12);
   hnew->Draw();
   c2->Print("hnew.png");
   hNtrkOffline->Divide(hnew);


   c3->cd();
   hNtrkOffline->Draw();
   c3->Print("hNtrkOffline_ratio.png");

}
