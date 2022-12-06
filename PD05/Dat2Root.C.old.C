TFile *Dat2Root(string inputName, string outputName) 
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

   // Parent Candidate Tree Variables
   Int_t           ParC_area1;
   Int_t           ParC_area2;
   Float_t         ParC_txpeak;
   Float_t         ParC_typeak;
   Int_t           ParC_i;
   Float_t         ParC_vx;
   Float_t         ParC_vy;
   Float_t         ParC_vz;
   Int_t           ParC_n_1ry_pl;
   Int_t           ParC_flagw;
   Int_t           ParC_n_1ry_trk;
   Int_t           ParC_n_1ry_parent_cut0;
   Int_t           ParC_n_1ry_parent_dmin_cut;
   Int_t           ParC_n_1ry_parent_dmin_cut_dt_cut;
   Float_t         ParC_dt;
   Float_t         ParC_dz;
   Int_t           ParC_id;
   Int_t           ParC_plt_of_1seg;
   Int_t           ParC_seg_id_of_1seg;
   Int_t           ParC_vID;
   Float_t         ParC_seg_x;
   Float_t         ParC_seg_y;
   Float_t         ParC_tx;
   Float_t         ParC_ty;
   Int_t           ParC_nseg;
   Float_t         ParC_ip_to_1ry_using_1stseg;
   Float_t         ParC_ip_to_1ry_using_2ndseg;
   Float_t         ParC_ph_mean;
   Float_t         ParC_dtrms1_trk;
   Float_t Par9,Par13,Par14,ip_pos05,ip_pos04,dt_pos;
   Int_t Par11,Par12,Par15,ntrk_small,Par26,Par27,Par28,Par29;
   Char_t ipChar05[16],ipChar04[16],ntrk_smallChar[16],dtChar[16],dt_posChar[16];

   Float_t ip_pos_05, ip_pos_04;

   Char_t ipChr1[16];
   Char_t ipChr2[16];
   Char_t chr[16];

   char inArr[1024];
   strcpy(inArr, inputName.c_str());

   TString filename = outputName;
   //FILE *fp = fopen("20220622_PD04/PD04/ds_res_PR2018_PD04_p006.txt","r");
   FILE *fp = fopen(inArr,"r");

   TFile *hfile = 0;

   /*
   if (!gSystem->AccessPathName(filename,kFileExists)) 
   {
      hfile = TFile::Open(filename); //in current dir
      if (hfile) return hfile;
   }
   */

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

   TTree *parCand = new TTree("PARCand","ParentCandidate");

   parCand->Branch("area1",&trk_area1,"area1/I");
   parCand->Branch("area2",&trk_area2,"area2/I");
   parCand->Branch("txpeak",&trk_txpeak,"txpeak/F");
   parCand->Branch("typeak",&trk_typeak,"typeak/F");
   parCand->Branch("i",&trk_i,"i/I");
   parCand->Branch("vx",&trk_vx,"vx/F");
   parCand->Branch("vy",&trk_vy,"vy/F");
   parCand->Branch("vz",&trk_vz,"vz/F");
   parCand->Branch("Par9",&Par9,"Par9/F");
   parCand->Branch("trk_id",&ParC_id,"trk_id/I");
   parCand->Branch("Par11",&Par11,"Par11/I");
   parCand->Branch("Par12",&Par12,"Par12/I");
   parCand->Branch("Par13",&Par13,"Par13/F");
   parCand->Branch("Par14",&Par14,"Par14/F");
   parCand->Branch("Par15",&Par15,"Par15/I");
   //parCand->Branch("Par16",&Par16,"Par16/F");
   parCand->Branch("ip_pos05",&ip_pos05,"ip_pos05/F");
   //parCand->Branch("Par18",&Par18,"Par18/F");
   parCand->Branch("ip_pos04",&ip_pos04,"ip_pos04/F");
   //parCand->Branch("Par20",&Par20,"Par20/F");
   parCand->Branch("ntrk_small",&ntrk_small,"ntrk_small/I");
   //parCand->Branch("Par22",&Par22,"Par22/F");
   parCand->Branch("dt",&trk_dt,"dt/F");
   //parCand->Branch("Par24",&Par24,"Par24/F");
   parCand->Branch("dt_pos",&dt_pos,"dt_pos/F");
   parCand->Branch("Par26",&Par26,"Par26/I");
   parCand->Branch("Par27",&Par27,"Par27/I");
   parCand->Branch("Par28",&Par28,"Par28/I");
   parCand->Branch("Par29",&Par29,"Par29/I");

   int VtxId = 0, chldNum = 0;
   char line[1024];

   int vNum = 0, pNum = 0, tNum = 0;

   while (fgets(line,1024,fp)) 
   {
      sscanf(&line[0],"%s ",type);
      if(strcmp(type,"1ry_vtx") == 0)
      {
         sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %d %d %f",&vtx_area1,&vtx_area2,&vtx_txpeak,&vtx_typeak,&vtx_i,&vtx_vx,&vtx_vy,&vtx_vz,&vtx_n_1ry_pl,&vtx_flagw,&vtx_n_1ry_trk,
            &vtx_n_1ry_parent_cut0,&vtx_n_1ry_parent_dmin_cut,&vtx_n_1ry_parent_dmin_cut_dt_cut,&vtx_dt);

         chldNum = 0;
         
         if (trk_n_1ry_parent_dmin_cut == 1)
         {
            VtxId++;
            vtx_vID = VtxId;
         }
      }
      else if (strcmp(type,"parent_cand") == 0)
      {
         sscanf(&line[16],"%d %d %f %f %d %f %f %f %f %d %d %d %f %f %d %s %f %s %f %s %d %s %f %s %f %d %d %d %d",&ParC_area1,&ParC_area2,&ParC_txpeak,&ParC_typeak,&ParC_i,&ParC_vx,&ParC_vy,&ParC_vz,&Par9,
            &ParC_id,&Par11,&Par12,&Par13,&Par14,&Par15,&ipChar05[16],&ip_pos05,&ipChar04[16],&ip_pos04,&ntrk_smallChar[16],&ntrk_small,&dtChar[16],&ParC_dt,
            &dt_posChar[16],&dt_pos,&Par26,&Par27,&Par28,&Par29);

         /*
         if (trk_n_1ry_parent_dmin_cut == 1)
         {
            trk_vID = VtxId+1;
            parCand->Fill();
            cout << trk_vID << "-> ParCand: " << trk_id << endl;
         }
         */
      }
      else if(strcmp(type,"1ry_trk") == 0)
      {
         sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %f %d %d %d %f %f %f %f %d %f %f %f %f",&trk_area1,&trk_area2,&trk_txpeak,&trk_typeak,&trk_i,&trk_vx,&trk_vy,&trk_vz,&trk_flagw,&trk_n_1ry_trk,
            &trk_n_1ry_parent_cut0,&trk_n_1ry_parent_dmin_cut,&trk_dz,&trk_id,&trk_plt_of_1seg,&trk_seg_id_of_1seg,&trk_seg_x,&trk_seg_y,&trk_tx,&trk_ty,&trk_nseg,&trk_ip_to_1ry_using_1stseg,
            &trk_ip_to_1ry_using_2ndseg,&trk_ph_mean,&trk_dtrms1_trk);
         
         if (trk_n_1ry_parent_dmin_cut == 1)
         {
            chldNum++;
            trk_vID = VtxId;

            tNum++;

            if (chldNum == trk_n_1ry_trk)
            {
               par->Fill();
               vtx->Fill();
               parCand->Fill();

               pNum++;
               vNum++;

            }
            trk->Fill();
         }
      }
      
   }
   vtx->Print();
   trk->Print();
   par->Print();
   parCand->Print();

   vtx->Write();
   trk->Write();
   par->Write();
   parCand->Write();

   fclose(fp);
   delete hfile;
   
   hfile = TFile::Open(filename);

   cout << "Vertex Size: " << vNum << ", Parent Size: " << pNum << ", Track Size: " << tNum << endl;
   return hfile;
}
