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

void HistDraw(TH1F *hist1, TH1F *hist2);

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHistData = new TH1F("TXData","",50,-0.4,0.4);
TH1F *SlpTXHistMC1 = new TH1F("TXMC","",50,-0.4,0.4);

TH1F *SlpTYHistData = new TH1F("TYData","",50,-0.4,0.4);
TH1F *SlpTYHistMC1 = new TH1F("TYMC","",50,-0.4,0.4);

TH1F *SlpT2HistData = new TH1F("T2Data","",50,0,0.34);
TH1F *SlpT2HistMC1 = new TH1F("T2MC","",50,0,0.34);

TH1F *IPDataData = new TH1F("IPData","",25,0,5.8);
TH1F *IPDataMC1 = new TH1F("IPMC","",25,0,5.8);

TH1F *MultData = new TH1F("MultData","",33,5,38);
TH1F *MultMC1 = new TH1F("MultMC","",33,5,38);

TFile *Data, *MC1;

float DataVtxSize = 0, MC1VtxSize = 0;

bool intTypeActive = true;

double dataCorrection = 0.95;
float migCut = 18;

void MCDataCompEPOSKolmogorov()
{
  char  outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64, "MCDataCompEPOSKolmogorov.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    cout << "Processing subvolume " << dirIndex << endl;

    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    snprintf(dataName, 256, "../../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", dirIndex);
    
    if (dirIndex < 7) { snprintf(MC1Name, 256, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC1Name, 256, "../../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC2Name, 256, "../../../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC2Name, 256, "../../../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC3Name, 256, "../../../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC3Name, 256, "../../../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC4Name, 256, "../../../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC4Name, 256, "../../../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC5Name, 256, "../../../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC5Name, 256, "../../../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data = TFile::Open(dataName);
    MC1 = TFile::Open(MC1Name);

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeMCTrk1 = (TTree*)MC1->Get("TRK");

    TTree *treeDataVtx = (TTree*)Data->Get("VTX");
    TTree *treeMCVtx1 = (TTree*)MC1->Get("VTX");

    int dataTrkInd = 0, MC1TrkInd = 0;
    double initZ, lastZ;
    double *dataEndArr, *MC1EndArr;
    double dataMean, MC1Mean;

    dataEndArr = DataEndPoints(treeDataVtx);
    MC1EndArr = MCEndPoints(treeMCVtx1);

    dataMean = DataMean(treeDataVtx);
    MC1Mean = DataMean(treeMCVtx1);

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
  }

  SlpTXHistMC1->Scale(SlpTXHistData->Integral()/SlpTXHistMC1->Integral());
  SlpTYHistMC1->Scale(SlpTYHistData->Integral()/SlpTYHistMC1->Integral());

  for (int i = 1; i <= SlpT2HistData->GetNbinsX(); i++) {
      double content = SlpT2HistData->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      SlpT2HistData->SetBinError(i, error);
  }
  for (int i = 1; i <= SlpT2HistMC1->GetNbinsX(); i++) {
      double content = SlpT2HistMC1->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      SlpT2HistMC1->SetBinError(i, error);
  }
  // SlpT2HistData->Rebin(5);
  // SlpT2HistMC1->Rebin(5);

  for (int i = 1; i <= IPDataData->GetNbinsX(); i++) {
      double content = IPDataData->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      IPDataData->SetBinError(i, error);
  }
  for (int i = 1; i <= IPDataMC1->GetNbinsX(); i++) {
      double content = IPDataMC1->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      IPDataMC1->SetBinError(i, error);
  }
  // IPDataData->Rebin(5);
  // IPDataMC1->Rebin(5);

  for (int i = 1; i <= MultData->GetNbinsX(); i++) {
      double content = MultData->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      MultData->SetBinError(i, error);
  }
  for (int i = 1; i <= MultMC1->GetNbinsX(); i++) {
      double content = MultMC1->GetBinContent(i);
      double error = sqrt(content);  // Poisson error
      MultMC1->SetBinError(i, error);
  }
  // MultData->Rebin(3);
  // MultMC1->Rebin(3);

  SlpT2HistMC1->Scale(SlpT2HistData->Integral()/SlpT2HistMC1->Integral());
  IPDataMC1->Scale(IPDataData->Integral()/IPDataMC1->Integral());
  MultMC1->Scale(DataVtxSize/MC1VtxSize);
  
  double kolmogorovProbT2 = SlpT2HistData->KolmogorovTest(SlpT2HistMC1, "XU");
  cout << "Kolmogorov test probability: " << kolmogorovProbT2 << endl;

  double kolmogorovProbIP = IPDataData->KolmogorovTest(IPDataMC1, "XU");
  cout << "Kolmogorov test probability: " << kolmogorovProbIP << endl;

  double kolmogorovProbMult = MultData->KolmogorovTest(MultMC1, "XU");
  cout << "Kolmogorov test probability: " << kolmogorovProbMult << endl;

  //if(intTypeActive) {SlpT2HistData->GetYaxis()->SetRangeUser(0, 150000);}
  //else {SlpT2HistData->GetYaxis()->SetRangeUser(0, 220000);}

  if(compType == 2) {SlpT2HistMC1->GetYaxis()->SetRangeUser(-1000, 36000);}
  else {SlpT2HistMC1->GetYaxis()->SetRangeUser(-5000, 185000);}

  cout << SlpT2HistData->GetMean() << endl;

  gPad->SetGrid(100);
  SlpT2HistData->SetXTitle("Tan #theta");
  HistDraw(SlpT2HistData, SlpT2HistMC1);

  Canvas->Print(outNameStart, "pdf");

  //if(intTypeActive) {IPDataData->GetYaxis()->SetRangeUser(0, 400000);}
  //else {IPDataData->GetYaxis()->SetRangeUser(0, 580000);}

  IPDataMC1->GetYaxis()->SetRangeUser(-10000, 460000);

  IPDataData->SetXTitle("Impact Parameter (#mum)");
  HistDraw(IPDataData, IPDataMC1);

  Canvas->Print(outName, "pdf");

  //if(intTypeActive) {MultData->GetYaxis()->SetRangeUser(0, 4000);}
  //else {MultData->GetYaxis()->SetRangeUser(0, 6000);}

  MultMC1->GetYaxis()->SetRangeUser(-100, 6100);

  MultData->SetXTitle("Multiplicity");
  HistDraw(MultData, MultMC1);

  Canvas->Print(outNameEnd, "pdf");

  // double pValue1 = SlpT2HistData->Chi2Test(SlpT2HistMC1, "CHI2/NDF");
  // cout << pValue1 << endl;

  // double pValue2 = IPDataData->Chi2Test(IPDataMC1, "CHI2/NDF");
  // cout << pValue2 << endl;

  // double pValue3 = MultData->Chi2Test(MultMC1, "CHI2/NDF");
  // cout << pValue3 << endl;

  // double pValue1 = SlpT2HistData->KolmogorovTest(SlpT2HistMC1, "U N O");
  // cout << pValue1 << endl;

  // double pValue2 = IPDataData->KolmogorovTest(IPDataMC1, "U N O");
  // cout << pValue2 << endl;

  // double pValue3 = MultData->KolmogorovTest(MultMC1, "U N O");
  // cout << pValue3 << endl;
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{
  Canvas->cd(1);

  hist1->SetStats(0);
  hist1->SetTitle("");
  hist1->Draw("HIST E1"); hist2->SetLineColor(kBlue); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist1->SetFillColorAlpha(kRed, 0.2);
  hist1->GetXaxis()->SetLabelSize(0.05);
  hist1->GetYaxis()->SetLabelSize(0.05);
  hist1->GetXaxis()->SetLabelOffset(0.01);

  hist2->SetStats(0);
  hist2->Draw("SAMES HIST E1"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kMagenta, 0.15);
  
  TLegend *legend = new TLegend(0.74, 0.70, 0.97, 0.95);
  legend->AddEntry(hist1,"Data","f");
  legend->AddEntry(hist2,"EPOS","f");
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