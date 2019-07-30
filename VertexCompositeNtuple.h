//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May  8 14:30:48 2019 by ROOT version 6.06/01
// from TTree VertexCompositeNtuple/VertexCompositeNtuple
// found on file: /storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root
//////////////////////////////////////////////////////////

#ifndef VertexCompositeNtuple_h
#define VertexCompositeNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"

// Header file for the classes stored in the TTree if any.
#include "vector"

class VertexCompositeNtuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          RunNb;
   UInt_t          LSNb;
   UInt_t          EventNb;
   Short_t         nPV;
   Float_t         bestvtxX;
   Float_t         bestvtxY;
   Float_t         bestvtxZ;
   UInt_t          candSize;
   Short_t         centrality;
   Int_t           Npixel;
   Float_t         HFsumETPlus;
   Float_t         HFsumETMinus;
   Float_t         ZDCPlus;
   Float_t         ZDCMinus;
   Int_t           Ntrkoffline;
   Float_t         ephfpAngle[3];
   Float_t         ephfmAngle[3];
   Float_t         ephfpQ[3];
   Float_t         ephfmQ[3];
   Float_t         ephfpSumW;
   Float_t         ephfmSumW;
   Short_t         trigPrescale[8];
   Bool_t          trigHLT[8];
   Bool_t          evtSel[4];
   Float_t         pT[16];   //[candSize]
   Float_t         eta[16];   //[candSize]
   Float_t         phi[16];   //[candSize]
   Float_t         mass[16];   //[candSize]
   Float_t         y[16];   //[candSize]
   Float_t         flavor[16];   //[candSize]
   Float_t         VtxProb[16];   //[candSize]
   Float_t         m3DCosPointingAngle[16];   //[candSize]
   Float_t         m3DPointingAngle[16];   //[candSize]
   Float_t         m2DCosPointingAngle[16];   //[candSize]
   Float_t         m2DPointingAngle[16];   //[candSize]
   Float_t         m3DDecayLengthSignificance[16];   //[candSize]
   Float_t         m3DDecayLength[16];   //[candSize]
   Float_t         m3DDecayLengthError[16];   //[candSize]
   Float_t         m2DDecayLengthSignificance[16];   //[candSize]
   Float_t         m2DDecayLength[16];   //[candSize]
   Float_t         zDCASignificanceDaugther1[16];   //[candSize]
   Float_t         xyDCASignificanceDaugther1[16];   //[candSize]
   Float_t         NHitD1[16];   //[candSize]
   Bool_t          HighPurityDaugther1[16];   //[candSize]
   Float_t         pTD1[16];   //[candSize]
   Float_t         pTerrD1[16];   //[candSize]
   Float_t         EtaD1[16];   //[candSize]
   Float_t         PhiD1[16];   //[candSize]
   Short_t         chargeD1[16];   //[candSize]
   Float_t         zDCASignificanceDaugther2[16];   //[candSize]
   Float_t         xyDCASignificanceDaugther2[16];   //[candSize]
   Float_t         NHitD2[16];   //[candSize]
   Bool_t          HighPurityDaugther2[16];   //[candSize]
   Float_t         pTD2[16];   //[candSize]
   Float_t         pTerrD2[16];   //[candSize]
   Float_t         EtaD2[16];   //[candSize]
   Float_t         PhiD2[16];   //[candSize]
   Short_t         chargeD2[16];   //[candSize]
   Bool_t          OneStMuon1[16];   //[candSize]
   Bool_t          PFMuon1[16];   //[candSize]
   Bool_t          GlbMuon1[16];   //[candSize]
   Bool_t          trkMuon1[16];   //[candSize]
   Bool_t          tightMuon1[16];   //[candSize]
   Bool_t          softMuon1[16];   //[candSize]
   Bool_t          hybridMuon1[16];   //[candSize]
   Bool_t          HPMuon1[16];   //[candSize]
   vector<vector<unsigned char> > *trigMuon1;

   vector<vector<unsigned char>> TrigMuon1(){return *trigMuon1;}
   Short_t         nMatchedStationD1[16];   //[candSize]
   Short_t         nTrackerLayerD1[16];   //[candSize]
   Short_t         nPixelLayerD1[16];   //[candSize]
   Short_t         nPixelHitD1[16];   //[candSize]
   Short_t         nMuonHitD1[16];   //[candSize]
   Float_t         GlbTrkChiD1[16];   //[candSize]
   Float_t         muondXYD1[16];   //[candSize]
   Float_t         muondZD1[16];   //[candSize]
   Float_t         dXYD1[16];   //[candSize]
   Float_t         dZD1[16];   //[candSize]
   Short_t         nMatchedChamberD1[16];   //[candSize]
   Float_t         EnergyDepositionD1[16];   //[candSize]
   Float_t         dx1_seg[16];   //[candSize]
   Float_t         dy1_seg[16];   //[candSize]
   Float_t         dxSig1_seg[16];   //[candSize]
   Float_t         dySig1_seg[16];   //[candSize]
   Float_t         ddxdz1_seg[16];   //[candSize]
   Float_t         ddydz1_seg[16];   //[candSize]
   Float_t         ddxdzSig1_seg[16];   //[candSize]
   Float_t         ddydzSig1_seg[16];   //[candSize]
   Bool_t          OneStMuon2[16];   //[candSize]
   Bool_t          PFMuon2[16];   //[candSize]
   Bool_t          GlbMuon2[16];   //[candSize]
   Bool_t          trkMuon2[16];   //[candSize]
   Bool_t          tightMuon2[16];   //[candSize]
   Bool_t          softMuon2[16];   //[candSize]
   Bool_t          hybridMuon2[16];   //[candSize]
   Bool_t          HPMuon2[16];   //[candSize]
   vector<vector<unsigned char> > *trigMuon2;
   Short_t         nMatchedStationD2[16];   //[candSize]
   Short_t         nTrackerLayerD2[16];   //[candSize]
   Short_t         nPixelLayerD2[16];   //[candSize]
   Short_t         nPixelHitD2[16];   //[candSize]
   Short_t         nMuonHitD2[16];   //[candSize]
   Float_t         GlbTrkChiD2[16];   //[candSize]
   Float_t         muondXYD2[16];   //[candSize]
   Float_t         muondZD2[16];   //[candSize]
   Float_t         dXYD2[16];   //[candSize]
   Float_t         dZD2[16];   //[candSize]
   Short_t         nMatchedChamberD2[16];   //[candSize]
   Float_t         EnergyDepositionD2[16];   //[candSize]
   Float_t         dx2_seg[16];   //[candSize]
   Float_t         dy2_seg[16];   //[candSize]
   Float_t         dxSig2_seg[16];   //[candSize]
   Float_t         dySig2_seg[16];   //[candSize]
   Float_t         ddxdz2_seg[16];   //[candSize]
   Float_t         ddydz2_seg[16];   //[candSize]
   Float_t         ddxdzSig2_seg[16];   //[candSize]
   Float_t         ddydzSig2_seg[16];   //[candSize]

   // List of branches
   TBranch        *b_RunNb;   //!
   TBranch        *b_LSNb;   //!
   TBranch        *b_EventNb;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_bestvtxX;   //!
   TBranch        *b_bestvtxY;   //!
   TBranch        *b_bestvtxZ;   //!
   TBranch        *b_candSize;   //!
   TBranch        *b_centrality;   //!
   TBranch        *b_Npixel;   //!
   TBranch        *b_HFsumETPlus;   //!
   TBranch        *b_HFsumETMinus;   //!
   TBranch        *b_ZDCPlus;   //!
   TBranch        *b_ZDCMinus;   //!
   TBranch        *b_Ntrkoffline;   //!
   TBranch        *b_ephfpAngle;   //!
   TBranch        *b_ephfmAngle;   //!
   TBranch        *b_ephfpQ;   //!
   TBranch        *b_ephfmQ;   //!
   TBranch        *b_ephfpSumW;   //!
   TBranch        *b_ephfmSumW;   //!
   TBranch        *b_trigPrescale;   //!
   TBranch        *b_trigHLT;   //!
   TBranch        *b_evtSel;   //!
   TBranch        *b_pT;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_y;   //!
   TBranch        *b_flavor;   //!
   TBranch        *b_VtxProb;   //!
   TBranch        *b_3DCosPointingAngle;   //!
   TBranch        *b_3DPointingAngle;   //!
   TBranch        *b_2DCosPointingAngle;   //!
   TBranch        *b_2DPointingAngle;   //!
   TBranch        *b_3DDecayLengthSignificance;   //!
   TBranch        *b_3DDecayLength;   //!
   TBranch        *b_3DDecayLengthError;   //!
   TBranch        *b_2DDecayLengthSignificance;   //!
   TBranch        *b_2DDecayLength;   //!
   TBranch        *b_zDCASignificanceDaugther1;   //!
   TBranch        *b_xyDCASignificanceDaugther1;   //!
   TBranch        *b_NHitD1;   //!
   TBranch        *b_HighPurityDaugther1;   //!
   TBranch        *b_pTD1;   //!
   TBranch        *b_pTerrD1;   //!
   TBranch        *b_EtaD1;   //!
   TBranch        *b_PhiD1;   //!
   TBranch        *b_chargeD1;   //!
   TBranch        *b_zDCASignificanceDaugther2;   //!
   TBranch        *b_xyDCASignificanceDaugther2;   //!
   TBranch        *b_NHitD2;   //!
   TBranch        *b_HighPurityDaugther2;   //!
   TBranch        *b_pTD2;   //!
   TBranch        *b_pTerrD2;   //!
   TBranch        *b_EtaD2;   //!
   TBranch        *b_PhiD2;   //!
   TBranch        *b_chargeD2;   //!
   TBranch        *b_OneStMuon1;   //!
   TBranch        *b_PFMuon1;   //!
   TBranch        *b_GlbMuon1;   //!
   TBranch        *b_trkMuon1;   //!
   TBranch        *b_tightMuon1;   //!
   TBranch        *b_softMuon1;   //!
   TBranch        *b_hybridMuon1;   //!
   TBranch        *b_HPMuon1;   //!
   TBranch        *b_trigMuon1;   //!
   TBranch        *b_nMatchedStationD1;   //!
   TBranch        *b_nTrackerLayerD1;   //!
   TBranch        *b_nPixelLayerD1;   //!
   TBranch        *b_nPixelHitD1;   //!
   TBranch        *b_nMuonHitD1;   //!
   TBranch        *b_GlbTrkChiD1;   //!
   TBranch        *b_muondXYD1;   //!
   TBranch        *b_muondZD1;   //!
   TBranch        *b_dXYD1;   //!
   TBranch        *b_dZD1;   //!
   TBranch        *b_nMatchedChamberD1;   //!
   TBranch        *b_EnergyDepositionD1;   //!
   TBranch        *b_dx1_seg;   //!
   TBranch        *b_dy1_seg;   //!
   TBranch        *b_dxSig1_seg;   //!
   TBranch        *b_dySig1_seg;   //!
   TBranch        *b_ddxdz1_seg;   //!
   TBranch        *b_ddydz1_seg;   //!
   TBranch        *b_ddxdzSig1_seg;   //!
   TBranch        *b_ddydzSig1_seg;   //!
   TBranch        *b_OneStMuon2;   //!
   TBranch        *b_PFMuon2;   //!
   TBranch        *b_GlbMuon2;   //!
   TBranch        *b_trkMuon2;   //!
   TBranch        *b_tightMuon2;   //!
   TBranch        *b_softMuon2;   //!
   TBranch        *b_hybridMuon2;   //!
   TBranch        *b_HPMuon2;   //!
   TBranch        *b_trigMuon2;   //!
   TBranch        *b_nMatchedStationD2;   //!
   TBranch        *b_nTrackerLayerD2;   //!
   TBranch        *b_nPixelLayerD2;   //!
   TBranch        *b_nPixelHitD2;   //!
   TBranch        *b_nMuonHitD2;   //!
   TBranch        *b_GlbTrkChiD2;   //!
   TBranch        *b_muondXYD2;   //!
   TBranch        *b_muondZD2;   //!
   TBranch        *b_dXYD2;   //!
   TBranch        *b_dZD2;   //!
   TBranch        *b_nMatchedChamberD2;   //!
   TBranch        *b_EnergyDepositionD2;   //!
   TBranch        *b_dx2_seg;   //!
   TBranch        *b_dy2_seg;   //!
   TBranch        *b_dxSig2_seg;   //!
   TBranch        *b_dySig2_seg;   //!
   TBranch        *b_ddxdz2_seg;   //!
   TBranch        *b_ddydz2_seg;   //!
   TBranch        *b_ddxdzSig2_seg;   //!
   TBranch        *b_ddydzSig2_seg;   //!

   VertexCompositeNtuple(TTree *tree=0);
   virtual ~VertexCompositeNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t    GetEntries() {return fChain->GetEntries();}
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(){};
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifndef VertexCompositeNtuple_cxx
#define VertexCompositeNtuple_cxx
VertexCompositeNtuple::VertexCompositeNtuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/storage1/users/wl33/DiMuTrees/PbPb2018/Tree/VertexCompositeTree_HISingleMuon_HIRun2018_DiMuMassMin7.root:/dimucontana");
      dir->GetObject("VertexCompositeNtuple",tree);

   }
   Init(tree);
}

VertexCompositeNtuple::~VertexCompositeNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t VertexCompositeNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t VertexCompositeNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void VertexCompositeNtuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trigMuon1 = 0;
   trigMuon2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNb", &RunNb, &b_RunNb);
   fChain->SetBranchAddress("LSNb", &LSNb, &b_LSNb);
   fChain->SetBranchAddress("EventNb", &EventNb, &b_EventNb);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("bestvtxX", &bestvtxX, &b_bestvtxX);
   fChain->SetBranchAddress("bestvtxY", &bestvtxY, &b_bestvtxY);
   fChain->SetBranchAddress("bestvtxZ", &bestvtxZ, &b_bestvtxZ);
   fChain->SetBranchAddress("candSize", &candSize, &b_candSize);
   fChain->SetBranchAddress("centrality", &centrality, &b_centrality);
   fChain->SetBranchAddress("Npixel", &Npixel, &b_Npixel);
   fChain->SetBranchAddress("HFsumETPlus", &HFsumETPlus, &b_HFsumETPlus);
   fChain->SetBranchAddress("HFsumETMinus", &HFsumETMinus, &b_HFsumETMinus);
   fChain->SetBranchAddress("ZDCPlus", &ZDCPlus, &b_ZDCPlus);
   fChain->SetBranchAddress("ZDCMinus", &ZDCMinus, &b_ZDCMinus);
   fChain->SetBranchAddress("Ntrkoffline", &Ntrkoffline, &b_Ntrkoffline);
   fChain->SetBranchAddress("ephfpAngle", ephfpAngle, &b_ephfpAngle);
   fChain->SetBranchAddress("ephfmAngle", ephfmAngle, &b_ephfmAngle);
   fChain->SetBranchAddress("ephfpQ", ephfpQ, &b_ephfpQ);
   fChain->SetBranchAddress("ephfmQ", ephfmQ, &b_ephfmQ);
   fChain->SetBranchAddress("ephfpSumW", &ephfpSumW, &b_ephfpSumW);
   fChain->SetBranchAddress("ephfmSumW", &ephfmSumW, &b_ephfmSumW);
   fChain->SetBranchAddress("trigPrescale", trigPrescale, &b_trigPrescale);
   fChain->SetBranchAddress("trigHLT", trigHLT, &b_trigHLT);
   fChain->SetBranchAddress("evtSel", evtSel, &b_evtSel);
   fChain->SetBranchAddress("pT", pT, &b_pT);
   fChain->SetBranchAddress("eta", eta, &b_eta);
   fChain->SetBranchAddress("phi", phi, &b_phi);
   fChain->SetBranchAddress("mass", mass, &b_mass);
   fChain->SetBranchAddress("y", y, &b_y);
   fChain->SetBranchAddress("flavor", flavor, &b_flavor);
   fChain->SetBranchAddress("VtxProb", VtxProb, &b_VtxProb);
   fChain->SetBranchAddress("3DCosPointingAngle", m3DCosPointingAngle, &b_3DCosPointingAngle);
   fChain->SetBranchAddress("3DPointingAngle", m3DPointingAngle, &b_3DPointingAngle);
   fChain->SetBranchAddress("2DCosPointingAngle", m2DCosPointingAngle, &b_2DCosPointingAngle);
   fChain->SetBranchAddress("2DPointingAngle", m2DPointingAngle, &b_2DPointingAngle);
   fChain->SetBranchAddress("3DDecayLengthSignificance", m3DDecayLengthSignificance, &b_3DDecayLengthSignificance);
   fChain->SetBranchAddress("3DDecayLength", m3DDecayLength, &b_3DDecayLength);
   fChain->SetBranchAddress("3DDecayLengthError", m3DDecayLengthError, &b_3DDecayLengthError);
   fChain->SetBranchAddress("2DDecayLengthSignificance", m2DDecayLengthSignificance, &b_2DDecayLengthSignificance);
   fChain->SetBranchAddress("2DDecayLength", m2DDecayLength, &b_2DDecayLength);
   fChain->SetBranchAddress("zDCASignificanceDaugther1", zDCASignificanceDaugther1, &b_zDCASignificanceDaugther1);
   fChain->SetBranchAddress("xyDCASignificanceDaugther1", xyDCASignificanceDaugther1, &b_xyDCASignificanceDaugther1);
   fChain->SetBranchAddress("NHitD1", NHitD1, &b_NHitD1);
   fChain->SetBranchAddress("HighPurityDaugther1", HighPurityDaugther1, &b_HighPurityDaugther1);
   fChain->SetBranchAddress("pTD1", pTD1, &b_pTD1);
   fChain->SetBranchAddress("pTerrD1", pTerrD1, &b_pTerrD1);
   fChain->SetBranchAddress("EtaD1", EtaD1, &b_EtaD1);
   fChain->SetBranchAddress("PhiD1", PhiD1, &b_PhiD1);
   fChain->SetBranchAddress("chargeD1", chargeD1, &b_chargeD1);
   fChain->SetBranchAddress("zDCASignificanceDaugther2", zDCASignificanceDaugther2, &b_zDCASignificanceDaugther2);
   fChain->SetBranchAddress("xyDCASignificanceDaugther2", xyDCASignificanceDaugther2, &b_xyDCASignificanceDaugther2);
   fChain->SetBranchAddress("NHitD2", NHitD2, &b_NHitD2);
   fChain->SetBranchAddress("HighPurityDaugther2", HighPurityDaugther2, &b_HighPurityDaugther2);
   fChain->SetBranchAddress("pTD2", pTD2, &b_pTD2);
   fChain->SetBranchAddress("pTerrD2", pTerrD2, &b_pTerrD2);
   fChain->SetBranchAddress("EtaD2", EtaD2, &b_EtaD2);
   fChain->SetBranchAddress("PhiD2", PhiD2, &b_PhiD2);
   fChain->SetBranchAddress("chargeD2", chargeD2, &b_chargeD2);
   fChain->SetBranchAddress("OneStMuon1", OneStMuon1, &b_OneStMuon1);
   fChain->SetBranchAddress("PFMuon1", PFMuon1, &b_PFMuon1);
   fChain->SetBranchAddress("GlbMuon1", GlbMuon1, &b_GlbMuon1);
   fChain->SetBranchAddress("trkMuon1", trkMuon1, &b_trkMuon1);
   fChain->SetBranchAddress("tightMuon1", tightMuon1, &b_tightMuon1);
   fChain->SetBranchAddress("softMuon1", softMuon1, &b_softMuon1);
   fChain->SetBranchAddress("hybridMuon1", hybridMuon1, &b_hybridMuon1);
   fChain->SetBranchAddress("HPMuon1", HPMuon1, &b_HPMuon1);
   fChain->SetBranchAddress("trigMuon1", &trigMuon1, &b_trigMuon1);
   fChain->SetBranchAddress("nMatchedStationD1", nMatchedStationD1, &b_nMatchedStationD1);
   fChain->SetBranchAddress("nTrackerLayerD1", nTrackerLayerD1, &b_nTrackerLayerD1);
   fChain->SetBranchAddress("nPixelLayerD1", nPixelLayerD1, &b_nPixelLayerD1);
   fChain->SetBranchAddress("nPixelHitD1", nPixelHitD1, &b_nPixelHitD1);
   fChain->SetBranchAddress("nMuonHitD1", nMuonHitD1, &b_nMuonHitD1);
   fChain->SetBranchAddress("GlbTrkChiD1", GlbTrkChiD1, &b_GlbTrkChiD1);
   fChain->SetBranchAddress("muondXYD1", muondXYD1, &b_muondXYD1);
   fChain->SetBranchAddress("muondZD1", muondZD1, &b_muondZD1);
   fChain->SetBranchAddress("dXYD1", dXYD1, &b_dXYD1);
   fChain->SetBranchAddress("dZD1", dZD1, &b_dZD1);
   fChain->SetBranchAddress("nMatchedChamberD1", nMatchedChamberD1, &b_nMatchedChamberD1);
   fChain->SetBranchAddress("EnergyDepositionD1", EnergyDepositionD1, &b_EnergyDepositionD1);
   fChain->SetBranchAddress("dx1_seg", dx1_seg, &b_dx1_seg);
   fChain->SetBranchAddress("dy1_seg", dy1_seg, &b_dy1_seg);
   fChain->SetBranchAddress("dxSig1_seg", dxSig1_seg, &b_dxSig1_seg);
   fChain->SetBranchAddress("dySig1_seg", dySig1_seg, &b_dySig1_seg);
   fChain->SetBranchAddress("ddxdz1_seg", ddxdz1_seg, &b_ddxdz1_seg);
   fChain->SetBranchAddress("ddydz1_seg", ddydz1_seg, &b_ddydz1_seg);
   fChain->SetBranchAddress("ddxdzSig1_seg", ddxdzSig1_seg, &b_ddxdzSig1_seg);
   fChain->SetBranchAddress("ddydzSig1_seg", ddydzSig1_seg, &b_ddydzSig1_seg);
   fChain->SetBranchAddress("OneStMuon2", OneStMuon2, &b_OneStMuon2);
   fChain->SetBranchAddress("PFMuon2", PFMuon2, &b_PFMuon2);
   fChain->SetBranchAddress("GlbMuon2", GlbMuon2, &b_GlbMuon2);
   fChain->SetBranchAddress("trkMuon2", trkMuon2, &b_trkMuon2);
   fChain->SetBranchAddress("tightMuon2", tightMuon2, &b_tightMuon2);
   fChain->SetBranchAddress("softMuon2", softMuon2, &b_softMuon2);
   fChain->SetBranchAddress("hybridMuon2", hybridMuon2, &b_hybridMuon2);
   fChain->SetBranchAddress("HPMuon2", HPMuon2, &b_HPMuon2);
   fChain->SetBranchAddress("trigMuon2", &trigMuon2, &b_trigMuon2);
   fChain->SetBranchAddress("nMatchedStationD2", nMatchedStationD2, &b_nMatchedStationD2);
   fChain->SetBranchAddress("nTrackerLayerD2", nTrackerLayerD2, &b_nTrackerLayerD2);
   fChain->SetBranchAddress("nPixelLayerD2", nPixelLayerD2, &b_nPixelLayerD2);
   fChain->SetBranchAddress("nPixelHitD2", nPixelHitD2, &b_nPixelHitD2);
   fChain->SetBranchAddress("nMuonHitD2", nMuonHitD2, &b_nMuonHitD2);
   fChain->SetBranchAddress("GlbTrkChiD2", GlbTrkChiD2, &b_GlbTrkChiD2);
   fChain->SetBranchAddress("muondXYD2", muondXYD2, &b_muondXYD2);
   fChain->SetBranchAddress("muondZD2", muondZD2, &b_muondZD2);
   fChain->SetBranchAddress("dXYD2", dXYD2, &b_dXYD2);
   fChain->SetBranchAddress("dZD2", dZD2, &b_dZD2);
   fChain->SetBranchAddress("nMatchedChamberD2", nMatchedChamberD2, &b_nMatchedChamberD2);
   fChain->SetBranchAddress("EnergyDepositionD2", EnergyDepositionD2, &b_EnergyDepositionD2);
   fChain->SetBranchAddress("dx2_seg", dx2_seg, &b_dx2_seg);
   fChain->SetBranchAddress("dy2_seg", dy2_seg, &b_dy2_seg);
   fChain->SetBranchAddress("dxSig2_seg", dxSig2_seg, &b_dxSig2_seg);
   fChain->SetBranchAddress("dySig2_seg", dySig2_seg, &b_dySig2_seg);
   fChain->SetBranchAddress("ddxdz2_seg", ddxdz2_seg, &b_ddxdz2_seg);
   fChain->SetBranchAddress("ddydz2_seg", ddydz2_seg, &b_ddydz2_seg);
   fChain->SetBranchAddress("ddxdzSig2_seg", ddxdzSig2_seg, &b_ddxdzSig2_seg);
   fChain->SetBranchAddress("ddydzSig2_seg", ddydzSig2_seg, &b_ddydzSig2_seg);
   Notify();
}

Bool_t VertexCompositeNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void VertexCompositeNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t VertexCompositeNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef VertexCompositeNtuple_cxx
