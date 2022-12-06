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

TH1F *SlpTXHist1 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist4 = new TH1F("TX","X Slope",100,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist4 = new TH1F("TY","Y Slope",100,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist4 = new TH1F("T2","Space Angle",100,0,0.5);

TH1F *IPData1 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData2 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData3 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData4 = new TH1F("IP","Impact Parameter",50,0,10);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",100,0,100);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",100,0,100);
TH1F *Mult3 = new TH1F("Mlt","Multiplicity",100,0,100);
TH1F *Mult4 = new TH1F("Mlt","Multiplicity",100,0,100);

TH1F *VX1 = new TH1F("VX","Vertex X",100,10000,140000);
TH1F *VX2 = new TH1F("VX","Vertex X",100,10000,140000);
TH1F *VX3 = new TH1F("VX","Vertex X",100,10000,140000);
TH1F *VX4 = new TH1F("VX","Vertex X",100,10000,140000);

TH1F *VY1 = new TH1F("VY","Vertex Y",100,10000,110000);
TH1F *VY2 = new TH1F("VY","Vertex Y",100,10000,110000);
TH1F *VY3 = new TH1F("VY","Vertex Y",100,10000,110000);
TH1F *VY4 = new TH1F("VY","Vertex Y",100,10000,110000);

TH1F *VZ1 = new TH1F("VZ","Vertex Z",100,1000,7500);
TH1F *VZ2 = new TH1F("VZ","Vertex Z",100,1000,7500);
TH1F *VZ3 = new TH1F("VZ","Vertex Z",100,1000,7500);
TH1F *VZ4 = new TH1F("VZ","Vertex Z",100,1000,7500);

TH1F *DZ1 = new TH1F("DZ","Delta Z",100,-100,2200);
TH1F *DZ2 = new TH1F("DZ","Delta Z",100,-100,2200);
TH1F *DZ3 = new TH1F("DZ","Delta Z",100,-100,2200);
TH1F *DZ4 = new TH1F("DZ","Delta Z",100,-100,2200);

TH1F *SegX1 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX2 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX3 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX4 = new TH1F("SX","Segment X",100,0,140000);

TH1F *SegY1 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY2 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY3 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY4 = new TH1F("SY","Segment Y",100,0,110000);

TH1F *PNum1 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum2 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum3 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum4 = new TH1F("PN","Parent Number",5,0,5);

TH2F *VXY1 = new TH2F("VXY1","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY2 = new TH2F("VXY2","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY3 = new TH2F("VXY3","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY4 = new TH2F("VXY4","Vertex X vs Y",100,10000,90000,100,10000,90000);

TFile *Data1, *Data2, *Data3, *Data4;

float Data1VtxSize = 0, Data2VtxSize = 0, Data3VtxSize = 0, Data4VtxSize = 0;

void DataMCComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"DataMCComp.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD04.root");
  Data2 = TFile::Open("../Root/reco-bt-001-040.root");
  Data3 = TFile::Open("../Root/reco-bt-001-040_new_smearing.root");
  Data4 = TFile::Open("../Root/reco-bt-001-040_mt_new_smearing.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataTrk3 = (TTree*)Data3->Get("TRK");
  TTree *treeDataTrk4 = (TTree*)Data4->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  TTree *treeDataVtx3 = (TTree*)Data3->Get("VTX");
  TTree *treeDataVtx4 = (TTree*)Data4->Get("VTX");
  
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
    
    //double TX = slpTX->GetValue();
    //double TY = slpTY->GetValue();

    //beamTXTot += TX;
    //beamTYTot += TY;

    SlpTXHist1->Fill(TX);
    SlpTYHist1->Fill(TY);
    //SlpT2Hist1->Fill(slpT2->GetValue());
    SlpT2Hist1->Fill(sqrt(TX*TX+TY*TY));
    IPData1->Fill(IP->GetValue());
    
  }
  
  //float beamTXAvg = beamTXTot/treeDataTrk1->GetEntriesFast();
  //float beamTYAvg = beamTYTot/treeDataTrk1->GetEntriesFast();
  
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

    //double TX = slpTX->GetValue();
    //double TY = slpTY->GetValue();

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

    //double TX = slpTX->GetValue() + beamTXAvg;
    //double TY = slpTY->GetValue() + beamTYAvg;

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

    //double TX = slpTX->GetValue() + beamTXAvg;
    //double TY = slpTY->GetValue() + beamTYAvg;

    SlpTXHist4->Fill(TX);
    SlpTYHist4->Fill(TY);
    //SlpT2Hist4->Fill(slpT2->GetValue());
    SlpT2Hist4->Fill(sqrt(TX*TX+TY*TY));
    IPData4->Fill(IP->GetValue());
  }
  
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
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

      //DataX1[i] = VX->GetValue();
      //DataY1[i] = VY->GetValue();

      Data1VtxSize++;
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

    PNum2->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult2->Fill(mult->GetValue());
      VX2->Fill(VX->GetValue());
      VY2->Fill(VY->GetValue());
      VZ2->Fill(VZ->GetValue());

      //VXY2->Fill(VX->GetValue(), VY->GetValue());

      //DataX2[i] = VX->GetValue();
      //DataY2[i] = VY->GetValue();

      Data2VtxSize++;
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

    PNum3->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult3->Fill(mult->GetValue());
      VX3->Fill(VX->GetValue());
      VY3->Fill(VY->GetValue());
      VZ3->Fill(VZ->GetValue());
      
      
      //VXY3->Fill(VX->GetValue(), VY->GetValue());

      //DataX3[i] = VX->GetValue();
      //DataY3[i] = VY->GetValue();

      Data3VtxSize++;
    }
  }

  for (int i = 0; i < treeDataVtx4->GetEntriesFast(); i++)
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

      //DataX4[i] = VX->GetValue();
      //DataY4[i] = VY->GetValue();

      Data4VtxSize++;
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
  
  /*
  TGraph *DataXY1 = new TGraph(Data1VtxSize, DataX1, DataY1);
  TGraph *DataXY2 = new TGraph(Data2VtxSize, DataX2, DataY2);
  TGraph *DataXY3 = new TGraph(Data3VtxSize, DataX3, DataY3);
  TGraph *DataXY4 = new TGraph(Data4VtxSize, DataX4, DataY4);
  */

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

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 650000);
  HistDraw(SlpTXHist1, SlpTXHist2, SlpTXHist3, SlpTXHist4);
  Canvas->Print( outNameStart, "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 650000);
  HistDraw(SlpTYHist1, SlpTYHist2, SlpTYHist3, SlpTYHist4);
  Canvas->Print( outName, "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 520000);
  HistDraw(SlpT2Hist1, SlpT2Hist2, SlpT2Hist3, SlpT2Hist4);
  Canvas->Print( outName, "pdf");

  IPData1->GetYaxis()->SetRangeUser(0, 1400000);
  HistDraw(IPData1, IPData2, IPData3, IPData4);
  Canvas->Print( outName, "pdf");

  Mult1->GetYaxis()->SetRangeUser(0, 48000);
  HistDraw(Mult1, Mult2, Mult3, Mult4);
  Canvas->Print( outName, "pdf");

  VX1->GetYaxis()->SetRangeUser(0, 6800);
  HistDraw(VX1, VX2, VX3, VX4);
  Canvas->Print( outName, "pdf");

  VY1->GetYaxis()->SetRangeUser(0, 6800);
  HistDraw(VY1, VY2, VY3, VY4);
  Canvas->Print( outName, "pdf");

  VZ1->GetYaxis()->SetRangeUser(0, 40000);
  HistDraw(VZ1, VZ2, VZ3, VZ4);
  Canvas->Print( outName, "pdf");

  PNum1->GetYaxis()->SetRangeUser(0, 320000);
  HistDraw(PNum1, PNum2, PNum3, PNum4);
  Canvas->Print( outName, "pdf");

  DZ1->GetYaxis()->SetRangeUser(0, 220000);
  HistDraw(DZ1, DZ2, DZ3, DZ4);
  Canvas->Print( outName, "pdf");

  SegX1->GetYaxis()->SetRangeUser(0, 120000);
  HistDraw(SegX1, SegX2, SegX3, SegX4);
  Canvas->Print( outName, "pdf");

  SegY1->GetYaxis()->SetRangeUser(0, 120000);
  HistDraw(SegY1, SegY2, SegY3, SegY4);
  Canvas->Print( outNameEnd, "pdf");
  /*
  DataXY1->SetTitle("PD01 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY1->GetXaxis()->SetLimits(10000, 120000);
  DataXY1->GetHistogram()->SetMaximum(90000);
  DataXY1->GetHistogram()->SetMinimum(10000);
  DataXY1->Draw("AP");

  Canvas->Print( "DataMCComp.pdf", "pdf");

  DataXY2->SetTitle("PD01 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY2->GetXaxis()->SetLimits(10000, 120000);
  DataXY2->GetHistogram()->SetMaximum(90000);
  DataXY2->GetHistogram()->SetMinimum(10000);
  DataXY2->Draw("AP");

  Canvas->Print( "DataMCComp.pdf", "pdf");

  DataXY3->SetTitle("PD05 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY3->GetXaxis()->SetLimits(10000, 120000);
  DataXY3->GetHistogram()->SetMaximum(90000);
  DataXY3->GetHistogram()->SetMinimum(10000);
  DataXY3->Draw("AP");

  Canvas->Print( "DataMCComp.pdf", "pdf");

  DataXY4->SetTitle("PD06 Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY4->GetXaxis()->SetLimits(10000, 120000);
  DataXY4->GetHistogram()->SetMaximum(90000);
  DataXY4->GetHistogram()->SetMinimum(10000);
  DataXY4->Draw("AP");
  
  Canvas->Print( "DataMCComp.pdf)", "pdf");
  */
  
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD04");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("reco-bt-001-040");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kTeal+10); hist3->SetLineStyle(1); hist3->SetLineWidth(2); hist3->SetFillColorAlpha(kTeal+10, 0.3);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("reco-bt-001-040_new_smearing");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kTeal+10);
  StatBox3->Draw();

  hist4->Draw("SAMES HIST"); hist4->SetLineColor(kBlack); hist4->SetLineStyle(1); hist4->SetLineWidth(2); hist4->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("reco-bt-001-040_mt_new_smearing");
  StatBox4->SetY1NDC(0.3);
  StatBox4->SetY2NDC(0.1);
  StatBox4->SetTextColor(kBlack);
  StatBox4->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.8, 0.32, 0.95);
  legend->AddEntry(hist1,"PD04","f");
  legend->AddEntry(hist2,"reco-bt-001-040","f");
  legend->AddEntry(hist3,"reco-bt-001-040_new_smearing","f");
  legend->AddEntry(hist4,"reco-bt-001-040_mt_new_smearing","f");
  legend->Draw();
  
}