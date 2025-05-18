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
//double dataCorrection = 1;

float migCut = 18;

void SlopeHist()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  //Canvas->SetWindowSize(800, 800);

  TH1F *ThetaHist1 = new TH1F("Theta1","Theta for Sub-volume 1",50,0.0,0.4);
  TH1F *ThetaHist2 = new TH1F("Theta2","Theta for Sub-volume 2",50,0.0,0.4);
  TH1F *ThetaHist3 = new TH1F("Theta3","Theta for Sub-volume 3",50,0.0,0.4);
  TH1F *ThetaHist4 = new TH1F("Theta4","Theta for Sub-volume 4",50,0.0,0.4);
  TH1F *ThetaHist5 = new TH1F("Theta5","Theta for Sub-volume 5",50,0.0,0.4);
  TH1F *ThetaHist6 = new TH1F("Theta6","Theta for Sub-volume 6",50,0.0,0.4);
  TH1F *ThetaHist7 = new TH1F("Theta7","Theta for Sub-volume 7",50,0.0,0.4);
  TH1F *ThetaHist8 = new TH1F("Theta8","Theta for Sub-volume 8",50,0.0,0.4);

  TH1F *ThetaHistTot = new TH1F("ThetaTot","Theta Full Module",50,0,0.4);

  TFile *Data, *MC1, *MC2, *MC3, *MC4;

  TH1F *HistArr[8] = {ThetaHist1, ThetaHist2, ThetaHist3, ThetaHist4, ThetaHist5, ThetaHist6, ThetaHist7, ThetaHist8};

  char  outName[64], outNameStart[64], outNameEnd[64];
  snprintf(outName, 64, "SlopeSeg.pdf");
  snprintf(outNameStart, 64, "%s(", outName);
  snprintf(outNameEnd, 64, "%s)", outName);

  gStyle->SetOptStat(0);
  gStyle->SetPalette(kRainBow);

  int vtxSize = 0;
  float scaleFactor = 1/125;

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

    TTree *treeDataTrk = (TTree*)Data->Get("TRK");
    TTree *treeDataVtx = (TTree*)Data->Get("VTX");
    TTree *treeDataPar = (TTree*)Data->Get("PAR");

    double *dataEndArr = DataEndPoints(treeDataVtx);
    //double *dataEndArr = MCEndPoints(treeDataVtx);
    double mean = DataMean(treeDataVtx);

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
        TLeaf *vz = treeDataVtx->GetLeaf("vz");

        TLeaf *nseg = treeDataPar->GetLeaf("nseg");

        treeDataVtx->GetEntry(vtxIndex);
        treeDataPar->GetEntry(vtxIndex);

        ThetaHistTot->Fill(T2);
        HistArr[dirIndex]->Fill(T2);

        bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));

        //if (areaBool == 1 && iType->GetValue() >= 1 && vz->GetValue() - dataEndArr[0] > migCut && vz->GetValue() - dataEndArr[1] < -migCut)
        if (/*areaBool == 1 &&*/ iType->GetValue() >= 1 && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
        {
          //ThetaHistTot->Fill(nseg->GetValue(), T2);
          //HistArr[dirIndex]->Fill(nseg->GetValue(), T2);

          vtxSize++;
        }
      }
    }

      HistArr[dirIndex]->SetContour(20);
      //HistArr[dirIndex]->Scale(scaleFactor);

      HistArr[dirIndex]->Draw();
      //MultThetaHistTot->SetMinimum(0);
      //MultThetaHistTot->SetMaximum(100);
      //MultThetaHistTot->SetTitle("");
      HistArr[dirIndex]->SetXTitle("Tan #theta");
      HistArr[dirIndex]->SetYTitle("Number of Tracks");

    if (dirIndex == 0) {Canvas->Print(outNameStart, "pdf");}
    else {Canvas->Print(outName, "pdf");}
  }

  double Hist0Peak = DataPeak(HistArr[0])[1];
  HistArr[0]->SetContour(20);
  HistArr[0]->SetTitle("Theta for All Sub-volumes");
  HistArr[0]->Draw();
  HistArr[0]->SetLineColor(1);

  HistArr[1]->Draw("SAMES");
  HistArr[1]->SetLineColor(2);
  HistArr[1]->Scale(Hist0Peak/DataPeak(HistArr[1])[1]);

  HistArr[2]->Draw("SAMES");
  HistArr[2]->SetLineColor(3);
  HistArr[2]->Scale(Hist0Peak/DataPeak(HistArr[2])[1]);

  HistArr[3]->Draw("SAMES");
  HistArr[3]->SetLineColor(4);
  HistArr[3]->Scale(Hist0Peak/DataPeak(HistArr[3])[1]);

  HistArr[4]->Draw("SAMES");
  HistArr[4]->SetLineColor(6);
  HistArr[4]->Scale(Hist0Peak/DataPeak(HistArr[4])[1]);

  HistArr[5]->Draw("SAMES");
  HistArr[5]->SetLineColor(7);
  HistArr[5]->Scale(Hist0Peak/DataPeak(HistArr[5])[1]);

  HistArr[6]->Draw("SAMES");
  HistArr[6]->SetLineColor(11);
  HistArr[6]->Scale(Hist0Peak/DataPeak(HistArr[6])[1]);

  TLegend *legend = new TLegend(0.74, 0.6, 0.97, 0.95);
  legend->AddEntry(HistArr[0],"Sub-volume 1","f");
  legend->AddEntry(HistArr[1],"Sub-volume 2","f");
  legend->AddEntry(HistArr[2],"Sub-volume 3","f");
  legend->AddEntry(HistArr[3],"Sub-volume 4","f");
  legend->AddEntry(HistArr[4],"Sub-volume 5","f");
  legend->AddEntry(HistArr[5],"Sub-volume 6","f");
  legend->AddEntry(HistArr[6],"Sub-volume 7","f");
  legend->Draw();

  Canvas->Print(outName, "pdf");

  TH1F *Hist0Small = (TH1F*) HistArr[0]->Clone();
  TH1F *Hist1Small = (TH1F*) HistArr[1]->Clone();
  TH1F *Hist2Small = (TH1F*) HistArr[2]->Clone();
  TH1F *Hist3Small = (TH1F*) HistArr[3]->Clone();
  TH1F *Hist4Small = (TH1F*) HistArr[4]->Clone();
  TH1F *Hist5Small = (TH1F*) HistArr[5]->Clone();
  TH1F *Hist6Small = (TH1F*) HistArr[6]->Clone();

  TH1F *Hist0Greater = (TH1F*) HistArr[0]->Clone();
  TH1F *Hist1Greater = (TH1F*) HistArr[1]->Clone();
  TH1F *Hist2Greater = (TH1F*) HistArr[2]->Clone();
  TH1F *Hist3Greater = (TH1F*) HistArr[3]->Clone();
  TH1F *Hist4Greater = (TH1F*) HistArr[4]->Clone();
  TH1F *Hist5Greater = (TH1F*) HistArr[5]->Clone();
  TH1F *Hist6Greater = (TH1F*) HistArr[6]->Clone();

  Hist0Small->GetXaxis()->SetRangeUser(0, 0.2);
  Hist0Greater->GetXaxis()->SetRangeUser(0.2, 0.4);

  Hist0Small->SetContour(20);
  Hist0Small->SetTitle("Data Track Slopes for All Sub-volumes (< 0.20 rad)");
  Hist0Small->Draw();
  Hist0Small->SetLineColor(1);

  Hist1Small->Draw("SAMES");
  Hist1Small->SetLineColor(2);

  Hist2Small->Draw("SAMES");
  Hist2Small->SetLineColor(3);

  Hist3Small->Draw("SAMES");
  Hist3Small->SetLineColor(4);

  Hist4Small->Draw("SAMES");
  Hist4Small->SetLineColor(6);

  Hist5Small->Draw("SAMES");
  Hist5Small->SetLineColor(7);

  Hist6Small->Draw("SAMES");
  Hist6Small->SetLineColor(11);

  TLegend *legend1 = new TLegend(0.74, 0.6, 0.97, 0.95);
  legend1->AddEntry(Hist0Small,"Sub-volume 1","f");
  legend1->AddEntry(Hist1Small,"Sub-volume 2","f");
  legend1->AddEntry(Hist2Small,"Sub-volume 3","f");
  legend1->AddEntry(Hist3Small,"Sub-volume 4","f");
  legend1->AddEntry(Hist4Small,"Sub-volume 5","f");
  legend1->AddEntry(Hist5Small,"Sub-volume 6","f");
  legend1->AddEntry(Hist6Small,"Sub-volume 7","f");
  legend1->Draw();

  Canvas->Print(outName, "pdf");

  Hist0Greater->SetContour(20);
  Hist0Greater->SetTitle("Data Track Slopes for All Sub-volumes (> 0.20 rad)");
  Hist0Greater->Draw();
  Hist0Greater->SetLineColor(1);

  Hist1Greater->Draw("SAMES");
  Hist1Greater->SetLineColor(2);

  Hist2Greater->Draw("SAMES");
  Hist2Greater->SetLineColor(3);

  Hist3Greater->Draw("SAMES");
  Hist3Greater->SetLineColor(4);

  Hist4Greater->Draw("SAMES");
  Hist4Greater->SetLineColor(6);

  Hist5Greater->Draw("SAMES");
  Hist5Greater->SetLineColor(7);

  Hist6Greater->Draw("SAMES");
  Hist6Greater->SetLineColor(11);

  TLegend *legend2 = new TLegend(0.74, 0.6, 0.97, 0.95);
  legend2->AddEntry(Hist0Greater,"Sub-volume 1","f");
  legend2->AddEntry(Hist1Greater,"Sub-volume 2","f");
  legend2->AddEntry(Hist2Greater,"Sub-volume 3","f");
  legend2->AddEntry(Hist3Greater,"Sub-volume 4","f");
  legend2->AddEntry(Hist4Greater,"Sub-volume 5","f");
  legend2->AddEntry(Hist5Greater,"Sub-volume 6","f");
  legend2->AddEntry(Hist6Greater,"Sub-volume 7","f");
  legend2->Draw();

  Canvas->Print(outName, "pdf");

  ThetaHistTot->SetContour(20);
  //ThetaHistTot->Scale(scaleFactor);

  ThetaHistTot->Draw();
  //ThetaHistTot->SetMinimum(0);
  //ThetaHistTot->SetMaximum(100);
  //ThetaHistTot->SetTitle("");
  ThetaHistTot->SetXTitle("Tan #theta");
  ThetaHistTot->SetYTitle("Number of Tracks");

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