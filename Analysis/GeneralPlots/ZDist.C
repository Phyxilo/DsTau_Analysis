#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *zDist = new TH1F("ZDist","",500,0,50000);
TH1F *zDistW = new TH1F("ZDistW","",500,0,50000);
TH1F *zDistNonW = new TH1F("ZDistNonW","",500,0,50000);

TFile *Data;

void ZDist()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    sprintf(outName, "ZDist.png");
    sprintf(outNameStart, "%s(", outName);
    sprintf(outNameEnd, "%s)", outName);

    for (int j = 0; j < 8; j++)
    {
        char dir [128];

        if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
        else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

        Data = TFile::Open(dir);
        
        TTree *vtxData = (TTree*)Data->Get("VTX");
        
        for (int i = 0; i < vtxData->GetEntriesFast(); i++)
        {
            vtxData->GetEntry(i);

            TLeaf *vz = vtxData->GetLeaf("vz");
            TLeaf *w = vtxData->GetLeaf("flagw");

            if (w->GetValue()){zDistW->Fill(vz->GetValue());}
            else{zDistNonW->Fill(vz->GetValue());}
            zDist->Fill(vz->GetValue());

            dataSize++;
        }
    }

    zDist->Draw();
    zDist->SetStats(0);
    zDist->SetLineWidth(2);
    zDist->SetLineColor(kBlue);
    zDist->SetXTitle("Z Position (#mum)");
    Canvas->Print(outName, "png");
    /*
    zDistW->Draw();
    zDistW->SetStats(0);
    zDistW->SetLineWidth(1);
    zDistW->SetLineColor(kRed);
    zDistW->SetXTitle("Z Position (#mum)");
    Canvas->Print(outName, "pdf");

    zDistW->Draw();
    zDistNonW->Draw("SAMES");
    zDistNonW->SetStats(0);
    zDistNonW->SetLineWidth(1);
    zDistNonW->SetLineColor(kBlue);
    zDistNonW->SetXTitle("Z Position (#mum)");
    Canvas->Print(outNameEnd, "pdf");
    */
}