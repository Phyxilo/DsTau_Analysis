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

float MultCorection(int mult);
void ReadMultEffData();
double* DataEndPoints(TTree *data);
double DataMean(TTree *data);
int NormedAxis(int index, float scale, float inter);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Eff = new TH1F("","Efficiency",50,0,50);
TH1F *Multip = new TH1F("","Multiplicity",50,0,50);
TH1F *MultipEffCorrected = new TH1F("","Efficiency Corrected Multiplicity",50,0,50);
TH1F *NormedMult = new TH1F("","",44,0.,3);
TH1F *NormedMultEffCorrected = new TH1F("","Efficiency Corrected Normalized Multiplicity",44,0.,3);

TFile *Data1;

float Data1VtxSize;
double mean = 1;
float migCut = 15;
float multEffArr[50];

void FitComp6()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FitComp6.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  ReadMultEffData();

  for (int j = 0; j < 8; j++)
  {
    char dir [128];

    sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data1 = TFile::Open(dir);

    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");

    double *endArr = DataEndPoints(treeDataVtx1);
    double mean = DataMean(treeDataVtx1);

    Data1VtxSize = treeDataVtx1->GetEntriesFast();

    for (int i = 0; i < Data1VtxSize; i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *iMed = treeDataVtx1->GetLeaf("intMed");
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");

      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      //if(PN->GetValue() == 1 && iMed->GetValue() == 1 && areaBool && vz->GetValue() - endArr[0] > migCut && vz->GetValue() - endArr[1] < -migCut)
      if(PN->GetValue() == 1 && iMed->GetValue() == 1 && areaBool && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
      {
        Multip->Fill(MultCorection(mult->GetValue()));
        int Mlt = (int)MultCorection(mult->GetValue());

        float weigth = 1;

        if (Mlt > 0 && Mlt < 50)
        {
          weigth = 1/multEffArr[Mlt];
        }
        else
        {
          weigth = 1;
        }

        MultipEffCorrected->Fill(Mlt, weigth);
      }
    }
  }

  gStyle->SetOptFit(100);
  gPad->Update();

  for (int x = 0; x < 50; x++)
  {
    Eff->SetBinContent(x, multEffArr[x]);
  }

  TF1 *MultKNOG = new TF1("MultKNOGFunc",MultKNOGFunc,12,50,3);

  MultipEffCorrected->Fit("MultKNOGFunc", "R");
  TF1 *MultipKNOGf = MultipEffCorrected->GetFunction("MultKNOGFunc");

  double fitMean = MultipKNOGf->Mean(0, 50);

  float correctedMean = MultipEffCorrected->GetMean();

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
        //NormedMult->Fill((mult->GetValue()-2)/(fitMean));
        //NormedMult->Fill((mult->GetValue())/(fitMean));

        NormedMult->Fill(MultCorection(mult->GetValue())/correctedMean);
        int Mlt = (int)MultCorection(mult->GetValue());

        float weigth = 1;

        if (Mlt > 0 && Mlt < 50)
        {
          weigth = 1/multEffArr[Mlt];
        }
        else
        {
          weigth = 1;
        }

        NormedMultEffCorrected->Fill(Mlt/(correctedMean), weigth);
        
        //cout << weigth << endl;

        scaleFac++;
      }
    }
  }

  mean = NormedMult->GetMean();

  //NormedMult->Scale((fitMean)/scaleFac);
  NormedMult->Scale((correctedMean)/scaleFac);
  NormedMult->SetLineColor(kBlack);
  NormedMult->SetXTitle("z");
  NormedMult->SetYTitle("#Psi(z)");
  //NormedMult->Scale(0.90);
  NormedMult->Draw("E1");

  TF1 *KNOG1 = new TF1("KNOGFunc1",KNOGFunc1,0.5,3,3);
  TF1 *KNOG2 = new TF1("KNOGFunc2",KNOGFunc2,0.5,3,3);

  /*
  KNOG1->FixParameter(0, 1.19);
  KNOG1->FixParameter(1, 0.62);
  KNOG1->FixParameter(2, 0.66);
  
  KNOG2->FixParameter(0, 1.25);
  KNOG2->FixParameter(1, 0.62);
  KNOG2->FixParameter(2, 0.14);

  KNOG->FixParameter(0, 1.638);
  KNOG->FixParameter(1, 0.121);
  KNOG->FixParameter(2, 4.25);
  */

  TH1* NormedMult2 = new TH1F(*NormedMult);

  NormedMult->Fit("KNOGFunc1", "R", "");
  TF1 *KNOG1f = NormedMult->GetFunction("KNOGFunc1");

  //cout << f1->GetChisquare() << endl;
  cout << "Histogram Mean: " << multMean << endl;
  cout << "Corrected Mean: " << correctedMean << endl;
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

  Canvas->Modified();

  TLegend *legend1 = new TLegend (0.28, 0.85, 0.08, 0.95);
  legend1->AddEntry(NormedMult,"Data Histogram","fel");
  legend1->AddEntry(KNOG1f,"KNO-G Scaling (#Psi_{1})","l");
  legend1->Draw();

  NormedMult->GetYaxis()->SetRangeUser(0, 1);

  Canvas->Print(outNameStart, "pdf");

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  Eff->Draw();

  Canvas->Print(outNameEnd, "pdf");
}

Double_t KNOGFunc1 (Double_t *x, Double_t *par)
{
  double n = x[0];
  //double funct = par[0]*pow((n+par[4])/par[3], par[1])*exp(par[2]*((n+par[4])/par[3])*((n+par[4])/par[3]))/(par[3]);
  
  double fitMean = 15.9177;
  double meanRatio = (fitMean + par[3])/fitMean;
  //double ne = (n + par[3])/meanRatio;
  
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

Double_t MultKNOGFunc (Double_t *x, Double_t *par)
{
  double n = x[0];

  double funct = -par[0]*exp(par[1]*n+par[2]*n*n);

  return funct;
}

void ReadMultEffData()
{
  FILE *inFile = fopen("MultEfficiency_PLink.dat", "r");

  for(int i = 0; i < 50; i++)
  {
    fscanf(inFile, "%8f", &multEffArr[i]);
  }
  fclose(inFile);
}

double* DataEndPoints(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double endPoints[2];

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *intMedium = data->GetLeaf("intMed");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    bool areaBool = (area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29);

    if (parNum->GetValue() == 1 && areaBool)
    {
      if (intMedium->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  endPoints[0] = InterHist->FindFirstBinAbove(0);
  endPoints[1] = InterHist->FindLastBinAbove(0);

  delete InterHist;

  return endPoints;
}

double DataMean(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double mean;

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *w = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (w->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  mean = InterHist->GetMean();

  delete InterHist;

  return mean;
}

int NormedAxis(int index, float scale, float inter)
{
  float normedIndex = 0;

  float scaledIndex = ((float)index)/scale;
  normedIndex = (int)(scaledIndex/inter);

  //cout << "Index: " << index << ", Scaled: " << scaledIndex << ", Normed: " << normedIndex << endl;

  return normedIndex;
}

float MultCorection(int mult)
{
  float correctedMult = 0;

  //float a = 0.00146007;
  //float b = 0.124302;

  float a = 0.001568;
  float b = 0.07993;

  correctedMult = mult*(1 + (a*mult + b));

  return correctedMult;
}