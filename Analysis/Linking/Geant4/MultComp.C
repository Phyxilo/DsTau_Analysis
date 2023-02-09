#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TLeaf.h"

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Mult1;
TH1F *Mult2;

TFile *Data;

int subV = 0;

char dir [128];

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;
vector<int> intVecVertexing;

void HistDraw(TH1F *hist1, TH1F *hist2);

void MultComp()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    for (int j = 0; j < 7; j++)
    {
        Mult1 = new TH1F("Mlt","Multiplicity",45,5,50);
        Mult2 = new TH1F("Mlt","Multiplicity",45,5,50);
        
        sprintf(outName,"MultComp/MultComp_%d.png", j);
        sprintf(outNameStart,"%s(", outName);
        sprintf(outNameEnd,"%s)", outName);

        char dir [128];
        sprintf(dir,"../../../Geant4SM_v1.0/Linked/RootOut/pl0%d1_%02d0.root", j, j+3);

        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        TTree *vtxData = (TTree*)Data->Get("VTX");
        
        for (int i = 0; i < parData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);

            TLeaf *vx = parData->GetLeaf("vx");
            TLeaf *vy = parData->GetLeaf("vy");
            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *trk = parData->GetLeaf("trk_id");
            TLeaf *mlt = parData->GetLeaf("n_1ry_trk");
            TLeaf *flagp = parData->GetLeaf("flagp");
            TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");
            TLeaf *plmax = parData->GetLeaf("pl_up1ry_plmax");

            TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int Trk = trk->GetValue();
            int Mlt = mlt->GetValue();
            int fp = flagp->GetValue();

            if (plmax->GetValue() == 5+j*10 /*&& plmin->GetValue() == j*10+1 && pNum->GetValue() == 0*/)
            {
                if (fp == 1)
                {
                    Mult2->Fill(Mlt);
                }
                Mult1->Fill(Mlt);
            }

            dataSize++;
        }

        Mult1->Scale(1/dataSize);
        Mult2->Scale(1/dataSize);

        //Mult1->GetYaxis()->SetRangeUser(0, 0.1);
        HistDraw(Mult1, Mult2);
        Canvas->Print(outName, "png");
    }
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("All Multiplicity");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("Primary Interaction Multiplicity");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"All","f");
  legend->AddEntry(hist2,"Primary","f");
  legend->Draw();
}