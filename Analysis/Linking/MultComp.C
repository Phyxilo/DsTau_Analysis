#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",35,5,40);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",35,5,40);

TFile *Data;

int subV = 0;
int posInt = 1000;

char dir [128];

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;
vector<int> intVecVertexing;

vector<int> ReadFile(char *inFile);
void HistDraw(TH1F *hist1, TH1F *hist2);

void MultComp()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char USInName[128] = "Links/connectedUS_00.dat";
    char DSInName[128] = "Links/connectedDS_00.dat";

    char outName[64], outNameStart[64], outNameEnd[64];

    sprintf(outName,"MultComp.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    float dataSize = 0;

    for (int j = 0; j < 1; j++)
    {
        UStrID = ReadFile(USInName);
        DStrID = ReadFile(DSInName);

        char dir [128];
        sprintf(dir,"../../Geant4SM_v1.0/RootOut/pl0%d1_%02d0.root", j, j+3);

        Data = TFile::Open(dir);
        
        TTree *parData = (TTree*)Data->Get("PAR");
        
        for (int i = 0; i < parData->GetEntriesFast(); i++)
        {
            parData->GetEntry(i);

            TLeaf *vx = parData->GetLeaf("vx");
            TLeaf *vy = parData->GetLeaf("vy");
            TLeaf *plt = parData->GetLeaf("plt_of_1seg");
            TLeaf *trk = parData->GetLeaf("trk_id");
            TLeaf *mlt = parData->GetLeaf("n_1ry_trk");

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int Trk = trk->GetValue();
            int Mlt = mlt->GetValue();

            if((VX < posInt && VX > -posInt) && (VY < posInt && VY > -posInt))
            {
                auto it = find(UStrID.begin(), UStrID.end(), Trk);
                if (it != UStrID.end())
                {
                    Mult1->Fill(Mlt);
                    cout << Trk << endl;
                }
                Mult2->Fill(Mlt);

                dataSize++;
            }
        }
    }

    Mult1->Scale(1/dataSize);
    Mult2->Scale(1/dataSize);

    Mult1->GetYaxis()->SetRangeUser(0, 0.1);
    HistDraw(Mult1, Mult2);
    Canvas->Print(outName, "pdf");
}

vector<int> ReadFile(char *inFile)
{
    vector<int> trIDVec;

    FILE *fUS = fopen(inFile, "r");
        
    char line[1024];
    
    int numLines = 0;
    char buff[512];

    size_t num;
    
    while ((num = fread(buff, 1, 512, fUS)) > 0)
    {
        for (int i = 0; i < num; i++)
        {
            if(buff[i] == '\n')
            {
                ++numLines;
            }
        }
        
    }
    fclose(fUS);

    const int numL = numLines;

    int trID[numLines];
    int pltID[numLines];
    int segID[numLines];
    int sxID[numLines];
    int syID[numLines];
    int szID[numLines];
    
    fUS = fopen(inFile, "r");
    
    for(int i = 0; i < numLines; i++)
    {
        fscanf(fUS, "%8d, %8d, %8d, %8d, %8d, %8d", &trID[i], &pltID[i], &segID[i], &sxID[i], &syID[i], &szID[i]);
        trIDVec.push_back(trID[i]);
    }
    fclose(fUS);

    return trIDVec;
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{

  hist1->Draw("HIST"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("Primary");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("VertexOut");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();
  
  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"Primary","f");
  legend->AddEntry(hist2,"VertexOut","f");
  legend->Draw();
}