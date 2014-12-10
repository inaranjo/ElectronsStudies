//--------------------------------------------------------------------------------------------------
// makeRootFilesAntiEMVA 
//
// Macro creating signal and background rootFiles from the ouput tree of the AntiEMVA analyzer. 
// Signal is when the branch for matching with a hadron from tau is 1.
// Background is when the branch for matching with an electron is 1.
// It also separates into 5 categories -> 5 different Rootfiles for Signal and the same for Bkg.
//
// Authors: I.Naranjo
//--------------------------------------------------------------------------------------------------
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TPad.h"
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TAxis.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include "TCut.h"

#include <string>
#include <map>
#include <iostream>
#include <iomanip>

#define DEBUG false

bool isInEcalCrack(Float_t eta) 
{
  eta = fabs(eta);
  return(eta>1.460 && eta<1.558);
}

bool isInEcalCrackAll(Float_t eta) 
{
  eta = fabs(eta);
  return(eta < 0.018 ||
	 (eta>0.423 && eta<0.461) ||
	 (eta>0.770 && eta<0.806) ||
	 (eta>1.127 && eta<1.163) ||
	 (eta>1.460 && eta<1.558));
}

//useful to compute the signed distance to the closest crack in the barrel
double minimum(double a,double b){
  if(TMath::Abs(b)<TMath::Abs(a)) return b;
  else return a;
}

//compute the unsigned distance to the closest phi-crack in the barrel
double dCrackPhi(double phi, double eta){

  double pi= TMath::Pi();// 3.14159265358979323846;
  
  //Location of the 18 phi-cracks
  static std::vector<double> cPhi;
  if(cPhi.size()==0)
    {
      cPhi.resize(18,0);
      cPhi[0]=2.97025;
      for(unsigned i=1;i<=17;++i) cPhi[i]=cPhi[0]-2*i*pi/18;
    }

  //Shift of this location if eta<0
  double delta_cPhi=0.00638;

  double m; //the result

  if (eta>=- 1.47464 && eta<= 1.47464){

    //the location is shifted
    if(eta<0) phi +=delta_cPhi;

    if (phi>=-pi && phi<=pi){

      //the problem of the extrema
      if (phi<cPhi[17] || phi>=cPhi[0]){
	if (phi<0) phi+= 2*pi;
	m = minimum(phi -cPhi[0],phi-cPhi[17]-2*pi);        	
      }

      //between these extrema...
      else{
	bool OK = false;
	unsigned i=16;
	while(!OK){
	  if (phi<cPhi[i]){
	    m=minimum(phi-cPhi[i+1],phi-cPhi[i]);
	    OK=true;
	  }
	  else i-=1;
	}
      }
    }
    else{
      m=0.;        //if there is a problem, we assum that we are in a crack
//       std::cout<<"Problem in dminphi"<<std::endl;
    }
  }
  else{
    return -99.;       
    std::cout<<"Encap region"<<std::endl;
  }
  
  return TMath::Abs(m);
}

//compute the unsigned distance to the closest phi-crack in the barrel
double dCrackEta(double eta){
  
  //Location of the eta-cracks
  double cracks[5] = {0, 4.44747e-01, 7.92824e-01, 1.14090e+00, 1.47464e+00};
  
  double m=99.; //the result
  
  for(int i=0;i<5;i++){
    double d = minimum(eta-cracks[i], eta+cracks[i]);
    if (TMath::Abs(d)<TMath::Abs(m)){
      m=d;
    }
  }

  return TMath::Abs(m);
}

void test_dCrackEta()
{
  std::vector<double> etaTestValues;
  etaTestValues.push_back(-2.);
  etaTestValues.push_back(-1.6);
  etaTestValues.push_back(-1.5);
  etaTestValues.push_back(-1.4);
  etaTestValues.push_back(-0.45);
  etaTestValues.push_back(-0.44);
  etaTestValues.push_back(-0.1);
  etaTestValues.push_back(0.);
  etaTestValues.push_back(0.1);
  etaTestValues.push_back(0.2);
  etaTestValues.push_back(0.8);
  etaTestValues.push_back(1.1);
  etaTestValues.push_back(1.2);
  etaTestValues.push_back(1.4);
  etaTestValues.push_back(1.5);
  etaTestValues.push_back(1.6);
  etaTestValues.push_back(1.7);
  
  for ( std::vector<double>::const_iterator eta = etaTestValues.begin();
	eta != etaTestValues.end(); ++eta ) {
    std::cout << "eta = " << (*eta) << ": dCrack = " << dCrackEta(*eta) << std::endl;
  }
}

void makeRoot(string matching = "Elec",
	      string category = "woG",
	      string discriminator = "",
	      string Region = "Barrel"
	      )
{
  TChain *inputTree = new TChain("AntiEMVAAnalyzer2/tree");
//   TString pathToFile = "/data_CMS/cms/ivo/AntiEMVANewTraining/Trees/AntiEMVATrees-DYJetsToLL-madgraph-DR53X-Summer12-iter2/";
  TString pathToFile = "/data_CMS/cms/ivo/AntiEMVANewTraining/Trees/";
  inputTree->Add(pathToFile+"/AntiEMVATrees-DYJetsToLL-madgraph-DR53X-Summer12-iter5/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-BBH130-pythia-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-BBH160-pythia-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-BBH180-pythia-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-BBH450-pythia-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-GGFH120-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-GGFH160-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-GGFH250-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-GGFH300-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-GGFH400-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-TTJets-madgraph-DR53X-Summer12-iter3/AntiEMVA*.root");
//   inputTree->Add(pathToFile+"/AntiEMVATrees-VBFH120-powheg-DR53X-Summer12-iter3/AntiEMVA*.root");

  int nEntries = inputTree->GetEntries();

// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV6AndV7/AntiEMVA_V7.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV6AndV7/AntiEMVA_V6iter1.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV6AndV7/AntiEMVA_V6.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9/AntiEMVA_V9.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9/AntiEMVA_AntiEMVATrees-DYJetsToLL-madgraph-DR53X-Summer12.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9V10V11/AntiEMVA_V12.root";
// //    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9V10V11/AntiEMVA_V9.root";
//    std::string inputFileName = "/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV13/AntiEMVA_V13.root";
//   TFile* inputFile = new TFile (inputFileName.data(),"READ");
//   if(inputFile->IsZombie()){
//     cout << "No such file!" << endl;
//     return;
//   }

//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/tree_testAntiEMVA%s_%s_%s.root",discriminator.data(),category.data(),matching.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/tree_AntiEMVA-EleVeto%s_%s_%s_%s.root",discriminator.data(),category.data(),matching.data(),Region.data());
  std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVANewTraining/root/tree_AntiEMVA-DY%s_%s_%s_%s.root",discriminator.data(),category.data(),matching.data(),Region.data());

  TFile* outputFile = new TFile (outputFileName.data(),"RECREATE");
  TTree* mytree = new TTree("tree", "tree");

//   for(int i=0;i<5;i++){
//     mytree[i]= new TTree(Form("tree%i",i), "tree");
//   }
//   TTree* mytree[5];
//   for(int i=0;i<5;i++){
//     mytree[i]= new TTree(Form("tree%i",i), "tree");
//   }

  ULong64_t t_run_,t_event_,t_lumi_;
  int t_NumPV_;
  int t_NumGsfEle_;
  int t_NumPFTaus_;
  int t_NumGenEle_;
  int t_NumGenHad_;
  int t_NumGenJet_;

  int t_Elec_GenEleMatch_;
  int t_Elec_GenEleFromZMatch_;
  int t_Elec_GenEleFromZTauTauMatch_;
  int t_Elec_GenHadMatch_;
  int t_Elec_GenJetMatch_;
  float t_Elec_AbsEta_;
  float t_Elec_HasSC_;
  float t_Elec_Pt_;
  float t_Elec_PFMvaOutput_;
  float t_Elec_Ee_;
  float t_Elec_Egamma_;
  float t_Elec_Pin_;
  float t_Elec_Pout_;
  float t_Elec_EtotOverPin_;
  float t_Elec_EeOverPout_;
  float t_Elec_EgammaOverPdif_;
  int t_Elec_EarlyBrem_;
  int t_Elec_LateBrem_;
  float t_Elec_Logsihih_;
  float t_Elec_DeltaEta_;
  float t_Elec_HoHplusE_;
  float t_Elec_Fbrem_;
  float t_Elec_HasKF_;
  float t_Elec_Chi2KF_;
  float t_Elec_KFNumHits_;
  float t_Elec_KFNumPixelHits_;
  float t_Elec_KFNumStripHits_;
  float t_Elec_KFTrackResol_;
  float t_Elec_KFTracklnPt_;
  float t_Elec_KFTrackEta_;
  float t_Elec_HasGSF_;
  float t_Elec_Chi2GSF_;
  float t_Elec_GSFNumHits_;
  float t_Elec_GSFNumPixelHits_;
  float t_Elec_GSFNumStripHits_;
  float t_Elec_GSFTrackResol_;
  float t_Elec_GSFTracklnPt_;
  float t_Elec_GSFTrackEta_;


  int t_Tau_GsfEleMatch_;
  int t_Tau_GenEleMatch_;
  int t_Tau_GenEleFromZMatch_;
  int t_Tau_GenEleFromZTauTauMatch_;
  int t_Tau_GenHadMatch_;
  int t_Tau_GenJetMatch_;
  float t_Tau_Eta_;
  float t_Tau_EtaAtEcalEntrance_;
  float t_Tau_PhiAtEcalEntrance_;
  float t_Tau_Phi_;
  float t_Tau_dCrackPhi_;
  float t_Tau_dCrackEta_;
  float t_Tau_Pt_;
  float t_Tau_LeadHadronPt_;
  float t_Tau_HasGsf_; 
  float t_Tau_GSFChi2_; 
  float t_Tau_GSFNumHits_; 
  float t_Tau_GSFNumPixelHits_; 
  float t_Tau_GSFNumStripHits_; 
  float t_Tau_GSFTrackResol_; 
  float t_Tau_GSFTracklnPt_; 
  float t_Tau_GSFTrackEta_; 
  float t_Tau_HasKF_; 
  float t_Tau_KFChi2_; 
  float t_Tau_KFNumHits_; 
  float t_Tau_KFNumPixelHits_; 
  float t_Tau_KFNumStripHits_; 
  float t_Tau_KFTrackResol_; 
  float t_Tau_KFTracklnPt_; 
  float t_Tau_KFTrackEta_; 
  float t_Tau_EmFraction_; 
  float t_Tau_NumChargedCands_;
  float t_Tau_NumGammaCands_; 
  float t_Tau_HadrHoP_; 
  float t_Tau_HadrEoP_; 
  float t_Tau_VisMass_; 
  float t_Tau_GammaEtaMom_;
  float t_Tau_GammaPhiMom_;
  float t_Tau_GammaEnFrac_;
  float t_Tau_HadrMva_; 
  float t_Tau_AntiELoose_; 
  float t_Tau_AntiEMedium_; 
  float t_Tau_AntiETight_; 
  float t_Tau_AntiELooseMVA3_; 
  float t_Tau_AntiEMediumMVA3_; 
  float t_Tau_AntiETightMVA3_; 
  float t_Tau_AntiEVTightMVA3_; 
  float t_Tau_DecayMode_; 
  float t_Tau_MatchElePassVeto_;

  //counters
  mytree->Branch("run",&t_run_,"run/l");
  mytree->Branch("event",&t_event_,"event/l");
  mytree->Branch("lumi",&t_lumi_,"lumi/l");
  mytree->Branch("NumPV",&t_NumPV_,"NumPV/I");
  mytree->Branch("NumGsfEle",&t_NumGsfEle_,"NumGsfEle/I");
  mytree->Branch("NumGenEle",&t_NumGenEle_,"NumGenEle/I");
  mytree->Branch("NumPFTaus",&t_NumPFTaus_,"NumPFTaus/I");
  mytree->Branch("NumGenHad",&t_NumGenHad_,"NumGenHad/I");
  mytree->Branch("NumGenJet",&t_NumGenJet_,"NumGenEJet/I");

  //GsfElectron variables
  mytree->Branch("Elec_GenEleMatch",&t_Elec_GenEleMatch_,"Elec_GenEleMatch/I");
  mytree->Branch("Elec_GenEleFromZMatch",&t_Elec_GenEleFromZMatch_,"Elec_GenEleFromZMatch/I");
  mytree->Branch("Elec_GenEleFromZTauTauMatch",&t_Elec_GenEleFromZTauTauMatch_,"Elec_GenEleFromZTauTauMatch/I");
  mytree->Branch("Elec_GenHadMatch",&t_Elec_GenHadMatch_,"Elec_GenHadMatch/I");
  mytree->Branch("Elec_GenJetMatch",&t_Elec_GenJetMatch_,"Elec_GenJetMatch/I");
  mytree->Branch("Elec_AbsEta",&t_Elec_AbsEta_,"Elec_AbsEta/F");
  mytree->Branch("Elec_HasSC",&t_Elec_HasSC_,"Elec_HasSC/F");
  mytree->Branch("Elec_Pt",&t_Elec_Pt_,"Elec_Pt/F");
  mytree->Branch("Elec_PFMvaOutput",&t_Elec_PFMvaOutput_,"Elec_PFMvaOutput/F");
  mytree->Branch("Elec_Ee",&t_Elec_Ee_,"Elec_Ee/F");
  mytree->Branch("Elec_Egamma",&t_Elec_Egamma_,"Elec_Egamma/F");
  mytree->Branch("Elec_Pin",&t_Elec_Pin_,"Elec_Pin/F");
  mytree->Branch("Elec_Pout",&t_Elec_Pout_,"Elec_Pout/F");
  mytree->Branch("Elec_EtotOverPin",&t_Elec_EtotOverPin_,"Elec_EtotOverPin/F");
  mytree->Branch("Elec_EeOverPout",&t_Elec_EeOverPout_,"Elec_EeOverPout/F");
  mytree->Branch("Elec_EgammaOverPdif",&t_Elec_EgammaOverPdif_,"Elec_EgammaOverPdif/F");
  mytree->Branch("Elec_EarlyBrem",&t_Elec_EarlyBrem_,"Elec_EarlyBrem/I");
  mytree->Branch("Elec_LateBrem",&t_Elec_LateBrem_,"Elec_LateBrem/I");
  mytree->Branch("Elec_Logsihih",&t_Elec_Logsihih_,"Elec_Logsihih/F");
  mytree->Branch("Elec_DeltaEta",&t_Elec_DeltaEta_,"Elec_DeltaEta/F");
  mytree->Branch("Elec_HoHplusE",&t_Elec_HoHplusE_,"Elec_HoHplusE/F");
  mytree->Branch("Elec_Fbrem",&t_Elec_Fbrem_,"Elec_Fbrem/F");
  mytree->Branch("Elec_HasKF",&t_Elec_HasKF_,"Elec_HasKF/F");
  mytree->Branch("Elec_Chi2KF",&t_Elec_Chi2KF_,"Elec_Chi2KF/F");
  mytree->Branch("Elec_KFNumHits",&t_Elec_KFNumHits_,"Elec_KFNumHits/F");
  mytree->Branch("Elec_KFNumPixelHits",&t_Elec_KFNumPixelHits_,"Elec_KFNumPixelHits/F");
  mytree->Branch("Elec_KFNumStripHits",&t_Elec_KFNumStripHits_,"Elec_KFNumStripHits/F");
  mytree->Branch("Elec_KFTrackResol",&t_Elec_KFTrackResol_,"Elec_KFTrackResol/F");
  mytree->Branch("Elec_KFTracklnPt",&t_Elec_KFTracklnPt_,"Elec_KFTracklnPt/F");
  mytree->Branch("Elec_KFTrackEta",&t_Elec_KFTrackEta_,"Elec_KFTrackEta/F");
  mytree->Branch("Elec_HasGSF",&t_Elec_HasGSF_,"Elec_HasGSF/F");
  mytree->Branch("Elec_Chi2GSF",&t_Elec_Chi2GSF_,"Elec_Chi2GSF/F");
  mytree->Branch("Elec_GSFNumHits",&t_Elec_GSFNumHits_,"Elec_GSFNumHits/F");
  mytree->Branch("Elec_GSFNumPixelHits",&t_Elec_GSFNumPixelHits_,"Elec_GSFNumPixelHits/F");
  mytree->Branch("Elec_GSFNumStripHits",&t_Elec_GSFNumStripHits_,"Elec_GSFNumStripHits/F");
  mytree->Branch("Elec_GSFTrackResol",&t_Elec_GSFTrackResol_,"Elec_GSFTrackResol/F");
  mytree->Branch("Elec_GSFTracklnPt",&t_Elec_GSFTracklnPt_,"Elec_GSFTracklnPt/F");
  mytree->Branch("Elec_GSFTrackEta",&t_Elec_GSFTrackEta_,"Elec_GSFTrackEta/F");
  //PFTaus variables
  mytree->Branch("Tau_GsfEleMatch",&t_Tau_GsfEleMatch_,"Tau_GsfEleMatch/I");
  mytree->Branch("Tau_GenEleMatch",&t_Tau_GenEleMatch_,"Tau_GenEleMatch/I");
  mytree->Branch("Tau_GenEleFromZMatch",&t_Tau_GenEleFromZMatch_,"Tau_GenEleFromZMatch/I");
  mytree->Branch("Tau_GenEleFromZTauTauMatch",&t_Tau_GenEleFromZTauTauMatch_,"Tau_GenEleFromZTauTauMatch/I");
  mytree->Branch("Tau_GenHadMatch",&t_Tau_GenHadMatch_,"Tau_GenHadMatch/I");
  mytree->Branch("Tau_GenJetMatch",&t_Tau_GenJetMatch_,"Tau_GenJetMatch/I");
  mytree->Branch("Tau_Eta",&t_Tau_Eta_,"Tau_Eta/F");
  mytree->Branch("Tau_EtaAtEcalEntrance",&t_Tau_EtaAtEcalEntrance_,"Tau_EtaAtEcalEntrance/F");
  mytree->Branch("Tau_PhiAtEcalEntrance",&t_Tau_PhiAtEcalEntrance_,"Tau_PhiAtEcalEntrance/F");
  mytree->Branch("Tau_Phi",&t_Tau_Phi_,"Tau_Phi/F");
  mytree->Branch("Tau_dCrackPhi",&t_Tau_dCrackPhi_,"Tau_dCrackPhi/F");
  mytree->Branch("Tau_dCrackEta",&t_Tau_dCrackEta_,"Tau_dCrackEta/F");
  mytree->Branch("Tau_Pt",&t_Tau_Pt_,"Tau_Pt/F");
  mytree->Branch("Tau_LeadHadronPt",&t_Tau_LeadHadronPt_,"Tau_LeadHadronPt/F");
  mytree->Branch("Tau_HasGsf",&t_Tau_HasGsf_,"Tau_HasGsf/F");
  mytree->Branch("Tau_GSFChi2",&t_Tau_GSFChi2_,"Tau_GSFChi2/F");
  mytree->Branch("Tau_GSFNumHits",&t_Tau_GSFNumHits_,"Tau_GSFNumHits/F");
  mytree->Branch("Tau_GSFNumPixelHits",&t_Tau_GSFNumPixelHits_,"Tau_GSFNumPixelHits/F");
  mytree->Branch("Tau_GSFNumStripHits",&t_Tau_GSFNumStripHits_,"Tau_GSFNumStripHits/F");
  mytree->Branch("Tau_GSFTrackResol",&t_Tau_GSFTrackResol_,"Tau_GSFTrackResol/F");
  mytree->Branch("Tau_GSFTracklnPt",&t_Tau_GSFTracklnPt_,"Tau_GSFTracklnPt/F");
  mytree->Branch("Tau_GSFTrackEta",&t_Tau_GSFTrackEta_,"Tau_GSFTrackEta/F");
  mytree->Branch("Tau_HasKF",&t_Tau_HasKF_,"Tau_HasKF/F");
  mytree->Branch("Tau_KFChi2",&t_Tau_KFChi2_,"Tau_KFChi2/F");
  mytree->Branch("Tau_KFNumHits",&t_Tau_KFNumHits_,"Tau_KFNumHits/F");
  mytree->Branch("Tau_KFNumPixelHits",&t_Tau_KFNumPixelHits_,"Tau_KFNumPixelHits/F");
  mytree->Branch("Tau_KFNumStripHits",&t_Tau_KFNumStripHits_,"Tau_KFNumStripHits/F");
  mytree->Branch("Tau_KFTrackResol",&t_Tau_KFTrackResol_,"Tau_KFTrackResol/F");
  mytree->Branch("Tau_KFTracklnPt",&t_Tau_KFTracklnPt_,"Tau_KFTracklnPt/F");
  mytree->Branch("Tau_KFTrackEta",&t_Tau_KFTrackEta_,"Tau_KFTrackEta/F");
  mytree->Branch("Tau_EmFraction",&t_Tau_EmFraction_,"Tau_EmFraction/F");
  mytree->Branch("Tau_NumChargedCands",&t_Tau_NumChargedCands_,"Tau_NumChargedCands/F");
  mytree->Branch("Tau_NumGammaCands",&t_Tau_NumGammaCands_,"Tau_NumGammaCands/F");
  mytree->Branch("Tau_HadrHoP",&t_Tau_HadrHoP_,"Tau_HadrHoP/F");
  mytree->Branch("Tau_HadrEoP",&t_Tau_HadrEoP_,"Tau_HadrEoP/F");
  mytree->Branch("Tau_VisMass",&t_Tau_VisMass_,"Tau_VisMass/F");
  mytree->Branch("Tau_GammaEtaMom",&t_Tau_GammaEtaMom_,"Tau_GammaEtaMom/F");
  mytree->Branch("Tau_GammaPhiMom",&t_Tau_GammaPhiMom_,"Tau_GammaPhiMom/F");
  mytree->Branch("Tau_GammaEnFrac",&t_Tau_GammaEnFrac_,"Tau_GammaEnFrac/F");
  mytree->Branch("Tau_HadrMva",&t_Tau_HadrMva_,"Tau_HadrMva/F");
  mytree->Branch("Tau_AntiELoose",&t_Tau_AntiELoose_,"Tau_AntiELoose/F");
  mytree->Branch("Tau_AntiEMedium",&t_Tau_AntiEMedium_,"Tau_AntiEMedium/F");
  mytree->Branch("Tau_AntiETight",&t_Tau_AntiETight_,"Tau_AntiETight/F");
  mytree->Branch("Tau_AntiELooseMVA3",&t_Tau_AntiELooseMVA3_,"Tau_AntiELooseMVA3/F");
  mytree->Branch("Tau_AntiEMediumMVA3",&t_Tau_AntiEMediumMVA3_,"Tau_AntiEMediumMVA3/F");
  mytree->Branch("Tau_AntiETightMVA3",&t_Tau_AntiETightMVA3_,"Tau_AntiETightMVA3/F");
  mytree->Branch("Tau_AntiEVTightMVA3",&t_Tau_AntiEVTightMVA3_,"Tau_AntiEVTightMVA3/F");
  mytree->Branch("Tau_DecayMode",&t_Tau_DecayMode_,"Tau_DecayMode/F");
  mytree->Branch("Tau_MatchElePassVeto",&t_Tau_MatchElePassVeto_,"Tau_MatchElePassVeto/F");


//   TTree* inputTree = (TTree*)inputFile->Get("AntiEMVAAnalyzer2/tree");
//   int nEntries = inputTree->GetEntries();

  ULong64_t run,event,lumi;
  int NumPV;
  int NumGsfEle;
  int NumPFTaus;
  int NumGenEle;
  int NumGenHad;
  int NumGenJet;

  int Elec_GenEleMatch;
  int Elec_GenEleFromZMatch;
  int Elec_GenEleFromZTauTauMatch;
  int Elec_GenHadMatch;
  int Elec_GenJetMatch;
  float Elec_AbsEta;
  float Elec_Pt;
  float Elec_HasSC;
  float Elec_PFMvaOutput;
  float Elec_Ee;
  float Elec_Egamma;
  float Elec_Pin;
  float Elec_Pout;
  float Elec_EtotOverPin;
  float Elec_EeOverPout;
  float Elec_EgammaOverPdif;
  int Elec_EarlyBrem;
  int Elec_LateBrem;
  float Elec_Logsihih;
  float Elec_DeltaEta;
  float Elec_HoHplusE;
  float Elec_Fbrem;
  float Elec_HasKF;
  float Elec_Chi2KF;
  float Elec_KFNumHits;
  float Elec_KFNumPixelHits;
  float Elec_KFNumStripHits;
  float Elec_KFTrackResol;
  float Elec_KFTracklnPt;
  float Elec_KFTrackEta;
  float Elec_HasGSF;
  float Elec_Chi2GSF;
  float Elec_GSFNumHits;
  float Elec_GSFNumPixelHits;
  float Elec_GSFNumStripHits;
  float Elec_GSFTrackResol;
  float Elec_GSFTracklnPt;
  float Elec_GSFTrackEta;

  int Tau_GsfEleMatch;
  int Tau_GenEleMatch;
  int Tau_GenEleFromZMatch;
  int Tau_GenEleFromZTauTauMatch;
  int Tau_GenHadMatch;
  int Tau_GenJetMatch;
  float Tau_Eta;
  float Tau_EtaAtEcalEntrance;
  float Tau_PhiAtEcalEntrance;
  float Tau_Phi;
  float Tau_Pt;
  float Tau_LeadHadronPt;
  float Tau_HasGsf; 
  float Tau_GSFChi2; 
  float Tau_GSFNumHits; 
  float Tau_GSFNumPixelHits; 
  float Tau_GSFNumStripHits; 
  float Tau_GSFTrackResol; 
  float Tau_GSFTracklnPt; 
  float Tau_GSFTrackEta; 
  float Tau_HasKF; 
  float Tau_KFChi2; 
  float Tau_KFNumHits; 
  float Tau_KFNumPixelHits; 
  float Tau_KFNumStripHits; 
  float Tau_KFTrackResol; 
  float Tau_KFTracklnPt; 
  float Tau_KFTrackEta; 
  float Tau_EmFraction; 
  float Tau_NumChargedCands;
  float Tau_NumGammaCands; 
  float Tau_HadrHoP; 
  float Tau_HadrEoP; 
  float Tau_VisMass; 
  float Tau_GammaEtaMom;
  float Tau_GammaPhiMom;
  float Tau_GammaEnFrac;
  float Tau_LooseComb3HitsIso; 
  float Tau_HadrMva; 
  float Tau_AntiELoose; 
  float Tau_AntiEMedium; 
  float Tau_AntiETight; 
  float Tau_AntiELooseMVA3; 
  float Tau_AntiEMediumMVA3; 
  float Tau_AntiETightMVA3; 
  float Tau_AntiEVTightMVA3; 
  float Tau_DecayMode; 
  float Tau_MatchElePassVeto;

  int ElecVeto_N;
  float ElecVeto_Pt;
  float ElecVeto_Eta;
  float ElecVeto_Phi;

  inputTree->SetBranchAddress("run", &run);
  inputTree->SetBranchAddress("event", &event);
  inputTree->SetBranchAddress("lumi", &lumi);
  inputTree->SetBranchAddress("NumPV", &NumPV );
  inputTree->SetBranchAddress("NumGsfEle", &NumGsfEle );
  inputTree->SetBranchAddress("NumPFTaus", &NumPFTaus );
  inputTree->SetBranchAddress("NumGenEle", &NumGenEle );
  inputTree->SetBranchAddress("NumGenHad", &NumGenHad );
  inputTree->SetBranchAddress("NumGenJet", &NumGenJet );

  //GsfElectron variables
  inputTree->SetBranchAddress("Elec_GenEleMatch", &Elec_GenEleMatch );
  inputTree->SetBranchAddress("Elec_GenEleFromZMatch", &Elec_GenEleFromZMatch);
  inputTree->SetBranchAddress("Elec_GenEleFromZTauTauMatch", &Elec_GenEleFromZTauTauMatch );
  inputTree->SetBranchAddress("Elec_GenHadMatch", &Elec_GenHadMatch );
  inputTree->SetBranchAddress("Elec_GenJetMatch", &Elec_GenJetMatch );
  inputTree->SetBranchAddress("Elec_AbsEta", &Elec_AbsEta );
  inputTree->SetBranchAddress("Elec_Pt", &Elec_Pt );
  inputTree->SetBranchAddress("Elec_HasSC", &Elec_HasSC );
  inputTree->SetBranchAddress("Elec_PFMvaOutput", &Elec_PFMvaOutput );
  inputTree->SetBranchAddress("Elec_Ee", &Elec_Ee );
  inputTree->SetBranchAddress("Elec_Egamma", &Elec_Egamma );
  inputTree->SetBranchAddress("Elec_Pin", &Elec_Pin );
  inputTree->SetBranchAddress("Elec_Pout", &Elec_Pout );
  inputTree->SetBranchAddress("Elec_EtotOverPin", &Elec_EtotOverPin );
  inputTree->SetBranchAddress("Elec_EeOverPout", &Elec_EeOverPout );
  inputTree->SetBranchAddress("Elec_EgammaOverPdif", &Elec_EgammaOverPdif );
  inputTree->SetBranchAddress("Elec_EarlyBrem", &Elec_EarlyBrem );
  inputTree->SetBranchAddress("Elec_LateBrem", &Elec_LateBrem );
  inputTree->SetBranchAddress("Elec_Logsihih", &Elec_Logsihih );
  inputTree->SetBranchAddress("Elec_DeltaEta", &Elec_DeltaEta );
  inputTree->SetBranchAddress("Elec_HoHplusE", &Elec_HoHplusE );
  inputTree->SetBranchAddress("Elec_Fbrem", &Elec_Fbrem );
  inputTree->SetBranchAddress("Elec_HasKF", &Elec_HasKF );
  inputTree->SetBranchAddress("Elec_Chi2KF", &Elec_Chi2KF );
  inputTree->SetBranchAddress("Elec_KFNumHits", &Elec_KFNumHits );
  inputTree->SetBranchAddress("Elec_KFNumPixelHits", &Elec_KFNumPixelHits );
  inputTree->SetBranchAddress("Elec_KFNumStripHits", &Elec_KFNumStripHits );
  inputTree->SetBranchAddress("Elec_KFTrackResol", &Elec_KFTrackResol );
  inputTree->SetBranchAddress("Elec_KFTracklnPt", &Elec_KFTracklnPt );
  inputTree->SetBranchAddress("Elec_KFTrackEta", &Elec_KFTrackEta );
  inputTree->SetBranchAddress("Elec_HasGSF", &Elec_HasGSF );
  inputTree->SetBranchAddress("Elec_Chi2GSF", &Elec_Chi2GSF );
  inputTree->SetBranchAddress("Elec_GSFNumHits", &Elec_GSFNumHits );
  inputTree->SetBranchAddress("Elec_GSFNumPixelHits", &Elec_GSFNumPixelHits );
  inputTree->SetBranchAddress("Elec_GSFNumStripHits", &Elec_GSFNumStripHits );
  inputTree->SetBranchAddress("Elec_GSFTrackResol", &Elec_GSFTrackResol );
  inputTree->SetBranchAddress("Elec_GSFTracklnPt", &Elec_GSFTracklnPt );
  inputTree->SetBranchAddress("Elec_GSFTrackEta", &Elec_GSFTrackEta );

  //PFTaus variables
  inputTree->SetBranchAddress("Tau_GsfEleMatch", &Tau_GsfEleMatch );
  inputTree->SetBranchAddress("Tau_GenEleMatch", &Tau_GenEleMatch );
  inputTree->SetBranchAddress("Tau_GenEleFromZMatch", &Tau_GenEleFromZMatch );
  inputTree->SetBranchAddress("Tau_GenEleFromZTauTauMatch", &Tau_GenEleFromZTauTauMatch );
  inputTree->SetBranchAddress("Tau_GenHadMatch", &Tau_GenHadMatch );
  inputTree->SetBranchAddress("Tau_GenJetMatch", &Tau_GenJetMatch );
  inputTree->SetBranchAddress("Tau_Eta", &Tau_Eta );
  inputTree->SetBranchAddress("Tau_EtaAtEcalEntrance", &Tau_EtaAtEcalEntrance );
  inputTree->SetBranchAddress("Tau_PhiAtEcalEntrance", &Tau_PhiAtEcalEntrance );
  inputTree->SetBranchAddress("Tau_Phi", &Tau_Phi );
  inputTree->SetBranchAddress("Tau_Pt", &Tau_Pt );
  inputTree->SetBranchAddress("Tau_LeadHadronPt", &Tau_LeadHadronPt );
  inputTree->SetBranchAddress("Tau_HasGsf", &Tau_HasGsf ); 
  inputTree->SetBranchAddress("Tau_GSFChi2", &Tau_GSFChi2 );
  inputTree->SetBranchAddress("Tau_GSFNumHits", &Tau_GSFNumHits );
  inputTree->SetBranchAddress("Tau_GSFNumPixelHits", &Tau_GSFNumPixelHits );
  inputTree->SetBranchAddress("Tau_GSFNumStripHits", &Tau_GSFNumStripHits );
  inputTree->SetBranchAddress("Tau_GSFTrackResol", &Tau_GSFTrackResol );
  inputTree->SetBranchAddress("Tau_GSFTracklnPt", &Tau_GSFTracklnPt );
  inputTree->SetBranchAddress("Tau_GSFTrackEta", &Tau_GSFTrackEta );
  inputTree->SetBranchAddress("Tau_HasKF", &Tau_HasKF ); 
  inputTree->SetBranchAddress("Tau_KFChi2", &Tau_KFChi2 );
  inputTree->SetBranchAddress("Tau_KFNumHits", &Tau_KFNumHits );
  inputTree->SetBranchAddress("Tau_KFNumPixelHits", &Tau_KFNumPixelHits );
  inputTree->SetBranchAddress("Tau_KFNumStripHits", &Tau_KFNumStripHits );
  inputTree->SetBranchAddress("Tau_KFTrackResol", &Tau_KFTrackResol );
  inputTree->SetBranchAddress("Tau_KFTracklnPt", &Tau_KFTracklnPt );
  inputTree->SetBranchAddress("Tau_KFTrackEta", &Tau_KFTrackEta );
  inputTree->SetBranchAddress("Tau_EmFraction", &Tau_EmFraction ); 
  inputTree->SetBranchAddress("Tau_NumChargedCands", &Tau_NumChargedCands );
  inputTree->SetBranchAddress("Tau_NumGammaCands", &Tau_NumGammaCands ); 
  inputTree->SetBranchAddress("Tau_HadrHoP", &Tau_HadrHoP ); 
  inputTree->SetBranchAddress("Tau_HadrEoP", &Tau_HadrEoP ); 
  inputTree->SetBranchAddress("Tau_VisMass", &Tau_VisMass ); 
  inputTree->SetBranchAddress("Tau_GammaEtaMom", &Tau_GammaEtaMom );
  inputTree->SetBranchAddress("Tau_GammaPhiMom", &Tau_GammaPhiMom );
  inputTree->SetBranchAddress("Tau_GammaEnFrac", &Tau_GammaEnFrac );
  inputTree->SetBranchAddress("Tau_HadrMva", &Tau_HadrMva ); 
  inputTree->SetBranchAddress("Tau_LooseComb3HitsIso", &Tau_LooseComb3HitsIso ); 
  inputTree->SetBranchAddress("Tau_AntiELoose", &Tau_AntiELoose ); 
  inputTree->SetBranchAddress("Tau_AntiEMedium", &Tau_AntiEMedium ); 
  inputTree->SetBranchAddress("Tau_AntiETight", &Tau_AntiETight ); 
  inputTree->SetBranchAddress("Tau_AntiELooseMVA3", &Tau_AntiELooseMVA3 ); 
  inputTree->SetBranchAddress("Tau_AntiEMediumMVA3", &Tau_AntiEMediumMVA3 ); 
  inputTree->SetBranchAddress("Tau_AntiETightMVA3", &Tau_AntiETightMVA3 ); 
  inputTree->SetBranchAddress("Tau_AntiEVTightMVA3", &Tau_AntiEVTightMVA3 ); 
  inputTree->SetBranchAddress("Tau_DecayMode", &Tau_DecayMode ); 
  inputTree->SetBranchAddress("Tau_MatchElePassVeto", &Tau_MatchElePassVeto ); 

  inputTree->SetBranchAddress("ElecVeto_N",&ElecVeto_N);
  inputTree->SetBranchAddress("ElecVeto_Pt",&ElecVeto_Pt);
  inputTree->SetBranchAddress("ElecVeto_Eta",&ElecVeto_Eta);
  inputTree->SetBranchAddress("ElecVeto_Phi",&ElecVeto_Phi);

  inputTree->SetBranchStatus("run", 1);
  inputTree->SetBranchStatus("event", 1);
  inputTree->SetBranchStatus("lumi", 1);
  inputTree->SetBranchStatus("NumPV", 1);
  inputTree->SetBranchStatus("NumGsfEle", 1);
  inputTree->SetBranchStatus("NumPFTaus", 1);
  inputTree->SetBranchStatus("NumGenEle", 1);
  inputTree->SetBranchStatus("NumGenHad", 1);
  inputTree->SetBranchStatus("NumGenJet", 1);

  //GsfElectron variables
  inputTree->SetBranchStatus("Elec_GenEleMatch", 1);
  inputTree->SetBranchStatus("Elec_GenEleFromZMatch", 1);
  inputTree->SetBranchStatus("Elec_GenEleFromZTauTauMatch", 1);
  inputTree->SetBranchStatus("Elec_GenHadMatch", 1);
  inputTree->SetBranchStatus("Elec_GenJetMatch", 1);
  inputTree->SetBranchStatus("Elec_AbsEta", 1);
  inputTree->SetBranchStatus("Elec_Pt", 1);
  inputTree->SetBranchStatus("Elec_HasSC",1);
  inputTree->SetBranchStatus("Elec_PFMvaOutput", 1);
  inputTree->SetBranchStatus("Elec_Ee", 1);
  inputTree->SetBranchStatus("Elec_Egamma", 1);
  inputTree->SetBranchStatus("Elec_Pin", 1);
  inputTree->SetBranchStatus("Elec_Pout", 1);
  inputTree->SetBranchStatus("Elec_EtotOverPin", 1);
  inputTree->SetBranchStatus("Elec_EeOverPout", 1);
  inputTree->SetBranchStatus("Elec_EgammaOverPdif", 1);
  inputTree->SetBranchStatus("Elec_EarlyBrem", 1);
  inputTree->SetBranchStatus("Elec_LateBrem", 1);
  inputTree->SetBranchStatus("Elec_Logsihih", 1);
  inputTree->SetBranchStatus("Elec_DeltaEta", 1);
  inputTree->SetBranchStatus("Elec_HoHplusE", 1);
  inputTree->SetBranchStatus("Elec_Fbrem", 1);
  inputTree->SetBranchStatus("Elec_HasKF", 1);
  inputTree->SetBranchStatus("Elec_Chi2KF",1);
  inputTree->SetBranchStatus("Elec_KFNumHits",1);
  inputTree->SetBranchStatus("Elec_KFNumPixelHits",1);
  inputTree->SetBranchStatus("Elec_KFNumStripHits",1);
  inputTree->SetBranchStatus("Elec_KFTrackResol", 1);
  inputTree->SetBranchStatus("Elec_KFTracklnPt", 1);
  inputTree->SetBranchStatus("Elec_KFTrackEta", 1);
  inputTree->SetBranchStatus("Elec_HasGSF", 1);
  inputTree->SetBranchStatus("Elec_Chi2GSF",1);
  inputTree->SetBranchStatus("Elec_GSFNumHits",1);
  inputTree->SetBranchStatus("Elec_GSFNumPixelHits",1);
  inputTree->SetBranchStatus("Elec_GSFNumStripHits",1);
  inputTree->SetBranchStatus("Elec_GSFTrackResol", 1);
  inputTree->SetBranchStatus("Elec_GSFTracklnPt", 1);
  inputTree->SetBranchStatus("Elec_GSFTrackEta", 1);


  //PFTaus variables
  inputTree->SetBranchStatus("Tau_GsfEleMatch", 1);
  inputTree->SetBranchStatus("Tau_GenEleMatch", 1);
  inputTree->SetBranchStatus("Tau_GenEleFromZMatch", 1);
  inputTree->SetBranchStatus("Tau_GenEleFromZTauTauMatch", 1);
  inputTree->SetBranchStatus("Tau_GenHadMatch", 1);
  inputTree->SetBranchStatus("Tau_GenJetMatch", 1);
  inputTree->SetBranchStatus("Tau_Eta", 1);
  inputTree->SetBranchStatus("Tau_EtaAtEcalEntrance", 1);
  inputTree->SetBranchStatus("Tau_PhiAtEcalEntrance", 1);
  inputTree->SetBranchStatus("Tau_Phi", 1);
  inputTree->SetBranchStatus("Tau_Pt", 1);
  inputTree->SetBranchStatus("Tau_LeadHadronPt", 1);
  inputTree->SetBranchStatus("Tau_HasGsf", 1); 
  inputTree->SetBranchStatus("Tau_GSFChi2",1);
  inputTree->SetBranchStatus("Tau_GSFNumHits",1);
  inputTree->SetBranchStatus("Tau_GSFNumPixelHits",1);
  inputTree->SetBranchStatus("Tau_GSFNumStripHits",1);
  inputTree->SetBranchStatus("Tau_GSFTrackResol", 1);
  inputTree->SetBranchStatus("Tau_GSFTracklnPt", 1);
  inputTree->SetBranchStatus("Tau_GSFTrackEta", 1);
  inputTree->SetBranchStatus("Tau_HasKF", 1); 
  inputTree->SetBranchStatus("Tau_KFChi2",1);
  inputTree->SetBranchStatus("Tau_KFNumHits",1);
  inputTree->SetBranchStatus("Tau_KFNumPixelHits",1);
  inputTree->SetBranchStatus("Tau_KFNumStripHits",1);
  inputTree->SetBranchStatus("Tau_KFTrackResol", 1);
  inputTree->SetBranchStatus("Tau_KFTracklnPt", 1);
  inputTree->SetBranchStatus("Tau_KFTrackEta", 1);
  inputTree->SetBranchStatus("Tau_EmFraction", 1); 
  inputTree->SetBranchStatus("Tau_NumChargedCands", 1);
  inputTree->SetBranchStatus("Tau_NumGammaCands", 1); 
  inputTree->SetBranchStatus("Tau_HadrHoP", 1); 
  inputTree->SetBranchStatus("Tau_HadrEoP", 1); 
  inputTree->SetBranchStatus("Tau_VisMass", 1); 
  inputTree->SetBranchStatus("Tau_GammaEtaMom", 1);
  inputTree->SetBranchStatus("Tau_GammaPhiMom", 1);
  inputTree->SetBranchStatus("Tau_GammaEnFrac", 1);
  inputTree->SetBranchStatus("Tau_HadrMva", 1); 
  inputTree->SetBranchStatus("Tau_LooseComb3HitsIso", 1); 
  inputTree->SetBranchStatus("Tau_AntiELoose", 1); 
  inputTree->SetBranchStatus("Tau_AntiEMedium", 1); 
  inputTree->SetBranchStatus("Tau_AntiETight", 1); 
  inputTree->SetBranchStatus("Tau_AntiELooseMVA3", 1); 
  inputTree->SetBranchStatus("Tau_AntiEMediumMVA3", 1); 
  inputTree->SetBranchStatus("Tau_AntiETightMVA3", 1); 
  inputTree->SetBranchStatus("Tau_AntiEVTightMVA3", 1); 
  inputTree->SetBranchStatus("Tau_DecayMode", 1); 
  inputTree->SetBranchStatus("Tau_MatchElePassVeto", 1); 

  inputTree->SetBranchStatus("ElecVeto_N",1);
  inputTree->SetBranchStatus("ElecVeto_Pt",1);
  inputTree->SetBranchStatus("ElecVeto_Eta",1);
  inputTree->SetBranchStatus("ElecVeto_Phi",1);

  cout<< "Number of entries : "<<nEntries<<endl;

  for (int iEntry = 0; iEntry<nEntries ; iEntry++){
//   for (int iEntry = 0; iEntry<1000 ; iEntry++){
    if(iEntry%100000==0) cout << iEntry <<"/"<<nEntries << endl;

    inputTree->GetEntry(iEntry);



    //////    SecondEleVeto
//     bool matchElectronCutsVeto = false;
//     for (int i =0 ; i<ElecVeto_N ; i++){
//       if (deltaR(Tau_EtaAtEcalEntrance,Tau_EtaAtEcalEntrance,ElecVeto_Eta,ElecVeto_Phi)<0.3) ){
// 	matchElectronCutsVeto = true;
//       }//Loop on GsfElectrons
//     if(matchElectronCutsVeto)continue;
// //     if(Tau_MatchElePassVeto!=0) continue;

//     if(ElecVeto_Pt > -99)continue;
    if(Tau_MatchElePassVeto==1) continue;

    //////    Ecal crack veto
    if(isInEcalCrack(Tau_EtaAtEcalEntrance)) continue;

    if (Elec_EgammaOverPdif>1e3 || TMath::IsNaN(Elec_EgammaOverPdif)>0.5 ) continue;


//     if(discriminator == "" && Tau_CombIsoDBLoose!=1) continue;
//     if(discriminator == "MVAIso" && Tau_IsoMVALoose!=1) continue;
    //LooseComb3HitsIsolation
    if(Tau_LooseComb3HitsIso!=1) continue;

    if(matching == "Elec" && Tau_GenEleMatch!=1) continue;
    if(matching == "Tau" && Tau_GenHadMatch!=1) continue;

    if(Region == "Barrel"){
      if(TMath::Abs(Tau_EtaAtEcalEntrance)>1.479 && TMath::Abs(Tau_EtaAtEcalEntrance)<2.3 )continue;
    }
    if(Region == "Endcap"){
      if(TMath::Abs(Tau_EtaAtEcalEntrance)<1.479 )continue;
    }

    //No discriminator applied
    if(discriminator == "" && category == "NoEleMatch_woGwoGSF"){
      if(Tau_GsfEleMatch>0.5) continue;
      if(Tau_NumGammaCands>0) continue;
      if (Tau_HasGsf>0.5) continue;
    }
    if(discriminator == "" && category == "NoEleMatch_woGwGSF"){
      if(Tau_GsfEleMatch>0.5) continue;
      if(Tau_NumGammaCands>0) continue;
      if (Tau_HasGsf<0.5) continue;
    }
    if(discriminator == "" && category == "NoEleMatch_wGwoGSF"){
      if(Tau_GsfEleMatch>0.5) continue;
      if(Tau_NumGammaCands<1) continue;
      if (Tau_HasGsf>0.5) continue;
    }
    if(discriminator == "" && category == "NoEleMatch_wGwGSF"){
      if(Tau_GsfEleMatch>0.5) continue;
      if(Tau_NumGammaCands<1) continue;
      if (Tau_HasGsf<0.5) continue;
    }
    if(discriminator == "" && category == "woGwoGSF"){
      if(Tau_GsfEleMatch<0.5) continue;
      if(Tau_NumGammaCands>0) continue;
      if (Tau_HasGsf>0.5) continue;
    }
    if(discriminator == "" && category == "woGwGSF"){
      if(Tau_GsfEleMatch<0.5) continue;
      if(Tau_NumGammaCands>0) continue;
      if( Tau_HasGsf<0.5)continue;
    }
    if(discriminator == "" && category == "wGwoGSF"){
      if(Tau_GsfEleMatch<0.5) continue;
      if (Tau_NumGammaCands<1)continue;
      if (Tau_HasGsf>0.5) continue;
    }
    if(discriminator == "" && category == "wGwGSF"){
      if(Tau_GsfEleMatch<0.5) continue;
      if(Tau_NumGammaCands<1)continue;
      if( Tau_HasGsf<0.5)continue;
    }


    

    t_run_ = run;
    t_event_ = event;
    t_lumi_ = lumi;
    t_NumPV_ = NumPV ;
    t_NumGsfEle_ = NumGsfEle ;
    t_NumPFTaus_ = NumPFTaus ;
    t_NumGenEle_ = NumGenEle ;
    t_NumGenHad_ = NumGenHad ;
    t_NumGenJet_ = NumGenJet ;

    t_Elec_GenEleMatch_ = Elec_GenEleMatch ;
    t_Elec_GenEleFromZMatch_ = Elec_GenEleFromZMatch;
    t_Elec_GenEleFromZTauTauMatch_ = Elec_GenEleFromZTauTauMatch ;
    t_Elec_GenHadMatch_ = Elec_GenHadMatch ;
    t_Elec_GenJetMatch_ = Elec_GenJetMatch ;
    t_Elec_AbsEta_ = Elec_AbsEta ;
    t_Elec_Pt_ = Elec_Pt ;
    t_Elec_HasSC_ = Elec_HasSC ;
    t_Elec_PFMvaOutput_ = Elec_PFMvaOutput ;
    t_Elec_Ee_ = Elec_Ee ;
    t_Elec_Egamma_ = Elec_Egamma ;
    t_Elec_Pin_ = Elec_Pin ;
    t_Elec_Pout_ = Elec_Pout ;
    t_Elec_EtotOverPin_ = Elec_EtotOverPin ;
    t_Elec_EeOverPout_ = Elec_EeOverPout ;
    t_Elec_EgammaOverPdif_ = Elec_EgammaOverPdif ;
    t_Elec_EarlyBrem_ = Elec_EarlyBrem ;
    t_Elec_LateBrem_ = Elec_LateBrem ;
    t_Elec_Logsihih_ = Elec_Logsihih ;
    t_Elec_DeltaEta_ = Elec_DeltaEta ;
    t_Elec_HoHplusE_ = Elec_HoHplusE ;
    t_Elec_Fbrem_ = Elec_Fbrem; 
    t_Elec_HasKF_ = Elec_HasKF; 
    t_Elec_Chi2KF_ = Elec_Chi2KF; 
    t_Elec_KFNumHits_ = Elec_KFNumHits; 
    t_Elec_KFNumPixelHits_ = Elec_KFNumPixelHits; 
    t_Elec_KFNumStripHits_ = Elec_KFNumStripHits; 
    t_Elec_KFTrackResol_ = Elec_KFTrackResol; 
    t_Elec_KFTracklnPt_ = Elec_KFTracklnPt; 
    t_Elec_KFTrackEta_ = Elec_KFTrackEta; 
    t_Elec_HasGSF_ = Elec_HasGSF; 
    t_Elec_Chi2GSF_ = Elec_Chi2GSF; 
    t_Elec_GSFNumHits_ = Elec_GSFNumHits; 
    t_Elec_GSFNumPixelHits_ = Elec_GSFNumPixelHits; 
    t_Elec_GSFNumStripHits_ = Elec_GSFNumStripHits; 
    t_Elec_GSFTrackResol_ = Elec_GSFTrackResol; 
    t_Elec_GSFTracklnPt_ = Elec_GSFTracklnPt; 
    t_Elec_GSFTrackEta_ = Elec_GSFTrackEta; 

    t_Tau_GsfEleMatch_ = Tau_GsfEleMatch ;
    t_Tau_GenEleMatch_ = Tau_GenEleMatch ;
    t_Tau_GenEleFromZMatch_ = Tau_GenEleFromZMatch ;
    t_Tau_GenEleFromZTauTauMatch_ = Tau_GenEleFromZTauTauMatch ;
    t_Tau_GenHadMatch_ = Tau_GenHadMatch ;
    t_Tau_GenJetMatch_ = Tau_GenJetMatch ;
    t_Tau_Eta_ = Tau_Eta ;
    t_Tau_EtaAtEcalEntrance_ = Tau_EtaAtEcalEntrance ;
    t_Tau_PhiAtEcalEntrance_ = Tau_PhiAtEcalEntrance ;
    t_Tau_Pt_ = Tau_Pt ;
    t_Tau_Phi_ = Tau_Phi ;
    t_Tau_dCrackPhi_ = dCrackPhi(Tau_PhiAtEcalEntrance,Tau_EtaAtEcalEntrance) ;
    t_Tau_dCrackEta_ = dCrackEta(Tau_EtaAtEcalEntrance) ;
    t_Tau_LeadHadronPt_ = Tau_LeadHadronPt ;
    t_Tau_HasGsf_ = Tau_HasGsf ; 
    t_Tau_GSFChi2_ = Tau_GSFChi2; 
    t_Tau_GSFNumHits_ = Tau_GSFNumHits; 
    t_Tau_GSFNumPixelHits_ = Tau_GSFNumPixelHits; 
    t_Tau_GSFNumStripHits_ = Tau_GSFNumStripHits; 
    t_Tau_GSFTrackResol_ = Tau_GSFTrackResol; 
    t_Tau_GSFTracklnPt_ = Tau_GSFTracklnPt; 
    t_Tau_GSFTrackEta_ = Tau_GSFTrackEta; 
    t_Tau_HasKF_ = Tau_HasKF ; 
    t_Tau_KFChi2_ = Tau_KFChi2; 
    t_Tau_KFNumHits_ = Tau_KFNumHits; 
    t_Tau_KFNumPixelHits_ = Tau_KFNumPixelHits; 
    t_Tau_KFNumStripHits_ = Tau_KFNumStripHits; 
    t_Tau_KFTrackResol_ = Tau_KFTrackResol; 
    t_Tau_KFTracklnPt_ = Tau_KFTracklnPt; 
    t_Tau_KFTrackEta_ = Tau_KFTrackEta; 

    t_Tau_EmFraction_ = Tau_EmFraction ; 
    t_Tau_NumChargedCands_ = Tau_NumChargedCands ;
    t_Tau_NumGammaCands_ = Tau_NumGammaCands ; 
    t_Tau_HadrHoP_ = Tau_HadrHoP ; 
    t_Tau_HadrEoP_ = Tau_HadrEoP ; 
    t_Tau_VisMass_ = Tau_VisMass ; 
    t_Tau_GammaEtaMom_ = Tau_GammaEtaMom ;
    t_Tau_GammaPhiMom_ = Tau_GammaPhiMom ;
    t_Tau_GammaEnFrac_ = Tau_GammaEnFrac ;
    t_Tau_HadrMva_ = Tau_HadrMva ; 
    t_Tau_AntiELoose_ = Tau_AntiELoose ; 
    t_Tau_AntiEMedium_ = Tau_AntiEMedium ; 
    t_Tau_AntiETight_ = Tau_AntiETight ; 
    t_Tau_AntiELooseMVA3_ = Tau_AntiELooseMVA3 ; 
    t_Tau_AntiEMediumMVA3_ = Tau_AntiEMediumMVA3 ; 
    t_Tau_AntiETightMVA3_ = Tau_AntiETightMVA3 ; 
    t_Tau_AntiEVTightMVA3_ = Tau_AntiEVTightMVA3 ; 
    t_Tau_DecayMode_ = Tau_DecayMode ; 
    t_Tau_MatchElePassVeto_ = Tau_MatchElePassVeto ; 
    

    if(DEBUG){
      cout<<endl;
      cout<<" run : "<<t_run_<<endl;
      cout<<" event : "<<t_event_<<endl;
      cout<<" lumi : "<<t_lumi_<<endl;
      cout<<" NumPV : "<<t_NumPV_<<endl;
      cout<<" NumGsfEle : "<<t_NumGsfEle_<<endl;
      cout<<" NumPFTaus : "<<t_NumPFTaus_<<endl;
      cout<<" NumGenEle : "<<t_NumGenEle_<<endl;
      cout<<" NumGenHad : "<<t_NumGenHad_<<endl;
      cout<<" NumGenJet : "<<t_NumGenJet_<<endl;
      
      cout<<" Elec_GenEleMatch :"<<t_Elec_GenEleMatch_<<endl;
      cout<<" Elec_GenEleFromZMatch :"<<t_Elec_GenEleFromZMatch_<<endl;
      cout<<" Elec_GenEleFromZTauTauMatch :"<<t_Elec_GenEleFromZTauTauMatch_<<endl;
      cout<<" Elec_GenHadMatch :"<<t_Elec_GenHadMatch_<<endl;
      cout<<" Elec_GenJetMatch :"<<t_Elec_GenJetMatch_<<endl;
      cout<<" Elec_AbsEta :"<<t_Elec_AbsEta_<<endl;
      cout<<" Elec_Pt :"<<t_Elec_Pt_<<endl;
      cout<<" Elec_PFMvaOutput : "<<t_Elec_PFMvaOutput_<<endl;
      cout<<" Elec_Ee :"<<t_Elec_Ee_<<endl;
      cout<<" Elec_Egamma :"<<t_Elec_Egamma_<<endl;
      cout<<" Elec_Pin :"<<t_Elec_Pin_<<endl;
      cout<<" Elec_Pout : "<<t_Elec_Pout_<<endl;
      cout<<" Elec_EtotOverPin :"<<t_Elec_EtotOverPin_<<endl;
      cout<<" Elec_EeOverPout : "<<t_Elec_EeOverPout_<<endl;
      cout<<" Elec_EgammaOverPdif :"<<t_Elec_EgammaOverPdif_<<endl;
      cout<<" Elec_EarlyBrem :"<<t_Elec_EarlyBrem_ <<endl;
      cout<<" Elec_LateBrem :"<<t_Elec_LateBrem_<<endl;
      cout<<" Elec_Logsihih :"<<t_Elec_Logsihih_<<endl;
      cout<<" Elec_DeltaEta :"<<t_Elec_DeltaEta_<<endl;
      cout<<" Elec_HoHplusE :"<<t_Elec_HoHplusE_<<endl;
      cout<<" Elec_Fbrem :"<<t_Elec_Fbrem_<<endl;

      cout<<" Tau_GsfEleMatch :"<<t_Tau_GsfEleMatch_<<endl;
      cout<<" Tau_GenEleMatch :"<<t_Tau_GenEleMatch_<<endl;
      cout<<" Tau_GenEleFromZMatch :"<<t_Tau_GenEleFromZMatch_<<endl;
      cout<<" Tau_GenEleFromZTauTauMatch :"<<t_Tau_GenEleFromZTauTauMatch_<<endl;
      cout<<" Tau_GenHadMatch :"<<t_Tau_GenHadMatch_<<endl;
      cout<<" Tau_GenJetMatch :"<<t_Tau_GenJetMatch_<<endl;
      cout<<" Tau_Eta :"<<t_Tau_Eta_<<endl;
      cout<<" Tau_EtaAtEcalEntrance :"<<t_Tau_EtaAtEcalEntrance_<<endl;
      cout<<" Tau_Pt : "<<t_Tau_Pt_<<endl;
      cout<<" Tau_LeadHadronPt : "<<t_Tau_LeadHadronPt_<<endl;
      cout<<" Tau_HasGsf :"<<t_Tau_HasGsf_<<endl; 
      cout<<" Tau_EmFraction :"<<t_Tau_EmFraction_<<endl; 
      cout<<" Tau_NumChargedCands :"<<t_Tau_NumChargedCands_<<endl;
      cout<<" Tau_NumGammaCands :"<<t_Tau_NumGammaCands_<<endl; 
      cout<<" Tau_HadrHoP :"<<t_Tau_HadrHoP_<<endl; 
      cout<<" Tau_HadrEoP :"<<t_Tau_HadrEoP_<<endl; 
      cout<<" Tau_VisMass :"<<t_Tau_VisMass_<<endl; 
      cout<<" Tau_GammaEtaMom :"<<t_Tau_GammaEtaMom_<<endl;
      cout<<" Tau_GammaPhiMom :"<<t_Tau_GammaPhiMom_<<endl;
      cout<<" Tau_GammaEnFrac :"<<t_Tau_GammaEnFrac_<<endl;
      cout<<" Tau_HadrMva :"<<t_Tau_HadrMva_<<endl;
      cout<<" Tau_AntiELoose :"<<t_Tau_AntiELoose_<<endl; 
      cout<<" Tau_AntiEMedium :"<<t_Tau_AntiEMedium_<<endl; 
      cout<<" Tau_AntiETight :"<<t_Tau_AntiETight_<<endl; 
      cout<<" Tau_MatchElePassVeto :"<<t_Tau_MatchElePassVeto_<<endl; 
    
    }

    mytree->Fill();
  }
  mytree->Write();

  cout<<"Creating file : "<<outputFileName.data()<<endl;
//   inputFile->Close();
  outputFile->Close();
  return;
}



void makeAll(){

//   makeRoot("Elec","All","","Barrel");
//   makeRoot("Tau","All","","Barrel");
//   makeRoot("Elec","All","","Endcap");
//   makeRoot("Tau","All","","Endcap");

//   makeRoot("Elec","NoEleMatch_woGwoGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","","Barrel");
//   makeRoot("Elec","NoEleMatch_woGwGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwGSF","","Barrel");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","","Barrel");
  makeRoot("Tau","NoEleMatch_wGwoGSF","","Barrel");
  makeRoot("Elec","NoEleMatch_wGwGSF","","Barrel");
  makeRoot("Tau","NoEleMatch_wGwGSF","","Barrel");
  makeRoot("Elec","woGwoGSF","","Barrel");
  makeRoot("Tau","woGwoGSF","","Barrel");
  makeRoot("Elec","woGwGSF","","Barrel");
  makeRoot("Tau","woGwGSF","","Barrel");
  makeRoot("Elec","wGwoGSF","","Barrel");
  makeRoot("Tau","wGwoGSF","","Barrel");
//   makeRoot("Elec","wGwGSF","","Barrel");
//   makeRoot("Tau","wGwGSF","","Barrel");

//   makeRoot("Elec","NoEleMatch_woGwoGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_woGwGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwoGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwGSF","","Endcap");
//   makeRoot("Elec","woGwoGSF","","Endcap");
//   makeRoot("Tau","woGwoGSF","","Endcap");
//   makeRoot("Elec","woGwGSF","","Endcap");
//   makeRoot("Tau","woGwGSF","","Endcap");
//   makeRoot("Elec","wGwoGSF","","Endcap");
//   makeRoot("Tau","wGwoGSF","","Endcap");
//   makeRoot("Elec","wGwGSF","","Endcap");
//   makeRoot("Tau","wGwGSF","","Endcap");


//   //MVAIso
//   makeRoot("Elec","All","MVAIso","Barrel");
//   makeRoot("Tau","All","MVAIso","Barrel");
//   makeRoot("Elec","NoEleMatch","MVAIso","Barrel");
//   makeRoot("Tau","NoEleMatch","MVAIso","Barrel");
//   makeRoot("Elec","woG","MVAIso","Barrel");
//   makeRoot("Tau","woG","MVAIso","Barrel");
//   makeRoot("Elec","wGwoGSF","MVAIso","Barrel");
//   makeRoot("Tau","wGwoGSF","MVAIso","Barrel");
//   makeRoot("Elec","wGwGSFwoPFMVA","MVAIso","Barrel");
//   makeRoot("Tau","wGwGSFwoPFMVA","MVAIso","Barrel");
//   makeRoot("Elec","wGwGSFwPFMVA","MVAIso","Barrel");
//   makeRoot("Tau","wGwGSFwPFMVA","MVAIso","Barrel");
//v9
//   makeRoot("Elec","NoEleMatch_woGwoGSF","MVAIso","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","MVAIso","Barrel");
//   makeRoot("Elec","NoEleMatch_woGwGSF","MVAIso","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwGSF","MVAIso","Barrel");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","MVAIso","Barrel");
//   makeRoot("Tau","NoEleMatch_wGwoGSF","MVAIso","Barrel");
//   makeRoot("Elec","NoEleMatch_wGwGSF","MVAIso","Barrel");
//   makeRoot("Tau","NoEleMatch_wGwGSF","MVAIso","Barrel");
//   makeRoot("Elec","woGwoGSF","MVAIso","Barrel");
//   makeRoot("Tau","woGwoGSF","MVAIso","Barrel");
//   makeRoot("Elec","woGwGSF","MVAIso","Barrel");
//   makeRoot("Tau","woGwGSF","MVAIso","Barrel");
//   makeRoot("Elec","wGwoGSF","MVAIso","Barrel");
//   makeRoot("Tau","wGwoGSF","MVAIso","Barrel");
//   makeRoot("Elec","wGwGSF","MVAIso","Barrel");
//   makeRoot("Tau","wGwGSF","MVAIso","Barrel");

//   makeRoot("Elec","All","MVAIso","Endcap");
//   makeRoot("Tau","All","MVAIso","Endcap");
//   makeRoot("Elec","NoEleMatch","MVAIso","Endcap");
//   makeRoot("Tau","NoEleMatch","MVAIso","Endcap");
//   makeRoot("Elec","woG","MVAIso","Endcap");
//   makeRoot("Tau","woG","MVAIso","Endcap");
//   makeRoot("Elec","wGwoGSF","MVAIso","Endcap");
//   makeRoot("Tau","wGwoGSF","MVAIso","Endcap");
//   makeRoot("Elec","wGwGSFwoPFMVA","MVAIso","Endcap");
//   makeRoot("Tau","wGwGSFwoPFMVA","MVAIso","Endcap");
//   makeRoot("Elec","wGwGSFwPFMVA","MVAIso","Endcap");
//   makeRoot("Tau","wGwGSFwPFMVA","MVAIso","Endcap");
//v9
//   makeRoot("Elec","NoEleMatch_woGwoGSF","MVAIso","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","MVAIso","Endcap");
//   makeRoot("Elec","NoEleMatch_woGwGSF","MVAIso","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwGSF","MVAIso","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","MVAIso","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwoGSF","MVAIso","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwGSF","MVAIso","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwGSF","MVAIso","Endcap");
//   makeRoot("Elec","woGwoGSF","MVAIso","Endcap");
//   makeRoot("Tau","woGwoGSF","MVAIso","Endcap");
//   makeRoot("Elec","woGwGSF","MVAIso","Endcap");
//   makeRoot("Tau","woGwGSF","MVAIso","Endcap");
//   makeRoot("Elec","wGwoGSF","MVAIso","Endcap");
//   makeRoot("Tau","wGwoGSF","MVAIso","Endcap");
//   makeRoot("Elec","wGwGSF","MVAIso","Endcap");
//   makeRoot("Tau","wGwGSF","MVAIso","Endcap");

//   makeRoot("Elec","All","","Barrel");
//   makeRoot("Tau","All","","Barrel");
//   makeRoot("Elec","NoEleMatch","","Barrel");
//   makeRoot("Tau","NoEleMatch","","Barrel");
//   makeRoot("Elec","woG","","Barrel");
//   makeRoot("Tau","woG","","Barrel");
//   makeRoot("Elec","wGwoGSF","","Barrel");
//   makeRoot("Tau","wGwoGSF","","Barrel");
//   makeRoot("Elec","wGwGSFwoPFMVA","","Barrel");
//   makeRoot("Tau","wGwGSFwoPFMVA","","Barrel");
//   makeRoot("Elec","wGwGSFwPFMVA","","Barrel");
//   makeRoot("Tau","wGwGSFwPFMVA","","Barrel");

//   makeRoot("Elec","NoEleMatch_woGwoGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","","Barrel");
//   makeRoot("Elec","NoEleMatch_woGwGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_woGwGSF","","Barrel");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_wGwoGSF","","Barrel");
//   makeRoot("Elec","NoEleMatch_wGwGSF","","Barrel");
//   makeRoot("Tau","NoEleMatch_wGwGSF","","Barrel");
//   makeRoot("Elec","woGwoGSF","","Barrel");
//   makeRoot("Tau","woGwoGSF","","Barrel");
//   makeRoot("Elec","woGwGSF","","Barrel");
//   makeRoot("Tau","woGwGSF","","Barrel");
//   makeRoot("Elec","wGwoGSF","","Barrel");
//   makeRoot("Tau","wGwoGSF","","Barrel");
//   makeRoot("Elec","wGwGSF","","Barrel");
//   makeRoot("Tau","wGwGSF","","Barrel");

//   makeRoot("Elec","All","","Endcap");
//   makeRoot("Tau","All","","Endcap");
//   makeRoot("Elec","NoEleMatch","","Endcap");
//   makeRoot("Tau","NoEleMatch","","Endcap");
//   makeRoot("Elec","woG","","Endcap");
//   makeRoot("Tau","woG","","Endcap");
//   makeRoot("Elec","wGwoGSF","","Endcap");
//   makeRoot("Tau","wGwoGSF","","Endcap");
//   makeRoot("Elec","wGwGSFwoPFMVA","","Endcap");
//   makeRoot("Tau","wGwGSFwoPFMVA","","Endcap");
//   makeRoot("Elec","wGwGSFwPFMVA","","Endcap");
//   makeRoot("Tau","wGwGSFwPFMVA","","Endcap");
//   makeRoot("Elec","NoEleMatch_woGwoGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwoGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_woGwGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_woGwGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwoGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwoGSF","","Endcap");
//   makeRoot("Elec","NoEleMatch_wGwGSF","","Endcap");
//   makeRoot("Tau","NoEleMatch_wGwGSF","","Endcap");
//   makeRoot("Elec","woGwoGSF","","Endcap");
//   makeRoot("Tau","woGwoGSF","","Endcap");
//   makeRoot("Elec","woGwGSF","","Endcap");
//   makeRoot("Tau","woGwGSF","","Endcap");
 
//   makeRoot("Elec","wGwoGSF","","Endcap");
//   makeRoot("Tau","wGwoGSF","","Endcap");
//   makeRoot("Elec","wGwGSF","","Endcap");
//   makeRoot("Tau","wGwGSF","","Endcap");

//   makeRoot("Elec","All","-AntiEMed");
//   makeRoot("Tau","All","-AntiEMed");
//   makeRoot("Elec","NoEleMatch","-AntiEMed");
//   makeRoot("Tau","NoEleMatch","-AntiEMed");
//   makeRoot("Elec","woG","-AntiEMed");
//   makeRoot("Tau","woG","-AntiEMed");
//   makeRoot("Elec","wGwoGSF","-AntiEMed");
//   makeRoot("Tau","wGwoGSF","-AntiEMed");
//   makeRoot("Elec","wGwGSFwoPFMVA","-AntiEMed");
//   makeRoot("Tau","wGwGSFwoPFMVA","-AntiEMed");


//   makeRoot("Elec","wGwGSFwPFMVA","-AntiEMed");
//   makeRoot("Tau","wGwGSFwPFMVA","-AntiEMed");

}
