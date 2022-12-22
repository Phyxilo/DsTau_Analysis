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

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHist1 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("TX","X Slope",100,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("TY","Y Slope",100,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("T2","Space Angle",100,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("T2","Space Angle",100,0,0.5);

TH1F *IPData1 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData2 = new TH1F("IP","Impact Parameter",50,0,10);
TH1F *IPData3 = new TH1F("IP","Impact Parameter",50,0,10);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",45,5,50);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",45,5,50);
TH1F *Mult3 = new TH1F("Mlt","Multiplicity",45,5,50);

TH1F *VX1 = new TH1F("VX","Vertex X",100,10000,140000);
TH1F *VX2 = new TH1F("VX","Vertex X",100,10000,140000);
TH1F *VX3 = new TH1F("VX","Vertex X",100,10000,140000);

TH1F *VY1 = new TH1F("VY","Vertex Y",100,10000,110000);
TH1F *VY2 = new TH1F("VY","Vertex Y",100,10000,110000);
TH1F *VY3 = new TH1F("VY","Vertex Y",100,10000,110000);

TH1F *VZ1 = new TH1F("VZ","Vertex Z",100,1000,7500);
TH1F *VZ2 = new TH1F("VZ","Vertex Z",100,1000,7500);
TH1F *VZ3 = new TH1F("VZ","Vertex Z",100,1000,7500);

TH1F *DZ1 = new TH1F("DZ","Delta Z",100,-100,2200);
TH1F *DZ2 = new TH1F("DZ","Delta Z",100,-100,2200);
TH1F *DZ3 = new TH1F("DZ","Delta Z",100,-100,2200);

TH1F *SegX1 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX2 = new TH1F("SX","Segment X",100,0,140000);
TH1F *SegX3 = new TH1F("SX","Segment X",100,0,140000);

TH1F *SegY1 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY2 = new TH1F("SY","Segment Y",100,0,110000);
TH1F *SegY3 = new TH1F("SY","Segment Y",100,0,110000);

TH1F *PNum1 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum2 = new TH1F("PN","Parent Number",5,0,5);
TH1F *PNum3 = new TH1F("PN","Parent Number",5,0,5);

TH2F *VXY1 = new TH2F("VXY1","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY2 = new TH2F("VXY2","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY3 = new TH2F("VXY3","Vertex X vs Y",100,10000,90000,100,10000,90000);

TFile *Data1, *Data2, *Data3;

float Data1VtxSize = 0, Data2VtxSize = 0, Data3VtxSize = 0;

Double_t a[45];
Double_t b[45];

void DataMCComp2()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"DataMCComp2.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD05_p006.root");
  Data2 = TFile::Open("../Root/Geant4NewSm.root");
  Data3 = TFile::Open("../Root/Geant4SM_v2.1.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataTrk3 = (TTree*)Data3->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  TTree *treeDataVtx3 = (TTree*)Data3->Get("VTX");
  
  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);
    
    TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
    //TLeaf *slpT2 = treeDataTrk1->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");
    TLeaf *IP = treeDataTrk1->GetLeaf("ip_to_1ry_using_1stseg");
    TLeaf *vID = treeDataTrk1->GetLeaf("vID");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();
    
    //double TX = slpTX->GetValue();
    //double TY = slpTY->GetValue();

    //beamTXTot += TX;
    //beamTYTot += TY;

    if (/*-0.018 > beamTX->GetValue() && -0.022 < beamTX->GetValue()*/ true)
    {
      SlpTXHist1->Fill(TX);
      SlpTYHist1->Fill(TY);
      //SlpT2Hist1->Fill(slpT2->GetValue());
      SlpT2Hist1->Fill(sqrt(TX*TX+TY*TY));
      IPData1->Fill(IP->GetValue());
      //if (i < 1000){a[i]=IP->GetValue();}
    }
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
    TLeaf *vID = treeDataTrk2->GetLeaf("vID");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    //double TX = slpTX->GetValue();
    //double TY = slpTY->GetValue();

    SlpTXHist2->Fill(TX);
    SlpTYHist2->Fill(TY);
    //SlpT2Hist2->Fill(slpT2->GetValue());
    SlpT2Hist2->Fill(sqrt(TX*TX+TY*TY));
    IPData2->Fill(IP->GetValue());
    //if (i < 1000){b[i]=IP->GetValue();}
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
    TLeaf *vID = treeDataTrk3->GetLeaf("vID");

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
  
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *VX = treeDataVtx1->GetLeaf("vx");
    TLeaf *VY = treeDataVtx1->GetLeaf("vy");
    TLeaf *VZ = treeDataVtx1->GetLeaf("vz");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *vID = treeDataVtx1->GetLeaf("vID");

    PNum1->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult1->Fill(mult->GetValue());
      //VX1->Fill(VX->GetValue());
      //VY1->Fill(VY->GetValue());
      //VZ1->Fill(VZ->GetValue());

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
    TLeaf *vID = treeDataVtx2->GetLeaf("vID");

    PNum2->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult2->Fill(mult->GetValue());
      //VX2->Fill(VX->GetValue());
      //VY2->Fill(VY->GetValue());
      //VZ2->Fill(VZ->GetValue());

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
    TLeaf *vID = treeDataVtx3->GetLeaf("vID");

    PNum3->Fill(PN->GetValue());

    if(PN->GetValue() == 1)
    {
      Mult3->Fill(mult->GetValue());
      //VX3->Fill(VX->GetValue());
      //VY3->Fill(VY->GetValue());
      //VZ3->Fill(VZ->GetValue());
      
      
      //VXY3->Fill(VX->GetValue(), VY->GetValue());

      //DataX3[i] = VX->GetValue();
      //DataY3[i] = VY->GetValue();

      Data3VtxSize++;
    }
  }
  /*
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
  */
  /*
  TGraph *DataXY1 = new TGraph(Data1VtxSize, DataX1, DataY1);
  TGraph *DataXY2 = new TGraph(Data2VtxSize, DataX2, DataY2);
  TGraph *DataXY3 = new TGraph(Data3VtxSize, DataX3, DataY3);
  TGraph *DataXY4 = new TGraph(Data4VtxSize, DataX4, DataY4);
  */

  float r12 = Data1VtxSize/Data2VtxSize;
  float r13 = Data1VtxSize/Data3VtxSize;

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  SlpTXHist2->Scale(r12);
  SlpTXHist3->Scale(r13);

  SlpTYHist2->Scale(r12);
  SlpTYHist3->Scale(r13);

  SlpT2Hist2->Scale(r12);
  SlpT2Hist3->Scale(r13);

  IPData2->Scale(r12);
  IPData3->Scale(r13);

  Mult2->Scale(r12);
  Mult3->Scale(r13);
  /*
  VX2->Scale(r12);
  VX3->Scale(r13);

  VY2->Scale(r12);
  VY3->Scale(r13);

  VZ2->Scale(r12);
  VZ3->Scale(r13);

  DZ2->Scale(r12);
  DZ3->Scale(r13);

  SegX2->Scale(r12);
  SegX3->Scale(r13);

  SegY2->Scale(r12);
  SegY3->Scale(r13);

  PNum2->Scale(r12);
  PNum3->Scale(r13);
  */
  /*
  TF1 *f = new TF1("f","TMath::Gaus(x,0,1)",-10,10);
  TGraphQQ *qqplot = new TGraphQQ(45,a,f);
  qqplot->SetMarkerStyle(20);
  qqplot->SetMarkerColor(2);
  qqplot->SetMarkerSize(.9);
  qqplot->SetTitle("Q-Q plot of Normalized Residuals");
  */

  TH1F *copyT2Hist = (TH1F*) Mult1->Clone();
  copyT2Hist->SetBinContent(20, 1000);
  copyT2Hist->SetBinContent(25, 200);
  copyT2Hist->SetBinContent(30, 100);
  copyT2Hist->Scale(100);

  //double KomoT2 = SlpT2Hist1->KolmogorovTest(SlpT2Hist2, "DN");
  //double KomoIP = IPData1->KolmogorovTest(IPData2, "DN");
  double KomoMult = Mult1->KolmogorovTest(Mult2, "DN");
  //double KomoMult = TMath::KolmogorovTest(1, a, 1, b, "D");
  //double KomoMult = Mult1->Chi2Test(Mult2, "UW", a);

  //cout << "T2: " << KomoT2 << endl;
  //cout << "IP: " << KomoIP << endl;
  cout << "Mult: " << KomoMult << endl;

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 100000);
  HistDraw(SlpTXHist1, SlpTXHist2, SlpTXHist3);
  Canvas->Print( outNameStart, "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 100000);
  HistDraw(SlpTYHist1, SlpTYHist2, SlpTYHist3);
  Canvas->Print( outName, "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 58000);
  HistDraw(SlpT2Hist1, SlpT2Hist2, SlpT2Hist3);
  Canvas->Print( outName, "pdf");

  IPData1->GetYaxis()->SetRangeUser(0, 200000);
  HistDraw(IPData1, IPData2, IPData3);
  Canvas->Print( outName, "pdf");

  Mult1->GetYaxis()->SetRangeUser(0, 5200);
  HistDraw(Mult1, Mult2, Mult3);
  Canvas->Print( outNameEnd, "pdf");

  /*
  //VX1->GetYaxis()->SetRangeUser(0, 6800);
  HistDraw(VX1, VX2, VX3);
  Canvas->Print( outName, "pdf");

  //VY1->GetYaxis()->SetRangeUser(0, 6800);
  HistDraw(VY1, VY2, VY3);
  Canvas->Print( outName, "pdf");

  //VZ1->GetYaxis()->SetRangeUser(0, 40000);
  HistDraw(VZ1, VZ2, VZ3);
  Canvas->Print( outName, "pdf");

  //PNum1->GetYaxis()->SetRangeUser(0, 320000);
  HistDraw(PNum1, PNum2, PNum3);
  Canvas->Print( outName, "pdf");

  //DZ1->GetYaxis()->SetRangeUser(0, 220000);
  HistDraw(DZ1, DZ2, DZ3);
  Canvas->Print( outName, "pdf");

  //SegX1->GetYaxis()->SetRangeUser(0, 120000);
  HistDraw(SegX1, SegX2, SegX3);
  Canvas->Print( outName, "pdf");

  //SegY1->GetYaxis()->SetRangeUser(0, 120000);
  HistDraw(SegY1, SegY2, SegY3);
  Canvas->Print( outNameEnd, "pdf");
  */
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
  /*
  TF1 *fitx1 = new TF1("fitx1","gaus",-0.1,0.1);
  TF1 *fity1 = new TF1("fity1","gaus",-0.1,0.1);

  SlpTXHist1->Fit("fitx1");
  SlpTYHist1->Fit("fity1");

  double meanx1 = fitx1->GetParameter(1);
  double sigmax1 = fitx1->GetParameter(2);
  double meany1 = fity1->GetParameter(1);
  double sigmay1 = fity1->GetParameter(2);
  
  cout << "X1: Mean = " << meanx1 << ", Sigma = " << sigmax1 << endl;
  cout << "Y1: Mean = " << meany1 << ", Sigma = " << sigmay1 << endl;

  TF1 *fitx2 = new TF1("fitx2","gaus",-0.1,0.1);
  TF1 *fity2 = new TF1("fity2","gaus",-0.1,0.1);

  SlpTXHist2->Fit("fitx2");
  SlpTYHist2->Fit("fity2");

  double meanx2 = fitx2->GetParameter(1);
  double sigmax2 = fitx2->GetParameter(2);
  double meany2 = fity2->GetParameter(1);
  double sigmay2 = fity2->GetParameter(2);
  
  cout << "X2: Mean = " << meanx2 << ", Sigma = " << sigmax2 << endl;
  cout << "Y2: Mean = " << meany2 << ", Sigma = " << sigmay2 << endl;

  TF1 *fitx3 = new TF1("fitx3","gaus",-0.1,0.1);
  TF1 *fity3 = new TF1("fity3","gaus",-0.1,0.1);

  SlpTXHist3->Fit("fitx3");
  SlpTYHist3->Fit("fity3");

  double meanx3 = fitx3->GetParameter(1);
  double sigmax3 = fitx3->GetParameter(2);
  double meany3 = fity3->GetParameter(1);
  double sigmay3 = fity3->GetParameter(2);
  
  cout << "X3: Mean = " << meanx3 << ", Sigma = " << sigmax3 << endl;
  cout << "Y3: Mean = " << meany3 << ", Sigma = " << sigmay3 << endl;
  */
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

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
  StatBox2->SetName("reco-bt-001-040");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kBlack); hist3->SetLineStyle(1); hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("reco-bt-001-040_new_smearing");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kBlack);
  StatBox3->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"PD05","f");
  legend->AddEntry(hist2,"Geant4SM","f");
  legend->AddEntry(hist3,"Geant4SM_v2.1","f");
  legend->Draw();
  
}