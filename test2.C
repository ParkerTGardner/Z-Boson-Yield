#include "VertexCompositeNtuple.h"

#include <iostream>

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

const Int_t NBINS = 7;
Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 260};

int findNtrkBin(const double& nTrk)
{
   for(int intrk=0; intrk<NBINS; intrk++){
      if(nTrk<edges[intrk+1] && nTrk>=edges[intrk]) return intrk;
   }
   return -1;
}

void test2()
{
   TH1::SetDefaultSumw2(kTRUE); 
//canvas building
   TCanvas* c1 = new TCanvas("c1", "", 550, 450);
   TCanvas* c2 = new TCanvas("c2", "", 1050, 450);
   TCanvas* c3 = new TCanvas("c3", "", 550, 450);
   TCanvas* c4 = new TCanvas("c4", "", 1700, 450);
   c4->Divide(NBINS,1);
   TCanvas* c5 = new TCanvas("c5", "", 550, 450);
 

 //Getting data/files
 //
 //
 //TFile *f1 = new TFile("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root");
 TFile *f1 = new TFile("/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_PASingleMuon_PARun2016C_DiMuMassMin2.root"); 
 TFile *f2 = new TFile("NtrkofflineHistogram_pPb8TeV.root", "read");
  
   if(!f1->IsOpen()) std::cerr << "did not open the file" << std::endl;
   TTree* t = (TTree*) f1->Get("dimucontana/VertexCompositeNtuple");
 
   VertexCompositeNtuple* vtxCand = new VertexCompositeNtuple(t);
   TH1D* hNtrkOffline = new TH1D("hNtrkOffline", "", NBINS, edges);
   TH1D* hNtrkUnchanged = new TH1D("hNtrUnchanged", "", NBINS, edges);

//create MD naming and histograms
   TH1D* hBin[NBINS];
   for(int ih=0; ih<NBINS; ih++){
   hBin[ih] = new TH1D(Form("hBin%dMD", ih), "", 30, 60, 120);
   }

   long int nentries = vtxCand->GetEntries();
   std::cout << nentries << std::endl;
   long int nPassTightMuonPair=0;
   long int nPassPt =0;
   

   for(long int ientry=0; ientry < 1e6 ; ientry++){
      vtxCand->GetEntry(ientry);
      bool passCut = false;
      for(unsigned int iCand=0; iCand<vtxCand->candSize; iCand++){
          bool passTightMuonPair = vtxCand->tightMuon1[iCand] && vtxCand->tightMuon2[iCand];
          const bool goodEvt = vtxCand->evtSel[0];
          //const bool passTriggerMuonPair = vtxCand->trigHLT[1]; //&& static_cast<bool>(vtxCand->trigMuon1[1]->at(iCand));// || vtxCand->trigMuon2[1].at(iCand));
          if(passTightMuonPair) nPassTightMuonPair++;
          bool passpT = vtxCand->pTD1[iCand]>20 && vtxCand->pTD2[iCand]>20;
          if(passpT && !passTightMuonPair) nPassPt++;
          bool passMass = vtxCand->mass[iCand]>60 && vtxCand->mass[iCand]<120;
          if (!passTightMuonPair || !goodEvt) continue;
          if(passTightMuonPair && goodEvt &&  passMass && passpT ) passCut = true;
          if(passCut) break;
      }
      if(passCut)
          hNtrkOffline->Fill(vtxCand->Ntrkoffline);
     
      hNtrkUnchanged->Fill(vtxCand->Ntrkoffline);
      passCut = false;
      for(unsigned int iCand=0; iCand<vtxCand->candSize; iCand++){
          int index = findNtrkBin(vtxCand->Ntrkoffline);
	  if(index==-1) continue;
          bool passTightMuonPair = vtxCand->tightMuon1[iCand] && vtxCand->tightMuon2[iCand];
          const bool goodEvt = vtxCand->evtSel[0];
          //const bool passTriggerMuonPair = vtxCand->trigHLT[1] && static_cast<bool>((vtxCand->trigMuon1[1]).at(iCand)); //|| vtxCand->trigMuon2[1].at(iCand));
          //if(vtxCand->trigMuon1->size()<2) continue;
          //const bool passTriggerMuonPair = vtxCand->trigHLT[1] && vtxCand->TrigMuon1().at(1).at(iCand);
          bool passpT = vtxCand->pTD1[iCand]>20 && vtxCand->pTD2[iCand]>20;
          bool passMass = vtxCand->mass[iCand]>60 && vtxCand->mass[iCand]<120;
          if (!passTightMuonPair || !goodEvt) continue;
          if(passTightMuonPair && goodEvt && passMass && passpT ) passCut = true;
          if(passCut)
              hBin[index]->Fill(vtxCand->mass[iCand]);
        passCut=false;
      }
   }

std::cout << nPassTightMuonPair << std::endl;
std::cout << nPassPt<< std::endl;
std::cout << hNtrkOffline->GetBinContent(6) << std::endl;
  
   for(int ih=0; ih<NBINS; ih++){
       c4->cd(ih+1);
       hBin[ih]->Draw();
   }

   //TH1D* hOriginalBin = (TH1D*) f2->Get("hOriginalBin");
   TH1D* hOriginalBin = (TH1D*) f2->Get("hmult");
  // hOriginalBin->Sumw2();
  // TH1D *hNewBinning = (TH1D*)hOriginalBin->Clone();
  // hNewBinning->Sumw2();
 // hNewBinning->Rebin(NBINS,"hNewBinning",edges); 
   //TH1D *hNewBinning = dynamic_cast<TH1D*>(hOriginalBin->Rebin(NBINS,"hNewBinning", edges));  
   TH1D *hNewBinning = (TH1D*)hOriginalBin->Rebin(NBINS,"hNewBinning", edges);  


//Drawing   
 

   c1->cd();
//protecting error
  // hNtrkOffline->Sumw2();
   hNtrkOffline->Scale(1./173e9);
   hNtrkOffline->Draw();
   c1->Print("hNtrkOffline.png");

   c2->cd();
   c2->Divide(2, 1);
   c2->cd(1);
   hNewBinning->Draw("E");
   c2->cd(2);
   hOriginalBin->GetXaxis()->SetRangeUser(0, 190);
   hOriginalBin->Draw("E");
   c2->Print("hNewBinning.png");

   c3->cd();
   TH1D *hRatio = (TH1D*)hNtrkOffline->Clone();
   hRatio->SetName("hRatio");
  // hRatio->Sumw2();
   hRatio->Divide(hNewBinning);
   //hRatio->GetYaxis()->SetRangeUser(-1000,1000);
   hRatio->Draw();
   c3->Print("hRatio.png");
   
   c4->Print("hBinMD.png");

   c5->cd();
   hNtrkUnchanged->Draw();
   c5->Print("hNtrkUnchanged.png");

}
