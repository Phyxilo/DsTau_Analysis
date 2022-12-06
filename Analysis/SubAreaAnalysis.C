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

TH2F *VXY1 = new TH2F("VXY1","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY2 = new TH2F("VXY2","Vertex X vs Y",100,10000,90000,100,10000,90000);

TFile *Data1, *Data2, *Data3, *Data4;

float Data1VtxSize = 0, Data2VtxSize = 0, Data3VtxSize = 0, Data4VtxSize = 0;

void SubAreaAnalysis()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"SubAAnalysis.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("Root/PD05.root");
  Data2 = TFile::Open("Root/PD04.root");
  Data3 = TFile::Open("Root/Geant4.root");
  Data4 = TFile::Open("Root/Pythia.root");

  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  Data1VtxSize = treeDataVtx1->GetEntriesFast();
  Data2VtxSize = treeDataVtx2->GetEntriesFast();
  
  float DataX1[(int)Data1VtxSize], DataY1[(int)Data1VtxSize];
  float DataX2[(int)Data2VtxSize], DataY2[(int)Data2VtxSize];

  TGraph *DataXY1 = new TGraph();
  TGraph *DataXY2 = new TGraph();

  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *sVol = treeDataVtx1->GetLeaf("sub_vol");
    
    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx1->GetLeaf("vx");
    TLeaf *VY = treeDataVtx1->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx1->GetLeaf("vz");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

    //PNum1->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      DataX1[i] = VX->GetValue();
      DataY1[i] = VY->GetValue();

      Data1VtxSize++;

      DataXY1->SetPoint(i, VX->GetValue(), VY->GetValue());
    }
    
  }
  
  for (int i = 0; i < treeDataVtx2->GetEntriesFast(); i++)
  {
    treeDataVtx2->GetEntry(i);

    TLeaf *sVol = treeDataVtx2->GetLeaf("sub_vol");
    
    TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx2->GetLeaf("vx");
    TLeaf *VY = treeDataVtx2->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx2->GetLeaf("vz");
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");

    //PNum2->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      DataX2[i] = VX->GetValue();
      DataY2[i] = VY->GetValue();

      Data2VtxSize++;

      DataXY2->SetPoint(i, VX->GetValue(), VY->GetValue());
    }
    
  }
  
  //TGraph *DataXY1 = new TGraph(Data1VtxSize, DataX1, DataY1);
  //TGraph *DataXY2 = new TGraph(Data2VtxSize, DataX2, DataY2);

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