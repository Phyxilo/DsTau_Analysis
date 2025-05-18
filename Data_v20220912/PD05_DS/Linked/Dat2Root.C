#include <iostream>
#include <vector>
#include <unordered_map>

#include "fineAllign.h"

using namespace std;

vector<tuple<int, int, int, int, int, int, int>> ReadFile(char *inFile, int segNum);

bool firstEqual(const tuple<int, int, int, int, int, int, int>& a, const tuple<int, int, int, int, int, int, int>& b) 
{
   return get<0>(a) == get<0>(b);
}

void All_limits();
void FineAllign();

bool isInAcceptance(int index);
bool isTranslatedOut(int index, int posX, int posY, int posZ, float tX, int tY);
bool isInSubArea(int index, int posX, int posY);

ofstream out("DataAccOut.log", ios::out | ios::app);

TFile *Dat2Root(string inputName, string outputName, string inputDS, string inputUS, int dirIndex)
{
   //---------------------------------- ParFineAllign Start ----------------------------------

   //All_limits();

   h_align = new TH1F("h_all","h_all",2500,0,50000);

   h_align->GetXaxis()->SetTitle("mkm");
   h_align->GetXaxis()->SetTitleSize(0.06);
   h_align->GetXaxis()->SetTitleOffset(0.7);
   h_align->GetXaxis()->SetTickLength(0.009);
   h_align->GetXaxis()->SetLabelSize(0.04);
   h_align->GetYaxis()->SetTickLength(0.009);

   TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
   TCanvas *c3 = new TCanvas("c3","cLng", 1000,400);
   
   gStyle->SetOptTitle(0);
   gStyle->SetOptFit();

   int area=1;
   double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
   int nr=0, ok=0;

   int currentRow=0, currentColumn=0, Xmin=0, Xmax=0, Ymin=0, Ymax=0;
   int TotalColumns = 9;
   int TotalRows = 7;

   int plt=dirIndex*10+1;
   mean_limits(plt);
   limits(1,plt);
   Xmin=-2500;
   Xmax=12500;
   Ymin=-2500;
   Ymax=12500;

   //---------------------------------- ParFineAllign End ----------------------------------

   Char_t          type[16];

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
   Int_t           trk_int_medium;

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
   Int_t           vtx_int_type;
   Int_t           vtx_int_medium;

   // Parent Candidate Tree Variables
   Int_t           parC_area1;
   Int_t           parC_area2;
   Float_t         parC_txpeak;
   Float_t         parC_typeak;
   Int_t           parC_i;
   Float_t         parC_vx;
   Float_t         parC_vy;
   Float_t         parC_vz;
   Float_t         parC_dz;
   Int_t           parC_id;
   Int_t           parC_plt_of_1seg;
   Int_t           parC_seg_id_of_1seg;
   Float_t         parC_tx05pos;
   Float_t         parC_ty05pos;
   Int_t           parC_nseg;
   Int_t           parC_n_1ry_trk;
   Float_t         parC_ip_pos05; 
   Float_t         parC_ip_pos04;
   Int_t           parC_ntrk_small;
   Float_t         parC_dt;
   Float_t         parC_dt_pos;
   Int_t           parC_pl_up1ry_plmin;
   Int_t           parC_pl_up1ry_plmax;
   Int_t           parC_pl_dwn1ry_plmin;
   Int_t           parC_pl_dwn1ry_plmax;
   Int_t           parC_vID;
   Int_t           par_flagp;
   Int_t           glob_parid;

   // Upstream Proton Track Tree Variables
   Int_t           ptrk_US_area1;
   Int_t           ptrk_US_trID;
   Int_t           ptrk_US_gtrID;
   Int_t           ptrk_US_plt_of_1seg;
   Int_t           ptrk_US_PosX_of_1seg;
   Int_t           ptrk_US_PosY_of_1seg;
   Int_t           ptrk_US_PosZ_of_1seg;
   Float_t         ptrk_US_TX;
   Float_t         ptrk_US_TY;

   // Downstream Proton Track Tree Variables
   Int_t           ptrk_DS_area1;
   Int_t           ptrk_DS_trID;
   Int_t           ptrk_DS_gtrID;
   Int_t           ptrk_DS_plt_of_1seg;
   Int_t           ptrk_DS_PosX_of_1seg;
   Int_t           ptrk_DS_PosY_of_1seg;
   Int_t           ptrk_DS_PosZ_of_1seg;
   Float_t         ptrk_DS_TX;
   Float_t         ptrk_DS_TY;

   // DecaySearch_all
   Int_t    ds_all_area1;
   Int_t    ds_all_area2;
   Float_t  ds_all_txpeak;
   Float_t  ds_all_typeak;
   Int_t    ds_all_i; 
   Float_t  ds_all_xc;
   Float_t  ds_all_yc;
   Float_t  ds_all_1ry_vx;
   Float_t  ds_all_1ry_vy;
   Float_t  ds_all_1ry_vz;
   Int_t    ds_all_1ry_plt;
   Int_t    ds_all_flagw;
   Int_t    ds_all_n_1ry_trk;
   Float_t  ds_all_2ry_vx;
   Float_t  ds_all_2ry_vy;
   Float_t  ds_all_2ry_vz;
   Int_t    ds_all_2ry_plt;
   Int_t    ds_all_parent_plt_1st;
   Int_t    ds_all_parent_trkID;
   Int_t    ds_all_parent_MCEvt;
   Int_t    ds_all_parent_pdgID;
   Float_t  ds_all_parent_MCp;
   Int_t    ds_all_nparent_1ry;
   Int_t    ds_all_nparent_1ry_penet;
   Int_t    ds_all_nparent_non1ry;
   Float_t  ds_all_parent_tx;
   Float_t  ds_all_parent_ty;
   Int_t    ds_all_ndau;
   Int_t    ds_all_default1;
   Int_t    ds_all_default2;
   Int_t    ds_all_plt_dau1;
   Int_t    ds_all_segid_dau1;
   Int_t    ds_all_dau1_MCEvt;
   Int_t    ds_all_dau1_pdgID;
   Float_t  ds_all_dau1_MCp;
   Float_t  ds_all_ip_to1ry_dau1;
   Float_t  ds_all_ip_to2ry_dau1;
   Float_t  ds_all_tx_dau1;
   Float_t  ds_all_ty_dau1;
   Float_t  ds_all_dt_dau1;
   Float_t  ds_all_dtrms_dau1;
   Float_t  ds_all_dtrmst_dau1;
   Float_t  ds_all_dt_w_dau1;

   Int_t    ds_all_plt_dau2;
   Int_t    ds_all_segid_dau2;
   Int_t    ds_all_dau2_MCEvt;
   Int_t    ds_all_dau2_pdgID;
   Float_t  ds_all_dau2_MCp;
   Float_t  ds_all_ip_to1ry_dau2;
   Float_t  ds_all_ip_to2ry_dau2;
   Float_t  ds_all_tx_dau2;
   Float_t  ds_all_ty_dau2;
   Float_t  ds_all_dt_dau2;
   Float_t  ds_all_dtrms_dau2;
   Float_t  ds_all_dtrmst_dau2;
   Float_t  ds_all_dt_w_dau2;

   Int_t    ds_all_plt_dau3;
   Int_t    ds_all_segid_dau3;
   Int_t    ds_all_dau3_MCEvt;
   Int_t    ds_all_dau3_pdgID;
   Float_t  ds_all_dau3_MCp;
   Float_t  ds_all_ip_to1ry_dau3;
   Float_t  ds_all_ip_to2ry_dau3;
   Float_t  ds_all_tx_dau3;
   Float_t  ds_all_ty_dau3;
   Float_t  ds_all_dt_dau3;
   Float_t  ds_all_dtrms_dau3;
   Float_t  ds_all_dtrmst_dau3;
   Float_t  ds_all_dt_w_dau3;

   Int_t    ds_all_plt_dau4;
   Int_t    ds_all_segid_dau4;
   Int_t    ds_all_dau4_MCEvt;
   Int_t    ds_all_dau4_pdgID;
   Float_t  ds_all_dau4_MCp;
   Float_t  ds_all_ip_to1ry_dau4;
   Float_t  ds_all_ip_to2ry_dau4;
   Float_t  ds_all_tx_dau4;
   Float_t  ds_all_ty_dau4;
   Float_t  ds_all_dt_dau4;
   Float_t  ds_all_dtrms_dau4;
   Float_t  ds_all_dtrmst_dau4;
   Float_t  ds_all_dt_w_dau4;

   Float_t  ds_all_dmin_org_vee;
   Float_t  ds_all_dmin_fine_vee;
   Float_t  ds_all_topen_vee;
   Float_t  ds_all_dt1dt2_vee;
   Float_t  ds_all_dt012_vee;
   Int_t    ds_all_ntrk_around_2ry;
   Int_t    ds_all_ntrk_other_vtx_max;
   Int_t    ds_all_flag_final;


   Int_t    ds_all_vtx_id;

   // DecaySearch_final
   Int_t    ds_final_area1;
   Int_t    ds_final_area2;
   Float_t  ds_final_txpeak;
   Float_t  ds_final_typeak;
   Int_t    ds_final_i; 
   Float_t  ds_final_xc;
   Float_t  ds_final_yc;
   Float_t  ds_final_1ry_vx;
   Float_t  ds_final_1ry_vy;
   Float_t  ds_final_1ry_vz;
   Int_t    ds_final_1ry_plt;
   Int_t    ds_final_flagw;
   Int_t    ds_final_n_1ry_trk;
   Float_t  ds_final_2ry_vx;
   Float_t  ds_final_2ry_vy;
   Float_t  ds_final_2ry_vz;
   Int_t    ds_final_2ry_plt;
   Int_t    ds_final_parent_plt_1st;
   Int_t    ds_final_parent_trkID;
   Int_t    ds_final_parent_MCEvt;
   Int_t    ds_final_parent_pdgID;
   Float_t  ds_final_parent_MCp;
   Int_t    ds_final_nparent_1ry;
   Int_t    ds_final_nparent_1ry_penet;
   Int_t    ds_final_nparent_non1ry;
   Float_t  ds_final_parent_tx;
   Float_t  ds_final_parent_ty;
   Int_t    ds_final_ndau;
   Int_t    ds_final_default1;
   Int_t    ds_final_default2;
   Int_t    ds_final_plt_dau1;
   Int_t    ds_final_segid_dau1;
   Int_t    ds_final_dau1_MCEvt;
   Int_t    ds_final_dau1_pdgID;
   Float_t  ds_final_dau1_MCp;
   Float_t  ds_final_ip_to1ry_dau1;
   Float_t  ds_final_ip_to2ry_dau1;
   Float_t  ds_final_tx_dau1;
   Float_t  ds_final_ty_dau1;
   Float_t  ds_final_dt_dau1;
   Float_t  ds_final_dtrms_dau1;
   Float_t  ds_final_dtrmst_dau1;
   Float_t  ds_final_dt_w_dau1;

   Int_t    ds_final_plt_dau2;
   Int_t    ds_final_segid_dau2;
   Int_t    ds_final_dau2_MCEvt;
   Int_t    ds_final_dau2_pdgID;
   Float_t  ds_final_dau2_MCp;
   Float_t  ds_final_ip_to1ry_dau2;
   Float_t  ds_final_ip_to2ry_dau2;
   Float_t  ds_final_tx_dau2;
   Float_t  ds_final_ty_dau2;
   Float_t  ds_final_dt_dau2;
   Float_t  ds_final_dtrms_dau2;
   Float_t  ds_final_dtrmst_dau2;
   Float_t  ds_final_dt_w_dau2;

   Int_t    ds_final_plt_dau3;
   Int_t    ds_final_segid_dau3;
   Int_t    ds_final_dau3_MCEvt;
   Int_t    ds_final_dau3_pdgID;
   Float_t  ds_final_dau3_MCp;
   Float_t  ds_final_ip_to1ry_dau3;
   Float_t  ds_final_ip_to2ry_dau3;
   Float_t  ds_final_tx_dau3;
   Float_t  ds_final_ty_dau3;
   Float_t  ds_final_dt_dau3;
   Float_t  ds_final_dtrms_dau3;
   Float_t  ds_final_dtrmst_dau3;
   Float_t  ds_final_dt_w_dau3;

   Int_t    ds_final_plt_dau4;
   Int_t    ds_final_segid_dau4;
   Int_t    ds_final_dau4_MCEvt;
   Int_t    ds_final_dau4_pdgID;
   Float_t  ds_final_dau4_MCp;
   Float_t  ds_final_ip_to1ry_dau4;
   Float_t  ds_final_ip_to2ry_dau4;
   Float_t  ds_final_tx_dau4;
   Float_t  ds_final_ty_dau4;
   Float_t  ds_final_dt_dau4;
   Float_t  ds_final_dtrms_dau4;
   Float_t  ds_final_dtrmst_dau4;
   Float_t  ds_final_dt_w_dau4;

   Float_t  ds_final_dmin_org_vee;
   Float_t  ds_final_dmin_fine_vee;
   Float_t  ds_final_topen_vee;
   Float_t  ds_final_dt1dt2_vee;
   Float_t  ds_final_dt012_vee;
   Int_t    ds_final_ntrk_around_2ry;
   Int_t    ds_final_ntrk_other_vtx_max;
   Int_t    ds_final_flag_final;

   Int_t    ds_final_vtx_id;

   //DecaySearch_sumfinal
   Int_t    ds_sumfinal_area1;
   Int_t    ds_sumfinal_area2;
   Int_t    ds_sumfinal_i;
   Float_t  ds_sumfinal_xc;
   Float_t  ds_sumfinal_yc;
   Float_t  ds_sumfinal_1ry_vx;
   Float_t  ds_sumfinal_1ry_vy;
   Float_t  ds_sumfinal_1ry_vz;
   Int_t    ds_sumfinal_flagw;
   Int_t    ds_sumfinal_n_1ry_trk;
   Int_t    ds_sumfinal_c1_intrk1;
   Int_t    ds_sumfinal_c1_intrk2;
   Int_t    ds_sumfinal_c1;
   Int_t    ds_sumfinal_c2;
   Int_t    ds_sumfinal_c3;
   Int_t    ds_sumfinal_n2;
   Int_t    ds_sumfinal_n3;
   Int_t    ds_sumfinal_n4;
   Int_t    ds_sumfinal_dt50;
   Int_t    ds_sumfinal_n2_op50;
   Int_t    ds_sumfinal_c1_intrk_for_pa;

   //DecaySearch_intrk
   Int_t    ds_intrk_area1;
   Int_t    ds_intrk_area2;
   Float_t  ds_intrk_txpeak;
   Float_t  ds_intrk_typeak;
   Int_t    ds_intrk_i; 
   Float_t  ds_intrk_xc;
   Float_t  ds_intrk_yc;
   Float_t  ds_intrk_1ry_vx;
   Float_t  ds_intrk_1ry_vy;
   Float_t  ds_intrk_1ry_vz;
   Int_t    ds_intrk_1ry_plt;
   Int_t    ds_intrk_flagw;
   Int_t    ds_intrk_n_1ry_trk;
   Float_t  ds_intrk_2ry_vx;
   Float_t  ds_intrk_2ry_vy;
   Float_t  ds_intrk_2ry_vz;
   Int_t    ds_intrk_2ry_plt;
   Int_t    ds_intrk_parent_plt_1st;
   Int_t    ds_intrk_parent_trkID;
   Int_t    ds_intrk_parent_MCEvt;
   Int_t    ds_intrk_parent_pdgID;
   Float_t  ds_intrk_parent_MCp;
   Int_t    ds_intrk_nparent_1ry;
   Int_t    ds_intrk_nparent_1ry_penet;
   Int_t    ds_intrk_nparent_non1ry;
   Float_t  ds_intrk_parent_tx;
   Float_t  ds_intrk_parent_ty;
   Int_t    ds_intrk_ndau_all;
   Int_t    ds_intrk_ndau_ip700;
   Int_t    ds_intrk_ndau_ip500;
   Int_t    ds_intrk_plt_dau1;
   Int_t    ds_intrk_segid_dau1;
   Int_t    ds_intrk_dau1_MCEvt;
   Int_t    ds_intrk_dau1_pdgID;
   Float_t  ds_intrk_dau1_MCp;
   Float_t  ds_intrk_ip_to1ry_dau1;
   Float_t  ds_intrk_ip_to2ry_dau1;
   Float_t  ds_intrk_tx_dau1;
   Float_t  ds_intrk_ty_dau1;
   Float_t  ds_intrk_dt_dau1;
   Float_t  ds_intrk_dtrms_dau1;
   Float_t  ds_intrk_dtrmst_dau1;
   Float_t  ds_intrk_dt_w_dau1;

   Int_t    ds_intrk_plt_dau2;
   Int_t    ds_intrk_segid_dau2;
   Int_t    ds_intrk_dau2_MCEvt;
   Int_t    ds_intrk_dau2_pdgID;
   Float_t  ds_intrk_dau2_MCp;
   Float_t  ds_intrk_ip_to1ry_dau2;
   Float_t  ds_intrk_ip_to2ry_dau2;
   Float_t  ds_intrk_tx_dau2;
   Float_t  ds_intrk_ty_dau2;
   Float_t  ds_intrk_dt_dau2;
   Float_t  ds_intrk_dtrms_dau2;
   Float_t  ds_intrk_dtrmst_dau2;
   Float_t  ds_intrk_dt_w_dau2;

   Int_t    ds_intrk_plt_dau3;
   Int_t    ds_intrk_segid_dau3;
   Int_t    ds_intrk_dau3_MCEvt;
   Int_t    ds_intrk_dau3_pdgID;
   Float_t  ds_intrk_dau3_MCp;
   Float_t  ds_intrk_ip_to1ry_dau3;
   Float_t  ds_intrk_ip_to2ry_dau3;
   Float_t  ds_intrk_tx_dau3;
   Float_t  ds_intrk_ty_dau3;
   Float_t  ds_intrk_dt_dau3;
   Float_t  ds_intrk_dtrms_dau3;
   Float_t  ds_intrk_dtrmst_dau3;
   Float_t  ds_intrk_dt_w_dau3;

   //DecaySearch_intrk_wt
   Int_t    ds_intrk_wt_area1;
   Int_t    ds_intrk_wt_area2;
   Float_t  ds_intrk_wt_txpeak;
   Float_t  ds_intrk_wt_typeak;
   Int_t    ds_intrk_wt_i; 
   Float_t  ds_intrk_wt_xc;
   Float_t  ds_intrk_wt_yc;
   Float_t  ds_intrk_wt_1ry_vx;
   Float_t  ds_intrk_wt_1ry_vy;
   Float_t  ds_intrk_wt_1ry_vz;
   Int_t    ds_intrk_wt_1ry_plt;
   Int_t    ds_intrk_wt_flagw;
   Int_t    ds_intrk_wt_n_1ry_trk;
   Float_t  ds_intrk_wt_2ry_vx;
   Float_t  ds_intrk_wt_2ry_vy;
   Float_t  ds_intrk_wt_2ry_vz;
   Int_t    ds_intrk_wt_2ry_plt;
   Int_t    ds_intrk_wt_parent_plt_1st;
   Int_t    ds_intrk_wt_parent_trkID;
   Int_t    ds_intrk_wt_parent_MCEvt;
   Int_t    ds_intrk_wt_parent_pdgID;
   Float_t  ds_intrk_wt_parent_MCp;
   Int_t    ds_intrk_wt_nparent_1ry;
   Int_t    ds_intrk_wt_nparent_1ry_penet;
   Int_t    ds_intrk_wt_nparent_non1ry;
   Float_t  ds_intrk_wt_parent_tx;
   Float_t  ds_intrk_wt_parent_ty;
   Int_t    ds_intrk_wt_ndau_all;
   Int_t    ds_intrk_wt_ndau_ip700;
   Int_t    ds_intrk_wt_ndau_ip500;
   Int_t    ds_intrk_wt_plt_dau1;
   Int_t    ds_intrk_wt_segid_dau1;
   Int_t    ds_intrk_wt_dau1_MCEvt;
   Int_t    ds_intrk_wt_dau1_pdgID;
   Float_t  ds_intrk_wt_dau1_MCp;
   Float_t  ds_intrk_wt_ip_to1ry_dau1;
   Float_t  ds_intrk_wt_ip_to2ry_dau1;
   Float_t  ds_intrk_wt_tx_dau1;
   Float_t  ds_intrk_wt_ty_dau1;
   Float_t  ds_intrk_wt_dt_dau1;
   Float_t  ds_intrk_wt_dtrms_dau1;
   Float_t  ds_intrk_wt_dtrmst_dau1;
   Float_t  ds_intrk_wt_dt_w_dau1;

   Int_t    ds_intrk_wt_plt_dau2;
   Int_t    ds_intrk_wt_segid_dau2;
   Int_t    ds_intrk_wt_dau2_MCEvt;
   Int_t    ds_intrk_wt_dau2_pdgID;
   Float_t  ds_intrk_wt_dau2_MCp;
   Float_t  ds_intrk_wt_ip_to1ry_dau2;
   Float_t  ds_intrk_wt_ip_to2ry_dau2;
   Float_t  ds_intrk_wt_tx_dau2;
   Float_t  ds_intrk_wt_ty_dau2;
   Float_t  ds_intrk_wt_dt_dau2;
   Float_t  ds_intrk_wt_dtrms_dau2;
   Float_t  ds_intrk_wt_dtrmst_dau2;
   Float_t  ds_intrk_wt_dt_w_dau2;

   Int_t    ds_intrk_wt_plt_dau3;
   Int_t    ds_intrk_wt_segid_dau3;
   Int_t    ds_intrk_wt_dau3_MCEvt;
   Int_t    ds_intrk_wt_dau3_pdgID;
   Float_t  ds_intrk_wt_dau3_MCp;
   Float_t  ds_intrk_wt_ip_to1ry_dau3;
   Float_t  ds_intrk_wt_ip_to2ry_dau3;
   Float_t  ds_intrk_wt_tx_dau3;
   Float_t  ds_intrk_wt_ty_dau3;
   Float_t  ds_intrk_wt_dt_dau3;
   Float_t  ds_intrk_wt_dtrms_dau3;
   Float_t  ds_intrk_wt_dtrmst_dau3;
   Float_t  ds_intrk_wt_dt_w_dau3;

   //DecaySearch_intrk_for_pa
   Int_t    ds_intrk_for_pa_area1;
   Int_t    ds_intrk_for_pa_area2;
   Float_t  ds_intrk_for_pa_txpeak;
   Float_t  ds_intrk_for_pa_typeak;
   Int_t    ds_intrk_for_pa_i; 
   Float_t  ds_intrk_for_pa_xc;
   Float_t  ds_intrk_for_pa_yc;
   Float_t  ds_intrk_for_pa_1ry_vx;
   Float_t  ds_intrk_for_pa_1ry_vy;
   Float_t  ds_intrk_for_pa_1ry_vz;
   Int_t    ds_intrk_for_pa_1ry_plt;
   Int_t    ds_intrk_for_pa_flagw;
   Int_t    ds_intrk_for_pa_n_1ry_trk;
   Float_t  ds_intrk_for_pa_2ry_vx;
   Float_t  ds_intrk_for_pa_2ry_vy;
   Float_t  ds_intrk_for_pa_2ry_vz;
   Int_t    ds_intrk_for_pa_2ry_plt;
   Int_t    ds_intrk_for_pa_parent_plt_1st;
   Int_t    ds_intrk_for_pa_parent_trkID;
   Int_t    ds_intrk_for_pa_parent_MCEvt;
   Int_t    ds_intrk_for_pa_parent_pdgID;
   Float_t  ds_intrk_for_pa_parent_MCp;
   Int_t    ds_intrk_for_pa_nparent_1ry;
   Int_t    ds_intrk_for_pa_nparent_1ry_penet;
   Int_t    ds_intrk_for_pa_nparent_non1ry;
   Float_t  ds_intrk_for_pa_parent_tx;
   Float_t  ds_intrk_for_pa_parent_ty;
   Int_t    ds_intrk_for_pa_ndau_all;
   Int_t    ds_intrk_for_pa_ndau_ip700;
   Int_t    ds_intrk_for_pa_ndau_ip500;
   Int_t    ds_intrk_for_pa_plt_dau1;
   Int_t    ds_intrk_for_pa_segid_dau1;
   Int_t    ds_intrk_for_pa_dau1_MCEvt;
   Int_t    ds_intrk_for_pa_dau1_pdgID;
   Float_t  ds_intrk_for_pa_dau1_MCp;
   Float_t  ds_intrk_for_pa_ip_to1ry_dau1;
   Float_t  ds_intrk_for_pa_ip_to2ry_dau1;
   Float_t  ds_intrk_for_pa_tx_dau1;
   Float_t  ds_intrk_for_pa_ty_dau1;
   Float_t  ds_intrk_for_pa_dt_dau1;
   Float_t  ds_intrk_for_pa_dtrms_dau1;
   Float_t  ds_intrk_for_pa_dtrmst_dau1;
   Float_t  ds_intrk_for_pa_dt_w_dau1;

   Int_t    ds_intrk_for_pa_plt_dau2;
   Int_t    ds_intrk_for_pa_segid_dau2;
   Int_t    ds_intrk_for_pa_dau2_MCEvt;
   Int_t    ds_intrk_for_pa_dau2_pdgID;
   Float_t  ds_intrk_for_pa_dau2_MCp;
   Float_t  ds_intrk_for_pa_ip_to1ry_dau2;
   Float_t  ds_intrk_for_pa_ip_to2ry_dau2;
   Float_t  ds_intrk_for_pa_tx_dau2;
   Float_t  ds_intrk_for_pa_ty_dau2;
   Float_t  ds_intrk_for_pa_dt_dau2;
   Float_t  ds_intrk_for_pa_dtrms_dau2;
   Float_t  ds_intrk_for_pa_dtrmst_dau2;
   Float_t  ds_intrk_for_pa_dt_w_dau2;

   Int_t    ds_intrk_for_pa_plt_dau3;
   Int_t    ds_intrk_for_pa_segid_dau3;
   Int_t    ds_intrk_for_pa_dau3_MCEvt;
   Int_t    ds_intrk_for_pa_dau3_pdgID;
   Float_t  ds_intrk_for_pa_dau3_MCp;
   Float_t  ds_intrk_for_pa_ip_to1ry_dau3;
   Float_t  ds_intrk_for_pa_ip_to2ry_dau3;
   Float_t  ds_intrk_for_pa_tx_dau3;
   Float_t  ds_intrk_for_pa_ty_dau3;
   Float_t  ds_intrk_for_pa_dt_dau3;
   Float_t  ds_intrk_for_pa_dtrms_dau3;
   Float_t  ds_intrk_for_pa_dtrmst_dau3;
   Float_t  ds_intrk_for_pa_dt_w_dau3;

   //DecaySearch_intrk_for_pa_wt
   Int_t    ds_intrk_for_pa_wt_area1;
   Int_t    ds_intrk_for_pa_wt_area2;
   Float_t  ds_intrk_for_pa_wt_txpeak;
   Float_t  ds_intrk_for_pa_wt_typeak;
   Int_t    ds_intrk_for_pa_wt_i; 
   Float_t  ds_intrk_for_pa_wt_xc;
   Float_t  ds_intrk_for_pa_wt_yc;
   Float_t  ds_intrk_for_pa_wt_1ry_vx;
   Float_t  ds_intrk_for_pa_wt_1ry_vy;
   Float_t  ds_intrk_for_pa_wt_1ry_vz;
   Int_t    ds_intrk_for_pa_wt_1ry_plt;
   Int_t    ds_intrk_for_pa_wt_flagw;
   Int_t    ds_intrk_for_pa_wt_n_1ry_trk;
   Float_t  ds_intrk_for_pa_wt_2ry_vx;
   Float_t  ds_intrk_for_pa_wt_2ry_vy;
   Float_t  ds_intrk_for_pa_wt_2ry_vz;
   Int_t    ds_intrk_for_pa_wt_2ry_plt;
   Int_t    ds_intrk_for_pa_wt_parent_plt_1st;
   Int_t    ds_intrk_for_pa_wt_parent_trkID;
   Int_t    ds_intrk_for_pa_wt_parent_MCEvt;
   Int_t    ds_intrk_for_pa_wt_parent_pdgID;
   Float_t  ds_intrk_for_pa_wt_parent_MCp;
   Int_t    ds_intrk_for_pa_wt_nparent_1ry;
   Int_t    ds_intrk_for_pa_wt_nparent_1ry_penet;
   Int_t    ds_intrk_for_pa_wt_nparent_non1ry;
   Float_t  ds_intrk_for_pa_wt_parent_tx;
   Float_t  ds_intrk_for_pa_wt_parent_ty;
   Int_t    ds_intrk_for_pa_wt_ndau_all;
   Int_t    ds_intrk_for_pa_wt_ndau_ip700;
   Int_t    ds_intrk_for_pa_wt_ndau_ip500;
   Int_t    ds_intrk_for_pa_wt_plt_dau1;
   Int_t    ds_intrk_for_pa_wt_segid_dau1;
   Int_t    ds_intrk_for_pa_wt_dau1_MCEvt;
   Int_t    ds_intrk_for_pa_wt_dau1_pdgID;
   Float_t  ds_intrk_for_pa_wt_dau1_MCp;
   Float_t  ds_intrk_for_pa_wt_ip_to1ry_dau1;
   Float_t  ds_intrk_for_pa_wt_ip_to2ry_dau1;
   Float_t  ds_intrk_for_pa_wt_tx_dau1;
   Float_t  ds_intrk_for_pa_wt_ty_dau1;
   Float_t  ds_intrk_for_pa_wt_dt_dau1;
   Float_t  ds_intrk_for_pa_wt_dtrms_dau1;
   Float_t  ds_intrk_for_pa_wt_dtrmst_dau1;
   Float_t  ds_intrk_for_pa_wt_dt_w_dau1;

   Int_t    ds_intrk_for_pa_wt_plt_dau2;
   Int_t    ds_intrk_for_pa_wt_segid_dau2;
   Int_t    ds_intrk_for_pa_wt_dau2_MCEvt;
   Int_t    ds_intrk_for_pa_wt_dau2_pdgID;
   Float_t  ds_intrk_for_pa_wt_dau2_MCp;
   Float_t  ds_intrk_for_pa_wt_ip_to1ry_dau2;
   Float_t  ds_intrk_for_pa_wt_ip_to2ry_dau2;
   Float_t  ds_intrk_for_pa_wt_tx_dau2;
   Float_t  ds_intrk_for_pa_wt_ty_dau2;
   Float_t  ds_intrk_for_pa_wt_dt_dau2;
   Float_t  ds_intrk_for_pa_wt_dtrms_dau2;
   Float_t  ds_intrk_for_pa_wt_dtrmst_dau2;
   Float_t  ds_intrk_for_pa_wt_dt_w_dau2;

   Int_t    ds_intrk_for_pa_wt_plt_dau3;
   Int_t    ds_intrk_for_pa_wt_segid_dau3;
   Int_t    ds_intrk_for_pa_wt_dau3_MCEvt;
   Int_t    ds_intrk_for_pa_wt_dau3_pdgID;
   Float_t  ds_intrk_for_pa_wt_dau3_MCp;
   Float_t  ds_intrk_for_pa_wt_ip_to1ry_dau3;
   Float_t  ds_intrk_for_pa_wt_ip_to2ry_dau3;
   Float_t  ds_intrk_for_pa_wt_tx_dau3;
   Float_t  ds_intrk_for_pa_wt_ty_dau3;
   Float_t  ds_intrk_for_pa_wt_dt_dau3;
   Float_t  ds_intrk_for_pa_wt_dtrms_dau3;
   Float_t  ds_intrk_for_pa_wt_dtrmst_dau3;
   Float_t  ds_intrk_for_pa_wt_dt_w_dau3;

   Char_t ipChar05[16],ipChar04[16],ntrk_smallChar[16],dtChar[16],dt_posChar[16];

   Int_t trk_multip = 0, vtx_multip = 0;

   char inArr[1024];
   strcpy(inArr, inputName.c_str());

   TString filename = outputName;
   //FILE *fp = fopen("20220622_PD04/PD04/ds_res_PR2018_PD04_p006.txt","r");
   FILE *fp = fopen(inArr,"r");

   TFile *hfile = 0;

   hfile = TFile::Open(filename,"RECREATE");
   TTree *vtx = new TTree("VTX","VTXinfo");

   //vtx->Branch("type",type,"type/C");
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
   vtx->Branch("intType",&vtx_int_type,"intType/I");
   vtx->Branch("intMed",&vtx_int_medium,"intMed/I");

   TTree *trk = new TTree("TRK","TRKinfo");

   //trk->Branch("type",type,"type/C");
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
   trk->Branch("intMed",&trk_int_medium,"intMed/I");
   /*
   TTree *par = new TTree("PAR","ParentInfo");

   par->Branch("area1",&trk_area1,"area1/I");
   par->Branch("area2",&trk_area2,"area2/I");
   par->Branch("txpeak",&trk_txpeak,"txpeak/F");
   par->Branch("typeak",&trk_typeak,"typeak/F");
   par->Branch("i",&trk_i,"i/I");
   par->Branch("vx",&trk_vx,"vx/F");
   par->Branch("vy",&trk_vy,"vy/F");
   par->Branch("vz",&trk_vz,"vz/F");
   par->Branch("flagw",&trk_flagw,"flagw/I");
   par->Branch("n_1ry_trk",&trk_n_1ry_trk,"n_1ry_trk/I");
   par->Branch("n_1ry_parent_cut0",&trk_n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
   par->Branch("n_1ry_parent_dmin_cut",&trk_n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");
   par->Branch("dz",&trk_dz,"dz/F");
   par->Branch("trk_id",&trk_id,"trk_id/I");
   par->Branch("plt_of_1seg",&trk_plt_of_1seg,"plt_of_1seg/I");
   par->Branch("seg_id_of_1seg",&trk_seg_id_of_1seg,"seg_id_of_1seg/I");
   par->Branch("seg_x",&trk_seg_x,"seg_x/F");
   par->Branch("seg_y",&trk_seg_y,"seg_y/F");
   par->Branch("tx",&trk_tx,"tx/F");
   par->Branch("ty",&trk_ty,"ty/F");
   par->Branch("nseg",&trk_nseg,"nseg/I");
   par->Branch("vID",&trk_vID,"vID/I");
   par->Branch("ip_to_1ry_using_1stseg",&trk_ip_to_1ry_using_1stseg,"ip_to_1ry_using_1stseg/F");
   par->Branch("ip_to_1ry_using_2ndseg",&trk_ip_to_1ry_using_2ndseg,"ip_to_1ry_using_2ndseg/F");
   par->Branch("ph_mean",&trk_ph_mean,"ph_mean/F");
   par->Branch("dtrms1_trk",&trk_dtrms1_trk,"dtrms1_trk/F");
   */

   TTree *par = new TTree("PAR","PARinfo");

   par->Branch("area1",&parC_area1,"area1/I");
   par->Branch("area2",&parC_area2,"area2/I");
   par->Branch("txpeak",&parC_txpeak,"txpeak/F");
   par->Branch("typeak",&parC_typeak,"typeak/F");
   par->Branch("i",&parC_i,"i/I");
   par->Branch("vx",&parC_vx,"vx/F");
   par->Branch("vy",&parC_vy,"vy/F");
   par->Branch("vz",&parC_vz,"vz/F");
   par->Branch("dz",&parC_dz,"dz/F");
   par->Branch("trk_id",&parC_id,"trk_id/I");
   par->Branch("plt_of_1seg",&parC_plt_of_1seg,"plt_of_1seg/I");
   par->Branch("seg_id_of_1seg",&parC_seg_id_of_1seg,"seg_id_of_1seg/I");
   par->Branch("tx05pos",&parC_tx05pos,"tx05pos/F");
   par->Branch("ty05pos",&parC_ty05pos,"ty05pos/F");
   par->Branch("nseg",&parC_nseg,"nseg/I");
   par->Branch("n_1ry_trk",&parC_n_1ry_trk,"n_1ry_trk/I");
   //par->Branch("Par16",&Par16,"Par16/F");
   par->Branch("ip_pos05",&parC_ip_pos05,"ip_pos05/F");
   //par->Branch("Par18",&Par18,"Par18/F");
   par->Branch("ip_pos04",&parC_ip_pos04,"ip_pos04/F");
   //par->Branch("Par20",&Par20,"Par20/F");
   par->Branch("ntrk_small",&parC_ntrk_small,"ntrk_small/I");
   //par->Branch("Par22",&Par22,"Par22/F");
   par->Branch("dt",&parC_dt,"dt/F");
   //par->Branch("Par24",&Par24,"Par24/F");
   par->Branch("dt_pos",&parC_dt_pos,"dt_pos/F");
   par->Branch("pl_up1ry_plmin",&parC_pl_up1ry_plmin,"pl_up1ry_plmin/I");
   par->Branch("pl_up1ry_plmax",&parC_pl_up1ry_plmax,"pl_up1ry_plmax/I");
   par->Branch("pl_dwn1ry_plmin",&parC_pl_dwn1ry_plmin,"pl_dwn1ry_plmin/I");
   par->Branch("pl_dwn1ry_plmax",&parC_pl_dwn1ry_plmax,"pl_dwn1ry_plmax/I");
   par->Branch("vID",&parC_vID,"vID/I");
   par->Branch("flagp",&par_flagp,"flagp/I");
   par->Branch("global_parID",&glob_parid,"global_parID/I");

   TTree *us_ptrk = new TTree("US_PTRK","PTRKinfo");

   us_ptrk->Branch("area1",&ptrk_US_area1,"area1/I");
   us_ptrk->Branch("US_trID",&ptrk_US_trID,"US_trID/I");
   us_ptrk->Branch("US_gtrID",&ptrk_US_gtrID,"US_gtrID/I");
   us_ptrk->Branch("US_plt_of_1seg",&ptrk_US_plt_of_1seg,"US_plt_of_1seg/I");
   us_ptrk->Branch("US_PosX_of_1seg",&ptrk_US_PosX_of_1seg,"US_PosX_of_1seg/I");
   us_ptrk->Branch("US_PosY_of_1seg",&ptrk_US_PosY_of_1seg,"US_PosY_of_1seg/I");
   us_ptrk->Branch("US_PosZ_of_1seg",&ptrk_US_PosZ_of_1seg,"US_PosZ_of_1seg/I");
   us_ptrk->Branch("US_TX",&ptrk_US_TX,"US_TX/F");
   us_ptrk->Branch("US_TY",&ptrk_US_TY,"US_TY/F");

   TTree *ds_ptrk = new TTree("DS_PTRK","PTRKinfo");

   ds_ptrk->Branch("area1",&ptrk_DS_area1,"area1/I");
   ds_ptrk->Branch("DS_trID",&ptrk_DS_trID,"DS_trID/I");
   ds_ptrk->Branch("DS_gtrID",&ptrk_DS_gtrID,"DS_gtrID/I");
   ds_ptrk->Branch("DS_plt_of_1seg",&ptrk_DS_plt_of_1seg,"DS_plt_of_1seg/I");
   ds_ptrk->Branch("DS_PosX_of_1seg",&ptrk_DS_PosX_of_1seg,"DS_PosX_of_1seg/I");
   ds_ptrk->Branch("DS_PosY_of_1seg",&ptrk_DS_PosY_of_1seg,"DS_PosY_of_1seg/I");
   ds_ptrk->Branch("DS_PosZ_of_1seg",&ptrk_DS_PosZ_of_1seg,"DS_PosZ_of_1seg/I");
   ds_ptrk->Branch("DS_TX",&ptrk_DS_TX,"DS_TX/F");
   ds_ptrk->Branch("DS_TY",&ptrk_DS_TY,"DS_TY/F");

TTree *ds_all = new TTree("DsAll","DsAllinfo");

   ds_all->Branch("area1",&ds_all_area1,"area1/I");
   ds_all->Branch("area2",&ds_all_area2,"area2/I");
   ds_all->Branch("txpeak",&ds_all_txpeak,"txpeak/F");
   ds_all->Branch("typeak",&ds_all_typeak,"typeak/F");
   ds_all->Branch("i",&ds_all_i,"i/I");
   ds_all->Branch("xc",&ds_all_xc,"xc/F");
   ds_all->Branch("yc",&ds_all_yc,"yc/F");
   ds_all->Branch("1ry_vx",&ds_all_1ry_vx,"1ry_vx/F");
   ds_all->Branch("1ry_vy",&ds_all_1ry_vy,"1ry_vy/F");
   ds_all->Branch("1ry_vz",&ds_all_1ry_vz,"1ry_vz/F");
   ds_all->Branch("1ry_plt",&ds_all_1ry_plt,"1ry_plt/I");
   ds_all->Branch("flagw",&ds_all_flagw,"flagw/I");
   ds_all->Branch("n_1ry_trk",&ds_all_n_1ry_trk,"n_1ry_trk/I");
   ds_all->Branch("2ry_vx",&ds_all_2ry_vx,"2ry_vx/F");
   ds_all->Branch("2ry_vy",&ds_all_2ry_vy,"2ry_vy/F");
   ds_all->Branch("2ry_vz",&ds_all_2ry_vz,"2ry_vz/F");
   ds_all->Branch("2ry_plt",&ds_all_2ry_plt,"2ry_plt/I");
   ds_all->Branch("parent_plt_1st",&ds_all_parent_plt_1st,"parent_plt_1st/I");
   ds_all->Branch("parent_trkID",&ds_all_parent_trkID,"parent_trkID/I");
   ds_all->Branch("parent_MCEvt",&ds_all_parent_MCEvt,"parent_MCEvt/I");
   ds_all->Branch("parent_pdgID",&ds_all_parent_pdgID,"parent_pdgID/I");
   ds_all->Branch("parent_MCp",&ds_all_parent_MCp,"parent_MCp/F");
   ds_all->Branch("nparent_1ry",&ds_all_nparent_1ry,"nparent_1ry/I");
   ds_all->Branch("nparent_1ry_penet",&ds_all_nparent_1ry_penet,"nparent_1ry/I");
   ds_all->Branch("nparent_non1ry",&ds_all_nparent_non1ry,"nparent_non1ry/I");
   ds_all->Branch("parent_tx",&ds_all_parent_tx,"parent_tx/F");
   ds_all->Branch("parent_ty",&ds_all_parent_ty,"parent_ty/F");
   ds_all->Branch("ndau",&ds_all_ndau,"ndau/I");
   ds_all->Branch("default1",&ds_all_default1,"default1/I");
   ds_all->Branch("default2",&ds_all_default2,"default2/I");

   ds_all->Branch("plt_dau1",&ds_all_plt_dau1,"plt_dau1/I");
   ds_all->Branch("segid_dau1",&ds_all_segid_dau1,"segid_dau1/I");
   ds_all->Branch("dau1_MCEvt",&ds_all_dau1_MCEvt,"dau1_MCEvt/I");
   ds_all->Branch("dau1_pdgID",&ds_all_dau1_pdgID,"dau1_pdgID/I");
   ds_all->Branch("dau1_MCp",&ds_all_dau1_MCp,"dau1_MCp/F");
   ds_all->Branch("ip_to1ry_dau1",&ds_all_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_all->Branch("ip_to2ry_dau1",&ds_all_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_all->Branch("tx_dau1",&ds_all_tx_dau1,"tx_dau1/F");
   ds_all->Branch("ty_dau1",&ds_all_ty_dau1,"ty_dau1/F");
   ds_all->Branch("dt_dau1",&ds_all_dt_dau1,"dt_dau1/F");
   ds_all->Branch("dtrms_dau1",&ds_all_dtrms_dau1,"dtrms_dau1/F");
   ds_all->Branch("dtrmst_dau1",&ds_all_dtrmst_dau1,"dtrmst_dau1/F");
   ds_all->Branch("dt_w_dau1",&ds_all_dt_w_dau1,"dt_w_dau1/F");
   ds_all->Branch("plt_dau2",&ds_all_plt_dau2,"plt_dau2/I");
   ds_all->Branch("segid_dau2",&ds_all_segid_dau2,"segid_dau2/I");
   ds_all->Branch("dau2_MCEvt",&ds_all_dau2_MCEvt,"dau2_MCEvt/I");
   ds_all->Branch("dau2_pdgID",&ds_all_dau2_pdgID,"dau2_pdgID/I");
   ds_all->Branch("dau2_MCp",&ds_all_dau2_MCp,"dau2_MCp/F");
   ds_all->Branch("ip_to1ry_dau2",&ds_all_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_all->Branch("ip_to2ry_dau2",&ds_all_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_all->Branch("tx_dau2",&ds_all_tx_dau2,"tx_dau2/F");
   ds_all->Branch("ty_dau2",&ds_all_ty_dau2,"ty_dau2/F");
   ds_all->Branch("dt_dau2",&ds_all_dt_dau2,"dt_dau2/F");
   ds_all->Branch("dtrms_dau2",&ds_all_dtrms_dau2,"dtrms_dau2/F");
   ds_all->Branch("dtrmst_dau2",&ds_all_dtrmst_dau2,"dtrmst_dau2/F");
   ds_all->Branch("dt_w_dau2",&ds_all_dt_w_dau2,"dt_w_dau2/F");
   ds_all->Branch("plt_dau3",&ds_all_plt_dau3,"plt_dau3/I");
   ds_all->Branch("segid_dau3",&ds_all_segid_dau3,"segid_dau3/I");
   ds_all->Branch("dau3_MCEvt",&ds_all_dau3_MCEvt,"dau3_MCEvt/I");
   ds_all->Branch("dau3_pdgID",&ds_all_dau3_pdgID,"dau3_pdgID/I");
   ds_all->Branch("dau3_MCp",&ds_all_dau3_MCp,"dau3_MCp/F");
   ds_all->Branch("ip_to1ry_dau3",&ds_all_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_all->Branch("ip_to2ry_dau3",&ds_all_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_all->Branch("tx_dau3",&ds_all_tx_dau3,"tx_dau3/F");
   ds_all->Branch("ty_dau3",&ds_all_ty_dau3,"ty_dau3/F");
   ds_all->Branch("dt_dau3",&ds_all_dt_dau3,"dt_dau3/F");
   ds_all->Branch("dtrms_dau3",&ds_all_dtrms_dau3,"dtrms_dau3/F");
   ds_all->Branch("dtrmst_dau3",&ds_all_dtrmst_dau3,"dtrmst_dau3/F");
   ds_all->Branch("dt_w_dau3",&ds_all_dt_w_dau3,"dt_w_dau3/F"); 
   ds_all->Branch("plt_dau4",&ds_all_plt_dau4,"plt_dau4/I");
   ds_all->Branch("segid_dau4",&ds_all_segid_dau4,"segid_dau4/I");
   ds_all->Branch("dau4_MCEvt",&ds_all_dau4_MCEvt,"dau4_MCEvt/I");
   ds_all->Branch("dau4_pdgID",&ds_all_dau4_pdgID,"dau4_pdgID/I");
   ds_all->Branch("dau4_MCp",&ds_all_dau4_MCp,"dau4_MCp/F");
   ds_all->Branch("ip_to1ry_dau4",&ds_all_ip_to1ry_dau4,"ip_to1ry_dau4/F");
   ds_all->Branch("ip_to2ry_dau4",&ds_all_ip_to2ry_dau4,"ip_to2ry_dau4/F");
   ds_all->Branch("tx_dau4",&ds_all_tx_dau4,"tx_dau4/F");
   ds_all->Branch("ty_dau4",&ds_all_ty_dau4,"ty_dau4/F");
   ds_all->Branch("dt_dau4",&ds_all_dt_dau4,"dt_dau4/F");
   ds_all->Branch("dtrms_dau4",&ds_all_dtrms_dau4,"dtrms_dau4/F");
   ds_all->Branch("dtrmst_dau4",&ds_all_dtrmst_dau4,"dtrmst_dau4/F");
   ds_all->Branch("dt_w_dau4",&ds_all_dt_w_dau4,"dt_w_dau4/F"); 

   ds_all->Branch("dmin_org_vee",&ds_all_dmin_org_vee,"dmin_org_vee/F");
   ds_all->Branch("dmin_fine_vee",&ds_all_dmin_fine_vee,"dmin_fine_vee/F");
   ds_all->Branch("topen_vee",&ds_all_topen_vee,"topen_vee/F");
   ds_all->Branch("dt1dt2_vee",&ds_all_dt1dt2_vee,"dt1dt2_vee/F");
   ds_all->Branch("dt012_vee",&ds_all_dt012_vee,"dt012_vee/F");
   ds_all->Branch("ntrk_around_2ry",&ds_all_ntrk_around_2ry,"ntrk_around_2ry/I");
   ds_all->Branch("ntrk_other_vtx_max",&ds_all_ntrk_other_vtx_max,"ntrk_other_vtx_max/I");
   ds_all->Branch("flag_final",&ds_all_flag_final,"flag_final/I");

   ds_all->Branch("vID",&ds_all_vtx_id,"vID/I");


   TTree *ds_final = new TTree("DsFinal","DsFinalinfo");

   ds_final->Branch("area1",&ds_final_area1,"area1/I");
   ds_final->Branch("area2",&ds_final_area2,"area2/I");
   ds_final->Branch("txpeak",&ds_final_txpeak,"txpeak/F");
   ds_final->Branch("typeak",&ds_final_typeak,"typeak/F");
   ds_final->Branch("i",&ds_final_i,"i/I");
   ds_final->Branch("xc",&ds_final_xc,"xc/F");
   ds_final->Branch("yc",&ds_final_yc,"yc/F");
   ds_final->Branch("1ry_vx",&ds_final_1ry_vx,"1ry_vx/F");
   ds_final->Branch("1ry_vy",&ds_final_1ry_vy,"1ry_vy/F");
   ds_final->Branch("1ry_vz",&ds_final_1ry_vz,"1ry_vz/F");
   ds_final->Branch("1ry_plt",&ds_final_1ry_plt,"1ry_plt/I");
   ds_final->Branch("flagw",&ds_final_flagw,"flagw/I");
   ds_final->Branch("n_1ry_trk",&ds_final_n_1ry_trk,"n_1ry_trk/I");
   ds_final->Branch("2ry_vx",&ds_final_2ry_vx,"2ry_vx/F");
   ds_final->Branch("2ry_vy",&ds_final_2ry_vy,"2ry_vy/F");
   ds_final->Branch("2ry_vz",&ds_final_2ry_vz,"2ry_vz/F");
   ds_final->Branch("2ry_plt",&ds_final_2ry_plt,"2ry_plt/I");
   ds_final->Branch("parent_plt_1st",&ds_final_parent_plt_1st,"parent_plt_1st/I");
   ds_final->Branch("parent_trkID",&ds_final_parent_trkID,"parent_trkID/I");
   ds_final->Branch("parent_MCEvt",&ds_final_parent_MCEvt,"parent_MCEvt/I");
   ds_final->Branch("parent_pdgID",&ds_final_parent_pdgID,"parent_pdgID/I");
   ds_final->Branch("parent_MCp",&ds_final_parent_MCp,"parent_MCp/F");
   ds_final->Branch("nparent_1ry",&ds_final_nparent_1ry,"nparent_1ry/I");
   ds_final->Branch("nparent_1ry_penet",&ds_final_nparent_1ry_penet,"nparent_1ry/I");
   ds_final->Branch("nparent_non1ry",&ds_final_nparent_non1ry,"nparent_non1ry/I");
   ds_final->Branch("parent_tx",&ds_final_parent_tx,"parent_tx/F");
   ds_final->Branch("parent_ty",&ds_final_parent_ty,"parent_ty/F");
   ds_final->Branch("ndau",&ds_final_ndau,"ndau/I");
   ds_final->Branch("default1",&ds_final_default1,"default1/I");
   ds_final->Branch("default2",&ds_final_default2,"default2/I");

   ds_final->Branch("plt_dau1",&ds_final_plt_dau1,"plt_dau1/I");
   ds_final->Branch("segid_dau1",&ds_final_segid_dau1,"segid_dau1/I");
   ds_final->Branch("dau1_MCEvt",&ds_final_dau1_MCEvt,"dau1_MCEvt/I");
   ds_final->Branch("dau1_pdgID",&ds_final_dau1_pdgID,"dau1_pdgID/I");
   ds_final->Branch("dau1_MCp",&ds_final_dau1_MCp,"dau1_MCp/F");
   ds_final->Branch("ip_to1ry_dau1",&ds_final_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_final->Branch("ip_to2ry_dau1",&ds_final_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_final->Branch("tx_dau1",&ds_final_tx_dau1,"tx_dau1/F");
   ds_final->Branch("ty_dau1",&ds_final_ty_dau1,"ty_dau1/F");
   ds_final->Branch("dt_dau1",&ds_final_dt_dau1,"dt_dau1/F");
   ds_final->Branch("dtrms_dau1",&ds_final_dtrms_dau1,"dtrms_dau1/F");
   ds_final->Branch("dtrmst_dau1",&ds_final_dtrmst_dau1,"dtrmst_dau1/F");
   ds_final->Branch("dt_w_dau1",&ds_final_dt_w_dau1,"dt_w_dau1/F");
   ds_final->Branch("plt_dau2",&ds_final_plt_dau2,"plt_dau2/I");
   ds_final->Branch("segid_dau2",&ds_final_segid_dau2,"segid_dau2/I");
   ds_final->Branch("dau2_MCEvt",&ds_final_dau2_MCEvt,"dau2_MCEvt/I");
   ds_final->Branch("dau2_pdgID",&ds_final_dau2_pdgID,"dau2_pdgID/I");
   ds_final->Branch("dau2_MCp",&ds_final_dau2_MCp,"dau2_MCp/F");
   ds_final->Branch("ip_to1ry_dau2",&ds_final_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_final->Branch("ip_to2ry_dau2",&ds_final_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_final->Branch("tx_dau2",&ds_final_tx_dau2,"tx_dau2/F");
   ds_final->Branch("ty_dau2",&ds_final_ty_dau2,"ty_dau2/F");
   ds_final->Branch("dt_dau2",&ds_final_dt_dau2,"dt_dau2/F");
   ds_final->Branch("dtrms_dau2",&ds_final_dtrms_dau2,"dtrms_dau2/F");
   ds_final->Branch("dtrmst_dau2",&ds_final_dtrmst_dau2,"dtrmst_dau2/F");
   ds_final->Branch("dt_w_dau2",&ds_final_dt_w_dau2,"dt_w_dau2/F");
   ds_final->Branch("plt_dau3",&ds_final_plt_dau3,"plt_dau3/I");
   ds_final->Branch("segid_dau3",&ds_final_segid_dau3,"segid_dau3/I");
   ds_final->Branch("dau3_MCEvt",&ds_final_dau3_MCEvt,"dau3_MCEvt/I");
   ds_final->Branch("dau3_pdgID",&ds_final_dau3_pdgID,"dau3_pdgID/I");
   ds_final->Branch("dau3_MCp",&ds_final_dau3_MCp,"dau3_MCp/F");
   ds_final->Branch("ip_to1ry_dau3",&ds_final_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_final->Branch("ip_to2ry_dau3",&ds_final_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_final->Branch("tx_dau3",&ds_final_tx_dau3,"tx_dau3/F");
   ds_final->Branch("ty_dau3",&ds_final_ty_dau3,"ty_dau3/F");
   ds_final->Branch("dt_dau3",&ds_final_dt_dau3,"dt_dau3/F");
   ds_final->Branch("dtrms_dau3",&ds_final_dtrms_dau3,"dtrms_dau3/F");
   ds_final->Branch("dtrmst_dau3",&ds_final_dtrmst_dau3,"dtrmst_dau3/F");
   ds_final->Branch("dt_w_dau3",&ds_final_dt_w_dau3,"dt_w_dau3/F"); 
   ds_final->Branch("plt_dau4",&ds_final_plt_dau4,"plt_dau4/I");
   ds_final->Branch("segid_dau4",&ds_final_segid_dau4,"segid_dau4/I");
   ds_final->Branch("dau4_MCEvt",&ds_final_dau4_MCEvt,"dau4_MCEvt/I");
   ds_final->Branch("dau4_pdgID",&ds_final_dau4_pdgID,"dau4_pdgID/I");
   ds_final->Branch("dau4_MCp",&ds_final_dau4_MCp,"dau4_MCp/F");
   ds_final->Branch("ip_to1ry_dau4",&ds_final_ip_to1ry_dau4,"ip_to1ry_dau4/F");
   ds_final->Branch("ip_to2ry_dau4",&ds_final_ip_to2ry_dau4,"ip_to2ry_dau4/F");
   ds_final->Branch("tx_dau4",&ds_final_tx_dau4,"tx_dau4/F");
   ds_final->Branch("ty_dau4",&ds_final_ty_dau4,"ty_dau4/F");
   ds_final->Branch("dt_dau4",&ds_final_dt_dau4,"dt_dau4/F");
   ds_final->Branch("dtrms_dau4",&ds_final_dtrms_dau4,"dtrms_dau4/F");
   ds_final->Branch("dtrmst_dau4",&ds_final_dtrmst_dau4,"dtrmst_dau4/F");
   ds_final->Branch("dt_w_dau4",&ds_final_dt_w_dau4,"dt_w_dau4/F"); 

   ds_final->Branch("dmin_org_vee",&ds_final_dmin_org_vee,"dmin_org_vee/F");
   ds_final->Branch("dmin_fine_vee",&ds_final_dmin_fine_vee,"dmin_fine_vee/F");
   ds_final->Branch("topen_vee",&ds_final_topen_vee,"topen_vee/F");
   ds_final->Branch("dt1dt2_vee",&ds_final_dt1dt2_vee,"dt1dt2_vee/F");
   ds_final->Branch("dt012_vee",&ds_final_dt012_vee,"dt012_vee/F");
   ds_final->Branch("ntrk_around_2ry",&ds_final_ntrk_around_2ry,"ntrk_around_2ry/I");
   ds_final->Branch("ntrk_other_vtx_max",&ds_final_ntrk_other_vtx_max,"ntrk_other_vtx_max/I");
   ds_final->Branch("flag_final",&ds_final_flag_final,"flag_final/I");

   ds_final->Branch("vID",&ds_final_vtx_id,"vID/I");


   TTree *ds_sumfinal = new TTree("DsSumFinal","DsSumFinalinfo");

   ds_sumfinal->Branch("area1",&ds_sumfinal_area1,"area1/I");
   ds_sumfinal->Branch("area2",&ds_sumfinal_area2,"area2/I");
   ds_sumfinal->Branch("i",&ds_sumfinal_i,"i/I");
   ds_sumfinal->Branch("xc",&ds_sumfinal_xc,"xc/F");
   ds_sumfinal->Branch("yc",&ds_sumfinal_yc,"yc/F");
   ds_sumfinal->Branch("1ry_vx",&ds_sumfinal_1ry_vx,"1ry_vx/F");
   ds_sumfinal->Branch("1ry_vy",&ds_sumfinal_1ry_vy,"1ry_vy/F");
   ds_sumfinal->Branch("1ry_vz",&ds_sumfinal_1ry_vz,"1ry_vz/F");
   ds_sumfinal->Branch("flagw",&ds_sumfinal_flagw,"flagw/I");
   ds_sumfinal->Branch("n_1ry_trk",&ds_sumfinal_n_1ry_trk,"n_1ry_trk/I");
   ds_sumfinal->Branch("c1_intrk1",&ds_sumfinal_c1_intrk1,"c1_intrk1/I");
   ds_sumfinal->Branch("c1_intrk2",&ds_sumfinal_c1_intrk2,"c1_intrk2/I");
   ds_sumfinal->Branch("c1",&ds_sumfinal_c1,"c1/I");
   ds_sumfinal->Branch("c2",&ds_sumfinal_c2,"c2/I");
   ds_sumfinal->Branch("c3",&ds_sumfinal_c3,"c3/I");
   ds_sumfinal->Branch("n2",&ds_sumfinal_n2,"n2/I");
   ds_sumfinal->Branch("n3",&ds_sumfinal_n3,"n3/I");
   ds_sumfinal->Branch("n4",&ds_sumfinal_n4,"n4/I");
   ds_sumfinal->Branch("dt50",&ds_sumfinal_dt50,"dt50/I");
   ds_sumfinal->Branch("n2_op50",&ds_sumfinal_n2_op50,"n2_op50/I");
   ds_sumfinal->Branch("c1_intrk_for_pa",&ds_sumfinal_c1_intrk_for_pa,"c1_intrk_for_pa/I");


   TTree *ds_intrk = new TTree("DsInTrk","DsInTrkinfo");

   ds_intrk->Branch("area1",&ds_intrk_area1,"area1/I");
   ds_intrk->Branch("area2",&ds_intrk_area2,"area2/I");
   ds_intrk->Branch("txpeak",&ds_intrk_txpeak,"txpeak/F");
   ds_intrk->Branch("typeak",&ds_intrk_typeak,"typeak/F");
   ds_intrk->Branch("i",&ds_intrk_i,"i/I");
   ds_intrk->Branch("xc",&ds_intrk_xc,"xc/F");
   ds_intrk->Branch("yc",&ds_intrk_yc,"yc/F");
   ds_intrk->Branch("1ry_vx",&ds_intrk_1ry_vx,"1ry_vx/F");
   ds_intrk->Branch("1ry_vy",&ds_intrk_1ry_vy,"1ry_vy/F");
   ds_intrk->Branch("1ry_vz",&ds_intrk_1ry_vz,"1ry_vz/F");
   ds_intrk->Branch("1ry_plt",&ds_intrk_1ry_plt,"1ry_plt/I");
   ds_intrk->Branch("flagw",&ds_intrk_flagw,"flagw/I");
   ds_intrk->Branch("n_1ry_trk",&ds_intrk_n_1ry_trk,"n_1ry_trk/I");
   ds_intrk->Branch("2ry_vx",&ds_intrk_2ry_vx,"2ry_vx/F");
   ds_intrk->Branch("2ry_vy",&ds_intrk_2ry_vy,"2ry_vy/F");
   ds_intrk->Branch("2ry_vz",&ds_intrk_2ry_vz,"2ry_vz/F");
   ds_intrk->Branch("2ry_plt",&ds_intrk_2ry_plt,"2ry_plt/I");
   ds_intrk->Branch("parent_plt_1st",&ds_intrk_parent_plt_1st,"parent_plt_1st/I");
   ds_intrk->Branch("parent_trkID",&ds_intrk_parent_trkID,"parent_trkID/I");
   ds_intrk->Branch("parent_MCEvt",&ds_intrk_parent_MCEvt,"parent_MCEvt/I");
   ds_intrk->Branch("parent_pdgID",&ds_intrk_parent_pdgID,"parent_pdgID/I");
   ds_intrk->Branch("parent_MCp",&ds_intrk_parent_MCp,"parent_MCp/F");
   ds_intrk->Branch("nparent_1ry",&ds_intrk_nparent_1ry,"nparent_1ry/I");
   ds_intrk->Branch("nparent_1ry_penet",&ds_intrk_nparent_1ry_penet,"nparent_1ry/I");
   ds_intrk->Branch("nparent_non1ry",&ds_intrk_nparent_non1ry,"nparent_non1ry/I");
   ds_intrk->Branch("parent_tx",&ds_intrk_parent_tx,"parent_tx/F");
   ds_intrk->Branch("parent_ty",&ds_intrk_parent_ty,"parent_ty/F");
   ds_intrk->Branch("ndau",&ds_intrk_ndau_all,"ndau_all/I");
   ds_intrk->Branch("ndau_ip700",&ds_intrk_ndau_ip700,"ndau_ip700/I");
   ds_intrk->Branch("ndau_ip500",&ds_intrk_ndau_ip500,"ndau_ip500/I");

   ds_intrk->Branch("plt_dau1",&ds_intrk_plt_dau1,"plt_dau1/I");
   ds_intrk->Branch("segid_dau1",&ds_intrk_segid_dau1,"segid_dau1/I");
   ds_intrk->Branch("dau1_MCEvt",&ds_intrk_dau1_MCEvt,"dau1_MCEvt/I");
   ds_intrk->Branch("dau1_pdgID",&ds_intrk_dau1_pdgID,"dau1_pdgID/I");
   ds_intrk->Branch("dau1_MCp",&ds_intrk_dau1_MCp,"dau1_MCp/F");
   ds_intrk->Branch("ip_to1ry_dau1",&ds_intrk_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_intrk->Branch("ip_to2ry_dau1",&ds_intrk_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_intrk->Branch("tx_dau1",&ds_intrk_tx_dau1,"tx_dau1/F");
   ds_intrk->Branch("ty_dau1",&ds_intrk_ty_dau1,"ty_dau1/F");
   ds_intrk->Branch("dt_dau1",&ds_intrk_dt_dau1,"dt_dau1/F");
   ds_intrk->Branch("dtrms_dau1",&ds_intrk_dtrms_dau1,"dtrms_dau1/F");
   ds_intrk->Branch("dtrmst_dau1",&ds_intrk_dtrmst_dau1,"dtrmst_dau1/F");
   ds_intrk->Branch("dt_w_dau1",&ds_intrk_dt_w_dau1,"dt_w_dau1/F");
   ds_intrk->Branch("plt_dau2",&ds_intrk_plt_dau2,"plt_dau2/I");
   ds_intrk->Branch("segid_dau2",&ds_intrk_segid_dau2,"segid_dau2/I");
   ds_intrk->Branch("dau2_MCEvt",&ds_intrk_dau2_MCEvt,"dau2_MCEvt/I");
   ds_intrk->Branch("dau2_pdgID",&ds_intrk_dau2_pdgID,"dau2_pdgID/I");
   ds_intrk->Branch("dau2_MCp",&ds_intrk_dau2_MCp,"dau2_MCp/F");
   ds_intrk->Branch("ip_to1ry_dau2",&ds_intrk_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_intrk->Branch("ip_to2ry_dau2",&ds_intrk_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_intrk->Branch("tx_dau2",&ds_intrk_tx_dau2,"tx_dau2/F");
   ds_intrk->Branch("ty_dau2",&ds_intrk_ty_dau2,"ty_dau2/F");
   ds_intrk->Branch("dt_dau2",&ds_intrk_dt_dau2,"dt_dau2/F");
   ds_intrk->Branch("dtrms_dau2",&ds_intrk_dtrms_dau2,"dtrms_dau2/F");
   ds_intrk->Branch("dtrmst_dau2",&ds_intrk_dtrmst_dau2,"dtrmst_dau2/F");
   ds_intrk->Branch("dt_w_dau2",&ds_intrk_dt_w_dau2,"dt_w_dau2/F");
   ds_intrk->Branch("plt_dau3",&ds_intrk_plt_dau3,"plt_dau3/I");
   ds_intrk->Branch("segid_dau3",&ds_intrk_segid_dau3,"segid_dau3/I");
   ds_intrk->Branch("dau3_MCEvt",&ds_intrk_dau3_MCEvt,"dau3_MCEvt/I");
   ds_intrk->Branch("dau3_pdgID",&ds_intrk_dau3_pdgID,"dau3_pdgID/I");
   ds_intrk->Branch("dau3_MCp",&ds_intrk_dau3_MCp,"dau3_MCp/F");
   ds_intrk->Branch("ip_to1ry_dau3",&ds_intrk_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_intrk->Branch("ip_to2ry_dau3",&ds_intrk_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_intrk->Branch("tx_dau3",&ds_intrk_tx_dau3,"tx_dau3/F");
   ds_intrk->Branch("ty_dau3",&ds_intrk_ty_dau3,"ty_dau3/F");
   ds_intrk->Branch("dt_dau3",&ds_intrk_dt_dau3,"dt_dau3/F");
   ds_intrk->Branch("dtrms_dau3",&ds_intrk_dtrms_dau3,"dtrms_dau3/F");
   ds_intrk->Branch("dtrmst_dau3",&ds_intrk_dtrmst_dau3,"dtrmst_dau3/F");
   ds_intrk->Branch("dt_w_dau3",&ds_intrk_dt_w_dau3,"dt_w_dau3/F");


   TTree *ds_intrk_wt = new TTree("DsInTrkWt","DsInTrkWtinfo");

   ds_intrk_wt->Branch("area1",&ds_intrk_wt_area1,"area1/I");
   ds_intrk_wt->Branch("area2",&ds_intrk_wt_area2,"area2/I");
   ds_intrk_wt->Branch("txpeak",&ds_intrk_wt_txpeak,"txpeak/F");
   ds_intrk_wt->Branch("typeak",&ds_intrk_wt_typeak,"typeak/F");
   ds_intrk_wt->Branch("i",&ds_intrk_wt_i,"i/I");
   ds_intrk_wt->Branch("xc",&ds_intrk_wt_xc,"xc/F");
   ds_intrk_wt->Branch("yc",&ds_intrk_wt_yc,"yc/F");
   ds_intrk_wt->Branch("1ry_vx",&ds_intrk_wt_1ry_vx,"1ry_vx/F");
   ds_intrk_wt->Branch("1ry_vy",&ds_intrk_wt_1ry_vy,"1ry_vy/F");
   ds_intrk_wt->Branch("1ry_vz",&ds_intrk_wt_1ry_vz,"1ry_vz/F");
   ds_intrk_wt->Branch("1ry_plt",&ds_intrk_wt_1ry_plt,"1ry_plt/I");
   ds_intrk_wt->Branch("flagw",&ds_intrk_wt_flagw,"flagw/I");
   ds_intrk_wt->Branch("n_1ry_trk",&ds_intrk_wt_n_1ry_trk,"n_1ry_trk/I");
   ds_intrk_wt->Branch("2ry_vx",&ds_intrk_wt_2ry_vx,"2ry_vx/F");
   ds_intrk_wt->Branch("2ry_vy",&ds_intrk_wt_2ry_vy,"2ry_vy/F");
   ds_intrk_wt->Branch("2ry_vz",&ds_intrk_wt_2ry_vz,"2ry_vz/F");
   ds_intrk_wt->Branch("2ry_plt",&ds_intrk_wt_2ry_plt,"2ry_plt/I");
   ds_intrk_wt->Branch("parent_plt_1st",&ds_intrk_wt_parent_plt_1st,"parent_plt_1st/I");
   ds_intrk_wt->Branch("parent_trkID",&ds_intrk_wt_parent_trkID,"parent_trkID/I");
   ds_intrk_wt->Branch("parent_MCEvt",&ds_intrk_wt_parent_MCEvt,"parent_MCEvt/I");
   ds_intrk_wt->Branch("parent_pdgID",&ds_intrk_wt_parent_pdgID,"parent_pdgID/I");
   ds_intrk_wt->Branch("parent_MCp",&ds_intrk_wt_parent_MCp,"parent_MCp/F");
   ds_intrk_wt->Branch("nparent_1ry",&ds_intrk_wt_nparent_1ry,"nparent_1ry/I");
   ds_intrk_wt->Branch("nparent_1ry_penet",&ds_intrk_wt_nparent_1ry_penet,"nparent_1ry/I");
   ds_intrk_wt->Branch("nparent_non1ry",&ds_intrk_wt_nparent_non1ry,"nparent_non1ry/I");
   ds_intrk_wt->Branch("parent_tx",&ds_intrk_wt_parent_tx,"parent_tx/F");
   ds_intrk_wt->Branch("parent_ty",&ds_intrk_wt_parent_ty,"parent_ty/F");
   ds_intrk_wt->Branch("ndau",&ds_intrk_wt_ndau_all,"ndau_all/I");
   ds_intrk_wt->Branch("ndau_ip700",&ds_intrk_wt_ndau_ip700,"ndau_ip700/I");
   ds_intrk_wt->Branch("ndau_ip500",&ds_intrk_wt_ndau_ip500,"ndau_ip500/I");

   ds_intrk_wt->Branch("plt_dau1",&ds_intrk_wt_plt_dau1,"plt_dau1/I");
   ds_intrk_wt->Branch("segid_dau1",&ds_intrk_wt_segid_dau1,"segid_dau1/I");
   ds_intrk_wt->Branch("dau1_MCEvt",&ds_intrk_wt_dau1_MCEvt,"dau1_MCEvt/I");
   ds_intrk_wt->Branch("dau1_pdgID",&ds_intrk_wt_dau1_pdgID,"dau1_pdgID/I");
   ds_intrk_wt->Branch("dau1_MCp",&ds_intrk_wt_dau1_MCp,"dau1_MCp/F");
   ds_intrk_wt->Branch("ip_to1ry_dau1",&ds_intrk_wt_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_intrk_wt->Branch("ip_to2ry_dau1",&ds_intrk_wt_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_intrk_wt->Branch("tx_dau1",&ds_intrk_wt_tx_dau1,"tx_dau1/F");
   ds_intrk_wt->Branch("ty_dau1",&ds_intrk_wt_ty_dau1,"ty_dau1/F");
   ds_intrk_wt->Branch("dt_dau1",&ds_intrk_wt_dt_dau1,"dt_dau1/F");
   ds_intrk_wt->Branch("dtrms_dau1",&ds_intrk_wt_dtrms_dau1,"dtrms_dau1/F");
   ds_intrk_wt->Branch("dtrmst_dau1",&ds_intrk_wt_dtrmst_dau1,"dtrmst_dau1/F");
   ds_intrk_wt->Branch("dt_w_dau1",&ds_intrk_wt_dt_w_dau1,"dt_w_dau1/F");
   ds_intrk_wt->Branch("plt_dau2",&ds_intrk_wt_plt_dau2,"plt_dau2/I");
   ds_intrk_wt->Branch("segid_dau2",&ds_intrk_wt_segid_dau2,"segid_dau2/I");
   ds_intrk_wt->Branch("dau2_MCEvt",&ds_intrk_wt_dau2_MCEvt,"dau2_MCEvt/I");
   ds_intrk_wt->Branch("dau2_pdgID",&ds_intrk_wt_dau2_pdgID,"dau2_pdgID/I");
   ds_intrk_wt->Branch("dau2_MCp",&ds_intrk_wt_dau2_MCp,"dau2_MCp/F");
   ds_intrk_wt->Branch("ip_to1ry_dau2",&ds_intrk_wt_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_intrk_wt->Branch("ip_to2ry_dau2",&ds_intrk_wt_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_intrk_wt->Branch("tx_dau2",&ds_intrk_wt_tx_dau2,"tx_dau2/F");
   ds_intrk_wt->Branch("ty_dau2",&ds_intrk_wt_ty_dau2,"ty_dau2/F");
   ds_intrk_wt->Branch("dt_dau2",&ds_intrk_wt_dt_dau2,"dt_dau2/F");
   ds_intrk_wt->Branch("dtrms_dau2",&ds_intrk_wt_dtrms_dau2,"dtrms_dau2/F");
   ds_intrk_wt->Branch("dtrmst_dau2",&ds_intrk_wt_dtrmst_dau2,"dtrmst_dau2/F");
   ds_intrk_wt->Branch("dt_w_dau2",&ds_intrk_wt_dt_w_dau2,"dt_w_dau2/F");
   ds_intrk_wt->Branch("plt_dau3",&ds_intrk_wt_plt_dau3,"plt_dau3/I");
   ds_intrk_wt->Branch("segid_dau3",&ds_intrk_wt_segid_dau3,"segid_dau3/I");
   ds_intrk_wt->Branch("dau3_MCEvt",&ds_intrk_wt_dau3_MCEvt,"dau3_MCEvt/I");
   ds_intrk_wt->Branch("dau3_pdgID",&ds_intrk_wt_dau3_pdgID,"dau3_pdgID/I");
   ds_intrk_wt->Branch("dau3_MCp",&ds_intrk_wt_dau3_MCp,"dau3_MCp/F");
   ds_intrk_wt->Branch("ip_to1ry_dau3",&ds_intrk_wt_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_intrk_wt->Branch("ip_to2ry_dau3",&ds_intrk_wt_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_intrk_wt->Branch("tx_dau3",&ds_intrk_wt_tx_dau3,"tx_dau3/F");
   ds_intrk_wt->Branch("ty_dau3",&ds_intrk_wt_ty_dau3,"ty_dau3/F");
   ds_intrk_wt->Branch("dt_dau3",&ds_intrk_wt_dt_dau3,"dt_dau3/F");
   ds_intrk_wt->Branch("dtrms_dau3",&ds_intrk_wt_dtrms_dau3,"dtrms_dau3/F");
   ds_intrk_wt->Branch("dtrmst_dau3",&ds_intrk_wt_dtrmst_dau3,"dtrmst_dau3/F");
   ds_intrk_wt->Branch("dt_w_dau3",&ds_intrk_wt_dt_w_dau3,"dt_w_dau3/F"); 


   TTree *ds_intrk_for_pa = new TTree("DsInTrkForPa","DsInTrkForPainfo");

   ds_intrk_for_pa->Branch("area1",&ds_intrk_for_pa_area1,"area1/I");
   ds_intrk_for_pa->Branch("area2",&ds_intrk_for_pa_area2,"area2/I");
   ds_intrk_for_pa->Branch("txpeak",&ds_intrk_for_pa_txpeak,"txpeak/F");
   ds_intrk_for_pa->Branch("typeak",&ds_intrk_for_pa_typeak,"typeak/F");
   ds_intrk_for_pa->Branch("i",&ds_intrk_for_pa_i,"i/I");
   ds_intrk_for_pa->Branch("xc",&ds_intrk_for_pa_xc,"xc/F");
   ds_intrk_for_pa->Branch("yc",&ds_intrk_for_pa_yc,"yc/F");
   ds_intrk_for_pa->Branch("1ry_vx",&ds_intrk_for_pa_1ry_vx,"1ry_vx/F");
   ds_intrk_for_pa->Branch("1ry_vy",&ds_intrk_for_pa_1ry_vy,"1ry_vy/F");
   ds_intrk_for_pa->Branch("1ry_vz",&ds_intrk_for_pa_1ry_vz,"1ry_vz/F");
   ds_intrk_for_pa->Branch("1ry_plt",&ds_intrk_for_pa_1ry_plt,"1ry_plt/I");
   ds_intrk_for_pa->Branch("flagw",&ds_intrk_for_pa_flagw,"flagw/I");
   ds_intrk_for_pa->Branch("n_1ry_trk",&ds_intrk_for_pa_n_1ry_trk,"n_1ry_trk/I");
   ds_intrk_for_pa->Branch("2ry_vx",&ds_intrk_for_pa_2ry_vx,"2ry_vx/F");
   ds_intrk_for_pa->Branch("2ry_vy",&ds_intrk_for_pa_2ry_vy,"2ry_vy/F");
   ds_intrk_for_pa->Branch("2ry_vz",&ds_intrk_for_pa_2ry_vz,"2ry_vz/F");
   ds_intrk_for_pa->Branch("2ry_plt",&ds_intrk_for_pa_2ry_plt,"2ry_plt/I");
   ds_intrk_for_pa->Branch("parent_plt_1st",&ds_intrk_for_pa_parent_plt_1st,"parent_plt_1st/I");
   ds_intrk_for_pa->Branch("parent_trkID",&ds_intrk_for_pa_parent_trkID,"parent_trkID/I");
   ds_intrk_for_pa->Branch("parent_MCEvt",&ds_intrk_for_pa_parent_MCEvt,"parent_MCEvt/I");
   ds_intrk_for_pa->Branch("parent_pdgID",&ds_intrk_for_pa_parent_pdgID,"parent_pdgID/I");
   ds_intrk_for_pa->Branch("parent_MCp",&ds_intrk_for_pa_parent_MCp,"parent_MCp/F");
   ds_intrk_for_pa->Branch("nparent_1ry",&ds_intrk_for_pa_nparent_1ry,"nparent_1ry/I");
   ds_intrk_for_pa->Branch("nparent_1ry_penet",&ds_intrk_for_pa_nparent_1ry_penet,"nparent_1ry/I");
   ds_intrk_for_pa->Branch("nparent_non1ry",&ds_intrk_for_pa_nparent_non1ry,"nparent_non1ry/I");
   ds_intrk_for_pa->Branch("parent_tx",&ds_intrk_for_pa_parent_tx,"parent_tx/F");
   ds_intrk_for_pa->Branch("parent_ty",&ds_intrk_for_pa_parent_ty,"parent_ty/F");
   ds_intrk_for_pa->Branch("ndau",&ds_intrk_for_pa_ndau_all,"ndau_all/I");
   ds_intrk_for_pa->Branch("ndau_ip700",&ds_intrk_for_pa_ndau_ip700,"ndau_ip700/I");
   ds_intrk_for_pa->Branch("ndau_ip500",&ds_intrk_for_pa_ndau_ip500,"ndau_ip500/I");

   ds_intrk_for_pa->Branch("plt_dau1",&ds_intrk_for_pa_plt_dau1,"plt_dau1/I");
   ds_intrk_for_pa->Branch("segid_dau1",&ds_intrk_for_pa_segid_dau1,"segid_dau1/I");
   ds_intrk_for_pa->Branch("dau1_MCEvt",&ds_intrk_for_pa_dau1_MCEvt,"dau1_MCEvt/I");
   ds_intrk_for_pa->Branch("dau1_pdgID",&ds_intrk_for_pa_dau1_pdgID,"dau1_pdgID/I");
   ds_intrk_for_pa->Branch("dau1_MCp",&ds_intrk_for_pa_dau1_MCp,"dau1_MCp/F");
   ds_intrk_for_pa->Branch("ip_to1ry_dau1",&ds_intrk_for_pa_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_intrk_for_pa->Branch("ip_to2ry_dau1",&ds_intrk_for_pa_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_intrk_for_pa->Branch("tx_dau1",&ds_intrk_for_pa_tx_dau1,"tx_dau1/F");
   ds_intrk_for_pa->Branch("ty_dau1",&ds_intrk_for_pa_ty_dau1,"ty_dau1/F");
   ds_intrk_for_pa->Branch("dt_dau1",&ds_intrk_for_pa_dt_dau1,"dt_dau1/F");
   ds_intrk_for_pa->Branch("dtrms_dau1",&ds_intrk_for_pa_dtrms_dau1,"dtrms_dau1/F");
   ds_intrk_for_pa->Branch("dtrmst_dau1",&ds_intrk_for_pa_dtrmst_dau1,"dtrmst_dau1/F");
   ds_intrk_for_pa->Branch("dt_w_dau1",&ds_intrk_for_pa_dt_w_dau1,"dt_w_dau1/F");
   ds_intrk_for_pa->Branch("plt_dau2",&ds_intrk_for_pa_plt_dau2,"plt_dau2/I");
   ds_intrk_for_pa->Branch("segid_dau2",&ds_intrk_for_pa_segid_dau2,"segid_dau2/I");
   ds_intrk_for_pa->Branch("dau2_MCEvt",&ds_intrk_for_pa_dau2_MCEvt,"dau2_MCEvt/I");
   ds_intrk_for_pa->Branch("dau2_pdgID",&ds_intrk_for_pa_dau2_pdgID,"dau2_pdgID/I");
   ds_intrk_for_pa->Branch("dau2_MCp",&ds_intrk_for_pa_dau2_MCp,"dau2_MCp/F");
   ds_intrk_for_pa->Branch("ip_to1ry_dau2",&ds_intrk_for_pa_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_intrk_for_pa->Branch("ip_to2ry_dau2",&ds_intrk_for_pa_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_intrk_for_pa->Branch("tx_dau2",&ds_intrk_for_pa_tx_dau2,"tx_dau2/F");
   ds_intrk_for_pa->Branch("ty_dau2",&ds_intrk_for_pa_ty_dau2,"ty_dau2/F");
   ds_intrk_for_pa->Branch("dt_dau2",&ds_intrk_for_pa_dt_dau2,"dt_dau2/F");
   ds_intrk_for_pa->Branch("dtrms_dau2",&ds_intrk_for_pa_dtrms_dau2,"dtrms_dau2/F");
   ds_intrk_for_pa->Branch("dtrmst_dau2",&ds_intrk_for_pa_dtrmst_dau2,"dtrmst_dau2/F");
   ds_intrk_for_pa->Branch("dt_w_dau2",&ds_intrk_for_pa_dt_w_dau2,"dt_w_dau2/F");
   ds_intrk_for_pa->Branch("plt_dau3",&ds_intrk_for_pa_plt_dau3,"plt_dau3/I");
   ds_intrk_for_pa->Branch("segid_dau3",&ds_intrk_for_pa_segid_dau3,"segid_dau3/I");
   ds_intrk_for_pa->Branch("dau3_MCEvt",&ds_intrk_for_pa_dau3_MCEvt,"dau3_MCEvt/I");
   ds_intrk_for_pa->Branch("dau3_pdgID",&ds_intrk_for_pa_dau3_pdgID,"dau3_pdgID/I");
   ds_intrk_for_pa->Branch("dau3_MCp",&ds_intrk_for_pa_dau3_MCp,"dau3_MCp/F");
   ds_intrk_for_pa->Branch("ip_to1ry_dau3",&ds_intrk_for_pa_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_intrk_for_pa->Branch("ip_to2ry_dau3",&ds_intrk_for_pa_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_intrk_for_pa->Branch("tx_dau3",&ds_intrk_for_pa_tx_dau3,"tx_dau3/F");
   ds_intrk_for_pa->Branch("ty_dau3",&ds_intrk_for_pa_ty_dau3,"ty_dau3/F");
   ds_intrk_for_pa->Branch("dt_dau3",&ds_intrk_for_pa_dt_dau3,"dt_dau3/F");
   ds_intrk_for_pa->Branch("dtrms_dau3",&ds_intrk_for_pa_dtrms_dau3,"dtrms_dau3/F");
   ds_intrk_for_pa->Branch("dtrmst_dau3",&ds_intrk_for_pa_dtrmst_dau3,"dtrmst_dau3/F");
   ds_intrk_for_pa->Branch("dt_w_dau3",&ds_intrk_for_pa_dt_w_dau3,"dt_w_dau3/F");


   TTree *ds_intrk_for_pa_wt = new TTree("DsInTrkForPaWt","DsInTrkForPaWtinfo");

   ds_intrk_for_pa_wt->Branch("area1",&ds_intrk_for_pa_wt_area1,"area1/I");
   ds_intrk_for_pa_wt->Branch("area2",&ds_intrk_for_pa_wt_area2,"area2/I");
   ds_intrk_for_pa_wt->Branch("txpeak",&ds_intrk_for_pa_wt_txpeak,"txpeak/F");
   ds_intrk_for_pa_wt->Branch("typeak",&ds_intrk_for_pa_wt_typeak,"typeak/F");
   ds_intrk_for_pa_wt->Branch("i",&ds_intrk_for_pa_wt_i,"i/I");
   ds_intrk_for_pa_wt->Branch("xc",&ds_intrk_for_pa_wt_xc,"xc/F");
   ds_intrk_for_pa_wt->Branch("yc",&ds_intrk_for_pa_wt_yc,"yc/F");
   ds_intrk_for_pa_wt->Branch("1ry_vx",&ds_intrk_for_pa_wt_1ry_vx,"1ry_vx/F");
   ds_intrk_for_pa_wt->Branch("1ry_vy",&ds_intrk_for_pa_wt_1ry_vy,"1ry_vy/F");
   ds_intrk_for_pa_wt->Branch("1ry_vz",&ds_intrk_for_pa_wt_1ry_vz,"1ry_vz/F");
   ds_intrk_for_pa_wt->Branch("1ry_plt",&ds_intrk_for_pa_wt_1ry_plt,"1ry_plt/I");
   ds_intrk_for_pa_wt->Branch("flagw",&ds_intrk_for_pa_wt_flagw,"flagw/I");
   ds_intrk_for_pa_wt->Branch("n_1ry_trk",&ds_intrk_for_pa_wt_n_1ry_trk,"n_1ry_trk/I");
   ds_intrk_for_pa_wt->Branch("2ry_vx",&ds_intrk_for_pa_wt_2ry_vx,"2ry_vx/F");
   ds_intrk_for_pa_wt->Branch("2ry_vy",&ds_intrk_for_pa_wt_2ry_vy,"2ry_vy/F");
   ds_intrk_for_pa_wt->Branch("2ry_vz",&ds_intrk_for_pa_wt_2ry_vz,"2ry_vz/F");
   ds_intrk_for_pa_wt->Branch("2ry_plt",&ds_intrk_for_pa_wt_2ry_plt,"2ry_plt/I");
   ds_intrk_for_pa_wt->Branch("parent_plt_1st",&ds_intrk_for_pa_wt_parent_plt_1st,"parent_plt_1st/I");
   ds_intrk_for_pa_wt->Branch("parent_trkID",&ds_intrk_for_pa_wt_parent_trkID,"parent_trkID/I");
   ds_intrk_for_pa_wt->Branch("parent_MCEvt",&ds_intrk_for_pa_wt_parent_MCEvt,"parent_MCEvt/I");
   ds_intrk_for_pa_wt->Branch("parent_pdgID",&ds_intrk_for_pa_wt_parent_pdgID,"parent_pdgID/I");
   ds_intrk_for_pa_wt->Branch("parent_MCp",&ds_intrk_for_pa_wt_parent_MCp,"parent_MCp/F");
   ds_intrk_for_pa_wt->Branch("nparent_1ry",&ds_intrk_for_pa_wt_nparent_1ry,"nparent_1ry/I");
   ds_intrk_for_pa_wt->Branch("nparent_1ry_penet",&ds_intrk_for_pa_wt_nparent_1ry_penet,"nparent_1ry/I");
   ds_intrk_for_pa_wt->Branch("nparent_non1ry",&ds_intrk_for_pa_wt_nparent_non1ry,"nparent_non1ry/I");
   ds_intrk_for_pa_wt->Branch("parent_tx",&ds_intrk_for_pa_wt_parent_tx,"parent_tx/F");
   ds_intrk_for_pa_wt->Branch("parent_ty",&ds_intrk_for_pa_wt_parent_ty,"parent_ty/F");
   ds_intrk_for_pa_wt->Branch("ndau",&ds_intrk_for_pa_wt_ndau_all,"ndau_all/I");
   ds_intrk_for_pa_wt->Branch("ndau_ip700",&ds_intrk_for_pa_wt_ndau_ip700,"ndau_ip700/I");
   ds_intrk_for_pa_wt->Branch("ndau_ip500",&ds_intrk_for_pa_wt_ndau_ip500,"ndau_ip500/I");

   ds_intrk_for_pa_wt->Branch("plt_dau1",&ds_intrk_for_pa_wt_plt_dau1,"plt_dau1/I");
   ds_intrk_for_pa_wt->Branch("segid_dau1",&ds_intrk_for_pa_wt_segid_dau1,"segid_dau1/I");
   ds_intrk_for_pa_wt->Branch("dau1_MCEvt",&ds_intrk_for_pa_wt_dau1_MCEvt,"dau1_MCEvt/I");
   ds_intrk_for_pa_wt->Branch("dau1_pdgID",&ds_intrk_for_pa_wt_dau1_pdgID,"dau1_pdgID/I");
   ds_intrk_for_pa_wt->Branch("dau1_MCp",&ds_intrk_for_pa_wt_dau1_MCp,"dau1_MCp/F");
   ds_intrk_for_pa_wt->Branch("ip_to1ry_dau1",&ds_intrk_for_pa_wt_ip_to1ry_dau1,"ip_to1ry_dau1/F");
   ds_intrk_for_pa_wt->Branch("ip_to2ry_dau1",&ds_intrk_for_pa_wt_ip_to2ry_dau1,"ip_to2ry_dau1/F");
   ds_intrk_for_pa_wt->Branch("tx_dau1",&ds_intrk_for_pa_wt_tx_dau1,"tx_dau1/F");
   ds_intrk_for_pa_wt->Branch("ty_dau1",&ds_intrk_for_pa_wt_ty_dau1,"ty_dau1/F");
   ds_intrk_for_pa_wt->Branch("dt_dau1",&ds_intrk_for_pa_wt_dt_dau1,"dt_dau1/F");
   ds_intrk_for_pa_wt->Branch("dtrms_dau1",&ds_intrk_for_pa_wt_dtrms_dau1,"dtrms_dau1/F");
   ds_intrk_for_pa_wt->Branch("dtrmst_dau1",&ds_intrk_for_pa_wt_dtrmst_dau1,"dtrmst_dau1/F");
   ds_intrk_for_pa_wt->Branch("dt_w_dau1",&ds_intrk_for_pa_wt_dt_w_dau1,"dt_w_dau1/F");
   ds_intrk_for_pa_wt->Branch("plt_dau2",&ds_intrk_for_pa_wt_plt_dau2,"plt_dau2/I");
   ds_intrk_for_pa_wt->Branch("segid_dau2",&ds_intrk_for_pa_wt_segid_dau2,"segid_dau2/I");
   ds_intrk_for_pa_wt->Branch("dau2_MCEvt",&ds_intrk_for_pa_wt_dau2_MCEvt,"dau2_MCEvt/I");
   ds_intrk_for_pa_wt->Branch("dau2_pdgID",&ds_intrk_for_pa_wt_dau2_pdgID,"dau2_pdgID/I");
   ds_intrk_for_pa_wt->Branch("dau2_MCp",&ds_intrk_for_pa_wt_dau2_MCp,"dau2_MCp/F");
   ds_intrk_for_pa_wt->Branch("ip_to1ry_dau2",&ds_intrk_for_pa_wt_ip_to1ry_dau2,"ip_to1ry_dau2/F");
   ds_intrk_for_pa_wt->Branch("ip_to2ry_dau2",&ds_intrk_for_pa_wt_ip_to2ry_dau2,"ip_to2ry_dau2/F");
   ds_intrk_for_pa_wt->Branch("tx_dau2",&ds_intrk_for_pa_wt_tx_dau2,"tx_dau2/F");
   ds_intrk_for_pa_wt->Branch("ty_dau2",&ds_intrk_for_pa_wt_ty_dau2,"ty_dau2/F");
   ds_intrk_for_pa_wt->Branch("dt_dau2",&ds_intrk_for_pa_wt_dt_dau2,"dt_dau2/F");
   ds_intrk_for_pa_wt->Branch("dtrms_dau2",&ds_intrk_for_pa_wt_dtrms_dau2,"dtrms_dau2/F");
   ds_intrk_for_pa_wt->Branch("dtrmst_dau2",&ds_intrk_for_pa_wt_dtrmst_dau2,"dtrmst_dau2/F");
   ds_intrk_for_pa_wt->Branch("dt_w_dau2",&ds_intrk_for_pa_wt_dt_w_dau2,"dt_w_dau2/F");
   ds_intrk_for_pa_wt->Branch("plt_dau3",&ds_intrk_for_pa_wt_plt_dau3,"plt_dau3/I");
   ds_intrk_for_pa_wt->Branch("segid_dau3",&ds_intrk_for_pa_wt_segid_dau3,"segid_dau3/I");
   ds_intrk_for_pa_wt->Branch("dau3_MCEvt",&ds_intrk_for_pa_wt_dau3_MCEvt,"dau3_MCEvt/I");
   ds_intrk_for_pa_wt->Branch("dau3_pdgID",&ds_intrk_for_pa_wt_dau3_pdgID,"dau3_pdgID/I");
   ds_intrk_for_pa_wt->Branch("dau3_MCp",&ds_intrk_for_pa_wt_dau3_MCp,"dau3_MCp/F");
   ds_intrk_for_pa_wt->Branch("ip_to1ry_dau3",&ds_intrk_for_pa_wt_ip_to1ry_dau3,"ip_to1ry_dau3/F");
   ds_intrk_for_pa_wt->Branch("ip_to2ry_dau3",&ds_intrk_for_pa_wt_ip_to2ry_dau3,"ip_to2ry_dau3/F");
   ds_intrk_for_pa_wt->Branch("tx_dau3",&ds_intrk_for_pa_wt_tx_dau3,"tx_dau3/F");
   ds_intrk_for_pa_wt->Branch("ty_dau3",&ds_intrk_for_pa_wt_ty_dau3,"ty_dau3/F");
   ds_intrk_for_pa_wt->Branch("dt_dau3",&ds_intrk_for_pa_wt_dt_dau3,"dt_dau3/F");
   ds_intrk_for_pa_wt->Branch("dtrms_dau3",&ds_intrk_for_pa_wt_dtrms_dau3,"dtrms_dau3/F");
   ds_intrk_for_pa_wt->Branch("dtrmst_dau3",&ds_intrk_for_pa_wt_dtrmst_dau3,"dtrmst_dau3/F");
   ds_intrk_for_pa_wt->Branch("dt_w_dau3",&ds_intrk_for_pa_wt_dt_w_dau3,"dt_w_dau3/F");               


   int VtxId = -1, chldNum = 0;
   char line[1024];

   int vNum = 0, pNum = 0, tNum = 0, recNum = 0, notRecNum = 0;

   int prevSubAreaPar = 1, prevSubAreaTrk = 1, recoNum = 1;
   
   for (int segNum = 0; segNum <= 1; segNum++)
   {
      int parid = 0;

      unordered_map<int, int> trkIDMap;
      vector<int> paridVec;

      vector<tuple<int, int, int, int, int, int, int>> USPair [63], DSPair [63];
      //vector<pair<int, int>> USPair, DSPair;
      //set<pair<int, int>> USPair, DSPair;

      vector<int> UStrID[63], USgtrID[63];
      vector<int> DStrID[63], DSgtrID[63];
      vector<int> intVec[63];
      vector<int> UStrIDOut[63];

      int pInAcc = 0, pOutAcc = 0;

      for (int areaInd = 0; areaInd < 63; areaInd++)
      {
         if (isInAcceptance(areaInd+1))
         {
            const int USStrLength = inputUS.length();
            const int DSStrLength = inputDS.length();

            char* USChr = new char[USStrLength + 1];
            char* DSChr = new char[DSStrLength + 1];

            strcpy(USChr, inputUS.c_str());
            strcpy(DSChr, inputDS.c_str());

            char USIn[128], DSIn[128];

            snprintf(USIn, 128, "../../PD05/Linked/PD05_FullArea_Links_3Sigma/Area_%02d/Output/Merged/%s", areaInd+1, USChr);
            snprintf(DSIn, 128, "../../PD05/Linked/PD05_FullArea_Links_3Sigma/Area_%02d/Output/Merged/%s", areaInd+1, DSChr);

            cout << USIn << endl;

            USPair[areaInd] = ReadFile(USIn, segNum);
            DSPair[areaInd] = ReadFile(DSIn, segNum);
            
            sort(USPair[areaInd].begin(), USPair[areaInd].end());
            sort(DSPair[areaInd].begin(), DSPair[areaInd].end());
            
            USPair[areaInd].erase(unique(USPair[areaInd].begin(), USPair[areaInd].end(), firstEqual), USPair[areaInd].end());
            DSPair[areaInd].erase(unique(DSPair[areaInd].begin(), DSPair[areaInd].end(), firstEqual), DSPair[areaInd].end());

            for (int i = 0; i < USPair[areaInd].size(); i++)
            {
               int trid = get<0>(USPair[areaInd][i]);
               int gtrid = get<1>(USPair[areaInd][i]);
               int posX = get<2>(USPair[areaInd][i]);
               int posY = get<3>(USPair[areaInd][i]);
               int posZ = get<4>(USPair[areaInd][i]);

               float tX = ((float)get<5>(USPair[areaInd][i])/1000000);
               float tY = ((float)get<6>(USPair[areaInd][i])/1000000);

               if (!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY) /*&& isInSubArea(areaInd+1, posX, posY)*/)
               {
                  UStrID[areaInd].push_back(trid);
                  USgtrID[areaInd].push_back(gtrid);

                  ptrk_US_area1 = areaInd+1;
                  ptrk_US_trID = trid;
                  ptrk_US_gtrID = gtrid;
                  ptrk_US_plt_of_1seg = segNum+1;
                  ptrk_US_PosX_of_1seg = posX;
                  ptrk_US_PosY_of_1seg = posY;
                  ptrk_US_PosZ_of_1seg = posZ;
                  ptrk_US_TX = tX;
                  ptrk_US_TY = tY;

                  us_ptrk->Fill();

                  pInAcc++;
               }
               else
               {
                  UStrIDOut[areaInd].push_back(trid);
                  pOutAcc++;
               }
            }

            for (int i = 0; i < DSPair[areaInd].size(); i++)
            {
               int trid = get<0>(DSPair[areaInd][i]);
               int gtrid = get<1>(DSPair[areaInd][i]);
               int posX = get<2>(DSPair[areaInd][i]);
               int posY = get<3>(DSPair[areaInd][i]);
               int posZ = get<4>(DSPair[areaInd][i]);

               float tX = ((float)get<5>(DSPair[areaInd][i])/1000000);
               float tY = ((float)get<6>(DSPair[areaInd][i])/1000000);

               //cout << areaInd+1 << ", " << posX << ", " << posY << endl;

               if (!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY) /*&& isInSubArea(areaInd+1, posX, posY)*/)
               {
                  DStrID[areaInd].push_back(trid);
                  DSgtrID[areaInd].push_back(gtrid);

                  ptrk_DS_area1 = areaInd+1;
                  ptrk_DS_trID = trid;
                  ptrk_DS_gtrID = gtrid;
                  ptrk_DS_plt_of_1seg = segNum+1;
                  ptrk_DS_PosX_of_1seg = posX;
                  ptrk_DS_PosY_of_1seg = posY;
                  ptrk_DS_PosZ_of_1seg = posZ;
                  ptrk_DS_TX = tX;
                  ptrk_DS_TY = tY;

                  ds_ptrk->Fill();
               }
            }

            intVec[areaInd].assign(UStrID[areaInd].begin(), UStrID[areaInd].end());

            for (int i = 0; i < DStrID[areaInd].size(); i++)
            {
               auto it = find(intVec[areaInd].begin(), intVec[areaInd].end(), DStrID[areaInd][i]);
               if (it != intVec[areaInd].end())
               {
                  intVec[areaInd].erase(it);
               }
            }

            cout << "Area " << areaInd+1 << " - Done" << endl;
         }
      }

      int pTot = pInAcc + pOutAcc;

      out << "Sub-volume: " << dirIndex << ", InitSeg: " << segNum << endl;
      out << "Number of Protons Inside Acceptance: " << pInAcc << " - Ratio: " << (float)pInAcc/pTot << ", Number of Protons Outside Acceptance: " << pOutAcc << " - Ratio: " << (float)pOutAcc/pTot << endl;

      while (fgets(line,1024,fp)) 
      {
         sscanf(&line[0],"%s ",type);
         if(strcmp(type,"1ry_vtx") == 0)
         {
            sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %d %d %f",&vtx_area1,&vtx_area2,&vtx_txpeak,&vtx_typeak,&vtx_i,&vtx_vx,&vtx_vy,&vtx_vz,&vtx_n_1ry_pl,&vtx_flagw,&vtx_multip,
               &vtx_n_1ry_parent_cut0,&vtx_n_1ry_parent_dmin_cut,&vtx_n_1ry_parent_dmin_cut_dt_cut,&vtx_dt);

            chldNum = 0;
            
            if (vtx_n_1ry_parent_dmin_cut > 0 && isInAcceptance(vtx_area1))
            {
               parC_id = parid;

               vtx_int_type = 0;
               par_flagp = 0;
               glob_parid = 0;

               for(int x = 0; x < paridVec.size(); x++)
               {
                  auto it = find(UStrID[parC_area1-1].begin(), UStrID[parC_area1-1].end(), paridVec[x]);
                  if (it != UStrID[parC_area1-1].end())
                  {
                     int index = it - UStrID[parC_area1-1].begin();
                     parC_id = paridVec[x];
                     
                     vtx_int_type = 1;
                     par_flagp = 1;

                     glob_parid = USgtrID[parC_area1-1][index];
                  }

                  it = find(intVec[parC_area1-1].begin(), intVec[parC_area1-1].end(), paridVec[x]);
                  if (it != intVec[parC_area1-1].end())
                  {
                     int index = it - UStrID[parC_area1-1].end();

                     vtx_int_type = 2;
                  }

                  /*
                  it = find(UStrIDOut[parC_area1-1].begin(), UStrIDOut[parC_area1-1].end(), paridVec[x]);
                  if (it != UStrIDOut[parC_area1-1].end())
                  {
                     if(isInSubArea(parC_area1-1, vtx_vx, vtx_vy))
                     {
                        //cout << paridVec[x] << endl;
                     }
                     else
                     {
                        //cout << paridVec[x] << endl;
                     }
                  }
                  */
               }

               VtxId++;
               vtx_vID = VtxId;

               vtx_n_1ry_trk = vtx_multip;
               trk_n_1ry_trk = vtx_multip;
               parC_n_1ry_trk = vtx_multip;

               vtx_int_medium = -1;

               if(area<vtx_area1)
               {
                  area=vtx_area1;
                  limits(vtx_area1,plt);

                  //center of subarea
                  currentRow = 5000 + (area-1)%TotalColumns * 15000;
                  currentColumn = 5000 + (area-1)/TotalColumns * 15000;

                  //main limits of subarea
                  Xmin=currentRow-7500;
                  Xmax=currentRow+7500;
                  Ymin=currentColumn-7500;
                  Ymax=currentColumn+7500;
               }

               if(area==vtx_area1) //all are 0 in MC
               {
                  float tempVZ = vtx_vz;

                  //Tungsten
                  for(int j=1; j<=1 && vtx_int_medium == -1; j++)
                  {
                     if(tempVZ>tl[j] && tempVZ<=tr[j])
                     {
                        mean_thickness = mtr[j]-mtl[j]; //cout<<mean_thickness<<" tungsten "<<endl;
                        scanned_thickness = tr[j]-tl[j];
                        vertex_correction = tempVZ-tl[j];

                        float newZ = mtl[j] + mean_thickness * vertex_correction / scanned_thickness;

                        h_align->Fill(newZ);
                        vtx_vz = newZ;

                        //cout << "Tungsten: " << mtl[j] + mean_thickness * vertex_correction / scanned_thickness << endl;

                        vtx_int_medium = 1;
                     }
                  }

                  //Emulsion
                  for(int j=0; j<=19 && vtx_int_medium == -1; j++)
                  {
                     if(tempVZ>el[j] && tempVZ<=er[j])
                     {
                        mean_thickness = mer[j]-mel[j]; //cout<<mean_thickness<<" emulsion "<<endl;
                        scanned_thickness = er[j]-el[j];
                        vertex_correction = tempVZ-el[j];

                        float newZ = mel[j] + mean_thickness * vertex_correction / scanned_thickness;

                        h_align->Fill(newZ);
                        vtx_vz = newZ;

                        //cout << "Emulsion: " << mel[j] + mean_thickness * vertex_correction / scanned_thickness << endl;

                        vtx_int_medium = 2;
                     }
                  }

                  //Plastic
                  for(int j=0; j<=19 && vtx_int_medium == -1; j++)
                  {
                     if(tempVZ>pl[j] && tempVZ<=pr[j])
                     {
                        mean_thickness = mpr[j]-mpl[j]; //cout<<mean_thickness<<" plastic "<<endl;
                        scanned_thickness = pr[j]-pl[j];
                        vertex_correction = tempVZ-pl[j];

                        float newZ = mpl[j] + mean_thickness * vertex_correction / scanned_thickness;

                        h_align->Fill(newZ);
                        vtx_vz = newZ;

                        //cout << "Plastic: " << mpl[j] + mean_thickness * vertex_correction / scanned_thickness << endl;

                        vtx_int_medium = 3;
                     }
                  }
               }

               pNum++;
               vNum++;

               par->Fill();
               vtx->Fill();
            }

            paridVec.clear();
         }
         else if (strcmp(type,"parent_cand") == 0)
         {
            sscanf(&line[11],"%d %d %f %f %d %f %f %f %f %d %d %d %f %f %d %s %f %s %f %s %d %s %f %s %f %d %d %d %d",&parC_area1,&parC_area2,&parC_txpeak,&parC_typeak,&parC_i,&parC_vx,&parC_vy,&parC_vz,&parC_dz,
               &parid,&parC_plt_of_1seg,&parC_seg_id_of_1seg,&parC_tx05pos,&parC_ty05pos,&parC_nseg,&ipChar05[8],&parC_ip_pos05,&ipChar04[8],&parC_ip_pos04,&ntrk_smallChar[10],&parC_ntrk_small,&dtChar[2],&parC_dt,
               &dt_posChar[6],&parC_dt_pos,&parC_pl_up1ry_plmin,&parC_pl_up1ry_plmax,&parC_pl_dwn1ry_plmin,&parC_pl_dwn1ry_plmax);

            /*
            if (trk_n_1ry_parent_dmin_cut == 1)
            {
               trk_vID = VtxId+1;
               parCand->Fill();
               cout << trk_vID << "-> ParCand: " << trk_id << endl;
            }
            */
            if(parC_pl_up1ry_plmin == dirIndex*10+segNum+1 && isInAcceptance(parC_area1)){paridVec.push_back(parid);}
         }
         else if(strcmp(type,"1ry_trk") == 0)
         {
            sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %f %d %d %d %f %f %f %f %d %f %f %f %f",&trk_area1,&trk_area2,&trk_txpeak,&trk_typeak,&trk_i,&trk_vx,&trk_vy,&trk_vz,&trk_flagw,&trk_multip,
               &trk_n_1ry_parent_cut0,&trk_n_1ry_parent_dmin_cut,&trk_dz,&trk_id,&trk_plt_of_1seg,&trk_seg_id_of_1seg,&trk_seg_x,&trk_seg_y,&trk_tx,&trk_ty,&trk_nseg,&trk_ip_to_1ry_using_1stseg,
               &trk_ip_to_1ry_using_2ndseg,&trk_ph_mean,&trk_dtrms1_trk);
            
            if (trk_n_1ry_parent_dmin_cut > 0 && isInAcceptance(trk_area1))
            {
               if (/*parC_id != trk_id*/ true)
               {
                  chldNum++;
                  trk_vID = VtxId;
                  parC_vID = VtxId;

                  tNum++;
                  if (chldNum == vtx_multip)
                  {
                     notRecNum++;
                     //cout << "Parent TrkId (Parent not reconstructed): " << parC_id << endl;
                  }

                  trk_int_medium = vtx_int_medium;
                  if (trk_int_medium != -1)
                  {
                     trk_vz = vtx_vz;
                  }
                  trk->Fill();
               }
               else
               {
                  recNum++;
                  //cout << "Parent TrkId: " << parC_id << endl;
               }
            }
         }

         else if(strcmp(type,"ds_all") == 0)
         {
            sscanf(&line[8], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d ",
            &ds_all_area1,&ds_all_area2,&ds_all_txpeak,&ds_all_typeak,&ds_all_i,&ds_all_xc,&ds_all_yc,&ds_all_1ry_vx,&ds_all_1ry_vy,&ds_all_1ry_vz,
            &ds_all_1ry_plt,&ds_all_flagw,&ds_all_n_1ry_trk,&ds_all_2ry_vx,&ds_all_2ry_vy,&ds_all_2ry_vz,&ds_all_2ry_plt,&ds_all_parent_plt_1st,
            &ds_all_parent_trkID,&ds_all_parent_MCEvt,&ds_all_parent_pdgID,&ds_all_parent_MCp,&ds_all_nparent_1ry,&ds_all_nparent_1ry_penet,
            &ds_all_nparent_non1ry,&ds_all_parent_tx,&ds_all_parent_ty,&ds_all_ndau,&ds_all_default1,&ds_all_default2,
            &ds_all_plt_dau1,&ds_all_segid_dau1,&ds_all_dau1_MCEvt,&ds_all_dau1_pdgID,&ds_all_dau1_MCp,&ds_all_ip_to1ry_dau1,&ds_all_ip_to2ry_dau1,&ds_all_tx_dau1,&ds_all_ty_dau1,&ds_all_dt_dau1,&ds_all_dtrms_dau1,&ds_all_dtrmst_dau1,&ds_all_dt_w_dau1,
            &ds_all_plt_dau2,&ds_all_segid_dau2,&ds_all_dau2_MCEvt,&ds_all_dau2_pdgID,&ds_all_dau2_MCp,&ds_all_ip_to1ry_dau2,&ds_all_ip_to2ry_dau2,&ds_all_tx_dau2,&ds_all_ty_dau2,&ds_all_dt_dau2,&ds_all_dtrms_dau2,&ds_all_dtrmst_dau2,&ds_all_dt_w_dau2,
            &ds_all_plt_dau3,&ds_all_segid_dau3,&ds_all_dau3_MCEvt,&ds_all_dau3_pdgID,&ds_all_dau3_MCp,&ds_all_ip_to1ry_dau3,&ds_all_ip_to2ry_dau3,&ds_all_tx_dau3,&ds_all_ty_dau3,&ds_all_dt_dau3,&ds_all_dtrms_dau3,&ds_all_dtrmst_dau3,&ds_all_dt_w_dau3,
            &ds_all_plt_dau4,&ds_all_segid_dau4,&ds_all_dau4_MCEvt,&ds_all_dau4_pdgID,&ds_all_dau4_MCp,&ds_all_ip_to1ry_dau4,&ds_all_ip_to2ry_dau4,&ds_all_tx_dau4,&ds_all_ty_dau4,&ds_all_dt_dau4,&ds_all_dtrms_dau4,&ds_all_dtrmst_dau4,&ds_all_dt_w_dau4,
            &ds_all_dmin_org_vee,&ds_all_dmin_fine_vee,&ds_all_topen_vee,&ds_all_dt1dt2_vee,&ds_all_dt012_vee,&ds_all_ntrk_around_2ry,&ds_all_ntrk_other_vtx_max,&ds_all_flag_final);

            ds_all_area1 = vtx_area1;
            ds_all_vtx_id = -1;

            auto it = trkIDMap.find(ds_all_parent_trkID);
            if (it != trkIDMap.end()) 
            {
               ds_all_vtx_id = it->second;
            }
            ds_all->Fill();
         }

         else if(strcmp(type,"ds_final") == 0)
         {
            sscanf(&line[8], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d ",
            &ds_final_area1,&ds_final_area2,&ds_final_txpeak,&ds_final_typeak,&ds_final_i,&ds_final_xc,&ds_final_yc,&ds_final_1ry_vx,&ds_final_1ry_vy,&ds_final_1ry_vz,
            &ds_final_1ry_plt,&ds_final_flagw,&ds_final_n_1ry_trk,&ds_final_2ry_vx,&ds_final_2ry_vy,&ds_final_2ry_vz,&ds_final_2ry_plt,&ds_final_parent_plt_1st,
            &ds_final_parent_trkID,&ds_final_parent_MCEvt,&ds_final_parent_pdgID,&ds_final_parent_MCp,&ds_final_nparent_1ry,&ds_final_nparent_1ry_penet,
            &ds_final_nparent_non1ry,&ds_final_parent_tx,&ds_final_parent_ty,&ds_final_ndau,&ds_final_default1,&ds_final_default2,
            &ds_final_plt_dau1,&ds_final_segid_dau1,&ds_final_dau1_MCEvt,&ds_final_dau1_pdgID,&ds_final_dau1_MCp,&ds_final_ip_to1ry_dau1,&ds_final_ip_to2ry_dau1,&ds_final_tx_dau1,&ds_final_ty_dau1,&ds_final_dt_dau1,&ds_final_dtrms_dau1,&ds_final_dtrmst_dau1,&ds_final_dt_w_dau1,
            &ds_final_plt_dau2,&ds_final_segid_dau2,&ds_final_dau2_MCEvt,&ds_final_dau2_pdgID,&ds_final_dau2_MCp,&ds_final_ip_to1ry_dau2,&ds_final_ip_to2ry_dau2,&ds_final_tx_dau2,&ds_final_ty_dau2,&ds_final_dt_dau2,&ds_final_dtrms_dau2,&ds_final_dtrmst_dau2,&ds_final_dt_w_dau2,
            &ds_final_plt_dau3,&ds_final_segid_dau3,&ds_final_dau3_MCEvt,&ds_final_dau3_pdgID,&ds_final_dau3_MCp,&ds_final_ip_to1ry_dau3,&ds_final_ip_to2ry_dau3,&ds_final_tx_dau3,&ds_final_ty_dau3,&ds_final_dt_dau3,&ds_final_dtrms_dau3,&ds_final_dtrmst_dau3,&ds_final_dt_w_dau3,
            &ds_final_plt_dau4,&ds_final_segid_dau4,&ds_final_dau4_MCEvt,&ds_final_dau4_pdgID,&ds_final_dau4_MCp,&ds_final_ip_to1ry_dau4,&ds_final_ip_to2ry_dau4,&ds_final_tx_dau4,&ds_final_ty_dau4,&ds_final_dt_dau4,&ds_final_dtrms_dau4,&ds_final_dtrmst_dau4,&ds_final_dt_w_dau4,
            &ds_final_dmin_org_vee,&ds_final_dmin_fine_vee,&ds_final_topen_vee,&ds_final_dt1dt2_vee,&ds_final_dt012_vee,&ds_final_ntrk_around_2ry,&ds_final_ntrk_other_vtx_max,&ds_final_flag_final);

            ds_final_area1 = vtx_area1;
            ds_final_vtx_id = -1;

            auto it = trkIDMap.find(ds_final_parent_trkID);
            if (it != trkIDMap.end()) 
            {
               ds_final_vtx_id = it->second;
            }
            ds_final->Fill();
         }

         else if (strcmp(type, "dssum_final") == 0)
         {
            char dummy1[50], dummy2[50], dummy3[50], dummy4[50], dummy5[50], dummy6[50], dummy7[50], dummy8[50], dummy9[50], dummy10[50]; // Dummy variables for strings

            sscanf(&line[15], "%d %d %d %f %f %f %f %f %d %d %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d",
            &ds_sumfinal_area1, &ds_sumfinal_area2, &ds_sumfinal_i, &ds_sumfinal_xc, &ds_sumfinal_yc,
            &ds_sumfinal_1ry_vx, &ds_sumfinal_1ry_vy, &ds_sumfinal_1ry_vz, &ds_sumfinal_flagw,
            &ds_sumfinal_n_1ry_trk, dummy1, &ds_sumfinal_c1_intrk1, &ds_sumfinal_c1_intrk2, dummy2,
            &ds_sumfinal_c1, dummy3, &ds_sumfinal_c2, dummy4, &ds_sumfinal_c3, dummy5,
            &ds_sumfinal_n2, dummy6, &ds_sumfinal_n3, dummy7, &ds_sumfinal_n4, dummy8,
            &ds_sumfinal_dt50, dummy9, &ds_sumfinal_n2_op50, dummy10, &ds_sumfinal_c1_intrk_for_pa);

            if (ds_sumfinal_c1 != 0 || ds_sumfinal_c2 != 0 || ds_sumfinal_c3 != 0 || 
               ds_sumfinal_n2 != 0 || ds_sumfinal_n3 != 0 || ds_sumfinal_n4 != 0)
               ds_sumfinal->Fill();
         }

         else if(strcmp(type,"ds_intrk") == 0)
         {
            sscanf(&line[8], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f",
            &ds_intrk_area1,&ds_intrk_area2,&ds_intrk_txpeak,&ds_intrk_typeak,&ds_intrk_i,&ds_intrk_xc,&ds_intrk_yc,&ds_intrk_1ry_vx,&ds_intrk_1ry_vy,&ds_intrk_1ry_vz,
            &ds_intrk_1ry_plt,&ds_intrk_flagw,&ds_intrk_n_1ry_trk,&ds_intrk_2ry_vx,&ds_intrk_2ry_vy,&ds_intrk_2ry_vz,&ds_intrk_2ry_plt,&ds_intrk_parent_plt_1st,
            &ds_intrk_parent_trkID,&ds_intrk_parent_MCEvt,&ds_intrk_parent_pdgID,&ds_intrk_parent_MCp,&ds_intrk_nparent_1ry,&ds_intrk_nparent_1ry_penet,
            &ds_intrk_nparent_non1ry,&ds_intrk_parent_tx,&ds_intrk_parent_ty,&ds_intrk_ndau_all,&ds_intrk_ndau_ip700,&ds_intrk_ndau_ip500,
            &ds_intrk_plt_dau1,&ds_intrk_segid_dau1,&ds_intrk_dau1_MCEvt,&ds_intrk_dau1_pdgID,&ds_intrk_dau1_MCp,&ds_intrk_ip_to1ry_dau1,&ds_intrk_ip_to2ry_dau1,&ds_intrk_tx_dau1,&ds_intrk_ty_dau1,&ds_intrk_dt_dau1,&ds_intrk_dtrms_dau1,&ds_intrk_dtrmst_dau1,&ds_intrk_dt_w_dau1,
            &ds_intrk_plt_dau2,&ds_intrk_segid_dau2,&ds_intrk_dau2_MCEvt,&ds_intrk_dau2_pdgID,&ds_intrk_dau2_MCp,&ds_intrk_ip_to1ry_dau2,&ds_intrk_ip_to2ry_dau2,&ds_intrk_tx_dau2,&ds_intrk_ty_dau2,&ds_intrk_dt_dau2,&ds_intrk_dtrms_dau2,&ds_intrk_dtrmst_dau2,&ds_intrk_dt_w_dau2,
            &ds_intrk_plt_dau3,&ds_intrk_segid_dau3,&ds_intrk_dau3_MCEvt,&ds_intrk_dau3_pdgID,&ds_intrk_dau3_MCp,&ds_intrk_ip_to1ry_dau3,&ds_intrk_ip_to2ry_dau3,&ds_intrk_tx_dau3,&ds_intrk_ty_dau3,&ds_intrk_dt_dau3,&ds_intrk_dtrms_dau3,&ds_intrk_dtrmst_dau3,&ds_intrk_dt_w_dau3 );         

            ds_intrk_area1 = vtx_area1;
            ds_intrk->Fill();               
         }


         else if(strcmp(type,"ds_intrk_wt") == 0)
         {
            sscanf(&line[12], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f",
            &ds_intrk_wt_area1,&ds_intrk_wt_area2,&ds_intrk_wt_txpeak,&ds_intrk_wt_typeak,&ds_intrk_wt_i,&ds_intrk_wt_xc,&ds_intrk_wt_yc,&ds_intrk_wt_1ry_vx,&ds_intrk_wt_1ry_vy,&ds_intrk_wt_1ry_vz,
            &ds_intrk_wt_1ry_plt,&ds_intrk_wt_flagw,&ds_intrk_wt_n_1ry_trk,&ds_intrk_wt_2ry_vx,&ds_intrk_wt_2ry_vy,&ds_intrk_wt_2ry_vz,&ds_intrk_wt_2ry_plt,&ds_intrk_wt_parent_plt_1st,
            &ds_intrk_wt_parent_trkID,&ds_intrk_wt_parent_MCEvt,&ds_intrk_wt_parent_pdgID,&ds_intrk_wt_parent_MCp,&ds_intrk_wt_nparent_1ry,&ds_intrk_wt_nparent_1ry_penet,
            &ds_intrk_wt_nparent_non1ry,&ds_intrk_wt_parent_tx,&ds_intrk_wt_parent_ty,&ds_intrk_wt_ndau_all,&ds_intrk_wt_ndau_ip700,&ds_intrk_wt_ndau_ip500,
            &ds_intrk_wt_plt_dau1,&ds_intrk_wt_segid_dau1,&ds_intrk_wt_dau1_MCEvt,&ds_intrk_wt_dau1_pdgID,&ds_intrk_wt_dau1_MCp,&ds_intrk_wt_ip_to1ry_dau1,&ds_intrk_wt_ip_to2ry_dau1,&ds_intrk_wt_tx_dau1,&ds_intrk_wt_ty_dau1,&ds_intrk_wt_dt_dau1,&ds_intrk_wt_dtrms_dau1,&ds_intrk_wt_dtrmst_dau1,&ds_intrk_wt_dt_w_dau1,
            &ds_intrk_wt_plt_dau2,&ds_intrk_wt_segid_dau2,&ds_intrk_wt_dau2_MCEvt,&ds_intrk_wt_dau2_pdgID,&ds_intrk_wt_dau2_MCp,&ds_intrk_wt_ip_to1ry_dau2,&ds_intrk_wt_ip_to2ry_dau2,&ds_intrk_wt_tx_dau2,&ds_intrk_wt_ty_dau2,&ds_intrk_wt_dt_dau2,&ds_intrk_wt_dtrms_dau2,&ds_intrk_wt_dtrmst_dau2,&ds_intrk_wt_dt_w_dau2,
            &ds_intrk_wt_plt_dau3,&ds_intrk_wt_segid_dau3,&ds_intrk_wt_dau3_MCEvt,&ds_intrk_wt_dau3_pdgID,&ds_intrk_wt_dau3_MCp,&ds_intrk_wt_ip_to1ry_dau3,&ds_intrk_wt_ip_to2ry_dau3,&ds_intrk_wt_tx_dau3,&ds_intrk_wt_ty_dau3,&ds_intrk_wt_dt_dau3,&ds_intrk_wt_dtrms_dau3,&ds_intrk_wt_dtrmst_dau3,&ds_intrk_wt_dt_w_dau3 );         

            //cout << ds_intrk_wt_area2 << " , " << ds_intrk_wt_parent_trkID << " , " << ds_intrk_wt_plt_dau3 << endl;
         
            ds_intrk_wt_area1 = vtx_area1;
            ds_intrk_wt->Fill(); 
         }


         else if(strcmp(type,"ds_intrk_for_pa") == 0)
         {
            sscanf(&line[16], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f",
            &ds_intrk_for_pa_area1,&ds_intrk_for_pa_area2,&ds_intrk_for_pa_txpeak,&ds_intrk_for_pa_typeak,&ds_intrk_for_pa_i,&ds_intrk_for_pa_xc,&ds_intrk_for_pa_yc,&ds_intrk_for_pa_1ry_vx,&ds_intrk_for_pa_1ry_vy,&ds_intrk_for_pa_1ry_vz,
            &ds_intrk_for_pa_1ry_plt,&ds_intrk_for_pa_flagw,&ds_intrk_for_pa_n_1ry_trk,&ds_intrk_for_pa_2ry_vx,&ds_intrk_for_pa_2ry_vy,&ds_intrk_for_pa_2ry_vz,&ds_intrk_for_pa_2ry_plt,&ds_intrk_for_pa_parent_plt_1st,
            &ds_intrk_for_pa_parent_trkID,&ds_intrk_for_pa_parent_MCEvt,&ds_intrk_for_pa_parent_pdgID,&ds_intrk_for_pa_parent_MCp,&ds_intrk_for_pa_nparent_1ry,&ds_intrk_for_pa_nparent_1ry_penet,
            &ds_intrk_for_pa_nparent_non1ry,&ds_intrk_for_pa_parent_tx,&ds_intrk_for_pa_parent_ty,&ds_intrk_for_pa_ndau_all,&ds_intrk_for_pa_ndau_ip700,&ds_intrk_for_pa_ndau_ip500,
            &ds_intrk_for_pa_plt_dau1,&ds_intrk_for_pa_segid_dau1,&ds_intrk_for_pa_dau1_MCEvt,&ds_intrk_for_pa_dau1_pdgID,&ds_intrk_for_pa_dau1_MCp,&ds_intrk_for_pa_ip_to1ry_dau1,&ds_intrk_for_pa_ip_to2ry_dau1,&ds_intrk_for_pa_tx_dau1,&ds_intrk_for_pa_ty_dau1,&ds_intrk_for_pa_dt_dau1,&ds_intrk_for_pa_dtrms_dau1,&ds_intrk_for_pa_dtrmst_dau1,&ds_intrk_for_pa_dt_w_dau1,
            &ds_intrk_for_pa_plt_dau2,&ds_intrk_for_pa_segid_dau2,&ds_intrk_for_pa_dau2_MCEvt,&ds_intrk_for_pa_dau2_pdgID,&ds_intrk_for_pa_dau2_MCp,&ds_intrk_for_pa_ip_to1ry_dau2,&ds_intrk_for_pa_ip_to2ry_dau2,&ds_intrk_for_pa_tx_dau2,&ds_intrk_for_pa_ty_dau2,&ds_intrk_for_pa_dt_dau2,&ds_intrk_for_pa_dtrms_dau2,&ds_intrk_for_pa_dtrmst_dau2,&ds_intrk_for_pa_dt_w_dau2,
            &ds_intrk_for_pa_plt_dau3,&ds_intrk_for_pa_segid_dau3,&ds_intrk_for_pa_dau3_MCEvt,&ds_intrk_for_pa_dau3_pdgID,&ds_intrk_for_pa_dau3_MCp,&ds_intrk_for_pa_ip_to1ry_dau3,&ds_intrk_for_pa_ip_to2ry_dau3,&ds_intrk_for_pa_tx_dau3,&ds_intrk_for_pa_ty_dau3,&ds_intrk_for_pa_dt_dau3,&ds_intrk_for_pa_dtrms_dau3,&ds_intrk_for_pa_dtrmst_dau3,&ds_intrk_for_pa_dt_w_dau3 );         
         
            //cout << ds_intrk_for_pa_area2 << " , " << ds_intrk_for_pa_parent_trkID << " , " << ds_intrk_for_pa_plt_dau3 << endl;
            
            ds_intrk_for_pa_area1 = vtx_area1;
            ds_intrk_for_pa->Fill();
         }

         else if(strcmp(type,"ds_intrk_for_pa_wt") == 0)
         {
            sscanf(&line[18], "%d %d %f %f %d %f %f %f %f %f %d %d %d %f %f %f %d %d %d %d %d %f %d %d %d %f %f %d %d %d %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f %f %f %f %f %f",
            &ds_intrk_for_pa_wt_area1,&ds_intrk_for_pa_wt_area2,&ds_intrk_for_pa_wt_txpeak,&ds_intrk_for_pa_wt_typeak,&ds_intrk_for_pa_wt_i,&ds_intrk_for_pa_wt_xc,&ds_intrk_for_pa_wt_yc,&ds_intrk_for_pa_wt_1ry_vx,&ds_intrk_for_pa_wt_1ry_vy,&ds_intrk_for_pa_wt_1ry_vz,
            &ds_intrk_for_pa_wt_1ry_plt,&ds_intrk_for_pa_wt_flagw,&ds_intrk_for_pa_wt_n_1ry_trk,&ds_intrk_for_pa_wt_2ry_vx,&ds_intrk_for_pa_wt_2ry_vy,&ds_intrk_for_pa_wt_2ry_vz,&ds_intrk_for_pa_wt_2ry_plt,&ds_intrk_for_pa_wt_parent_plt_1st,
            &ds_intrk_for_pa_wt_parent_trkID,&ds_intrk_for_pa_wt_parent_MCEvt,&ds_intrk_for_pa_wt_parent_pdgID,&ds_intrk_for_pa_wt_parent_MCp,&ds_intrk_for_pa_wt_nparent_1ry,&ds_intrk_for_pa_wt_nparent_1ry_penet,
            &ds_intrk_for_pa_wt_nparent_non1ry,&ds_intrk_for_pa_wt_parent_tx,&ds_intrk_for_pa_wt_parent_ty,&ds_intrk_for_pa_wt_ndau_all,&ds_intrk_for_pa_wt_ndau_ip700,&ds_intrk_for_pa_wt_ndau_ip500,
            &ds_intrk_for_pa_wt_plt_dau1,&ds_intrk_for_pa_wt_segid_dau1,&ds_intrk_for_pa_wt_dau1_MCEvt,&ds_intrk_for_pa_wt_dau1_pdgID,&ds_intrk_for_pa_wt_dau1_MCp,&ds_intrk_for_pa_wt_ip_to1ry_dau1,&ds_intrk_for_pa_wt_ip_to2ry_dau1,&ds_intrk_for_pa_wt_tx_dau1,&ds_intrk_for_pa_wt_ty_dau1,&ds_intrk_for_pa_wt_dt_dau1,&ds_intrk_for_pa_wt_dtrms_dau1,&ds_intrk_for_pa_wt_dtrmst_dau1,&ds_intrk_for_pa_wt_dt_w_dau1,
            &ds_intrk_for_pa_wt_plt_dau2,&ds_intrk_for_pa_wt_segid_dau2,&ds_intrk_for_pa_wt_dau2_MCEvt,&ds_intrk_for_pa_wt_dau2_pdgID,&ds_intrk_for_pa_wt_dau2_MCp,&ds_intrk_for_pa_wt_ip_to1ry_dau2,&ds_intrk_for_pa_wt_ip_to2ry_dau2,&ds_intrk_for_pa_wt_tx_dau2,&ds_intrk_for_pa_wt_ty_dau2,&ds_intrk_for_pa_wt_dt_dau2,&ds_intrk_for_pa_wt_dtrms_dau2,&ds_intrk_for_pa_wt_dtrmst_dau2,&ds_intrk_for_pa_wt_dt_w_dau2,
            &ds_intrk_for_pa_wt_plt_dau3,&ds_intrk_for_pa_wt_segid_dau3,&ds_intrk_for_pa_wt_dau3_MCEvt,&ds_intrk_for_pa_wt_dau3_pdgID,&ds_intrk_for_pa_wt_dau3_MCp,&ds_intrk_for_pa_wt_ip_to1ry_dau3,&ds_intrk_for_pa_wt_ip_to2ry_dau3,&ds_intrk_for_pa_wt_tx_dau3,&ds_intrk_for_pa_wt_ty_dau3,&ds_intrk_for_pa_wt_dt_dau3,&ds_intrk_for_pa_wt_dtrms_dau3,&ds_intrk_for_pa_wt_dtrmst_dau3,&ds_intrk_for_pa_wt_dt_w_dau3 );         
         
            //cout << ds_intrk_for_pa_wt_area2 << " , " << ds_intrk_for_pa_wt_parent_trkID << " , " << ds_intrk_for_pa_wt_plt_dau3 << endl;

            ds_intrk_for_pa_wt_area1 = vtx_area1;
            ds_intrk_for_pa_wt->Fill();
         }


      }
   }
   h_align->Draw();

   vtx->Print();
   trk->Print();
   par->Print();
   //parCand->Print();

   vtx->Write();
   trk->Write();
   par->Write();
   //parCand->Write();

   us_ptrk->Write();
   ds_ptrk->Write();

   ds_all->Write();
   ds_final->Write();
   ds_sumfinal->Write();
   ds_intrk->Write();
   ds_intrk_wt->Write();
   ds_intrk_for_pa->Write();
   ds_intrk_for_pa_wt->Write();

   fclose(fp);
   delete hfile;

   h_align->SetLineColor(kBlack);
   h_align->SetLineWidth(1);
   h_align->Draw("sames");

   c3->Modified(); c3->Update();
   TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);


   t3->AddText("Vertices in the depth of detector PD05");
   t3->SetTextSize(0.06);
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->Draw();
   c3->Print("ZVertex_PD05_all_aligned_vertices.pdf");
   
   hfile = TFile::Open(filename);

   cout << "Vertex Size: " << vNum << ", Parent Size: " << pNum << ", Track Size: " << tNum << endl;
   //cout << "Reconstructed Size: " << recNum << ", Not Reconstructed Size: " << notRecNum << endl;
   return hfile;
}


vector<tuple<int, int, int, int, int, int, int>> ReadFile(char *inFile, int segNum)
{
   vector<tuple<int, int, int, int, int, int, int>> trIDVec;

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

   int* initSegPlt = new int[numLines];
   int* trID = new int[numLines];
   int* globalTrID = new int[numLines];
   int* initPosX = new int[numLines];
   int* initPosY = new int[numLines];
   int* initPosZ = new int[numLines];
   
   int* pltID = new int[numLines];
   int* segID = new int[numLines];

   int* initTX = new int[numLines];
   int* initTY = new int[numLines];
   
   fUS = fopen(inFile, "r");
   
   for(int i = 0; i < numLines; i++)
   {
      fscanf(fUS, "%8d, %8d, %10d, %8d, %8d, %8d, %8d, %8d", &initSegPlt[i], &trID[i], &globalTrID[i], &initPosX[i], &initPosY[i], &initPosZ[i], &initTX[i], &initTY[i]);
      //fscanf(fUS, "%8d, %8d, %10d", &initSegPlt[i], &trID[i], &globalTrID[i]);
      //fscanf(fUS, "%8d, %8d, %8d, %8d", &trID[i], &pltID[i], &segID[i], &initSegPlt[i]);
      
      if (segNum == initSegPlt[i]) {trIDVec.push_back(make_tuple(trID[i], globalTrID[i], initPosX[i], initPosY[i], initPosZ[i], initTX[i], initTY[i]));}
   }
   fclose(fUS);

   delete[] initSegPlt;
   delete[] trID;
   delete[] globalTrID;
   delete[] initPosX;
   delete[] initPosY;
   delete[] initPosZ;
   delete[] pltID;
   delete[] segID;
   delete[] initTX;
   delete[] initTY;

   return trIDVec;
}

void FineAllign()
{
   All_limits(); //only once!!

   h_align = new TH1F("h_all","h_all",2500,0,50000);

   h_align->GetXaxis()->SetTitle("mkm");
   h_align->GetXaxis()->SetTitleSize(0.06);
   h_align-> GetXaxis() -> SetTitleOffset(0.7);
   h_align-> GetXaxis() ->SetTickLength(0.009);
   h_align->GetXaxis()->SetLabelSize(0.04);
   h_align-> GetYaxis() ->SetTickLength(0.009);

   TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
   TCanvas *c3 = new TCanvas("c3","cLng", 1000,400);

   gStyle->SetOptTitle(0);
   gStyle->SetOptFit();

   int area=0;
   double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
   int nr=0, ok=0;

   int currentRow=0, currentColumn=0, Xmin=0, Xmax=0, Ymin=0, Ymax=0;
   int TotalColumns = 9;
   int TotalRows = 7;

   for(int i_name=0;i_name<=2;i_name++)
   {
      char filename[64];
      snprintf(filename, 64, "../../PD05/ds_res_PR2018_PD05_p0%d6.txt",i_name);

      //calculate the limits for this file
      int plt=i_name*10+1;
      mean_limits(plt);
      limits(1,plt);
      int area=1;
      Xmin=-2500;
      Xmax=12500;
      Ymin=-2500;
      Ymax=12500;

      ifstream f;
      string line;
      f.open(filename);
   

      if (f.is_open())
      {
         cout<<"Is open: "<<filename<<endl;
         char* paritate = (char*)calloc(1000, 1); //"1ry_trk"
         int* s1;  //area
         int* s2; //area2
         float* s3;   //tx_peak (beam angle chked in the local area)
         float* s4;   //ty_peak
         int* s5;  //i
         float* s6;   //1ry vx
         float* s7;   //1ry vy
         float* s8;    //1ry vz
         int* s9;  //flag_in_w (1: in tungsten, 0: other material) -> tentative flag, better to chk z dist
         int* s10;   //n_1ry-trk
         int* s11;  //n_1ry-parent_default
         int* s12;    //n_1ry-parent_dmin-cut
         float* s13;     //dz between 1ry and 1st seg
         long* s14;     //trk-id
         int* s15;  //plate of 1st seg
         long* s16;   //seg-id of 1st seg
         float *s17;  //1st_seg x
         float *s18; //1st_seg y
         float* s19;     //tx
         float* s20;   //ty
         int* s21;    //n_seg
         float* s22; //ip_to_1ry_using_pos
         float* s23; //ip_to_1ry_using_pos, 2nd
         char *s24; //ph_mean
         float* s25;  //dtrms1_trk
         
         //1ry_trk
         int p1;  //area
         int p2;  //area2
         float p3;   //tx_peak(beam angle chked in the local area)
         float p4;  //ty_peak
         int p5;   //i
         float p6;     //1ry vx
         float p7;  //1ry vy
         float p8;   //1ry vz
         int p9; //1ry pl (vID),
         int p10;   //flag_in_w (1: in tungsten, 0: other material) -> tentative flag, better to chk z dist
         int p11;    //n_1ry-trk
         int p12;   //n_1ry-parent_cut0
         int p13;  //n_1ry-parent_dmin-cut, <- Please use this,
         int p14; //n_1ry-parent_dmin-cut_dt-cut
         float p15;    //dt (angle difference between 1ry-parent and connected trk if any)
         
         
         while (f.peek()!=EOF )   //EOF end of https://youtu.be/4cfFYvTD09Afile
         {

            //Check if paritate isn't already primary, else read primary paritate
            if (strcmp(paritate, "1ry_vtx")!=0) 
            {
               f >> paritate;
            }

            //cout << paritate << endl;
            if (strcmp("1ry_vtx", paritate) == 0)
            {
               //Reading primary element
               //cout << "Found a primar" << endl;
               f >> p1;
               f >> p2;
               f >> p3;
               f >> p4;
               f >> p5;
               f >> p6;
               f >> p7;
               f >> p8;
               f >> p9;
               f >> p10;
               f >> p11;
               f >> p12;
               f >> p13;
               f >> p14;
               f >> p15; 
               
               //Reinitalizing seconday elements container
               s1 = (int*)calloc(p8+1, sizeof(int));
               s2 = (int*)calloc(p8+1, sizeof(int));
               s3 = (float*)calloc(p8+1, sizeof(float));
               s4 = (float*)calloc(p8+1, sizeof(float));
               s5 = (int*)calloc(p8+1, sizeof(int));
               s6 = (float*)calloc(p8+1, sizeof(float));
               s7 = (float*)calloc(p8+1, sizeof(float));
               s8 = (float*)calloc(p8+1, sizeof(float));
               s9 = (int*)calloc(p8+1, sizeof(int));
               s10 = (int*)calloc(p8+1, sizeof(int));
               s11 = (int*)calloc(p8+1, sizeof(int));
               s12 = (int*)calloc(p8+1, sizeof(int));
               s13 = (float*)calloc(p8+1, sizeof(float));
               s14 = (long*)calloc(p8+1, sizeof(long));
               s15 = (int*)calloc(p8+1, sizeof(int));
               s16 = (long*)calloc(p8+1, sizeof(long));
               s17 = (float*)calloc(p8+1, sizeof(float));
               s18 = (float*)calloc(p8+1, sizeof(float));
               s19 = (float*)calloc(p8+1, sizeof(float));
               s20 = (float*)calloc(p8+1, sizeof(float));
               s21 = (int*)calloc(p8+1, sizeof(int));
               s22 = (float*)calloc(p8+1, sizeof(float));  
               s23 = (float*)calloc(p8+1, sizeof(float));  
               s24 = (char*)calloc(p8+1, sizeof(char));  
               s25 = (float*)calloc(p8+1, sizeof(float));  
               

               //Reading p5 elements
               int i = -1;//contorul de secunzi

               while (f >> paritate && strcmp("1ry_trk",paritate)==0 && f.peek()!=EOF) 
               {
                  ++i;
                  f >> s1[i];
                  f >> s2[i];
                  f >> s3[i];
                  f >> s4[i];
                  f >> s5[i];
                  f >> s6[i];
                  f >> s7[i];
                  f >> s8[i];
                  f >> s9[i];
                  f >> s10[i];
                  f >> s11[i];
                  f >> s12[i];
                  f >> s13[i];
                  f >> s14[i];
                  f >> s15[i];
                  f >> s16[i];
                  f >> s17[i];
                  f >> s18[i];
                  f >> s19[i];
                  f >> s20[i];
                  f >> s21[i];
                  f >> s22[i];
                  f >> s23[i];
                  f >> s24[i];
                  f >> s25[i];
                  
               }
               i++;  //cout<<p2<<" "<<p5<<endl;
               
               if (p13>0)
               {   
                  if(area<p1 )
                  {   
                     //draw_hist(area);
                     area=p1;
                     //hist(); //reinitialization of the histogram
                     limits(p1,plt);

                     //center of subarea
                     currentRow = 5000 + (area-1)%TotalColumns * 15000;
                     currentColumn = 5000 + (area-1)/TotalColumns * 15000;

                     //main limits of subarea
                     Xmin=currentRow-7500;
                     Xmax=currentRow+7500;
                     Ymin=currentColumn-7500;
                     Ymax=currentColumn+7500;
                  }

                  if(area==p1) //all are 0 in MC
                  {
                        
                     //Tungsten
                     for(int j=1;j<=1;j++)
                     {
                        if(p8>tl[j] && p8<=tr[j]) 
                        {
                           mean_thickness = mtr[j]-mtl[j]; //cout<<mean_thickness<<" tungsten "<<endl;
                           scanned_thickness = tr[j]-tl[j];
                           vertex_correction = p8-tl[j];

                           h_align->Fill(mtl[j] + mean_thickness * vertex_correction / scanned_thickness);
                        }
                     }

                     //Emulsion
                     for(int j=1;j<=20;j++)
                     {
                        if(p8>el[j] && p8<=er[j]) 
                        {
                           mean_thickness = mer[j]-mel[j]; //cout<<mean_thickness<<" emulsion "<<endl;
                           scanned_thickness = er[j]-el[j];
                           vertex_correction = p8-el[j];

                           h_align->Fill(mel[j] + mean_thickness * vertex_correction / scanned_thickness);
                        }
                     }

                     //Plastic
                     for(int j=1;j<20;j++)
                     {
                        if(p8>pl[j] && p8<=pr[j]) 
                        {
                           mean_thickness = mpr[j]-mpl[j]; //cout<<mean_thickness<<" plastic "<<endl;
                           scanned_thickness = pr[j]-pl[j];
                           vertex_correction = p8-pl[j];
                        } 
                     }
                  }
               }
                   
               free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
               free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
               free(s20); free(s21); free(s22);
            }
         }
      }
      else
      {
         cout << "Unable to open file";
      }

      f.close();
      h_align->Draw();

      int max= h_align->GetMaximum(); 
      max=max+100; //to fill untill the frame 
   }

   h_align->SetLineColor(kBlack);
   h_align->SetLineWidth(1);
   h_align->Draw("sames");

   c3->Modified(); c3->Update();
   TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);


   t3->AddText("Vertices in the depth of detector PD05");
   t3->SetTextSize(0.06);
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->Draw();
   c3->Print("ZVertex_PD05_all_aligned_vertices.pdf");
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

bool isTranslatedOut(int index, int posX, int posY, int posZ, float tX, int tY)
{
   int acceptanceCut[21] = 
   {
      29, 30, 31, 32, 33, 34, 35,
      38, 39, 40, 41, 42, 43, 44,
      47, 48, 49, 50, 51, 52, 53
   };

   float stepX = 15000;
   float stepY = 15000;

   float intX = 5000;
   float intY = 5000;

   /*
   int posXMin = intX + ((acceptanceCut[0]-1)%9)*stepX;
   int posYMin = intY + ((acceptanceCut[0]-1)/9)*stepY;
   int posXMax = intX + ((acceptanceCut[20])%9)*stepX;
   int posYMax = intY + ((acceptanceCut[20])/9)*stepY;
   */
   
   int posXMin = intX + ((index-1)%9)*stepX - stepX/2;
   int posYMin = intY + ((index-1)/9)*stepY - stepY/2;
   int posXMax = posXMin + stepX;
   int posYMax = posYMin + stepY;

   //cout << "Area: " << index << ", " << posXMin << ", " << posXMax << ", " << posYMin << ", " << posYMax << endl;

   //int zDif = 5300;
   int zDif = 7925;

   //cout << "Area: " << index << ", " << posX << ", " << posY << endl;

   float endPosX = posX + tX * zDif;
   float endPosY = posY + tY * zDif;

   if (endPosX > posXMin && endPosX < posXMax && endPosY > posYMin && endPosY < posYMax)
   {
      return false;
   }
   //else{cout << posX << ", " << posY << endl;}

   if (posX > posXMin && posX < posXMax && posY > posYMin && posY < posYMax)
   {
      return false;
   }

   return true;
}

bool isInSubArea(int index, int posX, int posY)
{
   float stepX = 15000;
   float stepY = 15000;

   float intX = 5000;
   float intY = 5000;
   
   int posXMin = intX + ((index-1)%9)*stepX - stepX/2;
   int posYMin = intY + ((index-1)/9)*stepY - stepY/2;
   int posXMax = posXMin + stepX;
   int posYMax = posYMin + stepY;

   if (posX > posXMin && posX < posXMax && posY > posYMin && posY < posYMax)
   {
      return true;
   }
   else
   {
      //cout << "Boundaries: " << posXMin << ", " << posYMin << ", Position: " << posX << ", " << posY << endl;
   }

   return false;
}