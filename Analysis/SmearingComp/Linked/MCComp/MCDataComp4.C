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

// compType == 0 for all events
// compType == 1 for multiplicity >= 10 events
// compType == 2 for multiplicity < 10 events
int compType = 0;

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4, TH1F *hist5, TH1F *hist6);
void ShowChi2Test();

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHistData = new TH1F("PD05","",50,-0.4,0.4);
TH1F *SlpTXHistMC1 = new TH1F("EPOS","",50,-0.4,0.4);
TH1F *SlpTXHistMC2 = new TH1F("Geant4","",50,-0.4,0.4);
TH1F *SlpTXHistMC3 = new TH1F("Pythia","",50,-0.4,0.4);
TH1F *SlpTXHistMC4 = new TH1F("DPMJET","",50,-0.4,0.4);
TH1F *SlpTXHistMC5 = new TH1F("QGSJET","",50,-0.4,0.4);

TH1F *SlpTYHistData = new TH1F("PD05","",50,-0.4,0.4);
TH1F *SlpTYHistMC1 = new TH1F("EPOS","",50,-0.4,0.4);
TH1F *SlpTYHistMC2 = new TH1F("Geant4","",50,-0.4,0.4);
TH1F *SlpTYHistMC3 = new TH1F("Pythia","",50,-0.4,0.4);
TH1F *SlpTYHistMC4 = new TH1F("DPMJET","",50,-0.4,0.4);
TH1F *SlpTYHistMC5 = new TH1F("QGSJET","",50,-0.4,0.4);

TH1F *SlpT2HistData = new TH1F("PD05","",50,0,0.35);
TH1F *SlpT2HistMC1 = new TH1F("EPOS","",50,0,0.35);
TH1F *SlpT2HistMC2 = new TH1F("Geant4","",50,0,0.35);
TH1F *SlpT2HistMC3 = new TH1F("Pythia","",50,0,0.35);
TH1F *SlpT2HistMC4 = new TH1F("DPMJET","",50,0,0.35);
TH1F *SlpT2HistMC5 = new TH1F("QGSJET","",50,0,0.35);

TH1F *IPDataData = new TH1F("PD05","",25,0,6);
TH1F *IPDataMC1 = new TH1F("EPOS","",25,0,6);
TH1F *IPDataMC2 = new TH1F("Geant4","",25,0,6);
TH1F *IPDataMC3 = new TH1F("Pythia","",25,0,6);
TH1F *IPDataMC4 = new TH1F("DPMJET","",25,0,6);
TH1F *IPDataMC5 = new TH1F("QGSJET","",25,0,6);

TH1F *MultData = new TH1F("PD05","",35,5,40);
TH1F *MultMC1 = new TH1F("EPOS","",35,5,40);
TH1F *MultMC2 = new TH1F("Geant4","",35,5,40);
TH1F *MultMC3 = new TH1F("Pythia","",35,5,40);
TH1F *MultMC4 = new TH1F("DPMJET","",35,5,40);
TH1F *MultMC5 = new TH1F("QGSJET","",35,5,40);

TFile *Data, *MC1, *MC2, *MC3, *MC4, *MC5;

float DataVtxSize = 0, MC1VtxSize = 0, MC2VtxSize = 0, MC3VtxSize = 0, MC4VtxSize = 0, MC5VtxSize = 0;

bool intTypeActive = true;

double dataCorrection = 0.95;
float migCut = 18;

void MCDataComp4()
{
  Canvas->SetWindowSize(1200, 1200);
  Canvas->SetCanvasSize(120*6, 120*6);

  Canvas->Divide(0,2,0,0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"MCDataComp4.pdf");
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
    double initZ, lastZ;
    double *dataEndArr, *MC1EndArr, *MC2EndArr, *MC3EndArr, *MC4EndArr, *MC5EndArr;
    double dataMean, MC1Mean, MC2Mean, MC3Mean, MC4Mean, MC5Mean;

    dataEndArr = DataEndPoints(treeDataVtx);
    MC1EndArr = MCEndPoints(treeMCVtx1);
    MC2EndArr = MCEndPoints(treeMCVtx2);
    MC3EndArr = MCEndPoints(treeMCVtx3);
    MC4EndArr = MCEndPoints(treeMCVtx4);
    MC5EndArr = MCEndPoints(treeMCVtx5);

    dataMean = DataMean(treeDataVtx);
    MC1Mean = DataMean(treeMCVtx1);
    MC2Mean = DataMean(treeMCVtx2);
    MC3Mean = DataMean(treeMCVtx3);
    MC4Mean = DataMean(treeMCVtx4);
    MC5Mean = DataMean(treeMCVtx5);

    initZ = dataEndArr[0];
    lastZ = dataEndArr[1];
    
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
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");
      TLeaf *mult = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeDataVtx->GetLeaf("vz");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = (slpTX->GetValue() - beamTX->GetValue()) * dataCorrection;
          double TY = (slpTY->GetValue() - beamTY->GetValue()) * dataCorrection;
          
          SlpTXHistData->Fill(TX);
          SlpTYHistData->Fill(TY);
          SlpT2HistData->Fill(sqrt(TX*TX+TY*TY));
          IPDataData->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC1EndArr[0];
    lastZ = MC1EndArr[1];
    
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
      TLeaf *mult = treeMCVtx1->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx1->GetLeaf("vz");

      //TLeaf *vtxVID = treeMCVtx1->GetLeaf("vID");
      //cout << "VtxVID: " << vtxVID->GetValue() << ", TrkVID: " << vID->GetValue() << endl;

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC1Mean - (250-migCut) && vz->GetValue() < MC1Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();

          SlpTXHistMC1->Fill(TX);
          SlpTYHistMC1->Fill(TY);
          SlpT2HistMC1->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC1->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC2EndArr[0];
    lastZ = MC2EndArr[1];

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
      TLeaf *mult = treeMCVtx2->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx2->GetLeaf("vz");
      
      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC2Mean - (250-migCut) && vz->GetValue() < MC2Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC2->Fill(TX);
          SlpTYHistMC2->Fill(TY);
          SlpT2HistMC2->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC2->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC3EndArr[0];
    lastZ = MC3EndArr[1];

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
      TLeaf *mult = treeMCVtx3->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx3->GetLeaf("vz");

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC3Mean - (250-migCut) && vz->GetValue() < MC3Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC3->Fill(TX);
          SlpTYHistMC3->Fill(TY);
          SlpT2HistMC3->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC3->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC4EndArr[0];
    lastZ = MC4EndArr[1];

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
      TLeaf *mult = treeMCVtx4->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx4->GetLeaf("vz");

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC4Mean - (250-migCut) && vz->GetValue() < MC4Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC4->Fill(TX);
          SlpTYHistMC4->Fill(TY);
          SlpT2HistMC4->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC4->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC5EndArr[0];
    lastZ = MC5EndArr[1];

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
      TLeaf *mult = treeMCVtx5->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx5->GetLeaf("vz");

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC5Mean - (250-migCut) && vz->GetValue() < MC5Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC5->Fill(TX);
          SlpTYHistMC5->Fill(TY);
          SlpT2HistMC5->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC5->Fill(IP->GetValue());
        }
      }
    }

    initZ = dataEndArr[0];
    lastZ = dataEndArr[1];

    for (int i = 0; i < treeDataVtx->GetEntriesFast(); i++)
    {
      treeDataVtx->GetEntry(i);

      TLeaf *mult = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeDataVtx->GetLeaf("vID");
      TLeaf *w = treeDataVtx->GetLeaf("flagw");
      TLeaf *iType = treeDataVtx->GetLeaf("intType");
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");
      TLeaf *vz = treeDataVtx->GetLeaf("vz");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultData->Fill(mult->GetValue());
          DataVtxSize++;
        }
      }
    }

    initZ = MC1EndArr[0];
    lastZ = MC1EndArr[1];

    for (int i = 0; i < treeMCVtx1->GetEntriesFast(); i++)
    {
      treeMCVtx1->GetEntry(i);

      TLeaf *mult = treeMCVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx1->GetLeaf("vID");
      TLeaf *w = treeMCVtx1->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx1->GetLeaf("intType");
      TLeaf *vz = treeMCVtx1->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC1Mean - (250-migCut) && vz->GetValue() < MC1Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC1->Fill(mult->GetValue());
          MC1VtxSize++;
        }
      }
    }

    initZ = MC2EndArr[0];
    lastZ = MC2EndArr[1];

    for (int i = 0; i < treeMCVtx2->GetEntriesFast(); i++)
    {
      treeMCVtx2->GetEntry(i);

      TLeaf *mult = treeMCVtx2->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx2->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx2->GetLeaf("vID");
      TLeaf *w = treeMCVtx2->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx2->GetLeaf("intType");
      TLeaf *vz = treeMCVtx2->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC2Mean - (250-migCut) && vz->GetValue() < MC2Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC2->Fill(mult->GetValue());
          MC2VtxSize++;
        }
      }
    }

    initZ = MC3EndArr[0];
    lastZ = MC3EndArr[1];

    for (int i = 0; i < treeMCVtx3->GetEntriesFast(); i++)
    {
      treeMCVtx3->GetEntry(i);

      TLeaf *mult = treeMCVtx3->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx3->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx3->GetLeaf("vID");
      TLeaf *w = treeMCVtx3->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx3->GetLeaf("intType");
      TLeaf *vz = treeMCVtx3->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC3Mean - (250-migCut) && vz->GetValue() < MC3Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC3->Fill(mult->GetValue());
          MC3VtxSize++;
        }
      }
    }

    initZ = MC4EndArr[0];
    lastZ = MC4EndArr[1];

    for (int i = 0; i < treeMCVtx4->GetEntriesFast(); i++)
    {
      treeMCVtx4->GetEntry(i);

      TLeaf *mult = treeMCVtx4->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx4->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx4->GetLeaf("vID");
      TLeaf *w = treeMCVtx4->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx4->GetLeaf("intType");
      TLeaf *vz = treeMCVtx4->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC4Mean - (250-migCut) && vz->GetValue() < MC4Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC4->Fill(mult->GetValue());
          MC4VtxSize++;
        }
      }
    }

    initZ = MC5EndArr[0];
    lastZ = MC5EndArr[1];

    for (int i = 0; i < treeMCVtx5->GetEntriesFast(); i++)
    {
      treeMCVtx5->GetEntry(i);

      TLeaf *mult = treeMCVtx5->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx5->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx5->GetLeaf("vID");
      TLeaf *w = treeMCVtx5->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx5->GetLeaf("intType");
      TLeaf *vz = treeMCVtx5->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC5Mean - (250-migCut) && vz->GetValue() < MC5Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC5->Fill(mult->GetValue());
          MC5VtxSize++;
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


  
  TH1F *copyT2HistMC1 = (TH1F*) SlpT2HistMC1->Clone();
  copyT2HistMC1->SetName("T2Hist");
  copyT2HistMC1->Divide(SlpT2HistData);
  TH1F *copyT2HistMC2 = (TH1F*) SlpT2HistMC2->Clone();
  copyT2HistMC2->SetName("T2Hist");
  copyT2HistMC2->Divide(SlpT2HistData);
  TH1F *copyT2HistMC3 = (TH1F*) SlpT2HistMC3->Clone();
  copyT2HistMC3->SetName("T2Hist");
  copyT2HistMC3->Divide(SlpT2HistData);
  TH1F *copyT2HistMC4 = (TH1F*) SlpT2HistMC4->Clone();
  copyT2HistMC4->SetName("T2Hist");
  copyT2HistMC4->Divide(SlpT2HistData);
  TH1F *copyT2HistMC5 = (TH1F*) SlpT2HistMC5->Clone();
  copyT2HistMC5->SetName("T2Hist");
  copyT2HistMC5->Divide(SlpT2HistData);

  TH1F *copyIPHistMC1 = (TH1F*) IPDataMC1->Clone();
  copyIPHistMC1->SetName("IPHist");
  copyIPHistMC1->Divide(IPDataData);
  TH1F *copyIPHistMC2 = (TH1F*) IPDataMC2->Clone();
  copyIPHistMC2->SetName("IPHist");
  copyIPHistMC2->Divide(IPDataData);
  TH1F *copyIPHistMC3 = (TH1F*) IPDataMC3->Clone();
  copyIPHistMC3->SetName("IPHist");
  copyIPHistMC3->Divide(IPDataData);
  TH1F *copyIPHistMC4 = (TH1F*) IPDataMC4->Clone();
  copyIPHistMC4->SetName("IPHist");
  copyIPHistMC4->Divide(IPDataData);
  TH1F *copyIPHistMC5 = (TH1F*) IPDataMC5->Clone();
  copyIPHistMC5->SetName("IPHist");
  copyIPHistMC5->Divide(IPDataData);

  TH1F *copyMultHistMC1 = (TH1F*) MultMC1->Clone();
  copyMultHistMC1->SetName("MultHist");
  copyMultHistMC1->Divide(MultData);
  TH1F *copyMultHistMC2 = (TH1F*) MultMC2->Clone();
  copyMultHistMC2->SetName("MultHist");
  copyMultHistMC2->Divide(MultData);
  TH1F *copyMultHistMC3 = (TH1F*) MultMC3->Clone();
  copyMultHistMC3->SetName("MultHist");
  copyMultHistMC3->Divide(MultData);
  TH1F *copyMultHistMC4 = (TH1F*) MultMC4->Clone();
  copyMultHistMC4->SetName("MultHist");
  copyMultHistMC4->Divide(MultData);
  TH1F *copyMultHistMC5 = (TH1F*) MultMC5->Clone();
  copyMultHistMC5->SetName("MultHist");
  copyMultHistMC5->Divide(MultData);

  //if(intTypeActive) {SlpT2HistData->GetYaxis()->SetRangeUser(0, 150000);}
  //else {SlpT2HistData->GetYaxis()->SetRangeUser(0, 220000);}

  if(compType == 2) {SlpT2HistMC2->GetYaxis()->SetRangeUser(-1000, 26000);}
  else {SlpT2HistMC2->GetYaxis()->SetRangeUser(-5000, 185000);}

  cout << SlpT2HistData->GetMean() << endl;

  Canvas->cd(1);
  gPad->SetGrid(100);
  SlpT2HistData->SetXTitle("Tan #theta");
  HistDraw(SlpT2HistData, SlpT2HistMC2, SlpT2HistMC3, SlpT2HistMC4, SlpT2HistMC5, SlpT2HistMC1);

  Canvas->cd(2);
  gPad->SetGrid(100);
  copyT2HistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyT2HistMC2->SetXTitle("Tan #theta");
  copyT2HistMC2->SetYTitle("MC / Data");
  copyT2HistMC2->GetYaxis()->SetLabelSize(0.05);
  copyT2HistMC2->GetXaxis()->SetLabelSize(0.05);

  copyT2HistMC2->Draw("HIST E1"); copyT2HistMC2->SetLineWidth(2); copyT2HistMC2->SetLineColor(kGreen); copyT2HistMC2->GetYaxis()->SetRangeUser(0, 2.05);
  copyT2HistMC3->Draw("SAMES HIST E1"); copyT2HistMC3->SetLineWidth(2); copyT2HistMC3->SetLineColor(kBlue); copyT2HistMC3->GetYaxis()->SetRangeUser(0, 2.05); copyT2HistMC3->SetStats(0);
  copyT2HistMC4->Draw("SAMES HIST E1"); copyT2HistMC4->SetLineWidth(2); copyT2HistMC4->SetLineColor(kMagenta); copyT2HistMC4->GetYaxis()->SetRangeUser(0, 2.05);  copyT2HistMC4->SetStats(0);
  copyT2HistMC5->Draw("SAMES HIST E1"); copyT2HistMC5->SetLineWidth(2); copyT2HistMC5->SetLineColor(kOrange + 2); copyT2HistMC5->GetYaxis()->SetRangeUser(0, 2.05); copyT2HistMC5->SetStats(0);
  copyT2HistMC1->Draw("SAMES HIST E1"); copyT2HistMC1->SetLineWidth(2); copyT2HistMC1->SetLineColor(kRed); copyT2HistMC1->GetYaxis()->SetRangeUser(0, 2.05); copyT2HistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statT2 = (TPaveStats*)copyT2HistMC2->GetListOfFunctions()->FindObject("stats"); 
  statT2->SetOptStat(0);

  TF1 *fa1 = new TF1("fa1","1",0,100);
  fa1->Draw("SAME");
  fa1->SetLineColor(kBlack);

  Canvas->Print( outNameStart, "pdf");

  //if(intTypeActive) {IPDataData->GetYaxis()->SetRangeUser(0, 400000);}
  //else {IPDataData->GetYaxis()->SetRangeUser(0, 580000);}

  IPDataMC2->GetYaxis()->SetRangeUser(-10000, 460000);

  Canvas->cd(1);
  IPDataData->SetXTitle("Impact Parameter (#mum)");
  HistDraw(IPDataData, IPDataMC2, IPDataMC3, IPDataMC4, IPDataMC5, IPDataMC1);

  Canvas->cd(2);
  copyIPHistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyIPHistMC2->SetXTitle("Impact Parameter (#mum)");
  copyIPHistMC2->SetYTitle("MC / Data");
  copyIPHistMC2->GetYaxis()->SetLabelSize(0.05);
  copyIPHistMC2->GetXaxis()->SetLabelSize(0.05);

  copyIPHistMC2->Draw("HIST E1"); copyIPHistMC2->SetLineWidth(2); copyIPHistMC2->SetLineColor(kGreen); copyIPHistMC2->GetYaxis()->SetRangeUser(0, 2.05);
  copyIPHistMC3->Draw("SAME HIST E1"); copyIPHistMC3->SetLineWidth(2); copyIPHistMC3->SetLineColor(kBlue); copyIPHistMC3->GetYaxis()->SetRangeUser(0, 2.05); copyIPHistMC3->SetStats(0);
  copyIPHistMC4->Draw("SAME HIST E1"); copyIPHistMC4->SetLineWidth(2); copyIPHistMC4->SetLineColor(kMagenta); copyIPHistMC4->GetYaxis()->SetRangeUser(0, 2.05); copyIPHistMC4->SetStats(0);
  copyIPHistMC5->Draw("SAME HIST E1"); copyIPHistMC5->SetLineWidth(2); copyIPHistMC5->SetLineColor(kOrange + 2); copyIPHistMC5->GetYaxis()->SetRangeUser(0, 2.05); copyIPHistMC5->SetStats(0);
  copyIPHistMC1->Draw("SAME HIST E1"); copyIPHistMC1->SetLineWidth(2); copyIPHistMC1->SetLineColor(kRed); copyIPHistMC1->GetYaxis()->SetRangeUser(0, 2.05); copyIPHistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statIP = (TPaveStats*)copyIPHistMC2->GetListOfFunctions()->FindObject("stats"); 
  statIP->SetOptStat(0);

  fa1->Draw("SAME");
  fa1->SetLineColor(kBlack);

  Canvas->Print( outName, "pdf");

  //if(intTypeActive) {MultData->GetYaxis()->SetRangeUser(0, 4000);}
  //else {MultData->GetYaxis()->SetRangeUser(0, 6000);}

  MultMC2->GetYaxis()->SetRangeUser(-100, 6100);

  Canvas->cd(1);
  MultData->SetXTitle("Multiplicity");
  HistDraw(MultData, MultMC2, MultMC3, MultMC4, MultMC5, MultMC1);

  Canvas->cd(2);
  copyMultHistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyMultHistMC2->SetXTitle("Multiplicity");
  copyMultHistMC2->SetYTitle("MC / Data");
  copyMultHistMC2->GetYaxis()->SetLabelSize(0.05);
  copyMultHistMC2->GetXaxis()->SetLabelSize(0.05);

  copyMultHistMC2->Draw("HIST E1"); copyMultHistMC2->SetLineWidth(2); copyMultHistMC2->SetLineColor(kGreen); copyMultHistMC2->GetYaxis()->SetRangeUser(0, 3.1);
  copyMultHistMC3->Draw("SAME HIST E1"); copyMultHistMC3->SetLineWidth(2); copyMultHistMC3->SetLineColor(kBlue); copyMultHistMC3->GetYaxis()->SetRangeUser(0, 3.1); copyMultHistMC3->SetStats(0);
  copyMultHistMC4->Draw("SAME HIST E1"); copyMultHistMC4->SetLineWidth(2); copyMultHistMC4->SetLineColor(kMagenta); copyMultHistMC4->GetYaxis()->SetRangeUser(0, 3.1); copyMultHistMC4->SetStats(0);
  copyMultHistMC5->Draw("SAME HIST E1"); copyMultHistMC5->SetLineWidth(2); copyMultHistMC5->SetLineColor(kOrange + 2); copyMultHistMC5->GetYaxis()->SetRangeUser(0, 3.1); copyMultHistMC5->SetStats(0);
  copyMultHistMC1->Draw("SAME HIST E1"); copyMultHistMC1->SetLineWidth(2); copyMultHistMC1->SetLineColor(kRed); copyMultHistMC1->GetYaxis()->SetRangeUser(0, 3.1); copyMultHistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statMult = (TPaveStats*)copyMultHistMC2->GetListOfFunctions()->FindObject("stats"); 
  statMult->SetOptStat(0);

  fa1->Draw("SAME");
  fa1->SetLineColor(kBlack);

  Canvas->Print( outNameEnd, "pdf");

  //ShowChi2Test();
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4, TH1F *hist5, TH1F *hist6)
{
  Canvas->cd(1);

  hist2->SetStats(0);
  hist2->SetTitle("");
  hist2->Draw("HIST"); hist2->SetLineColor(kGreen); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);
  hist2->GetXaxis()->SetLabelSize(0.05);
  hist2->GetYaxis()->SetLabelSize(0.05);
  hist2->GetXaxis()->SetLabelOffset(0.01);

  /*
  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("EPOS");
  StatBox2->SetY1NDC(0.8);
  StatBox2->SetY2NDC(0.6);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  */
  
  hist3->SetStats(0);
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kBlue); hist3->SetLineStyle(1); hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kGreen, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("Geant4");
  StatBox3->SetY1NDC(0.6);
  StatBox3->SetY2NDC(0.4);
  StatBox3->SetTextColor(kGreen);
  StatBox3->Draw();
  */

  hist4->SetStats(0);
  hist4->Draw("SAMES HIST"); hist4->SetLineColor(kMagenta); hist4->SetLineStyle(1); hist4->SetLineWidth(2); //hist4->SetFillColorAlpha(kBlue, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("QGSJET");
  StatBox4->SetY1NDC(0.4);
  StatBox4->SetY2NDC(0.2);
  StatBox4->SetTextColor(kBlue);
  StatBox4->Draw();
  */

  hist5->SetStats(0);
  hist5->Draw("SAMES HIST"); hist5->SetLineColor(kOrange + 2); hist5->SetLineStyle(1); hist5->SetLineWidth(2); //hist5->SetFillColorAlpha(kMagenta, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox5->SetName("Pythia");
  StatBox5->SetY1NDC(0.2);
  StatBox5->SetY2NDC(0.0);
  StatBox5->SetTextColor(kMagenta);
  StatBox5->Draw();
  */

  hist6->SetStats(0);
  hist6->Draw("SAMES HIST"); hist6->SetLineColor(kRed); hist6->SetLineStyle(1); hist6->SetLineWidth(2); //hist6->SetFillColorAlpha(kMagenta, 0.15);
  /*
  Canvas->Update();
  TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox5->SetName("Pythia");
  StatBox5->SetY1NDC(0.2);
  StatBox5->SetY2NDC(0.0);
  StatBox5->SetTextColor(kMagenta);
  StatBox5->Draw();
  */

  hist1->SetStats(0);
  hist1->Draw("SAMES HIST E1"); hist1->SetLineColor(kBlack); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlack, 0.1);

  /*
  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD05");
  StatBox1->SetY1NDC(1.0);
  StatBox1->SetY2NDC(0.8);
  StatBox1->SetTextColor(kBlack);
  StatBox1->Draw();
  */
  
  //TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  TLegend *legend = new TLegend(0.74, 0.65, 0.97, 0.95);
  legend->AddEntry(hist1,"Data","f");
  legend->AddEntry(hist6,"EPOS","f");
  legend->AddEntry(hist2,"Geant4","f");
  legend->AddEntry(hist3,"Pythia","f");
  legend->AddEntry(hist4,"DPMJET","f");
  legend->AddEntry(hist5,"QGSJET","f");
  legend->Draw();
}

void ShowChi2Test()
{
  cout << "Space Angle" << endl;

  cout << "EPOS" << endl;
  SlpT2HistData->Chi2Test(SlpT2HistMC1, "WW P");

  cout << "Geant4" << endl;
  SlpT2HistData->Chi2Test(SlpT2HistMC2, "WW P");

  cout << "Pythia" << endl;
  SlpT2HistData->Chi2Test(SlpT2HistMC3, "WW P");

  cout << "DPMJET" << endl;
  SlpT2HistData->Chi2Test(SlpT2HistMC4, "WW P");

  cout << "QGSJET" << endl;
  SlpT2HistData->Chi2Test(SlpT2HistMC5, "WW P");

  cout << "------------------" << endl;
  cout << "Impact Parameter" << endl;

  cout << "EPOS" << endl;
  IPDataData->Chi2Test(IPDataMC1, "WW P");

  cout << "Geant4" << endl;
  IPDataData->Chi2Test(IPDataMC2, "WW P");

  cout << "Pythia" << endl;
  IPDataData->Chi2Test(IPDataMC3, "WW P");

  cout << "DPMJET" << endl;
  IPDataData->Chi2Test(IPDataMC4, "WW P");

  cout << "QGSJET" << endl;
  IPDataData->Chi2Test(IPDataMC5, "WW P");

  cout << "------------------" << endl;
  cout << "Multiplicity" << endl;

  cout << "EPOS" << endl;
  MultData->Chi2Test(MultMC1, "WW P");

  cout << "Geant4" << endl;
  MultData->Chi2Test(MultMC2, "WW P");

  cout << "Pythia" << endl;
  MultData->Chi2Test(MultMC3, "WW P");

  cout << "DPMJET" << endl;
  MultData->Chi2Test(MultMC4, "WW P");

  cout << "QGSJET" << endl;
  MultData->Chi2Test(MultMC5, "WW P");
}

double* DataEndPoints(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double endPoints[2];

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *intMedium = data->GetLeaf("intMed");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    bool areaBool = (area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29);

    if (parNum->GetValue() == 1 && areaBool)
    {
      if (intMedium->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  endPoints[0] = InterHist->FindFirstBinAbove(0);
  endPoints[1] = InterHist->FindLastBinAbove(0);

  delete InterHist;

  return endPoints;
}

double* MCEndPoints(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double endPoints[2];

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *w = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (w->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  endPoints[0] = InterHist->FindFirstBinAbove(0);
  endPoints[1] = InterHist->FindLastBinAbove(0);

  delete InterHist;

  return endPoints;
}

double DataMean(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double mean;

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *w = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (w->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  mean = InterHist->GetMean();

  delete InterHist;

  return mean;
}