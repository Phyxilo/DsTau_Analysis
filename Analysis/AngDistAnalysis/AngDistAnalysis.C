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

TH1F *SlpTXHist1 = new TH1F("TX_PD05","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX_PD04","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("TX_hadrons_g4_pythia1ryin_r102","X Slope",100,-0.4,0.4);
TH1F *SlpTXHist4 = new TH1F("TX_hadrons-r102","X Slope",100,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY_PD05","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY_PD04","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("TY_hadrons_g4_pythia1ryin_r102","Y Slope",100,-0.4,0.4);
TH1F *SlpTYHist4 = new TH1F("TY_hadrons-r102","Y Slope",100,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2_PD05","Space Angle",100,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("T2_PD04","Space Angle",100,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("T2_hadrons_g4_pythia1ryin_r102","Space Angle",100,0,0.5);
TH1F *SlpT2Hist4 = new TH1F("T2_hadrons-r102","Space Angle",100,0,0.5);

TH1F *IPData1 = new TH1F("IP_PD05","Impact Parameter",50,0,10);
TH1F *IPData2 = new TH1F("IP_PD04","Impact Parameter",50,0,10);
TH1F *IPData3 = new TH1F("IP_hadrons_g4_pythia1ryin_r102","Impact Parameter",50,0,10);
TH1F *IPData4 = new TH1F("IP_hadrons-r102","Impact Parameter",50,0,10);

TH1F *Mult1 = new TH1F("Mlt_PD05","Multiplicity",100,0,100);
TH1F *Mult2 = new TH1F("Mlt_PD04","Multiplicity",100,0,100);
TH1F *Mult3 = new TH1F("Mlt_hadrons_g4_pythia1ryin_r102","Multiplicity",100,0,100);
TH1F *Mult4 = new TH1F("Mlt_hadrons-r102","Multiplicity",100,0,100);

TH1F *VX1 = new TH1F("VX_PD05","Vertex X",100,10000,140000);
TH1F *VX2 = new TH1F("VX_PD04","Vertex X",100,10000,140000);
TH1F *VX3 = new TH1F("VX_hadrons_g4_pythia1ryin_r102","Vertex X",100,10000,140000);
TH1F *VX4 = new TH1F("VX_hadrons-r102","Vertex X",100,10000,140000);

TH1F *VY1 = new TH1F("VY_PD05","Vertex Y",100,10000,110000);
TH1F *VY2 = new TH1F("VY_PD04","Vertex Y",100,10000,110000);
TH1F *VY3 = new TH1F("VY_hadrons_g4_pythia1ryin_r102","Vertex Y",100,10000,110000);
TH1F *VY4 = new TH1F("VY_hadrons-r102","Vertex Y",100,10000,110000);

TH1F *VZ1 = new TH1F("VZ_PD05","Vertex Z",100,1000,7500);
TH1F *VZ2 = new TH1F("VZ_PD04","Vertex Z",100,1000,7500);
TH1F *VZ3 = new TH1F("VZ_hadrons_g4_pythia1ryin_r102","Vertex Z",100,1000,7500);
TH1F *VZ4 = new TH1F("VZ_hadrons-r102","Vertex Z",100,1000,7500);

TFile *Data1, *Data2, *Data3, *Data4;

float Data1VtxSize = 0, Data2VtxSize = 0, Data3VtxSize = 0, Data4VtxSize = 0;

void AngDistAnalysis(float initAng, float step)
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char outName[64], outNameStart[64], outNameEnd[64], txtOutName[64];
  sprintf(outName,"AngDistAnlaysis_%.3f_%.3f.pdf", initAng, step);
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  sprintf(txtOutName, "AngDistAnlaysis__%.3f_%.3f.txt", initAng, step);

  Data1 = TFile::Open("../Root/PD05.root");
  Data2 = TFile::Open("../Root/PD04.root");
  Data3 = TFile::Open("../Root/Geant4.root");
  Data4 = TFile::Open("../Root/Pythia.root");

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

  int Ntrk1 = 0, Ntrk2 = 0, Ntrk3 = 0, Ntrk4 = 0;
  double totT2_1 = 0, totT2_2 = 0, totT2_3 = 0, totT2_4 = 0;

  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);

    TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
    TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");
    TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    double T2 = sqrt(TX*TX+TY*TY);

    if (T2 >= initAng && T2 < initAng+step && PN->GetValue() == 1)
    {
      TLeaf *IP = treeDataTrk1->GetLeaf("ip_to_1ry_using_1stseg");

      SlpTXHist1->Fill(TX);
      SlpTYHist1->Fill(TY);
      SlpT2Hist1->Fill(T2);
      IPData1->Fill(IP->GetValue());

      Ntrk1++;
      totT2_1 += T2;
    }
  }
  
  for (int i = 0; i < treeDataTrk2->GetEntriesFast(); i++)
  {
    treeDataTrk2->GetEntry(i);

    TLeaf *slpTX = treeDataTrk2->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk2->GetLeaf("ty");
    TLeaf *beamTX = treeDataTrk2->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk2->GetLeaf("typeak");
    TLeaf *PN = treeDataTrk2->GetLeaf("n_1ry_parent_dmin_cut");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    double T2 = sqrt(TX*TX+TY*TY);

    if (T2 >= initAng && T2 < initAng+step && PN->GetValue() == 1)
    {
      TLeaf *IP = treeDataTrk2->GetLeaf("ip_to_1ry_using_1stseg");

      SlpTXHist2->Fill(TX);
      SlpTYHist2->Fill(TY);
      SlpT2Hist2->Fill(T2);
      IPData2->Fill(IP->GetValue());

      Ntrk2++;
      totT2_2 += T2;
    }
  }

  for (int i = 0; i < treeDataTrk3->GetEntriesFast(); i++)
  {
    treeDataTrk3->GetEntry(i);

    TLeaf *slpTX = treeDataTrk3->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk3->GetLeaf("ty");
    TLeaf *beamTX = treeDataTrk3->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk3->GetLeaf("typeak");
    TLeaf *PN = treeDataTrk3->GetLeaf("n_1ry_parent_dmin_cut");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    double T2 = sqrt(TX*TX+TY*TY);

    if (T2 >= initAng && T2 < initAng+step && PN->GetValue() == 1)
    {
      TLeaf *IP = treeDataTrk3->GetLeaf("ip_to_1ry_using_1stseg");

      SlpTXHist3->Fill(TX);
      SlpTYHist3->Fill(TY);
      SlpT2Hist3->Fill(T2);
      IPData3->Fill(IP->GetValue());

      Ntrk3++;
      totT2_3 += T2;
    }
  }

  for (int i = 0; i < treeDataTrk4->GetEntriesFast(); i++)
  {
    treeDataTrk4->GetEntry(i);

    TLeaf *slpTX = treeDataTrk4->GetLeaf("tx");
    TLeaf *slpTY = treeDataTrk4->GetLeaf("ty");
    TLeaf *beamTX = treeDataTrk4->GetLeaf("txpeak");
    TLeaf *beamTY = treeDataTrk4->GetLeaf("typeak");
    TLeaf *PN = treeDataTrk4->GetLeaf("n_1ry_parent_dmin_cut");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    double T2 = sqrt(TX*TX+TY*TY);
    
    if (T2 >= initAng && T2 < initAng+step && PN->GetValue() == 1)
    {
      TLeaf *IP = treeDataTrk4->GetLeaf("ip_to_1ry_using_1stseg");

      SlpTXHist4->Fill(TX);
      SlpTYHist4->Fill(TY);
      SlpT2Hist4->Fill(T2);
      IPData4->Fill(IP->GetValue());

      Ntrk4++;
      totT2_4 += T2;
    }
  }

  float avgT2_1 = totT2_1/Ntrk1;
  float avgT2_2 = totT2_2/Ntrk2;
  float avgT2_3 = totT2_3/Ntrk3;
  float avgT2_4 = totT2_4/Ntrk4;

  float avgMlt1 = Ntrk1/Data1VtxSize;
  float avgMlt2 = Ntrk2/Data2VtxSize;
  float avgMlt3 = Ntrk3/Data3VtxSize;
  float avgMlt4 = Ntrk4/Data4VtxSize;

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

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 650000);
  HistDraw(SlpTXHist1, SlpTXHist2, SlpTXHist3, SlpTXHist4);
  Canvas->Print( outNameStart, "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 650000);
  HistDraw(SlpTYHist1, SlpTYHist2, SlpTYHist3, SlpTYHist4);
  Canvas->Print( outName, "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 520000);
  HistDraw(SlpT2Hist1, SlpT2Hist2, SlpT2Hist3, SlpT2Hist4);
  Canvas->Print( outName, "pdf");

  //IPData1->GetYaxis()->SetRangeUser(0, 12000);
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

  VZ1->GetYaxis()->SetRangeUser(0, 6800);
  HistDraw(VZ1, VZ2, VZ3, VZ4);
  Canvas->Print( outNameEnd, "pdf");

  ofstream out = ofstream(txtOutName, ios::out);

  out << "PD05: " << "Average Angle: " << avgT2_1 << ", Number of Tracks: " << Ntrk1 << ", Track per Vertex: " << avgMlt1 << endl;
  out << "PD04: " << "Average Angle: " << avgT2_2 << ", Number of Tracks: " << Ntrk2 << ", Track per Vertex: " << avgMlt2 << endl;
  out << "Pythia: " << "Average Angle: " << avgT2_3 << ", Number of Tracks: " << Ntrk3 << ", Track per Vertex: " << avgMlt3 << endl;
  out << "Geant4: " << "Average Angle: " << avgT2_4 << ", Number of Tracks: " << Ntrk4 << ", Track per Vertex: " << avgMlt4 << endl;
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3, TH1F *hist4)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD05");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("PD04");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kTeal+10); hist3->SetLineStyle(1); hist3->SetLineWidth(2); hist3->SetFillColorAlpha(kTeal+10, 0.3);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("hadrons_g4_pythia1ryin_r102");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kTeal+10);
  StatBox3->Draw();

  hist4->Draw("SAMES HIST"); hist4->SetLineColor(kBlack); hist4->SetLineStyle(1); hist4->SetLineWidth(2); hist4->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("hadrons-r102");
  StatBox4->SetY1NDC(0.3);
  StatBox4->SetY2NDC(0.1);
  StatBox4->SetTextColor(kBlack);
  StatBox4->Draw();
  /*
  TLegend *legend = new TLegend(0.1, 0.8, 0.32, 0.95);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(hist1,"PD05","f");
  legend->AddEntry(hist2,"PD04","f");
  legend->AddEntry(hist3,"hadrons_g4_pythia1ryin_r102","f");
  legend->AddEntry(hist4,"hadrons-r102","f");
  legend->Draw();
  */
}