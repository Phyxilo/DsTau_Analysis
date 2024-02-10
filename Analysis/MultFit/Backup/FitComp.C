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

TH1F *Mult1 = new TH1F("","",45,5,50);
//TH1F *Mult2 = new TH1F("Mlt","Multiplicity",50,5,55);

TH1F *MultEff = new TH1F("MltEff","Multiplicity Efficiency",45,5,50);

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

  for (int j = 0; j < 8; j++)
  {
    char dir [128];

    //Data1 = TFile::Open("/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p006.root");

    //if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
    //else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

    sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data1 = TFile::Open(dir);
    
    TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
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
        Mult1->Fill(mult->GetValue());
      }
    } 
  }

  FILE *effFile = fopen("MultEfficiency.dat", "r");
  for (int multInd = 0; multInd <= 50; multInd++)
  {
    float eff = 0;

    fscanf(effFile, "%8f", &eff);
    
    if (multInd >= 5)
    {
      
      if (/*multInd < 10*/ false)
      {
        MultEff->SetBinContent(multInd-4, 1);
      }
      else
      {
        if (eff == 0)
        {
          MultEff->SetBinContent(multInd-4, 1);
        }
        else
        {
          MultEff->SetBinContent(multInd-4, eff);
        }
      }

      //double err = Mult1->GetBinError(multInd) / eff;
      //Mult1->SetBinError(multInd, err);

    }

    //cout << eff << endl;
  }
  MultEff->Draw();
  Canvas->Print("MultEff.png", "png");

  gStyle->SetOptFit(1);
  gPad->Update();

  //Mult1->Divide(MultEff);

  mean = Mult1->GetMean();
  int bin = Mult1->GetXaxis()->FindBin(mean);
  float meanPeak = Mult1->GetBinContent(bin);

  //Mult1->Scale(mean/Mult1->Integral());
  Mult1->Scale(1/meanPeak);
  Mult1->SetLineColor(kBlack);
  Mult1->SetXTitle("Multiplicity");
  Mult1->SetYTitle("n_{s} / <n_{s}>");
  Mult1->Draw("E1");

  TH1* Mult2 = new TH1F(*Mult1);
  TH1* Mult3 = new TH1F(*Mult1);
  
  TF1 *KNO = new TF1("KNOFunc",KNOFunc,10,50,5);
  TF1 *KNOG = new TF1("KNOGFunc",KNOGFunc,10,50,3);
  TF1 *f1 = new TF1 ("bFit", "[0]*ROOT::Math::negative_binomial_pdf(x, [1], [2])", 10, 50);

  KNO->SetParameter(0, 1);
  KNOG->SetParameter(0, 1);
  f1->SetNpx(40);
  f1->SetParameter(0, 1);
  f1->SetParameter(1, 0.3);
  f1->SetParameter(2, 5);
  
  Mult1->Fit("KNOFunc", "R", "");
  TF1 *KNOf = Mult1->GetFunction("KNOFunc");
  //KNOf->Draw("SAME");

  Mult2->Fit("KNOGFunc", "R", "SAMES");
  TF1 *KNOGf = Mult2->GetFunction("KNOGFunc");
  KNOGf->SetLineColor(kBlue);
  
  Mult3->Fit("bFit", "R+", "SAMES");
  TF1 *Binomf = Mult3->GetFunction("bFit");
  Binomf->SetLineColor(kMagenta);
  Mult3->Draw("SAMES E1");
  //Binomf->Draw("SAMES");

  cout << f1->GetChisquare() << endl;

  gStyle->SetOptStat();
  
  Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Mult1->FindObject("stats");
  StatBox1->SetName("StatBox1");
  StatBox1->SetY1NDC(0.95);
  StatBox1->SetY2NDC(0.65);
  StatBox1->SetX1NDC(1.0);
  StatBox1->SetX2NDC(0.70);
  StatBox1->SetTextColor(kRed);
  StatBox1->SetOptStat(0);
  gStyle->SetStatFontSize(1);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Mult2->FindObject("stats");
  StatBox2->SetName("StatBox2");
  StatBox2->SetY1NDC(0.65);
  StatBox2->SetY2NDC(0.45);
  StatBox2->SetX1NDC(1.0);
  StatBox2->SetX2NDC(0.70);
  StatBox2->SetTextColor(kBlue);
  StatBox2->SetOptStat(0);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Mult3->FindObject("stats");
  StatBox3->SetName("StatBox3");
  StatBox3->SetY1NDC(0.45);
  StatBox3->SetY2NDC(0.25);
  StatBox3->SetX1NDC(1.0);
  StatBox3->SetX2NDC(0.70);
  StatBox3->SetTextColor(kMagenta);
  StatBox3->SetOptStat(0);

  /*
  TList *SB1list = StatBox1->GetListOfLines();
  SB1list->Remove(StatBox1->GetLineWith("Mean"));
  SB1list->Remove(StatBox1->GetLineWith("Entries"));
  Mult1->SetStats(0);
  */

  Canvas->Modified();

  //TLegend *legend1 = new TLegend (0.98, 0.55, 0.78, 0.7);
  TLegend *legend1 = new TLegend (0.28, 0.85, 0.08, 0.95);
  legend1->AddEntry(Mult1,"Data Histogram","fel");
  legend1->AddEntry(KNOf,"KNO Scaling","l");
  legend1->AddEntry(KNOGf,"KNO-G Scaling","l");
  legend1->AddEntry(Binomf,"Negative Binomial PDF","l");
  legend1->Draw();

  Mult1->GetYaxis()->SetRangeUser(0, 1.30);

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

Double_t KNOGFunc (Double_t *x, Double_t *par)
{
  double n = x[0]/mean;
  double funct = -par[0]*exp(par[1]*n+par[2]*n*n);

  return funct;
}