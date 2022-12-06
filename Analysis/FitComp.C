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

void FitComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FitComp.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("Root/PD04_05_Merged.root");
  //Data2 = TFile::Open("Root/PD04.root");
  
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

  //Mult1->Scale(mean/Mult1->Integral());
  Mult1->Scale(1/meanPeak);
  
  TF1 *KNO = new TF1("KNOFunc",KNOFunc,5,50,5);
  TF1 *f1 = new TF1 ("bFit", "[0]*ROOT::Math::negative_binomial_pdf(x, [1], [2])", 5, 50);

  KNO->SetParameter(0, 1);
  f1->SetNpx(45);
  f1->SetParameter(0, 1);
  f1->SetParameter(1, 0.3);
  f1->SetParameter(2, 5);
  
  Mult1->Fit("KNOFunc", "R");
  TF1 *KNOf = Mult1->GetFunction("KNOFunc");
  KNOf->Draw();

  cout << KNO->GetChisquare() << endl;
  
  Mult1->Fit("bFit", "+R");
  TF1 *Binomf = Mult1->GetFunction("bFit");
  Binomf->SetLineColor(kBlue);
  Binomf->Draw("SAME ");

  cout << f1->GetChisquare() << endl;

  TLegend *legend1 = new TLegend (0.98, 0.55, 0.78, 0.7);
  legend1->SetHeader("Legend","C");
  legend1->AddEntry(Mult1,"PD05 Histogram","fel");
  legend1->AddEntry(KNOf,"KNO Scaling","l");
  legend1->AddEntry(Binomf,"Negative Binomial PDF","l");
  legend1->Draw();

  Canvas->Print(outName, "pdf");
  /*
  mean = Mult2->GetMean();
  bin = Mult2->GetXaxis()->FindBin(mean);
  meanPeak = Mult2->GetBinContent(bin);

  //Mult1->Scale(mean/Mult1->Integral());
  Mult2->Scale(1/meanPeak);
  
  KNO = new TF1("KNOFunc",KNOFunc,5,55,1);
  f1 = new TF1 ("bFit", "[0]*ROOT::Math::negative_binomial_pdf(x, [1], [2])", 5, 55);

  KNO->SetParameter(0, 1);
  f1->SetNpx(50);
  f1->SetParameter(0, 1);
  f1->SetParameter(1, 0.3);
  f1->SetParameter(2, 5);
  
  Mult2->Fit("KNOFunc");
  KNOf = Mult2->GetFunction("KNOFunc");
  KNOf->Draw();
  
  Mult2->Fit("bFit", "+");
  Binomf = Mult2->GetFunction("bFit");
  Binomf->SetLineColor(kBlue);
  Binomf->Draw("SAME");

  TLegend *legend2 = new TLegend (0.98, 0.55, 0.78, 0.7);
  legend2->SetHeader("Legend","C");
  legend2->AddEntry(Mult2,"PD05 Histogram","f");
  legend2->AddEntry("KNOf","KNO Scaling","l");
  legend2->AddEntry("Binomf","Negative Binomial PDF","l");
  legend2->Draw();

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