#include <iostream>
#include <vector>

using namespace std;

const int subAreaNum = 13;

bool removeOutOfBounds = false;

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

   int VtxId = -1, chldNum = 0;
   char line[1024];

   int vNum = 0, pNum = 0, tNum = 0, recNum = 0, notRecNum = 0;

   int prevSubArea = 1, recoNum = 1;

   for (int segNum = 0; segNum <= 1; segNum++)
   {
      int parid = 0;
      vector<int> paridVec;

      vector<tuple<int, int, int, int, int, int, int>> USPair [subAreaNum], DSPair [subAreaNum];
      //vector<pair<int, int>> USPair, DSPair;
      //set<pair<int, int>> USPair, DSPair;

      vector<int> UStrID[subAreaNum], USgtrID[subAreaNum];
      vector<int> DStrID[subAreaNum], DSgtrID[subAreaNum];
      vector<int> intVec[subAreaNum];
      vector<int> UStrIDOut[subAreaNum];

      for (int areaInd = 0; areaInd < subAreaNum; areaInd++)
      {
         int pInAcc = 0, pOutAcc = 0;

         const int USStrLength = inputUS.length();
         const int DSStrLength = inputDS.length();

         char* USChr = new char[USStrLength + 1];
         char* DSChr = new char[DSStrLength + 1];

         strcpy(USChr, inputUS.c_str());
         strcpy(DSChr, inputDS.c_str());

         char USIn[128], DSIn[128];

         snprintf(USIn, 128, "EPOS_Full_3Sigma/Area_%02d/Output/Merged/%s", areaInd+1, USChr);
         snprintf(DSIn, 128, "EPOS_Full_3Sigma/Area_%02d/Output/Merged/%s", areaInd+1, DSChr);

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

            if ((removeOutOfBounds == true && !isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY)) || removeOutOfBounds == false)
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

               if ((removeOutOfBounds == true && !isTranslatedOut(areaInd+1, posX, posY, posZ, tX, tY)) || removeOutOfBounds == false)
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

         cout << "Area " << areaInd+1 << " - Done" << endl;
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

            if (parC_area2 != prevSubArea && parC_area2 == 1)
            {
               //cout << parC_area1 << endl;
               recoNum++;
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

bool isTranslatedOut(int index, int posX, int posY, int posZ, float tX, int tY)
{

   int posXMin = -7500;
   int posYMin = -7500;
   int posXMax = 7500;
   int posYMax = 7500;

   int zDif = 8325;

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