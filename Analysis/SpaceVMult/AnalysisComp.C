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
double dataCorrection = 1.05;
// double dataCorrection = 1;

float migCut = 18;

void AnalysisComp()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  //Canvas->SetWindowSize(800, 800);

  TH2F *MultThetaHistData = new TH2F("MultThetaData","Multiplicity vs. Theta",50,0,50,50,0,0.2);
  TH2F *MultThetaHistDataNormed = new TH2F("MultThetaDataXNorm","Multiplicity vs. Theta",50,0,50,50,0,0.2);

  TH2F *MultThetaHistMC = new TH2F("MultThetaMC","Multiplicity vs. Theta",50,0,50,50,0,0.2);
  TH2F *MultThetaHistMCNormed = new TH2F("MultThetaMCXNorm","Multiplicity vs. Theta",50,0,50,50,0,0.2);

  TFile *Data, *MC;

  char  outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64,"AnalysisComp.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  int vtxSize = 0;

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    snprintf(dataName, 256, "../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", dirIndex);

    if (dirIndex < 7) { snprintf(MC1Name, 256, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC1Name, 256, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC2Name, 256, "../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC2Name, 256, "../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC3Name, 256, "../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC3Name, 256, "../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC4Name, 256, "../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC4Name, 256, "../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC5Name, 256, "../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC5Name, 256, "../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data = TFile::Open(dataName);
    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeDataVtx = (TTree*)Data->Get("VTX");

    MC = TFile::Open(MC5Name);
    TTree *treeMCTrk = (TTree*)MC->Get("TRK");
    TTree *treeMCVtx = (TTree*)MC->Get("VTX");

    double *dataEndArr = DataEndPoints(treeDataVtx);
    double *mcEndArr = MCEndPoints(treeMCVtx);
    double dataMean = DataMean(treeDataVtx);
    double mcMean = DataMean(treeMCVtx);

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

        if (areaBool && iType->GetValue() >= 1 && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
        {
          MultThetaHistData->Fill(mlt->GetValue(), T2);

          vtxSize++;
        }
      }
    }

    for (int i = 0; i < treeMCTrk->GetEntriesFast(); i++)
    {
      treeMCTrk->GetEntry(i);

      TLeaf *PN = treeMCTrk->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeMCTrk->GetLeaf("flagw");
      TLeaf *vID = treeMCTrk->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if (w->GetValue() == 1)
      {
        TLeaf *slpTX = treeMCTrk->GetLeaf("tx");
        TLeaf *slpTY = treeMCTrk->GetLeaf("ty");
        TLeaf *beamTX = treeMCTrk->GetLeaf("txpeak");
        TLeaf *beamTY = treeMCTrk->GetLeaf("typeak");

        double TX = (slpTX->GetValue() - beamTX->GetValue());
        double TY = (slpTY->GetValue() - beamTY->GetValue());
        double T2 = sqrt(TX*TX+TY*TY);

        TLeaf *mlt = treeMCVtx->GetLeaf("n_1ry_trk");
        TLeaf *iType = treeMCVtx->GetLeaf("intType");
        TLeaf *area1 = treeMCVtx->GetLeaf("area1");
        TLeaf *vz = treeMCVtx->GetLeaf("vz");

        treeMCVtx->GetEntry(vtxIndex);

        if (iType->GetValue() >= 1 && vz->GetValue() > mcMean - (250-migCut) && vz->GetValue() < mcMean + (250-migCut))
        {
          MultThetaHistMC->Fill(mlt->GetValue(), T2);

          vtxSize++;
        }
      }
    }
  }

  int binx = 50, biny = 50;
  float num, Entry;

  for (int i = 0; i < binx; i++) 
  {
    num = 0;
    for (int j = 0; j < biny; j++)
    {
      num += MultThetaHistData->GetBinContent(i, j);
    }

    for (int j = 0; j < biny; j++)
    {
      Entry = MultThetaHistData->GetBinContent(i, j);
      if (num > 0) MultThetaHistDataNormed->SetBinContent(i, j, Entry*100./num);
      if (num == 0) MultThetaHistDataNormed->SetBinContent(i, j, 0);
    }
  }

  for (int i = 0; i < binx; i++) 
  {
    num = 0;
    for (int j = 0; j < biny; j++)
    {
      num += MultThetaHistMC->GetBinContent(i, j);
    }

    for (int j = 0; j < biny; j++)
    {
      Entry = MultThetaHistMC->GetBinContent(i, j);
      if (num > 0) MultThetaHistMCNormed->SetBinContent(i, j, Entry*100./num);
      if (num == 0) MultThetaHistMCNormed->SetBinContent(i, j, 0);
    }
  }

  MultThetaHistData->SetContour(20);
  MultThetaHistDataNormed->SetContour(20);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

  MultThetaHistData->Draw("COLZ");
  MultThetaHistData->SetTitle("");
  MultThetaHistData->SetXTitle("Multiplicity");
  MultThetaHistData->SetYTitle("Tan #theta");

  Canvas->Print(outNameStart, "pdf");

  MultThetaHistDataNormed->Draw("COLZ");
  MultThetaHistDataNormed->SetMaximum(12);
  MultThetaHistDataNormed->SetTitle("");
  MultThetaHistDataNormed->SetXTitle("Multiplicity");
  MultThetaHistDataNormed->SetYTitle("Tan #theta");

  Canvas->Print(outName, "pdf");

  MultThetaHistMC->SetContour(20);
  MultThetaHistMCNormed->SetContour(20);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

  MultThetaHistMC->Draw("COLZ");
  MultThetaHistMC->SetTitle("");
  MultThetaHistMC->SetXTitle("Multiplicity");
  MultThetaHistMC->SetYTitle("Tan #theta");

  Canvas->Print(outName, "pdf");

  MultThetaHistMCNormed->Draw("COLZ");
  MultThetaHistMCNormed->SetMaximum(12);
  MultThetaHistMCNormed->SetTitle("");
  MultThetaHistMCNormed->SetXTitle("Multiplicity");
  MultThetaHistMCNormed->SetYTitle("Tan #theta");

  Canvas->Print(outName, "pdf");

  TH2F *DividedHist = (TH2F*)MultThetaHistData->Clone("DividedHist");
  DividedHist->Divide(MultThetaHistMC);

  DividedHist->SetContour(20);
  DividedHist->SetContour(20);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

  DividedHist->SetMinimum(0.);
  DividedHist->SetMaximum(2.0);

  const Int_t Number = 5;
  Double_t Red[Number]    = {1.0, 0.0, 0.0, 0.0, 1.0};
  Double_t Green[Number]  = {0.0, 1.0, 0.0, 1.0, 0.0};
  Double_t Blue[Number]   = {0.0, 0.0, 1.0, 0.0, 0.0};
  Double_t Length[Number] = {0.0, 0.25, 0.5, 0.75, 1.0};

  Int_t nb = 255;
  TColor::CreateGradientColorTable(Number, Length, Red, Green, Blue, nb);
  gStyle->SetNumberContours(nb);

  DividedHist->Draw("COLZ");
  DividedHist->SetTitle("");
  DividedHist->SetXTitle("Multiplicity");
  DividedHist->SetYTitle("Tan #theta");

  Canvas->Print(outName, "pdf");

  TH2F *DividedHistNormed = (TH2F*)MultThetaHistDataNormed->Clone("DividedHistNormed");
  DividedHistNormed->Divide(MultThetaHistMCNormed);

  DividedHistNormed->SetMinimum(0.);
  DividedHistNormed->SetMaximum(2.0);

  DividedHistNormed->Draw("COLZ");
  DividedHistNormed->SetTitle("");
  DividedHistNormed->SetXTitle("Multiplicity");
  DividedHistNormed->SetYTitle("Tan #theta");

  Canvas->Print(outNameEnd, "pdf");
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