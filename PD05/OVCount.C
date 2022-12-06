#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

float GetCommons(vector<int> vec1, vector<int> vec2);

TH1F *VtxZHist = new TH1F("VtxZ" ,"Vertex Z"  ,100, 0, 30000);
TCanvas *Canvas= new TCanvas("canvas","Result Canvas",20,20,1920,1080);

//vector<string> inFiles = {"p006.root", "p016.root", "p026.root", "p036.root", "p046.root", "p056.root", "p066.root", "p076.root", "p086.root"};
vector<string> inFiles = {"p006.root", "p016.root"};

ofstream out = ofstream("OverlappingVTX.txt", ios::out);

vector<float> datX;
vector<float> datY;
vector<float> datZ;

void OVCount()
{
  for (int in = 0; in < inFiles.size(); in++)
  {
    vector<int> eIDList; vector<int> eIDListFull;
    vector<int> tVIDList;

    int eSize = 0, ovSize = 0;

    string inFile = "RootOut/" + inFiles[in];
    char inFileArr[inFile.length() + 1]; 

    strcpy(inFileArr, inFile.c_str()); 
    
    TFile *Data = TFile::Open(inFileArr);
    TTree *TrkTree = (TTree*)Data->Get("TRK");
    TTree *VtxTree = (TTree*)Data->Get("VTX");
    TTree *ParTree = (TTree*)Data->Get("PAR");
    TTree *ParCandTree = (TTree*)Data->Get("PARCand");

    TLeaf *Par_trID = ParTree->GetLeaf("trk_id");
    TLeaf *Par_MCTX = ParTree->GetLeaf("tx");
    TLeaf *Par_MCTY = ParTree->GetLeaf("ty");
    TLeaf *Par_vtxId = ParTree->GetLeaf("vID");
    TLeaf *Par_trVX = ParTree->GetLeaf("vx");
    TLeaf *Par_trVY = ParTree->GetLeaf("vy");
    TLeaf *Par_trVZ = ParTree->GetLeaf("vz");
    TLeaf *Par_trMlt = ParTree->GetLeaf("n_1ry_trk");

    TLeaf *Trk_trID = TrkTree->GetLeaf("trk_id");
    TLeaf *Trk_MCTX = TrkTree->GetLeaf("tx");
    TLeaf *Trk_MCTY = TrkTree->GetLeaf("ty");
    TLeaf *Trk_vtxId = TrkTree->GetLeaf("vID");
    TLeaf *Trk_trVX = TrkTree->GetLeaf("vx");
    TLeaf *Trk_trVY = TrkTree->GetLeaf("vy");
    TLeaf *Trk_trVZ = TrkTree->GetLeaf("vz");
    TLeaf *Trk_trMlt = TrkTree->GetLeaf("n_1ry_trk");

    int refIDEvent = 0, currentEID = 0;

    eSize = ParTree->GetEntries();
    for (int i = 0; i < eSize; i++)
    {
      //if (i%1000 == 0) cout << i << "/" << eSize << endl;

      ParTree->GetEntry(i);
      currentEID = Par_trID->GetValue();
      eIDListFull.push_back(currentEID);

      if (find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
      {
        eIDList.push_back(currentEID);
      }
    }

    for (int i = 0; i < TrkTree->GetEntries(); i++)
    {
      TrkTree->GetEntry(i);
      tVIDList.push_back(Trk_vtxId->GetValue());
    }

    ovSize = eIDList.size();

    Read dat;

    for (int i = 0; i < ovSize; i++)
    {
      if (i%1000 == 0) cout << i << "/" << ovSize << endl;
      
      int cnt = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);
      ParTree->GetEntry(i);

      int index = 0;

      if (cnt > 1)
      {
        //out << "Index: " << i << " / " << eIDList.size() << endl;
        //out << "Parent TrackID: " << Par_trID->GetValue() << endl;

        float initVtxX = 0;
        float initVtxY = 0;
        float initVtxZ = 0;
        float initMult = 0;
        int initVID = 0;

        for (int j = 0; j < cnt; j++)
        {

          auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eIDList[i]);
          if (it != eIDListFull.end())
          {
            index = it - eIDListFull.begin();
            ParTree->GetEntry(index);

            int VtxX = Par_trVX->GetValue();
            int VtxY = Par_trVY->GetValue();
            int VtxZ = Par_trVZ->GetValue();

            if (j == 0)
            {
              initVtxX = VtxX;
              initVtxY = VtxY;
              initVtxZ = VtxZ;
              initMult = Par_trMlt->GetValue();
              initVID = Par_vtxId->GetValue();
            }
            else if (abs(initVtxX-VtxX) <= 100 && abs(initVtxY-VtxY) <= 100 && abs(initVtxZ-VtxZ) <= 100)
            {
              vector<int> fTrID, sTrID;

              datX.push_back(VtxX); datX.push_back(initVtxX);
              datY.push_back(VtxY); datY.push_back(initVtxY);

              VtxZHist->Fill(VtxZ); VtxZHist->Fill(initVtxZ);

              out << "Index: " << i << " / " << eIDList.size() << endl;
              out << fixed << setprecision(0) << "Parent TrackID: " << Par_trID->GetValue() << endl;

              int mult = initMult;
              int indexSec = 0, dCount = 1;

              out << "Parent #" << 1 << ": Mult: " << initMult-1 << ", Vertex X: " << initVtxX << ", Vertex Y: " << initVtxY << ", Vertex Z: " << initVtxZ << endl;

              out << "---------------Daughters---------------" << endl;
              for (int mlt = 0; mlt < mult-1; mlt++)
              {
                auto iter = find(tVIDList.begin() + indexSec + 1, tVIDList.end(), initVID);
                if (iter != tVIDList.end())
                {
                  indexSec = iter - tVIDList.begin();
                  TrkTree->GetEntry(indexSec);

                  int trID = Trk_trID->GetValue();
                  fTrID.push_back(trID);

                  out << dCount << ". " << fixed << trID << endl;
                  dCount++;
                }
              }
              out << endl;

              mult = Par_trMlt->GetValue();
              indexSec = 0; dCount = 1;

              out << "Parent #" << 2 << ": Mult: " << Par_trMlt->GetValue()-1 << ", Vertex X: " << VtxX << ", Vertex Y: " << VtxY << ", Vertex Z: " << VtxZ << endl;

              out << "---------------Daughters---------------" << endl;
              for (int mlt = 0; mlt < mult-1; mlt++)
              {
                auto iter = find(tVIDList.begin() + indexSec + 1, tVIDList.end(), initVID);
                if (iter != tVIDList.end())
                {
                  indexSec = iter - tVIDList.begin();
                  TrkTree->GetEntry(indexSec);

                  int trID = Trk_trID->GetValue();
                  sTrID.push_back(trID);

                  out << dCount << ". " << fixed << trID << endl;
                  dCount++;
                }
              }
              out << endl;

              float commons = GetCommons(fTrID, sTrID);
              out << "Number of common tracks: " << commons << endl;
              out << "Commons percentage: " << (commons/(fTrID.size()+sTrID.size()-commons))*100 << "%" << endl;
              out << "***************************************" << endl;
              out << endl;

            }
          }
        }
        //out << endl;

      }
    }
  }
  
  VtxZHist->Draw();
  Canvas->Print( "OVResult.pdf(", "pdf");

  float DataX[datX.size()], DataY[datY.size()];

  copy(datX.begin(), datX.end(), DataX);
  copy(datY.begin(), datY.end(), DataY);

  TGraph *DataXY = new TGraph(datX.size(), DataX, DataY);

  DataXY->SetTitle("Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
  DataXY->Draw("AP");
  Canvas->Print( "OVResult.pdf)", "pdf");

  //out << "Full List Size: " << eIDListFull.size() << ", List Size: " << eIDList.size() << endl;
}

float GetCommons(vector<int> vec1, vector<int> vec2)
{
  float cnt = 0;

  if (vec1.size() <= vec2.size())
  {
    for (int i = 0; i < vec1.size(); i++)
    {
      if (find(vec2.begin(), vec2.end(), vec1[i]) != vec2.end())
      {
        cnt++;
      }
    }
    //cout << cnt << endl;
    //return cnt/vec1.size();
  }
  else
  {
    for (int i = 0; i < vec2.size(); i++)
    {
      if (find(vec1.begin(), vec1.end(), vec2[i]) != vec1.end())
      {
        cnt++;
      }
    }
    //cout << cnt << endl;
    //return cnt/vec2.size();
  }

  return cnt;
}

void DataRead(TFile *Dat)
{
  TFile *Data = TFile::Open(Dat);
  TTree *TrkTree = (TTree*)Data->Get("TRK");
  TTree *VtxTree = (TTree*)Data->Get("VTX");
  TTree *ParTree = (TTree*)Data->Get("PAR");
  TTree *ParCandTree = (TTree*)Data->Get("PARCand");
}