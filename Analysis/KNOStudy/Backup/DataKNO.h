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

#ifndef DATAKNO_H
#define DATAKNO_H

float MultCorection(int mult);
void ReadMultEffData();
double DataMean(TTree *data);

TH1F *Multip = new TH1F("","Multiplicity",50,0,50);
TH1F *MultipEffCorrected = new TH1F("","Efficiency Corrected Multiplicity",50,0,50);
TH1F *NormedMult = new TH1F("","",50,0.,3);

TFile *Data1;

float Data1VtxSize;
double mean = 1;
float migCut = 15;
float multEffArr[50];

TH1F* DataKNO()
{
  char outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64, "DataKNO.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  ReadMultEffData();

  for (int j = 0; j < 8; j++)
  {
    char dir [128];
    snprintf(dir, 128, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut_4Sigma/p%02d6.root", j);
    Data1 = TFile::Open(dir);
    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");

    double mean = DataMean(treeDataVtx1);

    Data1VtxSize = treeDataVtx1->GetEntriesFast();
    for (int i = 0; i < Data1VtxSize; i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *iMed = treeDataVtx1->GetLeaf("intMed");
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");

      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));
      if(PN->GetValue() == 1 && iMed->GetValue() == 1 && areaBool && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
      {
        Multip->Fill(MultCorection(mult->GetValue()));
        int Mlt = (int)MultCorection(mult->GetValue());

        float weigth = 1;
        if (Mlt > 0 && Mlt < 50)
        {
          weigth = 1/multEffArr[Mlt];
        }
        else
        {
          weigth = 1;
        }

        MultipEffCorrected->Fill(Mlt, weigth);
      }
    }
  }

  gStyle->SetOptFit(100);
  gPad->Update();
  
  float correctedMean = MultipEffCorrected->GetMean()/1.0536345;
  float multMean = Multip->GetMean();
  int bin = Multip->GetXaxis()->FindBin(multMean);
  float meanPeak = Multip->GetBinContent(bin);

  correctedMean += 2.06; // Alpha correction

  int scaleFac = 0;
  for (int j = 0; j < 8; j++)
  {
    char dir [128];
    snprintf(dir, 128, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut_4Sigma/p%02d6.root", j);
    Data1 = TFile::Open(dir);
    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
    Data1VtxSize = treeDataVtx1->GetEntriesFast();

    for (int i = 0; i < Data1VtxSize; i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");

      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      if(PN->GetValue() == 1 && w->GetValue() == 1 && areaBool)
      {
        NormedMult->Fill(MultCorection(mult->GetValue())/correctedMean);
        int Mlt = (int)MultCorection(mult->GetValue());

        float weigth = 1;

        if (Mlt > 0 && Mlt < 50)
        {
          weigth = 1/multEffArr[Mlt];
        }
        else
        {
          weigth = 1;
        }
        scaleFac += weigth;
      }
    }
  }

  NormedMult->Scale((correctedMean)/scaleFac);
  NormedMult->SetLineColor(kBlack);
  NormedMult->SetXTitle("z");
  NormedMult->SetYTitle("#Psi(z)");

  for (int bin = 1; bin <= NormedMult->GetNbinsX(); ++bin)
  {
    float content = NormedMult->GetBinContent(bin);
    float error = NormedMult->GetBinError(bin);
    float additionalError = 0.025 * content;
    NormedMult->SetBinError(bin, sqrt(error * error + additionalError * additionalError));
  }

  NormedMult->Draw("E1");
  
  return NormedMult;
}

void ReadMultEffData()
{
  FILE *inFile = fopen("MultEfficiency_PLink.dat", "r");

  for(int i = 0; i < 50; i++)
  {
    fscanf(inFile, "%8f", &multEffArr[i]);
  }
  fclose(inFile);
}

double DataMean(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);
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

  static double mean = InterHist->GetMean();
  delete InterHist;

  return mean;
}

float MultCorection(int mult)
{
  float a = 0.001568;
  float b = 0.07993;
  float correctedMult = mult*(1 + (a*mult + b));

  return correctedMult;
}

#endif