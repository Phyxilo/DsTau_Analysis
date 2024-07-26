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

// compType == 0 for all events
// compType == 1 for multiplicity >= 10 events
// compType == 2 for multiplicity < 10 events
int compType = 0;

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3);

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHistData = new TH1F("PD05","",50,-0.4,0.4);
TH1F *SlpTXHistMC1 = new TH1F("EPOS_Old","",50,-0.4,0.4);
TH1F *SlpTXHistMC2 = new TH1F("EPOS_New","",50,-0.4,0.4);

TH1F *SlpTYHistData = new TH1F("PD05","",50,-0.4,0.4);
TH1F *SlpTYHistMC1 = new TH1F("EPOS_Old","",50,-0.4,0.4);
TH1F *SlpTYHistMC2 = new TH1F("EPOS_New","",50,-0.4,0.4);

TH1F *SlpT2HistData = new TH1F("PD05","",50,0,0.34);
TH1F *SlpT2HistMC1 = new TH1F("EPOS_Old","",50,0,0.34);
TH1F *SlpT2HistMC2 = new TH1F("EPOS_New","",50,0,0.34);

TH1F *IPDataData = new TH1F("PD05","",25,0,5.8);
TH1F *IPDataMC1 = new TH1F("EPOS_Old","",25,0,5.8);
TH1F *IPDataMC2 = new TH1F("EPOS_New","",25,0,5.8);

TH1F *MultData = new TH1F("PD05","",33,5,38);
TH1F *MultMC1 = new TH1F("EPOS_Old","",33,5,38);
TH1F *MultMC2 = new TH1F("EPOS_New","",33,5,38);

TFile *Data, *MC1, *MC2;

float DataVtxSize = 0, MC1VtxSize = 0, MC2VtxSize = 0;

bool intTypeActive = true;

double dataCorrection = 0.95;
float migCut = 18;

void MCDataCompEPOS()
{
  Canvas->SetWindowSize(1200, 1200);
  Canvas->SetCanvasSize(120*6, 120*6);

  Canvas->Divide(0,2,0,0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"MCDataCompEPOS.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    cout << "Processing subvolume " << dirIndex << endl;

    char dataName [256], MC1Name[256], MC2Name[256];

    sprintf(dataName, "../../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", dirIndex);

    if (dirIndex < 7) { sprintf(MC1Name, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC1Name, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl071_105.root"); }
    
    if (dirIndex < 7) { sprintf(MC2Name, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { sprintf(MC1Name, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl071_105.root"); }

    Data = TFile::Open(dataName);
    MC1 = TFile::Open(MC1Name);
    MC2 = TFile::Open(MC2Name);

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeMCTrk1 = (TTree*)MC1->Get("TRK");
    TTree *treeMCTrk2 = (TTree*)MC2->Get("TRK");

    TTree *treeDataVtx = (TTree*)Data->Get("VTX");
    TTree *treeMCVtx1 = (TTree*)MC1->Get("VTX");
    TTree *treeMCVtx2 = (TTree*)MC2->Get("VTX");

    int dataTrkInd = 0, MC1TrkInd = 0, MC2TrkInd = 0;
    double initZ, lastZ;
    double *dataEndArr, *MC1EndArr, *MC2EndArr;
    double dataMean, MC1Mean, MC2Mean;

    dataEndArr = DataEndPoints(treeDataVtx);
    MC1EndArr = MCEndPoints(treeMCVtx1);
    MC2EndArr = MCEndPoints(treeMCVtx2);

    dataMean = DataMean(treeDataVtx);
    MC1Mean = DataMean(treeMCVtx1);
    MC2Mean = DataMean(treeMCVtx2);

    initZ = dataEndArr[0];
    lastZ = dataEndArr[1];
    
    for (int i = 0; i < treeDataTrk->GetEntriesFast(); i++)
    {
      treeDataTrk->GetEntry(i);
      
      TLeaf *slpTX = treeDataTrk->GetLeaf("tx");
      TLeaf *slpTY = treeDataTrk->GetLeaf("ty");
      TLeaf *beamTX = treeDataTrk->GetLeaf("txpeak");
      TLeaf *beamTY = treeDataTrk->GetLeaf("typeak");
      TLeaf *IP = treeDataTrk->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeDataTrk->GetLeaf("vID");
      TLeaf *PN = treeDataTrk->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeDataTrk->GetLeaf("flagw");

      treeDataVtx->GetEntry(vID->GetValue());

      TLeaf *iType = treeDataVtx->GetLeaf("intType");
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");
      TLeaf *mult = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeDataVtx->GetLeaf("vz");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = (slpTX->GetValue() - beamTX->GetValue()) * dataCorrection;
          double TY = (slpTY->GetValue() - beamTY->GetValue()) * dataCorrection;
          
          SlpTXHistData->Fill(TX);
          SlpTYHistData->Fill(TY);
          SlpT2HistData->Fill(sqrt(TX*TX+TY*TY));
          IPDataData->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC1EndArr[0];
    lastZ = MC1EndArr[1];
    
    for (int i = 0; i < treeMCTrk1->GetEntriesFast(); i++)
    {
      treeMCTrk1->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk1->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk1->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk1->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk1->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk1->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk1->GetLeaf("vID");
      TLeaf *PN = treeMCTrk1->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk1->GetLeaf("flagw");

      treeMCVtx1->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx1->GetLeaf("intType");
      TLeaf *mult = treeMCVtx1->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx1->GetLeaf("vz");

      //TLeaf *vtxVID = treeMCVtx1->GetLeaf("vID");
      //cout << "VtxVID: " << vtxVID->GetValue() << ", TrkVID: " << vID->GetValue() << endl;

      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC1Mean - (250-migCut) && vz->GetValue() < MC1Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();

          SlpTXHistMC1->Fill(TX);
          SlpTYHistMC1->Fill(TY);
          SlpT2HistMC1->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC1->Fill(IP->GetValue());
        }
      }
    }

    initZ = MC2EndArr[0];
    lastZ = MC2EndArr[1];

    for (int i = 0; i < treeMCTrk2->GetEntriesFast(); i++)
    {
      treeMCTrk2->GetEntry(i);
      
      TLeaf *slpTX = treeMCTrk2->GetLeaf("tx");
      TLeaf *slpTY = treeMCTrk2->GetLeaf("ty");
      TLeaf *beamTX = treeMCTrk2->GetLeaf("txpeak");
      TLeaf *beamTY = treeMCTrk2->GetLeaf("typeak");
      TLeaf *IP = treeMCTrk2->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeMCTrk2->GetLeaf("vID");
      TLeaf *PN = treeMCTrk2->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeMCTrk2->GetLeaf("flagw");

      treeMCVtx2->GetEntry(vID->GetValue());

      TLeaf *iType = treeMCVtx2->GetLeaf("intType");
      TLeaf *mult = treeMCVtx2->GetLeaf("n_1ry_trk");
      TLeaf *vz = treeMCVtx2->GetLeaf("vz");
      
      //if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if (PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC2Mean - (250-migCut) && vz->GetValue() < MC2Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          
          SlpTXHistMC2->Fill(TX);
          SlpTYHistMC2->Fill(TY);
          SlpT2HistMC2->Fill(sqrt(TX*TX+TY*TY));
          IPDataMC2->Fill(IP->GetValue());
        }
      }
    }

    initZ = dataEndArr[0];
    lastZ = dataEndArr[1];

    for (int i = 0; i < treeDataVtx->GetEntriesFast(); i++)
    {
      treeDataVtx->GetEntry(i);

      TLeaf *mult = treeDataVtx->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeDataVtx->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeDataVtx->GetLeaf("vID");
      TLeaf *w = treeDataVtx->GetLeaf("flagw");
      TLeaf *iType = treeDataVtx->GetLeaf("intType");
      TLeaf *area1 = treeDataVtx->GetLeaf("area1");
      TLeaf *vz = treeDataVtx->GetLeaf("vz");

      //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
      bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && areaBool && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultData->Fill(mult->GetValue());
          DataVtxSize++;
        }
      }
    }

    initZ = MC1EndArr[0];
    lastZ = MC1EndArr[1];

    for (int i = 0; i < treeMCVtx1->GetEntriesFast(); i++)
    {
      treeMCVtx1->GetEntry(i);

      TLeaf *mult = treeMCVtx1->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx1->GetLeaf("vID");
      TLeaf *w = treeMCVtx1->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx1->GetLeaf("intType");
      TLeaf *vz = treeMCVtx1->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC1Mean - (250-migCut) && vz->GetValue() < MC1Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC1->Fill(mult->GetValue());
          MC1VtxSize++;
        }
      }
    }

    initZ = MC2EndArr[0];
    lastZ = MC2EndArr[1];

    for (int i = 0; i < treeMCVtx2->GetEntriesFast(); i++)
    {
      treeMCVtx2->GetEntry(i);

      TLeaf *mult = treeMCVtx2->GetLeaf("n_1ry_trk");
      TLeaf *PN = treeMCVtx2->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *vID = treeMCVtx2->GetLeaf("vID");
      TLeaf *w = treeMCVtx2->GetLeaf("flagw");
      TLeaf *iType = treeMCVtx2->GetLeaf("intType");
      TLeaf *vz = treeMCVtx2->GetLeaf("vz");

      //if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() - initZ > migCut && vz->GetValue() - lastZ < -migCut)
      if(PN->GetValue() > 0 && w->GetValue() == 1 && ((intTypeActive && iType->GetValue() >= 1) || (!intTypeActive)) && vz->GetValue() > MC2Mean - (250-migCut) && vz->GetValue() < MC2Mean + (250-migCut))
      {
        if (compType == 0 || (compType == 1 && mult->GetValue() >= 10) || (compType == 2 && mult->GetValue() < 10))
        {
          MultMC2->Fill(mult->GetValue());
          MC2VtxSize++;
        }
      }
    }
  }

  SlpTXHistMC1->Scale(SlpTXHistData->Integral()/SlpTXHistMC1->Integral());
  SlpTXHistMC2->Scale(SlpTXHistData->Integral()/SlpTXHistMC2->Integral());

  SlpTYHistMC1->Scale(SlpTYHistData->Integral()/SlpTYHistMC1->Integral());
  SlpTYHistMC2->Scale(SlpTYHistData->Integral()/SlpTYHistMC2->Integral());

  SlpT2HistMC1->Scale(SlpT2HistData->Integral()/SlpT2HistMC1->Integral());
  SlpT2HistMC2->Scale(SlpT2HistData->Integral()/SlpT2HistMC2->Integral());

  IPDataMC1->Scale(IPDataData->Integral()/IPDataMC1->Integral());
  IPDataMC2->Scale(IPDataData->Integral()/IPDataMC2->Integral());

  MultMC1->Scale(MultData->Integral()/MultMC1->Integral());
  MultMC2->Scale(MultData->Integral()/MultMC2->Integral());


  TH1F *copyT2HistMC1 = (TH1F*) SlpT2HistMC1->Clone();
  copyT2HistMC1->SetName("T2Hist");
  copyT2HistMC1->Divide(SlpT2HistData);
  TH1F *copyT2HistMC2 = (TH1F*) SlpT2HistMC2->Clone();
  copyT2HistMC2->SetName("T2Hist");
  copyT2HistMC2->Divide(SlpT2HistData);

  TH1F *copyIPHistMC1 = (TH1F*) IPDataMC1->Clone();
  copyIPHistMC1->SetName("IPHist");
  copyIPHistMC1->Divide(IPDataData);
  TH1F *copyIPHistMC2 = (TH1F*) IPDataMC2->Clone();
  copyIPHistMC2->SetName("IPHist");
  copyIPHistMC2->Divide(IPDataData);

  TH1F *copyMultHistMC1 = (TH1F*) MultMC1->Clone();
  copyMultHistMC1->SetName("MultHist");
  copyMultHistMC1->Divide(MultData);
  TH1F *copyMultHistMC2 = (TH1F*) MultMC2->Clone();
  copyMultHistMC2->SetName("MultHist");
  copyMultHistMC2->Divide(MultData);

  //if(intTypeActive) {SlpT2HistData->GetYaxis()->SetRangeUser(0, 150000);}
  //else {SlpT2HistData->GetYaxis()->SetRangeUser(0, 220000);}

  if(compType == 2) {SlpT2HistMC2->GetYaxis()->SetRangeUser(-1000, 36000);}
  else {SlpT2HistMC2->GetYaxis()->SetRangeUser(-5000, 185000);}

  cout << SlpT2HistData->GetMean() << endl;

  Canvas->cd(1);
  gPad->SetGrid(100);
  SlpT2HistData->SetXTitle("Tan #theta");
  HistDraw(SlpT2HistData, SlpT2HistMC2, SlpT2HistMC1);

  Canvas->cd(2);
  gPad->SetGrid(100);
  copyT2HistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyT2HistMC2->SetXTitle("Tan #theta");
  copyT2HistMC2->SetYTitle("MC / Data");
  copyT2HistMC2->GetYaxis()->SetLabelSize(0.05);
  copyT2HistMC2->GetXaxis()->SetLabelSize(0.05);

  copyT2HistMC2->Draw("HIST E1"); copyT2HistMC2->SetLineWidth(2); copyT2HistMC2->SetLineColor(kBlue); copyT2HistMC2->GetYaxis()->SetRangeUser(0.6, 1.45);
  copyT2HistMC1->Draw("SAMES HIST E1"); copyT2HistMC1->SetLineWidth(2); copyT2HistMC1->SetLineColor(kRed); copyT2HistMC1->GetYaxis()->SetRangeUser(0.6, 1.45); copyT2HistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statT2 = (TPaveStats*)copyT2HistMC2->GetListOfFunctions()->FindObject("stats"); 
  statT2->SetOptStat(0);

  TF1 *fa1 = new TF1("fa1","1",0,1);
  fa1->Draw("SAME");
  fa1->SetLineWidth(2);
  fa1->SetLineColor(kBlack);

  Canvas->Print( outNameStart, "pdf");

  //if(intTypeActive) {IPDataData->GetYaxis()->SetRangeUser(0, 400000);}
  //else {IPDataData->GetYaxis()->SetRangeUser(0, 580000);}

  IPDataMC2->GetYaxis()->SetRangeUser(-10000, 460000);

  Canvas->cd(1);
  IPDataData->SetXTitle("Impact Parameter (#mum)");
  HistDraw(IPDataData, IPDataMC2, IPDataMC1);

  Canvas->cd(2);
  copyIPHistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyIPHistMC2->SetXTitle("Impact Parameter (#mum)");
  copyIPHistMC2->SetYTitle("MC / Data");
  copyIPHistMC2->GetYaxis()->SetLabelSize(0.05);
  copyIPHistMC2->GetXaxis()->SetLabelSize(0.05);

  copyIPHistMC2->Draw("HIST E1"); copyIPHistMC2->SetLineWidth(2); copyIPHistMC2->SetLineColor(kBlue); copyIPHistMC2->GetYaxis()->SetRangeUser(0.6, 1.45);
  copyIPHistMC1->Draw("SAME HIST E1"); copyIPHistMC1->SetLineWidth(2); copyIPHistMC1->SetLineColor(kRed); copyIPHistMC1->GetYaxis()->SetRangeUser(0.6, 1.45); copyIPHistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statIP = (TPaveStats*)copyIPHistMC2->GetListOfFunctions()->FindObject("stats"); 
  statIP->SetOptStat(0);

  TF1 *fa2 = new TF1("fa1","1",0,10);
  fa2->Draw("SAME");
  fa2->SetLineWidth(2);
  fa2->SetLineColor(kBlack);

  Canvas->Print( outName, "pdf");

  //if(intTypeActive) {MultData->GetYaxis()->SetRangeUser(0, 4000);}
  //else {MultData->GetYaxis()->SetRangeUser(0, 6000);}

  MultMC2->GetYaxis()->SetRangeUser(-100, 6100);

  Canvas->cd(1);
  MultData->SetXTitle("Multiplicity");
  HistDraw(MultData, MultMC2, MultMC1);

  Canvas->cd(2);
  copyMultHistMC2->GetYaxis()->SetLabelOffset(0.01);
  copyMultHistMC2->SetXTitle("Multiplicity");
  copyMultHistMC2->SetYTitle("MC / Data");
  copyMultHistMC2->GetYaxis()->SetLabelSize(0.05);
  copyMultHistMC2->GetXaxis()->SetLabelSize(0.05);

  copyMultHistMC2->Draw("HIST E1"); copyMultHistMC2->SetLineWidth(2); copyMultHistMC2->SetLineColor(kBlue); copyMultHistMC2->GetYaxis()->SetRangeUser(0, 2.6);
  copyMultHistMC1->Draw("SAME HIST E1"); copyMultHistMC1->SetLineWidth(2); copyMultHistMC1->SetLineColor(kRed); copyMultHistMC1->GetYaxis()->SetRangeUser(0, 2.6); copyMultHistMC1->SetStats(0);

  gPad->Update();
  TPaveStats *statMult = (TPaveStats*)copyMultHistMC2->GetListOfFunctions()->FindObject("stats"); 
  statMult->SetOptStat(0);

  TF1 *fa3 = new TF1("fa1","1",0,50);
  fa3->Draw("SAME");
  fa3->SetLineWidth(2);
  fa3->SetLineColor(kBlack);

  Canvas->Print( outNameEnd, "pdf");
}

void HistDraw(TH1F *hist1, TH1F *hist2, TH1F *hist3)
{
  Canvas->cd(1);

  hist2->SetStats(0);
  hist2->SetTitle("");
  hist2->Draw("HIST"); hist2->SetLineColor(kBlue); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);
  hist2->GetXaxis()->SetLabelSize(0.05);
  hist2->GetYaxis()->SetLabelSize(0.05);
  hist2->GetXaxis()->SetLabelOffset(0.01);

  hist3->SetStats(0);
  hist3->Draw("SAMES HIST"); hist3->SetLineColor(kRed); hist3->SetLineStyle(1); hist3->SetLineWidth(2); //hist3->SetFillColorAlpha(kMagenta, 0.15);

  hist1->SetStats(0);
  hist1->Draw("SAMES HIST E1"); hist1->SetLineColor(kBlack); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlack, 0.1);
  
  TLegend *legend = new TLegend(0.74, 0.65, 0.97, 0.95);
  legend->AddEntry(hist1,"Data","f");
  legend->AddEntry(hist3,"EPOS_Old","f");
  legend->AddEntry(hist2,"EPOS_New","f");
  legend->Draw();
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

double* MCEndPoints(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double endPoints[2];

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