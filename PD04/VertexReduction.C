#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

bool TrackReduction = true;

// Track Tree Variables
Int_t           trk_area1;
Int_t           trk_area2;
Float_t         trk_txpeak;
Float_t         trk_typeak;
Int_t           trk_i;
Float_t         trk_vx;
Float_t         trk_vy;
Float_t         trk_vz;
Int_t           trk_n_1ry_pl;
Int_t           trk_flagw;
Int_t           trk_n_1ry_trk;
Int_t           trk_n_1ry_parent_cut0;
Int_t           trk_n_1ry_parent_dmin_cut;
Int_t           trk_n_1ry_parent_dmin_cut_dt_cut;
Float_t         trk_dt;
Float_t         trk_dz;
Int_t           trk_id;
Int_t           trk_plt_of_1seg;
Int_t           trk_seg_id_of_1seg;
Int_t           trk_vID;
Float_t         trk_seg_x;
Float_t         trk_seg_y;
Float_t         trk_tx;
Float_t         trk_ty;
Int_t           trk_nseg;
Float_t         trk_ip_to_1ry_using_1stseg;
Float_t         trk_ip_to_1ry_using_2ndseg;
Float_t         trk_ph_mean;
Float_t         trk_dtrms1_trk;
Int_t           trk_sub_vol;

/*
// Parent Tree Variables
Int_t           par_area1;
Int_t           par_area2;
Float_t         par_txpeak;
Float_t         par_typeak;
Int_t           par_i;
Float_t         par_vx;
Float_t         par_vy;
Float_t         par_vz;
Int_t           par_n_1ry_pl;
Int_t           par_flagw;
Int_t           par_n_1ry_trk;
Int_t           par_n_1ry_parent_cut0;
Int_t           par_n_1ry_parent_dmin_cut;
Int_t           par_n_1ry_parent_dmin_cut_dt_cut;
Float_t         par_dt;
Float_t         par_dz;
Int_t           par_id;
Int_t           par_plt_of_1seg;
Int_t           par_seg_id_of_1seg;
Int_t           par_vID;
Float_t         par_seg_x;
Float_t         par_seg_y;
Float_t         par_tx;
Float_t         par_ty;
Int_t           par_nseg;
Float_t         par_ip_to_1ry_using_1stseg;
Float_t         par_ip_to_1ry_using_2ndseg;
Float_t         par_ph_mean;
Float_t         par_dtrms1_trk;
Int_t           par_sub_vol;
*/

// Vertex Tree Variables
Int_t           vtx_area1;
Int_t           vtx_area2;
Float_t         vtx_txpeak;
Float_t         vtx_typeak;
Int_t           vtx_i;
Float_t         vtx_vx;
Float_t         vtx_vy;
Float_t         vtx_vz;
Int_t           vtx_n_1ry_pl;
Int_t           vtx_flagw;
Int_t           vtx_n_1ry_trk;
Int_t           vtx_n_1ry_parent_cut0;
Int_t           vtx_n_1ry_parent_dmin_cut;
Int_t           vtx_n_1ry_parent_dmin_cut_dt_cut;
Float_t         vtx_dt;
Float_t         vtx_dz;
Int_t           vtx_trk_id;
Int_t           vtx_plt_of_1seg;
Int_t           vtx_seg_id_of_1seg;
Int_t           vtx_vID;
Float_t         vtx_seg_x;
Float_t         vtx_seg_y;
Float_t         vtx_tx;
Float_t         vtx_ty;
Int_t           vtx_nseg;
Float_t         vtx_ip_to_1ry_using_1stseg;
Float_t         vtx_ip_to_1ry_using_2ndseg;
Float_t         vtx_ph_mean;
Float_t         vtx_dtrms1_trk;
Int_t           vtx_sub_vol;

// Parent Tree Variables
Int_t           par_area1;
Int_t           par_area2;
Float_t         par_txpeak;
Float_t         par_typeak;
Int_t           par_i;
Float_t         par_vx;
Float_t         par_vy;
Float_t         par_vz;
Float_t         par_dz;
Int_t           par_id;
Int_t           par_plt_of_1seg;
Int_t           par_seg_id_of_1seg;
Float_t         par_tx05pos;
Float_t         par_ty05pos;
Int_t           par_nseg;
Int_t           par_n_1ry_trk;
Float_t         par_ip_pos05; 
Float_t         par_ip_pos04;
Int_t           par_ntrk_small;
Float_t         par_dt;
Float_t         par_dt_pos;
Int_t           par_pl_up1ry_plmin;
Int_t           par_pl_up1ry_plmax;
Int_t           par_pl_dwn1ry_plmin;
Int_t           par_pl_dwn1ry_plmax;
Int_t           par_sub_vol;
Int_t           par_vID;

TLeaf *Vtx_area1;
TLeaf *Vtx_area2;
TLeaf *Vtx_txPeak;
TLeaf *Vtx_tyPeak;
TLeaf *Vtx_I;
TLeaf *Vtx_VX;
TLeaf *Vtx_VY;
TLeaf *Vtx_VZ;
TLeaf *Vtx_Plt;
TLeaf *Vtx_w;
TLeaf *Vtx_ID;
TLeaf *Vtx_Mlt;
TLeaf *Vtx_cut0;
TLeaf *Vtx_dminCut;
TLeaf *Vtx_dminDtCut;
TLeaf *Vtx_dt;

TLeaf *Trk_area1;
TLeaf *Trk_area2;
TLeaf *Trk_txPeak;
TLeaf *Trk_tyPeak;
TLeaf *Trk_I;
TLeaf *Trk_VX;
TLeaf *Trk_VY;
TLeaf *Trk_VZ;
TLeaf *Trk_w;
TLeaf *Trk_Mlt;
TLeaf *Trk_cut0;
TLeaf *Trk_dminCut;
TLeaf *Trk_dz;
TLeaf *Trk_ID;
TLeaf *Trk_plt1Seg;
TLeaf *Trk_sID;
TLeaf *Trk_segX;
TLeaf *Trk_segY;
TLeaf *Trk_TX;
TLeaf *Trk_TY;
TLeaf *Trk_nSeg;
TLeaf *Trk_vID;
TLeaf *Trk_IPSeg1;
TLeaf *Trk_IPSeg2;
TLeaf *Trk_PHMean;
TLeaf *Trk_dtrms1;

/*
TLeaf *Par_area1;
TLeaf *Par_area2;
TLeaf *Par_txPeak;
TLeaf *Par_tyPeak;
TLeaf *Par_I;
TLeaf *Par_VX;
TLeaf *Par_VY;
TLeaf *Par_VZ;
TLeaf *Par_w;
TLeaf *Par_Mlt;
TLeaf *Par_cut0;
TLeaf *Par_dminCut;
TLeaf *Par_dz;
TLeaf *Par_ID;
TLeaf *Par_plt1Seg;
TLeaf *Par_sID;
TLeaf *Par_segX;
TLeaf *Par_segY;
TLeaf *Par_TX;
TLeaf *Par_TY;
TLeaf *Par_nSeg;
TLeaf *Par_vID;
TLeaf *Par_IPSeg1;
TLeaf *Par_IPSeg2;
TLeaf *Par_PHMean;
TLeaf *Par_dtrms1;
*/

TLeaf *Par_area1;
TLeaf *Par_area2;
TLeaf *Par_txPeak;
TLeaf *Par_tyPeak;
TLeaf *Par_I;
TLeaf *Par_VX;
TLeaf *Par_VY;
TLeaf *Par_VZ;
TLeaf *Par_dz;
TLeaf *Par_ID;
TLeaf *Par_plt1Seg;
TLeaf *Par_segIdSeg1;
TLeaf *Par_tx05pos;
TLeaf *Par_ty05pos;
TLeaf *Par_Mlt;
TLeaf *Par_nSeg;
TLeaf *Par_ipPos05;
TLeaf *Par_ipPos04;
TLeaf *Par_ntrkSmall;
TLeaf *Par_dt;
TLeaf *Par_dt_pos;
TLeaf *Par_pl_up1ry_plmin;
TLeaf *Par_pl_up1ry_plmax;
TLeaf *Par_pl_dwn1ry_plmin;
TLeaf *Par_pl_dwn1ry_plmax;
TLeaf *Par_vID;

TFile *hfile;
TTree *vtx;
TTree *trk;
TTree *par;
//TTree *parCand;

void VtxCopy();
void TrkCopy();
void ParCopy();
//void ParCCopy();

vector<string> inFiles = {"p006.root", "p016.root", "p026.root", "p036.root", "p046.root", "p056.root", "p066.root", "p076.root", "p086.root"};

void VertexReduction()
{
  hfile = TFile::Open("Out.root","RECREATE");
  vtx = new TTree("VTX","VTXinfo");
  trk = new TTree("TRK","TRKinfo");
  par = new TTree("PAR","ParentInfo");
  //parCand = new TTree("PARCand","ParentCandidateInfo");

  vtx->Branch("area1",&vtx_area1,"area1/I");
  vtx->Branch("area2",&vtx_area2,"area2/I");
  vtx->Branch("txpeak",&vtx_txpeak,"txpeak/F");
  vtx->Branch("typeak",&vtx_typeak,"typeak/F");
  vtx->Branch("i",&vtx_i,"i/I");
  vtx->Branch("vx",&vtx_vx,"vx/F");
  vtx->Branch("vy",&vtx_vy,"vy/F");
  vtx->Branch("vz",&vtx_vz,"vz/F");
  vtx->Branch("n_1ry_pl",&vtx_n_1ry_pl,"n_1ry_pl/I");
  vtx->Branch("flagw",&vtx_flagw,"flagw/I");
  vtx->Branch("vID",&vtx_vID,"vID/I");
  vtx->Branch("n_1ry_trk",&vtx_n_1ry_trk,"n_1ry_trk/I");
  vtx->Branch("n_1ry_parent_cut0",&vtx_n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
  vtx->Branch("n_1ry_parent_dmin_cut",&vtx_n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");
  vtx->Branch("n_1ry_parent_dmin_cut_dt_cut",&vtx_n_1ry_parent_dmin_cut_dt_cut,"n_1ry_parent_dmin_cut_dt_cut/I");
  vtx->Branch("dt",&vtx_dt,"dt/F");
  vtx->Branch("sub_vol",&vtx_sub_vol,"sub_vol/I");

  trk->Branch("area1",&trk_area1,"area1/I");
  trk->Branch("area2",&trk_area2,"area2/I");
  trk->Branch("txpeak",&trk_txpeak,"txpeak/F");
  trk->Branch("typeak",&trk_typeak,"typeak/F");
  trk->Branch("i",&trk_i,"i/I");
  trk->Branch("vx",&trk_vx,"vx/F");
  trk->Branch("vy",&trk_vy,"vy/F");
  trk->Branch("vz",&trk_vz,"vz/F");
  trk->Branch("flagw",&trk_flagw,"flagw/I");
  trk->Branch("n_1ry_trk",&trk_n_1ry_trk,"n_1ry_trk/I");
  trk->Branch("n_1ry_parent_cut0",&trk_n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
  trk->Branch("n_1ry_parent_dmin_cut",&trk_n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");
  trk->Branch("dz",&trk_dz,"dz/F");
  trk->Branch("trk_id",&trk_id,"trk_id/I");
  trk->Branch("plt_of_1seg",&trk_plt_of_1seg,"plt_of_1seg/I");
  trk->Branch("seg_id_of_1seg",&trk_seg_id_of_1seg,"seg_id_of_1seg/I");
  trk->Branch("seg_x",&trk_seg_x,"seg_x/F");
  trk->Branch("seg_y",&trk_seg_y,"seg_y/F");
  trk->Branch("tx",&trk_tx,"tx/F");
  trk->Branch("ty",&trk_ty,"ty/F");
  trk->Branch("nseg",&trk_nseg,"nseg/I");
  trk->Branch("vID",&trk_vID,"vID/I");
  trk->Branch("ip_to_1ry_using_1stseg",&trk_ip_to_1ry_using_1stseg,"ip_to_1ry_using_1stseg/F");
  trk->Branch("ip_to_1ry_using_2ndseg",&trk_ip_to_1ry_using_2ndseg,"ip_to_1ry_using_2ndseg/F");
  trk->Branch("ph_mean",&trk_ph_mean,"ph_mean/F");
  trk->Branch("dtrms1_trk",&trk_dtrms1_trk,"dtrms1_trk/F");
  trk->Branch("sub_vol",&trk_sub_vol,"sub_vol/I");

  /*
  par->Branch("area1",&par_area1,"area1/I");
  par->Branch("area2",&par_area2,"area2/I");
  par->Branch("txpeak",&par_txpeak,"txpeak/F");
  par->Branch("typeak",&par_typeak,"typeak/F");
  par->Branch("i",&par_i,"i/I");
  par->Branch("vx",&par_vx,"vx/F");
  par->Branch("vy",&par_vy,"vy/F");
  par->Branch("vz",&par_vz,"vz/F");
  par->Branch("flagw",&par_flagw,"flagw/I");
  par->Branch("n_1ry_trk",&par_n_1ry_trk,"n_1ry_trk/I");
  par->Branch("n_1ry_parent_cut0",&par_n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
  par->Branch("n_1ry_parent_dmin_cut",&par_n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");
  par->Branch("dz",&par_dz,"dz/F");
  par->Branch("par_id",&par_id,"par_id/I");
  par->Branch("plt_of_1seg",&par_plt_of_1seg,"plt_of_1seg/I");
  par->Branch("seg_id_of_1seg",&par_seg_id_of_1seg,"seg_id_of_1seg/I");
  par->Branch("seg_x",&par_seg_x,"seg_x/F");
  par->Branch("seg_y",&par_seg_y,"seg_y/F");
  par->Branch("tx",&par_tx,"tx/F");
  par->Branch("ty",&par_ty,"ty/F");
  par->Branch("nseg",&par_nseg,"nseg/I");
  par->Branch("vID",&par_vID,"vID/I");
  par->Branch("ip_to_1ry_using_1stseg",&par_ip_to_1ry_using_1stseg,"ip_to_1ry_using_1stseg/F");
  par->Branch("ip_to_1ry_using_2ndseg",&par_ip_to_1ry_using_2ndseg,"ip_to_1ry_using_2ndseg/F");
  par->Branch("ph_mean",&par_ph_mean,"ph_mean/F");
  par->Branch("dtrms1_trk",&par_dtrms1_trk,"dtrms1_trk/F");
  par->Branch("sub_vol",&par_sub_vol,"sub_vol/I");
  */

  par->Branch("area1",&par_area1,"area1/I");
  par->Branch("area2",&par_area2,"area2/I");
  par->Branch("txpeak",&par_txpeak,"txpeak/F");
  par->Branch("typeak",&par_typeak,"typeak/F");
  par->Branch("i",&par_i,"i/I");
  par->Branch("vx",&par_vx,"vx/F");
  par->Branch("vy",&par_vy,"vy/F");
  par->Branch("vz",&par_vz,"vz/F");
  par->Branch("dz",&par_dz,"dz/F");
  par->Branch("trk_id",&par_id,"trk_id/I");
  par->Branch("plt_of_1seg",&par_plt_of_1seg,"plt_of_1seg/I");
  par->Branch("seg_id_of_1seg",&par_seg_id_of_1seg,"seg_id_of_1seg/I");
  par->Branch("tx05pos",&par_tx05pos,"tx05pos/F");
  par->Branch("ty05pos",&par_ty05pos,"ty05pos/F");
  par->Branch("nseg",&par_nseg,"nseg/I");
  par->Branch("n_1ry_trk",&par_n_1ry_trk,"n_1ry_trk/I");
  par->Branch("ip_pos05",&par_ip_pos05,"ip_pos05/F");
  par->Branch("ip_pos04",&par_ip_pos04,"ip_pos04/F");
  par->Branch("ntrk_small",&par_ntrk_small,"ntrk_small/I");
  par->Branch("dt",&par_dt,"dt/F");
  par->Branch("dt_pos",&par_dt_pos,"dt_pos/F");
  par->Branch("pl_up1ry_plmin",&par_pl_up1ry_plmin,"pl_up1ry_plmin/I");
  par->Branch("pl_up1ry_plmax",&par_pl_up1ry_plmax,"pl_up1ry_plmax/I");
  par->Branch("pl_dwn1ry_plmin",&par_pl_dwn1ry_plmin,"pl_dwn1ry_plmin/I");
  par->Branch("pl_dwn1ry_plmax",&par_pl_dwn1ry_plmax,"pl_dwn1ry_plmax/I");
  par->Branch("vID",&par_vID,"vID/I");

  for (int subV = 0; subV < inFiles.size(); subV++)
  {
    cout << "Sub Volume: " << subV << endl;

    vector<int> eIDList; vector<int> eIDListFull;
    vector<int> tVIDList;

    int eSize = 0, ovSize = 0;

    string inFile = "RootOut/" + inFiles[subV];
    char inFileArr[inFile.length() + 1]; 

    strcpy(inFileArr, inFile.c_str()); 
    
    TFile *Data = TFile::Open(inFileArr);
    TTree *TrkTree = (TTree*)Data->Get("TRK");
    TTree *VtxTree = (TTree*)Data->Get("VTX");
    TTree *ParTree = (TTree*)Data->Get("PAR");
    //TTree *ParCandTree = (TTree*)Data->Get("PARCand");
    Data->cd();

    Vtx_area1 = VtxTree->GetLeaf("area1");
    Vtx_area2 = VtxTree->GetLeaf("area2");
    Vtx_txPeak = VtxTree->GetLeaf("txpeak");
    Vtx_tyPeak = VtxTree->GetLeaf("typeak");
    Vtx_I = VtxTree->GetLeaf("i");
    Vtx_VX = VtxTree->GetLeaf("vx");
    Vtx_VY = VtxTree->GetLeaf("vy");
    Vtx_VZ = VtxTree->GetLeaf("vz");
    Vtx_Plt = VtxTree->GetLeaf("n_1ry_pl");
    Vtx_w = VtxTree->GetLeaf("flagw");
    Vtx_ID = VtxTree->GetLeaf("vID");
    Vtx_Mlt = VtxTree->GetLeaf("n_1ry_trk");
    Vtx_cut0 = VtxTree->GetLeaf("n_1ry_parent_cut0");
    Vtx_dminCut = VtxTree->GetLeaf("n_1ry_parent_dmin_cut");
    Vtx_dminDtCut = VtxTree->GetLeaf("n_1ry_parent_dmin_cut_dt_cut");
    Vtx_dt = VtxTree->GetLeaf("dt");

    Trk_area1 = TrkTree->GetLeaf("area1");
    Trk_area2 = TrkTree->GetLeaf("area2");
    Trk_txPeak = TrkTree->GetLeaf("txpeak");
    Trk_tyPeak = TrkTree->GetLeaf("typeak");
    Trk_I = TrkTree->GetLeaf("i");
    Trk_VX = TrkTree->GetLeaf("vx");
    Trk_VY = TrkTree->GetLeaf("vy");
    Trk_VZ = TrkTree->GetLeaf("vz");
    Trk_w = TrkTree->GetLeaf("flagw");
    Trk_Mlt = TrkTree->GetLeaf("n_1ry_trk");
    Trk_cut0 = TrkTree->GetLeaf("n_1ry_parent_cut0");
    Trk_dminCut = TrkTree->GetLeaf("n_1ry_parent_dmin_cut");
    Trk_dz = TrkTree->GetLeaf("dz");
    Trk_ID = TrkTree->GetLeaf("trk_id");
    Trk_plt1Seg = TrkTree->GetLeaf("plt_of_1seg");
    Trk_sID = TrkTree->GetLeaf("seg_id_of_1seg");
    Trk_segX = TrkTree->GetLeaf("seg_x");
    Trk_segY = TrkTree->GetLeaf("seg_y");
    Trk_TX = TrkTree->GetLeaf("tx");
    Trk_TY = TrkTree->GetLeaf("ty");
    Trk_nSeg = TrkTree->GetLeaf("nseg");
    Trk_vID = TrkTree->GetLeaf("vID");
    Trk_IPSeg1 = TrkTree->GetLeaf("ip_to_1ry_using_1stseg");
    Trk_IPSeg2 = TrkTree->GetLeaf("ip_to_1ry_using_2ndseg");
    Trk_PHMean = TrkTree->GetLeaf("ph_mean");
    Trk_dtrms1 = TrkTree->GetLeaf("dtrms1_trk");
    /*
    Par_area1 = ParTree->GetLeaf("area1");
    Par_area2 = ParTree->GetLeaf("area2");
    Par_txPeak = ParTree->GetLeaf("txpeak");
    Par_tyPeak = ParTree->GetLeaf("typeak");
    Par_I = ParTree->GetLeaf("i");
    Par_VX = ParTree->GetLeaf("vx");
    Par_VY = ParTree->GetLeaf("vy");
    Par_VZ = ParTree->GetLeaf("vz");
    Par_w = ParTree->GetLeaf("flagw");
    Par_Mlt = ParTree->GetLeaf("n_1ry_trk");
    Par_cut0 = ParTree->GetLeaf("n_1ry_parent_cut0");
    Par_dminCut = ParTree->GetLeaf("n_1ry_parent_dmin_cut");
    Par_dz = ParTree->GetLeaf("dz");
    Par_ID = ParTree->GetLeaf("trk_id");
    Par_plt1Seg = ParTree->GetLeaf("plt_of_1seg");
    Par_sID = ParTree->GetLeaf("seg_id_of_1seg");
    Par_segX = ParTree->GetLeaf("seg_x");
    Par_segY = ParTree->GetLeaf("seg_y");
    Par_TX = ParTree->GetLeaf("tx");
    Par_TY = ParTree->GetLeaf("ty");
    Par_nSeg = ParTree->GetLeaf("nseg");
    Par_vID = ParTree->GetLeaf("vID");
    Par_IPSeg1 = ParTree->GetLeaf("ip_to_1ry_using_1stseg");
    Par_IPSeg2 = ParTree->GetLeaf("ip_to_1ry_using_2ndseg");
    Par_PHMean = ParTree->GetLeaf("ph_mean");
    Par_dtrms1 = ParTree->GetLeaf("dtrms1_trk");
    */
    Par_area1 = ParTree->GetLeaf("area1");
    Par_area2 = ParTree->GetLeaf("area2");
    Par_txPeak = ParTree->GetLeaf("txpeak");
    Par_tyPeak = ParTree->GetLeaf("typeak");
    Par_I = ParTree->GetLeaf("i");
    Par_VX = ParTree->GetLeaf("vx");
    Par_VY = ParTree->GetLeaf("vy");
    Par_VZ = ParTree->GetLeaf("vz");
    Par_dz = ParTree->GetLeaf("dz");
    Par_ID = ParTree->GetLeaf("trk_id");
    Par_plt1Seg = ParTree->GetLeaf("plt_of_1seg");
    Par_segIdSeg1 = ParTree->GetLeaf("seg_id_of_1seg");
    Par_tx05pos = ParTree->GetLeaf("tx05pos");
    Par_ty05pos = ParTree->GetLeaf("ty05pos");
    Par_nSeg = ParTree->GetLeaf("nseg");
    Par_Mlt = ParTree->GetLeaf("n_1ry_trk");
    Par_ipPos05 = ParTree->GetLeaf("ip_pos05");
    Par_ipPos04 = ParTree->GetLeaf("ip_pos04");
    Par_ntrkSmall = ParTree->GetLeaf("ntrk_small");
    Par_dt = ParTree->GetLeaf("dt");
    Par_dt_pos = ParTree->GetLeaf("dt_pos");
    Par_pl_up1ry_plmin = ParTree->GetLeaf("pl_up1ry_plmin");
    Par_pl_up1ry_plmax = ParTree->GetLeaf("pl_up1ry_plmax");
    Par_pl_dwn1ry_plmin = ParTree->GetLeaf("pl_dwn1ry_plmin");
    Par_pl_dwn1ry_plmax = ParTree->GetLeaf("pl_dwn1ry_plmax");
    Par_vID = ParTree->GetLeaf("vID");

    int refIDEvent = 0, currentEID = 0;

    eSize = ParTree->GetEntries();
    for (int i = 0; i < eSize; i++)
    {
      //if (i%1000 == 0) cout << i << "/" << eSize << endl;

      ParTree->GetEntry(i);
      currentEID = Par_ID->GetValue();
      eIDListFull.push_back(currentEID);

      if (find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
      {
        eIDList.push_back(currentEID);
      }
    }

    for (int i = 0; i < TrkTree->GetEntries(); i++)
    {
      TrkTree->GetEntry(i);
      tVIDList.push_back(Trk_vID->GetValue());
    }

    ovSize = eIDList.size();
    //int trkIndex = 0;

    for (int i = 0; i < ovSize; i++)
    {
      if (i%1000 == 0) cout << "Vertex: " << i << "/" << ovSize << endl;
      
      int cnt = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);
      
      ParTree->GetEntry(i);
      //ParCandTree->GetEntry(i);
      VtxTree->GetEntry(i);

      int index = 0;
      vector <int> TrkList;

      if (cnt > 1)
      {
        float initVtxX = 0;
        float initVtxY = 0;
        float initVtxZ = 0;
        float initMult = 0;
        int initVID = 0;
        int initIndex = 0;

        for (int j = 0; j < cnt; j++)
        {

          auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eIDList[i]);
          if (it != eIDListFull.end())
          {
            index = it - eIDListFull.begin();
            ParTree->GetEntry(index);
            //ParCandTree->GetEntry(index);

            int VtxX = Par_VX->GetValue();
            int VtxY = Par_VY->GetValue();
            int VtxZ = Par_VZ->GetValue();
            int Mult = Par_Mlt->GetValue();
            int vID = Par_vID->GetValue();

            if (j == 0)
            {
              initVtxX = VtxX;
              initVtxY = VtxY;
              initVtxZ = VtxZ;
              initMult = Mult;
              initVID = vID;
              initIndex = index;
            }
            else if (abs(initVtxX-VtxX) <= 100 && abs(initVtxY-VtxY) <= 100 && abs(initVtxZ-VtxZ) <= 100)
            {
              int indexSec = 0, newMult = 0;

              if (initMult < Mult)
              {
                ParTree->GetEntry(index);
                //ParCandTree->GetEntry(index);
                VtxTree->GetEntry(index);

                TrkList.clear();
                for (int mlt = 0; mlt < Mult; mlt++)
                {
                  auto iter = find(tVIDList.begin() + indexSec + 1, tVIDList.end(), vID);
                  if (iter != tVIDList.end())
                  {
                    indexSec = iter - tVIDList.begin();
                    TrkTree->GetEntry(indexSec);

                    if (TrackReduction == true)
                    {
                      int currentTrID = Trk_ID->GetValue();

                      //cout << fixed << "Normal: " << Trk_ID->GetValue() << endl;

                      if (find(TrkList.begin(), TrkList.end(), currentTrID) == TrkList.end())
                      {
                        TrkList.push_back(currentTrID);

                        trk_sub_vol = subV;
                        TrkCopy();

                        //cout << fixed << "Reduced: " << Trk_ID->GetValue() << endl;
                        newMult++;
                      }
                    }
                    else
                    {
                      trk_sub_vol = subV;
                      TrkCopy();
                    }
                  }
                }
                par_sub_vol = subV;
                vtx_sub_vol = subV;

                par_n_1ry_trk = newMult;
                vtx_n_1ry_trk = newMult;

                ParCopy();
                //ParCCopy();
                VtxCopy();

              }
              if (initMult >= Mult)
              {
                ParTree->GetEntry(initIndex);
                //ParCandTree->GetEntry(initIndex);
                VtxTree->GetEntry(initIndex);
                
                TrkList.clear();
                for (int mlt = 0; mlt < initMult; mlt++)
                {
                  auto iter = find(tVIDList.begin() + indexSec + 1, tVIDList.end(), initVID);
                  if (iter != tVIDList.end())
                  {
                    indexSec = iter - tVIDList.begin();
                    TrkTree->GetEntry(indexSec);
                    
                    if (TrackReduction == true)
                    {
                      int currentTrID = Trk_ID->GetValue();

                      //cout << fixed << "Normal: " << Trk_ID->GetValue() << endl;

                      if (find(TrkList.begin(), TrkList.end(), currentTrID) == TrkList.end())
                      {
                        TrkList.push_back(currentTrID);

                        trk_sub_vol = subV;
                        TrkCopy();

                        //cout << fixed << "Reduced: " << Trk_ID->GetValue() << endl;
                        newMult++;
                      }
                    }
                    else
                    {
                      trk_sub_vol = subV;
                      TrkCopy();
                    }
                  }
                }
                par_sub_vol = subV;
                vtx_sub_vol = subV;

                par_n_1ry_trk = newMult;
                vtx_n_1ry_trk = newMult;

                ParCopy();
                //ParCCopy();
                VtxCopy();
              }
            }
          }
        }
      }
      else
      {
        int indexSec = 0, newMult = 0;
        
        TrkList.clear();
        for (int mlt = 0; mlt < Par_Mlt->GetValue(); mlt++)
        {
          auto iter = find(tVIDList.begin() + indexSec + 1, tVIDList.end(), Par_vID->GetValue());
          if (iter != tVIDList.end())
          {
            indexSec = iter - tVIDList.begin();
            TrkTree->GetEntry(indexSec);
            
            if (TrackReduction == true)
            {
              int currentTrID = Trk_ID->GetValue();

              //cout << fixed << "Normal: " << Trk_ID->GetValue() << endl;

              if (find(TrkList.begin(), TrkList.end(), currentTrID) == TrkList.end())
              {
                TrkList.push_back(currentTrID);

                trk_sub_vol = subV;
                TrkCopy();

                //cout << fixed << "Reduced: " << Trk_ID->GetValue() << endl;
                newMult++;
              }
            }
            else
            {
              trk_sub_vol = subV;
              TrkCopy();
            }
          }
        }
        par_sub_vol = subV;
        vtx_sub_vol = subV;

        par_n_1ry_trk = newMult;
        vtx_n_1ry_trk = newMult;

        ParCopy();
        //ParCCopy();
        VtxCopy();
      }
    }

    Data->Close();
    delete Data;
  }
  
  hfile->cd();
  vtx->Write();
  trk->Write();
  par->Write();
  //parCand->Write();

  hfile->Close();
  delete hfile;
}

void VtxCopy()
{
  vtx_area1 = Vtx_area1->GetValue();
  vtx_area2 = Vtx_area2->GetValue();
  vtx_txpeak = Vtx_txPeak->GetValue();
  vtx_typeak = Vtx_tyPeak->GetValue();
  vtx_i = Vtx_I->GetValue();
  vtx_vx = Vtx_VX->GetValue();
  vtx_vy = Vtx_VY->GetValue();
  vtx_vz = Vtx_VZ->GetValue();
  vtx_n_1ry_pl = Vtx_Plt->GetValue();
  vtx_flagw = Vtx_w->GetValue();
  vtx_vID = Vtx_ID->GetValue();
  if (TrackReduction == false) { vtx_n_1ry_trk = Vtx_Mlt->GetValue(); }
  vtx_n_1ry_parent_cut0 = Vtx_cut0->GetValue();
  vtx_n_1ry_parent_dmin_cut = Vtx_dminCut->GetValue();
  vtx_n_1ry_parent_dmin_cut_dt_cut = Vtx_dminDtCut->GetValue();
  vtx_dt = Vtx_dt->GetValue();

  vtx->Fill();
}

void TrkCopy()
{
  trk_area1 = Trk_area1->GetValue();
  trk_area2 = Trk_area2->GetValue();
  trk_txpeak = Trk_txPeak->GetValue();
  trk_typeak = Trk_tyPeak->GetValue();
  trk_i = Trk_I->GetValue();
  trk_vx = Trk_VX->GetValue();
  trk_vy = Trk_VY->GetValue();
  trk_vz = Trk_VZ->GetValue();
  trk_flagw = Trk_w->GetValue();
  trk_n_1ry_trk = Trk_Mlt->GetValue();
  trk_n_1ry_parent_cut0 = Trk_cut0->GetValue();
  trk_n_1ry_parent_dmin_cut = Trk_dminCut->GetValue();
  trk_dz = Trk_dz->GetValue();
  trk_id = Trk_ID->GetValue();
  trk_plt_of_1seg = Trk_plt1Seg->GetValue();
  trk_seg_id_of_1seg = Trk_sID->GetValue();
  trk_seg_x = Trk_segX->GetValue();
  trk_seg_y = Trk_segY->GetValue();
  trk_tx = Trk_TX->GetValue();
  trk_ty = Trk_TY->GetValue();
  trk_nseg = Trk_nSeg->GetValue();
  trk_vID = Trk_vID->GetValue();
  trk_ip_to_1ry_using_1stseg = Trk_IPSeg1->GetValue();
  trk_ip_to_1ry_using_2ndseg = Trk_IPSeg2->GetValue();
  trk_ph_mean = Trk_PHMean->GetValue();
  trk_dtrms1_trk = Trk_dtrms1->GetValue();

  trk->Fill();
}
/*
void ParCopy()
{
  par_area1 = Par_area1->GetValue();
  par_area2 = Par_area2->GetValue();
  par_txpeak = Par_txPeak->GetValue();
  par_typeak = Par_tyPeak->GetValue();
  par_i = Par_I->GetValue();
  par_vx = Par_VX->GetValue();
  par_vy = Par_VY->GetValue();
  par_vz = Par_VZ->GetValue();
  par_flagw = Par_w->GetValue();
  if (TrackReduction == false) { par_n_1ry_trk = Par_Mlt->GetValue(); }
  par_n_1ry_parent_cut0 = Par_cut0->GetValue();
  par_n_1ry_parent_dmin_cut = Par_dminCut->GetValue();
  par_dz = Par_dz->GetValue();
  par_id = Par_ID->GetValue();
  par_plt_of_1seg = Par_plt1Seg->GetValue();
  par_seg_id_of_1seg = Par_sID->GetValue();
  par_seg_x = Par_segX->GetValue();
  par_seg_y = Par_segY->GetValue();
  par_tx = Par_TX->GetValue();
  par_ty = Par_TY->GetValue();
  par_nseg = Par_nSeg->GetValue();
  par_vID = Par_vID->GetValue();
  par_ip_to_1ry_using_1stseg = Par_IPSeg1->GetValue();
  par_ip_to_1ry_using_2ndseg = Par_IPSeg2->GetValue();
  par_ph_mean = Par_PHMean->GetValue();
  par_dtrms1_trk = Par_dtrms1->GetValue();

  par->Fill();
}
*/
void ParCopy()
{
  par_area1 = Par_area1->GetValue();
  par_area2 = Par_area2->GetValue();
  par_txpeak = Par_txPeak->GetValue();
  par_typeak = Par_tyPeak->GetValue();
  par_i = Par_I->GetValue();
  par_vx = Par_VX->GetValue();
  par_vy = Par_VY->GetValue();
  par_vz = Par_VZ->GetValue();
  par_dz = Par_dz->GetValue();
  par_id = Par_ID->GetValue();
  par_plt_of_1seg = Par_plt1Seg->GetValue();
  par_seg_id_of_1seg = Par_segIdSeg1->GetValue();
  par_tx05pos = Par_tx05pos->GetValue();
  par_ty05pos = Par_ty05pos->GetValue();
  par_nseg = Par_nSeg->GetValue();
  if (TrackReduction == false) { par_n_1ry_trk = Par_Mlt->GetValue(); }
  par_ip_pos05 = Par_ipPos05->GetValue(); 
  par_ip_pos04 = Par_ipPos04->GetValue();
  par_ntrk_small = Par_ntrkSmall->GetValue();
  par_dt = Par_dt->GetValue();
  par_dt_pos = Par_dt_pos->GetValue();
  par_pl_up1ry_plmin = Par_pl_up1ry_plmin->GetValue();
  par_pl_up1ry_plmax = Par_pl_up1ry_plmax->GetValue();
  par_pl_dwn1ry_plmin = Par_pl_dwn1ry_plmin->GetValue();
  par_pl_dwn1ry_plmax = Par_pl_dwn1ry_plmax->GetValue();
  par_vID = Par_vID->GetValue();

  par->Fill();
}