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
#include "tnp_weight.h"



void test6()
{
	TH1::SetDefaultSumw2(kTRUE); //error is correct 

	//*********************************
	//Getting data/files
	//*********************************

	//const auto& treeDir = "dimucontana_mc"; // For MC use dimucontana_mc
	//const auto& inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_DYToMuMu_pPb-Bst_pPb816Summer16_DiMuMC.root";
                //VertexCompositeTree treepPb;
	//const auto& inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_DYToMuMu_PbP-Bst_pPb816Summer16_DiMuMC.root";
	        //VertexCompositeTree treePbP;

	int evtCol = 1; //pPb
        //evtCol = -1; //Pbp




	//*********************************
	//Creating histograms
	//*********************************
	const Int_t NBINS=1;
	const int pTbins=10;
	const int ybins=5;
	
	//Double_t edges[NBINS+1] = {0, 30, 60, 90, 120, 155, 190, 250};
        Double_t edges[NBINS+1] = {0,250};
 
        TH2D* DenomGenCan[NBINS];
	TH2D* NumRecoCan[NBINS];
        TH2D* newNRC[NBINS];
        
	TH1D* SF1h = new TH1D("SF1h", "",20, 0.8,1);
	TH1D* SF2h = new TH1D("SF2h", "",20, 0.8,1);
	TH1D* SF3Nh = new TH1D("SFNh", "",20, 0.8,1);
	TH1D* SF3Dh = new TH1D("SFDh", "",20, 0.8,1);
        TH1D* SFallh = new TH1D("SFallh", "",20, 0.8,1);

	float etaedge =2.4;
	float ptedge = 200;

        for(int ih=0; ih<NBINS; ih++){
                DenomGenCan[ih] = new TH2D(Form("DGC%d", ih), "", pTbins,0, ptedge, ybins, 0, etaedge);
                }
        for(int ih=0; ih<NBINS; ih++){
                NumRecoCan[ih] = new TH2D(Form("NRC%d", ih), "", pTbins,0, ptedge, ybins, 0, etaedge);
                }
        for(int ih=0; ih<NBINS; ih++){
                newNRC[ih] = new TH2D(Form("newNRC%d", ih), "", pTbins,0, ptedge, ybins, 0, etaedge);
                }

	//TH2D* DenomGenCan = new TH2D("DenomGenCan", "", pTbins,0,200, ybins, 0, 2.4);
        //TH2D* NumRecoCan = new TH2D("NumRecoCan", "", pTbins,0,200, ybins, 0, 2.4);
	//TH2D* newNRC = new TH2D("newNRC", "", pTbins,0,200, ybins, 0, 2.4);

        //*********************************
        //Primary loop
        //*********************************
	
	int IndexMark=1;
	
	for(int treechoice=0; treechoice<2;  treechoice++){

	std::string inputFile;
	VertexCompositeTree tree;
	if(treechoice == 0){
	inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_DYToMuMu_pPb-Bst_pPb816Summer16_DiMuMC.root";
	}

	if(treechoice == 1){
	inputFile = "/storage1/users/wl33/DiMuTrees/pPb2016/Tree/VertexCompositeTree_DYToMuMu_PbP-Bst_pPb816Summer16_DiMuMC.root";
	}

        const auto& treeDir = "dimucontana_mc"; // For MC use dimucontana_mc

	// For pPb, find out the run on data
	if (!tree.GetTree(inputFile, treeDir)){
		std::cout << "Invalid tree!" << std::endl; return; }
	long int nevents = tree.GetEntries();
	std::cout <<  nevents  << std::endl; 


	//for(long int jentry=0; jentry < nevents ; jentry++){
	//for(long int jentry=0; jentry < nevents; jentry++){
	for(long int jentry=0; jentry < nevents; jentry++){
		
		bool passCut = false;//reset at begining of loop.
                bool SkipReco = false;
		//int IndexMark;
		
		//Progress Marker
		if(!(jentry % 100000)){
			std::cout<<"Processed "<<jentry<<" events out of "<<nevents<<std::endl; }     
		if (tree.GetEntry(jentry)<0){
			std::cout << "Invalid entry!" << std::endl; return; }
		
		for(unsigned int iCand_gen=0; iCand_gen<tree.candSize_gen(); iCand_gen++){
			IndexMark=iCand_gen;
			SkipReco = false;
			//Accounting for rapidity abd pseudorapidity when considering muon pT
			tree.eta_gen()[iCand_gen]=(evtCol *    ( tree.eta_gen()[iCand_gen] +0.465   ));
			tree.y_gen()[iCand_gen]=(evtCol *      ( tree.y_gen()[iCand_gen]   +0.465   ));
			

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
					//Mu ID scale
					float idSF1 = tnp_weight_muid_ppb(tree.pTD1()[tree.RecIdx_gen()[IndexMark]], tree.EtaD1()[tree.RecIdx_gen()[IndexMark]] , 0);
					float idSF2 = tnp_weight_muid_ppb(tree.pTD2()[tree.RecIdx_gen()[IndexMark]], tree.EtaD2()[tree.RecIdx_gen()[IndexMark]] , 0);
					float idSF3Num = (1-(1-tnp_weight_trg_ppb(tree.EtaD1()[tree.RecIdx_gen()[IndexMark]], 200))*(1-tnp_weight_trg_ppb(tree.EtaD2()[tree.RecIdx_gen()[IndexMark]], 200)));
                                        float idSF3Den = (1-(1-tnp_weight_trg_ppb(tree.EtaD1()[tree.RecIdx_gen()[IndexMark]], 300))*(1-tnp_weight_trg_ppb(tree.EtaD2()[tree.RecIdx_gen()[IndexMark]], 300)));
					float SF=idSF1*idSF2*idSF3Num/idSF3Den;
                                	SF1h->Fill(idSF1);
                                        SF2h->Fill(idSF2);
                                        SF3Nh->Fill(idSF3Num);
                                        SF3Dh->Fill(idSF3Den);
					SFallh->Fill(SF);
					NumRecoCan[ih]->Fill(tree.pT_gen()[IndexMark],tree.y_gen()[IndexMark], SF);
					}
				}
			}
		passCut = false; 
		}

	}
	int Entry4 = NumRecoCan[0]->GetEntries();
	int Entry5 = DenomGenCan[0]->GetEntries();

	for(int ih=0; ih<NBINS; ih++){
		std::cout << "Array for Ntrk Bin #" << ih;
		std::cout << " * " <<'\n';
		NumRecoCan[ih]->Divide(DenomGenCan[ih]);
		Double_t See[pTbins];
		for(int j=0; j<ybins; j++){
			for(int i=0; i<pTbins; i++){
				See[i] = NumRecoCan[ih]->GetBinContent(i+1,j+1);
				std::cout << " * " << Form("%.3f",See[i]);
				}
			std::cout << " * " <<'\n';
			}
	
		for(int j=0; j<ybins; j++){
	                for(int i=0; i<pTbins; i++){
	                        newNRC[ih]->SetBinContent(i+1,j+1,1-(NumRecoCan[ih]->GetBinContent(i+1,j+1)));
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

	//std::vector<float> xvec;
	
	//This set up will give me several lines of % verus pT axis. lines split by y 
	float xvecpT[ybins][pTbins];
	float yvecpT[ybins][pTbins];
        float yvecpTE[ybins][pTbins];
	float xvecpTEX[ybins][pTbins]={0.};	

	//This set up will give me several lines of % verus y axis. lines split by pT
	
	float xvecy[pTbins][ybins];
	float yvecy[pTbins][ybins];
        float yvecyE[pTbins][ybins];
	float xvecyEX[pTbins][ybins]={0.};

	for(int ih=0; ih<pTbins; ih++){
		for(int jh=0; jh<ybins; jh++){
			
			xvecy[ih][jh]=((TAxis*)NumRecoCan[0]->GetYaxis())->GetBinCenter(jh+1);
			yvecy[ih][jh]=NumRecoCan[0]->GetBinContent(ih+1,jh+1);
			yvecyE[ih][jh]=NumRecoCan[0]->GetBinError(ih+1,jh+1);
			}
		}



        for(int ih=0; ih<ybins; ih++){
                for(int jh=0; jh<pTbins; jh++){
                
                        xvecpT[ih][jh]=((TAxis*)NumRecoCan[0]->GetXaxis())->GetBinCenter(jh+1);
                        yvecpT[ih][jh]=NumRecoCan[0]->GetBinContent(jh+1,ih+1);
                        yvecpTE[ih][jh]=NumRecoCan[0]->GetBinError(jh+1,ih+1);
			}
                }
	
        TCanvas* cXY1 = new TCanvas("cXY1", "", 1300, 650);
	int XCI[ybins]={1,2,3,4,5};
        int YCI[pTbins]={0,1,2,3,4,5,6,7,8,9};
        cXY1->Divide(2,1);

        std::vector<TGraphErrors*> cx;
        std::vector<TGraphErrors*> cy;


	cXY1->SetFillColor(42);
        TMultiGraph *mgx = new TMultiGraph();
        TMultiGraph *mgy = new TMultiGraph();

        //cx[0]=new TGraphErrors(pTbins,xvecpT[0],yvecpT[0],xvecpTEX[0],yvecpTE[0]);
	//cx[0]->Draw("AP");

	for(int ih=0; ih<ybins; ih++){
		cx.push_back(new TGraphErrors(pTbins,xvecpT[ih],yvecpT[ih],xvecpTEX[ih],yvecpTE[ih]));
		cx[ih]->SetMarkerStyle(22);
                cx[ih]->SetLineColor(XCI[ih]);
		mgx->Add(cx[ih],"ALP");
		}
        for(int ih=0; ih<pTbins; ih++){
                cy.push_back(new TGraphErrors(ybins,xvecy[ih],yvecy[ih],xvecyEX[ih],yvecyE[ih]));
                cy[ih]->SetMarkerStyle(22);
                cy[ih]->SetLineColor(YCI[ih]);
                mgy->Add(cy[ih],"ALP");
                }

cXY1->cd(1);
cXY1->cd(1)->SetFillColor(42);
mgx->Draw("ALP");
cXY1->cd(2);
cXY1->cd(2)->SetFillColor(42);
mgy->Draw("ALP");

TCanvas* cSF = new TCanvas("SF", "", 1400, 650);
cSF->Divide(2,2);


cSF->cd(1);
gPad->SetLogy(1);
SF1h ->SetTitle("SF1h");
SF1h->Draw();

cSF->cd(2);
gPad->SetLogy(1);
SF1h ->SetTitle("SF2h");
SF2h->Draw();

cSF->cd(3);
gPad->SetLogy(1);
SF1h ->SetTitle("SF3Nh");
SF3Nh->Draw();

cSF->cd(4);
gPad->SetLogy(1);
SF1h ->SetTitle("SF3Dh");
SF3Dh->Draw();

TCanvas* cSFall = new TCanvas("SFall", "", 800, 800);
gPad->SetLogy(1); 
SF1h ->SetTitle("SFall");
SFallh->Draw();


int Entry1 = NumRecoCan[0]->GetEntries();
int Entry2 = newNRC[0]->GetEntries();
int Entry3 = SFallh->GetEntries();


std::cout << "NRC/denom " << Entry1 <<'\n';

std::cout << "newNRC " << Entry2 <<'\n';

std::cout << "SFall " << Entry3 <<'\n';

std::cout << "Num " << Entry4 <<'\n';

std::cout << "Denom " << Entry5 <<'\n';


}
