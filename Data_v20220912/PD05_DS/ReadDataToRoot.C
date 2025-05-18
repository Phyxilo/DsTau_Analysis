#include <string>  // Include the necessary header for std::string

void ReadDataToRoot(const char* filename) {
    // Open the input file
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Create a ROOT file to store the trees
    TFile* outfile = new TFile("output.root", "RECREATE");

    // Create the first tree (ds_sumfinal)
    TTree* tree_ds_sumfinal = new TTree("ds_sumfinal_tree", "Tree from dssum_final lines");

    // Define variables to store the data for ds_sumfinal
    Int_t ds_sumfinal_area1, ds_sumfinal_area2, ds_sumfinal_i, ds_sumfinal_flagw, ds_sumfinal_n_1ry_trk;
    Float_t ds_sumfinal_xc, ds_sumfinal_yc, ds_sumfinal_1ry_vx, ds_sumfinal_1ry_vy, ds_sumfinal_1ry_vz;
    Int_t ds_sumfinal_c1_intrk1, ds_sumfinal_c1_intrk2, ds_sumfinal_c1, ds_sumfinal_c2, ds_sumfinal_c3;
    Int_t ds_sumfinal_n2, ds_sumfinal_n3, ds_sumfinal_n4, ds_sumfinal_dt50, ds_sumfinal_n2_op50;
    Int_t ds_sumfinal_c1_intrk_for_pa;

    // Set tree branches for ds_sumfinal
    tree_ds_sumfinal->Branch("area1", &ds_sumfinal_area1, "area1/I");
    tree_ds_sumfinal->Branch("area2", &ds_sumfinal_area2, "area2/I");
    tree_ds_sumfinal->Branch("i", &ds_sumfinal_i, "i/I");
    tree_ds_sumfinal->Branch("xc", &ds_sumfinal_xc, "xc/F");
    tree_ds_sumfinal->Branch("yc", &ds_sumfinal_yc, "yc/F");
    tree_ds_sumfinal->Branch("1ry_vx", &ds_sumfinal_1ry_vx, "1ry_vx/F");
    tree_ds_sumfinal->Branch("1ry_vy", &ds_sumfinal_1ry_vy, "1ry_vy/F");
    tree_ds_sumfinal->Branch("1ry_vz", &ds_sumfinal_1ry_vz, "1ry_vz/F");
    tree_ds_sumfinal->Branch("flagw", &ds_sumfinal_flagw, "flagw/I");
    tree_ds_sumfinal->Branch("n_1ry_trk", &ds_sumfinal_n_1ry_trk, "n_1ry_trk/I");
    tree_ds_sumfinal->Branch("c1_intrk1", &ds_sumfinal_c1_intrk1, "c1_intrk1/I");
    tree_ds_sumfinal->Branch("c1_intrk2", &ds_sumfinal_c1_intrk2, "c1_intrk2/I");
    tree_ds_sumfinal->Branch("c1", &ds_sumfinal_c1, "c1/I");
    tree_ds_sumfinal->Branch("c2", &ds_sumfinal_c2, "c2/I");
    tree_ds_sumfinal->Branch("c3", &ds_sumfinal_c3, "c3/I");
    tree_ds_sumfinal->Branch("n2", &ds_sumfinal_n2, "n2/I");
    tree_ds_sumfinal->Branch("n3", &ds_sumfinal_n3, "n3/I");
    tree_ds_sumfinal->Branch("n4", &ds_sumfinal_n4, "n4/I");
    tree_ds_sumfinal->Branch("dt50", &ds_sumfinal_dt50, "dt50/I");
    tree_ds_sumfinal->Branch("n2_op50", &ds_sumfinal_n2_op50, "n2_op50/I");
    tree_ds_sumfinal->Branch("c1_intrk_for_pa", &ds_sumfinal_c1_intrk_for_pa, "c1_intrk_for_pa/I");

    // Create the second tree (ds_final)
    TTree* tree_ds_final = new TTree("ds_final_tree", "Tree from ds_final lines");

    // Define variables to store the data for ds_final
    Int_t ds_final_area1, ds_final_area2, ds_final_i;
    Float_t ds_final_txpeak, ds_final_typeak, ds_final_xc, ds_final_yc;
    Int_t ds_final_1ry_plt, ds_final_flagw, ds_final_n_1ry_trk;
    Float_t ds_final_1ry_vx, ds_final_1ry_vy, ds_final_1ry_vz, ds_final_2ry_vx, ds_final_2ry_vy, ds_final_2ry_vz;
    Int_t ds_final_2ry_plt, ds_final_parent_plt_1st, ds_final_parent_trkID, ds_final_parent_MCEvt;
    Int_t ds_final_parent_pdgID, ds_final_nparent_1ry, ds_final_nparent_1ry_penet, ds_final_nparent_non1ry;
    Float_t ds_final_parent_tx, ds_final_parent_ty, ds_final_parent_MCp;
    Int_t ds_final_ndau, ds_final_default1, ds_final_default2;
    Int_t ds_final_plt_dau1, ds_final_segid_dau1, ds_final_dau1_MCEvt, ds_final_dau1_pdgID;
    Float_t ds_final_dau1_MCp, ds_final_ip_to1ry_dau1, ds_final_ip_to2ry_dau1, ds_final_tx_dau1;
    Float_t ds_final_ty_dau1, ds_final_dt_dau1, ds_final_dtrms_dau1, ds_final_dtrmst_dau1, ds_final_dt_w_dau1;
    Int_t ds_final_plt_dau2, ds_final_segid_dau2, ds_final_dau2_MCEvt, ds_final_dau2_pdgID;
    Float_t ds_final_dau2_MCp, ds_final_ip_to1ry_dau2, ds_final_ip_to2ry_dau2, ds_final_tx_dau2;
    Float_t ds_final_ty_dau2, ds_final_dt_dau2, ds_final_dtrms_dau2, ds_final_dtrmst_dau2, ds_final_dt_w_dau2;
    Int_t ds_final_plt_dau3, ds_final_segid_dau3, ds_final_dau3_MCEvt, ds_final_dau3_pdgID;
    Float_t ds_final_dau3_MCp, ds_final_ip_to1ry_dau3, ds_final_ip_to2ry_dau3, ds_final_tx_dau3;
    Float_t ds_final_ty_dau3, ds_final_dt_dau3, ds_final_dtrms_dau3, ds_final_dtrmst_dau3, ds_final_dt_w_dau3;
    Int_t ds_final_plt_dau4, ds_final_segid_dau4, ds_final_dau4_MCEvt, ds_final_dau4_pdgID;
    Float_t ds_final_dau4_MCp, ds_final_ip_to1ry_dau4, ds_final_ip_to2ry_dau4, ds_final_tx_dau4;
    Float_t ds_final_ty_dau4, ds_final_dt_dau4, ds_final_dtrms_dau4, ds_final_dtrmst_dau4, ds_final_dt_w_dau4;
    Float_t ds_final_dmin_org_vee, ds_final_dmin_fine_vee, ds_final_topen_vee, ds_final_dt1dt2_vee;
    Float_t ds_final_dt012_vee;
    Int_t ds_final_ntrk_around_2ry, ds_final_ntrk_other_vtx_max, ds_final_flag_final, ds_final_vtx_id;



    // Set tree branches for ds_final
    tree_ds_final->Branch("area1", &ds_final_area1, "area1/I");
    tree_ds_final->Branch("area2", &ds_final_area2, "area2/I");
    tree_ds_final->Branch("txpeak", &ds_final_txpeak, "txpeak/F");
    tree_ds_final->Branch("typeak", &ds_final_typeak, "typeak/F");
    tree_ds_final->Branch("i", &ds_final_i, "i/I");
    tree_ds_final->Branch("xc", &ds_final_xc, "xc/F");
    tree_ds_final->Branch("yc", &ds_final_yc, "yc/F");
    tree_ds_final->Branch("1ry_vx", &ds_final_1ry_vx, "1ry_vx/F");
    tree_ds_final->Branch("1ry_vy", &ds_final_1ry_vy, "1ry_vy/F");
    tree_ds_final->Branch("1ry_vz", &ds_final_1ry_vz, "1ry_vz/F");
    tree_ds_final->Branch("1ry_plt", &ds_final_1ry_plt, "1ry_plt/I");
    tree_ds_final->Branch("flagw", &ds_final_flagw, "flagw/I");
    tree_ds_final->Branch("n_1ry_trk", &ds_final_n_1ry_trk, "n_1ry_trk/I");
    tree_ds_final->Branch("2ry_vx", &ds_final_2ry_vx, "2ry_vx/F");
    tree_ds_final->Branch("2ry_vy", &ds_final_2ry_vy, "2ry_vy/F");
    tree_ds_final->Branch("2ry_vz", &ds_final_2ry_vz, "2ry_vz/F");
    tree_ds_final->Branch("2ry_plt", &ds_final_2ry_plt, "2ry_plt/I");
    tree_ds_final->Branch("parent_plt_1st", &ds_final_parent_plt_1st, "parent_plt_1st/I");
    tree_ds_final->Branch("parent_trkID", &ds_final_parent_trkID, "parent_trkID/I");
    tree_ds_final->Branch("parent_MCEvt", &ds_final_parent_MCEvt, "parent_MCEvt/I");
    tree_ds_final->Branch("parent_pdgID", &ds_final_parent_pdgID, "parent_pdgID/I");
    tree_ds_final->Branch("nparent_1ry", &ds_final_nparent_1ry, "nparent_1ry/I");
    tree_ds_final->Branch("nparent_1ry_penet", &ds_final_nparent_1ry_penet, "nparent_1ry_penet/I");
    tree_ds_final->Branch("nparent_non1ry", &ds_final_nparent_non1ry, "nparent_non1ry/I");
    tree_ds_final->Branch("parent_tx", &ds_final_parent_tx, "parent_tx/F");
    tree_ds_final->Branch("parent_ty", &ds_final_parent_ty, "parent_ty/F");
    tree_ds_final->Branch("parent_MCp", &ds_final_parent_MCp, "parent_MCp/F");
    tree_ds_final->Branch("ndau", &ds_final_ndau, "ndau/I");
    tree_ds_final->Branch("default1", &ds_final_default1, "default1/I");
    tree_ds_final->Branch("default2", &ds_final_default2, "default2/I");
    tree_ds_final->Branch("plt_dau1", &ds_final_plt_dau1, "plt_dau1/I");
    tree_ds_final->Branch("segid_dau1", &ds_final_segid_dau1, "segid_dau1/I");
    tree_ds_final->Branch("dau1_MCEvt", &ds_final_dau1_MCEvt, "dau1_MCEvt/I");
    tree_ds_final->Branch("dau1_pdgID", &ds_final_dau1_pdgID, "dau1_pdgID/I");
    tree_ds_final->Branch("dau1_MCp", &ds_final_dau1_MCp, "dau1_MCp/F");
    tree_ds_final->Branch("ip_to1ry_dau1", &ds_final_ip_to1ry_dau1, "ip_to1ry_dau1/F");
    tree_ds_final->Branch("ip_to2ry_dau1", &ds_final_ip_to2ry_dau1, "ip_to2ry_dau1/F");
    tree_ds_final->Branch("tx_dau1", &ds_final_tx_dau1, "tx_dau1/F");
    tree_ds_final->Branch("ty_dau1", &ds_final_ty_dau1, "ty_dau1/F");
    tree_ds_final->Branch("dt_dau1", &ds_final_dt_dau1, "dt_dau1/F");
    tree_ds_final->Branch("dtrms_dau1", &ds_final_dtrms_dau1, "dtrms_dau1/F");
    tree_ds_final->Branch("dtrmst_dau1", &ds_final_dtrmst_dau1, "dtrmst_dau1/F");
    tree_ds_final->Branch("dt_w_dau1", &ds_final_dt_w_dau1, "dt_w_dau1/F");

    tree_ds_final->Branch("plt_dau2", &ds_final_plt_dau1, "plt_dau2/I");
    tree_ds_final->Branch("segid_dau2", &ds_final_segid_dau1, "segid_dau2/I");
    tree_ds_final->Branch("dau2_MCEvt", &ds_final_dau1_MCEvt, "dau2_MCEvt/I");
    tree_ds_final->Branch("dau2_pdgID", &ds_final_dau1_pdgID, "dau2_pdgID/I");
    tree_ds_final->Branch("dau2_MCp", &ds_final_dau1_MCp, "dau2_MCp/F");
    tree_ds_final->Branch("ip_to1ry_dau2", &ds_final_ip_to1ry_dau1, "ip_to1ry_dau2/F");
    tree_ds_final->Branch("ip_to2ry_dau2", &ds_final_ip_to2ry_dau1, "ip_to2ry_dau2/F");
    tree_ds_final->Branch("tx_dau2", &ds_final_tx_dau1, "tx_dau2/F");
    tree_ds_final->Branch("ty_dau2", &ds_final_ty_dau1, "ty_dau2/F");
    tree_ds_final->Branch("dt_dau2", &ds_final_dt_dau1, "dt_dau2/F");
    tree_ds_final->Branch("dtrms_dau2", &ds_final_dtrms_dau1, "dtrms_dau2/F");
    tree_ds_final->Branch("dtrmst_dau2", &ds_final_dtrmst_dau1, "dtrmst_dau2/F");
    tree_ds_final->Branch("dt_w_dau2", &ds_final_dt_w_dau1, "dt_w_dau2/F");

    tree_ds_final->Branch("plt_dau3", &ds_final_plt_dau1, "plt_dau3/I");
    tree_ds_final->Branch("segid_dau3", &ds_final_segid_dau1, "segid_dau3/I");
    tree_ds_final->Branch("dau3_MCEvt", &ds_final_dau1_MCEvt, "dau3_MCEvt/I");
    tree_ds_final->Branch("dau3_pdgID", &ds_final_dau1_pdgID, "dau3_pdgID/I");
    tree_ds_final->Branch("dau3_MCp", &ds_final_dau1_MCp, "dau3_MCp/F");
    tree_ds_final->Branch("ip_to1ry_dau3", &ds_final_ip_to1ry_dau1, "ip_to1ry_dau3/F");
    tree_ds_final->Branch("ip_to2ry_dau3", &ds_final_ip_to2ry_dau1, "ip_to2ry_dau3/F");
    tree_ds_final->Branch("tx_dau3", &ds_final_tx_dau1, "tx_dau3/F");
    tree_ds_final->Branch("ty_dau3", &ds_final_ty_dau1, "ty_dau3/F");
    tree_ds_final->Branch("dt_dau3", &ds_final_dt_dau1, "dt_dau3/F");
    tree_ds_final->Branch("dtrms_dau3", &ds_final_dtrms_dau1, "dtrms_dau3/F");
    tree_ds_final->Branch("dtrmst_dau3", &ds_final_dtrmst_dau1, "dtrmst_dau3/F");
    tree_ds_final->Branch("dt_w_dau3", &ds_final_dt_w_dau1, "dt_w_dau3/F");


    tree_ds_final->Branch("plt_dau4", &ds_final_plt_dau1, "plt_dau4/I");
    tree_ds_final->Branch("segid_dau4", &ds_final_segid_dau1, "segid_dau4/I");
    tree_ds_final->Branch("dau4_MCEvt", &ds_final_dau1_MCEvt, "dau4_MCEvt/I");
    tree_ds_final->Branch("dau4_pdgID", &ds_final_dau1_pdgID, "dau4_pdgID/I");
    tree_ds_final->Branch("dau4_MCp", &ds_final_dau1_MCp, "dau4_MCp/F");
    tree_ds_final->Branch("ip_to1ry_dau4", &ds_final_ip_to1ry_dau1, "ip_to1ry_dau4/F");
    tree_ds_final->Branch("ip_to2ry_dau4", &ds_final_ip_to2ry_dau1, "ip_to2ry_dau4/F");
    tree_ds_final->Branch("tx_dau4", &ds_final_tx_dau1, "tx_dau4/F");
    tree_ds_final->Branch("ty_dau4", &ds_final_ty_dau1, "ty_dau4/F");
    tree_ds_final->Branch("dt_dau4", &ds_final_dt_dau1, "dt_dau4/F");
    tree_ds_final->Branch("dtrms_dau4", &ds_final_dtrms_dau1, "dtrms_dau4/F");
    tree_ds_final->Branch("dtrmst_dau4", &ds_final_dtrmst_dau1, "dtrmst_dau4/F");
    tree_ds_final->Branch("dt_w_dau4", &ds_final_dt_w_dau1, "dt_w_dau4/F");

    tree_ds_final->Branch("dmin_org_vee", &ds_final_dmin_org_vee, "dmin_org_vee/F");
    tree_ds_final->Branch("dmin_fine_vee", &ds_final_dmin_fine_vee, "dmin_fine_vee/F");
    tree_ds_final->Branch("topen_vee", &ds_final_topen_vee, "topen_vee/F");
    tree_ds_final->Branch("dt1dt2_vee", &ds_final_dt1dt2_vee, "dt1dt2_vee/F");
    tree_ds_final->Branch("dt012_vee", &ds_final_dt012_vee, "dt012_vee/F");
    tree_ds_final->Branch("ntrk_around_2ry", &ds_final_ntrk_around_2ry, "ntrk_around_2ry/I");
    tree_ds_final->Branch("ntrk_other_vtx_max", &ds_final_ntrk_other_vtx_max, "ntrk_other_vtx_max/I");
    tree_ds_final->Branch("flag_final", &ds_final_flag_final, "flag_final/I");
    tree_ds_final->Branch("vtx_id", &ds_final_vtx_id, "vtx_id/I");



    // Read the file line by line
    std::string line;
    std::string label;  // Declare the label variable
    while (std::getline(infile, line)) {
        // Skip lines that don't start with "dssum_final" or "ds_final"
        if (line.find("dssum_final") == 0) {
            // Parse ds_sumfinal data
            std::istringstream iss(line);
            iss.ignore(12); // Skip "dssum_final"
            iss >> ds_sumfinal_area1 >> ds_sumfinal_area2 >> ds_sumfinal_i;
            iss >> ds_sumfinal_xc >> ds_sumfinal_yc >> ds_sumfinal_1ry_vx >> ds_sumfinal_1ry_vy >> ds_sumfinal_1ry_vz;
            iss >> ds_sumfinal_flagw >> ds_sumfinal_n_1ry_trk;

            // Parse dynamic label-value pairs for ds_sumfinal
            while (iss >> label) {  // Use label here
                if (label == "c1_intrk") {
                    iss >> ds_sumfinal_c1_intrk1 >> ds_sumfinal_c1_intrk2;
                } else if (label == "c1") {
                    iss >> ds_sumfinal_c1;
                } else if (label == "c2") {
                    iss >> ds_sumfinal_c2;
                } else if (label == "c3") {
                    iss >> ds_sumfinal_c3;
                } else if (label == "n2") {
                    iss >> ds_sumfinal_n2;
                } else if (label == "n3") {
                    iss >> ds_sumfinal_n3;
                } else if (label == "n4") {
                    iss >> ds_sumfinal_n4;
                } else if (label == "c1_dt50") {
                    iss >> ds_sumfinal_dt50;
                } else if (label == "n2_op50") {
                    iss >> ds_sumfinal_n2_op50;
                } else if (label == "c1_intrk_for_pa") {
                    iss >> ds_sumfinal_c1_intrk_for_pa;
                } else {
                    int skipValue;
                    iss >> skipValue; // Skip unknown label values
                }
            }

            // Fill ds_sumfinal tree
            tree_ds_sumfinal->Fill();
        } 
        else if (line.find("ds_final") == 0) {
            // Parse ds_final data
            std::istringstream iss(line);
            iss.ignore(19); // Skip "ds_final"
            iss >> ds_final_area1 >> ds_final_area2 ;
            iss >> ds_final_txpeak >> ds_final_typeak >> ds_final_i >> ds_final_xc >> ds_final_yc;
            iss >> ds_final_1ry_vx >> ds_final_1ry_vy >> ds_final_1ry_vz;
            iss >> ds_final_1ry_plt >> ds_final_flagw >> ds_final_n_1ry_trk;
            iss >> ds_final_2ry_vx >> ds_final_2ry_vy >> ds_final_2ry_vz;
            iss >> ds_final_2ry_plt >> ds_final_parent_plt_1st >> ds_final_parent_trkID;
            iss >> ds_final_parent_MCEvt >>  ds_final_parent_pdgID >> ds_final_parent_MCp >> ds_final_nparent_1ry;
            iss >> ds_final_nparent_1ry_penet >> ds_final_nparent_non1ry >> ds_final_parent_tx;
            iss >> ds_final_parent_ty >>  ds_final_ndau;
            iss >> ds_final_default1 >> ds_final_default2 >> ds_final_plt_dau1;
            iss >> ds_final_segid_dau1 >> ds_final_dau1_MCEvt >> ds_final_dau1_pdgID;
            iss >> ds_final_dau1_MCp >> ds_final_ip_to1ry_dau1 >> ds_final_ip_to2ry_dau1;
            iss >> ds_final_tx_dau1 >> ds_final_ty_dau1 >> ds_final_dt_dau1;
            iss >> ds_final_dtrms_dau1 >> ds_final_dtrmst_dau1 >> ds_final_dt_w_dau1;
            iss >> ds_final_plt_dau2;
            iss >> ds_final_segid_dau2 >> ds_final_dau2_MCEvt >> ds_final_dau2_pdgID;
            iss >> ds_final_dau2_MCp >> ds_final_ip_to1ry_dau2 >> ds_final_ip_to2ry_dau2;
            iss >> ds_final_tx_dau2 >> ds_final_ty_dau2 >> ds_final_dt_dau2;
            iss >> ds_final_dtrms_dau2 >> ds_final_dtrmst_dau2 >> ds_final_dt_w_dau2;
            iss >> ds_final_plt_dau3;
            iss >> ds_final_segid_dau3 >> ds_final_dau3_MCEvt >> ds_final_dau3_pdgID;
            iss >> ds_final_dau3_MCp >> ds_final_ip_to1ry_dau3 >> ds_final_ip_to2ry_dau3;
            iss >> ds_final_tx_dau3 >> ds_final_ty_dau3 >> ds_final_dt_dau3;
            iss >> ds_final_dtrms_dau3 >> ds_final_dtrmst_dau3 >> ds_final_dt_w_dau3;
            iss >> ds_final_plt_dau4;
            iss >> ds_final_segid_dau4 >> ds_final_dau4_MCEvt >> ds_final_dau4_pdgID;
            iss >> ds_final_dau4_MCp >> ds_final_ip_to1ry_dau4 >> ds_final_ip_to2ry_dau4;
            iss >> ds_final_tx_dau4 >> ds_final_ty_dau4 >> ds_final_dt_dau4;
            iss >> ds_final_dtrms_dau4 >> ds_final_dtrmst_dau4 >> ds_final_dt_w_dau4;

            iss >> ds_final_dmin_org_vee >> ds_final_dmin_fine_vee >> ds_final_topen_vee;
            iss >> ds_final_dt1dt2_vee >> ds_final_dt012_vee >> ds_final_ntrk_around_2ry;
            iss >> ds_final_ntrk_other_vtx_max >> ds_final_flag_final;



            // Fill ds_final tree
            tree_ds_final->Fill();
        }
    }

    // Write both trees to the file and clean up
    tree_ds_sumfinal->Write();
    tree_ds_final->Write();

    // Close the files
    outfile->Close();
    infile.close();
    std::cout << "Trees created successfully in output.root" << std::endl;
}

int main() {
    ReadDataToRoot("ds_res_PR2018_PD05_p086.txt");
    return 0;
}
