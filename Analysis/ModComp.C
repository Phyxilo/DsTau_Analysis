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

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHist1 = new TH1F("TX_PD01","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX_PD04","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("TX_PD05","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist4 = new TH1F("TX_PD06","X Slope",100,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY_PD01","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY_PD04","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("TY_PD05","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist4 = new TH1F("TY_PD06","Y Slope",100,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2_PD01","Space Angle",100,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("T2_PD04","Space Angle",100,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("T2_PD05","Space Angle",100,0,0.5);
TH1F *SlpT2Hist4 = new TH1F("T2_PD06","Space Angle",100,0,0.5);

TH1F *IPData1 = new TH1F("IP_PD01","Impact Parameter",50,0,10);
TH1F *IPData2 = new TH1F("IP_PD04","Impact Parameter",50,0,10);
TH1F *IPData3 = new TH1F("IP_PD05","Impact Parameter",50,0,10);
TH1F *IPData4 = new TH1F("IP_PD06","Impact Parameter",50,0,10);

TH1F *Mult1 = new TH1F("Mlt_PD01","Multiplicity",100,0,100);
TH1F *Mult2 = new TH1F("Mlt_PD04","Multiplicity",100,0,100);
TH1F *Mult3 = new TH1F("Mlt_PD05","Multiplicity",100,0,100);
TH1F *Mult4 = new TH1F("Mlt_PD06","Multiplicity",100,0,100);

TH1F *VX1 = new TH1F("VX_PD01","Vertex X",100,10000,140000);
TH1F *VX2 = new TH1F("VX_PD04","Vertex X",100,10000,140000);
TH1F *VX3 = new TH1F("VX_PD05","Vertex X",100,10000,140000);
TH1F *VX4 = new TH1F("VX_PD06","Vertex X",100,10000,140000);

TH1F *VY1 = new TH1F("VY_PD01","Vertex Y",100,10000,110000);
TH1F *VY2 = new TH1F("VY_PD04","Vertex Y",100,10000,110000);
TH1F *VY3 = new TH1F("VY_PD05","Vertex Y",100,10000,110000);
TH1F *VY4 = new TH1F("VY_PD06","Vertex Y",100,10000,110000);

TH1F *VZ1 = new TH1F("VZ_PD01","Vertex Z",100,1000,6500);
TH1F *VZ2 = new TH1F("VZ_PD04","Vertex Z",100,1000,6500);
TH1F *VZ3 = new TH1F("VZ_PD05","Vertex Z",100,1000,6500);
TH1F *VZ4 = new TH1F("VZ_PD06","Vertex Z",100,1000,6500);

TH1F *DZ1 = new TH1F("DZ_PD01","Delta Z",100,-100,2000);
TH1F *DZ2 = new TH1F("DZ_PD04","Delta Z",100,-100,2000);
TH1F *DZ3 = new TH1F("DZ_PD05","Delta Z",100,-100,2000);
TH1F *DZ4 = new TH1F("DZ_PD06","Delta Z",100,-100,2000);

TH1F *SegX1 = new TH1F("SX_PD01","Segment X",100,0,140000);
TH1F *SegX2 = new TH1F("SX_PD04","Segment X",100,0,140000);
TH1F *SegX3 = new TH1F("SX_PD05","Segment X",100,0,140000);
TH1F *SegX4 = new TH1F("SX_PD06","Segment X",100,0,140000);

TH1F *SegY1 = new TH1F("SY_PD01","Segment Y",100,0,110000);
TH1F *SegY2 = new TH1F("SY_PD04","Segment Y",100,0,110000);
TH1F *SegY3 = new TH1F("SY_PD05","Segment Y",100,0,110000);
TH1F *SegY4 = new TH1F("SY_PD06","Segment Y",100,0,110000);

TH1F *PNum1 = new TH1F("PN_PD01","Parent Number",5,0,5);
TH1F *PNum2 = new TH1F("PN_PD04","Parent Number",5,0,5);
TH1F *PNum3 = new TH1F("PN_PD05","Parent Number",5,0,5);
TH1F *PNum4 = new TH1F("PN_PD06","Parent Number",5,0,5);

TH2F *VXY1 = new TH2F("VXY1","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY2 = new TH2F("VXY2","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY3 = new TH2F("VXY3","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY4 = new TH2F("VXY4","Vertex X vs Y",100,10000,90000,100,10000,90000);

TFile *Data1, *Data2, *Data3, *Data4;

float Data1VtxSize, Data2VtxSize, Data3VtxSize, Data4VtxSize;

void ModComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);
  
  Data1 = TFile::Open("PD01Full.root");
  Data2 = TFile::Open("PD04Full.root");
  Data3 = TFile::Open("PD05Full.root");
  Data4 = TFile::Open("PD06Full.root");

  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataTrk3 = (TTree*)Data3->Get("TRK");
  TTree *treeDataTrk4 = (TTree*)Data4->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  TTree *treeDataVtx3 = (TTree*)Data3->Get("VTX");
  TTree *treeDataVtx4 = (TTree*)Data4->Get("VTX");

  Data1VtxSize = treeDataVtx1->GetEntriesFast();
  Data2VtxSize = treeDataVtx2->GetEntriesFast();
  Data3VtxSize = treeDataVtx3->GetEntriesFast();
  Data4VtxSize = treeDataVtx4->GetEntriesFast();

  float DataX1[(int)Data1VtxSize], DataY1[(int)Data1VtxSize];
  float DataX2[(int)Data2VtxSize], DataY2[(int)Data2VtxSize];
  float DataX3[(int)Data3VtxSize], DataY3[(int)Data3VtxSize];
  float DataX4[(int)Data4VtxSize], DataY4[(int)Data4VtxSize];

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

  for (int i = 0; i < treeDataTrk3->GetEntriesFast(); i++)
  {
    treeDataTrk3->GetEntry(i);

    TLeaf *slpTX = treeDataTrk3->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk3->GetLeaf("ty");
    //TLeaf *slpT2 = treeDataTrk3->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk3->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk3->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk3->GetLeaf("ip_to_1ry_using_1stseg");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    SlpTXHist3->Fill(TX);
    SlpTYHist3->Fill(TY);
    //SlpT2Hist3->Fill(slpT2->GetValue());
    SlpT2Hist3->Fill(sqrt(TX*TX+TY*TY));
    IPData3->Fill(IP->GetValue());
  }

  for (int i = 0; i < treeDataTrk4->GetEntriesFast(); i++)
  {
    treeDataTrk4->GetEntry(i);

    TLeaf *slpTX = treeDataTrk4->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk4->GetLeaf("ty");
    //TLeaf *slpT2 = treeDataTrk4->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk4->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk4->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk4->GetLeaf("ip_to_1ry_using_1stseg");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    SlpTXHist4->Fill(TX);
    SlpTYHist4->Fill(TY);
    //SlpT2Hist4->Fill(slpT2->GetValue());
    SlpT2Hist4->Fill(sqrt(TX*TX+TY*TY));
    IPData4->Fill(IP->GetValue());
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

  for (int i = 0; i < Data3VtxSize; i++)
  {
    treeDataVtx3->GetEntry(i);

    TLeaf *mult = treeDataVtx3->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx3->GetLeaf("vx");
    TLeaf *VY = treeDataVtx3->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx3->GetLeaf("vz");
    TLeaf *PN = treeDataVtx3->GetLeaf("n_1ry_parent_dmin_cut");

    PNum3->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult3->Fill(mult->GetValue());
      VX3->Fill(VX->GetValue());
      VY3->Fill(VY->GetValue());
      VZ3->Fill(VZ->GetValue());
      
      
      //VXY3->Fill(VX->GetValue(), VY->GetValue());

      DataX3[i] = VX->GetValue();
      DataY3[i] = VY->GetValue();
    }
  }

  for (int i = 0; i < Data4VtxSize; i++)
  {
    treeDataVtx4->GetEntry(i);

    TLeaf *mult = treeDataVtx4->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx4->GetLeaf("vx");
    TLeaf *VY = treeDataVtx4->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx4->GetLeaf("vz");
    TLeaf *PN = treeDataVtx4->GetLeaf("n_1ry_parent_dmin_cut");

    PNum4->Fill(PN->GetValue());

    if (PN->GetValue() == 1)
    {
      Mult4->Fill(mult->GetValue());
      VX4->Fill(VX->GetValue());
      VY4->Fill(VY->GetValue());
      VZ4->Fill(VZ->GetValue());

      //VXY4->Fill(VX->GetValue(), VY->GetValue());

      DataX4[i] = VX->GetValue();
      DataY4[i] = VY->GetValue();
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

  for (int i = 0; i < treeDataTrk3->GetEntriesFast(); i++)
  {
    treeDataTrk3->GetEntry(i);

    TLeaf *dz = treeDataTrk3->GetLeaf("dz");
    TLeaf *segX = treeDataTrk3->GetLeaf("seg_x");
    TLeaf *segY = treeDataTrk3->GetLeaf("seg_y");
    TLeaf *PN = treeDataTrk3->GetLeaf("n_1ry_parent_dmin_cut");

    if (PN->GetValue() == 1)
    {
      DZ3->Fill(dz->GetValue());
      SegX3->Fill(segX->GetValue());
      SegY3->Fill(segY->GetValue());
    }
  }

  for (int i = 0; i < treeDataTrk4->GetEntriesFast(); i++)
  {
    treeDataTrk4->GetEntry(i);

    TLeaf *dz = treeDataTrk4->GetLeaf("dz");
    TLeaf *segX = treeDataTrk4->GetLeaf("seg_x");
    TLeaf *segY = treeDataTrk4->GetLeaf("seg_y");
    TLeaf *PN = treeDataTrk4->GetLeaf("n_1ry_parent_dmin_cut");

    if (PN->GetValue() == 1)
    {
      DZ4->Fill(dz->GetValue());
      SegX4->Fill(segX->GetValue());
      SegY4->Fill(segY->GetValue());
    }
  }
  
  TGraph *DataXY1 = new TGraph(Data1VtxSize, DataX1, DataY1);
  TGraph *DataXY2 = new TGraph(Data2VtxSize, DataX2, DataY2);
  TGraph *DataXY3 = new TGraph(Data3VtxSize, DataX3, DataY3);
  TGraph *DataXY4 = new TGraph(Data4VtxSize, DataX4, DataY4);

  float r12 = Data1VtxSize/Data2VtxSize;
  float r13 = Data1VtxSize/Data3VtxSize;
  float r14 = Data1VtxSize/Data4VtxSize;

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  SlpTXHist2->Scale(r12);
  SlpTXHist3->Scale(r13);
  SlpTXHist4->Scale(r14);

  SlpTYHist2->Scale(r12);
  SlpTYHist3->Scale(r13);
  SlpTYHist4->Scale(r14);

  SlpT2Hist2->Scale(r12);
  SlpT2Hist3->Scale(r13);
  SlpT2Hist4->Scale(r14);

  IPData2->Scale(r12);
  IPData3->Scale(r13);
  IPData4->Scale(r14);

  Mult2->Scale(r12);
  Mult3->Scale(r13);
  Mult4->Scale(r14);

  VX2->Scale(r12);
  VX3->Scale(r13);
  VX4->Scale(r14);

  VY2->Scale(r12);
  VY3->Scale(r13);
  VY4->Scale(r14);

  VZ2->Scale(r12);
  VZ3->Scale(r13);
  VZ4->Scale(r14);

  DZ2->Scale(r12);
  DZ3->Scale(r13);
  DZ4->Scale(r14);

  SegX2->Scale(r12);
  SegX3->Scale(r13);
  SegX4->Scale(r14);

  SegY2->Scale(r12);
  SegY3->Scale(r13);
  SegY4->Scale(r14);

  PNum2->Scale(r12);
  PNum3->Scale(r13);
  PNum4->Scale(r14);

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 400000);
  HistDraw(SlpTXHist1, SlpTXHist2, SlpTXHist3, SlpTXHist4);
  Canvas->Print( "ModCompHist.pdf(", "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 400000);
  HistDraw(SlpTYHist1, SlpTYHist2, SlpTYHist3, SlpTYHist4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 300000);
  HistDraw(SlpT2Hist1, SlpT2Hist2, SlpT2Hist3, SlpT2Hist4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  IPData1->GetYaxis()->SetRangeUser(0, 800000);
  HistDraw(IPData1, IPData2, IPData3, IPData4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  Mult1->GetYaxis()->SetRangeUser(0, 18000);
  HistDraw(Mult1, Mult2, Mult3, Mult4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  VX1->GetYaxis()->SetRangeUser(0, 4400);
  HistDraw(VX1, VX2, VX3, VX4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  VY1->GetYaxis()->SetRangeUser(0, 4400);
  HistDraw(VY1, VY2, VY3, VY4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  VZ1->GetYaxis()->SetRangeUser(0, 18000);
  HistDraw(VZ1, VZ2, VZ3, VZ4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  PNum1->GetYaxis()->SetRangeUser(0, 300000);
  HistDraw(PNum1, PNum2, PNum3, PNum4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  DZ1->GetYaxis()->SetRangeUser(0, 160000);
  HistDraw(DZ1, DZ2, DZ3, DZ4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  SegX1->GetYaxis()->SetRangeUser(0, 80000);
  HistDraw(SegX1, SegX2, SegX3, SegX4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  SegY1->GetYaxis()->SetRangeUser(0, 80000);
  HistDraw(SegY1, SegY2, SegY3, SegY4);
  Canvas->Print( "ModCompHist.pdf", "pdf");

  DataXY1->SetTitle("PD01 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY1->GetXaxis()->SetLimits(10000, 120000);
  DataXY1->GetHistogram()->SetMaximum(90000);
  DataXY1->GetHistogram()->SetMinimum(10000);
  DataXY1->Draw("AP");

  Canvas->Print( "ModCompHist.pdf", "pdf");

  DataXY2->SetTitle("PD04 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY2->GetXaxis()->SetLimits(10000, 120000);
  DataXY2->GetHistogram()->SetMaximum(90000);
  DataXY2->GetHistogram()->SetMinimum(10000);
  DataXY2->Draw("AP");

  Canvas->Print( "ModCompHist.pdf", "pdf");

  DataXY3->SetTitle("PD05 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY3->GetXaxis()->SetLimits(10000, 120000);
  DataXY3->GetHistogram()->SetMaximum(90000);
  DataXY3->GetHistogram()->SetMinimum(10000);
  DataXY3->Draw("AP");

  Canvas->Print( "ModCompHist.pdf", "pdf");

  DataXY4->SetTitle("PD06 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY4->GetXaxis()->SetLimits(10000, 120000);
  DataXY4->GetHistogram()->SetMaximum(90000);
  DataXY4->GetHistogram()->SetMinimum(10000);
  DataXY4->Draw("AP");

  Canvas->Print( "ModCompHist.pdf)", "pdf");
  
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4)
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
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kTeal+10); hist3->SetLineStyle(1); hist3->SetLineWidth(3); hist3->SetFillColorAlpha(kTeal+10, 0.3);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("PD05");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kTeal+10);
  StatBox3->Draw();

  hist4->Draw("SAMES HIST"); hist4->SetLineColor(kBlack); hist4->SetLineStyle(1); hist4->SetLineWidth(3); hist4->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("PD06");
  StatBox4->SetY1NDC(0.3);
  StatBox4->SetY2NDC(0.1);
  StatBox4->SetTextColor(kBlack);
  StatBox4->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.8, 0.32, 0.95);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(hist1,"PD01","f");
  legend->AddEntry(hist2,"PD04","f");
  legend->AddEntry(hist3,"PD05","f");
  legend->AddEntry(hist4,"PD06","f");
  legend->Draw();
  
}