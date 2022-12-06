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

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TFile *Data1, *Data2;

float thetaStep = 50;

void AnalysisThetaLoop()
{
  for (int thetaSize = 0; thetaSize <= 450; thetaSize += thetaStep)
  {
    float Data1TrkIndex = 0;
    float thetaMin = thetaSize;
    float thetaMax = thetaSize+thetaStep;
    
    TH2F *MultThetaHist1 = new TH2F("MultTheta","Multiplicity vs. Theta",50,0,50,thetaStep,thetaMin,thetaMax);

    Canvas->SetWindowSize(1920, 1080);
    Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];
    sprintf(outName,"W/ThetaSubRegions/Analysis_%d-%d.pdf", (int)thetaMin, (int)thetaMax);
    //sprintf(outName,"Analysis.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);
    
    Data1 = TFile::Open("Root/PD04_05_Merged.root");
    //Data2 = TFile::Open("Root/PD04.root");
    
    TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
    //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
    //TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);
      
      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");

      int mlt = mult->GetValue();

      if(PN->GetValue() == 1 && w->GetValue() == 1)
      {
        for (int j = 0; j < mlt; j++)
        {
          treeDataTrk1->GetEntry(Data1TrkIndex);

          //cout << Data1TrkIndex << endl;

          TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
          TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
          TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
          TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");

          float TX = slpTX->GetValue() - beamTX->GetValue();
          float TY = slpTY->GetValue() - beamTY->GetValue();
          float T2 = sqrt(TX*TX+TY*TY)*1000;

          if (T2 >= thetaMin && T2 < thetaMax)
          {
            //cout << "thetaMin: " << thetaMin << ", thetaMax: " << thetaMax << ", T2: " << T2 << endl;
            //cout << T2 << endl;
            MultThetaHist1->Fill(mlt, T2);
          }

          Data1TrkIndex++;
        }
      }
    }

    float MaxBin = MultThetaHist1->GetMaximumBin();
    float MaxCount = MultThetaHist1->GetBinContent(MaxBin);
    //cout << MaxCount << endl;

    //Double_t norm = 1/MultThetaHist1->Integral();
    //MultThetaHist1->Scale(1/MaxCount);

    //Double_t levels[] = {MultThetaHist1->GetMinimum() - 1, 0.0, 200, 400, 600, 800, MultThetaHist1->GetMinimum() + 1};
    MultThetaHist1->SetContour(4);
    //MultThetaHist1->SetContour((sizeof(levels)/sizeof(Double_t)), levels);

    MultThetaHist1->Draw("COLZ");
    MultThetaHist1->SetXTitle("Multiplicity");
    MultThetaHist1->SetYTitle("Theta (mrad)");

    Canvas->Modified(); Canvas->Update();
    TPaveStats *StatBox = (TPaveStats*)Canvas->GetPrimitive("stats");
    StatBox->SetName("PD05");
    StatBox->SetY1NDC(0.9);
    StatBox->SetY2NDC(0.7);
    StatBox->SetX1NDC(0.9);
    StatBox->SetX2NDC(0.7);
    StatBox->Draw();

    Canvas->Print( outName, "pdf");
    delete MultThetaHist1;
  }
}