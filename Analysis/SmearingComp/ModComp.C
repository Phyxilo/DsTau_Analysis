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

void HistDraw(TH1F *hist1, TH1F *hist2);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHist1 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX","X Slope",100,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY","Y Slope",100,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("T2","Space Angle",100,0,0.5);

TH1F *IPData1 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData2 = new TH1F("IP","Impact Parameter",50,0,10);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",100,0,100);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",100,0,100);

TH1F *VX1 = new TH1F("VX","Vertex X",100,0,140000);
TH1F *VX2 = new TH1F("VX","Vertex X",100,0,140000);

TH1F *VY1 = new TH1F("VY","Vertex Y",100,0,110000);
TH1F *VY2 = new TH1F("VY","Vertex Y",100,0,110000);

TH1F *VZ1 = new TH1F("VZ","Vertex Z",100,0,6500);
TH1F *VZ2 = new TH1F("VZ","Vertex Z",100,0,6500);

TH1F *DZ1 = new TH1F("DZ","Delta Z",100,-100,2000);
TH1F *DZ2 = new TH1F("DZ","Delta Z",100,-100,2000);

TH1F *SegX1 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX2 = new TH1F("SX","Segment X",100,0,140000);

TH1F *SegY1 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY2 = new TH1F("SY","Segment Y",100,0,110000);

TH1F *PNum1 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum2 = new TH1F("PN","Parent Number",5,0,5);

TFile *Data1, *Data2;

float Data1VtxSize, Data2VtxSize;

void ModComp()
{
  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"SmearingComp.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);
  
  Data1 = TFile::Open("../Root/reco-bt-001-040_new_smearing.root");
  Data2 = TFile::Open("../Root/reco-bt-001-040_mt_new_smearing.root");

  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  Data1VtxSize = treeDataVtx1->GetEntriesFast();
  Data2VtxSize = treeDataVtx2->GetEntriesFast();

  float DataX1[(int)Data1VtxSize], DataY1[(int)Data1VtxSize];
  float DataX2[(int)Data2VtxSize], DataY2[(int)Data2VtxSize];

  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);
    
    TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
    //TLeaf *slpT2 = treeDataTrk1->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk1->GetLeaf("ip_to_1ry_using_1stseg");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();
    
    SlpTXHist1->Fill(TX);
    SlpTYHist1->Fill(TY);
    //SlpT2Hist1->Fill(slpT2->GetValue());
    SlpT2Hist1->Fill(sqrt(TX*TX+TY*TY));
    IPData1->Fill(IP->GetValue());
    
  }
  
  for (int i = 0; i < treeDataTrk2->GetEntriesFast(); i++)
  {
    treeDataTrk2->GetEntry(i);

    TLeaf *slpTX = treeDataTrk2->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk2->GetLeaf("ty");
    //TLeaf *slpT2 = treeDataTrk2->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk2->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk2->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk2->GetLeaf("ip_to_1ry_using_1stseg");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    SlpTXHist2->Fill(TX);
    SlpTYHist2->Fill(TY);
    //SlpT2Hist2->Fill(slpT2->GetValue());
    SlpT2Hist2->Fill(sqrt(TX*TX+TY*TY));
    IPData2->Fill(IP->GetValue());
  }

  for (int i = 0; i < Data1VtxSize; i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx1->GetLeaf("vx");
    TLeaf *VY = treeDataVtx1->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx1->GetLeaf("vz");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

    PNum1->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult1->Fill(mult->GetValue());
      VX1->Fill(VX->GetValue());
      VY1->Fill(VY->GetValue());
      VZ1->Fill(VZ->GetValue());

      //VXY1->Fill(VX->GetValue(), VY->GetValue());

      DataX1[i] = VX->GetValue();
      DataY1[i] = VY->GetValue();
    }
  }

  for (int i = 0; i < Data2VtxSize; i++)
  {
    treeDataVtx2->GetEntry(i);

    TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx2->GetLeaf("vx");
    TLeaf *VY = treeDataVtx2->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx2->GetLeaf("vz");
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");

    PNum2->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult2->Fill(mult->GetValue());
      VX2->Fill(VX->GetValue());
      VY2->Fill(VY->GetValue());
      VZ2->Fill(VZ->GetValue());

      //VXY2->Fill(VX->GetValue(), VY->GetValue());

      DataX2[i] = VX->GetValue();
      DataY2[i] = VY->GetValue();
    }
  }

  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);

    TLeaf *dz = treeDataTrk1->GetLeaf("dz");
    TLeaf *segX = treeDataTrk1->GetLeaf("seg_x");
    TLeaf *segY = treeDataTrk1->GetLeaf("seg_y");
    TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");

    if (PN->GetValue() == 1)
    {
      DZ1->Fill(dz->GetValue());
      SegX1->Fill(segX->GetValue());
      SegY1->Fill(segY->GetValue());
    }
  }

  for (int i = 0; i < treeDataTrk2->GetEntriesFast(); i++)
  {
    treeDataTrk2->GetEntry(i);

    TLeaf *dz = treeDataTrk2->GetLeaf("dz");
    TLeaf *segX = treeDataTrk2->GetLeaf("seg_x");
    TLeaf *segY = treeDataTrk2->GetLeaf("seg_y");
    TLeaf *PN = treeDataTrk2->GetLeaf("n_1ry_parent_dmin_cut");

    if (PN->GetValue() == 1)
    {
      DZ2->Fill(dz->GetValue());
      SegX2->Fill(segX->GetValue());
      SegY2->Fill(segY->GetValue());
    }
  }

  TGraph *DataXY1 = new TGraph(Data1VtxSize, DataX1, DataY1);
  TGraph *DataXY2 = new TGraph(Data2VtxSize, DataX2, DataY2);

  float r12 = Data1VtxSize/Data2VtxSize;

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  SlpTXHist2->Scale(r12);

  SlpTYHist2->Scale(r12);

  SlpT2Hist2->Scale(r12);

  IPData2->Scale(r12);

  Mult2->Scale(r12);

  VX2->Scale(r12);

  VY2->Scale(r12);

  VZ2->Scale(r12);

  DZ2->Scale(r12);

  SegX2->Scale(r12);

  SegY2->Scale(r12);

  PNum2->Scale(r12);

  //SlpTXHist1->GetYaxis()->SetRangeUser(0, 400000);
  HistDraw(SlpTXHist1, SlpTXHist2);
  Canvas->Print( outNameStart, "pdf");

  //SlpTYHist1->GetYaxis()->SetRangeUser(0, 400000);
  HistDraw(SlpTYHist1, SlpTYHist2);
  Canvas->Print( outName, "pdf");

  //SlpT2Hist1->GetYaxis()->SetRangeUser(0, 300000);
  HistDraw(SlpT2Hist1, SlpT2Hist2);
  Canvas->Print( outName, "pdf");

  //IPData1->GetYaxis()->SetRangeUser(0, 800000);
  HistDraw(IPData1, IPData2);
  Canvas->Print( outName, "pdf");

  //Mult1->GetYaxis()->SetRangeUser(0, 18000);
  HistDraw(Mult1, Mult2);
  Canvas->Print( outName, "pdf");

  //VX1->GetYaxis()->SetRangeUser(0, 4400);
  HistDraw(VX1, VX2);
  Canvas->Print( outName, "pdf");

  //VY1->GetYaxis()->SetRangeUser(0, 4400);
  HistDraw(VY1, VY2);
  Canvas->Print( outName, "pdf");

  //VZ1->GetYaxis()->SetRangeUser(0, 18000);
  HistDraw(VZ1, VZ2);
  Canvas->Print( outName, "pdf");

  //PNum1->GetYaxis()->SetRangeUser(0, 300000);
  HistDraw(PNum1, PNum2);
  Canvas->Print( outName, "pdf");

  //DZ1->GetYaxis()->SetRangeUser(0, 160000);
  HistDraw(DZ1, DZ2);
  Canvas->Print( outName, "pdf");

  //SegX1->GetYaxis()->SetRangeUser(0, 80000);
  HistDraw(SegX1, SegX2);
  Canvas->Print( outName, "pdf");

  //SegY1->GetYaxis()->SetRangeUser(0, 80000);
  HistDraw(SegY1, SegY2);

  Canvas->Print( outNameEnd, "pdf");
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(3); hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD01");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(3); hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("PD04");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"reco-bt-001-040","f");
  legend->AddEntry(hist2,"reco-bt-001-040_mt","f");
  legend->Draw();
  
}