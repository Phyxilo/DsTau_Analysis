#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

#include "TPaveStats.h"
#include "TPaveText.h"
#include "TText.h"
#include "TPavesText.h"

using namespace std;

void Analysis_Sato()
{
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,800,800);
  Canvas->SetWindowSize(800, 800);

  TH2F *MultThetaHist1 = new TH2F("MultTheta","Multiplicity vs. Theta",50,0,50,50,0,0.2);
  TH2F *MultThetaHist2 = new TH2F("MultThetaXNorm","Multiplicity vs. Theta",50,0,50,50,0,0.2);
  TH2F *MultThetaHist3 = new TH2F("MultThetaYNorm","Multiplicity vs. Theta",50,0,50,50,0,0.2);

	FILE *fpo;
	fpo= fopen("Trk_dump.dat","wt");
	
  TFile *Data1, *Data2;

  int Data1TrkIndex = 0, Data2TrkIndex = 0;

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"Analysis.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  //Data1 = TFile::Open("../Root/p006.root");
  //Data1 = TFile::Open("../Root/Pythia.root");
  Data1 = TFile::Open("../Root/PD05.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  //TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  int preVID = -1;
  int ind = 0;
  int ntr=0;
  int last=-1;
  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++){
      treeDataTrk1->GetEntry(i);

      TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataTrk1->GetLeaf("flagw");
      TLeaf *vID = treeDataTrk1->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if (w->GetValue() == 1){
          TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
          TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
          TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
          TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");

          double TX = slpTX->GetValue() - beamTX->GetValue();
          double TY = slpTY->GetValue() - beamTY->GetValue();
          double T2 = sqrt(TX*TX+TY*TY);

          treeDataVtx1->GetEntry(vtxIndex);
          TLeaf *mlt = treeDataVtx1->GetLeaf("n_1ry_trk");

          if (vtxIndex!=last) {
              ntr=0;
              fprintf(fpo,"-------------------------------------------\n");
          }
          ntr +=1;

// printout information
          fprintf(fpo,   "%6d %4.0f %3d %8.5f %8.5f %8.5f\n", vtxIndex, mlt->GetValue(), ntr, slpTX->GetValue(), slpTY->GetValue(), T2);
          last = vtxIndex;
          
          MultThetaHist1->Fill(mlt->GetValue(), T2);

          /*
          if (vtxIndex != preVID)
          {
            if (ind == mlt->GetValue())
            {
              for (int x = ind; x > 0; x--)
              {
                MultThetaHist1->Fill(mlt->GetValue(), T2);
                //cout << "Index: " << ind << ", VtxIndex: " << vtxIndex << endl;
              }

              //cout << "Index: " << ind << ", VtxIndex: " << vtxIndex << endl;

            }

            preVID = vtxIndex;
            ind = 0;
          }

          ind++;
          //cout << "Index: " << ind << ", Mlt: " << mlt->GetValue() << endl;
          */
      }
  }
	fclose(fpo);
	
  int binx = 50, biny = 50;
  float num, Entry;

  for (int i = 0; i < binx; i++) 
  {
    num = 0;
    for (int j = 0; j < biny; j++)
    {
      num += MultThetaHist1->GetBinContent(i, j);
    }

    for (int j = 0; j < biny; j++)
    {
      Entry = MultThetaHist1->GetBinContent(i, j);
      if (num > 0) MultThetaHist2->SetBinContent(i, j, Entry*100./num);
      if (num == 0) MultThetaHist2->SetBinContent(i, j, 0);
    }
  }

  /*
  for (int j = 0; j < biny; j++) 
  {
    num = 0;
    for (int i = 0; i < binx; i++)
    {
      num += MultThetaHist1->GetBinContent(i, j);
    }

    for (int i = 0; i < binx; i++)
    {
      Entry = MultThetaHist1->GetBinContent(i, j);
      if (num > 0) MultThetaHist3->SetBinContent(i, j, Entry*100./num);
      if (num == 0) MultThetaHist3->SetBinContent(i, j, 0);
    }
  }
  */
  MultThetaHist1->SetContour(20);
  MultThetaHist2->SetContour(20);

  gStyle->SetOptStat(0);
//  gStyle->SetPalette(kRainBow); // KRainBow ����`����Ă��Ȃ��B

  MultThetaHist1->Draw("COLZ");
  //MultThetaHist1->SetMinimum(0);
  //MultThetaHist1->SetMaximum(100);
  MultThetaHist1->SetXTitle("Multiplicity");
  MultThetaHist1->SetYTitle("Theta (mrad)");

  Canvas->Print( outNameStart, "pdf");

  MultThetaHist2->Draw("COLZ");
  //MultThetaHist2->SetMinimum(0);
  MultThetaHist2->SetMaximum(12);
  MultThetaHist2->SetXTitle("Multiplicity");
  MultThetaHist2->SetYTitle("Theta (mrad)");

  Canvas->Print( outNameEnd, "pdf");
  /*
  MultThetaHist3->Draw("COLZ");
  //MultThetaHist3->SetMinimum(0);
  MultThetaHist3->SetMaximum(12);
  MultThetaHist3->SetXTitle("Multiplicity");
  MultThetaHist3->SetYTitle("Theta (mrad)");

  Canvas->Print( outNameEnd, "pdf");
  */
}