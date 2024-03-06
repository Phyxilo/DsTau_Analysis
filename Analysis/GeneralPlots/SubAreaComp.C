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

TH1F *multComp1 = new TH1F("multComp1", "Multiplicity Distribution Sub-Area1", 50, 0, 50);
TH1F *multComp2 = new TH1F("multComp2", "Multiplicity Distribution Sub-Area2", 50, 0, 50);
TH1F *multComp3 = new TH1F("multComp3", "Multiplicity Distribution Sub-Area3", 50, 0, 50);
TH1F *multComp4 = new TH1F("multComp4", "Multiplicity Distribution Sub-Area4", 50, 0, 50);
TH1F *multComp5 = new TH1F("multComp5", "Multiplicity Distribution Sub-Area5", 50, 0, 50);
TH1F *multComp6 = new TH1F("multComp6", "Multiplicity Distribution Sub-Area6", 50, 0, 50);
TH1F *multComp7 = new TH1F("multComp7", "Multiplicity Distribution Sub-Area7", 50, 0, 50);
TH1F *multComp8 = new TH1F("multComp8", "Multiplicity Distribution Sub-Area8", 50, 0, 50);

TH1F *IPComp1 = new TH1F("IPComp1", "IP Distribution Sub-Area1", 50, 0, 10);
TH1F *IPComp2 = new TH1F("IPComp2", "IP Distribution Sub-Area2", 50, 0, 10);
TH1F *IPComp3 = new TH1F("IPComp3", "IP Distribution Sub-Area3", 50, 0, 10);
TH1F *IPComp4 = new TH1F("IPComp4", "IP Distribution Sub-Area4", 50, 0, 10);
TH1F *IPComp5 = new TH1F("IPComp5", "IP Distribution Sub-Area5", 50, 0, 10);
TH1F *IPComp6 = new TH1F("IPComp6", "IP Distribution Sub-Area6", 50, 0, 10);
TH1F *IPComp7 = new TH1F("IPComp7", "IP Distribution Sub-Area7", 50, 0, 10);
TH1F *IPComp8 = new TH1F("IPComp8", "IP Distribution Sub-Area8", 50, 0, 10);

TFile *Data;

double *dataEndArr;
float migCut = 18;

float totVtxNum = 0, inVtxNum = 0;

void SubAreaComp()
{
  char outMultName[64], outMultNameStart[64], outMultNameEnd[64];
  char outIPName[64], outIPNameStart[64], outIPNameEnd[64];

  float dataSize = 0;

  sprintf(outMultName, "SubAreaMultComp.pdf");
  sprintf(outMultNameStart,"%s(", outMultName);
  sprintf(outMultNameEnd,"%s)", outMultName);

  sprintf(outIPName, "SubAreaIPComp.pdf");
  sprintf(outIPNameStart,"%s(", outIPName);
  sprintf(outIPNameEnd,"%s)", outIPName);

  for (int j = 0; j < 8; j++)
  {
    int inNum = 0, outNum = 0;

    char dir [128];

    sprintf(dir, "../../Data_v20220912/PD05/Linked/RootOut/p%02d6.root", j);

    Data = TFile::Open(dir);
    
    TTree *vtxData = (TTree*)Data->Get("VTX");
    TTree *trkData = (TTree*)Data->Get("TRK");

    dataEndArr = DataEndPoints(vtxData);
    //dataEndArr = MCEndPoints(vtxData);

    double mean = DataMean(vtxData);
    //double mean = DataMedian(vtxData);
    
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
            if(j == 0)
            {
              multComp1->Fill(mult->GetValue());
            }
            else if(j == 1)
            {
              multComp2->Fill(mult->GetValue());
            }
            else if(j == 2)
            {
              multComp3->Fill(mult->GetValue());
            }
            else if(j == 3)
            {
              multComp4->Fill(mult->GetValue());
            }
            else if(j == 4)
            {
              multComp5->Fill(mult->GetValue());
            }
            else if(j == 5)
            {
              multComp6->Fill(mult->GetValue());
            }
            else if(j == 6)
            {
              multComp7->Fill(mult->GetValue());
            }
            else if(j == 7)
            {
              multComp8->Fill(mult->GetValue());
            }

            inVtxNum++;
          }
        }
      }

      dataSize++;
    }

    for (int i = 0; i < trkData->GetEntriesFast(); i++)
    {
      trkData->GetEntry(i);
      
      TLeaf *slpTX = trkData->GetLeaf("tx");
      TLeaf *slpTY = trkData->GetLeaf("ty");
      TLeaf *beamTX = trkData->GetLeaf("txpeak");
      TLeaf *beamTY = trkData->GetLeaf("typeak");
      TLeaf *IP = trkData->GetLeaf("ip_to_1ry_using_1stseg");
      TLeaf *vID = trkData->GetLeaf("vID");
      TLeaf *PN = trkData->GetLeaf("n_1ry_parent_dmin_cut");

      TLeaf *w = trkData->GetLeaf("flagw");

      vtxData->GetEntry(vID->GetValue());

      TLeaf *iType = vtxData->GetLeaf("intType");
      TLeaf *mult = vtxData->GetLeaf("n_1ry_trk");
      TLeaf *vz = vtxData->GetLeaf("vz");

      if (PN->GetValue() > 0 && w->GetValue() == 1 && iType->GetValue() >= 1 && vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
      {
        if(j == 0)
        {
          IPComp1->Fill(IP->GetValue());
        }
        else if(j == 1)
        {
          IPComp2->Fill(IP->GetValue());
        }
        else if(j == 2)
        {
          IPComp3->Fill(IP->GetValue());
        }
        else if(j == 3)
        {
          IPComp4->Fill(IP->GetValue());
        }
        else if(j == 4)
        {
          IPComp5->Fill(IP->GetValue());
        }
        else if(j == 5)
        {
          IPComp6->Fill(IP->GetValue());
        }
        else if(j == 6)
        {
          IPComp7->Fill(IP->GetValue());
        }
        else if(j == 7)
        {
          IPComp8->Fill(IP->GetValue());
        }
      }
    }

    if(j == 0)
    {
      multComp1->Draw();
      Canvas->Print(outMultNameStart, "pdf");

      IPComp1->Draw();
      Canvas->Print(outIPNameStart, "pdf");
    }
    else if(j == 1)
    {
      multComp2->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp2->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 2)
    {
      multComp3->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp3->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 3)
    {
      multComp4->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp4->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 4)
    {
      multComp5->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp5->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 5)
    {
      multComp6->Draw();
      Canvas->Print(outMultName, "pdf");
      
      IPComp6->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 6)
    {
      multComp7->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp7->Draw();
      Canvas->Print(outIPName, "pdf");
    }
    else if(j == 7)
    {
      multComp8->Draw();
      Canvas->Print(outMultName, "pdf");

      IPComp8->Draw();
      Canvas->Print(outIPName, "pdf");
    }

  }

  multComp1->SetStats(0);

  multComp1->Draw("HIST");
  multComp1->SetLineColor(kBlack);

  multComp2->Draw("SAMES HIST");
  multComp2->SetLineColor(kRed);

  multComp3->Draw("SAMES HIST");
  multComp3->SetLineColor(kYellow);

  multComp4->Draw("SAMES HIST");
  multComp4->SetLineColor(kOrange);

  multComp5->Draw("SAMES HIST");
  multComp5->SetLineColor(kGreen);

  multComp6->Draw("SAMES HIST");
  multComp6->SetLineColor(kBlue);

  multComp7->Draw("SAMES HIST");
  multComp7->SetLineColor(kPink);

  multComp8->Draw("SAMES HIST");
  multComp8->SetLineColor(kViolet);

  TLegend *legend1 = new TLegend(0.74, 0.45, 0.97, 0.95);
  legend1->AddEntry(multComp1,"Sub-Area1","f");
  legend1->AddEntry(multComp2,"Sub-Area2","f");
  legend1->AddEntry(multComp3,"Sub-Area3","f");
  legend1->AddEntry(multComp4,"Sub-Area4","f");
  legend1->AddEntry(multComp5,"Sub-Area5","f");
  legend1->AddEntry(multComp6,"Sub-Area6","f");
  legend1->AddEntry(multComp7,"Sub-Area7","f");
  legend1->AddEntry(multComp8,"Sub-Area8","f");
  legend1->Draw();

  Canvas->Print(outMultNameEnd, "pdf");

  IPComp1->SetStats(0);

  IPComp1->Draw("HIST");
  IPComp1->SetLineColor(kBlack);

  IPComp2->Draw("SAMES HIST");
  IPComp2->SetLineColor(kRed);

  IPComp3->Draw("SAMES HIST");
  IPComp3->SetLineColor(kYellow);

  IPComp4->Draw("SAMES HIST");
  IPComp4->SetLineColor(kOrange);

  IPComp5->Draw("SAMES HIST");
  IPComp5->SetLineColor(kGreen);

  IPComp6->Draw("SAMES HIST");
  IPComp6->SetLineColor(kBlue);

  IPComp7->Draw("SAMES HIST");
  IPComp7->SetLineColor(kPink);

  IPComp8->Draw("SAMES HIST");
  IPComp8->SetLineColor(kViolet);

  TLegend *legend2 = new TLegend(0.74, 0.45, 0.97, 0.95);
  legend2->AddEntry(IPComp1,"Sub-Area1","f");
  legend2->AddEntry(IPComp2,"Sub-Area2","f");
  legend2->AddEntry(IPComp3,"Sub-Area3","f");
  legend2->AddEntry(IPComp4,"Sub-Area4","f");
  legend2->AddEntry(IPComp5,"Sub-Area5","f");
  legend2->AddEntry(IPComp6,"Sub-Area6","f");
  legend2->AddEntry(IPComp7,"Sub-Area7","f");
  legend2->AddEntry(IPComp8,"Sub-Area8","f");
  legend2->Draw();

  Canvas->Print(outIPNameEnd, "pdf");
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