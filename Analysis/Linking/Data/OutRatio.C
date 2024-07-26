#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

double* DataEndPoints(TTree *data);
double DataMean(TTree *data);

TCanvas *Canvas;
TFile *Data;

float migCut = 18;
float dataCorrection = 1.05;

char dir [128];

void OutRatio()
{

    for (int j = 0; j < 8; j++)
    {
        float InVtx = 0, OutVtx = 0, TotVtx = 0;

        snprintf(dir, 128, "../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p0%d6.root", j);

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

            bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29)); //New Method

            if (iMed->GetValue() == 1)
            {
                if (vz->GetValue() > mean - (250-migCut)/dataCorrection && vz->GetValue() < mean + (250-migCut)/dataCorrection)
                {
                    InVtx++;
                }
                else
                {
                    OutVtx++;
                }
                TotVtx++;
            }

        }

        //float vtxNumRatio = (TotVtx-InVtx)/TotVtx;
        float vtxNumRatio = (InVtx)/TotVtx;
        
        cout << vtxNumRatio << endl;
        
    }
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