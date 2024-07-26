#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

double* DataEndPoints(TTree *data);
double DataMean(TTree *data);

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

float migCut = 18;

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

TH1F *VtxIntW1 = new TH1F("VtxIntW1","Tungsten 1 Vertex Interaction",63,0,63);
TH1F *PriIntW1 = new TH1F("PriIntW1","Tungsten 1 Primary Interaction",63,0,63);
TH1F *ProIntW1 = new TH1F("ProIntW1","Tungsten 1 Proton Number",63,0,63);

TH1F *VtxIntW2 = new TH1F("VtxIntW2","Tungsten 2 Vertex Interaction",63,0,63);
TH1F *PriIntW2 = new TH1F("PriIntW2","Tungsten 2 Primary Interaction",63,0,63);
TH1F *ProIntW2 = new TH1F("ProIntW2","Tungsten 2 Proton Number",63,0,63);

TH1F *VtxIntW3 = new TH1F("VtxIntW3","Tungsten 3 Vertex Interaction",63,0,63);
TH1F *PriIntW3 = new TH1F("PriIntW3","Tungsten 3 Primary Interaction",63,0,63);
TH1F *ProIntW3 = new TH1F("ProIntW3","Tungsten 3 Proton Number",63,0,63);

TH1F *VtxIntW4 = new TH1F("VtxIntW4","Tungsten 4 Vertex Interaction",63,0,63);
TH1F *PriIntW4 = new TH1F("PriIntW4","Tungsten 4 Primary Interaction",63,0,63);
TH1F *ProIntW4 = new TH1F("ProIntW4","Tungsten 4 Proton Number",63,0,63);

TH1F *VtxIntW5 = new TH1F("VtxIntW5","Tungsten 5 Vertex Interaction",63,0,63);
TH1F *PriIntW5 = new TH1F("PriIntW5","Tungsten 5 Primary Interaction",63,0,63);
TH1F *ProIntW5 = new TH1F("ProIntW5","Tungsten 5 Proton Number",63,0,63);

TH1F *VtxIntW6 = new TH1F("VtxIntW6","Tungsten 6 Vertex Interaction",63,0,63);
TH1F *PriIntW6 = new TH1F("PriIntW6","Tungsten 6 Primary Interaction",63,0,63);
TH1F *ProIntW6 = new TH1F("ProIntW6","Tungsten 6 Proton Number",63,0,63);

TH1F *VtxIntW7 = new TH1F("VtxIntW7","Tungsten 7 Vertex Interaction",63,0,63);
TH1F *PriIntW7 = new TH1F("PriIntW7","Tungsten 7 Primary Interaction",63,0,63);
TH1F *ProIntW7 = new TH1F("ProIntW7","Tungsten 7 Proton Number",63,0,63);

TH1F *VtxIntW8 = new TH1F("VtxIntW8","Tungsten 8 Vertex Interaction",63,0,63);
TH1F *PriIntW8 = new TH1F("PriIntW8","Tungsten 8 Primary Interaction",63,0,63);
TH1F *ProIntW8 = new TH1F("ProIntW8","Tungsten 8 Proton Number",63,0,63);

TH1F *VtxHistArr[8] = 
{
    VtxIntW1, VtxIntW2, VtxIntW3, VtxIntW4, VtxIntW5, VtxIntW6, VtxIntW7, VtxIntW8
};

TH1F *PriHistArr[8] = 
{
    PriIntW1, PriIntW2, PriIntW3, PriIntW4, PriIntW5, PriIntW6, PriIntW7, PriIntW8
};

void DropSubArea3()
{
    TCanvas *Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);

    char  vtxOutName[64], vtxOutNameStart[64], vtxOutNameEnd[64];
    char  priOutName[64], priOutNameStart[64], priOutNameEnd[64];
    char  proOutName[64], proOutNameStart[64], proOutNameEnd[64];

    int ind = 0;

    snprintf(vtxOutName, 64, "DropSubArea3Vtx.pdf");
    snprintf(vtxOutNameStart, 64, "%s(", vtxOutName);
    snprintf(vtxOutNameEnd, 64, "%s)", vtxOutName);

    snprintf(priOutName, 64, "DropSubArea3Pri.pdf");
    snprintf(priOutNameStart, 64, "%s(", priOutName);
    snprintf(priOutNameEnd, 64, "%s)", priOutName);

    snprintf(proOutName, 64, "DropSubArea3Pro.pdf");
    snprintf(proOutNameStart, 64, "%s(", proOutName);
    snprintf(proOutNameEnd, 64, "%s)", proOutName);

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

            double *endArr = DataEndPoints(vtxData);
            double mean = DataMean(vtxData);

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

                if (area1->GetValue() == subA && iMed->GetValue() == 1)
                {
                    if (vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
                    {
                        if (fp >= 1)
                        {
                            IntPar++;
                            PriHistArr[j]->Fill(subA);
                        }

                        TotalPar++;
                        VtxHistArr[j]->Fill(subA);
                    }
                }
                if (area1->GetValue() > subA) break;

            }
            int totProtons = 0;

            for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
            {
                ptrkData->GetEntry(i);

                TLeaf *area1 = ptrkData->GetLeaf("area1");
                TLeaf *pltFirst = ptrkData->GetLeaf("US_plt_of_1seg");

                if(area1->GetValue() == subA)
                {
                    totProtons++;
                    ProIntW1->Fill(subA);
                }
            }
        }
    }

    gStyle->SetOptStat(0);

    for (int i = 0; i < 8; i++)
    {
        VtxHistArr[i]->Draw();

        if (i == 0){Canvas->Print(vtxOutNameStart, "pdf");}
        else if (i != 7) {Canvas->Print(vtxOutName, "pdf");}
        else if (i == 7) {Canvas->Print(vtxOutNameEnd, "pdf");}

        PriHistArr[i]->Draw();

        if (i == 0){Canvas->Print(priOutNameStart, "pdf");}
        else if (i != 7) {Canvas->Print(priOutName, "pdf");}
        else if (i == 7) {Canvas->Print(priOutNameEnd, "pdf");}
    }

    ProIntW1->Draw();
    Canvas->Print(proOutName, "pdf");

    /*
    VtxIntW1->Draw();
    Canvas->Print(outNameStart, "pdf");

    PriIntW1->Draw();
    Canvas->Print(outName, "pdf");

    ProIntW1->Draw();
    Canvas->Print(outNameEnd, "pdf");
    */
}

double* DataEndPoints(TTree *data)
{
    TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

    static double endPoints[2];

    for (int i = 0; i < data->GetEntriesFast(); i++)
    {
        data->GetEntry(i);
        
        TLeaf *vz = data->GetLeaf("vz");
        TLeaf *intMedium = data->GetLeaf("intMed");
        TLeaf *flagW = data->GetLeaf("flagw");
        TLeaf *area1 = data->GetLeaf("area1");
        TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

        bool areaBool = (area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29);
        //bool areaBool = area1->GetValue() == 31 || area1->GetValue() == 33 || area1->GetValue() == 41 || area1->GetValue() == 42 || area1->GetValue() == 51;
        //bool areaBool = area1->GetValue() == areaTest;

        if (parNum->GetValue() == 1 && areaBool)
        {
            if (intMedium->GetValue() == 1)
            {
                InterHist->Fill(vz->GetValue());
            }
        }
    }

    endPoints[0] = InterHist->FindFirstBinAbove(0);
    endPoints[1] = InterHist->FindLastBinAbove(0);

    delete InterHist;

    return endPoints;
}

double DataMean(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double mean;

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *intMedium = data->GetLeaf("intMed");
    TLeaf *flagW = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (flagW->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  mean = InterHist->GetMean();

  delete InterHist;

  return mean;
}