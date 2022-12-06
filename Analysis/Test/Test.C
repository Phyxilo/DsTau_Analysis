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

TH1F *Hist1 = new TH1F("Hist1","Histogram",100,0,100);
TH1F *Hist2 = new TH1F("Hist2","Histogram",100,0,100);

TFile *Data1;

float Data1VtxSize = 0;

void Test()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"Test.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD05.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  
  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);
    
    TLeaf *plt1Seg = treeDataTrk1->GetLeaf("plt_of_1seg");
    TLeaf *flagw = treeDataTrk1->GetLeaf("flagw");
    TLeaf *vz = treeDataTrk1->GetLeaf("vz");

    if (flagw->GetValue() == 0)
    {
      //Hist1->Fill(vz->GetValue());
      Hist2->Fill(plt1Seg->GetValue());
    }
    else
    {
      Hist1->Fill(plt1Seg->GetValue());
    }
  }

  Hist1->Draw();
  Hist1->SetLineColor(kRed);
  Hist2->Draw("SAMES");
  Canvas->Print( outName, "pdf");

  //Hist2->Draw();
  //Canvas->Print( outNameEnd, "pdf");
}