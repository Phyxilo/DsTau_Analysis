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

TFile *Data;

int subV = 18;

//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

int posXMin = 57000, posXMax = 73000;
int posYMin = 57000, posYMax = 73000;

char dir [128];

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;
vector<int> intVecVertexing;

void HistDraw(TH1F *hist1, TH1F *hist2);

void VertexComp()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    for (int j = 0; j < 8; j++)
    {
        int vtxSmallNum1 = 0, vtxSmallNum2 = 0, vtxLargeNum1 = 0, vtxLargeNum2 = 0;
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

            TLeaf *area1 = parData->GetLeaf("area1");

            TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int Trk = trk->GetValue();
            int Mlt = mlt->GetValue();
            int fp = flagp->GetValue();

            bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
            //bool areaBool = true;

            if (/*(VX > posXMin && VX < posXMax) && (VY > posYMin && VY < posYMax) && */ areaBool && plmax->GetValue() == 5+j*10 /*&& plmin->GetValue() == j*10+1 && pNum->GetValue() == 0*/)
            {
                if (fp == 1)
                {
                    if(Mlt < 10){vtxSmallNum2++;}
                    else{vtxLargeNum2++;}
                }

                if(Mlt < 10){vtxSmallNum1++;}
                else{vtxLargeNum1++;}
            }
        }

        cout << "Plate " << j+1 << ", Vertex (< 10): " << vtxSmallNum1 << ", Vertex (>= 10): " << vtxLargeNum1 << ", Proton Vertex (< 10): " << vtxSmallNum2 << ", Proton Vertex (>= 10): " << vtxLargeNum2 << endl;
    }
}