#include "IvoNaranjo/ElectronsStudies/interface/AntiEMVAAnalyzer2.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
// #include "DataFormats/PatCandidates/interface/Electron.h"


AntiEMVAAnalyzer2::AntiEMVAAnalyzer2(const edm::ParameterSet& cfg)
{ 
  srcPrimaryVertex_  = cfg.getParameter<edm::InputTag>("srcPrimaryVertex");
  srcGsfElectrons_  = cfg.getParameter<edm::InputTag>("srcGsfElectrons");
  srcPFTaus_  = cfg.getParameter<edm::InputTag>("srcPFTaus");
  srcGenElectrons_  = cfg.getParameter<edm::InputTag>("srcGenElectrons");
  srcGenElectronsFromZ_  = cfg.getParameter<edm::InputTag>("srcGenElectronsFromZ");
  srcGenElectronsFromZTauTau_  = cfg.getParameter<edm::InputTag>("srcGenElectronsFromZTauTau");
  srcGenTaus_  = cfg.getParameter<edm::InputTag>("srcGenTaus");
  srcGenJets_  = cfg.getParameter<edm::InputTag>("srcGenJets");
  srcPatTaus_  = cfg.getParameter<edm::InputTag>("srcPatTaus");
  debug_  = cfg.getParameter<bool>("debug");

} 

void AntiEMVAAnalyzer2::beginJob()
{ 
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree","AntiEMVA tree");
  //counters
  tree_->Branch("run",&run_,"run/l");
  tree_->Branch("event",&event_,"event/l");
  tree_->Branch("lumi",&lumi_,"lumi/l");
  tree_->Branch("NumPV",&NumPV_,"NumPV/I");
  tree_->Branch("NumGsfEle",&NumGsfEle_,"NumGsfEle/I");
  tree_->Branch("NumGenEle",&NumGenEle_,"NumGenEle/I");
  tree_->Branch("NumPFTaus",&NumPFTaus_,"NumPFTaus/I");
  tree_->Branch("NumGenHad",&NumGenHad_,"NumGenHad/I");
  tree_->Branch("NumGenJet",&NumGenJet_,"NumGenEJet/I");

  //GsfElectron variables
  tree_->Branch("Elec_GenEleMatch",&Elec_GenEleMatch_,"Elec_GenEleMatch/I");
  tree_->Branch("Elec_GenEleFromZMatch",&Elec_GenEleFromZMatch_,"Elec_GenEleFromZMatch/I");
  tree_->Branch("Elec_GenEleFromZTauTauMatch",&Elec_GenEleFromZTauTauMatch_,"Elec_GenEleFromZTauTauMatch/I");
  tree_->Branch("Elec_GenHadMatch",&Elec_GenHadMatch_,"Elec_GenHadMatch/I");
  tree_->Branch("Elec_GenJetMatch",&Elec_GenJetMatch_,"Elec_GenJetMatch/I");
  tree_->Branch("Elec_AbsEta",&Elec_AbsEta_,"Elec_AbsEta/F");
  tree_->Branch("Elec_Pt",&Elec_Pt_,"Elec_Pt/F");
  tree_->Branch("Elec_HasSC",&Elec_HasSC_,"Elec_HasSC/F");
  tree_->Branch("Elec_PFMvaOutput",&Elec_PFMvaOutput_,"Elec_PFMvaOutput/F");
  tree_->Branch("Elec_Ee",&Elec_Ee_,"Elec_Ee/F");
  tree_->Branch("Elec_Egamma",&Elec_Egamma_,"Elec_Egamma/F");
  tree_->Branch("Elec_Pin",&Elec_Pin_,"Elec_Pin/F");
  tree_->Branch("Elec_Pout",&Elec_Pout_,"Elec_Pout/F");
  tree_->Branch("Elec_EtotOverPin",&Elec_EtotOverPin_,"Elec_EtotOverPin/F");
  tree_->Branch("Elec_EeOverPout",&Elec_EeOverPout_,"Elec_EeOverPout/F");
  tree_->Branch("Elec_EgammaOverPdif",&Elec_EgammaOverPdif_,"Elec_EgammaOverPdif/F");
  tree_->Branch("Elec_EarlyBrem",&Elec_EarlyBrem_,"Elec_EarlyBrem/I");
  tree_->Branch("Elec_LateBrem",&Elec_LateBrem_,"Elec_LateBrem/I");
  tree_->Branch("Elec_Logsihih",&Elec_Logsihih_,"Elec_Logsihih/F");
  tree_->Branch("Elec_DeltaEta",&Elec_DeltaEta_,"Elec_DeltaEta/F");
  tree_->Branch("Elec_HoHplusE",&Elec_HoHplusE_,"Elec_HoHplusE/F");
  tree_->Branch("Elec_Fbrem",&Elec_Fbrem_,"Elec_Fbrem/F");
  tree_->Branch("Elec_HasKF",&Elec_HasKF_,"Elec_HasKF/F");
  tree_->Branch("Elec_Chi2KF",&Elec_Chi2KF_,"Elec_Chi2KF/F");
  tree_->Branch("Elec_KFNumHits",&Elec_KFNumHits_,"Elec_KFNumHits/F");
  tree_->Branch("Elec_KFNumPixelHits",&Elec_KFNumPixelHits_,"Elec_KFNumPixelHits/F");
  tree_->Branch("Elec_KFNumStripHits",&Elec_KFNumStripHits_,"Elec_KFNumStripHits/F");
  tree_->Branch("Elec_KFTrackResol",&Elec_KFTrackResol_,"Elec_KFTrackResol/F");
  tree_->Branch("Elec_KFTracklnPt",&Elec_KFTracklnPt_,"Elec_KFTracklnPt/F");
  tree_->Branch("Elec_KFTrackEta",&Elec_KFTrackEta_,"Elec_KFTrackEta/F");
  tree_->Branch("Elec_HasGSF",&Elec_HasGSF_,"Elec_HasGSF/F");
  tree_->Branch("Elec_Chi2GSF",&Elec_Chi2GSF_,"Elec_Chi2GSF/F");
  tree_->Branch("Elec_GSFNumHits",&Elec_GSFNumHits_,"Elec_GSFNumHits/F");
  tree_->Branch("Elec_GSFNumPixelHits",&Elec_GSFNumPixelHits_,"Elec_GSFNumPixelHits/F");
  tree_->Branch("Elec_GSFNumStripHits",&Elec_GSFNumStripHits_,"Elec_GSFNumStripHits/F");
  tree_->Branch("Elec_GSFTrackResol",&Elec_GSFTrackResol_,"Elec_GSFTrackResol/F");
  tree_->Branch("Elec_GSFTracklnPt",&Elec_GSFTracklnPt_,"Elec_GSFTracklnPt/F");
  tree_->Branch("Elec_GSFTrackEta",&Elec_GSFTrackEta_,"Elec_GSFTrackEta/F");
 
  tree_->Branch("ElecVeto_N",&ElecVeto_N_,"ElecVeto_N/I");
  tree_->Branch("ElecVeto_Pt",&ElecVeto_Pt_,"ElecVeto_Pt/F");
  tree_->Branch("ElecVeto_Eta",&ElecVeto_Eta_,"ElecVeto_Eta/F");
  tree_->Branch("ElecVeto_Phi",&ElecVeto_Phi_,"ElecVeto_Phi/F");


  //PFTaus variables
  tree_->Branch("Tau_GsfEleMatch",&Tau_GsfEleMatch_,"Tau_GsfEleMatch/I");
  tree_->Branch("Tau_GenEleMatch",&Tau_GenEleMatch_,"Tau_GenEleMatch/I");
  tree_->Branch("Tau_GenEleFromZMatch",&Tau_GenEleFromZMatch_,"Tau_GenEleFromZMatch/I");
  tree_->Branch("Tau_GenEleFromZTauTauMatch",&Tau_GenEleFromZTauTauMatch_,"Tau_GenEleFromZTauTauMatch/I");
  tree_->Branch("Tau_GenHadMatch",&Tau_GenHadMatch_,"Tau_GenHadMatch/I");
  tree_->Branch("Tau_GenJetMatch",&Tau_GenJetMatch_,"Tau_GenJetMatch/I");
  tree_->Branch("Tau_Eta",&Tau_Eta_,"Tau_Eta/F");
  tree_->Branch("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance_,"Tau_EtaAtEcalEntrance/F");
  tree_->Branch("Tau_PhiAtEcalEntrance",&Tau_PhiAtEcalEntrance_,"Tau_PhiAtEcalEntrance/F");
  tree_->Branch("Tau_Phi",&Tau_Phi_,"Tau_Phi/F");
  tree_->Branch("Tau_Pt",&Tau_Pt_,"Tau_Pt/F");
  tree_->Branch("Tau_LeadHadronPt",&Tau_LeadHadronPt_,"Tau_LeadHadronPt/F");
  tree_->Branch("Tau_HasGsf",&Tau_HasGsf_,"Tau_HasGsf/F");
  tree_->Branch("Tau_GSFChi2",&Tau_GSFChi2_,"Tau_GSFChi2/F");
  tree_->Branch("Tau_GSFNumHits",&Tau_GSFNumHits_,"Tau_GSFNumHits/F");
  tree_->Branch("Tau_GSFNumPixelHits",&Tau_GSFNumPixelHits_,"Tau_GSFNumPixelHits/F");
  tree_->Branch("Tau_GSFNumStripHits",&Tau_GSFNumStripHits_,"Tau_GSFNumStripHits/F");
  tree_->Branch("Tau_GSFTrackResol",&Tau_GSFTrackResol_,"Tau_GSFTrackResol/F");
  tree_->Branch("Tau_GSFTracklnPt",&Tau_GSFTracklnPt_,"Tau_GSFTracklnPt/F");
  tree_->Branch("Tau_GSFTrackEta",&Tau_GSFTrackEta_,"Tau_GSFTrackEta/F");
  tree_->Branch("Tau_HasKF",&Tau_HasKF_,"Tau_HasKF/F");
  tree_->Branch("Tau_KFChi2",&Tau_KFChi2_,"Tau_KFChi2/F");
  tree_->Branch("Tau_KFNumHits",&Tau_KFNumHits_,"Tau_KFNumHits/F");
  tree_->Branch("Tau_KFNumPixelHits",&Tau_KFNumPixelHits_,"Tau_KFNumPixelHits/F");
  tree_->Branch("Tau_KFNumStripHits",&Tau_KFNumStripHits_,"Tau_KFNumStripHits/F");
  tree_->Branch("Tau_KFTrackResol",&Tau_KFTrackResol_,"Tau_KFTrackResol/F");
  tree_->Branch("Tau_KFTracklnPt",&Tau_KFTracklnPt_,"Tau_KFTracklnPt/F");
  tree_->Branch("Tau_KFTrackEta",&Tau_KFTrackEta_,"Tau_KFTrackEta/F");

  tree_->Branch("Tau_EmFraction",&Tau_EmFraction_,"Tau_EmFraction/F");
  tree_->Branch("Tau_NumChargedCands",&Tau_NumChargedCands_,"Tau_NumChargedCands/F");
  tree_->Branch("Tau_NumGammaCands",&Tau_NumGammaCands_,"Tau_NumGammaCands/F");
  tree_->Branch("Tau_HadrHoP",&Tau_HadrHoP_,"Tau_HadrHoP/F");
  tree_->Branch("Tau_HadrEoP",&Tau_HadrEoP_,"Tau_HadrEoP/F");
  tree_->Branch("Tau_VisMass",&Tau_VisMass_,"Tau_VisMass/F");
  tree_->Branch("Tau_GammaEtaMom",&Tau_GammaEtaMom_,"Tau_GammaEtaMom/F");
  tree_->Branch("Tau_GammaPhiMom",&Tau_GammaPhiMom_,"Tau_GammaPhiMom/F");
  tree_->Branch("Tau_GammaEnFrac",&Tau_GammaEnFrac_,"Tau_GammaEnFrac/F");
  tree_->Branch("Tau_HadrMva",&Tau_HadrMva_,"Tau_HadrMva/F");
  tree_->Branch("Tau_IsoMVAraw",&Tau_IsoMVAraw_,"Tau_IsoMVAraw/F");
  tree_->Branch("Tau_IsoMVALoose",&Tau_IsoMVALoose_,"Tau_IsoMVALoose/F");
  tree_->Branch("Tau_IsoMVAMedium",&Tau_IsoMVAMedium_,"Tau_IsoMVAMedium/F");
  tree_->Branch("Tau_IsoMVATight",&Tau_IsoMVATight_,"Tau_IsoMVATight/F");
  tree_->Branch("Tau_CombIsoDBLoose",&Tau_CombIsoDBLoose_,"Tau_CombIsoDBLoose/F");
  tree_->Branch("Tau_CombIsoDBMedium",&Tau_CombIsoDBMedium_,"Tau_CombIsoDBMedium/F");
  tree_->Branch("Tau_CombIsoDBTight",&Tau_CombIsoDBTight_,"Tau_CombIsoDBTight/F");
  tree_->Branch("Tau_AntiELoose",&Tau_AntiELoose_,"Tau_AntiELoose/F");
  tree_->Branch("Tau_AntiEMedium",&Tau_AntiEMedium_,"Tau_AntiEMedium/F");
  tree_->Branch("Tau_AntiETight",&Tau_AntiETight_,"Tau_AntiETight/F");
  tree_->Branch("Tau_AntiEMVA",&Tau_AntiEMVA_,"Tau_AntiEMVA/F");
  tree_->Branch("Tau_AntiEMVA3raw",&Tau_AntiEMVA3raw_,"Tau_AntiEMVA3raw/F");
  tree_->Branch("Tau_AntiEMVA3category",&Tau_AntiEMVA3category_,"Tau_AntiEMVA3category/F");
  tree_->Branch("Tau_AntiEVLooseMVA3",&Tau_AntiEVLooseMVA3_,"Tau_AntiEVLooseMVA3/F");
  tree_->Branch("Tau_AntiELooseMVA3",&Tau_AntiELooseMVA3_,"Tau_AntiELooseMVA3/F");
  tree_->Branch("Tau_AntiEMediumMVA3",&Tau_AntiEMediumMVA3_,"Tau_AntiEMediumMVA3/F");
  tree_->Branch("Tau_AntiETightMVA3",&Tau_AntiETightMVA3_,"Tau_AntiETightMVA3/F");
  tree_->Branch("Tau_AntiEVTightMVA3",&Tau_AntiEVTightMVA3_,"Tau_AntiEVTightMVA3/F");
  tree_->Branch("Tau_MatchElePassVeto",&Tau_MatchElePassVeto_,"Tau_MatchElePassVeto/F");

}


void AntiEMVAAnalyzer2::analyze(const edm::Event& evt, const edm::EventSetup& es)
{
  run_   = evt.run();
  event_ = (evt.eventAuxiliary()).event();
  lumi_  = evt.luminosityBlock();
  
  edm::Handle<reco::GsfElectronCollection> GsfElectrons;
  evt.getByLabel(srcGsfElectrons_, GsfElectrons);

  edm::Handle<reco::PFTauCollection> PfTaus;
  evt.getByLabel(srcPFTaus_, PfTaus);
  const reco::PFTauCollection* Pftaus = PfTaus.product();
  if(debug_){
//     std::cout<<"num PfTaus : "<<Pftaus->size()<<std::endl;
  }

  edm::Handle<pat::TauCollection> PatTaus;
  evt.getByLabel(srcPatTaus_,PatTaus);
  const pat::TauCollection* taus = PatTaus.product();
  if(debug_){
//     std::cout<<"num PatTaus : "<<taus->size()<<std::endl;
  }
  typedef edm::View<reco::Candidate> CandidateView;

  edm::Handle<CandidateView> GenElectrons;
  evt.getByLabel(srcGenElectrons_, GenElectrons);
  if( !GenElectrons.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No GenElectrons label available \n";

  edm::Handle<CandidateView> GenElectronsFromZ;
  evt.getByLabel(srcGenElectronsFromZ_, GenElectronsFromZ);
  if( !GenElectronsFromZ.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No GenElectronsFromZ label available \n";

  edm::Handle<CandidateView> GenElectronsFromZTauTau;
  evt.getByLabel(srcGenElectronsFromZTauTau_, GenElectronsFromZTauTau);
  if( !GenElectronsFromZTauTau.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No GenElectronsFromZTauTau label available \n";

  edm::Handle<CandidateView> GenTaus;
  evt.getByLabel(srcGenTaus_, GenTaus);
  if( !GenTaus.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No GenTaus label available \n";

  edm::Handle<CandidateView> GenJets;
  evt.getByLabel(srcGenJets_, GenJets);
  if( !GenJets.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No GenJets label available \n";

  edm::Handle<reco::VertexCollection> pVertexes;
  evt.getByLabel(srcPrimaryVertex_, pVertexes);
  if( !pVertexes.isValid() )  
    edm::LogError("DataNotAvailable")
      << "No PV label available \n";
  const reco::VertexCollection* vertexes = pVertexes.product();
  if(debug_){
//     std::cout<<"numPV : "<<vertexes->size()<<std::endl;
//     for(unsigned int k = 0; k<vertexes->size(); k++){
//       std::cout << "Vtx[" << k << "] (x,y,z) = (" << ((*vertexes)[k].position()).x()
// 		<< "," << ((*vertexes)[k].position()).y() << "," << ((*vertexes)[k].position()).z() << ")"
// 		<< std::endl;
//     }
  }
  NumPV_ = vertexes->size();

  ///////////////////////////////////////////////////////////////////////////
  ////////////////////////////////PfTaus variables///////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  NumPFTaus_ = 0;
  NumGsfEle_ = 0;

  for ( reco::PFTauCollection::const_iterator PfTau = PfTaus->begin();
	PfTau != PfTaus->end(); ++PfTau ) {
       
    Tau_GsfEleMatch_= 0;
    const reco::GsfElectron* MatchedElectron = 0;
    for ( reco::GsfElectronCollection::const_iterator GsfElectron = GsfElectrons->begin();
	  GsfElectron != GsfElectrons->end(); ++GsfElectron ) {
      if(deltaR(PfTau->p4(),GsfElectron->p4())<0.3 && GsfElectron->pt()>10 &&( MatchedElectron==0 || GsfElectron->pt()>MatchedElectron->pt())){
	MatchedElectron = &(*GsfElectron);
	Tau_GsfEleMatch_ = 1;
      }
      NumGsfEle_ ++;
    } 

    Tau_EtaAtEcalEntrance_ = -99;
    Tau_PhiAtEcalEntrance_ = -99;
    Tau_Eta_ = -99;
    Tau_Phi_ = -99;
    Tau_Pt_ = -99;
    Tau_LeadHadronPt_ = -99;
    Tau_HasGsf_ = -99;
    Tau_GSFChi2_ = -99;
    Tau_GSFNumHits_ = -99;
    Tau_GSFNumPixelHits_ = -99;
    Tau_GSFNumStripHits_ = -99;
    Tau_GSFTrackResol_ = -99;
    Tau_GSFTracklnPt_ = -99;
    Tau_GSFTrackEta_ = -99;
    Tau_HasKF_ = -99;
    Tau_KFChi2_ = -99;
    Tau_KFNumHits_ = -99;
    Tau_KFNumPixelHits_ = -99;
    Tau_KFNumStripHits_ = -99;
    Tau_KFTrackResol_ = -99;
    Tau_KFTracklnPt_ = -99;
    Tau_KFTrackEta_ = -99;
    Tau_EmFraction_ = -99;
    Tau_NumChargedCands_ = -99;
    Tau_NumGammaCands_ = -99;
    Tau_HadrHoP_ = -99;
    Tau_HadrEoP_ = -99;
    Tau_VisMass_ = -99;
    Tau_GammaEtaMom_ = -99;
    Tau_GammaPhiMom_ = -99;
    Tau_GammaEnFrac_ = -99;
    Tau_HadrMva_ = -99;
    Tau_IsoMVAraw_ = -99;
    Tau_IsoMVALoose_ = -99;
    Tau_IsoMVAMedium_ = -99;
    Tau_IsoMVATight_ = -99;
    Tau_CombIsoDBLoose_ = -99;
    Tau_CombIsoDBMedium_ = -99;
    Tau_CombIsoDBTight_ = -99;
    Tau_AntiELoose_ = -99;
    Tau_AntiEMedium_ = -99;
    Tau_AntiETight_ = -99;
    Tau_AntiEMVA_ = -99;
    Tau_MatchElePassVeto_ = -99;
    /////////////////////////////////////Matchings  /////////////////////////////////////
    Tau_GenEleMatch_ = 0;
    Tau_GenEleFromZMatch_ = 0;
    Tau_GenEleFromZTauTauMatch_ = 0;
    Tau_GenHadMatch_ = 0;
    Tau_GenJetMatch_ = 0;

    NumGenEle_ = 0;
    NumGenHad_ = 0;
    NumGenJet_ = 0;
    
    Elec_AbsEta_ = -99;
    Elec_Pt_ = -99;
    Elec_PFMvaOutput_ = -99;
    Elec_EarlyBrem_ =  -99;
    Elec_LateBrem_=  -99;
    Elec_Logsihih_ =  -99;
    Elec_DeltaEta_ = -99;
    Elec_Fbrem_ =  -99;
    //Variables related to the SC
    Elec_HasSC_ = -99;
    Elec_Ee_ = -99;
    Elec_Egamma_ = -99;
    Elec_Pin_ = -99;
    Elec_Pout_ = -99;
    Elec_EtotOverPin_ = -99;
    Elec_EeOverPout_ = -99;
    Elec_EgammaOverPdif_ = -99;
    Elec_HoHplusE_ = -99;
    Elec_HasKF_ = -99;
    Elec_Chi2KF_ = -99;
    Elec_KFNumHits_ = -99;
    Elec_KFNumPixelHits_ = -99;
    Elec_KFNumStripHits_ = -99;
    Elec_KFTrackResol_ = -99;
    Elec_KFTracklnPt_ = -99;
    Elec_KFTrackEta_ = -99;
    Elec_HasGSF_ = -99;
    Elec_Chi2GSF_ = -99;
    Elec_GSFNumHits_ = -99;
    Elec_GSFNumPixelHits_ = -99;
    Elec_GSFNumStripHits_ = -99;
    Elec_GSFTrackResol_ = -99;
    Elec_GSFTracklnPt_ = -99;
    Elec_GSFTrackEta_ = -99;

    ElecVeto_N_ = 0.;
    ElecVeto_Pt_ = -99;
    ElecVeto_Eta_ = -99;
    ElecVeto_Phi_ = -99;

    /////////////////////////////////////Matchings  /////////////////////////////////////
    Elec_GenEleMatch_ = 0;
    Elec_GenEleFromZMatch_ = 0;
    Elec_GenEleFromZTauTauMatch_ = 0;
    Elec_GenHadMatch_ = 0; 
    Elec_GenJetMatch_ = 0;
    
    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////////GsfElectron variables//////////////////////
    ///////////////////////////////////////////////////////////////////////////

    if(MatchedElectron){

      for ( reco::CandidateView::const_iterator GenElectron = GenElectrons->begin();
	    GenElectron != GenElectrons->end(); ++GenElectron ) {
	//       if(debug_){
	// 	std::cout<<"  DeltaR GsfEle-GenEle :"<<deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectron->eta(),GenElectron->phi())<<std::endl;
	//       }
	NumGenEle_++;
	if(deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectron->eta(),GenElectron->phi())<0.3) Elec_GenEleMatch_ = 1;
      }
      for ( reco::CandidateView::const_iterator GenElectronFromZ = GenElectronsFromZ->begin();
	    GenElectronFromZ != GenElectronsFromZ->end(); ++GenElectronFromZ ) {
	//       if(debug_){
	  // 	std::cout<<"  DeltaR GsfEle-GenEleFromZ :"<<deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectronFromZ->eta(),GenElectronFromZ->phi())<<std::endl;
	  //       }
	if(deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectronFromZ->eta(),GenElectronFromZ->phi())<0.3) Elec_GenEleFromZMatch_ = 1;
      }
      for ( reco::CandidateView::const_iterator GenElectronFromZTauTau = GenElectronsFromZTauTau->begin();
	    GenElectronFromZTauTau != GenElectronsFromZTauTau->end(); ++GenElectronFromZTauTau ) {
	//       if(debug_){
	// 	std::cout<<"  DeltaR GsfEle-GenEleFromZTauTau :"<<deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectronFromZTauTau->eta(),GenElectronFromZTauTau->phi())<<std::endl;
	//       }
	if(deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenElectronFromZTauTau->eta(),GenElectronFromZTauTau->phi())<0.3) Elec_GenEleFromZTauTauMatch_ = 1;
      }
      for ( reco::CandidateView::const_iterator GenTau = GenTaus->begin();
	    GenTau != GenTaus->end(); ++GenTau ) {
	//       if(debug_){
	// 	std::cout<<"  DeltaR GsfEle-GenTau :"<<deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenTau->eta(),GenTau->phi())<<std::endl;
	//       }
	NumGenHad_++;
	if(deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenTau->eta(),GenTau->phi())<0.3)Elec_GenHadMatch_ = 1;
      }
      for ( reco::CandidateView::const_iterator GenJet = GenJets->begin();
	    GenJet != GenJets->end(); ++GenJet ) {
	//       if(debug_){
	// 	std::cout<<"  DeltaR GsfEle-GenJet :"<<deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenJet->eta(),GenJet->phi())<<std::endl;
	//       }
	NumGenJet_++;
	if(deltaR(MatchedElectron->eta(),MatchedElectron->phi(),GenJet->eta(),GenJet->phi())<0.3)Elec_GenJetMatch_ = 1;
      }
      /////////////////////////////////////Matchings  /////////////////////////////////////
      
      Elec_AbsEta_ = TMath::Abs(MatchedElectron->eta());
      Elec_Pt_ = MatchedElectron->pt();
      Elec_PFMvaOutput_ = TMath::Max(MatchedElectron->mvaOutput().mva,float(-1.0));
      Elec_EarlyBrem_ = MatchedElectron->mvaInput().earlyBrem;
      Elec_LateBrem_= MatchedElectron->mvaInput().lateBrem;
      Elec_Logsihih_ = log(MatchedElectron->mvaInput().sigmaEtaEta);
      Elec_DeltaEta_ = MatchedElectron->mvaInput().deltaEta;
      Elec_Fbrem_ = MatchedElectron->fbrem();
      
      //Variables related to the SC
      Elec_HasSC_ = 0.;
      reco::SuperClusterRef pfSuperCluster = MatchedElectron->pflowSuperCluster();
      if(pfSuperCluster.isNonnull() && pfSuperCluster.isAvailable()){
	Elec_HasSC_ = 1.;
	Elec_Ee_ = 0.;
	Elec_Egamma_ = 0.;
	//       if (debug_)std::cout<<"SuperCluster accessed   "<<std::endl;
	for (reco::CaloCluster_iterator pfCluster = pfSuperCluster->clustersBegin();
	     pfCluster != pfSuperCluster->clustersEnd(); ++pfCluster ) {
	  float pfClusterEn = (*pfCluster)->energy();
	  if ( pfCluster == pfSuperCluster->clustersBegin() ) Elec_Ee_ += pfClusterEn;
	  else Elec_Egamma_ += pfClusterEn;
	}
	Elec_Pin_ = TMath::Sqrt(MatchedElectron->trackMomentumAtVtx().Mag2());
	Elec_Pout_ = TMath::Sqrt(MatchedElectron->trackMomentumOut().Mag2()); 
	Elec_EtotOverPin_ = (Elec_Ee_+Elec_Egamma_)/Elec_Pin_;
	Elec_EeOverPout_ = Elec_Ee_/Elec_Pout_;
	Elec_EgammaOverPdif_ = Elec_Egamma_/(Elec_Pin_-Elec_Pout_);
	Elec_HoHplusE_ = MatchedElectron->mvaInput().hadEnergy/(MatchedElectron->mvaInput().hadEnergy+Elec_Ee_) ;
      }
      //Variables related to the CtfTrack
      Elec_HasKF_ = 0.;
      if (MatchedElectron->closestCtfTrackRef().isNonnull()){
	Elec_HasKF_ = 1.;
	Elec_Chi2KF_ = MatchedElectron->closestCtfTrackRef()->normalizedChi2();
	Elec_KFNumHits_ = MatchedElectron->closestCtfTrackRef()->numberOfValidHits();
	Elec_KFNumPixelHits_ = MatchedElectron->closestCtfTrackRef()->hitPattern().numberOfValidPixelHits();
	Elec_KFNumStripHits_ = MatchedElectron->closestCtfTrackRef()->hitPattern().numberOfValidStripHits();
    	Elec_KFTrackResol_ = MatchedElectron->closestCtfTrackRef()->ptError()/MatchedElectron->closestCtfTrackRef()->pt();
	Elec_KFTracklnPt_ = log(MatchedElectron->closestCtfTrackRef()->pt())*TMath::Ln10();
	Elec_KFTrackEta_ = MatchedElectron->closestCtfTrackRef()->eta();
       }
      //Variables related to the GsfTrack
      Elec_HasGSF_ = 0.;
      if(MatchedElectron->gsfTrack().isNonnull()){
	Elec_HasGSF_ = 1.;
	Elec_Chi2GSF_ = MatchedElectron->gsfTrack()->normalizedChi2();
	Elec_GSFNumHits_ = MatchedElectron->gsfTrack()->numberOfValidHits();
	Elec_GSFNumPixelHits_ = MatchedElectron->gsfTrack()->hitPattern().numberOfValidPixelHits();
	Elec_GSFNumStripHits_ = MatchedElectron->gsfTrack()->hitPattern().numberOfValidStripHits();
    	Elec_GSFTrackResol_ = MatchedElectron->gsfTrack()->ptError()/MatchedElectron->gsfTrack()->pt();
	Elec_GSFTracklnPt_ = log(MatchedElectron->gsfTrack()->pt())*TMath::Ln10();
	Elec_GSFTrackEta_ = MatchedElectron->gsfTrack()->eta();
      }
    
      if(debug_){
	//       std::cout<<"Elec_AbsEta :"<<Elec_AbsEta_<<std::endl;
	//       std::cout<<"Elec_Pt :"<<Elec_Pt_<<std::endl;
	//       std::cout<<"Elec_HasSC :"<<Elec_HasSC_<<std::endl;
	// 	 std::cout<<"Elec_Ee :   "<<Elec_Ee_<<" Elec_Egamma :  "<<Elec_Egamma_<<std::endl;
	// 	 std::cout<<"Elec_Pin :   "<<Elec_Pin_<<" Elec_Pout :  "<<Elec_Pout_<<std::endl;
	//       std::cout<<"Elec_HasKF :"<<Elec_HasKF_<<std::endl;
	//       std::cout<<"Elec_HasGSF :"<<Elec_HasGSF_<<std::endl;
	//       std::cout<<"Elec PFMvaOutput :"<<Elec_PFMvaOutput_<<std::endl;
	//       std::cout<<"E electron cluster plus photons over Pin :   "<<Elec_EtotOverPin_<<std::endl;
	//       std::cout<<"E electron cluster over Pout :   "<<Elec_EeOverPout_<<std::endl;
	//       std::cout<<"E photons over (Elec_Pin - Elec_Pout) :   "<<Elec_EgammaOverPdif_<<std::endl;
	//       std::cout<<"EarlyBrem :   "<<Elec_EarlyBrem_<<std::endl;
	//       std::cout<<"LateBrem :   "<<Elec_LateBrem_<<std::endl;
	//       std::cout<<"log(sigma EtaEta with the SC) :  "<<Elec_Logsihih_<<std::endl;
	//       std::cout<<"PF-cluster GSF track delta-eta :  "<<Elec_DeltaEta_<<std::endl;
	//       std::cout<<"H over H plus E :   "<<Elec_HoHplusE_<<std::endl;
	//       std::cout<<"FBrem :   "<<Elec_Fbrem_<<std::endl;
	//       std::cout<<"Normalized Chi2 KF :   "<<Elec_Chi2KF_<<std::endl;
	//       std::cout<<"Normalized Chi2 GSF :   "<<Elec_Chi2GSF_<<std::endl;
	//       std::cout<<"Number of valid hits KF :   "<<Elec_NumHits_<<std::endl;
	//       std::cout<<"GSFTrack sig(Pt)/Pt :   "<<Elec_GSFTrackResol_<<std::endl;
	//       std::cout<<"GSFTrack ln(Pt) :   "<<Elec_GSFTracklnPt_<<std::endl;
	//       std::cout<<"GSFTrack Eta :   "<<Elec_GSFTrackEta_<<std::endl;
	//       std::cout<<std::endl;
      }

    }//if MatchedElectron

    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////////PfTau variables//////////////////////
    ///////////////////////////////////////////////////////////////////////////

    for ( reco::CandidateView::const_iterator GenElectron = GenElectrons->begin();
	  GenElectron != GenElectrons->end(); ++GenElectron ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),GenElectron->eta(),GenElectron->phi())<0.3)Tau_GenEleMatch_ = 1;
    }
    for ( reco::CandidateView::const_iterator GenElectronFromZ = GenElectronsFromZ->begin();
	  GenElectronFromZ != GenElectronsFromZ->end(); ++GenElectronFromZ ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),GenElectronFromZ->eta(),GenElectronFromZ->phi())<0.3) Tau_GenEleFromZMatch_ = 1;
    }
    for ( reco::CandidateView::const_iterator GenElectronFromZTauTau = GenElectronsFromZTauTau->begin();
	  GenElectronFromZTauTau != GenElectronsFromZTauTau->end(); ++GenElectronFromZTauTau ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),GenElectronFromZTauTau->eta(),GenElectronFromZTauTau->phi())<0.3) Tau_GenEleFromZTauTauMatch_ = 1;
    }
    for ( reco::CandidateView::const_iterator GenTau = GenTaus->begin();
	  GenTau != GenTaus->end(); ++GenTau ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),GenTau->eta(),GenTau->phi())<0.3)Tau_GenHadMatch_ = 1;
    }
    for ( reco::CandidateView::const_iterator GenJet = GenJets->begin();
	  GenJet != GenJets->end(); ++GenJet ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),GenJet->eta(),GenJet->phi())<0.3)Tau_GenJetMatch_ = 1;
    }
    /////////////////////////////////////Matchings  /////////////////////////////////////
    float sumEtaTimesEnergy = 0;
    float sumEnergy = 0;
    for(unsigned int j = 0 ; j < (PfTau->signalPFCands()).size() ; j++){
       reco::PFCandidateRef pfcandidate = (PfTau->signalPFCands()).at(j);
       sumEtaTimesEnergy += pfcandidate->positionAtECALEntrance().eta()*pfcandidate->energy();
       sumEnergy += pfcandidate->energy();
    }
    if(sumEnergy>0)Tau_EtaAtEcalEntrance_ = sumEtaTimesEnergy/sumEnergy;

    float sumPhiTimesEnergy = 0;
    float sumEnergyPhi = 0;
    for(unsigned int j = 0 ; j < (PfTau->signalPFCands()).size() ; j++){
       reco::PFCandidateRef pfcandidate = (PfTau->signalPFCands()).at(j);
       sumPhiTimesEnergy += pfcandidate->positionAtECALEntrance().phi()*pfcandidate->energy();
       sumEnergyPhi += pfcandidate->energy();
    }
    if(sumEnergyPhi>0)Tau_PhiAtEcalEntrance_ = sumPhiTimesEnergy/sumEnergyPhi;

    Tau_Eta_ = PfTau->eta();
    Tau_Pt_ = PfTau->pt();
    Tau_Phi_ = PfTau->phi();
    Tau_EmFraction_ = TMath::Max(PfTau->emFraction(),float(0.0));
    Tau_NumChargedCands_ = PfTau->signalPFChargedHadrCands().size();
    Tau_NumGammaCands_  = PfTau->signalPFGammaCands().size();
    Tau_LeadHadronPt_ = PfTau->leadPFChargedHadrCand()->pt();
    Tau_HasGsf_ = (PfTau->leadPFChargedHadrCand()->gsfTrackRef()).isNonnull();
    if((PfTau->leadPFChargedHadrCand()->gsfTrackRef()).isNonnull()){
      Tau_GSFChi2_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->normalizedChi2();
      Tau_GSFNumHits_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->numberOfValidHits();
      Tau_GSFNumPixelHits_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->hitPattern().numberOfValidPixelHits();
      Tau_GSFNumStripHits_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->hitPattern().numberOfValidStripHits();
      Tau_GSFTrackResol_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->ptError()/PfTau->leadPFChargedHadrCand()->gsfTrackRef()->pt();
      Tau_GSFTracklnPt_ = log(PfTau->leadPFChargedHadrCand()->gsfTrackRef()->pt())*TMath::Ln10();
      Tau_GSFTrackEta_ = PfTau->leadPFChargedHadrCand()->gsfTrackRef()->eta();
    }
    Tau_HasKF_ = (PfTau->leadPFChargedHadrCand()->trackRef()).isNonnull();
    if((PfTau->leadPFChargedHadrCand()->trackRef()).isNonnull()){
      Tau_KFChi2_ = PfTau->leadPFChargedHadrCand()->trackRef()->normalizedChi2();
      Tau_KFNumHits_ = PfTau->leadPFChargedHadrCand()->trackRef()->numberOfValidHits();
      Tau_KFNumPixelHits_ = PfTau->leadPFChargedHadrCand()->trackRef()->hitPattern().numberOfValidPixelHits();
      Tau_KFNumStripHits_ = PfTau->leadPFChargedHadrCand()->trackRef()->hitPattern().numberOfValidStripHits();
      Tau_KFTrackResol_ = PfTau->leadPFChargedHadrCand()->trackRef()->ptError()/PfTau->leadPFChargedHadrCand()->trackRef()->pt();
      Tau_KFTracklnPt_ = log(PfTau->leadPFChargedHadrCand()->trackRef()->pt())*TMath::Ln10();
      Tau_KFTrackEta_ = PfTau->leadPFChargedHadrCand()->trackRef()->eta();
    }

    Tau_HadrHoP_ = PfTau->leadPFChargedHadrCand()->hcalEnergy()/PfTau->leadPFChargedHadrCand()->p();
    Tau_HadrEoP_ = PfTau->leadPFChargedHadrCand()->ecalEnergy()/PfTau->leadPFChargedHadrCand()->p();

    GammasdEta.clear();
    GammasdPhi.clear();
    GammasPt.clear();

    for(unsigned int k = 0 ; k < (PfTau->signalPFGammaCands()).size() ; k++){
      reco::PFCandidateRef gamma = (PfTau->signalPFGammaCands()).at(k);
      if( (PfTau->leadPFChargedHadrCand()).isNonnull() ){
	GammasdEta.push_back( gamma->eta() - PfTau->leadPFChargedHadrCand()->eta() );
	GammasdPhi.push_back( gamma->phi() - PfTau->leadPFChargedHadrCand()->phi() );
      }
      else{
	GammasdEta.push_back( gamma->eta() - PfTau->eta() );
	GammasdPhi.push_back( gamma->phi() - PfTau->phi() );
      }
      GammasPt.push_back(  gamma->pt() );
    }
    
    float sumPt  = 0;
    float dEta   = 0;
    float dEta2  = 0;
    float dPhi   = 0;
    float dPhi2  = 0;
    float sumPt2 = 0;
    
    for(unsigned int k = 0 ; k < GammasPt.size() ; k++){
      float pt_k  = GammasPt[k];
      float phi_k = GammasdPhi[k];
      if (GammasdPhi[k] > TMath::Pi()) phi_k = GammasdPhi[k] - 2*TMath::Pi();
      else if(GammasdPhi[k] < -TMath::Pi()) phi_k = GammasdPhi[k] + 2*TMath::Pi();
      float eta_k = GammasdEta[k];
      sumPt  +=  pt_k;
      sumPt2 += (pt_k*pt_k);
      dEta   += (pt_k*eta_k);
      dEta2  += (pt_k*eta_k*eta_k);
      dPhi   += (pt_k*phi_k);
      dPhi2  += (pt_k*phi_k*phi_k);  
    }
    
    float GammadPt_ = sumPt/PfTau->pt();
	    
    if(sumPt>0){
      dEta  /= sumPt;
      dPhi  /= sumPt;
      dEta2 /= sumPt;
      dPhi2 /= sumPt;
    }

    Tau_GammaEtaMom_ = TMath::Sqrt(dEta2)*TMath::Sqrt(GammadPt_)*PfTau->pt();
    Tau_GammaPhiMom_ = TMath::Sqrt(dPhi2)*TMath::Sqrt(GammadPt_)*PfTau->pt();  
    Tau_GammaEnFrac_ = GammadPt_;
    Tau_VisMass_ = PfTau->mass();
    Tau_HadrMva_ = TMath::Max(PfTau->electronPreIDOutput(),float(-1.0));

    if(debug_){
//       std::cout<<"PfTauLoop number : "<<NumPFTaus_<<std::endl;
//       std::cout<<"  GammaEtaMom : "<<Tau_GammaEtaMom_<<std::endl;
//       std::cout<<"  GammaPhiMom : "<<Tau_GammaPhiMom_<<std::endl;
//       std::cout<<"  GammaPt : "<<sumPt<<std::endl;
//       std::cout<<"  TauPt : "<<PfTau->pt()<<std::endl;
//       std::cout<<"  TauEta : "<<PfTau->eta()<<std::endl;
//       std::cout<<"  TauEtaAtEcalEntrance : "<<Tau_EtaAtEcalEntrance_<<std::endl;
//       std::cout<<"  sumEtaTimesEnergy : "<<sumEtaTimesEnergy<<std::endl;
//       std::cout<<"  sumEnergy : "<<sumEnergy<<std::endl;
//       std::cout<<"  GammaEnFrac : "<<Tau_GammaEnFrac_<<std::endl;
    }
    NumPatTaus_ = 0;
    int countMatch = 0;
    for (pat::TauCollection::const_iterator  PatTau = PatTaus->begin();
	  PatTau != PatTaus->end(); ++PatTau ) {
      if(deltaR(PfTau->eta(),PfTau->phi(),PatTau->eta(),PatTau->phi())<0.01){
	countMatch++;
	Tau_IsoMVAraw_ = PatTau->tauID("byIsolationMVAraw");
	Tau_IsoMVALoose_ = PatTau->tauID("byLooseIsolationMVA");
	Tau_IsoMVAMedium_ = PatTau->tauID("byMediumIsolationMVA");
	Tau_IsoMVATight_ = PatTau->tauID("byTightIsolationMVA");
	Tau_CombIsoDBLoose_ = PatTau->tauID("byLooseCombinedIsolationDeltaBetaCorr");
	Tau_CombIsoDBMedium_ = PatTau->tauID("byMediumCombinedIsolationDeltaBetaCorr");
	Tau_CombIsoDBTight_ = PatTau->tauID("byTightCombinedIsolationDeltaBetaCorr");
	Tau_AntiELoose_ = PatTau->tauID("againstElectronLoose");
	Tau_AntiEMedium_ = PatTau->tauID("againstElectronMedium");
	Tau_AntiETight_ = PatTau->tauID("againstElectronTight");
	Tau_AntiEMVA_ = PatTau->tauID("againstElectronMVA");
	Tau_AntiEMVA3raw_ = PatTau->tauID("againstElectronMVA3raw");
	Tau_AntiEMVA3category_ = PatTau->tauID("againstElectronMVA3category");
	Tau_AntiEVLooseMVA3_ = PatTau->tauID("againstElectronVLooseMVA3");
	Tau_AntiELooseMVA3_ = PatTau->tauID("againstElectronLooseMVA3");
	Tau_AntiEMediumMVA3_ = PatTau->tauID("againstElectronMediumMVA3");
	Tau_AntiETightMVA3_ = PatTau->tauID("againstElectronTightMVA3");
	Tau_AntiEVTightMVA3_ = PatTau->tauID("againstElectronVTightMVA3");

	if(debug_){
// 	  std::cout<<"===================>PAT MATCHED!!"<<std::endl;
// 	  std::cout<<" PatTauLoop number : "<<NumPatTaus_<<std::endl;
// 	  std::cout<<"  PfTau  : "<<PfTau->pt()<<" "<<PfTau->eta()<<" "<<PfTau->phi()<<std::endl;
// 	  std::cout<<"  PatTau : "<<PatTau->pt()<<" "<<PatTau->eta()<<" "<<PatTau->phi()<<std::endl;
// 	  std::cout<<" PatTau AntiELoose : "<<PatTau->tauID("againstElectronLoose")<<std::endl;
// 	  std::cout<<" PatTau AntiEMedium : "<<PatTau->tauID("againstElectronMedium")<<std::endl;
// 	  std::cout<<" PatTau AntiETight : "<<PatTau->tauID("againstElectronTight")<<std::endl;
// 	  std::cout<<" PatTau AntiEMVA : "<<PatTau->tauID("againstElectronMVA")<<std::endl;
// 	  std::cout<<" PatTau DecayMode : "<<PatTau->tauID("decayModeFinding")<<std::endl;
// 	  std::cout<<" PatTau CombIsoDB : "<<PatTau->tauID("byLooseCombinedIsolationDeltaBetaCorr")<<std::endl;
	}
      }
      NumPatTaus_++ ;   
    }
    
    //Tau is matched to a gsfElectron passing CutsVeto for SecondElectronVeto
    bool matchElectronCutsVeto = false;
    float matchElectronCutsVetoFloat = 0;
    for ( reco::GsfElectronCollection::const_iterator GsfElectron = GsfElectrons->begin();
	  GsfElectron != GsfElectrons->end(); ++GsfElectron ) {
      const reco::Track *el_track = (const reco::Track*)((GsfElectron)->gsfTrack().get());  
      const reco::HitPattern& p_inner = el_track->trackerExpectedHitsInner(); 
      float nHits = p_inner.numberOfHits();
      float dPhi  = fabs(GsfElectron->deltaPhiSuperClusterTrackAtVtx());
      float dEta  = fabs(GsfElectron->deltaEtaSuperClusterTrackAtVtx());
      float sihih = GsfElectron->sigmaIetaIeta();
      float HoE   = GsfElectron->hadronicOverEm();
      if(debug_){
	std::cout<<"GsfElectron nHits: "<<nHits<<std::endl;
	std::cout<<"GsfElectron dPhi: "<<dPhi<<std::endl;
	std::cout<<"GsfElectron dEta: "<<dEta<<std::endl;
	std::cout<<"GsfElectron sihih: "<<sihih<<std::endl;
	std::cout<<"GsfElectron HoE: "<<HoE<<std::endl;
      }
      bool ElectronPassCutsVeto = false;
      if((nHits<=999) &&
	 ((fabs(GsfElectron->eta())<1.5) &&
	  (sihih < 0.010) &&
	  (dPhi < 0.80) &&
	  (dEta < 0.007) &&
	  (HoE < 0.15)) ||
	 ((fabs(GsfElectron->eta())>1.5) && (fabs(GsfElectron->eta())<2.3) &&
	  (sihih < 0.030) &&
	  (dPhi < 0.70) &&
	  (dEta < 0.010) &&
	  (HoE < 999))
	 ) ElectronPassCutsVeto = true ;
      double ElePt = GsfElectron->pt();
      if ((deltaR(PfTau->eta(),PfTau->phi(),GsfElectron->eta(),GsfElectron->phi())<0.3) && ElectronPassCutsVeto && ElePt>ElecVeto_Pt_ ){
	matchElectronCutsVeto = true;
	ElecVeto_Pt_ = ElePt;
	ElecVeto_Eta_ = GsfElectron->eta();
	ElecVeto_Phi_ = GsfElectron->phi();
	ElecVeto_N_++;
      } 
    }//Loop on GsfElectrons
    if(matchElectronCutsVeto)matchElectronCutsVetoFloat = 1;
    Tau_MatchElePassVeto_ = matchElectronCutsVetoFloat;
    
    NumPFTaus_++;

    tree_->Fill();
  
  
  }//Loop on PFTaus
    

}//analyze()

AntiEMVAAnalyzer2::~AntiEMVAAnalyzer2()
{

}
void AntiEMVAAnalyzer2::endJob()
{
// nothing to be done yet...
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(AntiEMVAAnalyzer2);



