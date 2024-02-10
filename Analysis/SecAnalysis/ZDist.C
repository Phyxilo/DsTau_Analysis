#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *zDist = new TH1F("ZDist","Z Distribution",500,0,50000);

TFile *Data;

void ZDist()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    sprintf(outName, "ZDistTungsten.png");

    for (int j = 0; j < 8; j++)
    {
        char dir [128];

        if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/PythiaCharmSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
        else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/PythiaCharmSM_v2.1/Linked/RootOut/pl071_105.root"); }

        Data = TFile::Open(dir);
        
        TTree *vtxData = (TTree*)Data->Get("VTX");
        
        for (int i = 0; i < vtxData->GetEntriesFast(); i++)
        {
            vtxData->GetEntry(i);

            TLeaf *vz = vtxData->GetLeaf("vz");
            TLeaf *w = vtxData->GetLeaf("flagw");
            TLeaf *iType = vtxData->GetLeaf("intType");

            if (iType->GetValue() == 2){zDist->Fill(vz->GetValue());}

            dataSize++;
        }
    }

    zDist->Draw();
    Canvas->Print(outName, "png");
}