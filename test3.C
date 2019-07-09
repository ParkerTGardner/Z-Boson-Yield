#include "VertexCompositeNtuple_new.h"

#include <iostream>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"

const Int_t NBINS = 7;
Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 260};

int findNtrkBin(const double& nTrk)
{
   for(int intrk=0; intrk<NBINS; intrk++){
      if(nTrk<edges[intrk+1] && nTrk>=edges[intrk]) return intrk;
   }
   return -1;
}

void test3()
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
 TFile *f2 = new TFile("NtrkofflineHistogram_pPb8TeV.root", "read");
  
 const auto& inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_PASingleMuon_PARun2016C_DiMuMassMin2.root";
 const auto& treeDir = "dimucontana"; // For MC use dimucontana_mc
 VertexCompositeTree tree;
 if (!tree.GetTree(inputFile, treeDir)) { std::cout << "Invalid tree!" << std::endl; return; }
 long int nevents = tree.GetEntries();

 
 TH1D* hNtrkOffline = new TH1D("hNtrkOffline", "", NBINS, edges);
 TH1D* hNtrkUnchanged = new TH1D("hNtrUnchanged", "", NBINS, edges);



//create MD naming and histograms
   TH1D* hBin[NBINS];
   for(int ih=0; ih<NBINS; ih++){
   hBin[ih] = new TH1D(Form("hBin%dMD", ih), "", 30, 60, 120);
   }

   long int nPassTightMuonPair=0;
   long int nPassPt =0;
      
      //long int Samesign =0;
      //Double_t SamesignBin[NBINS];
      //for(int ih=0; ih<NBINS; ih++){
      //SamesignBin[ih] = 0;
      //}
      //long int PCSamesign =0;
      //Double_t PCSamesignBin[NBINS];
      //for(int ih=0; ih<NBINS; ih++){
      //PCSamesignBin[ih] = 0;
      //}
      //int iCandPause=0;
      //long int totalCan=0;

   for(long int jentry=0; jentry < nevents ; jentry++){

      if(!(jentry % 1000000)) std::cout<<"Processed "<<jentry<<" events out of "<<nevents<<std::endl;     
      if (tree.GetEntry(jentry)<0) { std::cout << "Invalid entry!" << std::endl; return; }

      bool passCut = false;

      for(unsigned int iCand=0; iCand<tree.candSize(); iCand++){
//Kinematic
//
          bool passEtaD1D2 = abs(tree.EtaD1()[iCand])<2.4 && abs(tree.EtaD2()[iCand])<2.4;
          //bool passEtaZ = tree.eta()[iCand]<2.4;
          bool passpT = tree.pTD1()[iCand]>20 && tree.pTD2()[iCand]>20;          
          bool passMass = tree.mass()[iCand]>60 && tree.mass()[iCand]<120;
//Event
//
          const bool passTriggerMuonPair = tree.trigHLT()[1] && (tree.trigMuon1()[1].at(iCand) || tree.trigMuon2()[1].at(iCand));
          const bool pileUpCut = tree.evtSel()[4];
          const bool goodEvt = tree.evtSel()[0];
//Quality
//
          bool passTightMuonPair = tree.tightMuon1()[iCand] && tree.tightMuon2()[iCand];

          if (!passTightMuonPair || !goodEvt || !passTriggerMuonPair || !pileUpCut ) continue;
          if(
            //Kinematic******
            passEtaD1D2 
            //passEtaZ
            && passpT 
            && passMass 
            //Event***********
            && passTriggerMuonPair 
            && pileUpCut
            && goodEvt
            //Quality*********
            && passTightMuonPair
          ) passCut = true;

          if(passCut){
          hNtrkOffline->Fill(tree.Ntrkoffline());
          passCut = false;
          //break;
          }
      }
      




      //if(passCut)
          //hNtrkOffline->Fill(tree.Ntrkoffline());
     

      hNtrkUnchanged->Fill(tree.Ntrkoffline());
      //passCut = false;

      for(unsigned int iCand=0; iCand<tree.candSize(); iCand++){
          int index = findNtrkBin(tree.Ntrkoffline());
	  if(index==-1) continue;

//Kinematic
          bool passEtaD1D2 = abs(tree.EtaD1()[iCand])<2.4 && abs(tree.EtaD2()[iCand])<2.4;
          //bool passEtaZ = tree.eta()[iCand]<2.4;
          bool passpT = tree.pTD1()[iCand]>20 && tree.pTD2()[iCand]>20;          
          bool passMass = tree.mass()[iCand]>60 && tree.mass()[iCand]<120;
//Event 
          const bool passTriggerMuonPair = tree.trigHLT()[1] && (tree.trigMuon1()[1].at(iCand) || tree.trigMuon2()[1].at(iCand));
          const bool pileUpCut = tree.evtSel()[4];
          const bool goodEvt = tree.evtSel()[0];
//Quality
          bool passTightMuonPair = tree.tightMuon1()[iCand] && tree.tightMuon2()[iCand];

          if (!passTightMuonPair || !goodEvt || !passTriggerMuonPair || !pileUpCut ) continue;
          if(
            //Kinematic*****
            //passEtaZ && 
            passEtaD1D2 &&
            passpT && 
            passMass && 
            //Event*********
            passTriggerMuonPair && 
            pileUpCut &&
            goodEvt &&
            //Quality*******
            passTightMuonPair
          ) passCut = true;
          
//Ignore, other versions of cutting
          //if (!passTightMuonPair || !goodEvt || !passTriggerMuonPair || !pileUpCut ) continue;
          //if(passTightMuonPair && passMass && passEta && passpT && passTriggerMuonPair && goodEvt && pileUpCut) passCut = true;          
          //if(passTightMuonPair) passCut = true;
          //if(passMass) passCut = true;
          //if(passpT) passCut = true;
          //if(passTriggerMuonPair) passCut = true;          
          //if(passEtaZ) passCut = true;
          //if(passEtaD1D2) passCut = true;
          //if(pileUpCut) passCut = true;
          //if(goodEvt) passCut = true;
      
          if(passCut){
              hBin[index]->Fill(tree.mass()[iCand]);
              passCut=false;
             // if(tree.chargeD2()[iCand] == tree.chargeD1()[iCand]){
             // PCSamesign++;
             // PCSamesignBin[index]++;
             // }
             }
      }

   }


//std::cout << totalCan  << std::endl;
//std::cout << "Below before cuts" << std::endl;
//std::cout << "By bins (1-7):" << std::endl;
//std::cout << SamesignBin[0] << std::endl;
//std::cout << SamesignBin[1] << std::endl;
//std::cout << SamesignBin[2] << std::endl;
//std::cout << SamesignBin[3] << std::endl;
//std::cout << SamesignBin[4] << std::endl;
//std::cout << SamesignBin[5] << std::endl;
//std::cout << SamesignBin[6] << std::endl;
//std::cout << "Total D1=D2:" << std::endl;
//std::cout << Samesign << std::endl;
//
//std::cout << "*****************" << std::endl;
//
//std::cout << "Below after cuts" << std::endl;
//std::cout << "By bins (1-7):" << std::endl;
//std::cout << PCSamesignBin[0] << std::endl;
//std::cout << PCSamesignBin[1] << std::endl;
//std::cout << PCSamesignBin[2] << std::endl;
//std::cout << PCSamesignBin[3] << std::endl;
//std::cout << PCSamesignBin[4] << std::endl;
//std::cout << PCSamesignBin[5] << std::endl;
//std::cout << PCSamesignBin[6] << std::endl;
//std::cout << "Total D1=D2:" << std::endl;
//std::cout << PCSamesign << std::endl;





 
//std::cout << nPassTightMuonPair << std::endl;
//std::cout << nPassPt<< std::endl;
//std::cout << hNtrkOffline->GetBinContent(6) << std::endl;
  
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
   //hOriginalBin->GetXaxis()->SetRangeUser(0, 190);
   hOriginalBin->Draw("E");
   c2->Print("hNewBinning.png");

   c3->cd();
   TH1D *hRatio = (TH1D*)hNtrkOffline->Clone();
   hRatio->SetName("Z Prduction verus Min Bias");
   hRatio->SetTitle("Z Prduction verus Min Bias");
   hRatio->Divide(hNewBinning);
   //hRatio->GetYaxis()->SetRangeUser(-1000,1000);
   hRatio->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
   hRatio->GetYaxis()->CenterTitle();
   hRatio->GetXaxis()->SetTitle("N Track Offline");
   hRatio->GetXaxis()->CenterTitle();

   hRatio->Draw();
   c3->Print("hRatio.png");
   
   c4->Print("hBinMD.png");

   c5->cd();
   hNtrkUnchanged->Draw();
   c5->Print("hNtrkUnchanged.png");

}
