#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas;

TFile *Data;

float dirArr[21];
float intParArr[21], totParArr[21], totProtonsArr[21];
float err1X[21], err1Y[21], err2X[21], err2Y[21], err3X[21], err3Y[21];

/*
const int acceptanceCut[21] = 
{
    29, 30, 31, 32, 33, 34, 35,
    38, 39, 40, 41, 42, 43, 44,
    47, 48, 49, 50, 51, 52, 53
};
*/

const char *acceptanceCut[21] = 
{
    "29", "30", "31", "32", "33", "34", "35",
    "38", "39", "40", "41", "42", "43", "44",
    "47", "48", "49", "50", "51", "52", "53"
};

//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

float posXMin = 57000, posXMax = 73000;
float posYMin = 57000, posYMax = 73000;

char dir [128];

bool isInArea(int areaNum)
{
    if ((areaNum <= 53 && areaNum >= 47) || (areaNum <= 44 && areaNum >= 38) || (areaNum <= 35 && areaNum >= 29))
    {
        return true;
    }

    return false;
}

void DropSubArea()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    int ind = 0;

    sprintf(outName,"DropSubArea.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int k = 1; k < 64; k++)
    {
        if (isInArea(k))
        {
            int firstIntPar = 0, firstTotPar = 0, firstTotProtons = 0;

            for (int j = 0; j < 8; j++)
            {
                int IntPar = 0, TotalPar = 0;

                sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut/p0%d6.root", j);
                //sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut_TrackSel+Res5/p0%d6.root", j);

                //cout << dir << endl;

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
                    TLeaf *vz = parData->GetLeaf("vz");
                    TLeaf *plt = parData->GetLeaf("plt_of_1seg");
                    TLeaf *flagp = parData->GetLeaf("flagp");
                    TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");
                    TLeaf *plmax = parData->GetLeaf("pl_up1ry_plmax");

                    TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");
                    TLeaf *area1 = vtxData->GetLeaf("area1");
                    TLeaf *iMed = vtxData->GetLeaf("intMed");
                    TLeaf *flagw = vtxData->GetLeaf("flagw");

                    float VX = vx->GetValue();
                    float VY = vy->GetValue();
                    int Plt = plt->GetValue();
                    int fp = flagp->GetValue();

                    //bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29)); //New Method

                    if (area1->GetValue() == k && (iMed->GetValue() == 1))
                    {
                        if (fp >= 1)
                        {
                            IntPar++;
                        }

                        TotalPar++;
                    }
                }

                int totProtons = 0;

                for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
                {
                    ptrkData->GetEntry(i);

                    TLeaf *area1 = ptrkData->GetLeaf("area1");
                    TLeaf *pltFirst = ptrkData->GetLeaf("US_plt_of_1seg");

                    if(area1->GetValue() == k){totProtons++;}
                }

                if (j == 0)
                {
                    firstIntPar = IntPar;
                    firstTotPar = TotalPar;
                    firstTotProtons = totProtons;
                }
                else if (j == 7)
                {
                    float intParDropRatio = ((float)(firstIntPar - IntPar)/firstIntPar)*100;
                    float totParDropRatio = ((float)(firstTotPar - TotalPar)/firstTotPar)*100;
                    float totProtonsDropRatio = ((float)(firstTotProtons - totProtons)/firstTotProtons)*100;

                    intParArr[ind] = intParDropRatio;
                    totParArr[ind] = totParDropRatio;
                    totProtonsArr[ind] = totProtonsDropRatio;
                    dirArr[ind] = ind;

                    err1X[ind] = 0;
                    err1Y[ind] = ((1-intParDropRatio)/IntPar)*100;

                    err2X[ind] = 0;
                    err2Y[ind] = ((1-totParDropRatio)/TotalPar)*100;

                    err3X[ind] = 0;
                    err3Y[ind] = ((1-totProtonsDropRatio)/totProtons)*100;

                    cout << "Index: " << acceptanceCut[ind] << ", Drop: " << totProtonsDropRatio << endl;

                    ind++;
                }
            }
        }
    }

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);

    gPad->SetGrid(1, 1);

    TGraph *IntGraph = new TGraph(21, dirArr, intParArr);
    TGraph *TotParGraph = new TGraph(21, dirArr, totParArr);
    TGraph *TotProtonsGraph = new TGraph(21, dirArr, totProtonsArr);

    for (int i = 0; i < 21; i++)
    {
        IntGraph->GetXaxis()->SetBinLabel(TotProtonsGraph->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph->GetXaxis()->SetBinLabel(TotProtonsGraph->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph->GetXaxis()->SetBinLabel(TotProtonsGraph->GetXaxis()->FindBin(i), acceptanceCut[i]);
    }

    gPad->Modified();
    gPad->Update();

    IntGraph->SetMarkerColor(4);
    //IntGraph->SetMinimum(0.);
    //IntGraph->SetMaximum(2.0);

    IntGraph->Draw("AP");
    IntGraph->SetTitle("Proton Linking");
    IntGraph->GetXaxis()->SetTitle("Sub-Area");
    IntGraph->GetYaxis()->SetTitle("Percentage");
    IntGraph->SetMarkerSize(1.5);
    IntGraph->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameStart,"pdf");

    TotParGraph->SetMarkerColor(4);
    //IntGraph->SetMinimum(0.);
    //IntGraph->SetMaximum(2.0);

    TotParGraph->Draw("AP");
    TotParGraph->SetTitle("Vertexing");
    TotParGraph->GetXaxis()->SetTitle("Sub-Area");
    TotParGraph->GetYaxis()->SetTitle("Percentage");
    TotParGraph->SetMarkerSize(1.5);
    TotParGraph->SetMarkerStyle(kFullCircle);

    Canvas->Print(outName,"pdf");

    TotProtonsGraph->SetMarkerColor(4);
    //IntGraph->SetMinimum(0.);
    //IntGraph->SetMaximum(2.0);

    TotProtonsGraph->Draw("AP");
    TotProtonsGraph->SetTitle("Total Number of Protons");
    TotProtonsGraph->GetXaxis()->SetTitle("Sub-Area");
    TotProtonsGraph->GetYaxis()->SetTitle("Percentage");
    TotProtonsGraph->SetMarkerSize(1.5);
    TotProtonsGraph->SetMarkerStyle(kFullCircle);

    Canvas->Print(outNameEnd,"pdf");
    
    Data->Close();
}