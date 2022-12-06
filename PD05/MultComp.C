#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *MultHist1 = new TH1F("Mult1","Multiplicity Histogram",100,0,100);
TH1F *MultHist2 = new TH1F("Mult2","Multiplicity Histogram (w/o Track Reduction)",100,0,100);

TFile *data1, *data2;

void MultComp()
{
  Canvas->SetWindowSize(1920, 1080);

  data1 = TFile::Open("RootOut/PD05Full.root");
  data2 = TFile::Open("RootOut/PD05Full_NoTrkRed.root");

  TTree *VtxTree1 = (TTree*)data1->Get("VTX");
  TTree *VtxTree2 = (TTree*)data2->Get("VTX");

  TLeaf *Mult1 = VtxTree1->GetLeaf("n_1ry_trk");
  TLeaf *Mult2 = VtxTree2->GetLeaf("n_1ry_trk");

  for (int i = 0; i < VtxTree1->GetEntriesFast(); i++)
  {
    VtxTree1->GetEntry(i);
    MultHist1->Fill(Mult1->GetValue());
  }
  for (int i = 0; i < VtxTree2->GetEntriesFast(); i++)
  {
    VtxTree2->GetEntry(i);
    MultHist2->Fill(Mult2->GetValue());
  }

  MultHist2->Scale(VtxTree1->GetEntriesFast()/VtxTree2->GetEntriesFast());

  MultHist1->Draw("HIST"); MultHist1->SetLineColor(kRed);
  MultHist2->Draw("SAME HIST"); MultHist2->SetLineColor(kBlue);

  MultHist1->GetYaxis()->SetRangeUser(0, 35000);

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(MultHist1,"Track Reduction","f");
  legendTX->AddEntry(MultHist2,"w/o Track Reduction","f");
  legendTX->Draw();

  Canvas->Print( "MultHist.pdf", "pdf");
}