#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",35,5,40);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",35,5,40);
TH1F *Mult3 = new TH1F("Mlt","Multiplicity",35,5,40);

TFile *Data1, *Data2, *Data3;

float Data1VtxSize = 0, Data2VtxSize = 0, Data3VtxSize = 0;

int subV = 0;

void MultComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"MultCompPerW.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD05_p006.root");
  Data2 = TFile::Open("../Root/Geant4_p006.root");
  Data3 = TFile::Open("../Root/EPOS.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataTrk3 = (TTree*)Data3->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  TTree *treeDataVtx3 = (TTree*)Data3->Get("VTX");
  
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx1->GetLeaf("vx");
    TLeaf *VY = treeDataVtx1->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx1->GetLeaf("vz");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *vID = treeDataVtx1->GetLeaf("vID");
    TLeaf *sVol = treeDataVtx1->GetLeaf("sub_vol");
    TLeaf *w = treeDataVtx1->GetLeaf("flagw");

    if(PN->GetValue() > 0)
    {
      if (/*sVol->GetValue() == subV &&*/ w->GetValue() == 1)
      {
        Mult1->Fill(mult->GetValue());

        Data1VtxSize++;
      }
    }
  }
  
  for (int i = 0; i < treeDataVtx2->GetEntriesFast(); i++)
  {
    treeDataVtx2->GetEntry(i);

    TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx2->GetLeaf("vx");
    TLeaf *VY = treeDataVtx2->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx2->GetLeaf("vz");
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *vID = treeDataVtx2->GetLeaf("vID");
    TLeaf *sVol = treeDataVtx2->GetLeaf("sub_vol");
    TLeaf *w = treeDataVtx2->GetLeaf("flagw");

    if(PN->GetValue() > 0)
    {
      if (/*sVol->GetValue() == subV && */w->GetValue() == 1)
      {
        Mult2->Fill(mult->GetValue());

        Data2VtxSize++;
      }
    }
  }

  for (int i = 0; i < treeDataVtx3->GetEntriesFast(); i++)
  {
    treeDataVtx3->GetEntry(i);

    TLeaf *mult = treeDataVtx3->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx3->GetLeaf("vx");
    TLeaf *VY = treeDataVtx3->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx3->GetLeaf("vz");
    TLeaf *PN = treeDataVtx3->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *vID = treeDataVtx3->GetLeaf("vID");
    TLeaf *sVol = treeDataVtx3->GetLeaf("sub_vol");
    TLeaf *w = treeDataVtx3->GetLeaf("flagw");

    if(PN->GetValue() > 0)
    {
      if (/*sVol->GetValue() == subV && */w->GetValue() == 1)
      {
        Mult3->Fill(mult->GetValue());

        Data3VtxSize++;
      }
    }
  }

  float r12 = Data1VtxSize/Data2VtxSize;
  float r13 = Data1VtxSize/Data3VtxSize;

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  Mult2->Scale(r12);
  Mult3->Scale(r13);

  //Mult1->GetYaxis()->SetRangeUser(0, 1800);
  HistDraw(Mult1, Mult2, Mult3);
  Canvas->Print( outName, "pdf");

}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3)
{

  hist1->Draw("HIST E1"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD05");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("Geant4");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kBlack); hist3->SetLineStyle(1); hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("Pythia");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kBlack);
  StatBox3->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"PD05","f");
  legend->AddEntry(hist2,"Geant4","f");
  legend->AddEntry(hist3,"Pythia","f");
  legend->Draw();
}