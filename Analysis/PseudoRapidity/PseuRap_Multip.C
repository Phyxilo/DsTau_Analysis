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

TH1F *Mult1 = new TH1F("M1","Pseudo-rapidity Distributions",10,0,10);
TH1F *Mult2 = new TH1F("M2","Pseudo-rapidity Distributions",10,0,10);
TH1F *Mult3 = new TH1F("M3","Pseudo-rapidity Distributions",10,0,10);
TH1F *Mult4 = new TH1F("M4","Pseudo-rapidity Distributions",10,0,10);
TH1F *Mult5 = new TH1F("M5","Pseudo-rapidity Distributions",10,0,10);
TH1F *Mult6 = new TH1F("M6","Pseudo-rapidity Distributions",10,0,10);

TFile *Data1;

float Data1TrkIndex = 0, Data2TrkIndex = 0;
float Data1VtxSize = 0, Data2VtxSize = 0;

void PseuRap_Multip()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"PseuRap_Mult.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p006.root");
  //Data1 = TFile::Open("../Root/PD05.root");
  //Data2 = TFile::Open("Root/PD04.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  //TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  int data1VtxSize = treeDataVtx1->GetEntriesFast();
  
  for (int i = 0; i < data1VtxSize; i++)
  {
    treeDataVtx1->GetEntry(i);
    
    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx1->GetLeaf("flagw");
    TLeaf *iType = treeDataVtx1->GetLeaf("intType");

    int mlt1 = 0, mlt2 = 0, mlt3 = 0, mlt4 = 0, mlt5 = 0, mlt6 = 0;
    int mlt = mult->GetValue();

    if(PN->GetValue() == 1 && w->GetValue() == 1 && iType->GetValue() >= 1)
    {
      mlt1 = 0;
      mlt2 = 0;
      mlt3 = 0;
      mlt4 = 0;
      mlt5 = 0;
      mlt6 = 0;

      for (int j = 0; j < mlt; j++)
      {
        treeDataTrk1->GetEntry(Data1TrkIndex);

        TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
        TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
        TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
        TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");

        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        double T2 = sqrt(TX*TX+TY*TY);
        double PRap = -log(tan(TX/2));

        if (PRap > 1 && PRap <= 2)
        {
          mlt1++;
        }
        else if (PRap > 2 && PRap <= 3)
        {
          mlt2++;
        }
        else if (PRap > 3 && PRap <= 4)
        {
          mlt3++;
        }
        else if (PRap > 4 && PRap <= 5.3)
        {
          mlt4++;
        }
        else if (PRap > 5.3 && PRap <= 7.7)
        {
          mlt5++;
        }
        else if (PRap > 7.7 && PRap <= 10)
        {
          mlt6++;
        }
        
        /*
        if (PRap > -5 && PRap <= -3)
        {
          mlt1++;
        }
        else if (PRap > -3 && PRap <= -1)
        {
          mlt2++;
        }
        else if (PRap > -1 && PRap <= 0)
        {
          mlt3++;
        }
        else if (PRap > 0 && PRap <= 1)
        {
          mlt4++;
        }
        else if (PRap > 1 && PRap <= 3)
        {
          mlt5++;
        }
        else if (PRap > 3 && PRap <= 5)
        {
          mlt6++;
        }
        */
        Data1TrkIndex++;
      }
    }

    if (mlt1 != 0 ) Mult1->Fill(mlt1);
    if (mlt2 != 0 ) Mult2->Fill(mlt2);
    if (mlt3 != 0 ) Mult3->Fill(mlt3);
    if (mlt4 != 0 ) Mult4->Fill(mlt4);
    if (mlt5 != 0 ) Mult5->Fill(mlt5);
    if (mlt6 != 0 ) Mult6->Fill(mlt6);
  }

  cout << Mult1->GetMean() << endl;
  cout << Mult2->GetMean() << endl;
  cout << Mult3->GetMean() << endl;
  cout << Mult4->GetMean() << endl;
  cout << Mult5->GetMean() << endl;
  cout << Mult6->GetMean() << endl;

  for (int i = 1; i < 9; i++)
  {
    int bin = Mult1->GetXaxis()->FindBin(i);
    float binCnt = Mult1->GetBinContent(bin);

    //cout << binCnt/data1VtxSize << endl;
  }

  //Mult1->GetYaxis()->SetRangeUser(0, 500000);

  Mult1->SetLineWidth(1);
  //Mult1->Scale(1/data1VtxSize);
  Mult1->SetMarkerStyle(20);
  Mult1->SetMarkerSize(1);
  Mult1->SetMarkerColor(2);
  Mult1->Draw("P");
  Mult1->Fit("gaus");
  Mult1->GetFunction("gaus")->SetLineColor(1);
  Mult1->GetFunction("gaus")->SetLineWidth(1);

  Mult2->SetLineWidth(1);
  //Mult2->Scale(1/data1VtxSize);
  Mult2->SetMarkerStyle(22);
  Mult2->SetMarkerSize(1);
  Mult2->SetMarkerColor(2);
  Mult2->Draw("SAMES P");
  Mult2->Fit("gaus");
  Mult2->GetFunction("gaus")->SetLineColor(1);
  Mult2->GetFunction("gaus")->SetLineWidth(1);

  Mult3->SetLineWidth(1);
  //Mult3->Scale(1/data1VtxSize);
  Mult3->SetMarkerStyle(47);
  Mult3->SetMarkerSize(1);
  Mult3->SetMarkerColor(2);
  Mult3->Draw("SAMES P");
  Mult3->Fit("gaus");
  Mult3->GetFunction("gaus")->SetLineColor(1);
  Mult3->GetFunction("gaus")->SetLineWidth(1);

  Mult4->SetLineWidth(1);
  //Mult4->Scale(1/data1VtxSize);
  Mult4->SetMarkerStyle(34);
  Mult4->SetMarkerSize(1);
  Mult4->SetMarkerColor(2);
  Mult4->Draw("SAMES P");
  Mult4->Fit("gaus");
  Mult4->GetFunction("gaus")->SetLineColor(1);
  Mult4->GetFunction("gaus")->SetLineWidth(1);

  Mult5->SetLineWidth(1);
  //Mult5->Scale(1/data1VtxSize);
  Mult5->SetMarkerStyle(21);
  Mult5->SetMarkerSize(1);
  Mult5->SetMarkerColor(2);
  Mult5->Draw("SAMES P");
  Mult5->Fit("gaus");
  Mult5->GetFunction("gaus")->SetLineColor(1);
  Mult5->GetFunction("gaus")->SetLineWidth(1);

  Mult6->SetLineWidth(1);
  //Mult5->Scale(1/data1VtxSize);
  Mult6->SetMarkerStyle(33);
  Mult6->SetMarkerSize(1.5);
  Mult6->SetMarkerColor(2);
  Mult6->Draw("SAMES P");
  Mult6->Fit("gaus");
  Mult6->GetFunction("gaus")->SetLineColor(1);
  Mult6->GetFunction("gaus")->SetLineWidth(1);

  gStyle->SetOptStat(0);

  auto legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->AddEntry(Mult1,"1 < #eta #leq 2","p");
  legend->AddEntry(Mult2,"2 < #eta #leq 3","p");
  legend->AddEntry(Mult3,"3 < #eta #leq 4","p");
  legend->AddEntry(Mult4,"4 < #eta #leq 5.3","p");
  legend->AddEntry(Mult5,"5.3 < #eta #leq 7.7","p");
  legend->AddEntry(Mult6,"7.7 < #eta #leq 10","p");
  legend->Draw();

  Canvas->Print( outName, "pdf");
}