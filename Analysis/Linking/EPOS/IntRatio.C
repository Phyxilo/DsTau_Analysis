#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

double* MCEndPoints(TTree *data);
double DataMean(TTree *data);

float migCut = 18;

TCanvas *Canvas;

TGraph *IntRatioGraph = new TGraph (7);

TFile *Data;

float dirArr[8];
float intRatio1[8], intRatio2[8];
float err1X[8], err1Y[8], err2X[8], err2Y[8];

int subV = 0;

char dir [128];

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
		int IntPar1 = 0, IntPar2 = 0, IntPar3 = 0, TotalPar = 0, ProtonNum = 0;

		//sprintf(dir,"../../../Geant4SM_v1.0/RootOut/pl0%d1_%02d0.root", j, j+3);

		if (j < 7){snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_4Sigma_New/pl0%d1_%02d0.root", j, j+3);}
		else {snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_4Sigma_New/pl071_105.root");}

		cout << dir << endl;

		//Data = TFile::Open("../Root/Geant4_p006.root");
		Data = TFile::Open(dir);
		
		TTree *parData = (TTree*)Data->Get("PAR");
		TTree *vtxData = (TTree*)Data->Get("VTX");
		TTree *ptrkData = (TTree*)Data->Get("US_PTRK");

		double *endArr = MCEndPoints(vtxData);
		double mean = DataMean(vtxData);

        //cout << endArr[0] << ", " << endArr[1] << ", " << endArr[1]-endArr[0] << endl;
		
		for (int i = 0; i < parData->GetEntriesFast(); i++)
		{
            parData->GetEntry(i);
            vtxData->GetEntry(i);

            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *flagp = parData->GetLeaf("flagp");
            TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");

            TLeaf *vx = vtxData->GetLeaf("vx");
            TLeaf *vy = vtxData->GetLeaf("vy");
            TLeaf *vz = vtxData->GetLeaf("vz");
            TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");
            TLeaf *flagw = vtxData->GetLeaf("flagw");
            TLeaf *area1 = vtxData->GetLeaf("area1");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int fp = flagp->GetValue();
            int fw = flagw->GetValue();
            int a1 = area1->GetValue();

            if (fw == 1 && vz->GetValue() - endArr[0] > migCut && vz->GetValue() - endArr[1] < -migCut)
            {
                if (vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
                {
                    if (Plt >= 5 + j*10 && Plt < 10 + j*10)
                    {                    
                        IntPar2++;
                    }
                    if (fp >= 1)
                    {
                        IntPar1++;
                    }

                    TotalPar++;
                }
                else{IntPar3++;}
            }
		}

        for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
        {
            ptrkData->GetEntry(i);

            TLeaf *area1 = ptrkData->GetLeaf("area1");
            int a1 = area1->GetValue();

            ProtonNum++;
        }

		float ratio1 = ((float)IntPar1/ProtonNum)*100;
		float ratio2 = ((float)TotalPar/ProtonNum)*100;

		intRatio1[j] = ratio1;
		intRatio2[j] = ratio2;

		IntRatioGraph->SetPoint(j, j, ratio1/ratio2);

		dirArr[j] = j;

		err1X[j] = 0; err2X[j] = 0;
		
		err1Y[j] = ((1-ratio1)/IntPar1)*100;
		err2Y[j] = ((1-ratio2)/IntPar2)*100;

		//cout << "Int: " << IntPar1 << ", Total: " << ProtonNum << ", Ratio: " << ratio1 << endl;
		cout << "Total Protons: " << ProtonNum << " | Primary Interaction: " << IntPar1 << ", Ratio: " << ratio1 << " | Vertex Points: " << TotalPar << ", Ratio: " << ratio2 << " | Out Points: " << IntPar2 << ", Ratio: " << ((float)IntPar3/ProtonNum)*100 << endl;
    }

    TGraphErrors *IntGrapEr1 = new TGraphErrors(7, dirArr, intRatio1, err1X, err1Y);
    
    IntGrapEr1->Fit("pol1");
    
    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);
    IntGrapEr1->SetMarkerColor(4);
    IntGrapEr1->SetMinimum(0);
    IntGrapEr1->SetMaximum(1.5);

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
    IntGrapEr2->SetMaximum(1.5);

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

double* MCEndPoints(TTree *data)
{
    TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

    static double endPoints[2];

    for (int i = 0; i < data->GetEntriesFast(); i++)
    {
        data->GetEntry(i);
        
        TLeaf *vz = data->GetLeaf("vz");
        TLeaf *w = data->GetLeaf("flagw");
        TLeaf *area1 = data->GetLeaf("area1");
        TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

        if (parNum->GetValue() == 1)
        {
            if (w->GetValue() == 1)
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
        TLeaf *w = data->GetLeaf("flagw");
        TLeaf *area1 = data->GetLeaf("area1");
        TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

        if (parNum->GetValue() == 1)
        {
            if (w->GetValue() == 1)
            {
                InterHist->Fill(vz->GetValue());
            }
        }
    }

    mean = InterHist->GetMean();

    delete InterHist;

    return mean;
}