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

TH2F *noMatch;

TFile *Data;

int subV = 0;

//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

int posXMin = 57000, posXMax = 73000;
int posYMin = 57000, posYMax = 73000;

char dir [128];

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;
vector<int> intVecVertexing;

void NonMatchingVert()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    noMatch = new TH2F("NonMatched","Position Distribution",200,10000,120000,200,10000,90000);

    for (int j = 0; j < 7; j++)
    {
        //noMatch = new TH2F("NonMatched","Position Distribution",200,10000,120000,200,10000,90000);
        //noMatch = new TH2F("NonMatched","Position Distribution",80,56000,74000,80,56000,74000);
        
        sprintf(outName,"NonMatched/NonMatched_%d.png", j);
        sprintf(outNameStart,"%s(", outName);
        sprintf(outNameEnd,"%s)", outName);

        char dir [128];
        sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", j);
        //sprintf(dir,"../../../Data_v20220912/PD05/Linked/Backup/RootOut_3Sigma/p0%d6.root", j);

        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        TTree *vtxData = (TTree*)Data->Get("VTX");
        
        for (int i = 0; i < parData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);
            vtxData->GetEntry(i);

            TLeaf *vx = parData->GetLeaf("vx");
            TLeaf *vy = parData->GetLeaf("vy");
            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *trk = parData->GetLeaf("trk_id");
            TLeaf *mlt = parData->GetLeaf("n_1ry_trk");
            TLeaf *flagp = parData->GetLeaf("flagp");
            TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");
            TLeaf *plmax = parData->GetLeaf("pl_up1ry_plmax");
            TLeaf *area1 = parData->GetLeaf("area1");

            TLeaf *iMed = vtxData->GetLeaf("intMed");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int Trk = trk->GetValue();
            int Mlt = mlt->GetValue();
            int fp = flagp->GetValue();

            bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));
            //bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29) || (area1->GetValue() <= 26 && area1->GetValue() >= 20) || (area1->GetValue() <= 17 && area1->GetValue() >= 11)); //New Method
            //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
            //bool areaBool = area1->GetValue() == 42;
            //bool areaBool = area1->GetValue() == 31;

            if (/*(VX > posXMin && VX < posXMax) && (VY > posYMin && VY < posYMax) &&*/ areaBool && plmax->GetValue() == 5+j*10 /*&& plmin->GetValue() == j*10+2 && pNum->GetValue() == 0*/)
            {
                if (fp == 0)
                {
                    //cout << fixed << trk->GetValue() << endl;

                    noMatch->Fill(VX, VY);
                }
                //Mult1->Fill(Mlt);
            }
            dataSize++;
        }

        gStyle->SetOptStat(0);
        gStyle->SetPalette(kRainBow);

        noMatch->Draw("COLZ");
        Canvas->Print(outName, "png");
    }
}