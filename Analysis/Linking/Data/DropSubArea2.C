#include <iostream>
#include <vector>

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

float xAxis [7] = {1, 2, 3, 4, 5, 6, 7};
float xAxis2 [8] = {1, 2, 3, 4, 5, 6, 7, 8};

float subAreaArr [21][7];
float subAreaVtxArr [21][7];
float subAreaPriArr [21][7];
float vtxIntArr [21][8];
float priIntArr [21][8];

const int acceptanceArray[21] = 
{
    29, 30, 31, 32, 33, 34, 35,
    38, 39, 40, 41, 42, 43, 44,
    47, 48, 49, 50, 51, 52, 53
};

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

void DropSubArea2()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    int ind = 0;

    snprintf(outName, 64, "DropSubArea2.pdf");
    snprintf(outNameStart, 64, "%s(", outName);
    snprintf(outNameEnd, 64, "%s)", outName);

    for (int k = 0; k < 21; k++)
    {
        int subA = acceptanceArray[k];
        int firstIntPar = 0, firstTotPar = 0, firstTotProtons = 0;

        for (int j = 0; j < 8; j++)
        {
            int IntPar = 0, TotalPar = 0;

            snprintf(dir, 128, "../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p0%d6.root", j);
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

                if (area1->GetValue() == subA && (iMed->GetValue() == 1))
                {
                    if (fp >= 1)
                    {
                        IntPar++;
                    }

                    TotalPar++;
                }
                if (area1->GetValue() > subA) break;

            }
            int totProtons = 0;

            for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
            {
                ptrkData->GetEntry(i);

                TLeaf *area1 = ptrkData->GetLeaf("area1");
                TLeaf *pltFirst = ptrkData->GetLeaf("US_plt_of_1seg");

                if(area1->GetValue() == subA){totProtons++;}
            }

           float totProtonsDropRatio = 0;
           float intParDropRatio = 0;
           float totParDropRatio = 0;

            if(j > 0)
            {
                intParDropRatio = ((float)(firstIntPar - IntPar)/firstIntPar)*100;
                totParDropRatio = ((float)(firstTotPar - TotalPar)/firstTotPar)*100;
                totProtonsDropRatio = ((float)(firstTotProtons - totProtons)/firstTotProtons)*100;
            }

            firstIntPar = IntPar;
            firstTotPar = TotalPar;
            firstTotProtons = totProtons;

            vtxIntArr[k][j] = TotalPar;
            priIntArr[k][j] = IntPar;

            if (j > 0)
            {
                subAreaArr[k][j-1] = totProtonsDropRatio;
                subAreaVtxArr[k][j-1] = totParDropRatio;
                subAreaPriArr[k][j-1] = intParDropRatio;
            }
            
        }
    }

    /*
    for (auto& arr : subAreaArr) 
    {
        for (auto& el : arr)
            cout << el << ' ';
    }
    */

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);

    gPad->SetGrid();

    TMultiGraph *DropMG = new TMultiGraph();
    TMultiGraph *DropVtxMG = new TMultiGraph();
    TMultiGraph *DropPriMG = new TMultiGraph();
    TMultiGraph *VtxMG = new TMultiGraph();
    TMultiGraph *PriMG = new TMultiGraph();

    TGraph *IntGraph1 = new TGraph(7, xAxis, subAreaArr[0]);
    TGraph *IntGraph2 = new TGraph(7, xAxis, subAreaArr[1]);
    TGraph *IntGraph3 = new TGraph(7, xAxis, subAreaArr[2]);
    TGraph *IntGraph4 = new TGraph(7, xAxis, subAreaArr[3]);
    TGraph *IntGraph5 = new TGraph(7, xAxis, subAreaArr[4]);
    TGraph *IntGraph6 = new TGraph(7, xAxis, subAreaArr[5]);
    TGraph *IntGraph7 = new TGraph(7, xAxis, subAreaArr[6]);
    TGraph *IntGraph8 = new TGraph(7, xAxis, subAreaArr[7]);
    TGraph *IntGraph9 = new TGraph(7, xAxis, subAreaArr[8]);
    TGraph *IntGraph10 = new TGraph(7, xAxis, subAreaArr[9]);
    TGraph *IntGraph11 = new TGraph(7, xAxis, subAreaArr[10]);
    TGraph *IntGraph12 = new TGraph(7, xAxis, subAreaArr[11]);
    TGraph *IntGraph13 = new TGraph(7, xAxis, subAreaArr[12]);
    TGraph *IntGraph14 = new TGraph(7, xAxis, subAreaArr[13]);
    TGraph *IntGraph15 = new TGraph(7, xAxis, subAreaArr[14]);
    TGraph *IntGraph16 = new TGraph(7, xAxis, subAreaArr[15]);
    TGraph *IntGraph17 = new TGraph(7, xAxis, subAreaArr[16]);
    TGraph *IntGraph18 = new TGraph(7, xAxis, subAreaArr[17]);
    TGraph *IntGraph19 = new TGraph(7, xAxis, subAreaArr[18]);
    TGraph *IntGraph20 = new TGraph(7, xAxis, subAreaArr[19]);
    TGraph *IntGraph21 = new TGraph(7, xAxis, subAreaArr[20]);

    TGraph *IntVtxGraph1 = new TGraph(7, xAxis, subAreaVtxArr[0]);
    TGraph *IntVtxGraph2 = new TGraph(7, xAxis, subAreaVtxArr[1]);
    TGraph *IntVtxGraph3 = new TGraph(7, xAxis, subAreaVtxArr[2]);
    TGraph *IntVtxGraph4 = new TGraph(7, xAxis, subAreaVtxArr[3]);
    TGraph *IntVtxGraph5 = new TGraph(7, xAxis, subAreaVtxArr[4]);
    TGraph *IntVtxGraph6 = new TGraph(7, xAxis, subAreaVtxArr[5]);
    TGraph *IntVtxGraph7 = new TGraph(7, xAxis, subAreaVtxArr[6]);
    TGraph *IntVtxGraph8 = new TGraph(7, xAxis, subAreaVtxArr[7]);
    TGraph *IntVtxGraph9 = new TGraph(7, xAxis, subAreaVtxArr[8]);
    TGraph *IntVtxGraph10 = new TGraph(7, xAxis, subAreaVtxArr[9]);
    TGraph *IntVtxGraph11 = new TGraph(7, xAxis, subAreaVtxArr[10]);
    TGraph *IntVtxGraph12 = new TGraph(7, xAxis, subAreaVtxArr[11]);
    TGraph *IntVtxGraph13 = new TGraph(7, xAxis, subAreaVtxArr[12]);
    TGraph *IntVtxGraph14 = new TGraph(7, xAxis, subAreaVtxArr[13]);
    TGraph *IntVtxGraph15 = new TGraph(7, xAxis, subAreaVtxArr[14]);
    TGraph *IntVtxGraph16 = new TGraph(7, xAxis, subAreaVtxArr[15]);
    TGraph *IntVtxGraph17 = new TGraph(7, xAxis, subAreaVtxArr[16]);
    TGraph *IntVtxGraph18 = new TGraph(7, xAxis, subAreaVtxArr[17]);
    TGraph *IntVtxGraph19 = new TGraph(7, xAxis, subAreaVtxArr[18]);
    TGraph *IntVtxGraph20 = new TGraph(7, xAxis, subAreaVtxArr[19]);
    TGraph *IntVtxGraph21 = new TGraph(7, xAxis, subAreaVtxArr[20]);

    TGraph *IntPriGraph1 = new TGraph(7, xAxis, subAreaPriArr[0]);
    TGraph *IntPriGraph2 = new TGraph(7, xAxis, subAreaPriArr[1]);
    TGraph *IntPriGraph3 = new TGraph(7, xAxis, subAreaPriArr[2]);
    TGraph *IntPriGraph4 = new TGraph(7, xAxis, subAreaPriArr[3]);
    TGraph *IntPriGraph5 = new TGraph(7, xAxis, subAreaPriArr[4]);
    TGraph *IntPriGraph6 = new TGraph(7, xAxis, subAreaPriArr[5]);
    TGraph *IntPriGraph7 = new TGraph(7, xAxis, subAreaPriArr[6]);
    TGraph *IntPriGraph8 = new TGraph(7, xAxis, subAreaPriArr[7]);
    TGraph *IntPriGraph9 = new TGraph(7, xAxis, subAreaPriArr[8]);
    TGraph *IntPriGraph10 = new TGraph(7, xAxis, subAreaPriArr[9]);
    TGraph *IntPriGraph11 = new TGraph(7, xAxis, subAreaPriArr[10]);
    TGraph *IntPriGraph12 = new TGraph(7, xAxis, subAreaPriArr[11]);
    TGraph *IntPriGraph13 = new TGraph(7, xAxis, subAreaPriArr[12]);
    TGraph *IntPriGraph14 = new TGraph(7, xAxis, subAreaPriArr[13]);
    TGraph *IntPriGraph15 = new TGraph(7, xAxis, subAreaPriArr[14]);
    TGraph *IntPriGraph16 = new TGraph(7, xAxis, subAreaPriArr[15]);
    TGraph *IntPriGraph17 = new TGraph(7, xAxis, subAreaPriArr[16]);
    TGraph *IntPriGraph18 = new TGraph(7, xAxis, subAreaPriArr[17]);
    TGraph *IntPriGraph19 = new TGraph(7, xAxis, subAreaPriArr[18]);
    TGraph *IntPriGraph20 = new TGraph(7, xAxis, subAreaPriArr[19]);
    TGraph *IntPriGraph21 = new TGraph(7, xAxis, subAreaPriArr[20]);

    TGraph *VtxGraph1 = new TGraph(8, xAxis2, vtxIntArr[0]);
    TGraph *VtxGraph2 = new TGraph(8, xAxis2, vtxIntArr[1]);
    TGraph *VtxGraph3 = new TGraph(8, xAxis2, vtxIntArr[2]);
    TGraph *VtxGraph4 = new TGraph(8, xAxis2, vtxIntArr[3]);
    TGraph *VtxGraph5 = new TGraph(8, xAxis2, vtxIntArr[4]);
    TGraph *VtxGraph6 = new TGraph(8, xAxis2, vtxIntArr[5]);
    TGraph *VtxGraph7 = new TGraph(8, xAxis2, vtxIntArr[6]);
    TGraph *VtxGraph8 = new TGraph(8, xAxis2, vtxIntArr[7]);
    TGraph *VtxGraph9 = new TGraph(8, xAxis2, vtxIntArr[8]);
    TGraph *VtxGraph10 = new TGraph(8, xAxis2, vtxIntArr[9]);
    TGraph *VtxGraph11 = new TGraph(8, xAxis2, vtxIntArr[10]);
    TGraph *VtxGraph12 = new TGraph(8, xAxis2, vtxIntArr[11]);
    TGraph *VtxGraph13 = new TGraph(8, xAxis2, vtxIntArr[12]);
    TGraph *VtxGraph14 = new TGraph(8, xAxis2, vtxIntArr[13]);
    TGraph *VtxGraph15 = new TGraph(8, xAxis2, vtxIntArr[14]);
    TGraph *VtxGraph16 = new TGraph(8, xAxis2, vtxIntArr[15]);
    TGraph *VtxGraph17 = new TGraph(8, xAxis2, vtxIntArr[16]);
    TGraph *VtxGraph18 = new TGraph(8, xAxis2, vtxIntArr[17]);
    TGraph *VtxGraph19 = new TGraph(8, xAxis2, vtxIntArr[18]);
    TGraph *VtxGraph20 = new TGraph(8, xAxis2, vtxIntArr[19]);
    TGraph *VtxGraph21 = new TGraph(8, xAxis2, vtxIntArr[20]);

    TGraph *PriGraph1 = new TGraph(8, xAxis2, priIntArr[0]);
    TGraph *PriGraph2 = new TGraph(8, xAxis2, priIntArr[1]);
    TGraph *PriGraph3 = new TGraph(8, xAxis2, priIntArr[2]);
    TGraph *PriGraph4 = new TGraph(8, xAxis2, priIntArr[3]);
    TGraph *PriGraph5 = new TGraph(8, xAxis2, priIntArr[4]);
    TGraph *PriGraph6 = new TGraph(8, xAxis2, priIntArr[5]);
    TGraph *PriGraph7 = new TGraph(8, xAxis2, priIntArr[6]);
    TGraph *PriGraph8 = new TGraph(8, xAxis2, priIntArr[7]);
    TGraph *PriGraph9 = new TGraph(8, xAxis2, priIntArr[8]);
    TGraph *PriGraph10 = new TGraph(8, xAxis2, priIntArr[9]);
    TGraph *PriGraph11 = new TGraph(8, xAxis2, priIntArr[10]);
    TGraph *PriGraph12 = new TGraph(8, xAxis2, priIntArr[11]);
    TGraph *PriGraph13 = new TGraph(8, xAxis2, priIntArr[12]);
    TGraph *PriGraph14 = new TGraph(8, xAxis2, priIntArr[13]);
    TGraph *PriGraph15 = new TGraph(8, xAxis2, priIntArr[14]);
    TGraph *PriGraph16 = new TGraph(8, xAxis2, priIntArr[15]);
    TGraph *PriGraph17 = new TGraph(8, xAxis2, priIntArr[16]);
    TGraph *PriGraph18 = new TGraph(8, xAxis2, priIntArr[17]);
    TGraph *PriGraph19 = new TGraph(8, xAxis2, priIntArr[18]);
    TGraph *PriGraph20 = new TGraph(8, xAxis2, priIntArr[19]);
    TGraph *PriGraph21 = new TGraph(8, xAxis2, priIntArr[20]);

    DropMG->Add(IntGraph1);
    DropMG->Add(IntGraph2);
    DropMG->Add(IntGraph3);
    DropMG->Add(IntGraph4);
    DropMG->Add(IntGraph5);
    DropMG->Add(IntGraph6);
    DropMG->Add(IntGraph7);
    DropMG->Add(IntGraph8);
    DropMG->Add(IntGraph9);
    DropMG->Add(IntGraph10);
    DropMG->Add(IntGraph11);
    DropMG->Add(IntGraph12);
    DropMG->Add(IntGraph13);
    DropMG->Add(IntGraph14);
    DropMG->Add(IntGraph15);
    DropMG->Add(IntGraph16);
    DropMG->Add(IntGraph17);
    DropMG->Add(IntGraph18);
    DropMG->Add(IntGraph19);
    DropMG->Add(IntGraph20);
    DropMG->Add(IntGraph21);

    DropVtxMG->Add(IntVtxGraph1);
    DropVtxMG->Add(IntVtxGraph2);
    DropVtxMG->Add(IntVtxGraph3);
    DropVtxMG->Add(IntVtxGraph4);
    DropVtxMG->Add(IntVtxGraph5);
    DropVtxMG->Add(IntVtxGraph6);
    DropVtxMG->Add(IntVtxGraph7);
    DropVtxMG->Add(IntVtxGraph8);
    DropVtxMG->Add(IntVtxGraph9);
    DropVtxMG->Add(IntVtxGraph10);
    DropVtxMG->Add(IntVtxGraph11);
    DropVtxMG->Add(IntVtxGraph12);
    DropVtxMG->Add(IntVtxGraph13);
    DropVtxMG->Add(IntVtxGraph14);
    DropVtxMG->Add(IntVtxGraph15);
    DropVtxMG->Add(IntVtxGraph16);
    DropVtxMG->Add(IntVtxGraph17);
    DropVtxMG->Add(IntVtxGraph18);
    DropVtxMG->Add(IntVtxGraph19);
    DropVtxMG->Add(IntVtxGraph20);
    DropVtxMG->Add(IntVtxGraph21);

    DropPriMG->Add(IntPriGraph1);
    DropPriMG->Add(IntPriGraph2);
    DropPriMG->Add(IntPriGraph3);
    DropPriMG->Add(IntPriGraph4);
    DropPriMG->Add(IntPriGraph5);
    DropPriMG->Add(IntPriGraph6);
    DropPriMG->Add(IntPriGraph7);
    DropPriMG->Add(IntPriGraph8);
    DropPriMG->Add(IntPriGraph9);
    DropPriMG->Add(IntPriGraph10);
    DropPriMG->Add(IntPriGraph11);
    DropPriMG->Add(IntPriGraph12);
    DropPriMG->Add(IntPriGraph13);
    DropPriMG->Add(IntPriGraph14);
    DropPriMG->Add(IntPriGraph15);
    DropPriMG->Add(IntPriGraph16);
    DropPriMG->Add(IntPriGraph17);
    DropPriMG->Add(IntPriGraph18);
    DropPriMG->Add(IntPriGraph19);
    DropPriMG->Add(IntPriGraph20);
    DropPriMG->Add(IntPriGraph21);

    VtxMG->Add(VtxGraph1);
    VtxMG->Add(VtxGraph2);
    VtxMG->Add(VtxGraph3);
    VtxMG->Add(VtxGraph4);
    VtxMG->Add(VtxGraph5);
    VtxMG->Add(VtxGraph6);
    VtxMG->Add(VtxGraph7);
    VtxMG->Add(VtxGraph8);
    VtxMG->Add(VtxGraph9);
    VtxMG->Add(VtxGraph10);
    VtxMG->Add(VtxGraph11);
    VtxMG->Add(VtxGraph12);
    VtxMG->Add(VtxGraph13);
    VtxMG->Add(VtxGraph14);
    VtxMG->Add(VtxGraph15);
    VtxMG->Add(VtxGraph16);
    VtxMG->Add(VtxGraph17);
    VtxMG->Add(VtxGraph18);
    VtxMG->Add(VtxGraph19);
    VtxMG->Add(VtxGraph20);
    VtxMG->Add(VtxGraph21);

    PriMG->Add(PriGraph1);
    PriMG->Add(PriGraph2);
    PriMG->Add(PriGraph3);
    PriMG->Add(PriGraph4);
    PriMG->Add(PriGraph5);
    PriMG->Add(PriGraph6);
    PriMG->Add(PriGraph7);
    PriMG->Add(PriGraph8);
    PriMG->Add(PriGraph9);
    PriMG->Add(PriGraph10);
    PriMG->Add(PriGraph11);
    PriMG->Add(PriGraph12);
    PriMG->Add(PriGraph13);
    PriMG->Add(PriGraph14);
    PriMG->Add(PriGraph15);
    PriMG->Add(PriGraph16);
    PriMG->Add(PriGraph17);
    PriMG->Add(PriGraph18);
    PriMG->Add(PriGraph19);
    PriMG->Add(PriGraph20);
    PriMG->Add(PriGraph21);

    DropMG->Draw("apl");
    DropMG->SetTitle("Proton Drop Rate");
    Canvas->Print(outNameStart,"pdf");

    DropVtxMG->Draw("apl");
    DropVtxMG->SetTitle("Vertex Interaction Drop Rate");
    Canvas->Print(outName,"pdf");

    DropPriMG->Draw("apl");
    DropPriMG->SetTitle("Primary Interaction Drop Rate");
    Canvas->Print(outName,"pdf");

    VtxMG->Draw("apl");
    VtxMG->SetTitle("Vertex Interaction");
    Canvas->Print(outName,"pdf");

    PriMG->Draw("apl");
    PriMG->SetTitle("Primary Interaction");
    Canvas->Print(outNameEnd,"pdf");

    Data->Close();
}