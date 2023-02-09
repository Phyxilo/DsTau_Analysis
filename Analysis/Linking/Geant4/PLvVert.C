#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas;

TFile *Data;

int subV = 0;
int posInt = 4000;

char dir [128];

vector<int> UStrID;
vector<int> DStrID;
vector<int> intVec;
vector<int> intVecVertexing;

vector<int> ReadFile(char *inFile);

void PLvVert()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char USInName[128] = "Links/connectedUS_00.dat";
    char DSInName[128] = "Links/connectedDS_00.dat";

    char outName[64], outNameStart[64], outNameEnd[64];

    sprintf(outName,"PLvVert.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int j = 0; j < 1; j++)
    {
        UStrID = ReadFile(USInName);
        DStrID = ReadFile(DSInName);

        for (int i = 0; i < DStrID.size(); i++)
        {
            auto it = find(UStrID.begin(), UStrID.end(), DStrID[i]);
            if (it != UStrID.end())
            {
                UStrID.erase(it);
            }
        }

        intVec.assign(UStrID.begin(), UStrID.end());

        //char dir [128] = "../../Geant4SM_v1.0/RootOut/pl011_040.root";
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

            int VX = vx->GetValue();
            int VY = vy->GetValue();
            int Plt = plt->GetValue();
            int Trk = trk->GetValue();

            if(/*(VX < posInt && VX > -posInt) && (VY < posInt && VY > -posInt)*/ true)
            {
                if (Plt >= 5 + j*10 && Plt < 10 + j*10)
                {
                    intVecVertexing.push_back(Trk);
                }
            }
        }

        int commonCnt = 0;

        for (int i = 0; i < intVec.size(); i++)
        {
            auto it = find(intVecVertexing.begin(), intVecVertexing.end(), intVec[i]);
            if (it != intVecVertexing.end())
            {
                commonCnt++;
                cout << intVec[i] << endl;
            }
        }

        cout << "ProtonLinking: " << intVec.size() << ", VertexOut: " << intVecVertexing.size() << ", Commons: " << commonCnt << endl;
    }
    
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