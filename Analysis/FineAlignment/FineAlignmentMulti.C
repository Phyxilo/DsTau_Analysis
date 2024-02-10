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

TH1F *Hist1 = new TH1F("Hist1","Vertex Z",50000,0,50000);
TH1F *Hist3 = new TH1F("Hist3","Vertex Z",700,-100,600);

TFile *Data1;

float Data1VtxSize = 0;

void FineAlignmentMulti()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  gStyle->SetOptStat(0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FineAlignMulti.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int x = 0; x < 8; x++)
  {
    TH1F *Hist2 = new TH1F("Hist2","Vertex Z",50000,0,50000);

    char inName[64];
    sprintf(inName, "../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", x);
    Data1 = TFile::Open(inName);
    
    TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
    
    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);
      
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");
      TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

      if (parNum->GetValue() == 1)
      {
        if (intMedium->GetValue() == 1)
        {
          Hist1->Fill(vz->GetValue());
          Hist2->Fill(vz->GetValue());
        }
      }
    }

    double initZ = Hist2->FindFirstBinAbove(0);
    double lastZ = Hist2->FindLastBinAbove(0);

    //TH1F *Hist4 = new TH1F("Hist4","SubVol Z",(int)(lastZ-initZ)+2000,initZ-1000,lastZ+1000);
    TH1F *Hist4 = new TH1F("Hist4","SubVol Z",(int)(lastZ-initZ)+2000,-1000,(int)(lastZ-initZ)+1000);

    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);
      
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");
      TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *flagw = treeDataVtx1->GetLeaf("flagw");

      if (parNum->GetValue() == 1)
      {
        if (intMedium->GetValue() == 1 /*flagw->GetValue() == 1*/)
        {
          Hist3->Fill(vz->GetValue() - initZ);
          Hist4->Fill(vz->GetValue() - initZ);
        }
      }
    }

    Hist4->Draw();
    if (x == 0) { Canvas->Print( outNameStart, "pdf"); }
    else { Canvas->Print( outName, "pdf"); }

    cout << Hist2->FindLastBinAbove(0) - Hist2->FindFirstBinAbove(0) << endl;
    delete Hist2;
    delete Hist4;
  }

  Hist1->Draw();
  Canvas->Print( outName, "pdf");

  Hist3->Draw();
  Canvas->Print( outNameEnd, "pdf");
}