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

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);

//For Data dataCorrection == 1.05
//For MC dataCorrection == 1
//double dataCorrection = 1.05;
double dataCorrection = 1;

float migCut = 18;

void Analysis()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  //Canvas->SetWindowSize(800, 800);

  TH2F *MultThetaHist1 = new TH2F("MultTheta","Multiplicity vs. Theta",50,0,50,50,0,0.2);
  TH2F *MultThetaHist2 = new TH2F("MultThetaXNorm","Multiplicity vs. Theta",50,0,50,50,0,0.2);

  TFile *Data, *MC1, *MC2, *MC3, *MC4;

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"Analysis.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  int vtxSize = 0;

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    sprintf(dataName, "../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", dirIndex);

    if (dirIndex < 7) { sprintf(MC1Name, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC1Name, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC2Name, "../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC2Name, "../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC3Name, "../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC3Name, "../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC4Name, "../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC4Name, "../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC5Name, "../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC5Name, "../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data = TFile::Open(MC5Name);

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeDataVtx = (TTree*)Data->Get("VTX");

    //double *dataEndArr = DataEndPoints(treeDataVtx);
    double *dataEndArr = MCEndPoints(treeDataVtx);
    double mean = DataMean(treeDataVtx);

    for (int i = 0; i < treeDataTrk->GetEntriesFast(); i++)
    {
      treeDataTrk->GetEntry(i);

      TLeaf *PN = treeDataTrk->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataTrk->GetLeaf("flagw");
      TLeaf *vID = treeDataTrk->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if (w->GetValue() == 1)
      {
        TLeaf *slpTX = treeDataTrk->GetLeaf("tx");
        TLeaf *slpTY = treeDataTrk->GetLeaf("ty");
        TLeaf *beamTX = treeDataTrk->GetLeaf("txpeak");
        TLeaf *beamTY = treeDataTrk->GetLeaf("typeak");

        double TX = (slpTX->GetValue() - beamTX->GetValue()) * dataCorrection;
        double TY = (slpTY->GetValue() - beamTY->GetValue()) * dataCorrection;
        double T2 = sqrt(TX*TX+TY*TY);

        TLeaf *mlt = treeDataVtx->GetLeaf("n_1ry_trk");
        TLeaf *iType = treeDataVtx->GetLeaf("intType");
        TLeaf *area1 = treeDataVtx->GetLeaf("area1");
        TLeaf *vz = treeDataVtx->GetLeaf("vz");

        treeDataVtx->GetEntry(vtxIndex);

        bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

        //if (areaBool == 1 && iType->GetValue() >= 1 && vz->GetValue() - dataEndArr[0] > migCut && vz->GetValue() - dataEndArr[1] < -migCut)
        if (/*areaBool == 1 &&*/ iType->GetValue() >= 1 && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
        {
          MultThetaHist1->Fill(mlt->GetValue(), T2);

          vtxSize++;
        }
      }
    }
  }

  //MultThetaHist1->Scale(2002278/2633691);

  int binx = 50, biny = 50;
  float num, Entry;

  for (int i = 0; i < binx; i++) 
  {
    num = 0;
    for (int j = 0; j < biny; j++)
    {
      num += MultThetaHist1->GetBinContent(i, j);
    }

    for (int j = 0; j < biny; j++)
    {
      Entry = MultThetaHist1->GetBinContent(i, j);
      if (num > 0) MultThetaHist2->SetBinContent(i, j, Entry*100./num);
      if (num == 0) MultThetaHist2->SetBinContent(i, j, 0);
    }
  }

  MultThetaHist1->SetContour(20);
  MultThetaHist2->SetContour(20);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

  MultThetaHist1->Draw("COLZ");
  //MultThetaHist1->SetMinimum(0);
  //MultThetaHist1->SetMaximum(100);
  MultThetaHist1->SetTitle("");
  MultThetaHist1->SetXTitle("Multiplicity");
  MultThetaHist1->SetYTitle("Tan #theta");

  Canvas->Print( outNameStart, "pdf");

  MultThetaHist2->Draw("COLZ");
  //MultThetaHist2->SetMinimum(0);
  MultThetaHist2->SetMaximum(12);
  MultThetaHist2->SetTitle("");
  MultThetaHist2->SetXTitle("Multiplicity");
  MultThetaHist2->SetYTitle("Tan #theta");

  Canvas->Print( outNameEnd, "pdf");

  cout << vtxSize << endl;
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

    if (parNum->GetValue() == 1 /*&& areaBool*/)
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