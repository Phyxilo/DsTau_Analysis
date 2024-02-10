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

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Hist1_1 = new TH1F("Hist1 > 25","Multiplicity",50,0,50);
TH1F *Hist1_2 = new TH1F("Hist2 > 25","Space Angle",50,0,0.4);
TH1F *Hist1_3 = new TH1F("Hist3 > 25","Z Distribution",500,0,500);
TH2F *Hist1_4 = new TH2F("Hist4 > 25","XY Distribution > 25",200,10000,120000,200,10000,90000);

TH1F *Hist2_1 = new TH1F("Hist1 < 25","Multiplicity",50,0,50);
TH1F *Hist2_2 = new TH1F("Hist2 < 25","Space Angle",50,0,0.4);
TH1F *Hist2_3 = new TH1F("Hist3 < 25","Z Distribution",500,0,500);
TH2F *Hist2_4 = new TH2F("Hist4 < 25","XY Distribution < 25",200,10000,120000,200,10000,90000);

TFile *Data1;

float Data1VtxSize = 0;

void FineAlignmentAnalsis()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  //gStyle->SetOptStat(0);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"FineAlignAnalysis.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  for (int x = 0; x < 8; x++)
  {
    TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

    char inName[64];
    sprintf(inName, "../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", x);
    Data1 = TFile::Open(inName);
    
    TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
    TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
    
    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);
      
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");
      TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");

      if (parNum->GetValue() == 1)
      {
        if (intMedium->GetValue() == 1)
        {
          InterHist->Fill(vz->GetValue());
        }
      }
    }

    double initZ = InterHist->FindFirstBinAbove(0);
    double lastZ = InterHist->FindLastBinAbove(0);

    for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
    {
      treeDataTrk1->GetEntry(i);
      
      TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
      TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
      TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
      TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");
      TLeaf *IP = treeDataTrk1->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = treeDataTrk1->GetLeaf("vID");
      TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = treeDataTrk1->GetLeaf("flagw");

      treeDataVtx1->GetEntry(vID->GetValue());

      TLeaf *vz = treeDataVtx1->GetLeaf("vz");
      TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *flagw = treeDataVtx1->GetLeaf("flagw");
      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");

      if (parNum->GetValue() == 1)
      {
        if (intMedium->GetValue() == 1)
        {
          //if (vz->GetValue() - initZ < 25 || vz->GetValue() - initZ > 475)
          if (vz->GetValue() - initZ > 25 && vz->GetValue() - initZ < 475)
          {
            double TX = slpTX->GetValue() - beamTX->GetValue();
            double TY = slpTY->GetValue() - beamTY->GetValue();
            
            Hist1_2->Fill(sqrt(TX*TX+TY*TY));
          }
          else 
          {
            double TX = slpTX->GetValue() - beamTX->GetValue();
            double TY = slpTY->GetValue() - beamTY->GetValue();
            
            Hist2_2->Fill(sqrt(TX*TX+TY*TY));
          }
        }
      }
    }

    for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
    {
      treeDataVtx1->GetEntry(i);
      
      TLeaf *vx = treeDataVtx1->GetLeaf("vx");
      TLeaf *vy = treeDataVtx1->GetLeaf("vy");
      TLeaf *vz = treeDataVtx1->GetLeaf("vz");
      TLeaf *intMedium = treeDataVtx1->GetLeaf("intMed");
      TLeaf *area1 = treeDataVtx1->GetLeaf("area1");
      TLeaf *parNum = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *flagw = treeDataVtx1->GetLeaf("flagw");
      TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");

      if (parNum->GetValue() == 1)
      {
        if (intMedium->GetValue() == 1 /*flagw->GetValue() == 1*/)
        {
          //if (vz->GetValue() - initZ < 25 || vz->GetValue() - initZ > 475)
          if (vz->GetValue() - initZ > 25 && vz->GetValue() - initZ < 475)
          {
            Hist1_1->Fill(mult->GetValue());
            Hist1_3->Fill(vz->GetValue() - initZ);
            Hist1_4->Fill(vx->GetValue(), vy->GetValue());
          }
          else
          {
            Hist2_1->Fill(mult->GetValue());
            Hist2_3->Fill(vz->GetValue() - initZ);
            Hist2_4->Fill(vx->GetValue(), vy->GetValue());
          }
        }
      }
    }

    cout << InterHist->FindLastBinAbove(0) - InterHist->FindFirstBinAbove(0) << endl;
    delete InterHist;
  }

  Hist1_1->Draw("HIST E1");
  Hist1_1->SetLineColor(kRed);
  Hist1_1->Scale(1/Hist1_1->Integral());
  Hist1_1->GetYaxis()->SetRangeUser(0, 0.06);

  Canvas->Modified(); 
  Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName(">25");
  StatBox1->SetY1NDC(0.95);
  StatBox1->SetY2NDC(0.75);
  StatBox1->SetTextColor(kRed);
  StatBox1->Draw();

  Hist2_1->Draw("SAMES HIST E1");
  Hist2_1->SetLineColor(kBlue);
  Hist2_1->Scale(1/Hist2_1->Integral());

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("<25");
  StatBox2->SetY1NDC(0.75);
  StatBox2->SetY2NDC(0.55);
  StatBox2->SetTextColor(kBlue);
  StatBox2->Draw();

  Canvas->Print( outNameStart, "pdf");

  Hist1_2->Draw("HIST E1");
  Hist1_2->SetLineColor(kRed);
  Hist1_2->Scale(1/Hist1_2->Integral());

  Canvas->Modified(); 
  Canvas->Update();
  TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox3->SetName(">25");
  StatBox3->SetY1NDC(0.95);
  StatBox3->SetY2NDC(0.75);
  StatBox3->SetTextColor(kRed);
  StatBox3->Draw();

  Hist2_2->Draw("SAMES HIST E1");
  Hist2_2->SetLineColor(kBlue);
  Hist2_2->Scale(1/Hist2_2->Integral());

  Canvas->Update();
  TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox4->SetName("<25");
  StatBox4->SetY1NDC(0.75);
  StatBox4->SetY2NDC(0.55);
  StatBox4->SetTextColor(kBlue);
  StatBox4->Draw();

  Canvas->Print( outName, "pdf");

  Hist1_3->Draw("HIST");
  Hist1_3->SetLineColor(kRed);
  //Hist1_3->Scale(1/Hist1_3->Integral());

  Canvas->Modified(); 
  Canvas->Update();
  TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox5->SetName(">25");
  StatBox5->SetY1NDC(0.45);
  StatBox5->SetY2NDC(0.25);
  StatBox5->SetTextColor(kRed);
  StatBox5->Draw();

  Hist2_3->Draw("SAMES HIST");
  Hist2_3->SetLineColor(kBlue);
  //Hist2_3->Scale(1/Hist2_3->Integral());

  Canvas->Update();
  TPaveStats *StatBox6 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox6->SetName("<25");
  StatBox6->SetY1NDC(0.25);
  StatBox6->SetY2NDC(0.05);
  StatBox6->SetTextColor(kBlue);
  StatBox6->Draw();

  Canvas->Print( outName, "pdf");

  Hist1_4->Draw();
  Canvas->Print( outName, "pdf");

  Hist2_4->Draw();
  Canvas->Print( outNameEnd, "pdf");

  Hist1_1->Chi2Test(Hist2_1, "WW P");
}