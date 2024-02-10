#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TFile *Data;

int const PlotLen = 100;

float numVtxArr[PlotLen];
float sumTXVtxArr[PlotLen], sumTYVtxArr[PlotLen], sumT2VtxArr[PlotLen];
float avgTXVtxArr[PlotLen], avgTYVtxArr[PlotLen], avgT2VtxArr[PlotLen];

float VtxArrXAxis[PlotLen];
float VtxArrTXErrXAxis[PlotLen], VtxArrTXErrYAxis[PlotLen];
float VtxArrTYErrXAxis[PlotLen], VtxArrTYErrYAxis[PlotLen];
float VtxArrT2ErrXAxis[PlotLen], VtxArrT2ErrYAxis[PlotLen];

float errCalc(float N0, float N);

void AvgTrk()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    sprintf(outName,"AverageTrack.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int j = 0; j < 8; j++)
    {
        char dir [128];

        if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
        else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

        Data = TFile::Open(dir);
        
        TTree *trkData = (TTree*)Data->Get("TRK");
        TTree *vtxData = (TTree*)Data->Get("VTX");
        
        for (int i = 0; i < trkData->GetEntriesFast(); i++)
        {
            trkData->GetEntry(i);

            TLeaf *vID = trkData->GetLeaf("vID");
            TLeaf *slpTX = trkData->GetLeaf("tx");
            TLeaf *slpTY = trkData->GetLeaf("ty");
            TLeaf *beamTX = trkData->GetLeaf("txpeak");
            TLeaf *beamTY = trkData->GetLeaf("typeak");

            vtxData->GetEntry(vID->GetValue());

            TLeaf *vz = vtxData->GetLeaf("vz");
            TLeaf *w = vtxData->GetLeaf("flagw");
            TLeaf *area1 = vtxData->GetLeaf("area1");

            double TX = slpTX->GetValue() - beamTX->GetValue();
            double TY = slpTY->GetValue() - beamTY->GetValue();
            double T2 = TX*TX + TY*TY;

            int index = (int)(vz->GetValue()/500);

            sumTXVtxArr[index] = sumTXVtxArr[index] + TX;
            sumTYVtxArr[index] = sumTYVtxArr[index] + TY;
            sumT2VtxArr[index] = sumT2VtxArr[index] + T2;

            numVtxArr[index] = numVtxArr[index] + 1;

            dataSize++;
        }
    }

    for (int i = 0; i < PlotLen; i++)
    {
        if (numVtxArr[i] != 0)
        {
            avgTXVtxArr[i] = sumTXVtxArr[i] / numVtxArr[i];
            avgTYVtxArr[i] = sumTYVtxArr[i] / numVtxArr[i];
            avgT2VtxArr[i] = sumT2VtxArr[i] / numVtxArr[i];

            //VtxArrTXErrYAxis[i] = errCalc()
            //VtxArrTYErrYAxis[i] = errCalc()
            //VtxArrT2ErrYAxis[i] = errCalc()
        }
        else
        {
            avgTXVtxArr[i] = 0;
            avgTYVtxArr[i] = 0;
            avgT2VtxArr[i] = 0;

            VtxArrTXErrYAxis[i] = 0;
            VtxArrTYErrYAxis[i] = 0;
            VtxArrT2ErrYAxis[i] = 0;
        }

        VtxArrTXErrXAxis[i] = 0;
        VtxArrTYErrXAxis[i] = 0;
        VtxArrT2ErrXAxis[i] = 0;

        VtxArrXAxis[i] = i*500;
    }

    gPad->SetGrid(100);

    TGraph *AvgTrkPlotTX = new TGraph(PlotLen, VtxArrXAxis, avgTXVtxArr);
    TGraph *AvgTrkPlotTY = new TGraph(PlotLen, VtxArrXAxis, avgTYVtxArr);
    TGraph *AvgTrkPlotT2 = new TGraph(PlotLen, VtxArrXAxis, avgT2VtxArr);

    TAxis *axisTX = AvgTrkPlotTX->GetXaxis();
    //axisTX->SetLimits(4,95);
    axisTX->SetLimits(2000.,45000.);

    TAxis *axisTY = AvgTrkPlotTY->GetXaxis();
    //axisTY->SetLimits(4,95);
    axisTY->SetLimits(2000.,45000.);

    TAxis *axisT2= AvgTrkPlotT2->GetXaxis();
    //axisT2->SetLimits(4,95);
    axisT2->SetLimits(2000.,45000.);

    //TGraphErrors *AvgTrkPlotTX = new TGraphErrors(100, VtxArrXAxis, avgTXVtxArr, VtxArrTXErrXAxis, VtxArrTXErrYAxis);
    //TGraphErrors *AvgTrkPlotTY = new TGraphErrors(100, VtxArrXAxis, avgTYVtxArr, VtxArrTYErrXAxis, VtxArrTYErrYAxis);
    //TGraphErrors *AvgTrkPlotT2 = new TGraphErrors(100, VtxArrXAxis, avgT2VtxArr, VtxArrT2ErrXAxis, VtxArrT2ErrYAxis);

    AvgTrkPlotTX->Draw("AP");
    AvgTrkPlotTX->SetTitle("; Z-Position; TX;");
    AvgTrkPlotTX->SetMarkerStyle(kFullCircle);
    AvgTrkPlotTX->SetMarkerSize(2.0);
    AvgTrkPlotTX->SetMarkerColor(kRed);
    Canvas->Print(outNameStart, "pdf");

    AvgTrkPlotTY->Draw("AP");
    AvgTrkPlotTY->SetTitle("; Z-Position; TY;");
    AvgTrkPlotTY->SetMarkerStyle(kFullCircle);
    AvgTrkPlotTY->SetMarkerSize(2.0);
    AvgTrkPlotTY->SetMarkerColor(kRed);
    Canvas->Print(outName, "pdf");

    AvgTrkPlotT2->Draw("AP");
    AvgTrkPlotT2->SetTitle("; Z-Position; T2;");
    AvgTrkPlotT2->SetMarkerStyle(kFullCircle);
    AvgTrkPlotT2->SetMarkerSize(2.0);
    AvgTrkPlotT2->SetMarkerColor(kRed);
    Canvas->Print(outNameEnd, "pdf");
}

float errCalc(float N0, float N)
{
    float epsilon = N/N0;
    
    return sqrt((epsilon*(1-epsilon))/N0);
}