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

TH1F *ParHisto1 = new TH1F("IP_Data_Emulsion","",50,0,10);
TH1F *ParHisto2 = new TH1F("IP_Data_Tungsten","",50,0,10);
TH1F *ParHisto3 = new TH1F("Multip_Emulsion","",100,0,100);
TH1F *ParHisto4 = new TH1F("Multip_Tungsten","",100,0,100);
TH1F *ParHisto5 = new TH1F("PseuRap_Emulsion","",100,0,20);
TH1F *ParHisto6 = new TH1F("PseuRap_Tungsten","",100,0,20);

TFile *Data1;

float Data1VtxSize = 0;

void CanvasModifier(TH1F *hist);

void ParHist()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"Hist.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD04_05_Merged.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  
  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);
    
    TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
    TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk1->GetLeaf("ip_to_1ry_using_1stseg");
    TLeaf *flagw = treeDataTrk1->GetLeaf("flagw");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();
    double T2 = sqrt(TX*TX+TY*TY);

    if (flagw->GetValue() == 0)
    {
      ParHisto1->Fill(IP->GetValue());
      ParHisto5->Fill(-log(tan(T2/2)));
    }
    else
    {
      ParHisto2->Fill(IP->GetValue());
      ParHisto6->Fill(-log(tan(T2/2)));
    }
  }

  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *flagw = treeDataVtx1->GetLeaf("flagw");

    treeDataVtx1->GetEntry(i);

    if (flagw->GetValue() == 0)
    {
      ParHisto3->Fill(mult->GetValue());
    }
    else
    {
      ParHisto4->Fill(mult->GetValue());
    }
  }

  ParHisto1->Draw();
  CanvasModifier(ParHisto1);
  ParHisto1->SetXTitle("IP (#mum)");
  Canvas->Print( outNameStart, "pdf");

  ParHisto2->Draw();
  CanvasModifier(ParHisto2);
  ParHisto2->SetXTitle("IP (#mum)");
  Canvas->Print( outName, "pdf");

  ParHisto3->Draw();
  CanvasModifier(ParHisto3);
  ParHisto3->SetXTitle("ns");
  Canvas->Print( outName, "pdf");

  ParHisto4->Draw();
  CanvasModifier(ParHisto4);
  ParHisto4->SetXTitle("ns");
  Canvas->Print( outName, "pdf");

  ParHisto5->Draw();
  CanvasModifier(ParHisto5);
  ParHisto5->SetXTitle("Pseudo Rapidity");
  Canvas->Print( outName, "pdf");

  ParHisto6->Draw();
  CanvasModifier(ParHisto6);
  ParHisto6->SetXTitle("Pseudo Rapidity");
  Canvas->Print( outNameEnd, "pdf");
}

void CanvasModifier(TH1F *hist)
{
  Canvas->Update();
  TPaveStats *ps = (TPaveStats*)Canvas->GetPrimitive("stats");
  ps->SetName("mystats");
  TList *listOfLines = ps->GetListOfLines();
  TText *tconst = ps->GetLineWith("Entries");
  listOfLines->Remove(tconst);
  hist->SetStats(0);
  Canvas->Modified();
}