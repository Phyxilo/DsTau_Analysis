#include <iostream>

using namespace std;

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);
double DataMedian(TTree *data);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TFile *Data;

double *dataEndArr;
float migCut = 18;

float totVtxNum = 0, inVtxNum = 0;

void IPDist()
{
  char outName[64], outNameStart[64], outNameEnd[64];

  float dataSize = 0;

  sprintf(outName, "IPDist.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  double prevMean = 0;

  TH1F *IPDistFull = new TH1F("IPDistFull","IP Distribution",100,0,10);

  for (int j = 0; j < 8; j++)
  {
    char dir [128];

    //sprintf(dir, "../../Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
    else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

    Data = TFile::Open(dir);
    
    TTree *vtxData = (TTree*)Data->Get("VTX");
    TTree *trkData = (TTree*)Data->Get("TRK");

    //dataEndArr = DataEndPoints(vtxData);
    dataEndArr = MCEndPoints(vtxData);

    double mean = DataMean(vtxData);
    //double mean = DataMedian(vtxData);

    cout << "Mean: " << mean << ", Dif: " << mean-prevMean << endl;

    prevMean = mean;

    TH1F *IPDist = new TH1F("IPDist","IP Distribution",100,0,10);
    TH1F *IPDistCutted = new TH1F("IPDistCutted","IP Distribution",100,0,10);

    for (int i = 0; i < trkData->GetEntriesFast(); i++)
    {
      trkData->GetEntry(i);

      TLeaf *ip = trkData->GetLeaf("ip_to_1ry_using_1stseg");

      IPDist->Fill(ip->GetValue());
      IPDistFull->Fill(ip->GetValue());
    }

    if(j == 0)
    {
      IPDist->Draw();
      Canvas->Print(outNameStart, "pdf");
    }
    else if(j == 7)
    {
      IPDist->Draw();
      //Canvas->Print(outName, "pdf");

      //IPDistFull->Draw();
      Canvas->Print(outNameEnd, "pdf");
    }
    else
    {
      IPDist->Draw();
      Canvas->Print(outName, "pdf");
    }
  }
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
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    bool areaBool = (area1->GetValue() <= 53 && area1->GetValue() >= 47) || (area1->GetValue() <= 44 && area1->GetValue() >= 38) || (area1->GetValue() <= 35 && area1->GetValue() >= 29);

    if (parNum->GetValue() == 1 && areaBool)
    {
      if (intMedium->GetValue() == 1)
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

double DataMedian(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  double median;
  double q = 0.5;

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

  InterHist->ComputeIntegral();
  InterHist->GetQuantiles(1, &median, &q);

  delete InterHist;

  return median;
  
}