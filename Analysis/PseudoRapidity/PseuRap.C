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

void CanvasModifier(TH1F *hist);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *pseuRap = new TH1F("Data","",100,-2,2);
TH1F *Mult2 = new TH1F("PD05","Pseudo-rapidity Distributions",100,0,20);

TFile *Data1, *Data2;

float Data1TrkIndex = 0, Data2TrkIndex = 0;
float Data1VtxSize = 0, Data2VtxSize = 0;

void PseuRap()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  char  outName[64], outNameStart[64], outNameEnd[64];
  sprintf(outName,"PseuRap.pdf");
  sprintf(outNameStart,"%s(", outName);
  sprintf(outNameEnd,"%s)", outName);

  Data1 = TFile::Open("/Users/emin/Desktop/Workspace/DsTau_Analysis/Data_v20220912/PD05/Linked/RootOut/p006.root");
  //Data2 = TFile::Open("Root/PD04.root");
  
  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  //TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  //TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");

  /*
  for (int i = 0; i < treeDataVtx1->GetEntriesFast(); i++)
  {
    treeDataVtx1->GetEntry(i);
    
    TLeaf *mult = treeDataVtx1->GetLeaf("n_1ry_trk");
    TLeaf *PN = treeDataVtx1->GetLeaf("n_1ry_parent_dmin_cut");
    TLeaf *w = treeDataVtx1->GetLeaf("flagw");

    int mlt = mult->GetValue();

    if(PN->GetValue() == 1 && w->GetValue() == 1)
    {
      for (int j = 0; j < mlt; j++)
      {
        treeDataTrk1->GetEntry(Data1TrkIndex);

        TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
        TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
        TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
        TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");

        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();
        double T2 = sqrt(TX*TX+TY*TY)*1000;

        pseuRap->Fill(-log(tan(TX/2)));
        //Mult2->Fill(-log(tan(TY/2)));

        Data1TrkIndex++;
      }
    }
  }
  */

  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
      treeDataTrk1->GetEntry(i);

      TLeaf *PN = treeDataTrk1->GetLeaf("n_1ry_parent_dmin_cut");
      TLeaf *w = treeDataTrk1->GetLeaf("flagw");
      TLeaf *vID = treeDataTrk1->GetLeaf("vID");

      int vtxIndex = vID->GetValue();

      if(w->GetValue() == 1)
      {
        TLeaf *slpTX = treeDataTrk1->GetLeaf("tx");
        TLeaf *slpTY = treeDataTrk1->GetLeaf("ty");
        TLeaf *beamTX = treeDataTrk1->GetLeaf("txpeak");
        TLeaf *beamTY = treeDataTrk1->GetLeaf("typeak");

        double TX = slpTX->GetValue() - beamTX->GetValue();
        double TY = slpTY->GetValue() - beamTY->GetValue();

        double angleX = acos(TX);
        double angleY = acos(TY);
        
        double T2 = sqrt(TX*TX+TY*TY);
        double angle2 = sqrt(angleX*angleX+angleY*angleY);

        TLeaf *mlt = treeDataVtx1->GetLeaf("n_1ry_trk");
        TLeaf *iType = treeDataVtx1->GetLeaf("intType");

        treeDataVtx1->GetEntry(vtxIndex);

        if (iType->GetValue() >= 1)
        {
          pseuRap->Fill(-log(tan(angle2/2)));
        }
      }
  }

  //float scale = pseuRap->Integral()/40;
  //pseuRap->Scale(1/scale);

  pseuRap->Draw("E");
  CanvasModifier(pseuRap);
  pseuRap->SetXTitle("Pseudo-rapidity (#eta)");
  Canvas->Print( outName, "pdf");
  
  //Mult2->Draw("HIST");
  //Canvas->Print( outNameEnd, "pdf");
  
}

void CanvasModifier(TH1F *hist)
{
    Canvas->Update();
    TPaveStats *ps = (TPaveStats*)Canvas->GetPrimitive("stats");
    ps->SetName("mystats");
    TList *listOfLines = ps->GetListOfLines();
    TText *tconst = ps->GetLineWith("Entries");
    listOfLines->Remove(tconst);
    hist->SetStats(0);
    Canvas->Modified();
}