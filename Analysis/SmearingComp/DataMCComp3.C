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

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1200,1200);

TH1F *SlpTXHist1 = new TH1F("TX","X Slope",50,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("TX","X Slope",50,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("TY","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("TY","Y Slope",50,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("T2","Space Angle",50,0,0.4);
TH1F *SlpT2Hist2 = new TH1F("T2","Space Angle",50,0,0.4);

TH1F *IPData1 = new TH1F("IP","Impact Parameter",25,0,6);
TH1F *IPData2 = new TH1F("IP","Impact Parameter",25,0,6);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",36,4,40);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",36,4,40);

TFile *Data1, *Data2;

float Data1VtxSize = 0, Data2VtxSize = 0;

void DataMCComp3()
{
  Canvas->SetWindowSize(1200, 1200);
  Canvas->SetCanvasSize(120*6, 120*6);

  gStyle->SetOptStat(0);
  Canvas->Divide(0,2,0,0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"DataMCComp3.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("../Root/PD05_p006.root");
  //Data2 = TFile::Open("../Root/Geant4.root");
  //Data2 = TFile::Open("../Root/Geant4SM_v2.1.root");
  //Data2 = TFile::Open("../Root/Pythia_p006.root");
  Data2 = TFile::Open("../Root/Geant4_p006.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  
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
    TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");

    if(PN->GetValue() == 1)
    {
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
    TLeaf *PN = treeDataTrk2->GetLeaf("n_1ry_parent_dmin_cut");

    if(PN->GetValue() > 0)
    {
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
  }

  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");

    if(PN->GetValue() > 0)
    {
      Mult1->Fill(mult->GetValue());

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
    TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");

    if(PN->GetValue() > 0)
    {
      Mult2->Fill(mult->GetValue());

      //VXY2->Fill(VX->GetValue(), VY->GetValue());

      //DataX2[i] = VX->GetValue();
      //DataY2[i] = VY->GetValue();

      Data2VtxSize++;
    }
  }
  
  float r12 = Data1VtxSize/Data2VtxSize;
  //float r12 = treeDataVtx1->GetEntriesFast()/treeDataVtx2->GetEntriesFast();

  //cout << Data1VtxSize << ", " << Data2VtxSize << ", " << Data3VtxSize << ", " << Data4VtxSize << endl;
  //cout << r12 << ", " << r13 << ", " << r14 << endl;

  //SlpTXHist2->Scale(r12);

  //SlpTYHist2->Scale(r12);

  SlpT2Hist2->Scale(r12);

  IPData2->Scale(r12);

  Mult2->Scale(r12);

  /*
  SlpTXHist1->GetYaxis()->SetRangeUser(0, 100000);
  HistDraw(SlpTXHist1, SlpTXHist2);
  Canvas->Print( outNameStart, "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 100000);
  HistDraw(SlpTYHist1, SlpTYHist2);
  Canvas->Print( outName, "pdf");
  */

  //gPad->SetGrid();
  //Canvas->SetGrid();
  //TH2C *h = new TH2C("h","h",32,0.,32.,64,0.,64.);
  //h->SetStats(0);
  //h->Draw();
  
  TH1F *copyT2Hist = (TH1F*) SlpT2Hist1->Clone();
  copyT2Hist->SetName("T2Hist");
  copyT2Hist->Divide(SlpT2Hist2);

  TH1F *copyIPHist = (TH1F*) IPData1->Clone();
  copyIPHist->SetName("IPHist");
  copyIPHist->Divide(IPData2);

  TH1F *copyMultHist = (TH1F*) Mult1->Clone();
  copyMultHist->SetName("MultHist");
  copyMultHist->Divide(Mult2);

  Canvas->cd(1);
  gPad->SetGrid(100);
  //IPData1->Draw();
  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 110000);
  //SlpT2Hist1->GetYaxis()->SetRangeUser(0, 700000);
  HistDraw(SlpT2Hist1, SlpT2Hist2);

  Canvas->cd(2);
  gPad->SetGrid(100);
  copyT2Hist->GetYaxis()->SetLabelOffset(0.01);
  copyT2Hist->Draw("HIST E1");
  copyT2Hist->SetTitle("Division");
  copyT2Hist->SetLineWidth(2);
  copyT2Hist->GetYaxis()->SetRangeUser(0, 2);

  TF1 *fa1 = new TF1("fa1","1",0,100);
  fa1->Draw("SAME");

  Canvas->Print( outNameStart, "pdf");

  Canvas->cd(1);
  //IPData1->Draw();
  IPData1->GetYaxis()->SetRangeUser(0, 250000);
  //IPData1->GetYaxis()->SetRangeUser(0, 1600000);
  HistDraw(IPData1, IPData2);

  Canvas->cd(2);
  copyIPHist->GetYaxis()->SetLabelOffset(0.01);
  copyIPHist->Draw("HIST E1");
  copyIPHist->SetTitle("Division");
  copyIPHist->SetLineWidth(2);
  copyIPHist->GetYaxis()->SetRangeUser(0, 2);

  fa1->Draw("SAME");

  Canvas->Print( outName, "pdf");

  Canvas->cd(1);
  //IPData1->Draw();
  Mult1->GetYaxis()->SetRangeUser(0, 5200);
  //Mult1->GetYaxis()->SetRangeUser(0, 32000);
  HistDraw(Mult1, Mult2);

  Canvas->cd(2);
  copyMultHist->GetYaxis()->SetLabelOffset(0.01);
  copyMultHist->Draw("HIST E1");
  copyMultHist->SetTitle("Division");
  copyMultHist->SetLineWidth(2);
  copyMultHist->GetYaxis()->SetRangeUser(0, 5);

  fa1->Draw("SAME");

  Canvas->Print( outNameEnd, "pdf");
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{

  Canvas->cd(1);
  hist1->Draw("HIST E1"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);
  /*
  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("PD05");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();
  */
  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);
  /*
  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("reco-bt-001-040");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  */
  /*
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kBlack); hist3->SetLineStyle(1); hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kBlack, 0.15);

  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName("reco-bt-001-040_new_smearing");
  StatBox3->SetY1NDC(0.5);
  StatBox3->SetY2NDC(0.3);
  StatBox3->SetTextColor(kBlack);
  StatBox3->Draw();
  */

  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"PD05","f");
  //legend->AddEntry(hist2,"reco-bt-001-040","f");
  legend->AddEntry(hist2,"Geant4","f");
  legend->Draw();
  
}