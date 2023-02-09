#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas;

TGraph *IntRatioGraph = new TGraph (7);

TFile *Data;

float linkedProton[8] = 
{
    236286, 
    204247, 
    189037, 
    174759, 
    160534, 
    146232, 
    132456, 
    117580
};
/*
float linkedProton[8] = 
{
    215879, 
    198611, 
    184469, 
    170625, 
    156658, 
    142552, 
    128711, 
    113519
};
*/
float dirArr[8];
float intRatio1[8], intRatio2[8];
float err1X[8], err1Y[8], err2X[8], err2Y[8];

int subV = 0;
//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

int posXMin = 57000, posXMax = 73000;
int posYMin = 57000, posYMax = 73000;

char dir [128];

void IntRatio()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    sprintf(outName,"IntRatio.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int j = 0; j < 7; j++)
    {
        int IntPar1 = 0, IntPar2 = 0, TotalPar = 0;

        //sprintf(dir,"../../../Geant4SM_v1.0/RootOut/pl0%d1_%02d0.root", j, j+3);
        sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", j);

        cout << dir << endl;

        //Data = TFile::Open("../Root/Geant4_p006.root");
        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        TTree *vtxData = (TTree*)Data->Get("VTX");
        TTree *ptrkData = (TTree*)Data->Get("US_PTRK");
        
        for (int i = 0; i < parData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);
            vtxData->GetEntry(i);

            TLeaf *vx = parData->GetLeaf("vx");
            TLeaf *vy = parData->GetLeaf("vy");
            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *flagp = parData->GetLeaf("flagp");
            TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");

            TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int fp = flagp->GetValue();

            if ((VX > posXMin && VX < posXMax) && (VY > posYMin && VY < posYMax)/* && plmin->GetValue() == j*10+1 && pNum->GetValue() == 1*/)
            {
                if (Plt >= 5 + j*10 && Plt < 10 + j*10)
                {                    
                    IntPar2++;
                }
                if (fp == 1)
                {
                    IntPar1++;
                }

                TotalPar++;  
            }
        }

        //float ratio1 = ((float)IntPar1/linkedProton[j])*100;
        //float ratio2 = ((float)TotalPar/linkedProton[j])*100;

        float ratio1 = ((float)IntPar1/ptrkData->GetEntriesFast())*100;
        float ratio2 = ((float)TotalPar/ptrkData->GetEntriesFast())*100;

        intRatio1[j] = ratio1;
        intRatio2[j] = ratio2;

        IntRatioGraph->SetPoint(j, j, ratio1/ratio2);

        dirArr[j] = j;

        err1X[j] = 0; err2X[j] = 0;
        
        err1Y[j] = ((1-ratio1)/IntPar1)*100;
        err2Y[j] = ((1-ratio2)/TotalPar)*100;

        cout << "Int: " << IntPar1 << ", Total: " << linkedProton[j] << ", Ratio: " << ratio1 << endl;
    }

    TGraphErrors *IntGrapEr1 = new TGraphErrors(7, dirArr, intRatio1, err1X, err1Y);
    
    IntGrapEr1->Fit("pol1");
    
    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGrapEr1->SetMarkerColor(4);
    IntGrapEr1->SetMinimum(0.);
    IntGrapEr1->SetMaximum(1.2);

    IntGrapEr1->Draw();
    IntGrapEr1->SetTitle("Proton-Only Interaction Rate");
    IntGrapEr1->GetXaxis()->SetTitle("Tungsten");
    IntGrapEr1->GetYaxis()->SetTitle("Percentage");
    IntGrapEr1->SetMarkerSize(1.5);
    IntGrapEr1->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameStart,"pdf");
    delete Canvas;

    TGraphErrors *IntGrapEr2 = new TGraphErrors(7, dirArr, intRatio2, err2X, err2Y);

    IntGrapEr2->Fit("pol1");

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGrapEr2->SetMarkerColor(4);
    IntGrapEr2->SetMinimum(0.);
    IntGrapEr2->SetMaximum(1.2);

    IntGrapEr2->Draw();
    IntGrapEr2->SetTitle("All Interaction Rate");
    IntGrapEr2->GetXaxis()->SetTitle("Tungsten");
    IntGrapEr2->GetYaxis()->SetTitle("Percentage");
    IntGrapEr2->SetMarkerSize(1.5);
    IntGrapEr2->SetMarkerStyle(kFullCircle);

    Canvas->Print(outName,"pdf");
    delete Canvas;

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntRatioGraph->SetMarkerColor(4);
    IntRatioGraph->SetMinimum(0.);
    IntRatioGraph->SetMaximum(2.);

    IntRatioGraph->Draw();
    IntRatioGraph->SetTitle("Ratio Division");
    IntRatioGraph->GetXaxis()->SetTitle("Tungsten");
    IntRatioGraph->SetMarkerSize(1.5);
    IntRatioGraph->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameEnd,"pdf");
    delete Canvas;

    Data->Close();
}