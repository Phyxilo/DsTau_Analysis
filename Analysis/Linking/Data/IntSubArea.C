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
float intParArr[8][21], totParArr[8][21], totProtonsArr[8][21];
float err1X[8][21], err1Y[8][21], err2X[8][21], err2Y[8][21], err3X[8][21], err3Y[8][21];

const char *acceptanceCut[21] = 
{
    "29", "30", "31", "32", "33", "34", "35",
    "38", "39", "40", "41", "42", "43", "44",
    "47", "48", "49", "50", "51", "52", "53"
};

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

void IntSubArea()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    int ind = 0;

    sprintf(outName,"IntSubArea.pdf");
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

                sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p0%d6.root", j);
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

                intParArr[j][ind] = IntPar;
                totParArr[j][ind] = TotalPar;
                totProtonsArr[j][ind] = totProtons;
                dirArr[ind] = ind;

                err1X[j][ind] = 0;
                err1Y[j][ind] = (sqrt(IntPar));

                err2X[j][ind] = 0;
                err2Y[j][ind] = (sqrt(TotalPar));

                err3X[j][ind] = 0;
                err3Y[j][ind] = (sqrt(totProtons));
            }

            ind++;
        }
    }

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);

    gPad->SetGrid(1, 1);

    TGraph *IntGraph1 = new TGraph(21, dirArr, intParArr[0]);
    TGraph *TotParGraph1 = new TGraph(21, dirArr, totParArr[0]);
    TGraph *TotProtonsGraph1 = new TGraph(21, dirArr, totProtonsArr[0]);

    TGraph *IntGraph2 = new TGraph(21, dirArr, intParArr[1]);
    TGraph *TotParGraph2 = new TGraph(21, dirArr, totParArr[1]);
    TGraph *TotProtonsGraph2 = new TGraph(21, dirArr, totProtonsArr[1]);

    TGraph *IntGraph3 = new TGraph(21, dirArr, intParArr[2]);
    TGraph *TotParGraph3 = new TGraph(21, dirArr, totParArr[2]);
    TGraph *TotProtonsGraph3 = new TGraph(21, dirArr, totProtonsArr[2]);

    TGraph *IntGraph4 = new TGraph(21, dirArr, intParArr[3]);
    TGraph *TotParGraph4 = new TGraph(21, dirArr, totParArr[3]);
    TGraph *TotProtonsGraph4 = new TGraph(21, dirArr, totProtonsArr[3]);

    TGraph *IntGraph5 = new TGraph(21, dirArr, intParArr[4]);
    TGraph *TotParGraph5 = new TGraph(21, dirArr, totParArr[4]);
    TGraph *TotProtonsGraph5 = new TGraph(21, dirArr, totProtonsArr[4]);

    TGraph *IntGraph6 = new TGraph(21, dirArr, intParArr[5]);
    TGraph *TotParGraph6 = new TGraph(21, dirArr, totParArr[5]);
    TGraph *TotProtonsGraph6 = new TGraph(21, dirArr, totProtonsArr[5]);

    TGraph *IntGraph7 = new TGraph(21, dirArr, intParArr[6]);
    TGraph *TotParGraph7 = new TGraph(21, dirArr, totParArr[6]);
    TGraph *TotProtonsGraph7 = new TGraph(21, dirArr, totProtonsArr[6]);

    TGraph *IntGraph8 = new TGraph(21, dirArr, intParArr[7]);
    TGraph *TotParGraph8 = new TGraph(21, dirArr, totParArr[7]);
    TGraph *TotProtonsGraph8 = new TGraph(21, dirArr, totProtonsArr[7]);

    for (int i = 0; i < 21; i++)
    {
        IntGraph1->GetXaxis()->SetBinLabel(TotProtonsGraph1->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph1->GetXaxis()->SetBinLabel(TotProtonsGraph1->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph1->GetXaxis()->SetBinLabel(TotProtonsGraph1->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph2->GetXaxis()->SetBinLabel(TotProtonsGraph2->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph2->GetXaxis()->SetBinLabel(TotProtonsGraph2->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph2->GetXaxis()->SetBinLabel(TotProtonsGraph2->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph3->GetXaxis()->SetBinLabel(TotProtonsGraph3->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph3->GetXaxis()->SetBinLabel(TotProtonsGraph3->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph3->GetXaxis()->SetBinLabel(TotProtonsGraph3->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph4->GetXaxis()->SetBinLabel(TotProtonsGraph4->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph4->GetXaxis()->SetBinLabel(TotProtonsGraph4->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph4->GetXaxis()->SetBinLabel(TotProtonsGraph4->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph5->GetXaxis()->SetBinLabel(TotProtonsGraph5->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph5->GetXaxis()->SetBinLabel(TotProtonsGraph5->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph5->GetXaxis()->SetBinLabel(TotProtonsGraph5->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph6->GetXaxis()->SetBinLabel(TotProtonsGraph6->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph6->GetXaxis()->SetBinLabel(TotProtonsGraph6->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph6->GetXaxis()->SetBinLabel(TotProtonsGraph6->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph7->GetXaxis()->SetBinLabel(TotProtonsGraph7->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph7->GetXaxis()->SetBinLabel(TotProtonsGraph7->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph7->GetXaxis()->SetBinLabel(TotProtonsGraph7->GetXaxis()->FindBin(i), acceptanceCut[i]);

        IntGraph8->GetXaxis()->SetBinLabel(TotProtonsGraph8->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotParGraph8->GetXaxis()->SetBinLabel(TotProtonsGraph8->GetXaxis()->FindBin(i), acceptanceCut[i]);
        TotProtonsGraph8->GetXaxis()->SetBinLabel(TotProtonsGraph8->GetXaxis()->FindBin(i), acceptanceCut[i]);
    }

    gPad->Modified();
    gPad->Update();

    IntGraph1->Draw("AP");
    IntGraph1->SetMarkerColor(1);
    IntGraph1->SetMarkerSize(1.5);
    IntGraph1->SetMarkerStyle(kFullCircle);
    
    IntGraph2->Draw("P");
    IntGraph2->SetMarkerColor(2);
    IntGraph2->SetMarkerSize(1.5);
    IntGraph2->SetMarkerStyle(kFullCircle);

    IntGraph3->Draw("P");
    IntGraph3->SetMarkerColor(3);
    IntGraph3->SetMarkerSize(1.5);
    IntGraph3->SetMarkerStyle(kFullCircle);

    IntGraph4->Draw("P");
    IntGraph4->SetMarkerColor(4);
    IntGraph4->SetMarkerSize(1.5);
    IntGraph4->SetMarkerStyle(kFullCircle);

    IntGraph5->Draw("P");
    IntGraph5->SetMarkerColor(5);
    IntGraph5->SetMarkerSize(1.5);
    IntGraph5->SetMarkerStyle(kFullCircle);

    IntGraph6->Draw("P");
    IntGraph6->SetMarkerColor(6);
    IntGraph6->SetMarkerSize(1.5);
    IntGraph6->SetMarkerStyle(kFullCircle);

    IntGraph7->Draw("P");
    IntGraph7->SetMarkerColor(7);
    IntGraph7->SetMarkerSize(1.5);
    IntGraph7->SetMarkerStyle(kFullCircle);

    IntGraph8->Draw("P");
    IntGraph8->SetMarkerColor(8);
    IntGraph8->SetMarkerSize(1.5);
    IntGraph8->SetMarkerStyle(kFullCircle);

    IntGraph1->SetTitle("Proton Linking");
    IntGraph1->GetXaxis()->SetTitle("Sub-Area");
    IntGraph1->GetYaxis()->SetTitle("Percentage");

    Canvas->Print(outNameStart,"pdf");

    TotParGraph1->Draw("AP");
    TotParGraph1->SetMarkerColor(1);
    TotParGraph1->SetMarkerSize(1.5);
    TotParGraph1->SetMarkerStyle(kFullCircle);

    TotParGraph2->Draw("P");
    TotParGraph2->SetMarkerColor(2);
    TotParGraph2->SetMarkerSize(1.5);
    TotParGraph2->SetMarkerStyle(kFullCircle);

    TotParGraph3->Draw("P");
    TotParGraph3->SetMarkerColor(3);
    TotParGraph3->SetMarkerSize(1.5);
    TotParGraph3->SetMarkerStyle(kFullCircle);

    TotParGraph4->Draw("P");
    TotParGraph4->SetMarkerColor(4);
    TotParGraph4->SetMarkerSize(1.5);
    TotParGraph4->SetMarkerStyle(kFullCircle);

    TotParGraph5->Draw("P");
    TotParGraph5->SetMarkerColor(5);
    TotParGraph5->SetMarkerSize(1.5);
    TotParGraph5->SetMarkerStyle(kFullCircle);

    TotParGraph6->Draw("P");
    TotParGraph6->SetMarkerColor(6);
    TotParGraph6->SetMarkerSize(1.5);
    TotParGraph6->SetMarkerStyle(kFullCircle);

    TotParGraph7->Draw("P");
    TotParGraph7->SetMarkerColor(7);
    TotParGraph7->SetMarkerSize(1.5);
    TotParGraph7->SetMarkerStyle(kFullCircle);

    TotParGraph8->Draw("P");
    TotParGraph8->SetMarkerColor(8);
    TotParGraph8->SetMarkerSize(1.5);
    TotParGraph8->SetMarkerStyle(kFullCircle);

    TotParGraph1->SetTitle("Vertexing");
    TotParGraph1->GetXaxis()->SetTitle("Sub-Area");
    TotParGraph1->GetYaxis()->SetTitle("Percentage");

    Canvas->Print(outName,"pdf");

    TotProtonsGraph1->Draw("AP");
    TotProtonsGraph1->SetMarkerColor(1);
    TotProtonsGraph1->SetMarkerSize(1.5);
    TotProtonsGraph1->SetMarkerStyle(kFullCircle);

    TotProtonsGraph2->Draw("P");
    TotProtonsGraph2->SetMarkerColor(2);
    TotProtonsGraph2->SetMarkerSize(1.5);
    TotProtonsGraph2->SetMarkerStyle(kFullCircle);

    TotProtonsGraph3->Draw("P");
    TotProtonsGraph3->SetMarkerColor(3);
    TotProtonsGraph3->SetMarkerSize(1.5);
    TotProtonsGraph3->SetMarkerStyle(kFullCircle);

    TotProtonsGraph4->Draw("P");
    TotProtonsGraph4->SetMarkerColor(4);
    TotProtonsGraph4->SetMarkerSize(1.5);
    TotProtonsGraph4->SetMarkerStyle(kFullCircle);

    TotProtonsGraph5->Draw("P");
    TotProtonsGraph5->SetMarkerColor(5);
    TotProtonsGraph5->SetMarkerSize(1.5);
    TotProtonsGraph5->SetMarkerStyle(kFullCircle);

    TotProtonsGraph6->Draw("P");
    TotProtonsGraph6->SetMarkerColor(6);
    TotProtonsGraph6->SetMarkerSize(1.5);
    TotProtonsGraph6->SetMarkerStyle(kFullCircle);

    TotProtonsGraph7->Draw("P");
    TotProtonsGraph7->SetMarkerColor(7);
    TotProtonsGraph7->SetMarkerSize(1.5);
    TotProtonsGraph7->SetMarkerStyle(kFullCircle);

    TotProtonsGraph8->Draw("P");
    TotProtonsGraph8->SetMarkerColor(8);
    TotProtonsGraph8->SetMarkerSize(1.5);
    TotProtonsGraph8->SetMarkerStyle(kFullCircle);

    TotProtonsGraph1->SetTitle("Total Number of Protons");
    TotProtonsGraph1->GetXaxis()->SetTitle("Sub-Area");
    TotProtonsGraph1->GetYaxis()->SetTitle("Percentage");

    Canvas->Print(outNameEnd,"pdf");
    
    Data->Close();
}