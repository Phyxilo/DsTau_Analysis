#include <iostream>
#include <vector>

using namespace std;

vector<tuple<int, int, int, int, int, int, int>> ReadFile(char *inFile, int segNum);

bool firstEqual(const tuple<int, int, int, int, int, int, int>& a, const tuple<int, int, int, int, int, int, int>& b) 
{
   return get<0>(a) == get<0>(b);
}

bool isTranslatedOut(int index, int posX, int posY, int posZ, float tX, int tY);
bool isInSubArea(int index, int posX, int posY);

TFile *Dat2Root(string inputName, string outputName, string inputDS, string inputUS, int dirIndex)
{

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

   int prevSubArea = 1, recoNum = 1;

   for (int segNum = 0; segNum <= 1; segNum++)
   {
      int parid = 0;
      vector<int> paridVec;

      vector<tuple<int, int, int, int, int, int, int>> USPair[63], DSPair[63];
      vector<tuple<int, int>> trkIDVec;
      vector<tuple<int, int>> parTrkIDVec;
      //vector<pair<int, int>> USPair, DSPair;
      //set<pair<int, int>> USPair, DSPair;

      vector<int> UStrID[63], USgtrID[63];
      vector<int> DStrID[63], DSgtrID[63];
      vector<int> intVec[63];
      vector<int> UStrIDOut[63];

      for (int areaInd = 0; areaInd < 1; areaInd++)
      {
         int pInAcc = 0, pOutAcc = 0;

         const int USStrLength = inputUS.length();
         const int DSStrLength = inputDS.length();

         char* USChr = new char[USStrLength + 1];
         char* DSChr = new char[DSStrLength + 1];

         strcpy(USChr, inputUS.c_str());
         strcpy(DSChr, inputDS.c_str());

         char USIn[64], DSIn[64];

         sprintf(USIn, "PythiaCharm_Full/Area_%02d/Output/Merged/%s", areaInd+1, USChr);
         sprintf(DSIn, "PythiaCharm_Full/Area_%02d/Output/Merged/%s", areaInd+1, DSChr);

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

            if (/*!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY)*/ true)
            {
               UStrID[areaInd].push_back(trid);
               USgtrID[areaInd].push_back(gtrid);

               ptrk_US_area1 = areaInd;
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

            if (/*!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY)*/ true)
            {
               DStrID[areaInd].push_back(trid);
               DSgtrID[areaInd].push_back(gtrid);

               ptrk_DS_area1 = areaInd;
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

         cout << "Area " << areaInd << " - Done" << endl;
         cout << "Number of Protons Inside Acceptance: " << pInAcc << ", Number of Protons Outside Acceptance: " << pOutAcc << endl;
      }

      while (fgets(line,1024,fp))
      {
         sscanf(&line[0],"%s ",type);
         if(strcmp(type,"1ry_vtx") == 0)
         {
            sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %d %d %f",&vtx_area1,&vtx_area2,&vtx_txpeak,&vtx_typeak,&vtx_i,&vtx_vx,&vtx_vy,&vtx_vz,&vtx_n_1ry_pl,&vtx_flagw,&vtx_multip,
               &vtx_n_1ry_parent_cut0,&vtx_n_1ry_parent_dmin_cut,&vtx_n_1ry_parent_dmin_cut_dt_cut,&vtx_dt);

            chldNum = 0;

            vtx_area1 = recoNum-1;
            
            if (vtx_n_1ry_parent_dmin_cut > 0)
            {
               parC_id = parid;

               vtx_int_type = 0;
               par_flagp = 0;
               glob_parid = 0;

               for(int x = 0; x < paridVec.size(); x++)
               {
                  auto it = find(UStrID[parC_area1].begin(), UStrID[parC_area1].end(), paridVec[x]);
                  if (it != UStrID[parC_area1].end())
                  {
                     int index = it - UStrID[parC_area1].begin();
                     parC_id = paridVec[x];
                     
                     vtx_int_type = 1;
                     par_flagp = 1;

                     glob_parid = USgtrID[parC_area1][index];
                  }

                  it = find(intVec[parC_area1].begin(), intVec[parC_area1].end(), paridVec[x]);
                  if (it != intVec[parC_area1].end())
                  {
                     int index = it - UStrID[parC_area1].end();

                     vtx_int_type = 2;
                  }
               }

               VtxId++;
               vtx_vID = VtxId;

               vtx_n_1ry_trk = vtx_multip;
               trk_n_1ry_trk = vtx_multip;
               parC_n_1ry_trk = vtx_multip;

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

            parTrkIDVec.push_back(make_tuple(parid, VtxId+1));
            
            if (parC_area2 != prevSubArea)
            {
               parTrkIDVec.clear();
               if (parC_area2 == 1){recoNum++;}
            }
            /*
            if (trk_n_1ry_parent_dmin_cut == 1)
            {
               trk_vID = VtxId+1;
               parCand->Fill();
               cout << trk_vID << "-> ParCand: " << trk_id << endl;
            }
            */
            if(parC_pl_up1ry_plmin == dirIndex*10+segNum+1){paridVec.push_back(parid);}

            parC_area1 = recoNum-1;

            prevSubArea = parC_area2;
         }
         else if(strcmp(type,"1ry_trk") == 0)
         {
            sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %f %d %d %d %f %f %f %f %d %f %f %f %f",&trk_area1,&trk_area2,&trk_txpeak,&trk_typeak,&trk_i,&trk_vx,&trk_vy,&trk_vz,&trk_flagw,&trk_multip,
               &trk_n_1ry_parent_cut0,&trk_n_1ry_parent_dmin_cut,&trk_dz,&trk_id,&trk_plt_of_1seg,&trk_seg_id_of_1seg,&trk_seg_x,&trk_seg_y,&trk_tx,&trk_ty,&trk_nseg,&trk_ip_to_1ry_using_1stseg,
               &trk_ip_to_1ry_using_2ndseg,&trk_ph_mean,&trk_dtrms1_trk);

            trk_area1 = recoNum-1;
            
            if (trk_n_1ry_parent_dmin_cut > 0)
            {
               if (/*parC_id != trk_id*/ true)
               {
                  chldNum++;
                  trk_vID = VtxId;
                  parC_vID = VtxId;

                  trkIDVec.push_back(make_tuple(trk_id, trk_vID));
                  if (trk_area2 != prevSubArea)
                  {
                     trkIDVec.clear();
                  }

                  tNum++;
                  if (chldNum == vtx_multip)
                  {
                     notRecNum++;
                     //cout << "Parent TrkId (Parent not reconstructed): " << parC_id << endl;
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

            ds_all_area1 = recoNum-1;
            ds_all_vtx_id = -10000;
            
            for (const auto& pairTuple : trkIDVec) 
            {
               if (get<0>(pairTuple) == ds_all_parent_trkID) 
               {
                  ds_all_vtx_id = get<1>(pairTuple);
                  //cout << "TrkID: " << get<0>(pairTuple) << ", VtxID: " << get<1>(pairTuple) << endl;
               }
            }
            ds_all->Fill();
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

            ds_intrk_area1 = recoNum-1 ;
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
         
            ds_intrk_wt_area1 = recoNum-1 ;
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
            
            ds_intrk_for_pa_area1 = recoNum-1 ;
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

            ds_intrk_for_pa_wt_area1 = recoNum-1 ;
            ds_intrk_for_pa_wt->Fill();
         }


      }
   }

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
   ds_intrk->Write();
   ds_intrk_wt->Write();
   ds_intrk_for_pa->Write();
   ds_intrk_for_pa_wt->Write();

   fclose(fp);
   delete hfile;
   
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

   const int numL = numLines;

   int initSegPlt[numLines];
   int trID[numLines];
   int globalTrID[numLines];
   int initPosX[numLines];
   int initPosY[numLines];
   int initPosZ[numLines];
   
   int pltID[numLines];
   int segID[numLines];

   int initTX[numLines];
   int initTY[numLines];
   
   fUS = fopen(inFile, "r");
   
   for(int i = 0; i < numLines; i++)
   {
      fscanf(fUS, "%8d, %8d, %10d, %8d, %8d, %8d, %8d, %8d", &initSegPlt[i], &trID[i], &globalTrID[i], &initPosX[i], &initPosY[i], &initPosZ[i], &initTX[i], &initTY[i]);
      //fscanf(fUS, "%8d, %8d, %10d", &initSegPlt[i], &trID[i], &globalTrID[i]);
      //fscanf(fUS, "%8d, %8d, %8d, %8d", &trID[i], &pltID[i], &segID[i], &initSegPlt[i]);
      
      if (segNum == initSegPlt[i]) {trIDVec.push_back(make_tuple(trID[i], globalTrID[i], initPosX[i], initPosY[i], initPosZ[i], initTX[i], initTY[i]));}
   }
   fclose(fUS);

   return trIDVec;
}

bool isTranslatedOut(int index, int posX, int posY, int posZ, float tX, int tY)
{

   int posXMin = -7500;
   int posYMin = -7500;
   int posXMax = 7500;
   int posYMax = 7500;

   int zDif = 5700;

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