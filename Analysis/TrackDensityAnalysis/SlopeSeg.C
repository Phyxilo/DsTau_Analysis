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

void SlopeSeg()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  //Canvas->SetWindowSize(800, 800);

  TH2F *MultThetaHist1 = new TH2F("MultTheta1","Multiplicity vs. Theta for Sub-volume 1",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist2 = new TH2F("MultTheta2","Multiplicity vs. Theta for Sub-volume 2",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist3 = new TH2F("MultTheta3","Multiplicity vs. Theta for Sub-volume 3",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist4 = new TH2F("MultTheta4","Multiplicity vs. Theta for Sub-volume 4",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist5 = new TH2F("MultTheta5","Multiplicity vs. Theta for Sub-volume 5",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist6 = new TH2F("MultTheta6","Multiplicity vs. Theta for Sub-volume 6",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist7 = new TH2F("MultTheta7","Multiplicity vs. Theta for Sub-volume 7",36,-0.5,35.5,50,0.0,0.4);
  TH2F *MultThetaHist8 = new TH2F("MultTheta8","Multiplicity vs. Theta for Sub-volume 8",36,-0.5,35.5,50,0.0,0.4);

  TH2F *MultThetaHistTot = new TH2F("MultThetaTot","Multiplicity vs. Theta Full Module",36,-0.5,35.5,50,0,0.4);

  TFile *Data, *MC1, *MC2, *MC3, *MC4;

  TH2F *HistArr[8] = {MultThetaHist1, MultThetaHist2, MultThetaHist3, MultThetaHist4, MultThetaHist5, MultThetaHist6, MultThetaHist7, MultThetaHist8};

  char  outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64, "SlopeSeg.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

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
    TTree *treeDataPar = (TTree*)Data->Get("PAR");

    double *dataEndArr = DataEndPoints(treeDataVtx);
    //double *dataEndArr = MCEndPoints(treeDataVtx);
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

        TLeaf *nseg = treeDataPar->GetLeaf("nseg");

        treeDataVtx->GetEntry(vtxIndex);
        treeDataPar->GetEntry(vtxIndex);

        MultThetaHistTot->Fill(nseg->GetValue(), T2);
        HistArr[dirIndex]->Fill(nseg->GetValue(), T2);

        bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

        //if (areaBool == 1 && iType->GetValue() >= 1 && vz->GetValue() - dataEndArr[0] > migCut && vz->GetValue() - dataEndArr[1] < -migCut)
        if (/*areaBool == 1 &&*/ iType->GetValue() >= 1 && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
        {
          //MultThetaHistTot->Fill(nseg->GetValue(), T2);
          //HistArr[dirIndex]->Fill(nseg->GetValue(), T2);

          vtxSize++;
        }
      }
    }

      HistArr[dirIndex]->SetContour(20);

      HistArr[dirIndex]->Draw("COLZ");
      //MultThetaHistTot->SetMinimum(0);
      //MultThetaHistTot->SetMaximum(100);
      //MultThetaHistTot->SetTitle("");
      HistArr[dirIndex]->SetXTitle("Number of Segments");
      HistArr[dirIndex]->SetYTitle("Tan #theta");

    if (dirIndex == 0) {Canvas->Print(outNameStart, "pdf");}
    else {Canvas->Print(outName, "pdf");}
  }

  MultThetaHistTot->SetContour(20);

  MultThetaHistTot->Draw("COLZ");
  //MultThetaHistTot->SetMinimum(0);
  //MultThetaHistTot->SetMaximum(100);
  //MultThetaHistTot->SetTitle("");
  MultThetaHistTot->SetXTitle("Number of Segments");
  MultThetaHistTot->SetYTitle("Tan #theta");

  Canvas->Print( outNameEnd, "pdf");
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