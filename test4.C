//*********************************
//Must include packages, add one every time you use a new class
//*********************************
//
#include "VertexCompositeNtuple_new.h"
#include <iostream>
#include <vector>
#include "TH1D.h"
#include "THStack.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"

//*********************************
//Defining bin count, and bin edges for NTRK. also creating function to classify which bin an event is in (how many ntrk)
//*********************************
//
const Int_t NBINS = 7;
const Int_t NpTBINS = 5;
Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 250};

int findNtrkBin(const double& nTrk)
{
   for(int intrk=0; intrk<NBINS; intrk++){
      if(nTrk<edges[intrk+1] && nTrk>=edges[intrk]){ return intrk;}
   }
   return -1;
}

//*********************************
//*********************************
//Begining of main program
//*********************************
//*********************************

void test4()
{
	TH1::SetDefaultSumw2(kTRUE); //error is correct 
	
	//*********************************
	//canvas building
	//*********************************
	
	TCanvas* c1 = new TCanvas("c1", "", 500, 500);
	TCanvas* c5 = new TCanvas("c5", "", 800, 800);
	TCanvas* c7 = new TCanvas("c7", "", 1200, 800);
	c7->Divide(2,1);
	//TCanvas* c6 = new TCanvas("c6", "", 1700, 1200);
	//c6->Divide(6,2);
	
	//*********************************
	//Getting data/files
	//*********************************
	
	//TFile *f1 = new TFile("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root");
	TFile *f2 = new TFile("NtrkofflineHistogram_pPb8TeV.root", "read"); //File Wei gave
	const auto& inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_PASingleMuon_PARun2016C_DiMuMassMin2.root";
	const auto& treeDir = "dimucontana"; // For MC use dimucontana_mc
	VertexCompositeTree tree;
	
	// For pPb, find out the run on data
	int evtCol=0;
	if (!tree.GetTree(inputFile, treeDir)){
		std::cout << "Invalid tree!" << std::endl; return; }
	long int nevents = tree.GetEntries();
	
	//*********************************
	//Creating histograms
	//*********************************
	
	TH1D* hBin[NBINS];
	for(int ih=0; ih<NBINS; ih++){
		hBin[ih] = new TH1D(Form("hBin%dpT", ih), "", 6, 2, 70);
		}
	
	TH1D *hOriginalBin = (TH1D*) f2->Get("hmult");
	TH1D *hNewBinning = (TH1D*)hOriginalBin->Rebin(NBINS,"hNewBinning", edges);  
	TH1D* hNtrkOfflineAll = new TH1D("hNtrkOfflineAll", "", NBINS, edges);
	//TH1D* hNtrkOfflinePos = new TH1D("hNtrkOfflinePos", "", NBINS, edges);
	//TH1D* hNtrkOfflineNeg = new TH1D("hNtrkOfflineNeg", "", NBINS, edges);
	TH2D* hNtrk3D = new TH2D("hNtrk3D", "", NBINS,edges ,6,2,70);
	TH1D* hpTdist = new TH1D("hpTdist", "", 6,2,70);   
	
	long int nPassTightMuonPair=0;
	long int nPassPt =0;
	long int totSelectedZ =0;   
	long int PosSelectedZ =0;
	long int NegSelectedZ =0;
	
	for(long int jentry=0; jentry < 1e5 ; jentry++){
		
		bool passCut = false;//reset at begining of loop.
		
		//Progress Marker
		if(!(jentry % 1000000)){
			std::cout<<"Processed "<<jentry<<" events out of "<<nevents<<std::endl; }     
		if (tree.GetEntry(jentry)<0){
			std::cout << "Invalid entry!" << std::endl; return; }
		
		//Accounting for beam switch direction, otherwise we cannot account for rapidity and pseudo rapidity direction forward backward
		if (tree.RunNb() >= 285410 && tree.RunNb() <= 285951){
			evtCol = -1; }        // "Pbp8Y16" 
		else if (tree.RunNb() >= 285952 && tree.RunNb() <= 286504){
			evtCol = 1; }  // "pPb8Y16"
		
		for(unsigned int iCand=0; iCand<tree.candSize(); iCand++){
			
			//Accounting for rapidity abd pseudorapidity when considering muon pT
			tree.eta()[iCand]=(evtCol *    ( tree.eta()[iCand] +0.465   ));
			tree.y()[iCand]=(evtCol *      ( tree.y()[iCand]   +0.465   ));
			
			//*********************************
			//KINEMATIC
			// only negative
			bool passNegY = 0>=tree.y()[iCand] && tree.y()[iCand]> -1.935;
			// only positive*****
			bool passPosY = 0<=tree.y()[iCand] && tree.y()[iCand]<1.935;
			//PM eta
			bool passAllEtaD1D2 = abs(tree.EtaD1()[iCand])<2.4 && abs(tree.EtaD2()[iCand])<2.4;
			//bool passEtaZ = tree.eta()[iCand]<2.4;
			bool passpT = tree.pTD1()[iCand]>20 && tree.pTD2()[iCand]>20;          
			bool passMass = tree.mass()[iCand]>60 && tree.mass()[iCand]<120;
			//EVENT
			const bool passTriggerMuonPair = tree.trigHLT()[1] && (tree.trigMuon1()[1].at(iCand) || tree.trigMuon2()[1].at(iCand));
			const bool pileUpCut = tree.evtSel()[4];
			const bool goodEvt = tree.evtSel()[0];
			//QUALITY
			bool passTightMuonPair = tree.tightMuon1()[iCand] && tree.tightMuon2()[iCand];
			//*********************************
			
			//if (!passTightMuonPair || !goodEvt || !passTriggerMuonPair || !pileUpCut ) continue;
			
			if(
				//Kinematic******
				(passAllEtaD1D2) 
				//passEtaZ
				&& (passpT) 
				&& (passMass) 
				//Event***********
				&& (passTriggerMuonPair) 
				&& (pileUpCut)
				&& (goodEvt)
				//Quality*********
				&& (passTightMuonPair)
				){ passCut = true;}
			
			if(passCut){
				hNtrkOfflineAll->Fill(tree.Ntrkoffline());
				hNtrk3D->Fill(tree.Ntrkoffline(),tree.pT()[iCand]);
				totSelectedZ++;
				}
			
			int index = findNtrkBin(tree.Ntrkoffline());
			
			if(index==-1){ continue;}
			if(passCut){
				hBin[index]->Fill(tree.pT()[iCand]);
			}
			passCut = false; 
			hpTdist->Fill(tree.pT()[iCand]);
			
			}
		
		}
	
	c1->cd();
	hpTdist->Draw();
	
	//normalizing z to yeild in direction of pT, not Ntrk
	c5->cd();
	Double_t One =hNewBinning->GetBinContent(1);
	Double_t Two =hNewBinning->GetBinContent(2);
	Double_t Three =hNewBinning->GetBinContent(3);
	Double_t Four =hNewBinning->GetBinContent(4);
	Double_t Five =hNewBinning->GetBinContent(5);
	Double_t Six =hNewBinning->GetBinContent(6);
	Double_t Seven =hNewBinning->GetBinContent(7);
	
	for(int i=1; i < NpTBINS+1; i++){
		Double_t OneI=hNtrk3D->GetBinContent(1,i);
		Double_t TwoI=hNtrk3D->GetBinContent(2,i);
		Double_t ThreeI=hNtrk3D->GetBinContent(3,i);
		Double_t FourI=hNtrk3D->GetBinContent(4,i);
		Double_t FiveI=hNtrk3D->GetBinContent(5,i);
		Double_t SixI=hNtrk3D->GetBinContent(6,i);
		Double_t SevenI=hNtrk3D->GetBinContent(7,i);
		
		hNtrk3D->SetBinContent(1,i,(OneI/One));
		hNtrk3D->SetBinContent(2,i,(TwoI/Two));
		hNtrk3D->SetBinContent(3,i,(ThreeI/Three));
		hNtrk3D->SetBinContent(4,i,(FourI/Four));
		hNtrk3D->SetBinContent(5,i,(FiveI/Five));
		hNtrk3D->SetBinContent(6,i,(SixI/Six));
		hNtrk3D->SetBinContent(7,i,(SevenI/Seven));
		
		}

	hNtrk3D->Scale(1./174e9);
	hNtrk3D ->SetName("Z yield v Ntrk");
	hNtrk3D ->SetTitle("Z yield v Ntrk");
	hNtrk3D ->GetZaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	hNtrk3D ->GetZaxis()->CenterTitle();
	hNtrk3D ->GetZaxis()->SetTitleOffset(1.5);
	hNtrk3D ->GetYaxis()->SetTitle("pT of Z");
	hNtrk3D ->GetYaxis()->CenterTitle();
	hNtrk3D ->GetXaxis()->SetTitle("N Track Offline");
	hNtrk3D ->GetXaxis()->CenterTitle();
	hNtrk3D ->GetYaxis()->SetTitleOffset(2);
	hNtrk3D ->GetXaxis()->SetTitleOffset(2);
	hNtrk3D ->SetStats(false);
	hNtrk3D->Draw("Lego2");
	
	
	c7->cd(1);
	
	for(int ih=0; ih<NBINS; ih++){
		hBin[ih]->SetStats(false);
		hBin[ih]->Scale(1/(hNewBinning->GetBinContent(ih+1)));
		hBin[ih]->Scale(1./174e9);
		}
	
	Double_t IntVec[NBINS];
	Double_t MeanVec[NBINS];
	Double_t MeanErrorVec[NBINS];
	Double_t IntVecTwo[NBINS];
	
	for(int jh=0; jh<NBINS; jh++){
		IntVec[jh]=hBin[jh]->Integral(1,7);
		hBin[jh]->Scale(1./IntVec[jh]);
		MeanVec[jh]=hBin[jh]->GetMean();
		MeanErrorVec[jh]=hBin[jh]->GetMeanError();
		IntVecTwo[jh]=hBin[jh]->Integral(1,7);
		}
	for(int jh=0; jh<NBINS; jh++){
		std::cout <<  "VecOne: " << jh  << std::endl;
		std::cout <<  IntVec[jh]  << std::endl;
		}	
	for(int jh=0; jh<NBINS; jh++){
		std::cout <<  "VecTwo: " << jh  << std::endl;
		std::cout <<  IntVecTwo[jh]  << std::endl;
		}
	for(int jh=0; jh<NBINS; jh++){
		std::cout <<  "Mean Vec: " << jh  << std::endl;
		std::cout <<  MeanVec[jh]  << std::endl;
		}

	hBin[6]->SetAxisRange(1, 80, "X"); 
	hBin[6]->GetXaxis()->SetMoreLogLabels(true);
	hBin[6]->SetMarkerStyle(23);
	hBin[6]->SetLineColor(kRed);
	hBin[6]->Draw();
	hBin[6]->GetXaxis()->SetMoreLogLabels(true);
	hBin[6]->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	hBin[6]->GetYaxis()->CenterTitle();
	hBin[6]->GetXaxis()->SetTitle("pT (GeV)");
	hBin[6] ->GetXaxis()->SetTitleOffset(1.5);
	hBin[6] ->GetYaxis()->SetTitleOffset(1.0);
	hBin[6]->GetXaxis()->CenterTitle();
	hBin[6]->SetName("Z yield v pT");
	hBin[6]->SetTitle("Z yield v pT");
	
	hBin[1]->SetMarkerStyle(28);
	hBin[1]->SetLineColor(kOrange);
	hBin[1]->Draw("SAME");
	hBin[2]->SetMarkerStyle(29);
	hBin[2]->SetLineColor(kBlack);
	hBin[2]->Draw("SAME");
	hBin[3]->SetMarkerStyle(20);
	hBin[3]->SetLineColor(kCyan);
	hBin[3]->Draw("SAME");
	hBin[4]->SetMarkerStyle(21);
	hBin[4]->SetLineColor(kBlue);
	hBin[4]->Draw("SAME");
	hBin[5]->SetMarkerStyle(22);
	hBin[5]->SetLineColor(kGreen);
	hBin[5]->Draw("SAME");
	hBin[0]->SetMarkerStyle(20);
	hBin[0]->SetLineColor(kYellow);
	hBin[0]->Draw("SAME");
	
	auto legend = new TLegend(0.1,0.7,0.3,0.9);
	legend->SetHeader(); // option "C" allows to center the header
	legend->AddEntry(hBin[0],"Ntrk 0-30");
	legend->AddEntry(hBin[1],"Ntrk 30-60");
	legend->AddEntry(hBin[2],"Ntrk 60-90");
	legend->AddEntry(hBin[3],"Ntrk 90-120");
	legend->AddEntry(hBin[4],"Ntrk 120-155");
	legend->AddEntry(hBin[5],"Ntrk 155-190");
	legend->AddEntry(hBin[6],"Ntrk 190-250");
	legend->Draw();
	
	Double_t NT[NBINS];
	for (Int_t i=0; i<NBINS; i++) {
		NT[i] = (edges[i]+edges[i+1])/2;
		}
	//TGraphErrors *pTMean100 = new TGraphErrors(NBINS,NT, MeanVec,0,MeanErrorVec);
	//TMultiGraph *mgE = new TMultiGraph();
	
	TGraphErrors *pTMean[NBINS];
	for(Int_t q=0; q<NBINS; q++){
		pTMean[q] = new TGraphErrors(1);
		pTMean[q]->SetPoint(q,NT[q],MeanVec[q]);
		pTMean[q]->SetPointError(q,0,MeanErrorVec[q]);
		}
	c7->cd(2);
	
	pTMean[6]->SetMarkerSize(2);	
	pTMean[6]->SetMarkerStyle(23);
	pTMean[6]->SetMarkerColor(kRed);
	pTMean[6]->Draw("AP");
	pTMean[6]->GetYaxis()->SetTitle("Mean pT (GeV)");
	pTMean[6]->GetYaxis()->CenterTitle();
	pTMean[6]->GetXaxis()->SetTitle("Ntrk (bin range)");
	pTMean[6] ->GetXaxis()->SetTitleOffset(1.5);
	pTMean[6] ->GetYaxis()->SetTitleOffset(1.0);
	pTMean[6]->GetXaxis()->CenterTitle();
	//pTMean[6]->SetName("Mean pT by Ntrk Bin");
	pTMean[6]->SetTitle("Mean pT by Ntrk Bin");
	
	pTMean[1]->SetMarkerSize(2);
	pTMean[1]->SetMarkerStyle(28);
	pTMean[1]->SetMarkerColor(kOrange);
	pTMean[2]->SetMarkerSize(2);
	pTMean[2]->SetMarkerStyle(29);
	pTMean[2]->SetMarkerColor(kBlack);
	pTMean[3]->SetMarkerSize(2);
	pTMean[3]->SetMarkerStyle(20);
	pTMean[3]->SetMarkerColor(kCyan);
	pTMean[4]->SetMarkerSize(2);
	pTMean[4]->SetMarkerStyle(21);
	pTMean[4]->SetMarkerColor(kBlue);
	pTMean[5]->SetMarkerSize(2);
	pTMean[5]->SetMarkerStyle(22);
	pTMean[5]->SetMarkerColor(kGreen);
	pTMean[0]->SetMarkerSize(2);
	pTMean[0]->SetMarkerStyle(20);
	pTMean[0]->SetMarkerColor(kYellow);
	
	pTMean[0]->Draw("P");
	pTMean[1]->Draw("P");
	pTMean[2]->Draw("P");
	pTMean[3]->Draw("P");
	pTMean[4]->Draw("P");
	pTMean[5]->Draw("P");
	pTMean[6]->Draw("P");

	c1->Print("pTdist.png");
	c5->Print("3DpTntrk.png");
	c7->Print("pTbyNtrk.png");
	
	std::cout <<  totSelectedZ  << std::endl;
	}
//std::cout <<  PosSelectedZ  << std::endl;
//std::cout <<  NegSelectedZ  << std::endl;



	//Drawing   
	   //hBinMD->SetStats(FALSE);
	//          c1->cd();
	//             hNtrkOfflineAll->Scale(1./174e9);
	//             hNtrkOfflineAll->Draw();
	//             //c1->Print("hNtrkOffline.png");
	//          c2->cd();  
	//             hNtrkOfflineNeg->Scale(1./174e9);
	//             hNtrkOfflineNeg->Draw();
	//             //c2->Print("hNtrkOfflineNeg.png");
	//          
	//          c3->cd();
	//             hNtrkOfflinePos->Scale(1./174e9);
	//             hNtrkOfflinePos->Draw();
	//             //c1->Print("hNtrkOfflinePos.png");
	//          
	//          c4->cd(1);
	//             TH1D *hRatioAll = (TH1D*)hNtrkOfflineAll->Clone();
	//             hRatioAll->SetName("Z yield v Ntrk: Lab  abs(eta)<2.4");
	//             hRatioAll->SetTitle("Z yield v Ntrk: Lab abs(eta)<2.4");
	//             hRatioAll->Divide(hNewBinning);
	//             hRatioAll->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	//             hRatioAll->GetYaxis()->CenterTitle();
	//             hRatioAll->GetYaxis()->SetTitleOffset(1.2);	
	//             hRatioAll->GetXaxis()->SetTitle("N Track Offline");
	//             hRatioAll->GetXaxis()->CenterTitle();
	//             hRatioAll->SetStats(false);
	//             hRatioAll->Draw();
	//          
	//          c4->cd(2);
	//             TH1D *hRatioPos = (TH1D*)hNtrkOfflinePos->Clone();
	//             hRatioPos->SetName("Z yield v Ntrk: COM 0 <rapidity< 1.935");
	//             hRatioPos->SetTitle("Z yield v Ntrk: COM 0 <rapidity< 1.935");
	//             hRatioPos->Divide(hNewBinning);
	//             //hRatioPos->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	//             //hRatioPos->GetYaxis()->CenterTitle();
	//             hRatioPos->GetXaxis()->SetTitle("N Track Offline");
	//             hRatioPos->GetXaxis()->CenterTitle();
	//             hRatioPos->SetStats(false);
	//             hRatioPos->Draw();
	//          
	//          c4->cd(3);
	//             TH1D *hRatioNeg = (TH1D*)hNtrkOfflineNeg->Clone();
	//             hRatioNeg->SetName("Z yield v Ntrk: COM 0 >rapidity> -1.935");
	//             hRatioNeg->SetTitle("Z yield v Ntrk: COM 0 >rapidity> -1.935");
	//             hRatioNeg->Divide(hNewBinning);
	//             //hRatioNeg->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	//             //hRatioNeg->GetYaxis()->CenterTitle();
	//             hRatioNeg->GetXaxis()->SetTitle("N Track Offline");
	//             hRatioNeg->GetXaxis()->CenterTitle();
	//             hRatioNeg->SetStats(false);
	//             hRatioNeg->Draw();

	//hs->Add(hNtrkOfflineAll1);
	//hNtrkOfflineAll1->SetMarkerStyle(23);
	//hNtrkOfflineAll1->SetLineColor(kRed);
	//hNtrkOfflineAll1->Divide(hNewBinning);
	//hNtrkOfflineAll1->Scale(1./174e9);
	//
	//
	//hs->Add(hNtrkOfflineAll3);
	//hNtrkOfflineAll3->SetMarkerStyle(22);
	//hNtrkOfflineAll3->SetLineColor(kYellow);
	//hNtrkOfflineAll3->Divide(hNewBinning);
	//hNtrkOfflineAll3->Scale(1./174e9);
	//
	//hs->Add(hNtrkOfflineAll5);
	//hNtrkOfflineAll5->SetMarkerStyle(21);
	//hNtrkOfflineAll5->SetLineColor(kGreen);
	//hNtrkOfflineAll5->Divide(hNewBinning);
	//hNtrkOfflineAll5->Scale(1./174e9);
	//
	//hs->Add(hNtrkOfflineAll7);
	//hNtrkOfflineAll7->SetMarkerStyle(20);
	//hNtrkOfflineAll7->SetLineColor(kCyan);
	//hNtrkOfflineAll7->Divide(hNewBinning);
	//hNtrkOfflineAll7->Scale(1./174e9);
	//
	//hs->Add(hNtrkOfflineAll9);
	//hNtrkOfflineAll9->SetMarkerStyle(15);
	//hNtrkOfflineAll9->SetLineColor(kBlue);
	//hNtrkOfflineAll9->Divide(hNewBinning);
	//hNtrkOfflineAll9->Scale(1./174e9);
	//
	//hs->Add(hNtrkOfflineAll11);
	//hNtrkOfflineAll11->SetMarkerStyle(29);
	//hNtrkOfflineAll11->SetLineColor(kMagenta);
	//hNtrkOfflineAll11->Divide(hNewBinning);
	//hNtrkOfflineAll11->Scale(1./174e9);
	//
	//hs->Add(hNtrkOfflineAll12);
	//hNtrkOfflineAll12->SetMarkerStyle(28);
	//hNtrkOfflineAll12->SetLineColor(kBlack);
	//hNtrkOfflineAll12->Divide(hNewBinning);
	//hNtrkOfflineAll12->Scale(1./174e9);
	//
	//
	////hs->Add(hNtrkOfflineAll);
	////hNtrkOfflineAll->SetMarkerStyle(15);
	////hNtrkOfflineAll->SetLineColor(kBlack);
	////hNtrkOfflineAll->Divide(hNewBinning);
	////hNtrkOfflineAll->Scale(1./174e9);
	//
	//
	////hNtrkOfflineAll->SetStats(false);
	//hNtrkOfflineAll1->SetStats(false);
	//hNtrkOfflineAll3->SetStats(false);
	//hNtrkOfflineAll5->SetStats(false);
	//hNtrkOfflineAll7->SetStats(false);
	//hNtrkOfflineAll9->SetStats(false);
	//hNtrkOfflineAll11->SetStats(false);
	//hNtrkOfflineAll12->SetStats(false);
	//
	//
	//
	//
	//
	//
	//c7->cd(); hs->Draw("nostack");
	//
	//hs->SetTitle("Z yield v Ntrk");
	//hs->GetYaxis()->SetTitle("#frac{#sigma_{Z}}{#sigma_{mb}}");
	//hs->GetYaxis()->CenterTitle();
	//hs->GetYaxis()->SetTitleOffset(1.2);
	//hs->GetXaxis()->SetTitle("N Track Offline");
	//hs->GetXaxis()->CenterTitle();
	//
	//auto legend = new TLegend(0.1,0.7,0.48,0.9);
	////legend->SetHeader(); // option "C" allows to center the header
	////legend->AddEntry(hNtrkOfflineAll,"pT All");
	//legend->AddEntry(hNtrkOfflineAll1,"pT 20-24");
	//legend->AddEntry(hNtrkOfflineAll3,"pT 24-28");
	//legend->AddEntry(hNtrkOfflineAll5,"pT 28-32");
	//legend->AddEntry(hNtrkOfflineAll7,"pT 32-36");
	//legend->AddEntry(hNtrkOfflineAll9,"pT 36-40");
	//legend->AddEntry(hNtrkOfflineAll11,"pT 40-44");
	//legend->AddEntry(hNtrkOfflineAll12,"pT 44-60");
	//legend->Draw();

	//c6->cd(1);
	//hNtrkOfflineAll1->Divide(hNewBinning);
	//hNtrkOfflineAll1->Draw();
	//hNtrkOfflineAll1->SetTitle("pT 20-22");
	//
	//c6->cd(2);
	//hNtrkOfflineAll2->Divide(hNewBinning);
	//hNtrkOfflineAll2->Draw();
	//hNtrkOfflineAll2->SetTitle("pT 22-24");
	//
	//c6->cd(3);
	//hNtrkOfflineAll3->Divide(hNewBinning);
	//hNtrkOfflineAll3->Draw();
	//hNtrkOfflineAll3->SetTitle("pT 24-26");
	//
	//c6->cd(4);
	//hNtrkOfflineAll4->Divide(hNewBinning);
	//hNtrkOfflineAll4->Draw();
	//hNtrkOfflineAll4->SetTitle("pT 26-28");
	//
	//c6->cd(5);
	//hNtrkOfflineAll5->Divide(hNewBinning);
	//hNtrkOfflineAll5->Draw();
	//hNtrkOfflineAll5->SetTitle("pT 28-30");
	//
	//c6->cd(6);
	//hNtrkOfflineAll6->Divide(hNewBinning);
	//hNtrkOfflineAll6->Draw();
	//hNtrkOfflineAll6->SetTitle("pT 30-32");
	//
	//c6->cd(7);
	//hNtrkOfflineAll7->Divide(hNewBinning);
	//hNtrkOfflineAll7->Draw();
	//hNtrkOfflineAll7->SetTitle("pT 32-34");
	//
	//c6->cd(8);
	//hNtrkOfflineAll8->Divide(hNewBinning);
	//hNtrkOfflineAll8->Draw();
	//hNtrkOfflineAll8->SetTitle("pT 34-36");
	//
	//c6->cd(9);
	//hNtrkOfflineAll9->Divide(hNewBinning);
	//hNtrkOfflineAll9->Draw();
	//hNtrkOfflineAll9->SetTitle("pT 36-38");
	//
	//c6->cd(10);
	//hNtrkOfflineAll10->Divide(hNewBinning);
	//hNtrkOfflineAll10->Draw();
	//hNtrkOfflineAll10->SetTitle("pT 38-40");
	//
	//
	//c6->cd(11);
	//hNtrkOfflineAll11->Divide(hNewBinning);
	//hNtrkOfflineAll11->Draw();
	//hNtrkOfflineAll11->SetTitle("pT 40-42");
	//
	//c6->cd(12);
	//hNtrkOfflineAll12->Divide(hNewBinning);
	//hNtrkOfflineAll12->Draw();
	//hNtrkOfflineAll12->SetTitle("pT 42-44");



	//c5->cd();
	 //  hNtrkUnchanged->Draw();
	   //c5->Print("hNtrkUnchanged.png");




	//   TH1D* hNtrkOfflineAll1 = new TH1D("hNtrkOfflineAll1", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll2 = new TH1D("hNtrkOfflineAll2", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll3 = new TH1D("hNtrkOfflineAll3", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll4 = new TH1D("hNtrkOfflineAll4", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll5 = new TH1D("hNtrkOfflineAll5", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll6 = new TH1D("hNtrkOfflineAll6", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll7 = new TH1D("hNtrkOfflineAll7", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll8 = new TH1D("hNtrkOfflineAll8", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll9 = new TH1D("hNtrkOfflineAll9", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll10 = new TH1D("hNtrkOfflineAll10", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll11 = new TH1D("hNtrkOfflineAll11", "", NBINS, edges);
	//   TH1D* hNtrkOfflineAll12 = new TH1D("hNtrkOfflineAll12", "", NBINS, edges);   

	//          if(passCut && passNegY){
	//          hNtrkOfflineNeg->Fill(tree.Ntrkoffline());
	//          NegSelectedZ++;
	//          }
	//
	//          if(passCut && passPosY){
	//          hNtrkOfflinePos->Fill(tree.Ntrkoffline());
	//          PosSelectedZ++;
	//          }





	//const Int_t NBINS = 7;
	//const Int_t sep=round(250/NBINS);
	//Double_t edges[NBINS+1];
	//for(int q=0; q<NBINS+1; q++){
	//edges[q]=sep*q;
	//}
	//}



 //  if(passCut && tree.pT()[iCand]<24 && tree.pT()[iCand]>=20){
 //  hNtrkOfflineAll1->Fill(tree.Ntrkoffline());
 //  }
 //  //if(passCut && tree.pT()[iCand]<24 && tree.pT()[iCand]>=22){
 //  //hNtrkOfflineAll2->Fill(tree.Ntrkoffline());
 //  //}
 //  if(passCut && tree.pT()[iCand]<28 && tree.pT()[iCand]>=24){
 //  hNtrkOfflineAll3->Fill(tree.Ntrkoffline());
 //  }
 //  //if(passCut && tree.pT()[iCand]<28 && tree.pT()[iCand]>=26){
 //  //hNtrkOfflineAll4->Fill(tree.Ntrkoffline());
 //  //}
 //  if(passCut && tree.pT()[iCand]<32 && tree.pT()[iCand]>=28){
 //  hNtrkOfflineAll5->Fill(tree.Ntrkoffline());
 //  }
 //  //if(passCut && tree.pT()[iCand]<32 && tree.pT()[iCand]>=30){
 //  //hNtrkOfflineAll6->Fill(tree.Ntrkoffline());
 //  //}
 //  if(passCut && tree.pT()[iCand]<36 && tree.pT()[iCand]>=32){
 //  hNtrkOfflineAll7->Fill(tree.Ntrkoffline());
 //  }
 //  //if(passCut && tree.pT()[iCand]<36 && tree.pT()[iCand]>=34){
 //  //hNtrkOfflineAll8->Fill(tree.Ntrkoffline());
 //  //}
 //  if(passCut && tree.pT()[iCand]<40 && tree.pT()[iCand]>=36){
 //  hNtrkOfflineAll9->Fill(tree.Ntrkoffline());
 //  }
 //  //if(passCut && tree.pT()[iCand]<40 && tree.pT()[iCand]>=38){
 //  //hNtrkOfflineAll10->Fill(tree.Ntrkoffline());
 //  //}
 //  if(passCut && tree.pT()[iCand]<44 && tree.pT()[iCand]>=40){
 //  hNtrkOfflineAll11->Fill(tree.Ntrkoffline());
 //  }
 //  if(passCut && tree.pT()[iCand]<60 && tree.pT()[iCand]>=44){
 //  hNtrkOfflineAll12->Fill(tree.Ntrkoffline());
 //  }




	//
