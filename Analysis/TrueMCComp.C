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

TH1F *G4MultCompHist = new TH1F("G4MultCompHist","Geant4 Multiplicty Histogram",50,0,100);
//TH2F *MultThetaHist2 = new TH2F("MultThetaPD04","Multiplicity vs. Theta",10,0,50,18,0,450);

TFile *Data1, *Data2;

float Data1TrkIndex = 0, Data2TrkIndex = 0;

void TrueMCComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"TrueMCComp.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("TrueMCCombined.root");
  //Data2 = TFile::Open("Root/PD04.root");
  
  TTree *DecayTree1 = (TTree*)Data1->Get("DecayTree");
  //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  int treeSize = DecayTree1->GetEntriesFast();
  for (int i = 0; i < treeSize; i++)
  {
    DecayTree1->GetEntry(i);

    TLeaf *flag = DecayTree1->GetLeaf("Flag");
    TLeaf *mult = DecayTree1->GetLeaf("Mult");

    if (flag->GetValue() == 111)
    {
      G4MultCompHist->Fill(mult->GetValue());
    }
    if (i%100000 == 0){cout << i << "/" << treeSize << endl;}
  }
  
  G4MultCompHist->Draw();
  Canvas->Print( outName, "pdf");
  
}