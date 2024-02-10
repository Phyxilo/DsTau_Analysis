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

Double_t KNOFunc (Double_t *x, Double_t *par);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",50,0,50);
//TH1F *Mult2 = new TH1F("Mlt","Multiplicity",50,5,55);

TFile *Data1, *Data2;

float Data1VtxSize, Data2VtxSize;
double mean = 1;

void KNO()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"KNO.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("Root/PD04_05_Merged.root");
  //Data2 = TFile::Open("../PD04/Out.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  //TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  Data1VtxSize = treeDataVtx1->GetEntriesFast();
  //Data2VtxSize = treeDataVtx2->GetEntriesFast();

  for (int i = 0; i < Data1VtxSize; i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx1->GetLeaf("flagw");

    if(PN->GetValue() == 1 && w->GetValue() == 1)
    {
      Mult1->Fill(mult->GetValue());
    }
  }
  /*
  for (int i = 0; i < Data2VtxSize; i++)
  {
    treeDataVtx2->GetEntry(i);

    TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx2->GetLeaf("flagw");

    if(PN->GetValue() == 1 && w->GetValue() == 1)
    {
      Mult2->Fill(mult->GetValue());
    }
  }
  */
  mean = Mult1->GetMean();
  int bin = Mult1->GetXaxis()->FindBin(mean);
  float meanPeak = Mult1->GetBinContent(bin);

  float scale = mean/Mult1->Integral();
  cout << scale << endl;
  //Mult1->Scale(mean/Mult1->Integral());
  Mult1->Scale(scale);

  TF1 *KNO = new TF1("KNOFunc",KNOFunc,5,55,5);
  KNO->SetParameter(0, 1);

  Mult1->Fit("KNOFunc", "R");

  float chi2 = KNO->GetChisquare();
  float c = KNO->GetParameter(0);
  cout << "Chi2: " << chi2 << endl;

  string par0Entry = "c = ";
  string par1Entry = "Chi2 = ";

  par0Entry += to_string(c);
  par1Entry += to_string(chi2);

  TLegend *leg1 = new TLegend (0.98, 0.55, 0.78, 0.7);
  leg1->SetHeader("Fit Parameters", "C");
  //leg1->AddEntry((TObject*)0, par0Entry.c_str(), "");
  leg1->AddEntry((TObject*)0, par1Entry.c_str(), "");
  leg1->Draw();

  Mult1->Draw("SAMES");
  Canvas->Print( outName, "pdf");
  /*
  mean = Mult2->GetMean();
  bin = Mult2->GetXaxis()->FindBin(mean);
  meanPeak = Mult2->GetBinContent(bin);

  //Mult2->Scale(mean/Mult2->Integral());
  Mult2->Scale(1/meanPeak);

  KNO = new TF1("KNOFunc",KNOFunc,5,55,1);
  KNO->SetParameter(0, 1);

  Mult2->Fit("KNOFunc");

  chi2 = KNO->GetChisquare();
  c = KNO->GetParameter(0);
  cout << "Chi2: " << chi2 << endl;

  par0Entry = "c = ";
  par1Entry = "Chi2 = ";

  par0Entry += to_string(c);
  par1Entry += to_string(chi2);

  TLegend *leg2 = new TLegend (0.98, 0.55, 0.78, 0.7);
  leg2->SetHeader("Fit Parameters", "C");
  leg2->AddEntry((TObject*)0, par0Entry.c_str(), "");
  leg2->AddEntry((TObject*)0, par1Entry.c_str(), "");
  leg2->Draw();

  Mult2->Draw("SAMES HIST");
  Canvas->Print( outNameEnd, "pdf");
  */
}

Double_t KNOFunc (Double_t *x, Double_t *par)
{
  double n = x[0]/mean;
  //double funct = par[0]*(1.895*n + 16.85*pow(n, 3) - 3.32*pow(n, 5) + 0.166*pow(n, 7))*exp(-3.04*n);
  double funct = (par[0]*n + par[1]*pow(n, 3) - par[2]*pow(n, 5) + par[3]*pow(n, 7))*exp(par[4]*n);
  
  return funct;
}