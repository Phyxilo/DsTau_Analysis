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

void SubVolumeAnalysisScatter()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  Data1 = TFile::Open("Root/PD04.root");
  Data2 = TFile::Open("Root/PD05.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  for (int subVol = 0; subVol <= 8; subVol++)
  {
    TGraph *DataXY1 = new TGraph();
    TGraph *DataXY2 = new TGraph();

    char  outName[64], outNameStart[64], outNameEnd[64];
    sprintf(outName,"SubVolumeAnalysis/Scatter/SubVAnalysisScatter_%d.pdf", subVol);
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *sVol = treeDataVtx1->GetLeaf("sub_vol");
      
      if (sVol->GetValue() == subVol)
      {
        TLeaf *VX = treeDataVtx1->GetLeaf("vx");
        TLeaf *VY = treeDataVtx1->GetLeaf("vy");
        TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

        //PNum1->Fill(PN->GetValue());

        if(PN->GetValue() == 1)
        {
          DataXY1->SetPoint(i, VX->GetValue(), VY->GetValue());
        }
      }
    }
    
    for (int i = 0; i < treeDataVtx2->GetEntriesFast(); i++)
    {
      treeDataVtx2->GetEntry(i);

      TLeaf *sVol = treeDataVtx2->GetLeaf("sub_vol");
      
      if (sVol->GetValue() == subVol)
      {
        TLeaf *VX = treeDataVtx2->GetLeaf("vx");
        TLeaf *VY = treeDataVtx2->GetLeaf("vy");
        TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");

        //PNum2->Fill(PN->GetValue());

        if(PN->GetValue() == 1)
        {
          DataXY2->SetPoint(i, VX->GetValue(), VY->GetValue());
        }
      }
    }

    DataXY1->SetTitle("PD04 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
    DataXY1->GetXaxis()->SetLimits(10000, 120000);
    DataXY1->GetHistogram()->SetMaximum(90000);
    DataXY1->GetHistogram()->SetMinimum(10000);
    DataXY1->Draw("AP");

    Canvas->Print( outNameStart, "pdf");

    DataXY2->SetTitle("PD05 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
    DataXY2->GetXaxis()->SetLimits(10000, 120000);
    DataXY2->GetHistogram()->SetMaximum(90000);
    DataXY2->GetHistogram()->SetMinimum(10000);
    DataXY2->Draw("AP");

    Canvas->Print( outNameEnd, "pdf");
  }
  
}