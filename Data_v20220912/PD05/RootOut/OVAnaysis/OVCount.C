#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

int notCovered;

float GetCommons(vector<int> vec1, vector<int> vec2);
void HistDraw(TH1F *hist1, TH1F *hist2);

TH1F *VtxZHist = new TH1F("VtxZ" ,"Vertex Z"  ,100, 0, 30000);
TCanvas *Canvas= new TCanvas("canvas","Result Canvas",20,20,1920,1080);

TH1F *Mult1 = new TH1F("Mlt","Multiplicity",45,5,50);
TH1F *Mult2 = new TH1F("Mlt","Multiplicity",45,5,50);

//vector<string> inFiles = {"p006.root", "p016.root", "p026.root", "p036.root", "p046.root", "p056.root", "p066.root", "p076.root", "p086.root"};
vector<string> inFiles = {"p006.root", "p016.root"};
//vector<string> inFiles = {"pl001_030.root", "pl011_040.root", "pl021_050.root", "pl031_060.root", "pl041_070.root", "pl051_080.root", "pl061_090.root", "pl071_105.root"};
//vector<string> inFiles = {"pl001_030.root", "pl011_040.root"};

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

    string inFile = "../" + inFiles[in];
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
    TLeaf *Par_area1 = ParTree->GetLeaf("area1");

    TLeaf *Trk_trID = TrkTree->GetLeaf("trk_id");
    TLeaf *Trk_MCTX = TrkTree->GetLeaf("tx");
    TLeaf *Trk_MCTY = TrkTree->GetLeaf("ty");
    TLeaf *Trk_vtxId = TrkTree->GetLeaf("vID");
    TLeaf *Trk_trVX = TrkTree->GetLeaf("vx");
    TLeaf *Trk_trVY = TrkTree->GetLeaf("vy");
    TLeaf *Trk_trVZ = TrkTree->GetLeaf("vz");
    TLeaf *Trk_trMlt = TrkTree->GetLeaf("n_1ry_trk");
    TLeaf *Trk_area1 = TrkTree->GetLeaf("area1");

    int refIDEvent = 0, currentEID = 0;

    eSize = ParTree->GetEntries();
    for (int i = 0; i < eSize; i++)
    {
      //if (i%1000 == 0) cout << i << "/" << eSize << endl;

      ParTree->GetEntry(i);

      bool areaBool = ((Par_area1->GetValue() <= 43 && Par_area1->GetValue() >= 39) || (Par_area1->GetValue() <= 34 && Par_area1->GetValue() >= 30) || (Par_area1->GetValue() <= 25 && Par_area1->GetValue() >= 21));

      if (/*areaBool*/ true)
      {
        currentEID = Par_trID->GetValue();
        eIDListFull.push_back(currentEID);

        if (find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
        {
          eIDList.push_back(currentEID);
        }
      }
    }

    for (int i = 0; i < TrkTree->GetEntries(); i++)
    {
      TrkTree->GetEntry(i);

      bool areaBool = ((Trk_area1->GetValue() <= 43 && Trk_area1->GetValue() >= 39) || (Trk_area1->GetValue() <= 34 && Trk_area1->GetValue() >= 30) || (Trk_area1->GetValue() <= 25 && Trk_area1->GetValue() >= 21));

      if(/*areaBool*/ true) {tVIDList.push_back(Trk_vtxId->GetValue());}
    }

    ovSize = eIDList.size();

    //Read dat;

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

              //Mult2->Fill(Par_trMlt->GetValue()-1);
              //Mult2->Fill(initMult-1);

              Mult2->Fill(fTrID.size());
              Mult2->Fill(sTrID.size());

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

  Double_t Data1Size = Mult1->Integral();
  Mult2->Scale(Data1Size/Mult2->Integral());

  HistDraw(Mult1, Mult2);
  Canvas->Print( "OVMult.pdf", "pdf");

  cout << notCovered << endl;
}

float GetCommons(vector<int> vec1, vector<int> vec2)
{
  float cnt = 0;

  sort(vec1.begin(), vec1.end());
  sort(vec2.begin(), vec2.end());

  vector<int> vi, vd;
  set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vi));
  set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vd));

  /*
  for (int k; k < vec1.size(); k++){cout << vec1[k] << ", ";}
  cout << endl;
  for (int k; k < vec2.size(); k++){cout << vec2[k] << ", ";}
  cout << endl;
  */

  int inter = vi.size();
  int diff = vd.size();

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

    int missingTrk = vec2.size() - (diff + inter);

    //cout << "Difference: " << diff << ", Intersection: " << inter << ", Selected: " << vec2.size() << ", Missing: " << missingTrk << endl;

    if (missingTrk != 0)
    {
      notCovered++;
    }

    Mult1->Fill(vec2.size() + missingTrk);
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

    int missingTrk = vec1.size() - (diff + inter);

    //cout << "Difference: " << diff << ", Intersection: " << inter << ", Selected: " << vec1.size() << ", Missing: " << missingTrk << endl;

    if (missingTrk != 0)
    {
      notCovered++;
    }

    Mult1->Fill(vec1.size() + missingTrk);
  }

  return cnt;
}

void HistDraw(TH1F *hist1, TH1F *hist2)
{

  hist1->Draw("HIST E1"); hist1->SetLineColor(kBlue); hist1->SetLineStyle(1); hist1->SetLineWidth(2); //hist1->SetFillColorAlpha(kBlue, 0.1);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox1->SetName("Selected");
  StatBox1->SetY1NDC(0.9);
  StatBox1->SetY2NDC(0.7);
  StatBox1->SetTextColor(kBlue);
  StatBox1->Draw();

  hist2->Draw("SAMES HIST"); hist2->SetLineColor(kRed); hist2->SetLineStyle(1); hist2->SetLineWidth(2); //hist2->SetFillColorAlpha(kRed, 0.2);

  Canvas->Update();
  TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  StatBox2->SetName("All");
  StatBox2->SetY1NDC(0.7);
  StatBox2->SetY2NDC(0.5);
  StatBox2->SetTextColor(kRed);
  StatBox2->Draw();

  TLegend *legend = new TLegend(0.1, 0.85, 0.32, 0.95);
  legend->AddEntry(hist1,"Selected","f");
  legend->AddEntry(hist2,"All Vertices","f");
  legend->Draw();
}