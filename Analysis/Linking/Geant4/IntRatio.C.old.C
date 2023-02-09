#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas;

TGraph *IntGraph1 = new TGraph (6);
TGraph *IntGraph2 = new TGraph (6);
TGraph *IntGraph3 = new TGraph (6);

TFile *Data;

float linkedProton[8] = 
{
    59916, 
    56496, 
    53237, 
    50136, 
    46979, 
    43710, 
    40472, 
    37044
};

float linkedInt[8] = 
{
    443, 
    324, 
    298, 
    312, 
    290, 
    313, 
    379, 
    414
};

float vertexInt[8], dirArr[8];

int subV = 0;
int posInt = 4000;

char dir [128];

void IntRatio()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    sprintf(outName,"IntRatio.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int j = 0; j < 6; j++)
    {
        int IntPar = 0, TotalPar = 0;

        sprintf(dir,"../../../Geant4SM_v1.0/RootOut/pl0%d1_%02d0.root", j, j+3);
        cout << dir << endl;

        //Data = TFile::Open("../Root/Geant4_p006.root");
        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        
        for (int i = 0; i < parData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);

            TLeaf *vx = parData->GetLeaf("vx");
            TLeaf *vy = parData->GetLeaf("vy");
            TLeaf *plt = parData->GetLeaf("plt_of_1seg");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();

            if((VX < posInt && VX > -posInt) && (VY < posInt && VY > -posInt))
            {
                if (Plt >= 5 + j*10 && Plt < 10 + j*10){IntPar++;}
            }
        }

        float ratio1 = ((float)IntPar/linkedProton[j])*100;
        float ratio2 = (float)(linkedInt[j]/linkedProton[j])*100;

        cout << "Int: " << IntPar << ", Total: " << linkedProton[j] << ", Ratio: " << ratio1 << endl;
        vertexInt[j] = IntPar;

        IntGraph1->SetPoint(j, j, ratio1);
        IntGraph2->SetPoint(j, j, ratio2);
        IntGraph3->SetPoint(j, j, ratio1/ratio2);
    }

    IntGraph1->Fit("pol1");
    
    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGraph1->SetMarkerColor(4);
    IntGraph1->SetMinimum(0.);
    IntGraph1->SetMaximum(2.);

    IntGraph1->Draw();
    IntGraph1->SetTitle("Interaction Rate");
    IntGraph1->GetXaxis()->SetTitle("Tungsten");
    IntGraph1->GetYaxis()->SetTitle("Percentage");
    IntGraph1->SetMarkerSize(1.5);
    IntGraph1->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameStart,"pdf");
    delete Canvas;

    IntGraph2->Fit("pol1");

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGraph2->SetMarkerColor(4);
    IntGraph2->SetMinimum(0.);
    IntGraph2->SetMaximum(2.);

    IntGraph2->Draw();
    IntGraph2->SetTitle("Interaction Rate");
    IntGraph2->GetXaxis()->SetTitle("Tungsten");
    IntGraph2->GetYaxis()->SetTitle("Percentage");
    IntGraph2->SetMarkerSize(1.5);
    IntGraph2->SetMarkerStyle(kFullCircle);

    Canvas->Print(outName,"pdf");
    delete Canvas;

    IntGraph3->Fit("pol1");

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGraph3->SetMarkerColor(4);
    IntGraph3->SetMinimum(0.);
    IntGraph3->SetMaximum(2.);

    IntGraph3->Draw();
    IntGraph3->SetTitle("Interaction Rate");
    IntGraph3->GetXaxis()->SetTitle("Tungsten");
    IntGraph3->SetMarkerSize(1.5);
    IntGraph3->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameEnd,"pdf");
    delete Canvas;

    Data->Close();
}