#ifndef GENIE_ANALYSIS_H
#define GENIE_ANALYSIS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TList.h>
#include <TNamed.h>
#include <TParameter.h>

#include "Fiducial.h"
#include "Subtraction.h"
#include "Constants.h"


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class genie_analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   std::string ftarget;     // The target name  // ------------------------------->>>>>>>>>>>>>Mariana
   std::string fbeam_en;    // The beam energy  // ------------------------------->>>>>>>>>>>>>Mariana

   TList *my_options = new TList();
   //Run Info
   TParameter<int> *t_nentries = new TParameter<int>("Entries", 0);
   TNamed *t_Run = new TNamed("Run type", "");
   TNamed *t_target = new TNamed("Target", "");
   TParameter<double> *t_beam_en = new TParameter<double>("Beam Energy", 0);
   std::string fFileName = "";

   //Cuts
   TParameter<bool> *t_AnyCuts = new TParameter<bool>("AnyCuts", false);
   TParameter<double> *t_deltaPhiEl = new TParameter<double>("El delta phi", 9999);
   TParameter<double> *t_thetaEl_lb = new TParameter<double>("El theta lb", 0);
   TParameter<double> *t_thetaEl_ub = new TParameter<double>("El theta ub", 180);
   TParameter<double> *t_elMom_lb = new TParameter<double>("El mom lb",0);
   TParameter<double> *t_deltaPhiProt = new TParameter<double>("Prot delta phi",9999);
   TParameter<double> *t_thetaProt_lb = new TParameter<double>("Prot theta lb", 0);
   TParameter<double> *t_thetaProt_ub = new TParameter<double>("Prot theta ub", 180);
   TParameter<double> *t_ProtMom_lb = new TParameter<double>("Prot mom lb", 0);
   TParameter<double> *t_ProtMom_ub = new TParameter<double>("Prot mom ub", 9999);
   TNamed *t_elSectors = new TNamed("electron sectors", "");
   TNamed *t_protSectors = new TNamed("proton sectors", "");

   bool fApplyPhiOpeningAngleEl = false;
   bool fApplyPhiOpeningAngleProt = false;
   bool fApplyThetaSliceEl = false;
   bool fApplyThetaSliceProt = false;
   bool fApplyPhiSliceEl_Sectors16 = false;
   bool fApplyPhiSliceEl_Sectors126 = false;
   bool fApplyPhiSliceProt_Sectors = false;
   bool fApplyElMomCut = false;
   bool fApplyProtMomCut = false;
   bool fApplyPtCut = false; // gchamber: apply pt cut or not (I did not end up using this)
   int fAllSectors = 0;
   int fFiducials = 0;
   int fAccWeights = 0;
   int fReso = 0;
   int fSignal = 0.;

   int N_tot;
   Fiducial   *fiducialcut;
   Subtraction *rotation;
   int fTorusCurrent;
   int fchoice;
   std::string target_name;
   std::map<std::string,double> en_beam;
   std::map<std::string,double> en_beam_Ecal;
   std::map<std::string,double> en_beam_Eqe;

   // Declaration of leaf types
   Int_t           iev;
   Int_t           neu;
   Int_t           fspl;
   Int_t           tgt;
   Int_t           Z;
   Int_t           A;
   Int_t           hitnuc;
   Int_t           hitqrk;
   Int_t           resid;
   Bool_t          sea;
   Bool_t          qel;
   Bool_t          mec;
   Bool_t          res;
   Bool_t          dis;
   Bool_t          coh;
   Bool_t          dfr;
   Bool_t          imd;
   Bool_t          imdanh;
   Bool_t          singlek;
   Bool_t          nuel;
   Bool_t          em;
   Bool_t          cc;
   Bool_t          nc;
   Bool_t          charm;
   Int_t           neut_code;
   Int_t           nuance_code;
   Double_t        wght;
   Double_t        xs;
   Double_t        ys;
   Double_t        ts;
   Double_t        Q2s;
   Double_t        Ws;
   Double_t        x;
   Double_t        y;
   Double_t        t;
   Double_t        Q2;
   Double_t        W;
   Double_t        EvRF;
   Double_t        Ev;
   Double_t        pxv;
   Double_t        pyv;
   Double_t        pzv;
   Double_t        En;
   Double_t        pxn;
   Double_t        pyn;
   Double_t        pzn;
   Double_t        El;
   Double_t        pxl;
   Double_t        pyl;
   Double_t        pzl;
   Double_t        pl;
   Double_t        cthl;
   Int_t           nfp;
   Int_t           nfn;
   Int_t           nfpip;
   Int_t           nfpim;
   Int_t           nfpi0;
   Int_t           nfkp;
   Int_t           nfkm;
   Int_t           nfk0;
   Int_t           nfem;
   Int_t           nfother;
   Int_t           nip;
   Int_t           nin;
   Int_t           nipip;
   Int_t           nipim;
   Int_t           nipi0;
   Int_t           nikp;
   Int_t           nikm;
   Int_t           nik0;
   Int_t           niem;
   Int_t           niother;
   Int_t           ni;
   Int_t           pdgi[2];   //[ni]
   Int_t           resc[1];   //[ni]
   Double_t        Ei[2];   //[ni]
   Double_t        pxi[2];   //[ni]
   Double_t        pyi[2];   //[ni]
   Double_t        pzi[2];   //[ni]
   Int_t           nf;
   Int_t           pdgf[120];   //[nf]
   Double_t        Ef[120];   //[nf]
   Double_t        pxf[120];   //[nf]
   Double_t        pyf[120];   //[nf]
   Double_t        pzf[120];   //[nf]
   Double_t        pf[120];   //[nf]
   Double_t        cthf[120];   //[nf]
   Double_t        vtxx;
   Double_t        vtxy;
   Double_t        vtxz;
   Double_t        vtxt;
   Double_t        sumKEf;
   Double_t        calresp0;

   // List of branches
   TBranch        *b_iev;   //!
   TBranch        *b_neu;   //!
   TBranch        *b_fspl;   //!
   TBranch        *b_tgt;   //!
   TBranch        *b_Z;   //!
   TBranch        *b_A;   //!
   TBranch        *b_hitnuc;   //!
   TBranch        *b_hitqrk;   //!
   TBranch        *b_resid;   //!
   TBranch        *b_sea;   //!
   TBranch        *b_qel;   //!
   TBranch        *b_mec;   //!
   TBranch        *b_res;   //!
   TBranch        *b_dis;   //!
   TBranch        *b_coh;   //!
   TBranch        *b_dfr;   //!
   TBranch        *b_imd;   //!
   TBranch        *b_imdanh;   //!
   TBranch        *b_singlek;   //!
   TBranch        *b_nuel;   //!
   TBranch        *b_em;   //!
   TBranch        *b_cc;   //!
   TBranch        *b_nc;   //!
   TBranch        *b_charm;   //!
   TBranch        *b_neut_code;   //!
   TBranch        *b_nuance_code;   //!
   TBranch        *b_wght;   //!
   TBranch        *b_xs;   //!
   TBranch        *b_ys;   //!
   TBranch        *b_ts;   //!
   TBranch        *b_Q2s;   //!
   TBranch        *b_Ws;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_t;   //!
   TBranch        *b_Q2;   //!
   TBranch        *b_W;   //!
   TBranch        *b_EvRF;   //!
   TBranch        *b_Ev;   //!
   TBranch        *b_pxv;   //!
   TBranch        *b_pyv;   //!
   TBranch        *b_pzv;   //!
   TBranch        *b_En;   //!
   TBranch        *b_pxn;   //!
   TBranch        *b_pyn;   //!
   TBranch        *b_pzn;   //!
   TBranch        *b_El;   //!
   TBranch        *b_pxl;   //!
   TBranch        *b_pyl;   //!
   TBranch        *b_pzl;   //!
   TBranch        *b_pl;   //!
   TBranch        *b_cthl;   //!
   TBranch        *b_nfp;   //!
   TBranch        *b_nfn;   //!
   TBranch        *b_nfpip;   //!
   TBranch        *b_nfpim;   //!
   TBranch        *b_nfpi0;   //!
   TBranch        *b_nfkp;   //!
   TBranch        *b_nfkm;   //!
   TBranch        *b_nfk0;   //!
   TBranch        *b_nfem;   //!
   TBranch        *b_nfother;   //!
   TBranch        *b_nip;   //!
   TBranch        *b_nin;   //!
   TBranch        *b_nipip;   //!
   TBranch        *b_nipim;   //!
   TBranch        *b_nipi0;   //!
   TBranch        *b_nikp;   //!
   TBranch        *b_nikm;   //!
   TBranch        *b_nik0;   //!
   TBranch        *b_niem;   //!
   TBranch        *b_niother;   //!
   TBranch        *b_ni;   //!
   TBranch        *b_pdgi;   //!
   TBranch        *b_resc;   //!
   TBranch        *b_Ei;   //!
   TBranch        *b_pxi;   //!
   TBranch        *b_pyi;   //!
   TBranch        *b_pzi;   //!
   TBranch        *b_nf;   //!
   TBranch        *b_pdgf;   //!
   TBranch        *b_Ef;   //!
   TBranch        *b_pxf;   //!
   TBranch        *b_pyf;   //!
   TBranch        *b_pzf;   //!
   TBranch        *b_pf;   //!
   TBranch        *b_cthf;   //!
   TBranch        *b_vtxx;   //!
   TBranch        *b_vtxy;   //!
   TBranch        *b_vtxz;   //!
   TBranch        *b_vtxt;   //!
   TBranch        *b_sumKEf;   //!
   TBranch        *b_calresp0;   //!
   
   genie_analysis(std::string, std::string, std::string, int, int, int, int, double, double, double, int, int, double, double, int, int, int, int, int, TTree *tree=0);
   virtual ~genie_analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

	// ------------------------------------------------------------------------------------------

	// apapadop // Nov 23 2020: adding extra fiducials with lower theta bounds for protons, pi pluses & pi minuses
	// Protons & Pi pluses are easy, just a min angle
	// Pi minuses are a functional form theta = A + B / P

	Bool_t PFiducialCutExtra(std::string beam_en, TVector3 momentum) {
	
		return fiducialcut->PFiducialCutExtra(beam_en, momentum);
	
	}

	Bool_t PiplFiducialCutExtra(std::string beam_en, TVector3 momentum) {
     
		return fiducialcut->PiplFiducialCutExtra(beam_en, momentum);
	
	}

	Bool_t PimiFiducialCutExtra(std::string beam_en, TVector3 momentum) {
     
		return fiducialcut->PimiFiducialCutExtra(beam_en, momentum);
	
	}

	Bool_t Phot_fidExtra(TVector3 momentum) {
     
		return fiducialcut->Phot_fidExtra(momentum);
	
	}

	// ------------------------------------------------------------------------------------------

   void SetFiducialCutParameters(std::string beam_en) {
     fiducialcut->SetFiducialCutParameters(beam_en);
   }
   Bool_t EFiducialCut(std::string beam_en, TVector3 momentum) {
     return fiducialcut->EFiducialCut(beam_en, momentum);
   }
   Bool_t PFiducialCut(std::string beam_en, TVector3 momentum) {
     return fiducialcut->PFiducialCut(beam_en, momentum);
   }
   Bool_t PiplFiducialCut(std::string beam_en, TVector3 momentum,Float_t *philow,Float_t *phiup) {
     return fiducialcut->PiplFiducialCut(beam_en, momentum, philow, phiup);
   }
   Bool_t PimiFiducialCut(std::string beam_en, TVector3 momentum,Float_t *philow,Float_t *phiup) {
     return fiducialcut->PimiFiducialCut(beam_en, momentum, philow, phiup);
   }
   bool Phot_fid(TVector3 V3_phot) {
     return fiducialcut->Phot_fid(V3_phot);
   }
   bool Pi_phot_fid_united(std::string beam_en, TVector3 V3_pi_phot, int q_pi_phot) {
     return fiducialcut->Pi_phot_fid_united(beam_en,V3_pi_phot, q_pi_phot);
   }
   Bool_t GetEPhiLimits(std::string beam_en, Float_t momentum, Float_t theta, Int_t sector, Float_t *EPhiMin, Float_t *EPhiMax) {
     return fiducialcut->GetEPhiLimits(beam_en, momentum, theta, sector, EPhiMin, EPhiMax);
   }
   void prot3_rot_func(std::string beam_en, TVector3 V3q, TVector3 V3prot[3],TVector3  V3prot_uncorr[3],TLorentzVector V4el,double Ecal_3pto2p[][2],double  pmiss_perp_3pto2p[][2],double  P3pto2p[][2],double N_p1[3],double Ecal_3pto1p[3],double  pmiss_perp_3pto1p[3], double *N_p3det);
   void prot2_rot_func(std::string beam_en, TVector3 V3q, TVector3  V3prot[2],TVector3  V3prot_uncorr[2],TLorentzVector V4el,double Ecal_2pto1p[2],double  pmiss_perp_2pto1p[2],double  P2pto1p[2], double *Nboth);
   void prot1_pi1_rot_func(std::string beam_en, TVector3 V3q, TVector3  V3prot,TVector3 V3pi, int q_pi,bool radstat, double *N_pi_p,double *N_nopi_p);
   void prot1_pi2_rot_func(std::string beam_en, TVector3 V3q, TVector3  V3prot,TVector3 V3pi[2], int q_pi[2],bool radstat[2], double *P_1p0pi,double P_1p1pi[2]);
   void prot1_pi3_rot_func(std::string beam_en, TVector3 V3q, TVector3  V3prot,TVector3 V3pi[3], int q_pi[3],bool radstat[3],double *P_tot);
   void prot2_pi1_rot_func(std::string beam_en, TVector3 V3q,TVector3 V3_2prot_corr[2],TVector3 V3_2prot_uncorr[2],TVector3 V3_1pi, int q_pi,bool radstat,TLorentzVector V4_el, double Ecal_2p1pi_to2p0pi[2],double p_miss_perp_2p1pi_to2p0pi[2],double P_2p1pito2p0pi[2],double P_2p1pito1p1pi[2],double P_2p1pito1p0pi[2],double *P_tot);
   void prot2_pi2_rot_func(std::string beam_en, TVector3 V3_q,TVector3 V3_2prot_corr[2],TVector3 V3_2prot_uncorr[2],TVector3 V3_2pi[2], int q_pi[2],bool radstat[2],TLorentzVector V4_el, double Ecal_2p2pi[2],double p_miss_perp_2p2pi[2],double P_tot_2p[2]);
   void prot3_pi1_rot_func(std::string beam_en, TVector3 V3_q,TVector3 V3_3prot_corr[3],TVector3 V3_3prot_uncorr[3],TVector3 V3_pi, int q_pi,bool radstat,TLorentzVector V4_el, double Ecal_3p1pi[3],double p_miss_perp_3p1pi[3],double P_tot_3p[3]);
   void pi1_rot_func(std::string beam_en, TVector3 V3_pi, int q_pi,bool radstat,TVector3 V3_q,double *P_pi);
   void pi2_rot_func(std::string beam_en, TVector3 V3_pi[2], int q_pi[2],bool radstat[2], TVector3 V3_q,double *P_0pi,double P_1pi[2]);
   void pi3_rot_func(std::string beam_en, TVector3 V3_pi[3], int q_pi[3],bool radstat[3], TVector3 V3_q,double *P_0pi,double P_1pi[3],double P_320[3],double P_3210[][2]);
   void pi4_rot_func(std::string beam_en, TVector3 V3_pi[4], int q_pi[4],bool radstat[4], TVector3 V3_q,double *P_0pi,double *P_410,double *P_420,double *P_4210,double *P_430,double *P_4310,double *P_4320,double *P_43210);
   double acceptance_c(double p, double cost, double phi, int id,TFile* file_acceptance, bool ApplyAccWeights);

};

#endif
#ifdef GENIE_ANALYSIS_C
genie_analysis::genie_analysis(std::string a_filename, std::string a_target, std::string a_beam_en, int number_rotations, int choice, int a_elSectors, int a_deltaPhiEl, double a_thetaEl_lb, double a_thetaEl_ub, double a_elMom_lb, int a_protSectors, int a_deltaPhiProt, double a_thetaProt_lb, double a_thetaProt_ub, int a_AllSectors, int a_Fiducials, int a_AccWeights, int a_Reso, int a_Signal, TTree *tree) : fChain(0)
//genie_analysis::genie_analysis(std::string a_filename, std::string a_target, std::string a_beam_en, int number_rotations, int choice, int a_elSectors, int a_deltaPhiEl, double a_thetaEl_lb, double a_thetaEl_ub, double a_elMom_lb, int a_protSectors, int a_deltaPhiProt, double a_thetaProt_lb, double a_thetaProt_ub, TTree *tree) : fChain(0)
//genie_analysis::genie_analysis( std::string a_target, std::string a_beam_en, int number_rotations, int choice, int a_elSectors, int a_deltaPhiEl, double a_thetaEl_lb, double a_thetaEl_ub, double a_elMom_lb, int a_protSectors, int a_deltaPhiProt, double a_thetaProt_lb, double a_thetaProt_ub, double a_protMom_lb, double a_protMom_ub, double a_Em_ub, TTree *tree) : fChain(0)
{
    std::cout << "File name = " << a_filename << "\n" << std::endl;
    std::cout << "Target = " << a_target << "\n" <<std::endl;
    std::cout << "Beam Energy = " << a_beam_en << "\n" <<std::endl;
    std::cout << "Number of Rotations = " << number_rotations << "\n" <<std::endl;
    std::cout << "Fchoice = " << choice << "\n" <<std::endl;
    std::cout << "Electron sectors = " << a_elSectors << "\n" <<std::endl;
    std::cout << "DeltaPhi Electron cut = " << (a_deltaPhiEl == 1 ? "true":"false") << "\n" <<std::endl;
    std::cout << "Electron Theta lb = " << a_thetaEl_lb << "\n" <<std::endl;
    std::cout << "Electron Theta ub = " << a_thetaEl_ub << "\n" <<std::endl;
    std::cout << "Electron Momentum lb = " << a_elMom_lb << "\n" <<std::endl;
    std::cout << "Proton sectors = " << a_protSectors << "\n" <<std::endl;
    std::cout << "DeltaPhi Proton cut = " << (a_deltaPhiProt == 1 ? "true":"false") << "\n" <<std::endl;
    std::cout << "Proton Theta lb = " << a_thetaProt_lb << "\n" <<std::endl;
    std::cout << "Proton Theta ub = " << a_thetaProt_ub << "\n" <<std::endl;
    
    std::cout << "UseAllSectors = " << a_AllSectors << "\n";
    std::cout << "ApplyFiducials = " << a_Fiducials << "\n";
    std::cout << "ApplyAccWeights = " << a_AccWeights << "\n";
    std::cout << "ApplyReso = " << a_Reso << "\n";
    std::cout << "TruthLevel1p0piSignalStudy = " << a_Signal << "\n";

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

     fiducialcut = new Fiducial();
     rotation = new Subtraction();
     N_tot = number_rotations;
     ftarget = a_target;
     fbeam_en = a_beam_en;
     fTorusCurrent = 0;
     fchoice = choice;
     fFileName = a_filename;

     if (a_elSectors == 2) { 
        t_elSectors->SetTitle("El_sect_16"); 
        fApplyPhiSliceEl_Sectors16 = true;
        t_AnyCuts->SetVal(true);
     }
     else if (a_elSectors == 1) { t_elSectors->SetTitle("El_sect_126"); fApplyPhiSliceEl_Sectors126 = true;}
     else if (a_elSectors == 0) { t_elSectors->SetTitle("El_sect_Nocut"); }
     else { 
         std::cout << "You have entered an invalid value for elSectors (parameter 5). Valid options are 0, 1, or 2. The given value is " << a_elSectors << "." << std::endl;
         std::cout << "If you are adding an option for elSectors (parameter 5), be sure to make the necessary changes in genie_analysis.C, genie_analysis.h, and run_genie_analysis.C." << std::endl;
     }

     if (a_protSectors == 1) {
         fApplyPhiSliceProt_Sectors = true;
         t_AnyCuts->SetVal(true);
         if (a_elSectors == 2) { t_protSectors->SetTitle("Prot_sect_43"); }
         if (a_elSectors == 1) { t_protSectors->SetTitle("Prot_sect_453"); }
     }
     else if (a_protSectors == 0) { t_protSectors->SetTitle("Prot_Sect_Nocut"); }
     else { 
       	 std::cout << "You have entered an invalid value for protSectors (parameter 10). Valid options are 0 or 1. The given value is " << a_protSectors << "." << std::endl;
       	 std::cout << "If you are adding an option for protSectors (parameter 10), be sure to make the necessary changes in genie_analysis.C, genie_analysis.h, and run_genie_analysis.C." << std::endl;
     } 

     if (a_deltaPhiEl == 1) {
        t_deltaPhiEl->SetVal(2 * PhiOpeningAngleEl); 
        fApplyPhiOpeningAngleEl = true;
        t_AnyCuts->SetVal(true);
     }
     else if (a_deltaPhiEl == 0) { t_deltaPhiEl->SetVal(9999); }
     else {
         std::cout << "You have entered an invalid value for deltaPhiEl (parameter 6). Valid options are 0 or 1. The given value is " << a_deltaPhiEl << "." << std::endl;
     }

     if (a_deltaPhiProt == 1) { 
        t_deltaPhiProt->SetVal(2 * PhiOpeningAngleProt); 
        fApplyPhiOpeningAngleProt = true;
        t_AnyCuts->SetVal(true);
     }
     else if (a_deltaPhiProt == 0) {t_deltaPhiProt->SetVal(9999);}
     else {
         std::cout << "You have entered an invalid value for deltaPhiProt (parameter 11). Valid options are 0 or 1. The given value is " << a_deltaPhiProt << "." << std::endl;
     } 

     // Electron theta lower and uper bounds
    if((a_thetaEl_lb + a_thetaEl_ub) < 180 && a_thetaEl_lb < a_thetaEl_ub) {
        t_thetaEl_lb->SetVal(a_thetaEl_lb); t_thetaEl_ub->SetVal(a_thetaEl_ub); 
        std::cout << "El theta lb = " << a_thetaEl_lb << ", El theta ub = " << a_thetaEl_ub<< "\n";
        fApplyThetaSliceEl = true;
        t_AnyCuts->SetVal(true);
    }
    
    // Electron momentum lower bound
    if( a_elMom_lb > 0 ) {
        t_elMom_lb->SetVal(a_elMom_lb); 
        fApplyElMomCut = true; 
        t_AnyCuts->SetVal(true);
    }

        // Proton theta lower and upper bounds
    if((a_thetaProt_lb + a_thetaProt_ub) < 180 && a_thetaProt_lb < a_thetaProt_ub) {
        t_thetaProt_lb->SetVal(a_thetaProt_lb); t_thetaProt_ub->SetVal(a_thetaProt_ub); 
        fApplyThetaSliceProt = true;
        t_AnyCuts->SetVal(true);
    }
    // Proton momentum lower and  upper bounds
    //if((a_protMom_lb + a_protMom_ub) > 0 && a_protMom_lb < a_protMom_ub) {
       //testing effect of proton momentum cut on missing energy and momentum distributions
        t_ProtMom_lb->SetVal(0); t_ProtMom_ub->SetVal(99999);
        //t_ProtMom_lb->SetVal(0.5);
        fApplyProtMomCut = false;
   // }

    fAllSectors = a_AllSectors;
    fFiducials = a_Fiducials;
    fAccWeights = a_AccWeights;
    fReso = a_Reso;
    fSignal = a_Signal;

    my_options->Add(t_nentries);
    my_options->Add(t_beam_en);
    my_options->Add(t_deltaPhiEl);
    my_options->Add(t_thetaEl_lb);
    my_options->Add(t_thetaEl_ub);
    my_options->Add(t_elMom_lb);
    my_options->Add(t_deltaPhiProt);
    my_options->Add(t_thetaProt_lb);
    my_options->Add(t_thetaProt_ub);
    my_options->Add(t_ProtMom_lb);
    my_options->Add(t_ProtMom_ub);
    my_options->Add(t_elSectors);
    my_options->Add(t_protSectors);
    my_options->Add(t_AnyCuts);

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("gst",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("gst","genie_analysis");

	if (fchoice == 0) { 

		chain->Add(Form("/pnfs/genie/persistent/users/apapadop/JLabSkimmed_1M/Skimmed_1M_e4vWorkshop_%s_%s.root",ftarget.c_str(), fbeam_en.c_str())); 
		//chain->Add(Form("/w/hallb-scifs17exp/clas/claseg2/apapadop/e4v_Workshop/e4vWorkshop_%s_%s.root",ftarget.c_str(), fbeam_en.c_str())); 
	}

      if (fchoice == 1) { 
		//std::cout << "What is going on" << "\n";
      		// Non radiative SuSav2
		//chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/%s_%sGeV/apapadop_SuSav2_%s_%sGeV_master.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));

		//Testing SuSAv2 (hA) with CFG
		chain->Add("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/2024Generation/GEM21_11a_Dipole_CFG_Q2_04_2GeV_eCarbon.gst.root");
		//chain->Add("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/2261/C12_SF_hN/EmQ2_04-routine_validation_01-eScattering/e4v_2261_hN_SF.gst.root");
      		// Ext Radiation SuSav2
//		  chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/%s_%sGeV/apapadop_Rad_SuSav2_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));  

      		// Ext_Int Radiation SuSav2
//		  chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/%s_%sGeV/apapadop_UpdatedSchwingerRad_SuSav2_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));  		   

		// Afro Tutorial File
//                chain->Add("/pnfs/genie/persistent/users/apapadop/e4v_Workshop_C12_1GeV_TestSample.root");
	}

      if (fchoice == 2) { 
      
		//std::cout << ((a_beam_en.compare("4461") == 0) && (ftarget.compare("C12") == 0)) << "\n";

      		// Non Radiative G2018
	
		if((a_beam_en.compare("2261") == 0) && (ftarget.compare("C12") == 0)) {
			std::cout << "did we make it in?" << "\n";
			chain->Add("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/2261/C12_G2018/master_Q2_0_4-routine_validation_01-eScattering/nsteinbe_G2018_C12_2261GeV_master.root");
		//adding G18 C12 2 GeV file with no FSI
		//chain->Add("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/EventGeneration/G18_10a_00_000/G18_10a_Q2_04_NoFSI_e_on_1000060120_2261MeV_NoRad.gst.root");
		}

		else if((a_beam_en.compare("4461") == 0) && (ftarget.compare("C12") == 0)) {
			std::cout << "did we make it in?" << "\n";
			chain->Add("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/4461/C12_G2018/master_Q2_0_8-routine_validation_01-eScattering/nsteinbe_G2018_C12_4461GeV_master.root");
		}

		else {
			std::cout << "What is going on" << "\n";
			chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/%s_%sGeV/apapadop_G2018_%s_%sGeV_master*.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));
		}

		
		//chain->Add("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/C12_1161_Q2cut_FSIoff.gst.root");
		//chain->Add("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/C12_2261_Q2cut_FSIoff2.gst.root");

	//	chain->Add(Form("/pnfs/genie/persistent/users/gchamber/Grid/output/C12_2261/C12_2261_EMQE_G18_02a_00_000_redo3_FSI.root")); 
		//chain->Add(Form("/genie/app/users/gchamber/e4nu_2022/e4nu/Simulations/output/C12_2261/C12_2261_EMQE_G18_02a_00_000_noFSI_bigstat.root")); 
		//chain->Add("/genie/app/users/gchamber/Generator/simulations/C12/1_161/G18_10a_02_11a/FSI/genie_gst_C12_1161_el_G18_10a_02_11a_FSI_50k.root");
      		// Ext Radiation G2018

//		chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/%s_%sGeV/apapadop_Rad_G2018_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));

      		// Ext+Int Radiation G2018

		//chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/%s_%sGeV/apapadop_UpdatedSchwingerRad_G2018_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));

	}

	if (fchoice == 3) { 

      		// Ext_Int Radiation SuSav2
		
		chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/%s_%sGeV/apapadop_UpdatedSchwingerRad_SuSav2_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));  	

	}

	if (fchoice == 4) {

      		// Ext+Int Radiation G2018

		chain->Add(Form("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/%s_%sGeV/apapadop_UpdatedSchwingerRad_G2018_%s_%sGeV.root", ftarget.c_str(),fbeam_en.c_str(),ftarget.c_str(),fbeam_en.c_str()));

	} 

      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

genie_analysis::~genie_analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t genie_analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t genie_analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void genie_analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);


   fChain->SetBranchAddress("iev", &iev, &b_iev);
   fChain->SetBranchAddress("neu", &neu, &b_neu);
   fChain->SetBranchAddress("fspl", &fspl, &b_fspl);
   fChain->SetBranchAddress("tgt", &tgt, &b_tgt);
   fChain->SetBranchAddress("Z", &Z, &b_Z);
   fChain->SetBranchAddress("A", &A, &b_A);
   fChain->SetBranchAddress("hitnuc", &hitnuc, &b_hitnuc);
   fChain->SetBranchAddress("hitqrk", &hitqrk, &b_hitqrk);
   fChain->SetBranchAddress("resid", &resid, &b_resid);
   fChain->SetBranchAddress("sea", &sea, &b_sea);
   fChain->SetBranchAddress("qel", &qel, &b_qel);
   fChain->SetBranchAddress("mec", &mec, &b_mec);//go down from here
   fChain->SetBranchAddress("res", &res, &b_res);
   fChain->SetBranchAddress("dis", &dis, &b_dis);
   fChain->SetBranchAddress("coh", &coh, &b_coh);
   fChain->SetBranchAddress("dfr", &dfr, &b_dfr);
   fChain->SetBranchAddress("imd", &imd, &b_imd);
   fChain->SetBranchAddress("imdanh", &imdanh, &b_imdanh);
   fChain->SetBranchAddress("singlek", &singlek, &b_singlek);
   fChain->SetBranchAddress("nuel", &nuel, &b_nuel);
   fChain->SetBranchAddress("em", &em, &b_em);
   fChain->SetBranchAddress("cc", &cc, &b_cc);
   fChain->SetBranchAddress("nc", &nc, &b_nc);
   fChain->SetBranchAddress("charm", &charm, &b_charm);
   fChain->SetBranchAddress("neut_code", &neut_code, &b_neut_code);
   fChain->SetBranchAddress("nuance_code", &nuance_code, &b_nuance_code);
   fChain->SetBranchAddress("wght", &wght, &b_wght);
   fChain->SetBranchAddress("xs", &xs, &b_xs);
   fChain->SetBranchAddress("ys", &ys, &b_ys);
   fChain->SetBranchAddress("ts", &ts, &b_ts);
   fChain->SetBranchAddress("Q2s", &Q2s, &b_Q2s);
   fChain->SetBranchAddress("Ws", &Ws, &b_Ws);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("Q2", &Q2, &b_Q2);
   fChain->SetBranchAddress("W", &W, &b_W);
   fChain->SetBranchAddress("EvRF", &EvRF, &b_EvRF);
   fChain->SetBranchAddress("Ev", &Ev, &b_Ev);
   fChain->SetBranchAddress("pxv", &pxv, &b_pxv);
   fChain->SetBranchAddress("pyv", &pyv, &b_pyv);
   fChain->SetBranchAddress("pzv", &pzv, &b_pzv);
   fChain->SetBranchAddress("En", &En, &b_En);
   fChain->SetBranchAddress("pxn", &pxn, &b_pxn);
   fChain->SetBranchAddress("pyn", &pyn, &b_pyn);
   fChain->SetBranchAddress("pzn", &pzn, &b_pzn);
   fChain->SetBranchAddress("El", &El, &b_El);
   fChain->SetBranchAddress("pxl", &pxl, &b_pxl);
   fChain->SetBranchAddress("pyl", &pyl, &b_pyl);
   fChain->SetBranchAddress("pzl", &pzl, &b_pzl);
   fChain->SetBranchAddress("pl", &pl, &b_pl);
   fChain->SetBranchAddress("cthl", &cthl, &b_cthl);
   fChain->SetBranchAddress("nfp", &nfp, &b_nfp);
   fChain->SetBranchAddress("nfn", &nfn, &b_nfn);
   fChain->SetBranchAddress("nfpip", &nfpip, &b_nfpip);
   fChain->SetBranchAddress("nfpim", &nfpim, &b_nfpim);
   fChain->SetBranchAddress("nfpi0", &nfpi0, &b_nfpi0);
   fChain->SetBranchAddress("nfkp", &nfkp, &b_nfkp);
   fChain->SetBranchAddress("nfkm", &nfkm, &b_nfkm);
   fChain->SetBranchAddress("nfk0", &nfk0, &b_nfk0);
   fChain->SetBranchAddress("nfem", &nfem, &b_nfem);
   fChain->SetBranchAddress("nfother", &nfother, &b_nfother);
   fChain->SetBranchAddress("nip", &nip, &b_nip);
   fChain->SetBranchAddress("nin", &nin, &b_nin);
   fChain->SetBranchAddress("nipip", &nipip, &b_nipip);
   fChain->SetBranchAddress("nipim", &nipim, &b_nipim);
   fChain->SetBranchAddress("nipi0", &nipi0, &b_nipi0);
   fChain->SetBranchAddress("nikp", &nikp, &b_nikp);
   fChain->SetBranchAddress("nikm", &nikm, &b_nikm);
   fChain->SetBranchAddress("nik0", &nik0, &b_nik0);
   fChain->SetBranchAddress("niem", &niem, &b_niem);
   fChain->SetBranchAddress("niother", &niother, &b_niother);
   fChain->SetBranchAddress("ni", &ni, &b_ni);
   fChain->SetBranchAddress("pdgi", pdgi, &b_pdgi);
   fChain->SetBranchAddress("resc", resc, &b_resc);
   fChain->SetBranchAddress("Ei", Ei, &b_Ei);
   fChain->SetBranchAddress("pxi", pxi, &b_pxi);
   fChain->SetBranchAddress("pyi", pyi, &b_pyi);
   fChain->SetBranchAddress("pzi", pzi, &b_pzi);
   fChain->SetBranchAddress("nf", &nf, &b_nf);
   fChain->SetBranchAddress("pdgf", pdgf, &b_pdgf);
   fChain->SetBranchAddress("Ef", Ef, &b_Ef);
   fChain->SetBranchAddress("pxf", pxf, &b_pxf);
   fChain->SetBranchAddress("pyf", pyf, &b_pyf);
   fChain->SetBranchAddress("pzf", pzf, &b_pzf);
   fChain->SetBranchAddress("pf", pf, &b_pf);
   fChain->SetBranchAddress("cthf", cthf, &b_cthf);
   fChain->SetBranchAddress("vtxx", &vtxx, &b_vtxx);
   fChain->SetBranchAddress("vtxy", &vtxy, &b_vtxy);
   fChain->SetBranchAddress("vtxz", &vtxz, &b_vtxz);
   fChain->SetBranchAddress("vtxt", &vtxt, &b_vtxt);
   fChain->SetBranchAddress("sumKEf", &sumKEf, &b_sumKEf);
   fChain->SetBranchAddress("calresp0", &calresp0, &b_calresp0);



   Notify();
}

Bool_t genie_analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void genie_analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t genie_analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef genie_analysis_h
