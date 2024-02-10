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

//TH1F *Hist1 = new TH1F("Hist1","Histogram",2,0,2);
TH1F *Hist1 = new TH1F("Hist1","Histogram",200,0,10000);
TH1F *Hist2 = new TH1F("Hist2","Histogram",200,0,10000);
TH1F *Hist3 = new TH1F("Hist3","Histogram",200,0,10000);

TGraph *DataXY1 = new TGraph();
TH1F *Hist4 = new TH1F("Hist4","Parent Number",5,0,5);
TH1F *Hist5 = new TH1F("Hist5","Subarea",63,0,63);
TH1F *Hist6 = new TH1F("Hist6","Tungsten Flag",2,0,2);
TH1F *Hist7 = new TH1F("Hist7","Z Dist.",200,0,10000);

TH1F *Hist8 = new TH1F("Hist8","Vertex Z",600,1800,2400);
TH1F *Hist9 = new TH1F("Hist9","Vertex Z",100000,0,100000);

TFile *Data1;

float Data1VtxSize = 0;

void FineAlignment()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  gStyle->SetOptStat(0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FineAlign.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  //Data1 = TFile::Open("../Root/PD05.root");
  Data1 = TFile::Open("../../Data_v20220912/PD05/Linked/RootOut/p006.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);
    
    TLeaf *plt1Seg = treeDataTrk1->GetLeaf("plt_of_1seg");
    TLeaf *flagw = treeDataVtx1->GetLeaf("flagw");
    TLeaf *vx = treeDataVtx1->GetLeaf("vx");
    TLeaf *vy = treeDataVtx1->GetLeaf("vy");
    TLeaf *vz = treeDataVtx1->GetLeaf("vz");
    TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
    TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
    TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

    if (/*area1->GetValue() == 41*/ parNum->GetValue() == 1)
    {
      if (intMedium->GetValue() == 1)
      {
        //Hist1->Fill(vz->GetValue());
        Hist1->Fill(vz->GetValue());
        Hist8->Fill(vz->GetValue());
        Hist9->Fill(vz->GetValue());
      }
      if (intMedium->GetValue() == 2)
      {
        Hist2->Fill(vz->GetValue());
      }
      if (intMedium->GetValue() == 3)
      {
        Hist3->Fill(vz->GetValue());
      }
    }

    if (intMedium->GetValue() == -1)
    {
      DataXY1->SetPoint(i, vx->GetValue(), vy->GetValue());
      Hist4->Fill(parNum->GetValue());
      Hist5->Fill(area1->GetValue());
      Hist6->Fill(flagw->GetValue());
      Hist7->Fill(vz->GetValue());
    }
  }

  cout << Hist9->FindLastBinAbove(0) - Hist9->FindFirstBinAbove(0) << endl;

  Hist1->Draw();
  Hist1->SetLineColor(kBlack);
  Hist2->Draw("SAMES");
  Hist2->SetLineColor(kRed);
  Hist3->Draw("SAMES");
  Hist3->SetLineColor(kBlue);
  Canvas->Print( outNameStart, "pdf");

  Hist8->Draw();
  Canvas->Print( outName, "pdf");  

  Hist7->Draw();
  Canvas->Print( outName, "pdf");

  DataXY1->SetTitle("-1 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY1->GetXaxis()->SetLimits(10000, 120000);
  DataXY1->GetHistogram()->SetMaximum(90000);
  DataXY1->GetHistogram()->SetMinimum(10000);
  DataXY1->Draw("AP");
  Canvas->Print( outName, "pdf");

  Hist4->Draw();
  Canvas->Print( outName, "pdf");

  Hist5->Draw();
  Canvas->Print( outName, "pdf");

  Hist6->Draw();
  Canvas->Print( outNameEnd, "pdf");
}