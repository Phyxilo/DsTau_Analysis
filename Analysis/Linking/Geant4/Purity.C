#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

char dir [128];

float totalSeg [7] = 
{
    85872,
    80821,
    75829,
    70614,
    65625,
    60377,
    55138
};

float nonProtonSeg [7] = 
{
    1162,
    1987,
    2816,
    3426,
    3945,
    4343,
    4667
};

float protonPer [7], wArr [7];

void Purity()
{
    char outName[64] = "Purity.png";

    float dataSize = 0;

    for (int i = 0; i < 7; i++)
    {
        protonPer[i] = 100*((totalSeg[i] - nonProtonSeg[i])/totalSeg[i]);
        wArr[i] = i+1;
    }
    
    Canvas->SetGrid();

    TGraph *PurGraph = new TGraph (7, wArr, protonPer);

    PurGraph->Draw();
    PurGraph->SetTitle("Proton Purity");
    PurGraph->GetXaxis()->SetTitle("Tungsten");
    PurGraph->GetYaxis()->SetTitle("Percentage");
    PurGraph->SetMarkerSize(1.5);
    PurGraph->SetMarkerStyle(kFullCircle);

    PurGraph->GetXaxis()->SetLimits(1,8);

    PurGraph->SetMaximum(100);
    PurGraph->SetMinimum(90);
    
    Canvas->Print(outName,"png");
    delete Canvas;
}