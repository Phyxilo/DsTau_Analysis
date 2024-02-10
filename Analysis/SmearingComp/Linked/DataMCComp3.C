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

TH1F *SlpT2Hist1 = new TH1F("T2","",50,0,0.4);
TH1F *SlpT2Hist2 = new TH1F("T2","",50,0,0.4);

TH1F *IPData1 = new TH1F("IP","",25,0,6);
TH1F *IPData2 = new TH1F("IP","",25,0,6);

TH1F *Mult1 = new TH1F("Mlt","",35,5,40);
TH1F *Mult2 = new TH1F("Mlt","",35,5,40);

TFile *Data1, *Data2;

float Data1VtxSize = 0, Data2VtxSize = 0;
float Data1TrkSize = 0, Data2TrkSize = 0;

void DataMCComp3()
{
  Canvas->SetWindowSize(1200, 1200);
  Canvas->SetCanvasSize(120*6, 120*6);

  Canvas->Divide(0,2,0,0);
  //gStyle->SetOptStat(0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"DataMCComp3.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    sprintf(dataName, "../../../Data_v20220912/PD05/Linked/RootOut/p%02d6.root", dirIndex);

    if (dirIndex < 7) { sprintf(MC1Name, "../../../EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC1Name, "../../../EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC2Name, "../../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC2Name, "../../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC3Name, "../../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC3Name, "../../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC4Name, "../../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC4Name, "../../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { sprintf(MC5Name, "../../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC5Name, "../../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data1 = TFile::Open(dataName);
    Data2 = TFile::Open(MC1Name);
    
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
      TLeaf *w = treeDataTrk1->GetLeaf("flagw");

      treeDataVtx1->GetEntry(vID->GetValue());

      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *intType = treeDataVtx1->GetLeaf("intType");

      bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));

      if(intType->GetValue() == 1 && areaBool && PN->GetValue() > 0 && w->GetValue() == 1)
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

        Data1TrkSize++;
      }

      /*
      if(areaBool && PN->GetValue() > 0 && w->GetValue() == 1)
      {
        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        
        //double TX = slpTX->GetValue();
        //double TY = slpTY->GetValue();

        //beamTXTot += TX;
        //beamTYTot += TY;

        SlpTXHist2->Fill(TX);
        SlpTYHist2->Fill(TY);
        //SlpT2Hist1->Fill(slpT2->GetValue());
        SlpT2Hist2->Fill(sqrt(TX*TX+TY*TY));
        IPData2->Fill(IP->GetValue());

        Data2TrkSize++;
      }
      */
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
      TLeaf *w = treeDataTrk2->GetLeaf("flagw");

      treeDataVtx2->GetEntry(vID->GetValue());

      TLeaf *area1 = treeDataVtx2->GetLeaf("area1");
      TLeaf *intType = treeDataVtx2->GetLeaf("intType");

      if(intType->GetValue() == 1 && PN->GetValue() > 0 && w->GetValue() == 1)
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

        Data2TrkSize++;
      }
    }

    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);

      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx1->GetLeaf("flagw");
      TLeaf *intType = treeDataVtx1->GetLeaf("intType");

      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");

      bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));

      if(intType->GetValue() == 1 && areaBool && PN->GetValue() > 0 && w->GetValue() == 1)
      {
        Mult1->Fill(mult->GetValue());

        //VXY1->Fill(VX->GetValue(), VY->GetValue());

        //DataX1[i] = VX->GetValue();
        //DataY1[i] = VY->GetValue();

        Data1VtxSize++;
      }
      
      /*
      if(areaBool && PN->GetValue() > 0 && w->GetValue() == 1)
      {
        Mult2->Fill(mult->GetValue());

        Data2VtxSize++;
      }
      */
    }
    
    for (int i = 0; i < treeDataVtx2->GetEntriesFast(); i++)
    {
      treeDataVtx2->GetEntry(i);

      TLeaf *mult = treeDataVtx2->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx2->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataVtx2->GetLeaf("flagw");
      TLeaf *intType = treeDataVtx2->GetLeaf("intType");

      if(intType->GetValue() == 1 && PN->GetValue() > 0 && w->GetValue() == 1)
      {
        Mult2->Fill(mult->GetValue());

        //VXY2->Fill(VX->GetValue(), VY->GetValue());

        //DataX2[i] = VX->GetValue();
        //DataY2[i] = VY->GetValue();

        Data2VtxSize++;
      }
    }
  }
  
  float r12 = Data1VtxSize/Data2VtxSize;
  float r12Trk = Data1TrkSize/Data2TrkSize;

  cout << r12Trk << endl;
  cout << r12 << endl;

  SlpT2Hist2->Scale(r12Trk);
  IPData2->Scale(r12Trk);
  Mult2->Scale(r12);
  
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
  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 150000);
  HistDraw(SlpT2Hist1, SlpT2Hist2);

  Canvas->cd(2);
  gPad->SetGrid(100);

  copyT2Hist->GetYaxis()->SetLabelOffset(0.01);
  copyT2Hist->Draw("HIST E1");
  //copyT2Hist->SetTitle("Division");
  copyT2Hist->SetLineWidth(2);
  copyT2Hist->GetYaxis()->SetRangeUser(0, 2);
  copyT2Hist->SetXTitle("Space angle (rad)");

  gPad->Update();
  TPaveStats *statT2 = (TPaveStats*)copyT2Hist->GetListOfFunctions()->FindObject("stats"); 
  statT2->SetOptStat(0);

  TF1 *fa1 = new TF1("fa1","1",0,100);
  fa1->Draw("SAME");

  Canvas->Print( outNameStart, "pdf");

  Canvas->cd(1);
  //IPData1->Draw();
  IPData1->GetYaxis()->SetRangeUser(0, 300000);
  HistDraw(IPData1, IPData2);

  Canvas->cd(2);

  copyIPHist->GetYaxis()->SetLabelOffset(0.01);
  copyIPHist->Draw("HIST E1");
  //copyIPHist->SetTitle("Division");
  copyIPHist->SetLineWidth(2);
  copyIPHist->GetYaxis()->SetRangeUser(0, 2);
  copyIPHist->SetXTitle("Impact Parameter (#mum)");

  gPad->Update();
  TPaveStats *statIP = (TPaveStats*)copyIPHist->GetListOfFunctions()->FindObject("stats"); 
  statIP->SetOptStat(0);

  fa1->Draw("SAME");

  Canvas->Print( outName, "pdf");

  Canvas->cd(1);
  //IPData1->Draw();
  Mult1->GetYaxis()->SetRangeUser(0, 3600);
  HistDraw(Mult1, Mult2);

  Canvas->cd(2);

  copyMultHist->GetYaxis()->SetLabelOffset(0.01);
  copyMultHist->Draw("HIST E1");
  //copyMultHist->SetTitle("Division");
  copyMultHist->SetLineWidth(2);
  copyMultHist->GetYaxis()->SetRangeUser(0, 5);
  copyMultHist->SetXTitle("Multiplicity");

  gPad->Update();
  TPaveStats *statMult = (TPaveStats*)copyMultHist->GetListOfFunctions()->FindObject("stats"); 
  statMult->SetOptStat(0);

  fa1->Draw("SAME");

  Canvas->Print( outNameEnd, "pdf");
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{
  Canvas->cd(1);

  hist1->SetStats(0);
  hist1->Draw("HIST E1"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

  /*
  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");
  StatBox1->SetName("Data");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();
  */

  hist2->SetStats(0);
  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);

  /*
  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  StatBox2->SetName("EPOS");
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
  legend->AddEntry(hist1,"Data","f");
  legend->AddEntry(hist2,"EPOS","f");
  //legend->AddEntry(hist2,"Geant4","f");
  //legend->AddEntry(hist2,"Pythia","f");
  //legend->AddEntry(hist2,"DPMJET","f");
  //legend->AddEntry(hist2,"QGSJET","f");
  legend->Draw();
  
}