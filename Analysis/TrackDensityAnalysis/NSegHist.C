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

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double* DataPeak(TH1F *data);
double DataMean(TTree *data);
double DataArea(TTree *data);

//For Data dataCorrection == 1.05
//For MC dataCorrection == 1
double dataCorrection = 1.05;
double mcCorrection = 1;

float migCut = 18;

void NSegHist()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

  TH1F *NSegHistDataUSSmaller = new TH1F("NSegDataUSSmall","nseg for Data US (< 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistDataDSSmaller = new TH1F("NSegDataDSSmall","nseg for Data DS (< 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistMCUSSmaller = new TH1F("NSegMCUSSmall","nseg for MC US (< 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistMCDSSmaller = new TH1F("NSegMCDSSmall","nseg for MC DS (< 0.2 rad)",30,-0.5,32.5);
  
  TH1F *NSegHistDataUSLarger = new TH1F("NSegDataUSLarger","nseg for Data US (> 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistDataDSLarger = new TH1F("NSegDataDSLarger","nseg for Data DS (> 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistMCUSLarger = new TH1F("NSegMCUSLarger","nseg for MC US (> 0.2 rad)",30,-0.5,32.5);
  TH1F *NSegHistMCDSLarger = new TH1F("NSegMCDSLarger","nseg for MC DS (> 0.2 rad)",30,-0.5,32.5);

  TH1F *NSegHistDataTot = new TH1F("NSegDataTot","nseg Full Module for Data",30,-0.5,32.5);
  TH1F *NSegHistMCTot = new TH1F("NSegMCTot","nseg Full Module for MC",30,-0.5,32.5);

  TFile *Data, *MC;

  char  outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64, "NSegHist.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  gStyle->SetOptStat(0);

  for (int dirIndex = 0; dirIndex < 8; dirIndex++)
  {
    char dataName [256], MC1Name[256], MC2Name[256], MC3Name[256], MC4Name[256], MC5Name[256];

    snprintf(dataName, 256, "../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", dirIndex);

    if (dirIndex < 7) { snprintf(MC1Name, 256, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC1Name, 256, "../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC2Name, 256, "../../Geant4SM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC2Name, 256, "../../Geant4SM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC3Name, 256, "../../PythiaSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC3Name, 256, "../../PythiaSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC4Name, 256, "../../DPMJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC4Name, 256, "../../DPMJETSM_v2.1/RootOut/pl071_105.root"); }

    if (dirIndex < 7) { snprintf(MC5Name, 256, "../../QGSJETSM_v2.1/RootOut/pl%02d1_%02d0.root", dirIndex, dirIndex + 3); }
    else { snprintf(MC5Name, 256, "../../QGSJETSM_v2.1/RootOut/pl071_105.root"); }

    Data = TFile::Open(dataName);
    MC = TFile::Open(MC1Name);

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeDataVtx = (TTree*)Data->Get("VTX");
    TTree *treeDataPar = (TTree*)Data->Get("PAR");

    double *dataEndArr = DataEndPoints(treeDataVtx);
    double dataMean = DataMean(treeDataVtx);

    TTree *treeMCTrk = (TTree*)MC->Get("TRK");
    TTree *treeMCVtx = (TTree*)MC->Get("VTX");
    TTree *treeMCPar = (TTree*)MC->Get("PAR");

    double *mcEndArr = MCEndPoints(treeMCVtx);
    double mcMean = DataMean(treeMCVtx);

    for (int i = 0; i < treeDataTrk->GetEntriesFast(); i++)
    {
      treeDataTrk->GetEntry(i);

      TLeaf *PN = treeDataTrk->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataTrk->GetLeaf("flagw");
      TLeaf *vID = treeDataTrk->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if (w->GetValue() == 1)
      {
        TLeaf *slpTX = treeDataTrk->GetLeaf("tx");
        TLeaf *slpTY = treeDataTrk->GetLeaf("ty");
        TLeaf *beamTX = treeDataTrk->GetLeaf("txpeak");
        TLeaf *beamTY = treeDataTrk->GetLeaf("typeak");

        double TX = (slpTX->GetValue() - beamTX->GetValue()) * dataCorrection;
        double TY = (slpTY->GetValue() - beamTY->GetValue()) * dataCorrection;
        double T2 = sqrt(TX*TX+TY*TY);

        TLeaf *mlt = treeDataVtx->GetLeaf("n_1ry_trk");
        TLeaf *iType = treeDataVtx->GetLeaf("intType");
        TLeaf *area1 = treeDataVtx->GetLeaf("area1");
        TLeaf *plNum = treeDataVtx->GetLeaf("n_1ry_pl");
        TLeaf *vz = treeDataVtx->GetLeaf("vz");

        TLeaf *nseg = treeDataPar->GetLeaf("nseg");

        treeDataVtx->GetEntry(vtxIndex);
        treeDataPar->GetEntry(vtxIndex);

        bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

        if (iType->GetValue() >= 1 && vz->GetValue() > dataMean - (250-migCut) && vz->GetValue() < dataMean + (250-migCut))
        {
          int segNum = nseg->GetValue();

          if (plNum->GetValue() < 50)
          {
            if (T2 > 0.2) {NSegHistDataUSSmaller->Fill(segNum);}
            else if (T2 < 0.2) {NSegHistDataUSLarger->Fill(segNum);}
          }
          else
          {
            if (T2 > 0.2) {NSegHistDataDSSmaller->Fill(segNum);}
            else if (T2 < 0.2) {NSegHistDataDSLarger->Fill(segNum);}
          }

          NSegHistDataTot->Fill(segNum);
        }
      }
    }

    for (int i = 0; i < treeMCTrk->GetEntriesFast(); i++)
    {
      treeMCTrk->GetEntry(i);

      TLeaf *PN = treeMCTrk->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeMCTrk->GetLeaf("flagw");
      TLeaf *vID = treeMCTrk->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if (w->GetValue() == 1)
      {
        TLeaf *slpTX = treeMCTrk->GetLeaf("tx");
        TLeaf *slpTY = treeMCTrk->GetLeaf("ty");
        TLeaf *beamTX = treeMCTrk->GetLeaf("txpeak");
        TLeaf *beamTY = treeMCTrk->GetLeaf("typeak");

        double TX = (slpTX->GetValue() - beamTX->GetValue()) * mcCorrection;
        double TY = (slpTY->GetValue() - beamTY->GetValue()) * mcCorrection;
        double T2 = sqrt(TX*TX+TY*TY);

        TLeaf *mlt = treeMCVtx->GetLeaf("n_1ry_trk");
        TLeaf *iType = treeMCVtx->GetLeaf("intType");
        TLeaf *area1 = treeMCVtx->GetLeaf("area1");
        TLeaf *plNum = treeMCVtx->GetLeaf("n_1ry_pl");
        TLeaf *vz = treeMCVtx->GetLeaf("vz");

        TLeaf *nseg = treeMCPar->GetLeaf("nseg");

        treeMCVtx->GetEntry(vtxIndex);
        treeMCPar->GetEntry(vtxIndex);

        bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

        if (iType->GetValue() >= 1 && vz->GetValue() > mcMean - (250-migCut) && vz->GetValue() < mcMean + (250-migCut))
        {
          int segNum = nseg->GetValue();

          if (plNum->GetValue() < 50)
          {
            if (T2 > 0.2) {NSegHistMCUSSmaller->Fill(segNum);}
            else if (T2 < 0.2) {NSegHistMCUSLarger->Fill(segNum);}
          }
          else
          {
            if (T2 > 0.2) {NSegHistMCDSSmaller->Fill(segNum);}
            else if (T2 < 0.2) {NSegHistMCDSLarger->Fill(segNum);}
          }

          NSegHistMCTot->Fill(segNum);
        }
      }
    }
  }

  NSegHistDataUSSmaller->SetLineColor(1);
  NSegHistDataDSSmaller->SetLineColor(2);
  NSegHistDataUSLarger->SetLineColor(6);
  NSegHistDataDSLarger->SetLineColor(4);

  NSegHistDataUSSmaller->SetFillColor(1);
  NSegHistDataDSSmaller->SetFillColor(2);
  NSegHistDataUSLarger->SetFillColor(6);
  NSegHistDataDSLarger->SetFillColor(4);

  NSegHistDataUSSmaller->SetFillStyle(3004);
  NSegHistDataDSSmaller->SetFillStyle(3004);
  NSegHistDataUSLarger->SetFillStyle(3004);
  NSegHistDataDSLarger->SetFillStyle(3004);
  
  NSegHistMCUSSmaller->SetLineColor(1);
  NSegHistMCDSSmaller->SetLineColor(2);
  NSegHistMCUSLarger->SetLineColor(6);
  NSegHistMCDSLarger->SetLineColor(4);

  NSegHistMCUSSmaller->SetFillColor(1);
  NSegHistMCDSSmaller->SetFillColor(2);
  NSegHistMCUSLarger->SetFillColor(6);
  NSegHistMCDSLarger->SetFillColor(4);

  NSegHistMCUSSmaller->SetFillStyle(3005);
  NSegHistMCDSSmaller->SetFillStyle(3005);
  NSegHistMCUSLarger->SetFillStyle(3005);
  NSegHistMCDSLarger->SetFillStyle(3005);

  NSegHistDataTot->SetLineColor(kBlack);
  NSegHistMCTot->SetLineColor(kRed);

  // Data US vs DS comparison

  NSegHistDataUSSmaller->SetTitle("nseg for Data (< 0.2 rad) - US vs DS; nseg");
  NSegHistDataUSSmaller->Draw();
  NSegHistDataDSSmaller->Draw("SAMES");

  TLegend *legend1 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend1->AddEntry(NSegHistDataUSSmaller,"Upstream","f");
  legend1->AddEntry(NSegHistDataDSSmaller,"Downstream","f");
  legend1->Draw();

  Canvas->Print(outNameStart, "pdf");

  NSegHistDataUSLarger->SetTitle("nseg for Data (> 0.2 rad) - US vs DS; nseg");
  NSegHistDataUSLarger->Draw();
  NSegHistDataDSLarger->Draw("SAMES");

  TLegend *legend2 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend2->AddEntry(NSegHistDataUSLarger,"Upstream","f");
  legend2->AddEntry(NSegHistDataDSLarger,"Downstream","f");
  legend2->Draw();

  Canvas->Print(outName, "pdf");

  // MC US vs DS comparison

  NSegHistMCUSSmaller->SetTitle("nseg for MC (< 0.2 rad) - US vs DS; nseg");
  NSegHistMCUSSmaller->Draw();
  NSegHistMCDSSmaller->Draw("SAMES");

  TLegend *legend3 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend3->AddEntry(NSegHistMCUSSmaller,"Upstream","f");
  legend3->AddEntry(NSegHistMCDSSmaller,"Downstream","f");
  legend3->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistDataUSLarger->SetTitle("nseg for MC (> 0.2 rad) - US vs DS; nseg");
  NSegHistDataUSLarger->Draw();
  NSegHistDataDSLarger->Draw("SAMES");

  TLegend *legend4 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend4->AddEntry(NSegHistDataUSLarger,"Upstream","f");
  legend4->AddEntry(NSegHistDataDSLarger,"Downstream","f");
  legend4->Draw();

  Canvas->Print(outName, "pdf");

  // Data Smaller vs Larger comparison

  NSegHistDataUSLarger->SetTitle("nseg for Data US - (< 0.2 rad) vs (> 0.2rad); nseg");
  NSegHistDataUSLarger->Draw();
  NSegHistDataUSSmaller->Draw("SAMES");

  TLegend *legend9 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend9->AddEntry(NSegHistDataUSLarger,"T2 > 0.2 rad","f");
  legend9->AddEntry(NSegHistDataUSSmaller,"T2 < 0.2 rad","f");
  legend9->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistDataDSLarger->SetTitle("nseg for Data DS - (< 0.2 rad) vs (> 0.2 rad); nseg");
  NSegHistDataDSLarger->Draw();
  NSegHistDataDSSmaller->Draw("SAMES");

  TLegend *legend10 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend10->AddEntry(NSegHistDataDSLarger,"T2 > 0.2 rad","f");
  legend10->AddEntry(NSegHistDataDSSmaller,"T2 < 0.2 rad","f");
  legend10->Draw();

  Canvas->Print(outName, "pdf");

  // MC Smaller vs Larger comparison

  NSegHistMCUSLarger->SetTitle("nseg for MC US - (< 0.2 rad) vs (> 0.2 rad); nseg");
  NSegHistMCUSLarger->Draw();
  NSegHistMCUSSmaller->Draw("SAMES");

  TLegend *legend11 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend11->AddEntry(NSegHistMCUSLarger,"T2 > 0.2 rad","f");
  legend11->AddEntry(NSegHistMCUSSmaller,"T2 < 0.2 rad","f");
  legend11->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistMCDSLarger->SetTitle("nseg for MC DS - (< 0.2 rad) vs (> 0.2 rad); nseg");
  NSegHistMCDSLarger->Draw();
  NSegHistMCDSSmaller->Draw("SAMES");

  TLegend *legend12 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend12->AddEntry(NSegHistMCDSLarger,"T2 > 0.2 rad","f");
  legend12->AddEntry(NSegHistMCDSSmaller,"T2 < 0.2 rad","f");
  legend12->Draw();

  Canvas->Print(outName, "pdf");

  // Data vs MC US comparison

  NSegHistMCUSSmaller->Scale(NSegHistDataUSSmaller->Integral()/NSegHistMCUSSmaller->Integral());

  NSegHistDataUSSmaller->SetTitle("nseg for US (< 0.2 rad) - Data vs MC; nseg");
  NSegHistDataUSSmaller->Draw("HIST");
  NSegHistMCUSSmaller->Draw("SAMES");

  TLegend *legend5 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend5->AddEntry(NSegHistDataUSSmaller,"Data","f");
  legend5->AddEntry(NSegHistMCUSSmaller,"MC","f");
  legend5->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistMCUSLarger->Scale(NSegHistDataUSLarger->Integral()/NSegHistMCUSLarger->Integral());

  NSegHistDataUSLarger->SetTitle("nseg for US (> 0.2 rad) - Data vs MC; nseg");
  NSegHistDataUSLarger->Draw("HIST");
  NSegHistMCUSLarger->Draw("SAMES");

  TLegend *legend6 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend6->AddEntry(NSegHistDataUSLarger,"Data","f");
  legend6->AddEntry(NSegHistMCUSLarger,"MC","f");
  legend6->Draw();

  Canvas->Print(outName, "pdf");

  // Data vs MC DS comparison

  NSegHistMCDSSmaller->Scale(NSegHistDataDSSmaller->Integral()/NSegHistMCDSSmaller->Integral());

  NSegHistDataDSSmaller->SetTitle("nseg for DS (< 0.2 rad) - Data vs MC; nseg");
  NSegHistDataDSSmaller->Draw("HIST");
  NSegHistMCDSSmaller->Draw("SAMES");

  TLegend *legend7 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend7->AddEntry(NSegHistDataDSSmaller,"Data","f");
  legend7->AddEntry(NSegHistMCDSSmaller,"MC","f");
  legend7->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistMCDSLarger->Scale(NSegHistDataDSLarger->Integral()/NSegHistMCDSLarger->Integral());

  NSegHistDataDSLarger->SetTitle("nseg for DS (> 0.2 rad) - Data vs MC; nseg");
  NSegHistDataDSLarger->Draw("HIST");
  NSegHistMCDSLarger->Draw("SAMES");

  TLegend *legend8 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend8->AddEntry(NSegHistDataDSLarger,"Data","f");
  legend8->AddEntry(NSegHistMCDSLarger,"MC","f");
  legend8->Draw();

  Canvas->Print(outName, "pdf");

  NSegHistDataTot->SetTitle("nseg - Data vs MC; nseg");
  NSegHistDataTot->Draw();
  NSegHistMCTot->Draw("SAMES");

  TLegend *legend13 = new TLegend(0.28, 0.85, 0.08, 0.95);
  legend13->AddEntry(NSegHistDataTot,"Data","f");
  legend13->AddEntry(NSegHistMCTot,"MC","f");
  legend13->Draw();

  Canvas->Print( outNameEnd, "pdf");
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

    if (parNum->GetValue() == 1 /*&& areaBool*/)
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

double DataArea(TTree *data)
{
  TH1F *InterHistX = new TH1F("InterHistX","Vertex X",50000,-50000,50000);
  TH1F *InterHistY = new TH1F("InterHistY","Vertex Y",50000,50000,50000);

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vx = data->GetLeaf("vx");
    TLeaf *vy = data->GetLeaf("vy");
    TLeaf *w = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (w->GetValue() == 1)
      {
        InterHistX->Fill(vx->GetValue()/10000);
        InterHistY->Fill(vy->GetValue()/10000);
      }
    }
  }

  double deltaX = InterHistX->FindFirstBinAbove(0)-InterHistX->FindLastBinAbove(0);
  double deltaY = InterHistY->FindFirstBinAbove(0)-InterHistY->FindLastBinAbove(0);
  double area = deltaX*deltaY;

  return area;
}

double* DataPeak(TH1F *data)
{
  int numBins = data->GetXaxis()->GetNbins();
  static double out[2];

  double *x = new double[numBins];
  double *y = new double[numBins];

  double peakX = 0, peakY = 0;

  for (int i = 0; i < numBins; i++) 
  {
    double x = data->GetBinCenter(i);
    double y = data->GetBinContent(i);
    
    if (peakY < y)
    {
      peakY = y;
      peakX = x;

      out[0] = peakX;
      out[1] = peakY;
    }
  }

  return out;
}