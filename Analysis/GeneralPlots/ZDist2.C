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
double dataCorrection = 1.05;

float totVtxNum = 0, inVtxNum = 0;

void ZDist2()
{
    char outName[64], outNameStart[64], outNameEnd[64];

    float dataSize = 0;

    sprintf(outName, "ZDist2.pdf");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    TH1F *zDistFull = new TH1F("","",50000/250,0,50000);
    TH1F *zDistFullCutted = new TH1F("","",50000/250,0,50000);

    double prevMean = 0;

    for (int j = 0; j < 8; j++)
    {
        char dir [128];

        int zWMin = 2520+(5700*j);
        int zWMax = zWMin+500;

        sprintf(dir, "../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p%02d6.root", j);

        //if (j < 7) { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl%02d1_%02d0.root", j, j + 3); }
        //else { sprintf(dir, "/Users/emin/Desktop/Workspace/DsTau_Analysis/EPOSSM_v2.1/Linked/RootOut/pl071_105.root"); }

        Data = TFile::Open(dir);
        
        TTree *vtxData = (TTree*)Data->Get("VTX");

        dataEndArr = DataEndPoints(vtxData);
        //dataEndArr = MCEndPoints(vtxData);

        double mean = DataMean(vtxData);
        //double mean = DataMedian(vtxData);

        cout << "Mean: " << mean << ", Dif: " << mean-prevMean << endl;

        prevMean = mean;

        TH1F *zDist = new TH1F("ZDist","",900/3,dataEndArr[0]-200,dataEndArr[1]+200);
        TH1F *zDistCutted = new TH1F("ZDistCutted","",900/3,dataEndArr[0]-200,dataEndArr[1]+200);

        //cout << dataEndArr[1] - dataEndArr[0] << endl;
        
        for (int i = 0; i < vtxData->GetEntriesFast(); i++)
        {
          vtxData->GetEntry(i);

          TLeaf *vz = vtxData->GetLeaf("vz");
          TLeaf *w = vtxData->GetLeaf("flagw");
          TLeaf *iMed = vtxData->GetLeaf("intMed");

          if (iMed->GetValue() == 1)
          //if (w->GetValue() == 1)
          {
            zDist->Fill(vz->GetValue() * dataCorrection);
            zDistFull->Fill(vz->GetValue() * dataCorrection);

            totVtxNum++;

            //if (vz->GetValue() - dataEndArr[0] > migCut && vz->GetValue() - dataEndArr[1] < -migCut)
            //if (vz->GetValue() > zWMin+migCut && vz->GetValue() < zWMax-migCut)
            if (vz->GetValue() * dataCorrection > mean - (250-migCut) && vz->GetValue() * dataCorrection < mean + (250-migCut))
            {
              zDistCutted->Fill(vz->GetValue() * dataCorrection);
              zDistFullCutted->Fill(vz->GetValue() * dataCorrection);
              
              inVtxNum++;
            }
          }

          dataSize++;
        }

        float vtxNumRatio = (totVtxNum-inVtxNum)/totVtxNum;

        cout << "Ratio: " << vtxNumRatio << endl;

        gStyle->SetOptStat(0);

        zDist->SetXTitle("Z (#mum)");

        if(j == 0)
        {
          zDist->Draw();
          zDistCutted->Draw("SAMES");
          zDistCutted->SetLineColor(kRed);
          Canvas->Print(outNameStart, "pdf");
        }
        else if(j == 7)
        {
          zDist->Draw();
          zDistCutted->Draw("SAMES");
          zDistCutted->SetLineColor(kRed);
          Canvas->Print(outName, "pdf");

          zDistFull->Draw();
          zDistFullCutted->Draw("SAMES");
          zDistFullCutted->SetLineColor(kRed);
          Canvas->Print(outNameEnd, "pdf");
        }
        else
        {
          zDist->Draw();
          zDistCutted->Draw("SAMES");
          zDistCutted->SetLineColor(kRed);
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
        InterHist->Fill(vz->GetValue() * dataCorrection);
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
        InterHist->Fill(vz->GetValue() * dataCorrection);
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
        InterHist->Fill(vz->GetValue() * dataCorrection);
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
        InterHist->Fill(vz->GetValue() * dataCorrection);
      }
    }
  }

  InterHist->ComputeIntegral();
  InterHist->GetQuantiles(1, &median, &q);

  delete InterHist;

  return median;
  
}