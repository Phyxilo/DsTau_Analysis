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

Double_t KNOGFunc1 (Double_t *x, Double_t *par);
Double_t KNOGFunc2 (Double_t *x, Double_t *par);
Double_t MultKNOGFunc (Double_t *x, Double_t *par);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Multip = new TH1F("","",50,0,50);
TH1F *NormedMult = new TH1F("","",60,0.,3);

TFile *Data1;

float Data1VtxSize;
double mean = 1;

void FitComp4()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FitComp4.pdf");
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

  TF1 *MultKNOG = new TF1("MultKNOGFunc",MultKNOGFunc,12,50,3);

  Multip->Fit("MultKNOGFunc", "R");
  TF1 *MultipKNOGf = Multip->GetFunction("MultKNOGFunc");

  double fitMean = MultipKNOGf->Mean(0, 50);

  //double fitMean = 15.9177;
  //double fitMean = 15.9177 - 0.133;
  //double fitMean = 15.9177 - 1.889;

  float multMean = Multip->GetMean();
  int bin = Multip->GetXaxis()->FindBin(multMean);
  float meanPeak = Multip->GetBinContent(bin);

  int scaleFac = 0;

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
        //NormedMult->Fill((mult->GetValue()-0.5)/(fitMean-0.5));
        //NormedMult->Fill((mult->GetValue()-0.133*15.9177)/(fitMean));
        NormedMult->Fill((mult->GetValue()-2)/(fitMean));
        //NormedMult->Fill((mult->GetValue()-1.889)/(fitMean));

        scaleFac++;
      }
    }
  }

  mean = NormedMult->GetMean();

  //NormedMult->Scale((fitMean-0.5)/NormedMult->Integral());
  //NormedMult->Scale((fitMean)/NormedMult->Integral());
  NormedMult->Scale((fitMean)/scaleFac);
  NormedMult->SetLineColor(kBlack);
  NormedMult->SetXTitle("z");
  NormedMult->SetYTitle("#Psi(z)");
  //NormedMult->Scale(0.90);
  NormedMult->Draw("E1");

  TF1 *KNOG1 = new TF1("KNOGFunc1",KNOGFunc1,0.72,3,3);
  TF1 *KNOG2 = new TF1("KNOGFunc2",KNOGFunc2,0.72,3,3);

  KNOG1->FixParameter(0, 1.19);
  KNOG1->FixParameter(1, 0.62);
  KNOG1->FixParameter(2, 0.66);
  
  KNOG2->FixParameter(0, 1.25);
  KNOG2->FixParameter(1, 0.62);
  KNOG2->FixParameter(2, 0.14);
  /*
  KNOG->FixParameter(0, 1.638);
  KNOG->FixParameter(1, 0.121);
  KNOG->FixParameter(2, 4.25);
  */

  TH1* NormedMult2 = new TH1F(*NormedMult);

  NormedMult->Fit("KNOGFunc1", "R", "");
  TF1 *KNOG1f = NormedMult->GetFunction("KNOGFunc1");

  NormedMult2->Fit("KNOGFunc2", "R", "SAMES");
  TF1 *KNOG2f = NormedMult2->GetFunction("KNOGFunc2");
  KNOG2f->SetLineColor(kBlue);

  //cout << f1->GetChisquare() << endl;
  cout << "Histogram Mean: " << multMean << endl;
  cout << "Fit Mean: " << fitMean << endl;

  gStyle->SetOptStat();
  
  Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)NormedMult->FindObject("stats");
  StatBox1->SetName("StatBox1");
  StatBox1->SetY1NDC(0.95);
  StatBox1->SetY2NDC(0.75);
  StatBox1->SetX1NDC(1.0);
  StatBox1->SetX2NDC(0.70);
  StatBox1->SetTextColor(kRed);
  StatBox1->SetOptStat(0);
  gStyle->SetStatFontSize(1);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)NormedMult2->FindObject("stats");
  StatBox2->SetName("StatBox2");
  StatBox2->SetY1NDC(0.75);
  StatBox2->SetY2NDC(0.55);
  StatBox2->SetX1NDC(1.0);
  StatBox2->SetX2NDC(0.70);
  StatBox2->SetTextColor(kBlue);
  StatBox2->SetOptStat(0);

  Canvas->Modified();

  TLegend *legend1 = new TLegend (0.28, 0.85, 0.08, 0.95);
  legend1->AddEntry(NormedMult,"Data Histogram","fel");
  legend1->AddEntry(KNOG1f,"KNO-G Scaling (#Psi_{1})","l");
  legend1->AddEntry(KNOG2f,"KNO-G Scaling (#Psi_{2})","l");
  legend1->Draw();

  NormedMult->GetYaxis()->SetRangeUser(0, 1);

  Canvas->Print(outName, "pdf");
}

Double_t KNOGFunc1 (Double_t *x, Double_t *par)
{
  double n = x[0];
  //double funct = par[0]*pow((n+par[4])/par[3], par[1])*exp(par[2]*((n+par[4])/par[3])*((n+par[4])/par[3]))/(par[3]);
  
  double fitMean = 15.9177;
  double meanRatio = (fitMean + par[3])/fitMean;
  //double avg_ne = (fitMean + par[3]);
  double ne = (n + par[3])/meanRatio;
  
  double funct = par[0]*pow(n, par[2])*exp(-par[1]*(n)*(n));
  //double funct = par[0]*pow(ne, par[1])*exp(par[2]*(ne)*(ne))/(meanRatio);

  return funct;
}

Double_t KNOGFunc2 (Double_t *x, Double_t *par)
{
  double n = x[0];
  
  double funct = par[0]*(n+par[2])*exp(-par[1]*(n+par[2])*(n+par[2]));

  return funct;
}
/*
Double_t KNOGFunc (Double_t *x, Double_t *par)
{
  double n = x[0];

  double funct = 1.06/(sqrt(2*M_PI)*par[1])+1/(n+par[2])*exp(-pow((log(n+par[2])-par[0]),2)/(2*par[1]*par[1]));

  return funct;
}
*/

Double_t MultKNOGFunc (Double_t *x, Double_t *par)
{
  double n = x[0];

  double funct = -par[0]*exp(par[1]*n+par[2]*n*n);

  return funct;
}
