#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

TH1F *h, *h_all, *h_align;
TH1F *hW_G4, *hP_G4,*hE_G4,*hW_F, *hE_F, *hP_F;
TH1F *hW_data, *hP_data,*hE_data;

int evtotW,evtotP,evtotE,evtotALL;
int numWF,numBF,numEF,numALLF;
float sclF, sclFref;
int numrefW,numrefE,numrefP,numrefALL;
double plf[200],prf[200],elf[211],erfluka[211],tlf[11],trf[11];
double plg[200],prg[200],elg[211],erg[211],tlg[11],trg[11];
double pl[200],pr[200],el[211],er[211],tl[11],tr[11];
int Emul[64], Plas[64], Tung[64]; 
double mpl[200],mpr[200], mel[200], mer[200], mtl[200], mtr[200];

void All_limits()
{
    
    //all subvolumes
    //for pe toate subareas, se alege subarea X , x de la 1 la 63
    //for pe toate fisierele care au subarea X, adica pe toate placile  i de la 1 la N ; 
   cout<<"calculatin limits"<<endl;
     int pl2=0;
     int TotalColumns = 9;
    int TotalRows = 7;
    

    for(int pl1=1; pl1<=81; pl1+= 10)
    {
        if(pl1==81) pl2=105;
        else pl2=pl1+29;

        cout<<endl<<pl1<<"  plate subvolume "<<endl;

       for(int x=1;x<=63;x++)
        {
            Double32_t middlebase[120],

            leftbase[120],
            rightbase[120],
            
            middlesep[120],
            leftsep[120],
            rightsep[120],
            
            middleT[120],
            leftT[120],
            rightT[120],
            
            EmRight[120],
            EmLeft[120];

            for (int i=pl1; i<=pl1+11;i++) //i nu e 1 si N e dat de file 
            {
                char* firstline1; //INCLUDE
                char* firstnext;  //default.par
                char* layer;    //ZLAYER
                double l1;
                double l2; //the middle of the plastic base 
                double l3;
                double l4;
                char*  position; //AFFXY;
                int p1;
                int p2;
                int p3; 
                int p4;
                int p5;
                int p6;
                int p7;

                ifstream f;
                char filename[128];
                int currentRow = 5000 + (x-1)%TotalColumns * 15000;
                int currentColumn = 5000 + (x-1)/TotalColumns * 15000;
                snprintf(filename, 128, "../../PD05/ParFineAlign/PR2018_PD05/pl%03d_%03d/reco%02d_%06d_%06d/par_finealign/%02d_001.par",pl1,pl2,x,currentRow,currentColumn,i);
                // cout << "Opening "<< filename<<endl;
                f.open(filename);

                if (f.is_open())
                {
                 
                 //cout<<"Is open: "<<filename<<endl;
                 firstline1= (char*)calloc(12, 1);
                 firstnext= (char*)calloc(13, 1);
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

               // cout<<setprecision(10)<<l2<<" "<<p7<<endl;

                 middlebase[i]=l2;

                 leftbase[i] = middlebase[i]-105;  // left border of the i-th base
                 rightbase[i] = middlebase[i]+105; //right corner of the i-th base 

                // cout<<setprecision(10)<<middlebase[i]<<" " <<leftbase[i]<<"  "<<rightbase[i]<<endl;
                 
                 f.close();
                 cout<<"Closed "<<filename<<endl;
                 free(firstline1); free(firstnext); free(layer); free(position);
                }


            } // pe toate placile din subarea X
            
            
            for(int i=pl1;i<=pl1+10;i++) // calculezi toate limitele din subarea x din subvolume
            {
                if(leftbase[i+1]-rightbase[i] < 500)
                {
                    //the middle of the separator plate
                    middlesep[i] = (leftbase[i+1]-rightbase[i])/2 + rightbase[i];
                    
                    //the limits of the separator plate
                    leftsep[i] = middlesep[i]-100;   //-100
                    rightsep[i] = middlesep[i]+100;  //100
                    
                    
                    //emulsion thickness
                    EmRight[i] = leftsep[i]-rightbase[i];
                    EmLeft[i+1] = leftbase[i+1]-rightsep[i];
                }
                else if (i<106)
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
            char outfilenamep[128];
            snprintf(outfilenamep,128,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Plastic.txt",x, pl1, pl2);
            cout << "Writting "<< outfilenamep<<endl;
            myfilep.open (outfilenamep);

            for(int i=pl1;i<=pl1+10;i++)
            {
                myfilep<<leftbase[i]<<"   "<<rightbase[i]<<endl;
                if(i%10!=5)
                    myfilep<<leftsep[i]<<"   "<<rightsep[i]<<endl;
            }
            
            myfilep.close();


            ofstream myfilet;
            char outfilenamet[128];
            snprintf(outfilenamet,128,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Tungsten.txt",x, pl1, pl2);
            cout << "Writting "<< outfilenamet<<endl;
            myfilet.open (outfilenamet);

            for(int i=pl1;i<pl1+10;i++)
          
                if(i%10==5)
                    myfilet<<leftT[i]<<"   "<<rightT[i]<<endl;
            
            myfilet.close();


            ofstream myfilee;
            char outfilenamee[128];
            snprintf(outfilenamee,128,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Emulsion.txt",x, pl1, pl2);
            cout << "Writting "<< outfilenamee<<endl;
            myfilee.open (outfilenamee);

            for(int i=pl1;i<pl1+10;i++)
            {
                myfilee<<rightsep[i-1]<<"   "<<leftbase[i]<<endl;
                myfilee<<rightbase[i]<<"   "<<leftsep[i]<<endl;
            }
            
            myfilee.close();
        }
    }
}
   
void limits(int subarea, int plt)
{
    //for the first 10 emulsion plates from each subvolume (and plastic and W between them)

    int pl2=0;
    if(plt==81) pl2=105;
    else pl2=plt+29;

    memset(el, 0, sizeof(el));
    memset(er, 0, sizeof(er));
    memset(pl, 0, sizeof(pl));
    memset(pr, 0, sizeof(pr));
    memset(tl, 0, sizeof(tl));
    memset(tr, 0, sizeof(tr));
     
    ifstream fp;
    char Plastic[256];  
    snprintf(Plastic,256,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Plastic.txt",subarea,plt,pl2);
    fp.open (Plastic);
    //if (fp.is_open()) cout << "Opening "<< Plastic<<endl;
    for(int iii=0;iii<20;iii++)
        fp>>pl[iii]>>pr[iii];
        //cout << pl[1] << ", " << pr[1] << endl;
    fp.close();  

    ifstream fe;
    char Emulsion[256];
    snprintf(Emulsion,256,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Emulsion.txt",subarea,plt,pl2);
    fe.open (Emulsion);
    //if (fe.is_open()) cout << "Opening "<< Emulsion<<endl;
    for(int ij=0;ij<=20;ij++)
    {
       fe>>el[ij]>>er[ij];
       //cout << el[ij] << ", " << er[ij] << endl;
    }
    fe.close();  

    ifstream ft;
    char Tungsten[256];
    snprintf(Tungsten,256,"ParFineAlign/limits_PD05/limits_subarea_%0d_PD05_subvolume_%d_%d_Tungsten.txt",subarea,plt,pl2);
    ft.open (Tungsten); 
    //if (ft.is_open()) cout << "Opening "<< Tungsten<<endl;
    for(int ijj=1;ijj<=1;ijj++)
        ft>>tl[ijj]>>tr[ijj];
    ft.close();  
}  

void mean_limits(int plt)
{
    //each material layer, all subareas
    //iterating over all subareas, doing the mean for each left and right boundary of each layer
    //pl gives the subvolume

    //re-initialize the vectors with 0 
    memset(mel, 0, sizeof(mel));
    memset(mer, 0, sizeof(mer));
    memset(mpl, 0, sizeof(mpl));
    memset(mpr, 0, sizeof(mpr));
    memset(mtl, 0, sizeof(mtl));
    memset(mtr, 0, sizeof(mtr));


    for(int i=1;i<=20;i++)
    {
        for(int x=1;x<=63;x++)
        {
            limits(x,plt);
            mel[i]+=el[i]/63;
            mer[i]+=er[i]/63;
        }
    }

    for(int i=1;i<20;i++)
    {
        for(int x=1;x<=63;x++)
        {
            limits(x,plt);
            mpl[i]+=pl[i]/63;
            mpr[i]+=pr[i]/63;
        }
    }

    for(int i=1;i<=1;i++)
    {
        for(int x=1;x<=63;x++)
        {
            limits(x,plt);
            mtl[i]+=tl[i]/63;
            mtr[i]+=tr[i]/63;
        }
    }
} 

bool verify_inside_main_part(int Xmin, int Xmax, int Ymin, int Ymax,float x, float y)
{
  if(x>Xmin)
    if(x<=Xmax)
        if(y>Ymin)
            if(y<=Ymax)
                return 1;
            else return 0;    
        else return 0;    
    else return 0;
  else return 0;   
}

void Z_adjustment()
{   
    All_limits(); //only once!!
    
    //h_align = new TH1F("h_all","h_all",300,0,6000);
    h_align = new TH1F("h_all","h_all",2500,0,50000);
    // h_all = new TH1F("h_all","h_all",225,1200,5700);
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
        snprintf(filename, 64, "../ds_res_PR2018_PD05_p0%d6.txt",i_name);

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
                    //margins,parent,z position
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

                              // cout<<p1<<" "<<Xmin<<" "<<Xmax<<" "<<Ymin<<" "<<Ymax<<endl;
                        }

                        if(area==p1) //all are 0 in MC
                        //if(verify_inside_main_part(Xmin,Xmax, Ymin, Ymax,p6,p7))
                        {
                            
                          //Tungsten
                          for(int j=1;j<=1;j++)
                            if(p8>tl[j] && p8<=tr[j]) 
                            {
                                mean_thickness = mtr[j]-mtl[j]; //cout<<mean_thickness<<" tungsten "<<endl;
                                scanned_thickness = tr[j]-tl[j];
                                vertex_correction = p8-tl[j];
                                h_align->Fill(mtl[j] + mean_thickness * vertex_correction / scanned_thickness);
                               
                            }

                          //Emulsion
                          for(int j=1;j<=20;j++)
                           if(p8>el[j] && p8<=er[j]) 
                            {
                                mean_thickness = mer[j]-mel[j]; //cout<<mean_thickness<<" emulsion "<<endl;
                                scanned_thickness = er[j]-el[j];
                                vertex_correction = p8-el[j];
                                h_align->Fill(mel[j] + mean_thickness * vertex_correction / scanned_thickness);
                                
                            }

                          //Plastic
                          for(int j=1;j<20;j++)
                            if(p8>pl[j] && p8<=pr[j]) 
                            {
                                mean_thickness = mpr[j]-mpl[j]; //cout<<mean_thickness<<" plastic "<<endl;
                                scanned_thickness = pr[j]-pl[j];
                                vertex_correction = p8-pl[j];
                                h_align->Fill(mpl[j] + mean_thickness * vertex_correction / scanned_thickness);
                               
                            } 
                        }
                       
                    }
                         
                    free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7); free(s8); free(s9);
                    free(s10); free(s11); free(s12); free(s13); free(s14); free(s15); free(s16); free(s17); free(s18); free(s19);
                    free(s20); free(s21); free(s22);  
                    
                }
            }

           // draw_hist(p1);

        }
        else
            cout << "Unable to open file";
        f.close();


        // h_align->SetLineColor(kBlack);
        // h_align->SetLineWidth(1);
        h_align->Draw();

        int max= h_align->GetMaximum(); 
        max=max+100; //to fill untill the frame 

        // for(int i=1;i<=20; i++)
        //  {
        //     //emulsion
        //     TBox *pe = new TBox(mel[i],0,mer[i],max);
        //     pe->SetFillStyle(3001);
        //     pe->SetFillColor(kBlue);//600
        //     //pe->SetBorderSize(0);
        //     pe->Draw();
        //  }

        //  for(int i=1;i<20; i++)
        //  {
        //     //plastic
        //     TBox *pp = new TBox(mpl[i],0,mpr[i],max);
        //     pp->SetFillStyle(3001);
        //     pp->SetFillColor(kGreen); //416
        //     //pp->SetBorderSize(0);
        //     pp->Draw();
        //  }

        //  for(int i=1;i<=1; i++)
        //  {
        //     TPaveText *pt = new TPaveText(mtl[i],0,mtr[i],max);
        //     pt->SetFillStyle(3001);
        //     pt->SetFillColor(920);
        //     pt->SetBorderSize(0);
        //     pt->Draw();
        //  }
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
