#include <iostream>

using namespace std;

double* DataEndPoints(TTree *data);
double* MCEndPoints(TTree *data);
double DataMean(TTree *data);
double DataMedian(TTree *data);
bool isInAcceptance(int index);
bool isInAera(int index, int posX, int posY);
bool isInVolume(int posZ, int mean);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TFile *Data;

double *dataEndArr;
float migCut = 18;

float totVtxNum = 0, inVtxNum = 0;

void EdgeMultComp()
{
  char outVtxName[64], outVtxNameStart[64], outVtxNameEnd[64];
  char outMultName[64], outMultNameStart[64], outMultNameEnd[64];
  char outVolMultName[64], outVolMultNameStart[64], outVolMultNameEnd[64];

  float dataSize = 0;

  sprintf(outVtxName, "EdgeVtxComp.pdf");
  sprintf(outVtxNameStart,"%s(", outVtxName);
  sprintf(outVtxNameEnd,"%s)", outVtxName);

  sprintf(outMultName, "EdgeMultComp.pdf");
  sprintf(outMultNameStart,"%s(", outMultName);
  sprintf(outMultNameEnd,"%s)", outMultName);

  sprintf(outVolMultName, "EdgeVolMultComp.pdf");
  sprintf(outVolMultNameStart,"%s(", outVolMultName);
  sprintf(outVolMultNameEnd,"%s)", outVolMultName);

  for (int j = 0; j < 8; j++)
  {
    int inNum = 0, outNum = 0;

    char dir [128];

    sprintf(dir, "../../Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data = TFile::Open(dir);
    
    TTree *vtxData = (TTree*)Data->Get("VTX");

    dataEndArr = DataEndPoints(vtxData);
    //dataEndArr = MCEndPoints(vtxData);

    double mean = DataMean(vtxData);
    //double mean = DataMedian(vtxData);

    TH2F *vtx2DIn = new TH2F("vtx2DIn","Position Distribution",200,10000,120000,200,10000,90000);
    TH2F *vtx2DOut = new TH2F("vtx2DOut","Position Distribution",200,10000,120000,200,10000,90000);

    TH1F *mult2DIn = new TH1F("mult2DIn", "Multiplicity Distribution", 50, 0, 50);
    TH1F *mult2DOut = new TH1F("mult2DOut", "Multiplicity Distribution", 50, 0, 50);

    TH1F *mult2DInVol = new TH1F("mult2DInVol", "Multiplicity Distribution", 50, 0, 50);
    TH1F *mult2DOutVol = new TH1F("mult2DOutVol", "Multiplicity Distribution", 50, 0, 50);
    
    for (int i = 0; i < vtxData->GetEntriesFast(); i++)
    {
      vtxData->GetEntry(i);

      TLeaf *vx = vtxData->GetLeaf("vx");
      TLeaf *vy = vtxData->GetLeaf("vy");
      TLeaf *vz = vtxData->GetLeaf("vz");
      TLeaf *w = vtxData->GetLeaf("flagw");
      TLeaf *iMed = vtxData->GetLeaf("intMed");
      TLeaf *area1 = vtxData->GetLeaf("area1");
      TLeaf *mult = vtxData->GetLeaf("n_1ry_trk");

      if (iMed->GetValue() == 1)
      {
        totVtxNum++;

        if (isInAcceptance(area1->GetValue()))
        {
          if (vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
          {
            if(isInAera(area1->GetValue(), vx->GetValue(), vy->GetValue()))
            {
              vtx2DIn->Fill(vx->GetValue(), vy->GetValue());
              mult2DIn->Fill(mult->GetValue());

              inNum++;
            }
            else
            {
              vtx2DOut->Fill(vx->GetValue(), vy->GetValue());
              mult2DOut->Fill(mult->GetValue());

              outNum++;
            }

            inVtxNum++;
          }

          if (isInVolume(vz->GetValue(), mean))
          {
            mult2DInVol->Fill(mult->GetValue());
          }
          else
          {
            mult2DOutVol->Fill(mult->GetValue());
          }
        }
      }

      dataSize++;
    }

    if(j == 0)
    {
      vtx2DIn->Draw();
      vtx2DIn->SetMarkerColor(kBlue);

      vtx2DOut->Draw("SAMES");
      vtx2DOut->SetMarkerColor(kRed);

      Canvas->Print(outVtxNameStart, "pdf");
    }
    else if(j == 7)
    {
      vtx2DIn->Draw();
      vtx2DIn->SetMarkerColor(kBlue);

      vtx2DOut->Draw("SAMES");
      vtx2DOut->SetMarkerColor(kRed);

      Canvas->Print(outVtxNameEnd, "pdf");
    }
    else
    {
      vtx2DIn->Draw();
      vtx2DIn->SetMarkerColor(kBlue);

      vtx2DOut->Draw("SAMES");
      vtx2DOut->SetMarkerColor(kRed);

      Canvas->Print(outVtxName, "pdf");
    }

    if(j == 0)
    {
      mult2DOut->Scale(mult2DIn->Integral()/mult2DOut->Integral());

      mult2DIn->Draw("HIST E1");
      mult2DIn->SetLineColor(kBlue);

      mult2DOut->Draw("SAMES HIST E1");
      mult2DOut->SetLineColor(kRed);

      Canvas->Print(outMultNameStart, "pdf");
    }
    else if(j == 7)
    {
      mult2DOut->Scale(mult2DIn->Integral()/mult2DOut->Integral());

      mult2DIn->Draw("HIST E1");
      mult2DIn->SetLineColor(kBlue);

      mult2DOut->Draw("SAMES HIST E1");
      mult2DOut->SetLineColor(kRed);

      Canvas->Print(outMultNameEnd, "pdf");
    }
    else
    {
      mult2DOut->Scale(mult2DIn->Integral()/mult2DOut->Integral());

      mult2DIn->Draw("HIST E1");
      mult2DIn->SetLineColor(kBlue);

      mult2DOut->Draw("SAMES HIST E1");
      mult2DOut->SetLineColor(kRed);

      Canvas->Print(outMultName, "pdf");
    }

    if(j == 0)
    {
      mult2DOutVol->Scale(mult2DInVol->Integral()/mult2DOutVol->Integral());

      mult2DInVol->Draw("HIST E1");
      mult2DInVol->SetLineColor(kBlue);

      mult2DOutVol->Draw("SAMES HIST E1");
      mult2DOutVol->SetLineColor(kRed);

      Canvas->Print(outVolMultNameStart, "pdf");
    }
    else if(j == 7)
    {
      mult2DOutVol->Scale(mult2DInVol->Integral()/mult2DOutVol->Integral());

      mult2DInVol->Draw("HIST E1");
      mult2DInVol->SetLineColor(kBlue);

      mult2DOutVol->Draw("SAMES HIST E1");
      mult2DOutVol->SetLineColor(kRed);

      Canvas->Print(outVolMultNameEnd, "pdf");
    }
    else
    {
      mult2DOutVol->Scale(mult2DInVol->Integral()/mult2DOutVol->Integral());

      mult2DInVol->Draw("HIST E1");
      mult2DInVol->SetLineColor(kBlue);

      mult2DOutVol->Draw("SAMES HIST E1");
      mult2DOutVol->SetLineColor(kRed);

      Canvas->Print(outVolMultName, "pdf");
    }
    
    //cout << "Ratio: " << (float)inNum/(float)(inNum+outNum) << endl;
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

bool isInAcceptance(int index)
{
  int acceptanceCut[21] = 
  {
    29, 30, 31, 32, 33, 34, 35,
    38, 39, 40, 41, 42, 43, 44,
    47, 48, 49, 50, 51, 52, 53
  };

  for (int i = 0; i < 21; i++)
  {
    if (acceptanceCut[i] == index)
    {
      return true;
      break;
    }
  }
  return false;
}

bool isInAera(int index, int posX, int posY)
{
  float stepX = 15000;
  float stepY = 15000;

  float initX = 5000;
  float initY = 5000;
  
  int posXMin = initX + ((index-1)%9)*stepX - stepX/2;
  int posYMin = initY + ((index-1)/9)*stepY - stepY/2;
  int posXMax = posXMin + stepX;
  int posYMax = posYMin + stepY;

  posXMin += 1000;
  posYMin += 1000;
  posXMax -= 1000;
  posYMax -= 1000;

  //cout << "Area: " << index << ", " << posXMin << ", " << posXMax << ", " << posYMin << ", " << posYMax << endl;
  //cout << "Area: " << index << ", " << posX << ", " << posY << endl;

  if (posX > posXMin && posX < posXMax && posY > posYMin && posY < posYMax)
  {
    return true;
  }

  return false;
}

bool isInVolume(int posZ, int mean)
{
  
  int posZMax = mean + (250-migCut);
  int posZMin = mean - (250-migCut);

  //cout << "Area: " << index << ", " << posXMin << ", " << posXMax << ", " << posYMin << ", " << posYMax << endl;
  //cout << "Area: " << index << ", " << posX << ", " << posY << endl;

  if (posZ > posZMin && posZ < posZMax)
  {
    return true;
  }

  return false;
}