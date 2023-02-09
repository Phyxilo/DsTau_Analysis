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

//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

int posXMin = 57000, posXMax = 73000;
int posYMin = 57000, posYMax = 73000;

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

void NonMatchedMult()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    for (int j = 0; j < 7; j++)
    {
        Mult1 = new TH1F("Mlt","Not Mathcing Vertices Multiplicity",45,5,50);
        
        sprintf(outName,"NonMatched/Mult_%d.png", j);
        sprintf(outNameStart,"%s(", outName);
        sprintf(outNameEnd,"%s)", outName);

        char dir [128];
        sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", j);

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

            if ((VX > posXMin && VX < posXMax) && (VY > posYMin && VY < posYMax) && plmax->GetValue() == 5+j*10 /*&& plmin->GetValue() == j*10+1 && pNum->GetValue() == 0*/)
            {
                if (fp == 0)
                {
                    Mult1->Fill(Mlt);
                }
            }

            dataSize++;
        }

        Mult1->Draw("HIST");
        Mult1->SetLineColor(kBlue);
        Mult1->SetLineStyle(1);
        Mult1->SetLineWidth(2);

        Canvas->Print(outName, "png");
    }
}