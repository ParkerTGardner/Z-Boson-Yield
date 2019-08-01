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

void test6()
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
	const Int_t NBINS=1;
	int pTbins=5;
	int ybins=5;
	
	//Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 250};
        Double_t edges[NBINS+1] = {0,250};
 
        TH2D* DenomGenCan[NBINS];
	TH2D* NumRecoCan[NBINS];
        TH2D* newNRC[NBINS];

        for(int ih=0; ih<NBINS; ih++){
                DenomGenCan[ih] = new TH2D(Form("DGC%d", ih), "", pTbins,0, 200, ybins, 0, 2.4);
                }
        for(int ih=0; ih<NBINS; ih++){
                NumRecoCan[ih] = new TH2D(Form("NRC%d", ih), "", pTbins,0, 200, ybins, 0, 2.4);
                }
        for(int ih=0; ih<NBINS; ih++){
                newNRC[ih] = new TH2D(Form("newNRC%d", ih), "", pTbins,0, 200, ybins, 0, 2.4);
                }

	//TH2D* DenomGenCan = new TH2D("DenomGenCan", "", pTbins,0,200, ybins, 0, 2.4);
        //TH2D* NumRecoCan = new TH2D("NumRecoCan", "", pTbins,0,200, ybins, 0, 2.4);
	//TH2D* newNRC = new TH2D("newNRC", "", pTbins,0,200, ybins, 0, 2.4);

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
				for(int ih=0; ih<NBINS; ih++){
					if(tree.Ntrkoffline() > edges[ih] && tree.Ntrkoffline() < edges[ih+1]){	
						DenomGenCan[ih]->Fill(tree.pT_gen()[IndexMark], tree.y_gen()[iCand_gen]); //should be zero selection, redund because of previous line.
					}	
				}
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
			for(int ih=0; ih<NBINS; ih++){
				if(tree.Ntrkoffline() > edges[ih] && tree.Ntrkoffline() < edges[ih+1]){
					NumRecoCan[ih]->Fill(tree.pT_gen()[IndexMark],tree.y_gen()[IndexMark]);
					}
				}
			}
		passCut = false; 
		}


	for(int ih=0; ih<NBINS; ih++){
		std::cout << "Array for Ntrk Bin #" << ih;
		std::cout << " * " <<'\n';
		NumRecoCan[ih]->Divide(DenomGenCan[ih]);
		Double_t See[pTbins];
		for(int j=1; j<ybins+1; j++){
			for(int i=1; i<pTbins+1; i++){
				See[i] = NumRecoCan[ih]->GetBinContent(i,j);
				std::cout << " * " << Form("%.3f",See[i]);
				}
			std::cout << " * " <<'\n';
			}
	
		for(int j=1; j<ybins+1; j++){
	                for(int i=1; i<pTbins+1; i++){
	                        newNRC[ih]->SetBinContent(i,j,1-(NumRecoCan[ih]->GetBinContent(i,j)));
				}
			}
		}



	
	//Option_t* c;
	//c={"c1","c2","c3"};
    	std::vector<TCanvas*> c;
	for(int ih=0; ih<NBINS; ih++){
		c.push_back(new TCanvas(Form("c%d",ih), "", 1300, 650));
		c[ih]->Divide(2,1);
	
		c[ih]->cd(1);
		NumRecoCan[ih] ->Scale(100);
		NumRecoCan[ih] ->SetTitle(Form("pPb MC Efficiency Ntrk %d", ih));
		NumRecoCan[ih] ->GetZaxis()->SetTitle("%");
	        NumRecoCan[ih] ->GetZaxis()->SetRangeUser(0,100);
		NumRecoCan[ih] ->GetZaxis()->CenterTitle();
		NumRecoCan[ih] ->GetZaxis()->SetTitleOffset(1.5);
		NumRecoCan[ih] ->GetYaxis()->SetTitle("y_gen");
		NumRecoCan[ih] ->GetYaxis()->CenterTitle();
		NumRecoCan[ih] ->GetXaxis()->SetTitle("pT_gen");
		NumRecoCan[ih] ->GetXaxis()->CenterTitle();
		NumRecoCan[ih] ->GetYaxis()->SetTitleOffset(2);
		NumRecoCan[ih] ->GetXaxis()->SetTitleOffset(2);
		NumRecoCan[ih] ->SetStats(false);
		NumRecoCan[ih] ->Draw("Lego2");
		
		c[ih]->cd(2);
	        newNRC[ih] ->Scale(100);
	        newNRC[ih] ->SetTitle(Form("pPb MC Efficiency Ntrk %d 100_minus",ih));
	        newNRC[ih] ->GetZaxis()->SetTitle("%");
	        newNRC[ih] ->GetZaxis()->SetRangeUser(0,100);
	        newNRC[ih] ->GetZaxis()->CenterTitle();
	        newNRC[ih] ->GetZaxis()->SetTitleOffset(1.5);
	        newNRC[ih] ->GetYaxis()->SetTitle("y_gen");
	        newNRC[ih] ->GetYaxis()->CenterTitle();
	        newNRC[ih] ->GetXaxis()->SetTitle("pT_gen");
	        newNRC[ih] ->GetXaxis()->CenterTitle();
	        newNRC[ih] ->GetYaxis()->SetTitleOffset(2);
	        newNRC[ih] ->GetXaxis()->SetTitleOffset(2);
	        newNRC[ih] ->SetStats(false);
	        newNRC[ih] ->Draw("Lego2");
		}


//        c3->cd(1);
//        NumRecoCan[2] ->Scale(100);
//        NumRecoCan[2] ->SetTitle("pPb MC Efficiency Ntrk3");
//        NumRecoCan[2] ->GetZaxis()->SetTitle("%");
//        NumRecoCan[2] ->GetZaxis()->SetRangeUser(0,100);
//        NumRecoCan[2] ->GetZaxis()->CenterTitle();
//        NumRecoCan[2] ->GetZaxis()->SetTitleOffset(1.5);
//        NumRecoCan[2] ->GetYaxis()->SetTitle("y_gen");
//        NumRecoCan[2] ->GetYaxis()->CenterTitle();
//        NumRecoCan[2] ->GetXaxis()->SetTitle("pT_gen");
//        NumRecoCan[2] ->GetXaxis()->CenterTitle();
//        NumRecoCan[2] ->GetYaxis()->SetTitleOffset(2);
//        NumRecoCan[2] ->GetXaxis()->SetTitleOffset(2);
//        NumRecoCan[2] ->SetStats(false);
//        NumRecoCan[2] ->Draw("Lego2");
//
//        c3->cd(2);
//        newNRC[2] ->Scale(100);
//        newNRC[2] ->SetTitle("pPb MC Efficiency Ntrk3 (100-%)");
//        newNRC[2] ->GetZaxis()->SetTitle("%");
//        newNRC[2] ->GetZaxis()->SetRangeUser(0,20);
//        newNRC[2] ->GetZaxis()->CenterTitle();
//        newNRC[2] ->GetZaxis()->SetTitleOffset(1.5);
//        newNRC[2] ->GetYaxis()->SetTitle("y_gen");
//        newNRC[2] ->GetYaxis()->CenterTitle();
//        newNRC[2] ->GetXaxis()->SetTitle("pT_gen");
//        newNRC[2] ->GetXaxis()->CenterTitle();
//        newNRC[2] ->GetYaxis()->SetTitleOffset(2);
//        newNRC[2] ->GetXaxis()->SetTitleOffset(2);
//        newNRC[2] ->SetStats(false);
//        newNRC[2] ->Draw("Lego2");
//
//        c2->cd(1);
//        NumRecoCan[1] ->Scale(100);
//        NumRecoCan[1] ->SetTitle("pPb MC Efficiency Ntrk2");
//        NumRecoCan[1] ->GetZaxis()->SetTitle("%");
//        NumRecoCan[1] ->GetZaxis()->SetRangeUser(0,100);
//        NumRecoCan[1] ->GetZaxis()->CenterTitle();
//        NumRecoCan[1] ->GetZaxis()->SetTitleOffset(1.5);
//        NumRecoCan[1] ->GetYaxis()->SetTitle("y_gen");
//        NumRecoCan[1] ->GetYaxis()->CenterTitle();
//        NumRecoCan[1] ->GetXaxis()->SetTitle("pT_gen");
//        NumRecoCan[1] ->GetXaxis()->CenterTitle();
//        NumRecoCan[1] ->GetYaxis()->SetTitleOffset(2);
//        NumRecoCan[1] ->GetXaxis()->SetTitleOffset(2);
//        NumRecoCan[1] ->SetStats(false);
//        NumRecoCan[1] ->Draw("Lego2");
//
//        c2->cd(2);
//        newNRC[1] ->Scale(100);
//        newNRC[1] ->SetTitle("pPb MC Efficiency Ntrk2 (100-%)");
//        newNRC[1] ->GetZaxis()->SetTitle("%");
//        newNRC[1] ->GetZaxis()->SetRangeUser(0,20);
//        newNRC[1] ->GetZaxis()->CenterTitle();
//        newNRC[1] ->GetZaxis()->SetTitleOffset(1.5);
//        newNRC[1] ->GetYaxis()->SetTitle("y_gen");
//        newNRC[1] ->GetYaxis()->CenterTitle();
//        newNRC[1] ->GetXaxis()->SetTitle("pT_gen");
//        newNRC[1] ->GetXaxis()->CenterTitle();
//        newNRC[1] ->GetYaxis()->SetTitleOffset(2);
//        newNRC[1] ->GetXaxis()->SetTitleOffset(2);
//        newNRC[1] ->SetStats(false);
//        newNRC[1] ->Draw("Lego2");

}
