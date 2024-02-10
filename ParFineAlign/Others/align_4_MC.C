void All_limits_G4_reco_bt_001_040()
{
    const int N=31;// the number of plates+1
    int TotalColumns = 9;
    int TotalRows = 7;

    char* firstline1; //INCLUDE
    char* firstnext;  //default.par
    char* layer;    //ZLAYER
    double l1;
    double l2; //the middle of the plastic base 
    double l3;
    double l4;
    char*  position; //AFFXY;
    double p1;
    double p2;
    double p3; 
    double p4;
    double p5;
    double p6;
    double p7;

    //for pe toate subareas, se alege subarea X , x de la 1 la 63
    //for pe toate fisierele care au subarea X, adica pe toate placile  i de la 1 la N ; 
    cout << "Start"<<endl;


   //for(int x=1;x<=63;x++).
    //{
        Double32_t middlebase[N],

        leftbase[N],
        rightbase[N],
        
        middlesep[N],
        leftsep[N],
        rightsep[N],
        
        middleT[N],
        leftT[N],
        rightT[N],
        
        EmRight[N],
        EmLeft[N];

        for (int i=1; i<N;i++)
        {

            ifstream f;

            char filename[100];
            //int currentRow = 5000 + (x-1)%TotalColumns * 15000;
            //int currentColumn = 5000 + (x-1)/TotalColumns * 15000;
            sprintf(filename, "/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040/pl001_030/par/%02d_001.par",i);
            ///home/miloi/reconstructed_Tomoko/Collaboration Meeting june 2022/20220610_data_MC/MC_Fluka

            f.open(filename);

            if (f.is_open())
            {
                cout << "Is open "<< filename<<endl; 
             firstline1= (char*)calloc(10, 1);
             firstnext= (char*)calloc(10, 1);
             layer= (char*)calloc(10, 1);
             position= (char*)calloc(10, 1);

             f>>firstline1;
             f>>firstnext;
             f>>layer;
             f>>l1;
             f>>l2;
             f>>l3;
             f>>l4;
             f>>position;
             f>>p1;
             f>>p2;
             f>>p3;
             f>>p4;
             f>>p5;
             f>>p6;
             f>>p7;
            
             middlebase[i]=l2;

             leftbase[i] = middlebase[i]-105;  // left border of the i-th base
             rightbase[i] = middlebase[i]+105; //right corner of the i-th base 

             //cout<<setprecision(10)<<middlebase[i]<<" " <<leftbase[i]<<"  "<<rightbase[i]<<endl;
             
             f.close();

            }
        } // pe toate placile din subarea X
        
        
        for(int i=1;i<N;i++) // calculezi toate limitele din subarea x
        {
            if(leftbase[i+1]-rightbase[i] < 500)
            {
                //the middle of the separator plate
                middlesep[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the separator plate
                leftsep[i] = middlesep[i]-95;   //-100
                rightsep[i] = middlesep[i]+95;  //100
                
                
                //emulsion thickness
                EmRight[i] = leftsep[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightsep[i]; 
            }
            else
              if (i<106)
                {
                //the middle of the Tungsten plate
                middleT[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the Tungsten plate
                leftT[i] = middleT[i]-250;
                rightT[i] = middleT[i]+250;
                
                //emulsion thickness
                EmRight[i] = leftT[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightT[i];
                
                leftsep[i] = leftT[i];
                rightsep[i] = rightT[i];
                }
        }

        ofstream myfilep;
        char outfilenamep[100];
        sprintf(outfilenamep,"limits_G4_reco-bt-001_040_pl001_030_Plastic.txt");
        cout << "Writting "<< outfilenamep<<endl;
        myfilep.open (outfilenamep);

        for(int i=1;i<N;i++)
        {
            myfilep<<leftbase[i]<<"   "<<rightbase[i]<<endl;
            if(i%10!=5)
                myfilep<<leftsep[i]<<"   "<<rightsep[i]<<endl;
        }
        
        myfilep.close();


        ofstream myfilet;
        char outfilenamet[100];
        sprintf(outfilenamet,"limits_G4_reco-bt-001_040_pl001_030_Tungsten.txt");
        cout << "Writting "<< outfilenamet<<endl;
        myfilet.open (outfilenamet);

        for(int i=1;i<N;i++)
      
            if(i%10==5)
                myfilet<<leftT[i]<<"   "<<rightT[i]<<endl;
        
        myfilet.close();


        ofstream myfilee;
        char outfilenamee[100];
        sprintf(outfilenamee,"limits_G4_reco-bt-001_040_pl001_030_Emulsion.txt");
        cout << "Writting "<< outfilenamee<<endl;
        myfilee.open (outfilenamee);

        for(int i=1;i<N;i++)
        {
            myfilee<<rightsep[i-1]<<"   "<<leftbase[i]<<endl;
            myfilee<<rightbase[i]<<"   "<<leftsep[i]<<endl;
        }
        myfilee.close();
   // }
}
   
void limits_G4_reco_bt_001_040()
{
    ifstream fp;
    char Plastic[100];  
    sprintf(Plastic,"limits_G4_reco-bt-001_040_pl001_030_Plastic.txt");
    fp.open (Plastic);
    if (fp.is_open()) cout << "Is open "<< Plastic<<endl;
    //fp.open("/limits_sub/limits_subarea_%d_PD16_Plastic.txt");
    for(int iii=1;iii<=57;iii++)
        fp>>plg[iii]>>prg[iii];
    
    fp.close();  

    ifstream fe;
    char Emulsion[100];
    sprintf(Emulsion,"limits_G4_reco-bt-001_040_pl001_030_Emulsion.txt");
    fe.open (Emulsion);
    if (fe.is_open()) cout << "Is open "<< Emulsion<<endl;
    for(int ij=1;ij<=60;ij++)
       fe>>elg[ij]>>erg[ij];
    fe.close();  

    ifstream ft;
    char Tungsten[100];
    sprintf(Tungsten,"limits_G4_reco-bt-001_040_pl001_030_Tungsten.txt");
    ft.open (Tungsten); 
    if (ft.is_open()) cout << "Is open "<< Tungsten<<endl;
    for(int ijj=1;ijj<=3;ijj++)
        ft>>tlg[ijj]>>trg[ijj];

    ft.close();  
}  

void ZVertex_G4_reco_bt_001_040()
{   
   //All_limits_G4_reco_bt_001_040();
   limits_G4_reco_bt_001_040();

    h_align = new TH1F("h_old","h_old",290,2200,8000);
    h_align->GetXaxis()->SetTitle("mkm");
    h_align->GetXaxis()->SetTitleSize(0.06);
    h_align-> GetXaxis() -> SetTitleOffset(0.7);
    h_align-> GetXaxis() ->SetTickLength(0.009);
    h_align->GetXaxis()->SetLabelSize(0.04);
    h_align-> GetYaxis() ->SetTickLength(0.009);

    double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
    //int area=0;
    int nr_W=0, nr_emu=0, nr_pl=0;

    ifstream f;
    string line;
    f.open("/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040/pl001_030/vtx_20220912_nods.dat");
 
    if (f.is_open())
    {
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
        float* s23; //ip_to_1ry_using_pos, skipping 1st seg
        float* s24;   //ip_to_1ry_using_1st_seg
        float* s25;    //ip_to_1ry_using_2nd_seg
        char *s26; //ph_mean
        float* s27;  //dtrms1_trk
        
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
                s24 = (float*)calloc(p8+1, sizeof(float));  
                s25 = (float*)calloc(p8+1, sizeof(float));  
                s26 = (char*)calloc(p8+1, sizeof(char));  
                s27 = (float*)calloc(p8+1, sizeof(float));  

                //Reading p5 elements
                int i = -1;//contorul de secunzi
                //f >> paritate; 

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
                    f >> paritate;
                    f >> s27[i];
                }
                //margins,parent,z position
                i++;
              
               if (p13>0)
                {   
                   // if(area==p1)
                    {
                      //Tungsten
                      for(int j=1;j<=1;j++)
                        if(p8>tlg[j] && p8<=trg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_W++;
                        }

                      //Emulsion
                      for(int j=1;j<30;j++)
                       if(p8>elg[j] && p8<=erg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_emu++;
                        }

                      //Plastic
                      for(int j=1;j<29;j++)
                        if(p8>plg[j] && p8<=prg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_pl++;
                        } 
                    }

                }
                
                free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
                free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
                free(s20); free(s21); free(s22);  
                
            }
             //f >> paritate;
        }

        //draw_hist_G4(p1);

    }
    else
        cout << "Unable to open file";
    f.close();


    cout<<"interactions in tungsten "<<nr_W<<endl;
    cout<<"interactions in emulsion "<<nr_emu<<endl;
    cout<<"interactions in plastic "<<nr_pl<<endl;

    TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
    TCanvas *c3 = new TCanvas("c3","cLng", 700,400);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit();


    h_align->SetLineColor(kBlack);
    h_align->SetLineWidth(1);
    h_align->Draw();

    int max= h_align->GetMaximum(); 
    //h_all->Draw("sames");

    max=max+1; //to fill untill the frame 

     for(int i=10;i<30; i++)
     {
        //emulsion
        TBox *pe = new TBox(elg[i],0,erg[i],max);
        pe->SetFillStyle(3001);
        pe->SetFillColor(kBlue);//600
        //pe->SetBorderSize(0);
        pe->Draw();
        
     }

     for(int i=9;i<28; i++)
     {
        //plastic
        TBox *pp = new TBox(plg[i],0,prg[i],max);
        pp->SetFillStyle(3001);
        pp->SetFillColor(kGreen); //416
        //pp->SetBorderSize(0);
        pp->Draw();
        
     }

     for(int i=1;i<=1; i++)
     {
        TPaveText *pt = new TPaveText(tlg[i],0,trg[i],max);
        pt->SetFillStyle(3001);
        pt->SetFillColor(920);
        pt->SetBorderSize(0);
        pt->Draw();
     }

   h_align->Draw("sames");

 c3->Modified(); c3->Update();
 TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);

 t3->AddText("Vertices in the depth of detector Geant4");
 t3->SetTextSize(0.06);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->Draw();
 c3->Print("G4_reco-bt-001_040_pl001_030.pdf");
}

void All_limits_G4_reco_bt_001_040_mt()
{
    const int N=31;// the number of plates+1
    int TotalColumns = 9;
    int TotalRows = 7;

    char* firstline1; //INCLUDE
    char* firstnext;  //default.par
    char* layer;    //ZLAYER
    double l1;
    double l2; //the middle of the plastic base 
    double l3;
    double l4;
    char*  position; //AFFXY;
    double p1;
    double p2;
    double p3; 
    double p4;
    double p5;
    double p6;
    double p7;

    //for pe toate subareas, se alege subarea X , x de la 1 la 63
    //for pe toate fisierele care au subarea X, adica pe toate placile  i de la 1 la N ; 
    cout << "Start"<<endl;


   //for(int x=1;x<=63;x++).
    //{
        Double32_t middlebase[N],

        leftbase[N],
        rightbase[N],
        
        middlesep[N],
        leftsep[N],
        rightsep[N],
        
        middleT[N],
        leftT[N],
        rightT[N],
        
        EmRight[N],
        EmLeft[N];

        for (int i=1; i<N;i++)
        {

            ifstream f;

            char filename[100];
            //int currentRow = 5000 + (x-1)%TotalColumns * 15000;
            //int currentColumn = 5000 + (x-1)/TotalColumns * 15000;
            sprintf(filename, "/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040-mt/pl001_030/par/%02d_001.par",i);
            ///home/miloi/reconstructed_Tomoko/Collaboration Meeting june 2022/20220610_data_MC/MC_Fluka

            f.open(filename);

            if (f.is_open())
            {
                cout << "Is open "<< filename<<endl; 
             firstline1= (char*)calloc(10, 1);
             firstnext= (char*)calloc(10, 1);
             layer= (char*)calloc(10, 1);
             position= (char*)calloc(10, 1);

             f>>firstline1;
             f>>firstnext;
             f>>layer;
             f>>l1;
             f>>l2;
             f>>l3;
             f>>l4;
             f>>position;
             f>>p1;
             f>>p2;
             f>>p3;
             f>>p4;
             f>>p5;
             f>>p6;
             f>>p7;
            
             middlebase[i]=l2;

             leftbase[i] = middlebase[i]-105;  // left border of the i-th base
             rightbase[i] = middlebase[i]+105; //right corner of the i-th base 

             //cout<<setprecision(10)<<middlebase[i]<<" " <<leftbase[i]<<"  "<<rightbase[i]<<endl;
             
             f.close();

            }
        } // pe toate placile din subarea X
        
        
        for(int i=1;i<N;i++) // calculezi toate limitele din subarea x
        {
            if(leftbase[i+1]-rightbase[i] < 500)
            {
                //the middle of the separator plate
                middlesep[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the separator plate
                leftsep[i] = middlesep[i]-95;   //-100
                rightsep[i] = middlesep[i]+95;  //100
                
                
                //emulsion thickness
                EmRight[i] = leftsep[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightsep[i]; 
            }
            else
              if (i<106)
                {
                //the middle of the Tungsten plate
                middleT[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the Tungsten plate
                leftT[i] = middleT[i]-250;
                rightT[i] = middleT[i]+250;
                
                //emulsion thickness
                EmRight[i] = leftT[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightT[i];
                
                leftsep[i] = leftT[i];
                rightsep[i] = rightT[i];
                }
        }

        ofstream myfilep;
        char outfilenamep[100];
        sprintf(outfilenamep,"limits_G4_reco-bt-001_040_mt_pl001_030_Plastic.txt");
        cout << "Writting "<< outfilenamep<<endl;
        myfilep.open (outfilenamep);

        for(int i=1;i<N;i++)
        {
            myfilep<<leftbase[i]<<"   "<<rightbase[i]<<endl;
            if(i%10!=5)
                myfilep<<leftsep[i]<<"   "<<rightsep[i]<<endl;
        }
        
        myfilep.close();


        ofstream myfilet;
        char outfilenamet[100];
        sprintf(outfilenamet,"limits_G4_reco-bt-001_040_mt_pl001_030_Tungsten.txt");
        cout << "Writting "<< outfilenamet<<endl;
        myfilet.open (outfilenamet);

        for(int i=1;i<N;i++)
      
            if(i%10==5)
                myfilet<<leftT[i]<<"   "<<rightT[i]<<endl;
        
        myfilet.close();


        ofstream myfilee;
        char outfilenamee[100];
        sprintf(outfilenamee,"limits_G4_reco-bt-001_040_mt_pl001_030_Emulsion.txt");
        cout << "Writting "<< outfilenamee<<endl;
        myfilee.open (outfilenamee);

        for(int i=1;i<N;i++)
        {
            myfilee<<rightsep[i-1]<<"   "<<leftbase[i]<<endl;
            myfilee<<rightbase[i]<<"   "<<leftsep[i]<<endl;
        }
        myfilee.close();
   // }
}
   
void limits_G4_reco_bt_001_040_mt()
{
    ifstream fp;
    char Plastic[100];  
    sprintf(Plastic,"limits_G4_reco-bt-001_040_mt_pl001_030_Plastic.txt");
    fp.open (Plastic);
    if (fp.is_open()) cout << "Is open "<< Plastic<<endl;
    //fp.open("/limits_sub/limits_subarea_%d_PD16_Plastic.txt");
    for(int iii=1;iii<=57;iii++)
        fp>>plg[iii]>>prg[iii];
    
    fp.close();  

    ifstream fe;
    char Emulsion[100];
    sprintf(Emulsion,"limits_G4_reco-bt-001_040_mt_pl001_030_Emulsion.txt");
    fe.open (Emulsion);
    if (fe.is_open()) cout << "Is open "<< Emulsion<<endl;
    for(int ij=1;ij<=60;ij++)
       fe>>elg[ij]>>erg[ij];
    fe.close();  

    ifstream ft;
    char Tungsten[100];
    sprintf(Tungsten,"limits_G4_reco-bt-001_040_mt_pl001_030_Tungsten.txt");
    ft.open (Tungsten); 
    if (ft.is_open()) cout << "Is open "<< Tungsten<<endl;
    for(int ijj=1;ijj<=3;ijj++)
        ft>>tlg[ijj]>>trg[ijj];

    ft.close();  
}  

void ZVertex_G4_reco_bt_001_040_mt()
{   
   All_limits_G4_reco_bt_001_040_mt();
   limits_G4_reco_bt_001_040_mt();

    h_align = new TH1F("h_mt","h_mt",290,2200,8000);
    h_align->GetXaxis()->SetTitle("mkm");
    h_align->GetXaxis()->SetTitleSize(0.06);
    h_align-> GetXaxis() -> SetTitleOffset(0.7);
    h_align-> GetXaxis() ->SetTickLength(0.009);
    h_align->GetXaxis()->SetLabelSize(0.04);
    h_align-> GetYaxis() ->SetTickLength(0.009);

    double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
    //int area=0;
    int nr_W=0, nr_emu=0, nr_pl=0;

    ifstream f;
    string line;
    f.open("/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040-mt/pl001_030/vtx_20220912_nods.dat");
 
    if (f.is_open())
    {
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
        float* s23; //ip_to_1ry_using_pos, skipping 1st seg
        float* s24;   //ip_to_1ry_using_1st_seg
        float* s25;    //ip_to_1ry_using_2nd_seg
        char *s26; //ph_mean
        float* s27;  //dtrms1_trk
        
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
                s24 = (float*)calloc(p8+1, sizeof(float));  
                s25 = (float*)calloc(p8+1, sizeof(float));  
                s26 = (char*)calloc(p8+1, sizeof(char));  
                s27 = (float*)calloc(p8+1, sizeof(float));  

                //Reading p5 elements
                int i = -1;//contorul de secunzi
                //f >> paritate; 

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
                    f >> paritate;
                    f >> s27[i];
                }
                //margins,parent,z position
                i++;
              
               if (p13>0)
                {   
                   // if(area==p1)
                    {
                      //Tungsten
                      for(int j=1;j<=1;j++)
                        if(p8>tlg[j] && p8<=trg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_W++;
                        }

                      //Emulsion
                      for(int j=1;j<30;j++)
                       if(p8>elg[j] && p8<=erg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_emu++;
                        }

                      //Plastic
                      for(int j=1;j<29;j++)
                        if(p8>plg[j] && p8<=prg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_pl++;
                        } 
                    }

                }
                
                free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
                free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
                free(s20); free(s21); free(s22);  
                
            }
             //f >> paritate;
        }

        //draw_hist_G4(p1);

    }
    else
        cout << "Unable to open file";
    f.close();


    cout<<"interactions in tungsten "<<nr_W<<endl;
    cout<<"interactions in emulsion "<<nr_emu<<endl;
    cout<<"interactions in plastic "<<nr_pl<<endl;

    TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
    TCanvas *c3 = new TCanvas("c3","cLng", 700,400);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit();


    h_align->SetLineColor(kBlack);
    h_align->SetLineWidth(1);
    h_align->Draw();

    int max= h_align->GetMaximum(); 
    //h_all->Draw("sames");

    max=max+1; //to fill untill the frame 

     for(int i=10;i<30; i++)
     {
        //emulsion
        TBox *pe = new TBox(elg[i],0,erg[i],max);
        pe->SetFillStyle(3001);
        pe->SetFillColor(kBlue);//600
        //pe->SetBorderSize(0);
        pe->Draw();
        
     }

     for(int i=9;i<28; i++)
     {
        //plastic
        TBox *pp = new TBox(plg[i],0,prg[i],max);
        pp->SetFillStyle(3001);
        pp->SetFillColor(kGreen); //416
        //pp->SetBorderSize(0);
        pp->Draw();
        
     }

     for(int i=1;i<=1; i++)
     {
        TPaveText *pt = new TPaveText(tlg[i],0,trg[i],max);
        pt->SetFillStyle(3001);
        pt->SetFillColor(920);
        pt->SetBorderSize(0);
        pt->Draw();
     }

   h_align->Draw("sames");

 c3->Modified(); c3->Update();
 TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);

 t3->AddText("Vertices in the depth of detector Geant4");
 t3->SetTextSize(0.06);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->Draw();
 c3->Print("G4_reco-bt-001_040_mt_pl001_030.pdf");
}

void All_limits_G4_reco_bt_001_040_new()
{
    const int N=31;// the number of plates+1
    int TotalColumns = 9;
    int TotalRows = 7;

    char* firstline1; //INCLUDE
    char* firstnext;  //default.par
    char* layer;    //ZLAYER
    double l1;
    double l2; //the middle of the plastic base 
    double l3;
    double l4;
    char*  position; //AFFXY;
    double p1;
    double p2;
    double p3; 
    double p4;
    double p5;
    double p6;
    double p7;

    //for pe toate subareas, se alege subarea X , x de la 1 la 63
    //for pe toate fisierele care au subarea X, adica pe toate placile  i de la 1 la N ; 
    cout << "Start"<<endl;


   //for(int x=1;x<=63;x++).
    //{
        Double32_t middlebase[N],

        leftbase[N],
        rightbase[N],
        
        middlesep[N],
        leftsep[N],
        rightsep[N],
        
        middleT[N],
        leftT[N],
        rightT[N],
        
        EmRight[N],
        EmLeft[N];

        for (int i=1; i<N;i++)
        {

            ifstream f;

            char filename[100];
            //int currentRow = 5000 + (x-1)%TotalColumns * 15000;
            //int currentColumn = 5000 + (x-1)/TotalColumns * 15000;
            sprintf(filename, "/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040_new_smearing/pl001_030/par/%02d_001.par",i);
            ///home/miloi/reconstructed_Tomoko/Collaboration Meeting june 2022/20220610_data_MC/MC_Fluka

            f.open(filename);

            if (f.is_open())
            {
                cout << "Is open "<< filename<<endl; 
             firstline1= (char*)calloc(10, 1);
             firstnext= (char*)calloc(10, 1);
             layer= (char*)calloc(10, 1);
             position= (char*)calloc(10, 1);

             f>>firstline1;
             f>>firstnext;
             f>>layer;
             f>>l1;
             f>>l2;
             f>>l3;
             f>>l4;
             f>>position;
             f>>p1;
             f>>p2;
             f>>p3;
             f>>p4;
             f>>p5;
             f>>p6;
             f>>p7;
            
             middlebase[i]=l2;

             leftbase[i] = middlebase[i]-105;  // left border of the i-th base
             rightbase[i] = middlebase[i]+105; //right corner of the i-th base 

             //cout<<setprecision(10)<<middlebase[i]<<" " <<leftbase[i]<<"  "<<rightbase[i]<<endl;
             
             f.close();

            }
        } // pe toate placile din subarea X
        
        
        for(int i=1;i<N;i++) // calculezi toate limitele din subarea x
        {
            if(leftbase[i+1]-rightbase[i] < 500)
            {
                //the middle of the separator plate
                middlesep[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the separator plate
                leftsep[i] = middlesep[i]-95;   //-100
                rightsep[i] = middlesep[i]+95;  //100
                
                
                //emulsion thickness
                EmRight[i] = leftsep[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightsep[i]; 
            }
            else
              if (i<106)
                {
                //the middle of the Tungsten plate
                middleT[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the Tungsten plate
                leftT[i] = middleT[i]-250;
                rightT[i] = middleT[i]+250;
                
                //emulsion thickness
                EmRight[i] = leftT[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightT[i];
                
                leftsep[i] = leftT[i];
                rightsep[i] = rightT[i];
                }
        }

        ofstream myfilep;
        char outfilenamep[100];
        sprintf(outfilenamep,"limits_G4_reco-bt-001_040_new_pl001_030_Plastic.txt");
        cout << "Writting "<< outfilenamep<<endl;
        myfilep.open (outfilenamep);

        for(int i=1;i<N;i++)
        {
            myfilep<<leftbase[i]<<"   "<<rightbase[i]<<endl;
            if(i%10!=5)
                myfilep<<leftsep[i]<<"   "<<rightsep[i]<<endl;
        }
        
        myfilep.close();


        ofstream myfilet;
        char outfilenamet[100];
        sprintf(outfilenamet,"limits_G4_reco-bt-001_040_new_pl001_030_Tungsten.txt");
        cout << "Writting "<< outfilenamet<<endl;
        myfilet.open (outfilenamet);

        for(int i=1;i<N;i++)
      
            if(i%10==5)
                myfilet<<leftT[i]<<"   "<<rightT[i]<<endl;
        
        myfilet.close();


        ofstream myfilee;
        char outfilenamee[100];
        sprintf(outfilenamee,"limits_G4_reco-bt-001_040_new_pl001_030_Emulsion.txt");
        cout << "Writting "<< outfilenamee<<endl;
        myfilee.open (outfilenamee);

        for(int i=1;i<N;i++)
        {
            myfilee<<rightsep[i-1]<<"   "<<leftbase[i]<<endl;
            myfilee<<rightbase[i]<<"   "<<leftsep[i]<<endl;
        }
        myfilee.close();
   // }
}
   
void limits_G4_reco_bt_001_040_new()
{
    ifstream fp;
    char Plastic[100];  
    sprintf(Plastic,"limits_G4_reco-bt-001_040_new_pl001_030_Plastic.txt");
    fp.open (Plastic);
    if (fp.is_open()) cout << "Is open "<< Plastic<<endl;
    //fp.open("/limits_sub/limits_subarea_%d_PD16_Plastic.txt");
    for(int iii=1;iii<=57;iii++)
        fp>>plg[iii]>>prg[iii];
    
    fp.close();  

    ifstream fe;
    char Emulsion[100];
    sprintf(Emulsion,"limits_G4_reco-bt-001_040_new_pl001_030_Emulsion.txt");
    fe.open (Emulsion);
    if (fe.is_open()) cout << "Is open "<< Emulsion<<endl;
    for(int ij=1;ij<=60;ij++)
       fe>>elg[ij]>>erg[ij];
    fe.close();  

    ifstream ft;
    char Tungsten[100];
    sprintf(Tungsten,"limits_G4_reco-bt-001_040_new_pl001_030_Tungsten.txt");
    ft.open (Tungsten); 
    if (ft.is_open()) cout << "Is open "<< Tungsten<<endl;
    for(int ijj=1;ijj<=3;ijj++)
        ft>>tlg[ijj]>>trg[ijj];

    ft.close();  
}  

void ZVertex_G4_reco_bt_001_040_new()
{   
   All_limits_G4_reco_bt_001_040_new();
   limits_G4_reco_bt_001_040_new();

    h_align = new TH1F("h_new","h_new",290,2200,8000);
    h_align->GetXaxis()->SetTitle("mkm");
    h_align->GetXaxis()->SetTitleSize(0.06);
    h_align-> GetXaxis() -> SetTitleOffset(0.7);
    h_align-> GetXaxis() ->SetTickLength(0.009);
    h_align->GetXaxis()->SetLabelSize(0.04);
    h_align-> GetYaxis() ->SetTickLength(0.009);

    double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
    //int area=0;
    int nr_W=0, nr_emu=0, nr_pl=0;

    ifstream f;
    string line;
    f.open("/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040_new_smearing/pl001_030/vtx_20220912_nods.dat");
 
    if (f.is_open())
    {
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
        float* s23; //ip_to_1ry_using_pos, skipping 1st seg
        float* s24;   //ip_to_1ry_using_1st_seg
        float* s25;    //ip_to_1ry_using_2nd_seg
        char *s26; //ph_mean
        float* s27;  //dtrms1_trk
        
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
                s24 = (float*)calloc(p8+1, sizeof(float));  
                s25 = (float*)calloc(p8+1, sizeof(float));  
                s26 = (char*)calloc(p8+1, sizeof(char));  
                s27 = (float*)calloc(p8+1, sizeof(float));  

                //Reading p5 elements
                int i = -1;//contorul de secunzi
                //f >> paritate; 

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
                    f >> paritate;
                    f >> s27[i];
                }
                //margins,parent,z position
                i++;
              
               if (p13>0)
                {   
                   // if(area==p1)
                    {
                      //Tungsten
                      for(int j=1;j<=1;j++)
                        if(p8>tlg[j] && p8<=trg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_W++;
                        }

                      //Emulsion
                      for(int j=1;j<30;j++)
                       if(p8>elg[j] && p8<=erg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_emu++;
                        }

                      //Plastic
                      for(int j=1;j<29;j++)
                        if(p8>plg[j] && p8<=prg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_pl++;
                        } 
                    }

                }
                
                free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
                free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
                free(s20); free(s21); free(s22);  
                
            }
             //f >> paritate;
        }

        //draw_hist_G4(p1);

    }
    else
        cout << "Unable to open file";
    f.close();


    cout<<"interactions in tungsten "<<nr_W<<endl;
    cout<<"interactions in emulsion "<<nr_emu<<endl;
    cout<<"interactions in plastic "<<nr_pl<<endl;

    TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
    TCanvas *c3 = new TCanvas("c3","cLng", 700,400);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit();


    h_align->SetLineColor(kBlack);
    h_align->SetLineWidth(1);
    h_align->Draw();

    int max= h_align->GetMaximum(); 
    //h_all->Draw("sames");

    max=max+1; //to fill untill the frame 

     for(int i=10;i<30; i++)
     {
        //emulsion
        TBox *pe = new TBox(elg[i],0,erg[i],max);
        pe->SetFillStyle(3001);
        pe->SetFillColor(kBlue);//600
        //pe->SetBorderSize(0);
        pe->Draw();
        
     }

     for(int i=9;i<28; i++)
     {
        //plastic
        TBox *pp = new TBox(plg[i],0,prg[i],max);
        pp->SetFillStyle(3001);
        pp->SetFillColor(kGreen); //416
        //pp->SetBorderSize(0);
        pp->Draw();
        
     }

     for(int i=1;i<=1; i++)
     {
        TPaveText *pt = new TPaveText(tlg[i],0,trg[i],max);
        pt->SetFillStyle(3001);
        pt->SetFillColor(920);
        pt->SetBorderSize(0);
        pt->Draw();
     }

   h_align->Draw("sames");

 c3->Modified(); c3->Update();
 TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);

 t3->AddText("Vertices in the depth of detector Geant4");
 t3->SetTextSize(0.06);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->Draw();
 c3->Print("G4_reco-bt-001_040_new_pl001_030.pdf");
}

void All_limits_G4_reco_bt_001_040_mt_new()
{
    const int N=31;// the number of plates+1
    int TotalColumns = 9;
    int TotalRows = 7;

    char* firstline1; //INCLUDE
    char* firstnext;  //default.par
    char* layer;    //ZLAYER
    double l1;
    double l2; //the middle of the plastic base 
    double l3;
    double l4;
    char*  position; //AFFXY;
    double p1;
    double p2;
    double p3; 
    double p4;
    double p5;
    double p6;
    double p7;

    //for pe toate subareas, se alege subarea X , x de la 1 la 63
    //for pe toate fisierele care au subarea X, adica pe toate placile  i de la 1 la N ; 
    cout << "Start"<<endl;


   //for(int x=1;x<=63;x++).
    //{
        Double32_t middlebase[N],

        leftbase[N],
        rightbase[N],
        
        middlesep[N],
        leftsep[N],
        rightsep[N],
        
        middleT[N],
        leftT[N],
        rightT[N],
        
        EmRight[N],
        EmLeft[N];

        for (int i=1; i<N;i++)
        {

            ifstream f;

            char filename[100];
            //int currentRow = 5000 + (x-1)%TotalColumns * 15000;
            //int currentColumn = 5000 + (x-1)/TotalColumns * 15000;
            sprintf(filename, "/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040-mt_new_smearing/pl001_030/par/%02d_001.par",i);
            ///home/miloi/reconstructed_Tomoko/Collaboration Meeting june 2022/20220610_data_MC/MC_Fluka

            f.open(filename);

            if (f.is_open())
            {
                cout << "Is open "<< filename<<endl; 
             firstline1= (char*)calloc(10, 1);
             firstnext= (char*)calloc(10, 1);
             layer= (char*)calloc(10, 1);
             position= (char*)calloc(10, 1);

             f>>firstline1;
             f>>firstnext;
             f>>layer;
             f>>l1;
             f>>l2;
             f>>l3;
             f>>l4;
             f>>position;
             f>>p1;
             f>>p2;
             f>>p3;
             f>>p4;
             f>>p5;
             f>>p6;
             f>>p7;
            
             middlebase[i]=l2;

             leftbase[i] = middlebase[i]-105;  // left border of the i-th base
             rightbase[i] = middlebase[i]+105; //right corner of the i-th base 

             //cout<<setprecision(10)<<middlebase[i]<<" " <<leftbase[i]<<"  "<<rightbase[i]<<endl;
             
             f.close();

            }
        } // pe toate placile din subarea X
        
        
        for(int i=1;i<N;i++) // calculezi toate limitele din subarea x
        {
            if(leftbase[i+1]-rightbase[i] < 500)
            {
                //the middle of the separator plate
                middlesep[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the separator plate
                leftsep[i] = middlesep[i]-95;   //-100
                rightsep[i] = middlesep[i]+95;  //100
                
                
                //emulsion thickness
                EmRight[i] = leftsep[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightsep[i]; 
            }
            else
              if (i<106)
                {
                //the middle of the Tungsten plate
                middleT[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                
                //the limits of the Tungsten plate
                leftT[i] = middleT[i]-250;
                rightT[i] = middleT[i]+250;
                
                //emulsion thickness
                EmRight[i] = leftT[i]-rightbase[i];
                EmLeft[i+1] = leftbase[i+1]-rightT[i];
                
                leftsep[i] = leftT[i];
                rightsep[i] = rightT[i];
                }
        }

        ofstream myfilep;
        char outfilenamep[100];
        sprintf(outfilenamep,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Plastic.txt");
        cout << "Writting "<< outfilenamep<<endl;
        myfilep.open (outfilenamep);

        for(int i=1;i<N;i++)
        {
            myfilep<<leftbase[i]<<"   "<<rightbase[i]<<endl;
            if(i%10!=5)
                myfilep<<leftsep[i]<<"   "<<rightsep[i]<<endl;
        }
        
        myfilep.close();


        ofstream myfilet;
        char outfilenamet[100];
        sprintf(outfilenamet,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Tungsten.txt");
        cout << "Writting "<< outfilenamet<<endl;
        myfilet.open (outfilenamet);

        for(int i=1;i<N;i++)
      
            if(i%10==5)
                myfilet<<leftT[i]<<"   "<<rightT[i]<<endl;
        
        myfilet.close();


        ofstream myfilee;
        char outfilenamee[100];
        sprintf(outfilenamee,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Emulsion.txt");
        cout << "Writting "<< outfilenamee<<endl;
        myfilee.open (outfilenamee);

        for(int i=1;i<N;i++)
        {
            myfilee<<rightsep[i-1]<<"   "<<leftbase[i]<<endl;
            myfilee<<rightbase[i]<<"   "<<leftsep[i]<<endl;
        }
        myfilee.close();
   // }
}
   
void limits_G4_reco_bt_001_040_mt_new()
{
    ifstream fp;
    char Plastic[100];  
    sprintf(Plastic,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Plastic.txt");
    fp.open (Plastic);
    if (fp.is_open()) cout << "Is open "<< Plastic<<endl;
    //fp.open("/limits_sub/limits_subarea_%d_PD16_Plastic.txt");
    for(int iii=1;iii<=57;iii++)
        fp>>plg[iii]>>prg[iii];
    
    fp.close();  

    ifstream fe;
    char Emulsion[100];
    sprintf(Emulsion,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Emulsion.txt");
    fe.open (Emulsion);
    if (fe.is_open()) cout << "Is open "<< Emulsion<<endl;
    for(int ij=1;ij<=60;ij++)
       fe>>elg[ij]>>erg[ij];
    fe.close();  

    ifstream ft;
    char Tungsten[100];
    sprintf(Tungsten,"limits_G4_reco-bt-001_040-mt_new_pl001_030_Tungsten.txt");
    ft.open (Tungsten); 
    if (ft.is_open()) cout << "Is open "<< Tungsten<<endl;
    for(int ijj=1;ijj<=3;ijj++)
        ft>>tlg[ijj]>>trg[ijj];

    ft.close();  
}  

void ZVertex_G4_reco_bt_001_040_mt_new()
{   
   All_limits_G4_reco_bt_001_040_mt_new();
   limits_G4_reco_bt_001_040_mt_new();

    h_align = new TH1F("h_mt_new","h_mt_new",290,2200,8000);
    h_align->GetXaxis()->SetTitle("mkm");
    h_align->GetXaxis()->SetTitleSize(0.06);
    h_align-> GetXaxis() -> SetTitleOffset(0.7);
    h_align-> GetXaxis() ->SetTickLength(0.009);
    h_align->GetXaxis()->SetLabelSize(0.04);
    h_align-> GetYaxis() ->SetTickLength(0.009);

    double mean_thickness=0, scanned_thickness=0, vertex_correction=0;
    //int area=0;
    int nr_W=0, nr_emu=0, nr_pl=0;

    ifstream f;
    string line;
    f.open("/netdata/MC/Geant4/Hadrons_g4_r102/reco-bt-001_040-mt_new_smearing/pl001_030/vtx_20220912_nods.dat");
 
    if (f.is_open())
    {
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
        float* s23; //ip_to_1ry_using_pos, skipping 1st seg
        float* s24;   //ip_to_1ry_using_1st_seg
        float* s25;    //ip_to_1ry_using_2nd_seg
        char *s26; //ph_mean
        float* s27;  //dtrms1_trk
        
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
                s24 = (float*)calloc(p8+1, sizeof(float));  
                s25 = (float*)calloc(p8+1, sizeof(float));  
                s26 = (char*)calloc(p8+1, sizeof(char));  
                s27 = (float*)calloc(p8+1, sizeof(float));  

                //Reading p5 elements
                int i = -1;//contorul de secunzi
                //f >> paritate; 

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
                    f >> paritate;
                    f >> s27[i];
                }
                //margins,parent,z position
                i++;
              
               if (p13>0)
                {   
                   // if(area==p1)
                    {
                      //Tungsten
                      for(int j=1;j<=1;j++)
                        if(p8>tlg[j] && p8<=trg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_W++;
                        }

                      //Emulsion
                      for(int j=1;j<30;j++)
                       if(p8>elg[j] && p8<=erg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_emu++;
                        }

                      //Plastic
                      for(int j=1;j<29;j++)
                        if(p8>plg[j] && p8<=prg[j]) 
                        {
                            h_align->Fill(p8);
                            nr_pl++;
                        } 
                    }

                }
                
                free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
                free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
                free(s20); free(s21); free(s22);  
                
            }
             //f >> paritate;
        }

        //draw_hist_G4(p1);

    }
    else
        cout << "Unable to open file";
    f.close();


    cout<<"interactions in tungsten "<<nr_W<<endl;
    cout<<"interactions in emulsion "<<nr_emu<<endl;
    cout<<"interactions in plastic "<<nr_pl<<endl;

    TPaveText *t3=new TPaveText (.35,.91,.65,.96, "NDC"); 
    TCanvas *c3 = new TCanvas("c3","cLng", 700,400);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit();


    h_align->SetLineColor(kBlack);
    h_align->SetLineWidth(1);
    h_align->Draw();

    int max= h_align->GetMaximum(); 
    //h_all->Draw("sames");

    max=max+1; //to fill untill the frame 

     for(int i=10;i<30; i++)
     {
        //emulsion
        TBox *pe = new TBox(elg[i],0,erg[i],max);
        pe->SetFillStyle(3001);
        pe->SetFillColor(kBlue);//600
        //pe->SetBorderSize(0);
        pe->Draw();
        
     }

     for(int i=9;i<28; i++)
     {
        //plastic
        TBox *pp = new TBox(plg[i],0,prg[i],max);
        pp->SetFillStyle(3001);
        pp->SetFillColor(kGreen); //416
        //pp->SetBorderSize(0);
        pp->Draw();
        
     }

     for(int i=1;i<=1; i++)
     {
        TPaveText *pt = new TPaveText(tlg[i],0,trg[i],max);
        pt->SetFillStyle(3001);
        pt->SetFillColor(920);
        pt->SetBorderSize(0);
        pt->Draw();
     }

   h_align->Draw("sames");

 c3->Modified(); c3->Update();
 TPaveStats *stats =(TPaveStats*)c3->GetPrimitive("stats");
   stats->SetName("h1stats");
   stats->SetX1NDC(.82);
   stats->SetX2NDC(.99);
   stats->SetY1NDC(.75);
   stats->SetY2NDC(.95);

 t3->AddText("Vertices in the depth of detector Geant4");
 t3->SetTextSize(0.06);
 t3->SetFillColor(0);
 t3->SetBorderSize(0);
 t3->Draw();
 c3->Print("G4_reco-bt-001_040-mt_new_pl001_030.pdf");
}
