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

Double_t customFit (Double_t *x, Double_t *par);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Mult1 = new TH1F("Mlt_PD05","Multiplicity",50,0,50);
TH1F *Mult2 = new TH1F("Mlt_PD04","Multiplicity",50,0,50);

TFile *Data1, *Data2, *Data3, *Data4;

float Data1VtxSize = 0, Data2VtxSize = 0;

void BinomialFit()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"BinomialFit.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p006.root");
  Data2 = TFile::Open("../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl001_030.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  //TF1 *func1 = new TF1 ("cFit1", customFit, 0, 50, 2);
  TF1 *f1 = new TF1 ("bFit1", "[0]*ROOT::Math::negative_binomial_pdf(x, [1], [2])", 5, 50);
  //func1->Draw();
  //TF1 *func = new TF1 ("binFit", ROOT::Math::binomial_pdf, -1, 1, 2);

  //ROOT::Math::binomial_pdf(1, 1, 1);
  
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx1->GetLeaf("flagw");

    if(PN->GetValue() == 1 && w->GetValue() == 1)
    {
      Mult1->Fill(mult->GetValue());

      Data1VtxSize++;
    }
  }
  
  for (int i = 0; i < treeDataVtx2->GetEntriesFast(); i++)
  {
    treeDataVtx2->GetEntry(i);

    TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx2->GetLeaf("flagw");

    if(PN->GetValue() == 1 && w->GetValue() == 1)
    {
      Mult2->Fill(mult->GetValue());

      Data2VtxSize++;
    }
  }

  float Hist1Mean = Mult1->GetMean();
  int bin1 = Mult1->GetXaxis()->FindBin(Hist1Mean);
  float meanPeak1 = Mult1->GetBinContent(bin1);

  float Hist2Mean = Mult2->GetMean();
  int bin2 = Mult2->GetXaxis()->FindBin(Hist2Mean);
  float meanPeak2 = Mult2->GetBinContent(bin2);

  Mult1->Scale(1/Mult1->Integral());
  Mult2->Scale(1/Mult2->Integral());

  f1->SetNpx(45);
  f1->SetParameter(0, 1);
  f1->SetParameter(1, 0.3);
  f1->SetParameter(2, 5);
  f1->Draw();
  Mult1->Fit("bFit1", "R");

  string par0Entry = "p = ";
  string par1Entry = "k = ";
  string par2Entry = "Chi2 = ";

  double p1 = f1->GetParameter(1);
  double k1 = f1->GetParameter(2);
  double chi2 = f1->GetChisquare();

  double fitMean = (k1*(1-p1))/p1;
  double fitVar = (k1*(1-p1))/(p1*p1);

  par0Entry += to_string(k1);
  par1Entry += to_string(p1);
  par2Entry += to_string(chi2);

  cout << "Mean = " << fitMean << endl;
  cout << "Std Dev = " << sqrt(fitVar) << endl;
  cout << par2Entry << endl;

  TLegend *leg1 = new TLegend (0.98, 0.55, 0.78, 0.7);
  leg1->SetHeader("Fit Parameters", "C");
  leg1->AddEntry((TObject*)0, par0Entry.c_str(), "");
  leg1->AddEntry((TObject*)0, par1Entry.c_str(), "");
  leg1->AddEntry((TObject*)0, par2Entry.c_str(), "");
  leg1->Draw();

  Mult1->Draw("SAMES HIST");
  Canvas->Print( outNameStart, "pdf");

  f1->SetParameter(0, 1);
  f1->SetParameter(1, 0.75);
  f1->SetParameter(2, 10);
  /*
  f1->SetParLimits(0, 1000000, 1100000);
  f1->SetParLimits(1, 0.3, 0.8);
  f1->SetParLimits(2, 0, 12);
  */
  f1->Draw();
  Mult2->Fit("bFit1", "R");

  par0Entry = "k = ";
  par1Entry = "p = ";
  par2Entry = "Chi2 = ";

  p1 = f1->GetParameter(1);
  k1 = f1->GetParameter(2);
  chi2 = f1->GetChisquare();

  fitMean = (k1*(1-p1))/p1;
  fitVar = (k1*(1-p1))/(p1*p1);

  par0Entry += to_string(k1);
  par1Entry += to_string(p1);
  par2Entry += to_string(chi2);

  cout << "Mean = " << fitMean << endl;
  cout << "Std Dev = " << sqrt(fitVar) << endl;
  cout << par2Entry << endl;

  TLegend *leg2 = new TLegend (0.98, 0.55, 0.78, 0.7);
  leg2->SetHeader("Fit Parameters", "C");
  leg2->AddEntry((TObject*)0, par0Entry.c_str(), "");
  leg2->AddEntry((TObject*)0, par1Entry.c_str(), "");
  leg2->AddEntry((TObject*)0, par2Entry.c_str(), "");
  leg2->Draw();

  Mult2->Draw("SAMES HIST");
  Canvas->Print( outNameEnd, "pdf");
}

Double_t customFit (Double_t *x, Double_t *par)
{
  double funct = (TMath::Factorial(par[0]-1)/TMath::Factorial(x[0]-1)*TMath::Factorial(par[0]-x[0]))*pow(par[1], par[0])*(pow(1-par[1], x[0]-par[0]));
  //Double_t funct = (ROOT::Math::tgamma(par[0])/ROOT::Math::tgamma(x[0])*ROOT::Math::tgamma(par[0]-x[0]-1))*pow(par[1], par[0])*(pow(1-par[1], x[0]-par[0]));
  
  return funct;
}