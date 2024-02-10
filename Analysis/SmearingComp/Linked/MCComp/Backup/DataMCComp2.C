#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

#include "TPaveStats.h"
#include "TPaveText.h"
#include "TText.h"
#include "TPavesText.h"

using namespace std;

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4, TH1F *hist5, TH1F *hist6);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHistData = new TH1F("PD05","X Slope",50,-0.4,0.4);
TH1F *SlpTXHistMC1 = new TH1F("EPOS","X Slope",50,-0.4,0.4);
TH1F *SlpTXHistMC2 = new TH1F("Geant4","X Slope",50,-0.4,0.4);
TH1F *SlpTXHistMC3 = new TH1F("Pythia","X Slope",50,-0.4,0.4);
TH1F *SlpTXHistMC4 = new TH1F("DPMJET","X Slope",50,-0.4,0.4);
TH1F *SlpTXHistMC5 = new TH1F("QGSJET","X Slope",50,-0.4,0.4);

TH1F *SlpTYHistData = new TH1F("PD05","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHistMC1 = new TH1F("EPOS","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHistMC2 = new TH1F("Geant4","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHistMC3 = new TH1F("Pythia","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHistMC4 = new TH1F("DPMJET","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHistMC5 = new TH1F("QGSJET","Y Slope",50,-0.4,0.4);

TH1F *SlpT2HistData = new TH1F("PD05","Space Angle",50,0,0.5);
TH1F *SlpT2HistMC1 = new TH1F("EPOS","Space Angle",50,0,0.5);
TH1F *SlpT2HistMC2 = new TH1F("Geant4","Space Angle",50,0,0.5);
TH1F *SlpT2HistMC3 = new TH1F("Pythia","Space Angle",50,0,0.5);
TH1F *SlpT2HistMC4 = new TH1F("DPMJET","Space Angle",50,0,0.5);
TH1F *SlpT2HistMC5 = new TH1F("QGSJET","Space Angle",50,0,0.5);

TH1F *IPDataData = new TH1F("PD05","Impact Parameter",25,0,10);
TH1F *IPDataMC1 = new TH1F("EPOS","Impact Parameter",25,0,10);
TH1F *IPDataMC2 = new TH1F("Geant4","Impact Parameter",25,0,10);
TH1F *IPDataMC3 = new TH1F("Pythia","Impact Parameter",25,0,10);
TH1F *IPDataMC4 = new TH1F("DPMJET","Impact Parameter",25,0,10);
TH1F *IPDataMC5 = new TH1F("QGSJET","Impact Parameter",25,0,10);

TH1F *MultData = new TH1F("PD05","Multiplicity",45,5,50);
TH1F *MultMC1 = new TH1F("EPOS","Multiplicity",45,5,50);
TH1F *MultMC2 = new TH1F("Geant4","Multiplicity",45,5,50);
TH1F *MultMC3 = new TH1F("Pythia","Multiplicity",45,5,50);
TH1F *MultMC4 = new TH1F("DPMJET","Multiplicity",45,5,50);
TH1F *MultMC5 = new TH1F("QGSJET","Multiplicity",45,5,50);

TFile *Data, *MC1, *MC2, *MC3, *MC4, *MC5;

float DataVtxSize = 0, MC1VtxSize = 0, MC2VtxSize = 0, MC3VtxSize = 0, MC4VtxSize = 0, MC5VtxSize = 0;

bool intTypeActive = true;

void DataMCComp2()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"DataMCComp2.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    cout << "Processing subvolume " << dirIndex << endl;

    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    sprintf(dataName, "../../../../Data_v20220912/PD05/Linked/RootOut/p%02d6.root", dirIndex);

    if (dirIndex < 7) { sprintf(MC1Name, "../../../../EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC1Name, "../../../../EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC2Name, "../../../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC2Name, "../../../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC3Name, "../../../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC3Name, "../../../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC4Name, "../../../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC4Name, "../../../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC5Name, "../../../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC5Name, "../../../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data = TFile::Open(dataName);
    MC1 = TFile::Open(MC1Name);
    MC2 = TFile::Open(MC2Name);
    MC3 = TFile::Open(MC3Name);
    MC4 = TFile::Open(MC4Name);
    MC5 = TFile::Open(MC5Name);

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeMCTrk1 = (TTree*)MC1->Get("TRK");
    TTree *treeMCTrk2 = (TTree*)MC2->Get("TRK");
    TTree *treeMCTrk3 = (TTree*)MC3->Get("TRK");
    TTree *treeMCTrk4 = (TTree*)MC4->Get("TRK");
    TTree *treeMCTrk5 = (TTree*)MC5->Get("TRK");

    TTree *treeDataVtx = (TTree*)Data->Get("VTX");
    TTree *treeMCVtx1 = (TTree*)MC1->Get("VTX");
    TTree *treeMCVtx2 = (TTree*)MC2->Get("VTX");
    TTree *treeMCVtx3 = (TTree*)MC3->Get("VTX");
    TTree *treeMCVtx4 = (TTree*)MC4->Get("VTX");
    TTree *treeMCVtx5 = (TTree*)MC5->Get("VTX");

    int dataTrkInd = 0, MC1TrkInd = 0, MC2TrkInd = 0, MC3TrkInd = 0, MC4TrkInd = 0, MC5TrkInd = 0;
    for (int i = 0; i < treeDataTrk->GetEntriesFast(); i++)
    {
      treeDataTrk->GetEntry(i);
      
      TLeaf *slpTX = treeDataTrk->GetLeaf("tx");
      TLeaf *slpTY = treeDataTrk->GetLeaf("ty");
      TLeaf *beamTX = treeDataTrk->GetLeaf("txpeak");
      TLeaf *beamTY = treeDataTrk->GetLeaf("typeak");
      TLeaf *IP = treeDataTrk->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeDataTrk->GetLeaf("vID");
      TLeaf *PN = treeDataTrk->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeDataTrk->GetLeaf("flagw");

      treeDataVtx->GetEntry(vID->GetValue());

      TLeaf *iType = treeDataVtx->GetLeaf("intType");
      TLeaf *mlt = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      if (PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        SlpTXHistData->Fill(TX);
        SlpTYHistData->Fill(TY);
        SlpT2HistData->Fill(sqrt(TX*TX+TY*TY));
        IPDataData->Fill(IP->GetValue());
      }
    }
    
    for (int i = 0; i < treeMCTrk1->GetEntriesFast(); i++)
    {
      treeMCTrk1->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk1->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk1->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk1->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk1->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk1->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk1->GetLeaf("vID");
      TLeaf *PN = treeMCTrk1->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk1->GetLeaf("flagw");

      treeMCVtx1->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx1->GetLeaf("intType");
      TLeaf *mlt = treeMCVtx1->GetLeaf("n_1ry_trk");

      //TLeaf *vtxVID = treeMCVtx1->GetLeaf("vID");
      //cout << "VtxVID: " << vtxVID->GetValue() << ", TrkVID: " << vID->GetValue() << endl;

      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();

        SlpTXHistMC1->Fill(TX);
        SlpTYHistMC1->Fill(TY);
        SlpT2HistMC1->Fill(sqrt(TX*TX+TY*TY));
        IPDataMC1->Fill(IP->GetValue());
      }
    }

    for (int i = 0; i < treeMCTrk2->GetEntriesFast(); i++)
    {
      treeMCTrk2->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk2->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk2->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk2->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk2->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk2->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk2->GetLeaf("vID");
      TLeaf *PN = treeMCTrk2->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk2->GetLeaf("flagw");

      treeMCVtx2->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx2->GetLeaf("intType");
      TLeaf *mlt = treeMCVtx2->GetLeaf("n_1ry_trk");

      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        SlpTXHistMC2->Fill(TX);
        SlpTYHistMC2->Fill(TY);
        SlpT2HistMC2->Fill(sqrt(TX*TX+TY*TY));
        IPDataMC2->Fill(IP->GetValue());
      }
    }

    for (int i = 0; i < treeMCTrk3->GetEntriesFast(); i++)
    {
      treeMCTrk3->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk3->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk3->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk3->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk3->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk3->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk3->GetLeaf("vID");
      TLeaf *PN = treeMCTrk3->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk3->GetLeaf("flagw");

      treeMCVtx3->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx3->GetLeaf("intType");
      TLeaf *mlt = treeMCVtx3->GetLeaf("n_1ry_trk");

      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        SlpTXHistMC3->Fill(TX);
        SlpTYHistMC3->Fill(TY);
        SlpT2HistMC3->Fill(sqrt(TX*TX+TY*TY));
        IPDataMC3->Fill(IP->GetValue());
      }
    }

    for (int i = 0; i < treeMCTrk4->GetEntriesFast(); i++)
    {
      treeMCTrk4->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk4->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk4->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk4->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk4->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk4->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk4->GetLeaf("vID");
      TLeaf *PN = treeMCTrk4->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk4->GetLeaf("flagw");

      treeMCVtx4->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx4->GetLeaf("intType");
      TLeaf *mlt = treeMCVtx4->GetLeaf("n_1ry_trk");

      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        SlpTXHistMC4->Fill(TX);
        SlpTYHistMC4->Fill(TY);
        SlpT2HistMC4->Fill(sqrt(TX*TX+TY*TY));
        IPDataMC4->Fill(IP->GetValue());
      }
    }

    for (int i = 0; i < treeMCTrk5->GetEntriesFast(); i++)
    {
      treeMCTrk5->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk5->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk5->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk5->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk5->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk5->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk5->GetLeaf("vID");
      TLeaf *PN = treeMCTrk5->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk5->GetLeaf("flagw");

      treeMCVtx5->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx5->GetLeaf("intType");
      TLeaf *mlt = treeMCVtx5->GetLeaf("n_1ry_trk");

      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        SlpTXHistMC5->Fill(TX);
        SlpTYHistMC5->Fill(TY);
        SlpT2HistMC5->Fill(sqrt(TX*TX+TY*TY));
        IPDataMC5->Fill(IP->GetValue());
      }
    }

    for (int i = 0; i < treeDataVtx->GetEntriesFast(); i++)
    {
      treeDataVtx->GetEntry(i);

      TLeaf *mult = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeDataVtx->GetLeaf("vID");
      TLeaf *w = treeDataVtx->GetLeaf("flagw");
      TLeaf *iType = treeDataVtx->GetLeaf("intType");
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      if(PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultData->Fill(mult->GetValue());
        DataVtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeDataTrk->GetEntry(dataTrkInd);
      
          TLeaf *slpTX = treeDataTrk->GetLeaf("tx");
          TLeaf *slpTY = treeDataTrk->GetLeaf("ty");
          TLeaf *beamTX = treeDataTrk->GetLeaf("txpeak");
          TLeaf *beamTY = treeDataTrk->GetLeaf("typeak");
          TLeaf *IP = treeDataTrk->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vIDTrk = treeDataTrk->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistData->Fill(TX);
          SlpTYHistData->Fill(TY);
          SlpT2HistData->Fill(sqrt(TX*TX+TY*TY));
          IPDataData->Fill(IP->GetValue());

          dataTrkInd++;
        }
      }
    }

    for (int i = 0; i < treeMCVtx1->GetEntriesFast(); i++)
    {
      treeMCVtx1->GetEntry(i);

      TLeaf *mult = treeMCVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx1->GetLeaf("vID");
      TLeaf *w = treeMCVtx1->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx1->GetLeaf("intType");

      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultMC1->Fill(mult->GetValue());
        MC1VtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeMCTrk1->GetEntry(MC1TrkInd);
      
          TLeaf *slpTX = treeMCTrk1->GetLeaf("tx");
          TLeaf *slpTY = treeMCTrk1->GetLeaf("ty");
          TLeaf *beamTX = treeMCTrk1->GetLeaf("txpeak");
          TLeaf *beamTY = treeMCTrk1->GetLeaf("typeak");
          TLeaf *IP = treeMCTrk1->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vID = treeMCTrk1->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC1->Fill(TX);
          SlpTYHistMC1->Fill(TY);
          SlpT2HistMC1->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC1->Fill(IP->GetValue());

          MC1TrkInd++;
        }
      }
    }

    for (int i = 0; i < treeMCVtx2->GetEntriesFast(); i++)
    {
      treeMCVtx2->GetEntry(i);

      TLeaf *mult = treeMCVtx2->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx2->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx2->GetLeaf("vID");
      TLeaf *w = treeMCVtx2->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx2->GetLeaf("intType");

      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultMC2->Fill(mult->GetValue());
        MC2VtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeMCTrk2->GetEntry(MC2TrkInd);
      
          TLeaf *slpTX = treeMCTrk2->GetLeaf("tx");
          TLeaf *slpTY = treeMCTrk2->GetLeaf("ty");
          TLeaf *beamTX = treeMCTrk2->GetLeaf("txpeak");
          TLeaf *beamTY = treeMCTrk2->GetLeaf("typeak");
          TLeaf *IP = treeMCTrk2->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vID = treeMCTrk2->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC2->Fill(TX);
          SlpTYHistMC2->Fill(TY);
          SlpT2HistMC2->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC2->Fill(IP->GetValue());

          MC2TrkInd++;
        }
      }
    }

    for (int i = 0; i < treeMCVtx3->GetEntriesFast(); i++)
    {
      treeMCVtx3->GetEntry(i);

      TLeaf *mult = treeMCVtx3->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx3->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx3->GetLeaf("vID");
      TLeaf *w = treeMCVtx3->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx3->GetLeaf("intType");

      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultMC3->Fill(mult->GetValue());
        MC3VtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeMCTrk3->GetEntry(MC3TrkInd);
      
          TLeaf *slpTX = treeMCTrk3->GetLeaf("tx");
          TLeaf *slpTY = treeMCTrk3->GetLeaf("ty");
          TLeaf *beamTX = treeMCTrk3->GetLeaf("txpeak");
          TLeaf *beamTY = treeMCTrk3->GetLeaf("typeak");
          TLeaf *IP = treeMCTrk3->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vID = treeMCTrk3->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC3->Fill(TX);
          SlpTYHistMC3->Fill(TY);
          SlpT2HistMC3->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC3->Fill(IP->GetValue());

          MC3TrkInd++;
        }
      }
    }

    for (int i = 0; i < treeMCVtx4->GetEntriesFast(); i++)
    {
      treeMCVtx4->GetEntry(i);

      TLeaf *mult = treeMCVtx4->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx4->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx4->GetLeaf("vID");
      TLeaf *w = treeMCVtx4->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx4->GetLeaf("intType");

      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultMC4->Fill(mult->GetValue());
        MC4VtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeMCTrk4->GetEntry(MC4TrkInd);
      
          TLeaf *slpTX = treeMCTrk4->GetLeaf("tx");
          TLeaf *slpTY = treeMCTrk4->GetLeaf("ty");
          TLeaf *beamTX = treeMCTrk4->GetLeaf("txpeak");
          TLeaf *beamTY = treeMCTrk4->GetLeaf("typeak");
          TLeaf *IP = treeMCTrk4->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vID = treeMCTrk4->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC4->Fill(TX);
          SlpTYHistMC4->Fill(TY);
          SlpT2HistMC4->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC4->Fill(IP->GetValue());

          MC4TrkInd++;
        }
      }
    }

    for (int i = 0; i < treeMCVtx5->GetEntriesFast(); i++)
    {
      treeMCVtx5->GetEntry(i);

      TLeaf *mult = treeMCVtx5->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx5->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx5->GetLeaf("vID");
      TLeaf *w = treeMCVtx5->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx5->GetLeaf("intType");

      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)))
      {
        MultMC5->Fill(mult->GetValue());
        MC4VtxSize++;

        for (int j = 0; j < mult->GetValue() && false; j++)
        {
          treeMCTrk5->GetEntry(MC4TrkInd);
      
          TLeaf *slpTX = treeMCTrk5->GetLeaf("tx");
          TLeaf *slpTY = treeMCTrk5->GetLeaf("ty");
          TLeaf *beamTX = treeMCTrk5->GetLeaf("txpeak");
          TLeaf *beamTY = treeMCTrk5->GetLeaf("typeak");
          TLeaf *IP = treeMCTrk5->GetLeaf("ip_to_1ry_using_1stseg");
          TLeaf *vID = treeMCTrk5->GetLeaf("vID");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC5->Fill(TX);
          SlpTYHistMC5->Fill(TY);
          SlpT2HistMC5->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC5->Fill(IP->GetValue());

          MC5TrkInd++;
        }
      }
    }
  }

  /*
  float dataVMC1 = DataVtxSize/MC1VtxSize;
  float dataVMC2 = DataVtxSize/MC2VtxSize;
  float dataVMC3 = DataVtxSize/MC3VtxSize;
  float dataVMC4 = DataVtxSize/MC4VtxSize;
  float dataVMC5 = DataVtxSize/MC5VtxSize;
  */

  float dataVMC1 = MultData->Integral()/MultMC1->Integral();
  float dataVMC2 = MultData->Integral()/MultMC2->Integral();
  float dataVMC3 = MultData->Integral()/MultMC3->Integral();
  float dataVMC4 = MultData->Integral()/MultMC4->Integral();
  float dataVMC5 = MultData->Integral()/MultMC5->Integral();

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  SlpTXHistMC1->Scale(dataVMC1);
  SlpTXHistMC2->Scale(dataVMC2);
  SlpTXHistMC3->Scale(dataVMC3);
  SlpTXHistMC4->Scale(dataVMC4);
  SlpTXHistMC5->Scale(dataVMC5);

  SlpTYHistMC1->Scale(dataVMC1);
  SlpTYHistMC2->Scale(dataVMC2);
  SlpTYHistMC3->Scale(dataVMC3);
  SlpTYHistMC4->Scale(dataVMC4);
  SlpTYHistMC5->Scale(dataVMC5);

  SlpT2HistMC1->Scale(dataVMC1);
  SlpT2HistMC2->Scale(dataVMC2);
  SlpT2HistMC3->Scale(dataVMC3);
  SlpT2HistMC4->Scale(dataVMC4);
  SlpT2HistMC5->Scale(dataVMC5);

  IPDataMC1->Scale(dataVMC1);
  IPDataMC2->Scale(dataVMC2);
  IPDataMC3->Scale(dataVMC3);
  IPDataMC4->Scale(dataVMC4);
  IPDataMC5->Scale(dataVMC5);

  MultMC1->Scale(dataVMC1);
  MultMC2->Scale(dataVMC2);
  MultMC3->Scale(dataVMC3);
  MultMC4->Scale(dataVMC4);
  MultMC5->Scale(dataVMC5);

  //if(intTypeActive) {SlpTXHistData->GetYaxis()->SetRangeUser(0, 250000);}
  //else {SlpTXHistData->GetYaxis()->SetRangeUser(0, 350000);}

  SlpTXHistData->GetYaxis()->SetRangeUser(0, 350000);

  SlpTXHistData->SetXTitle("Slope X");
  HistDraw(SlpTXHistData, SlpTXHistMC1, SlpTXHistMC2, SlpTXHistMC3, SlpTXHistMC4, SlpTXHistMC5);
  Canvas->Print( outNameStart, "pdf");

  //if(intTypeActive) {SlpTYHistData->GetYaxis()->SetRangeUser(0, 250000);}
  //else {SlpTYHistData->GetYaxis()->SetRangeUser(0, 350000);}

  SlpTYHistData->GetYaxis()->SetRangeUser(0, 350000);

  SlpTYHistData->SetXTitle("Slope Y");
  HistDraw(SlpTYHistData, SlpTYHistMC1, SlpTYHistMC2, SlpTYHistMC3, SlpTYHistMC4, SlpTYHistMC5);
  Canvas->Print( outName, "pdf");

  //if(intTypeActive) {SlpT2HistData->GetYaxis()->SetRangeUser(0, 150000);}
  //else {SlpT2HistData->GetYaxis()->SetRangeUser(0, 220000);}

  SlpT2HistData->GetYaxis()->SetRangeUser(0, 220000);

  SlpT2HistData->SetXTitle("Particle angle (rad)");
  HistDraw(SlpT2HistData, SlpT2HistMC1, SlpT2HistMC2, SlpT2HistMC3, SlpT2HistMC4, SlpT2HistMC5);
  Canvas->Print( outName, "pdf");

  //if(intTypeActive) {IPDataData->GetYaxis()->SetRangeUser(0, 400000);}
  //else {IPDataData->GetYaxis()->SetRangeUser(0, 580000);}

  IPDataData->GetYaxis()->SetRangeUser(0, 580000);

  IPDataData->SetXTitle("Impact Parameter (#mum)");
  HistDraw(IPDataData, IPDataMC1, IPDataMC2, IPDataMC3, IPDataMC4, IPDataMC5);
  Canvas->Print( outName, "pdf");

  //if(intTypeActive) {MultData->GetYaxis()->SetRangeUser(0, 4000);}
  //else {MultData->GetYaxis()->SetRangeUser(0, 6000);}

  MultData->GetYaxis()->SetRangeUser(0, 6000);

  MultData->SetXTitle("Multiplicity");
  HistDraw(MultData, MultMC1, MultMC2, MultMC3, MultMC4, MultMC5);
  Canvas->Print( outNameEnd, "pdf");
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4, TH1F *hist5, TH1F *hist6)
{
  gStyle->SetOptStat(0);

  hist1->SetTitle("");
  hist1->Draw("HIST E1"); hist1->SetLineColor(kBlack); hist1->SetLineStyle(1); //hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlack, 0.1);
  /*
  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD05");
  StatBox1->SetY1NDC(1.0);
  StatBox1->SetY2NDC(0.8);
  StatBox1->SetTextColor(kBlack);
  StatBox1->Draw();
  */

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); //hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);
  /*
  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("EPOS");
  StatBox2->SetY1NDC(0.8);
  StatBox2->SetY2NDC(0.6);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  */
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kGreen); hist3->SetLineStyle(1); //hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kGreen, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("Geant4");
  StatBox3->SetY1NDC(0.6);
  StatBox3->SetY2NDC(0.4);
  StatBox3->SetTextColor(kGreen);
  StatBox3->Draw();
  */

  hist4->Draw("SAMES HIST"); hist4->SetLineColor(kBlue); hist4->SetLineStyle(1); //hist4->SetLineWidth(2); //hist4->SetFillColorAlpha(kBlue, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("QGSJET");
  StatBox4->SetY1NDC(0.4);
  StatBox4->SetY2NDC(0.2);
  StatBox4->SetTextColor(kBlue);
  StatBox4->Draw();
  */

  
  hist5->Draw("SAMES HIST"); hist5->SetLineColor(kMagenta); hist5->SetLineStyle(1); //hist5->SetLineWidth(2); //hist5->SetFillColorAlpha(kMagenta, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox5->SetName("Pythia");
  StatBox5->SetY1NDC(0.2);
  StatBox5->SetY2NDC(0.0);
  StatBox5->SetTextColor(kMagenta);
  StatBox5->Draw();
  */

  hist6->Draw("SAMES HIST"); hist6->SetLineColor(kOrange +2); hist6->SetLineStyle(1); //hist5->SetLineWidth(2); //hist5->SetFillColorAlpha(kMagenta, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox5->SetName("Pythia");
  StatBox5->SetY1NDC(0.2);
  StatBox5->SetY2NDC(0.0);
  StatBox5->SetTextColor(kMagenta);
  StatBox5->Draw();
  */
  
  //TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  TLegend *legend = new TLegend(0.70, 0.65, 0.90, 0.90);
  legend->AddEntry(hist1,"Data","f");
  legend->AddEntry(hist2,"EPOS","f");
  legend->AddEntry(hist3,"Geant4","f");
  legend->AddEntry(hist4,"Pythia","f");
  legend->AddEntry(hist5,"DPMJET","f");
  legend->AddEntry(hist6,"QGSJET","f");
  legend->Draw();
}