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

void test5()
{
	TH1::SetDefaultSumw2(kTRUE); //error is correct 

	//*********************************
	//Getting data/files
	//*********************************

	const auto& inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_DYToMuMu_pPb-Bst_pPb816Summer16_DiMuMC.root";
	const auto& treeDir = "dimucontana_mc"; // For MC use dimucontana_mc
	int evtCol = 1; //pPb
        //evtCol = -1; //Pbp
	VertexCompositeTree tree;

	// For pPb, find out the run on data
	if (!tree.GetTree(inputFile, treeDir)){
		std::cout << "Invalid tree!" << std::endl; return; }
	long int nevents = tree.GetEntries();
	std::cout <<  nevents  << std::endl; 

	//*********************************
	//Creating histograms
	//*********************************
	
	int pTbins=5;
	int ybins=5;
        TH2D* DenomGenCan = new TH2D("DenomGenCan", "", pTbins,0,200, ybins, 0, 2.4);
        TH2D* NumRecoCan = new TH2D("NumRecoCan", "", pTbins,0,200, ybins, 0, 2.4);
	TH2D* newNRC = new TH2D("newNRC", "", pTbins,0,200, ybins, 0, 2.4);

        //*********************************
        //Primary loop
        //*********************************
	
	for(long int jentry=0; jentry < nevents ; jentry++){
		
		bool passCut = false;//reset at begining of loop.
                bool SkipReco = false;
		int IndexMark;
		
		//Progress Marker
		if(!(jentry % 100000)){
			std::cout<<"Processed "<<jentry<<" events out of "<<nevents<<std::endl; }     
		if (tree.GetEntry(jentry)<0){
			std::cout << "Invalid entry!" << std::endl; return; }
		
		for(unsigned int iCand_gen=0; iCand_gen<tree.candSize_gen(); iCand_gen++){
			IndexMark=iCand_gen;
			SkipReco = false;
			//Accounting for rapidity abd pseudorapidity when considering muon pT
			//tree.eta_gen()[iCand_gen]=(evtCol *    ( tree.eta_gen()[iCand_gen] +0.465   ));
			//tree.y_gen()[iCand_gen]=(evtCol *      ( tree.y_gen()[iCand_gen]   +0.465   ));
			

			//making cuts and filling the gen numerator for effiecency calc	
			if(tree.pTD1_gen()[iCand_gen]<20 || tree.pTD2_gen()[iCand_gen]<20){
				SkipReco=true;
				continue;
				}
			if(
				tree.pTD1_gen()[iCand_gen]>20 
				&& tree.pTD2_gen()[iCand_gen]>20
				&& abs(tree.EtaD1_gen()[iCand_gen])<2.4
				&& abs(tree.EtaD2_gen()[iCand_gen])<2.4
				&& tree.PID_gen()[iCand_gen] == 23
				//&& tree.mass()[tree.RecIdx_gen()[IndexMark]]>60
				//&& tree.mass()[tree.RecIdx_gen()[IndexMark]]<120
				){
				DenomGenCan->Fill(tree.pT_gen()[IndexMark], tree.y_gen()[iCand_gen]); //should be zero selection, redund because of previous line.
				//IndexMark=iCand_gen;
				break;
				}
			}
		if(SkipReco == true){continue;} //break to the next EVENT? 
		//*********************************
		//KINEMATIC
		// only negative
		//bool passNegY = 0>=tree.y()[tree.RecIdx_gen()[IndexMark]] && tree.y()[tree.RecIdx_gen()[IndexMark]]> -1.935;
		// only positive*****
		//bool passPosY = 0<=tree.y()[tree.RecIdx_gen()[IndexMark]] && tree.y()[tree.RecIdx_gen()[IndexMark]]<1.935;
		// PM eta
		bool passAllEtaD1D2 = abs(tree.EtaD1()[tree.RecIdx_gen()[IndexMark]])<2.4 && abs(tree.EtaD2()[tree.RecIdx_gen()[IndexMark]])<2.4;
		//bool passEtaZ = tree.eta()[iCand]<2.4;
		bool passpT = tree.pTD1()[tree.RecIdx_gen()[IndexMark]]>20 && tree.pTD2()[tree.RecIdx_gen()[IndexMark]]>20;          
		bool passMass = tree.mass()[tree.RecIdx_gen()[IndexMark]]>60 && tree.mass()[tree.RecIdx_gen()[IndexMark]]<120;
		//EVENT
		//const bool passTriggerMuonPair = tree.trigHLT()[1] && (tree.trigMuon1()[1].at(tree.RecIdx_gen()[IndexMark]) || tree.trigMuon2()[1].at(tree.RecIdx_gen()[IndexMark]));
		const bool pileUpCut = tree.evtSel()[4];
		const bool goodEvt = tree.evtSel()[0];
		//QUALITY
		bool passTightMuonPair = tree.tightMuon1()[tree.RecIdx_gen()[IndexMark]] && tree.tightMuon2()[tree.RecIdx_gen()[IndexMark]];
		//*********************************
		
		if(
			//Kinematic******
			(passAllEtaD1D2) 
			// passEtaZ
			&& (passpT) 
			&& (passMass) 
			//Event***********
			//&& (passTriggerMuonPair) 
			&& (pileUpCut)
			&& (goodEvt)
			//Quality*********
			&& (passTightMuonPair)
			){ passCut = true;}
		if(passCut){
			NumRecoCan->Fill(tree.pT_gen()[IndexMark],tree.y_gen()[IndexMark]);
			}
		passCut = false; 
		}
	NumRecoCan->Divide(DenomGenCan);
	Double_t See[pTbins];
	for(int j=1; j<ybins+1; j++){
		for(int i=1; i<pTbins+1; i++){
			See[i] = NumRecoCan->GetBinContent(i,j);
			std::cout << " * " << Form("%.3f",See[i]);
			}
		std::cout << " * " <<'\n';
		}

	for(int j=1; j<ybins+1; j++){
                for(int i=1; i<pTbins+1; i++){
                        newNRC->SetBinContent(i,j,1-(NumRecoCan->GetBinContent(i,j)));
			}
		}

	TCanvas* c1 = new TCanvas("c1", "", 1600, 800);
	c1->Divide(2,1);
	c1->cd(1);
	NumRecoCan ->Scale(100);
	NumRecoCan ->SetTitle("pPb MC Efficiency");
	NumRecoCan ->GetZaxis()->SetTitle("%");
        NumRecoCan ->GetZaxis()->SetRangeUser(0,100);
	NumRecoCan ->GetZaxis()->CenterTitle();
	NumRecoCan ->GetZaxis()->SetTitleOffset(1.5);
	NumRecoCan ->GetYaxis()->SetTitle("y_gen");
	NumRecoCan ->GetYaxis()->CenterTitle();
	NumRecoCan ->GetXaxis()->SetTitle("pT_gen");
	NumRecoCan ->GetXaxis()->CenterTitle();
	NumRecoCan ->GetYaxis()->SetTitleOffset(2);
	NumRecoCan ->GetXaxis()->SetTitleOffset(2);
	NumRecoCan ->SetStats(false);
	NumRecoCan ->Draw("Lego2");

	c1->cd(2);
        newNRC ->Scale(100);
        newNRC ->SetTitle("pPb MC Efficiency (100-%)");
        newNRC ->GetZaxis()->SetTitle("%");
        newNRC ->GetZaxis()->SetRangeUser(0,20);
        newNRC ->GetZaxis()->CenterTitle();
        newNRC ->GetZaxis()->SetTitleOffset(1.5);
        newNRC ->GetYaxis()->SetTitle("y_gen");
        newNRC ->GetYaxis()->CenterTitle();
        newNRC ->GetXaxis()->SetTitle("pT_gen");
        newNRC ->GetXaxis()->CenterTitle();
        newNRC ->GetYaxis()->SetTitleOffset(2);
        newNRC ->GetXaxis()->SetTitleOffset(2);
        newNRC ->SetStats(false);
        newNRC ->Draw("Lego2");

}
