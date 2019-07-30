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
	
	int NBINS=5;
        TH1D* DenomGenCan = new TH1D("DenomGenCan", "", NBINS,0,100);
        TH1D* NumRecoCan = new TH1D("NumRecoCan", "", NBINS,0,100);

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
			
			SkipReco = false;
			//Accounting for rapidity abd pseudorapidity when considering muon pT
			tree.eta()[iCand_gen]=(evtCol *    ( tree.eta()[iCand_gen] +0.465   ));
			tree.y()[iCand_gen]=(evtCol *      ( tree.y()[iCand_gen]   +0.465   ));
			

			//making cuts and filling the gen numerator for effiecency calc	
			if(tree.pTD1_gen()[iCand_gen]<20 || tree.pTD2_gen()[iCand_gen]<20){
				SkipReco=true;
				break;
				}
			if(tree.pTD1_gen()[iCand_gen]>20 && tree.pTD2_gen()[iCand_gen]>20){
				DenomGenCan->Fill(tree.pT()[iCand_gen]); //should be zero selection, redund because of previous line.
				IndexMark=iCand_gen;
				break;
				}
			}
		if(SkipReco){continue;} //break to the next EVENT? 
		//*********************************
		//KINEMATIC
		// only negative
		bool passNegY = 0>=tree.y()[tree.RecIdx_gen()[IndexMark]] && tree.y()[tree.RecIdx_gen()[IndexMark]]> -1.935;
		// only positive*****
		bool passPosY = 0<=tree.y()[tree.RecIdx_gen()[IndexMark]] && tree.y()[tree.RecIdx_gen()[IndexMark]]<1.935;
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
			//passEtaZ
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
			NumRecoCan->Fill(tree.pT()[tree.RecIdx_gen()[IndexMark]]);
			}
		passCut = false; 
		}
	NumRecoCan->Divide(DenomGenCan);
	for(int i=1; i<NBINS+1; i++){
		Double_t See =NumRecoCan->GetBinContent(i);
		std::cout <<  See  << std::endl;
		}
}
