#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

double* DataEndPoints(TTree *data);
double DataMean(TTree *data);

TCanvas *Canvas;

TGraph *IntRatioGraph = new TGraph (7);

TFile *Data;

float dirArr[8];
float intRatio1[8], intRatio2[8];
float err1X[8], err1Y[8], err2X[8], err2Y[8];

float migCut = 18;
double dataCorrection = 1;

//int posXMin = 56000, posXMax = 74000;
//int posYMin = 56000, posYMax = 74000;

float posXMin = 57000, posXMax = 73000;
float posYMin = 57000, posYMax = 73000;

char dir [128];

int areaTest = 50;

void IntRatio()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    snprintf(outName, 64, "IntRatio.pdf");
    snprintf(outNameStart, 64, "%s(", outName);
    snprintf(outNameEnd, 64, "%s)", outName);

    for (int j = 0; j < 8; j++)
    {
        int IntPar1 = 0, TotalPar = 0, IntPar2 = 0;

        //sprintf(dir,"../../../Geant4SM_v1.0/RootOut/pl0%d1_%02d0.root", j, j+3);
        //sprintf(dir,"../../../Data_v20220912/PD05/Linked/RootOut_TrackSel+Res5/p0%d6.root", j);
        snprintf(dir, 128, "../../../Data_v20220912/PD05/Linked/RootOut_4Sigma/p0%d6.root", j);

        cout << dir << endl;

        //Data = TFile::Open("../Root/Geant4_p006.root");
        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        TTree *vtxData = (TTree*)Data->Get("VTX");
        TTree *ptrkData = (TTree*)Data->Get("US_PTRK");

        double *endArr = DataEndPoints(vtxData);
        double mean = DataMean(vtxData);

        //cout << endArr[0] + migCut << ", " << endArr[1] - migCut << ", " << endArr[1]-endArr[0] << endl;
        
        for (int i = 0; i < vtxData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);
            vtxData->GetEntry(i);

            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *flagp = parData->GetLeaf("flagp");
            TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");
            TLeaf *plmax = parData->GetLeaf("pl_up1ry_plmax");

            TLeaf *vx = vtxData->GetLeaf("vx");
            TLeaf *vy = vtxData->GetLeaf("vy");
            TLeaf *vz = vtxData->GetLeaf("vz");
            TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");
            TLeaf *area1 = vtxData->GetLeaf("area1");
            TLeaf *iMed = vtxData->GetLeaf("intMed");
            TLeaf *flagw = vtxData->GetLeaf("flagw");

            float VX = vx->GetValue();
            float VY = vy->GetValue();
            int Plt = plt->GetValue();
            int fp = flagp->GetValue();

            //bool areaBool = area1->GetValue() == areaTest;

            //if (areaBool /*&& plmin->GetValue() == j*10+1*/ && (iMed->GetValue() == 1) && vz->GetValue() * dataCorrection - endArr[0] > migCut && vz->GetValue() * dataCorrection - endArr[1] < -migCut)
            if (iMed->GetValue() == 1)
            {
                if (vz->GetValue() * dataCorrection > mean - (250-migCut) && vz->GetValue() * dataCorrection < mean + (250-migCut))
                //if (vz->GetValue() * dataCorrection < endArr[1]-migCut)
                //if (vz->GetValue() * dataCorrection < mean + (250-migCut))
                //if (vz->GetValue() * dataCorrection < endArr[0] + (500-migCut))
                //if(vz->GetValue() * dataCorrection > endArr[0] + migCut && vz->GetValue() * dataCorrection < endArr[1] - migCut)
                {
                    if (fp >= 1)
                    {
                        IntPar1++;
                    }

                    TotalPar++;
                }
                else{IntPar2++;}
            }
        }

        int totProtons = 0;

        for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
        {
            ptrkData->GetEntry(i);

            TLeaf *area1 = ptrkData->GetLeaf("area1");
            TLeaf *pltFirst = ptrkData->GetLeaf("US_plt_of_1seg");

            //bool areaBool = ((area1->GetValue() <= 43 && area1->GetValue() >= 39) || (area1->GetValue() <= 34 && area1->GetValue() >= 30) || (area1->GetValue() <= 25 && area1->GetValue() >= 21));
            bool areaBool = ((area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29));  //New Method
            //bool areaBool = ((area1->GetValue() < 53 && area1->GetValue() > 47) || (area1->GetValue() < 44 && area1->GetValue() > 38) || (area1->GetValue() < 35 && area1->GetValue() > 29)); //New Method
            //bool areaBool = area1->GetValue() == areaTest;

            if(areaBool/* && pltFirst->GetValue() == 1*/){totProtons++;}
        }

        //float ratio1 = ((float)IntPar1/ptrkData->GetEntriesFast())*100;
        //float ratio2 = ((float)TotalPar/ptrkData->GetEntriesFast())*100;

        float ratio1 = ((float)IntPar1/totProtons)*100;
        float ratio2 = ((float)TotalPar/totProtons)*100;

        intRatio1[j] = ratio1;
        intRatio2[j] = ratio2;

        IntRatioGraph->SetPoint(j, j, ratio1/ratio2);

        dirArr[j] = j;

        err1X[j] = 0; err2X[j] = 0;
        
        err1Y[j] = ((1-ratio1)/IntPar1)*100;
        //err1Y[j] = 0;
        err2Y[j] = ((1-ratio2)/TotalPar)*100;
        //err2Y[j] = 0;

        cout << "Total Protons: " << totProtons << " | Primary Interaction: " << IntPar1 << ", Ratio: " << ratio1 << " | Vertex Points: " << TotalPar << ", Ratio: " << ratio2 << " | Out Points: " << IntPar2 << ", Ratio: " << ((float)IntPar2/totProtons)*100 << endl;
    }

    TGraphErrors *IntGrapEr1 = new TGraphErrors(7, dirArr, intRatio1, err1X, err1Y);
    
    IntGrapEr1->Fit("pol1");
    
    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGrapEr1->SetMarkerColor(4);
    IntGrapEr1->SetMinimum(0.);
    IntGrapEr1->SetMaximum(2.0);

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
    IntGrapEr2->SetMaximum(2.0);

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
                InterHist->Fill(vz->GetValue() * dataCorrection);
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
      if (intMedium->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue() * dataCorrection);
      }
    }
  }

  mean = InterHist->GetMean();

  delete InterHist;

  return mean;
}