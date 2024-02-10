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
Double_t KNOGFunc (Double_t *x, Double_t *par);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Multip = new TH1F("","",50,0,50);
TH1F *NormedMult = new TH1F("","",60,0,3);

TFile *Data1;

float Data1VtxSize;
double mean = 1;

void FitComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FitComp.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int j = 0; j < 8; j++)
  {
    char dir [128];

    sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data1 = TFile::Open(dir);

    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");

    Data1VtxSize = treeDataVtx1->GetEntriesFast();

    for (int i = 0; i < Data1VtxSize; i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");

      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      if(PN->GetValue() == 1 && w->GetValue() == 1 && areaBool)
      {
        Multip->Fill(mult->GetValue());
      }
    }
  }
  
  gStyle->SetOptFit(1);
  gPad->Update();

  //Multip->Divide(MultEff);

  TF1 *MultKNOG = new TF1("MultKNOGFunc",KNOGFunc,12,50,3);

  Multip->Fit("MultKNOGFunc", "R");
  TF1 *MultipKNOGf = Multip->GetFunction("MultKNOGFunc");

  double fitMean = MultipKNOGf->Mean(0, 50);

  float multMean = Multip->GetMean();
  int bin = Multip->GetXaxis()->FindBin(multMean);
  float meanPeak = Multip->GetBinContent(bin);

  for (int j = 0; j < 8; j++)
  {
    char dir [128];

    sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data1 = TFile::Open(dir);
    
    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");

    Data1VtxSize = treeDataVtx1->GetEntriesFast();

    for (int i = 0; i < Data1VtxSize; i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");

      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      if(PN->GetValue() == 1 && w->GetValue() == 1 && areaBool)
      {
        //NormedMult->Fill((mult->GetValue()+0.5)/(fitMean+0.5));
        NormedMult->Fill((mult->GetValue())/(fitMean));
      }
    }
  }

  mean = NormedMult->GetMean();

  //NormedMult->Scale((fitMean+0.5)/NormedMult->Integral());
  NormedMult->Scale((fitMean)/NormedMult->Integral());
  NormedMult->SetLineColor(kBlack);
  NormedMult->SetXTitle("z");
  NormedMult->SetYTitle("#Psi(z)");
  NormedMult->Draw("E1");
  
  TH1* NormedMult2 = new TH1F(*NormedMult);
  //TH1* NormedMult3 = new TH1F(*NormedMult);
  
  TF1 *KNO = new TF1("KNOFunc",KNOFunc,0.55,3,5);
  TF1 *KNOG = new TF1("KNOGFunc",KNOGFunc,0.55,3,3);
  //TF1 *f1 = new TF1("bFit", "[0]*ROOT::Math::negative_binomial_pdf(x, [1], [2])",0.5,3);

  KNO->SetParameter(0, 10);
  KNOG->SetParameter(0, 10);
  /*
  f1->SetNpx(60);
  f1->SetParameter(0, 10);
  f1->SetParameter(1, 0.3);
  f1->SetParameter(2, 0.5);
  */
  NormedMult->Fit("KNOFunc", "R", "");
  TF1 *KNOf = NormedMult->GetFunction("KNOFunc");
  //KNOf->Draw("SAME");
  
  NormedMult2->Fit("KNOGFunc", "R", "SAMES");
  TF1 *KNOGf = NormedMult2->GetFunction("KNOGFunc");
  KNOGf->SetLineColor(kBlue);
  
  /*
  NormedMult3->Fit("bFit", "R+", "SAMES");
  TF1 *Binomf = NormedMult3->GetFunction("bFit");
  Binomf->SetLineColor(kMagenta);
  NormedMult3->Draw("SAMES E1");
  */
  
  TF1 *KNOM = new TF1("KNOMeasured","1.19*pow(x, 0.66)*exp(-0.62*x*x)",0,3);
  //TF1 *KNOM = new TF1("KNOMeasured","1.19*(x+0.14)*exp(-0.62*pow(x+0.14, 2))",0,3);
  KNOM->SetNpx(6000);
  KNOM->SetLineColor(kOrange +2);
  KNOM->Draw("SAMES");

  //cout << f1->GetChisquare() << endl;
  cout << "Histogram Mean: " << multMean << endl;
  cout << "Fit Mean: " << fitMean << endl;

  gStyle->SetOptStat();
  
  Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)NormedMult->FindObject("stats");
  StatBox1->SetName("StatBox1");
  StatBox1->SetY1NDC(0.95);
  StatBox1->SetY2NDC(0.65);
  StatBox1->SetX1NDC(1.0);
  StatBox1->SetX2NDC(0.70);
  StatBox1->SetTextColor(kRed);
  StatBox1->SetOptStat(0);
  gStyle->SetStatFontSize(1);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)NormedMult2->FindObject("stats");
  StatBox2->SetName("StatBox2");
  StatBox2->SetY1NDC(0.65);
  StatBox2->SetY2NDC(0.45);
  StatBox2->SetX1NDC(1.0);
  StatBox2->SetX2NDC(0.70);
  StatBox2->SetTextColor(kBlue);
  StatBox2->SetOptStat(0);
  /*
  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Mult3->FindObject("stats");
  StatBox3->SetName("StatBox3");
  StatBox3->SetY1NDC(0.45);
  StatBox3->SetY2NDC(0.25);
  StatBox3->SetX1NDC(1.0);
  StatBox3->SetX2NDC(0.70);
  StatBox3->SetTextColor(kMagenta);
  StatBox3->SetOptStat(0);
  */
  Canvas->Modified();

  //TLegend *legend1 = new TLegend (0.98, 0.55, 0.78, 0.7);
  TLegend *legend1 = new TLegend (0.28, 0.85, 0.08, 0.95);
  legend1->AddEntry(NormedMult,"Data Histogram","fel");
  legend1->AddEntry(KNOf,"KNO Scaling","l");
  legend1->AddEntry(KNOGf,"KNO-G Scaling","l");
  //legend1->AddEntry(Binomf,"Negative Binomial PDF","l");
  legend1->Draw();

  NormedMult->GetYaxis()->SetRangeUser(0, 1);

  Canvas->Print(outName, "pdf");
}

Double_t KNOFunc (Double_t *x, Double_t *par)
{
  double n = x[0];
  //double funct = par[0]*(1.895*n + 16.85*pow(n, 3) - 3.32*pow(n, 5) + 0.166*pow(n, 7))*exp(-3.04*n);
  double funct = (par[0]*n + par[1]*pow(n, 3) - par[2]*pow(n, 5) + par[3]*pow(n, 7))*exp(par[4]*n);

  return funct;
}

Double_t KNOGFunc (Double_t *x, Double_t *par)
{
  double n = x[0];
  double funct = -par[0]*exp(par[1]*n+par[2]*n*n);

  return funct;
}