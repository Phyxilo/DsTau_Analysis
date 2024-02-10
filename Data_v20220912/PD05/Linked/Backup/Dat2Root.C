#include <iostream>
#include <vector>
#include <map>

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

   int VtxId = -1, chldNum = 0;
   char line[1024];

   int vNum = 0, pNum = 0, tNum = 0, recNum = 0, notRecNum = 0;

   for (int segNum = 0; segNum <= 2; segNum++)
   {
      int parid = 0;
      vector<int> paridVec;

      vector<tuple<int, int, int, int, int, int, int>> USPair [63], DSPair [63];
      //vector<pair<int, int>> USPair, DSPair;
      //set<pair<int, int>> USPair, DSPair;

      vector<int> UStrID[63], USgtrID[63];
      vector<int> DStrID[63], DSgtrID[63];
      vector<int> intVec[63];

      for (int areaInd = 0; areaInd < 63; areaInd++)
      {
         if (isInAcceptance(areaInd+1))
         {
            int pInAcc = 0, pOutAcc = 0;

            const int USStrLength = inputUS.length();
            const int DSStrLength = inputDS.length();

            char* USChr = new char[USStrLength + 1];
            char* DSChr = new char[DSStrLength + 1];

            strcpy(USChr, inputUS.c_str());
            strcpy(DSChr, inputDS.c_str());

            char USIn[128], DSIn[128];

            sprintf(USIn, "PD05_FullArea_Links/Area_%02d/Output/Merged/%s", areaInd+1, USChr);
            sprintf(DSIn, "PD05_FullArea_Links/Area_%02d/Output/Merged/%s", areaInd+1, DSChr);

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

               if (!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY))
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
               else{pOutAcc++;}
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

               if (!isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY))
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
            cout << "Number of Protons Inside Acceptance: " << pInAcc << ", Number of Protons Outside Acceptance: " << pOutAcc << endl;
         }
      }

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
      char filename[100];
      sprintf(filename, "../ds_res_PR2018_PD05_p0%d6.txt",i_name);

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

/*
bool isTranslatedOut(int index, int posX, int posY, int posZ)
{
   int acceptanceCut[21] = 
   {
      29, 30, 31, 32, 33, 34, 35,
      38, 39, 40, 41, 42, 43, 44,
      47, 48, 49, 50, 51, 52, 53
   };

   map <int, pair <float, float>> avgBeamSlope;

   avgBeamSlope[29] = make_pair(-0.02092, -0.00565);
   avgBeamSlope[30] = make_pair(-0.01845, -0.00509);
   avgBeamSlope[31] = make_pair(-0.01853, -0.00466);
   avgBeamSlope[32] = make_pair(-0.01998, -0.00515);
   avgBeamSlope[33] = make_pair(-0.02065, -0.00554);
   avgBeamSlope[34] = make_pair(-0.02110, -0.00516);
   avgBeamSlope[35] = make_pair(-0.02168, -0.00446);
   avgBeamSlope[38] = make_pair(-0.02183, -0.00757);
   avgBeamSlope[39] = make_pair(-0.01875, -0.00699);
   avgBeamSlope[40] = make_pair(-0.01822, -0.00652);
   avgBeamSlope[41] = make_pair(-0.02027, -0.00674);
   avgBeamSlope[42] = make_pair(-0.02028, -0.00662);
   avgBeamSlope[43] = make_pair(-0.02106, -0.00663);
   avgBeamSlope[44] = make_pair(-0.02151, -0.00587);
   avgBeamSlope[47] = make_pair(-0.02293, -0.00924);
   avgBeamSlope[48] = make_pair(-0.01879, -0.00924);
   avgBeamSlope[49] = make_pair(-0.01821, -0.00968);
   avgBeamSlope[50] = make_pair(-0.02011, -0.01000);
   avgBeamSlope[51] = make_pair(-0.02019, -0.00998);
   avgBeamSlope[52] = make_pair(-0.02013, -0.00909);
   avgBeamSlope[53] = make_pair(-0.02120, -0.00814);

   float stepX = 15000;
   float stepY = 15000;

   float intX = 5000;
   float intY = 5000;
   
   int posXMin = intX + ((index-1)%9)*stepX - stepX/2;
   int posYMin = intY + ((index-1)/9)*stepY - stepY/2;
   int posXMax = posXMin + stepX;
   int posYMax = posYMin + stepY;

   //cout << "Area: " << index << ", " << posXMin << ", " << posXMax << ", " << posYMin << ", " << posYMax << endl;

   int endPosZ = 5885;

   //int zDif = endPosZ - posZ;
   //int zDif = 810;
   int zDif = 5885;

   //cout << "Area: " << index << ", " << posX << ", " << posY << endl;

   float endPosX = posX + get<0>(avgBeamSlope[index]) * zDif;
   float endPosY = posY + get<1>(avgBeamSlope[index]) * zDif;

   if (endPosX > posXMin && endPosX < posXMax && endPosY > posYMin && endPosY < posYMax)
   {
      return false;
   }
   //else{cout << posX << ", " << posY << endl;}

   return true;
}
*/

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

   int endPosZ = 5885;

   //int zDif = endPosZ - posZ;
   //int zDif = 5885;
   int zDif = 5300;

   //cout << "Area: " << index << ", " << posX << ", " << posY << endl;

   float endPosX = posX + tX * zDif;
   float endPosY = posY + tY * zDif;

   if (endPosX > posXMin && endPosX < posXMax && endPosY > posYMin && endPosY < posYMax)if ((posX > posXMin+1000 && posX < posXMax-1000 && posY > posYMin+1000 && posY < posYMax-1000) && (endPosX > posXMin && endPosX < posXMax && endPosY > posYMin && endPosY < posYMax))
   {
      return false;
   }
   //else{cout << posX << ", " << posY << endl;}

   return true;
}