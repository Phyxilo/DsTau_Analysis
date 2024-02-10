#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *TXHist = new TH1F("TX","TX Distribution",80,-400,400);
TH1F *TYHist = new TH1F("TY","TY Distribution",80,-400,400);
TH1F *T2Hist = new TH1F("T2","T2 Distribution",40,0,400);

TFile *Data;

void SlopeDist()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    sprintf(outName, "Slope.pdf");

    for (int j = 0; j < 8; j++)
    {
        char dir [128];

        sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p%03d.root", j*10+6);

        Data = TFile::Open(dir);
        
        TTree *vtxData = (TTree*)Data->Get("VTX");
        TTree *trkData = (TTree*)Data->Get("TRK");

        int trkSize = trkData->GetEntriesFast();
        
        for (int i = 0; i < trkSize; i++)
        {
            trkData->GetEntry(i);

            TLeaf *tx = trkData->GetLeaf("tx");
            TLeaf *ty = trkData->GetLeaf("ty");
            TLeaf *iMed = trkData->GetLeaf("intMed");
            TLeaf *vID = trkData->GetLeaf("vID");

            float TX = tx->GetValue() * 1000;
            float TY = ty->GetValue() * 1000;
            float T2 = sqrt(TX*TX+TY*TY);
            
            if (iMed->GetValue() == 1)
            {
                vtxData->GetEntry(vID->GetValue());

                TLeaf *iType = vtxData->GetLeaf("intType");

                if (iType->GetValue() == 1)
                {
                    TXHist->Fill(TX);
                    TYHist->Fill(TY);
                    T2Hist->Fill(T2);
                }
            }

            dataSize++;
        }
    }

    for (int i = 1; i <= 40; i++)
    {
        TAxis *xaxis = T2Hist->GetXaxis();
        int binCenter = xaxis->GetBinCenter(i);

        float binCont = T2Hist->GetBinContent(i);

        cout << binCenter-5 << " - " << binCenter+5 << ": " << binCont/dataSize << endl;
    }

    T2Hist->Draw();
    Canvas->Print(outName, "pdf");
}