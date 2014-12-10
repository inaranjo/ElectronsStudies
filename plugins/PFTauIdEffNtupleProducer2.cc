#include "TauAnalysis/Test/plugins/PFTauIdEffNtupleProducer2.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TauAnalysis/CandidateTools/interface/candidateAuxFunctions.h"

#include <TMath.h>

int PFTauIdEffNtupleProducer2::verbosity_ = 0;

PFTauIdEffNtupleProducer2::PFTauIdEffNtupleProducer2(const edm::ParameterSet& cfg) 
  : moduleLabel_(cfg.getParameter<std::string>("@module_label")),
    ntuple_(0)
{
  srcGenParticles_ = cfg.getParameter<edm::InputTag>("srcGenParticles");
  srcRecVetoElectrons_ = cfg.getParameter<edm::InputTag>("srcRecVetoElectrons");
  srcRecTaus_ = cfg.getParameter<edm::InputTag>("srcRecTaus");
  srcVertices_ = cfg.getParameter<edm::InputTag>("srcVertices");

  srcWeights_ = cfg.getParameter<vInputTag>("srcWeights");

  tauIdDiscriminators_.push_back("decayModeFinding");
  tauIdDiscriminators_.push_back("byCombinedIsolationDeltaBetaCorrRaw");
  tauIdDiscriminators_.push_back("byVLooseCombinedIsolationDeltaBetaCorr");
  tauIdDiscriminators_.push_back("byLooseCombinedIsolationDeltaBetaCorr");
  tauIdDiscriminators_.push_back("byMediumCombinedIsolationDeltaBetaCorr");
  tauIdDiscriminators_.push_back("byTightCombinedIsolationDeltaBetaCorr");
  tauIdDiscriminators_.push_back("byCombinedIsolationDeltaBetaCorrRaw3Hits");
  tauIdDiscriminators_.push_back("byLooseCombinedIsolationDeltaBetaCorr3Hits");
  tauIdDiscriminators_.push_back("byMediumCombinedIsolationDeltaBetaCorr3Hits");
  tauIdDiscriminators_.push_back("byTightCombinedIsolationDeltaBetaCorr3Hits");
  tauIdDiscriminators_.push_back("byIsolationMVAraw");
  tauIdDiscriminators_.push_back("byLooseIsolationMVA");
  tauIdDiscriminators_.push_back("byMediumIsolationMVA");
  tauIdDiscriminators_.push_back("byTightIsolationMVA");
  tauIdDiscriminators_.push_back("byIsolationMVA2raw");
  tauIdDiscriminators_.push_back("byLooseIsolationMVA2");
  tauIdDiscriminators_.push_back("byMediumIsolationMVA2");
  tauIdDiscriminators_.push_back("byTightIsolationMVA2");
  tauIdDiscriminators_.push_back("againstElectronLoose");
  tauIdDiscriminators_.push_back("againstElectronMedium");
  tauIdDiscriminators_.push_back("againstElectronTight");
  tauIdDiscriminators_.push_back("againstElectronNewMVA3raw");
  tauIdDiscriminators_.push_back("againstElectronNewMVA3category");
  tauIdDiscriminators_.push_back("againstElectronLooseNewMVA3");
  tauIdDiscriminators_.push_back("againstElectronMediumNewMVA3");
  tauIdDiscriminators_.push_back("againstElectronTightNewMVA3");
  tauIdDiscriminators_.push_back("againstElectronVTightNewMVA3");
  tauIdDiscriminators_.push_back("againstElectronMVA3raw");
  tauIdDiscriminators_.push_back("againstElectronMVA3category");
  tauIdDiscriminators_.push_back("againstElectronLooseMVA3");
  tauIdDiscriminators_.push_back("againstElectronMediumMVA3");
  tauIdDiscriminators_.push_back("againstElectronTightMVA3");
  tauIdDiscriminators_.push_back("againstElectronVTightMVA3");
  tauIdDiscriminators_.push_back("againstElectronDeadECAL");
  tauIdDiscriminators_.push_back("againstMuonLoose");
  tauIdDiscriminators_.push_back("againstMuonMedium");
  tauIdDiscriminators_.push_back("againstMuonTight");
  tauIdDiscriminators_.push_back("againstMuonLoose2");
  tauIdDiscriminators_.push_back("againstMuonMedium2");
  tauIdDiscriminators_.push_back("againstMuonTight2");
  tauIdDiscriminators_.push_back("againstMuonLoose3");
  tauIdDiscriminators_.push_back("againstMuonTight3");
  tauIdDiscriminators_.push_back("againstMuonMVA3raw");
  tauIdDiscriminators_.push_back("againstMuonMVALoose");
  tauIdDiscriminators_.push_back("againstMuonMVAMedium");
  tauIdDiscriminators_.push_back("againstMuonMVATight");

  minGenVisPt_ = 15.;
}

PFTauIdEffNtupleProducer2::~PFTauIdEffNtupleProducer2()
{
// nothing to be done yet...
}

void PFTauIdEffNtupleProducer2::beginJob()
{
//--- create TTree
  edm::Service<TFileService> fs;
  ntuple_ = fs->make<TTree>("pfTauIdEffNtuple", "pfTauIdEffNtuple");

//--- add branches 
  addBranch("run");
  addBranch("event");
  addBranch("lumi");

  addBranch_EnPxPyPz("recTau");
  addBranch("recTauDecayMode");
  addBranch_EnPxPyPz("recJet");
  addBranch_EnPxPyPz("leadPFCand");
  addBranch_EnPxPyPz("leadPFChargedHadrCand");
  addBranch("Tau_HoP");
  for ( vstring::const_iterator tauIdDiscriminator = tauIdDiscriminators_.begin();
	tauIdDiscriminator != tauIdDiscriminators_.end(); ++tauIdDiscriminator ) {
    addBranch(*tauIdDiscriminator);
  }
  addBranch("ElectronVetoDeltaR");
  addBranch("ElectronVetoMatch");
  addBranch_EnPxPyPz("genTau");
  addBranch("genTauDecayMode");
  addBranch("genTauMatch");
  addBranch("genTauDeltaR");
  addBranch_EnPxPyPz("genElectron");
  addBranch("genElectronMatch");
  addBranch("genElectronDeltaR");
  addBranch_EnPxPyPz("genMuon");
  addBranch("genMuonMatch");
  addBranch("genMuonDeltaR");
  addBranch("numVertices");
  addBranch("evtWeight");
}

const pat::Tau* PFTauIdEffNtupleProducer2::findMatchingRecTau(const pat::TauCollection& recTaus, const reco::Candidate::LorentzVector& genParticleP4)
{
  const pat::Tau* recTau_matched = 0;
  
  double genTauDeltaR = 9.9;
  for ( pat::TauCollection::const_iterator recTau = recTaus.begin();
	recTau != recTaus.end(); ++recTau ) {
    
    if ( recTau->pt() < 15. ) continue;
    
    double dR = deltaR(recTau->p4(), genParticleP4);
    if ( dR < 0.3 && dR < genTauDeltaR ) {
      genTauDeltaR = dR;
      recTau_matched = &(*recTau);
    }
  }

  return recTau_matched;
}

const pat::Electron* PFTauIdEffNtupleProducer2::findMatchingElectronVeto(const pat::Tau& recTau, const pat::ElectronCollection& recVetoElectrons)
{
  const pat::Electron* recElectronVeto_matched = 0;
  
  double EleVetoDeltaR = 9.9;
  for ( pat::ElectronCollection::const_iterator recElectron = recVetoElectrons.begin();
	recElectron != recVetoElectrons.end(); ++recElectron ) {
    
    if ( recElectron->pt() < 10. ) continue;
    
    double dR = deltaR(recElectron->p4(), recTau);
    if ( dR < 0.3 && dR < EleVetoDeltaR ) {
      EleVetoDeltaR = dR;
      recElectronVeto_matched = &(*recElectron);
    }
  }

  return recElectronVeto_matched;
}

void PFTauIdEffNtupleProducer2::setRecTauValues(const pat::Tau* recTau_matched ,const pat::ElectronCollection& recVetoElectrons)
{
  if ( recTau_matched ) {
    setValue_EnPxPyPz("recTau", recTau_matched->p4());
    setValue("recTauDecayMode", recTau_matched->decayMode());
    setValue_EnPxPyPz("recJet", recTau_matched->pfJetRef()->p4());
    if ( recTau_matched->leadPFCand().isNonnull() ) setValue_EnPxPyPz("leadPFCand", recTau_matched->leadPFCand()->p4());
    else setValue_EnPxPyPz("leadPFCand", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    if ( recTau_matched->leadPFChargedHadrCand().isNonnull() ){
      setValue_EnPxPyPz("leadPFChargedHadrCand", recTau_matched->leadPFChargedHadrCand()->p4());
      setValue("Tau_HoP", recTau_matched->leadPFChargedHadrCand()->hcalEnergy()/recTau_matched->leadPFChargedHadrCand()->p());
    }
    else setValue_EnPxPyPz("leadPFChargedHadrCand", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    for ( vstring::const_iterator tauIdDiscriminator = tauIdDiscriminators_.begin();
	  tauIdDiscriminator != tauIdDiscriminators_.end(); ++tauIdDiscriminator ) {
      setValue(*tauIdDiscriminator, recTau_matched->tauID(*tauIdDiscriminator));
    }

    const pat::Electron* ElectronVeto_matched = findMatchingElectronVeto(*recTau_matched, recVetoElectrons);
    double ElectronVetoDeltaR = ( ElectronVeto_matched ) ? deltaR(ElectronVeto_matched->p4(), recTau_matched->p4()) : 9.9;
    bool ElectronVetoMatch = (ElectronVetoDeltaR < 0.3);
    setValue("ElectronVetoDeltaR", ElectronVetoDeltaR);
    setValue("ElectronVetoMatch", ElectronVetoMatch);

  } else {
    setValue_EnPxPyPz("recTau", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    setValue("recTauDecayMode", -1);
    setValue_EnPxPyPz("recJet", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    setValue_EnPxPyPz("leadPFCand", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    setValue_EnPxPyPz("leadPFChargedHadrCand", reco::Candidate::LorentzVector(0.,0.,0.,0.));
    setValue("Tau_HoP", 0.);
    for ( vstring::const_iterator tauIdDiscriminator = tauIdDiscriminators_.begin();
	  tauIdDiscriminator != tauIdDiscriminators_.end(); ++tauIdDiscriminator ) {
      setValue(*tauIdDiscriminator, 0.);
    }
    setValue("ElectronVetoDeltaR", 0.);
    setValue("ElectronVetoMatch", 0.);
  }
}

void PFTauIdEffNtupleProducer2::setGenTauMatchValues(bool genTauMatch, const reco::Candidate::LorentzVector& genTauP4, int genTauDecayMode, double genTauDeltaR)
{
  setValue_EnPxPyPz("genTau", genTauP4);
  setValue("genTauDecayMode", genTauDecayMode);
  setValue("genTauMatch", genTauMatch);
  setValue("genTauDeltaR", genTauDeltaR);
}

void PFTauIdEffNtupleProducer2::setGenElectronMatchValues(bool genElectronMatch, const reco::Candidate::LorentzVector& genElectronP4, double genElectronDeltaR)
{
  setValue_EnPxPyPz("genElectron", genElectronP4);
  setValue("genElectronMatch", genElectronMatch);
  setValue("genElectronDeltaR", genElectronDeltaR);
}

void PFTauIdEffNtupleProducer2::setGenMuonMatchValues(bool genMuonMatch, const reco::Candidate::LorentzVector& genMuonP4, double genMuonDeltaR)
{
  setValue_EnPxPyPz("genMuon", genMuonP4);
  setValue("genMuonMatch", genMuonMatch);
  setValue("genMuonDeltaR", genMuonDeltaR);
}

void PFTauIdEffNtupleProducer2::produce(edm::Event& evt, const edm::EventSetup& es) 
{
  setValue("run" ,evt.run());
  setValue("event", (evt.eventAuxiliary()).event());
  setValue("lumi", evt.luminosityBlock());
  
  assert(ntuple_);

  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(srcGenParticles_, genParticles);

  std::vector<int> pdgIdsGenTau;
  pdgIdsGenTau.push_back(-15);
  pdgIdsGenTau.push_back(+15);

  std::vector<int> pdgIdsGenElectron;
  pdgIdsGenElectron.push_back(-11);
  pdgIdsGenElectron.push_back(+11);

  std::vector<int> pdgIdsGenMuon;
  pdgIdsGenMuon.push_back(-13);
  pdgIdsGenMuon.push_back(+13);

  edm::Handle<pat::ElectronCollection> recVetoElectrons;
  evt.getByLabel(srcRecVetoElectrons_, recVetoElectrons);

  edm::Handle<pat::TauCollection> recTaus;
  evt.getByLabel(srcRecTaus_, recTaus);

  edm::Handle<reco::VertexCollection> vertices;
  evt.getByLabel(srcVertices_, vertices);

  double evtWeight = 1.0;
  for ( vInputTag::const_iterator srcWeight = srcWeights_.begin();
	srcWeight != srcWeights_.end(); ++srcWeight ) {
    edm::Handle<double> weight;
    evt.getByLabel(*srcWeight, weight);
    evtWeight *= (*weight);
  }

  for ( reco::GenParticleCollection::const_iterator genParticle = genParticles->begin();
	genParticle != genParticles->end(); ++genParticle ) {

    if ( genParticle->energy() < minGenVisPt_ ) continue;

    unsigned numHypotheses = 0;

    bool isGenTau = false;
    for ( std::vector<int>::const_iterator pdgIdGenTau = pdgIdsGenTau.begin();
	  pdgIdGenTau != pdgIdsGenTau.end(); ++pdgIdGenTau ) {
      if ( genParticle->status() == 2 && genParticle->pdgId() == (*pdgIdGenTau) ) isGenTau = true;
    }
    if ( isGenTau ) {
      reco::Candidate::LorentzVector genTauP4 = getVisMomentum(&(*genParticle));
      std::string genTauDecayMode_string = getGenTauDecayMode(&(*genParticle));
//       std::cout<<"1Pi0Pi0 : "<<reco::PFTau::kOneProng0PiZero<<std::endl;
//       std::cout<<"1Pi1Pi0 : "<<reco::PFTau::kOneProng1PiZero<<std::endl;
//       std::cout<<"1Pi2Pi0 : "<<reco::PFTau::kOneProng2PiZero<<std::endl;
//       std::cout<<"3Pi0Pi0 : "<<reco::PFTau::kThreeProng0PiZero<<std::endl;
//       std::cout<<"3Pi1Pi0 : "<<reco::PFTau::kThreeProng1PiZero<<std::endl;
//       std::cout<<"GenDecayMode : "<<getGenTauDecayMode(&(*genParticle))<<std::endl;
      int genTauDecayMode_int = -1;
      if      ( genTauDecayMode_string == "oneProng0Pi0"    ) genTauDecayMode_int = reco::PFTau::kOneProng0PiZero;
      else if ( genTauDecayMode_string == "oneProng1Pi0"    ) genTauDecayMode_int = reco::PFTau::kOneProng1PiZero;
      else if ( genTauDecayMode_string == "oneProng2Pi0"    ) genTauDecayMode_int = reco::PFTau::kOneProng2PiZero;
      else if ( genTauDecayMode_string == "threeProng0Pi0"  ) genTauDecayMode_int = reco::PFTau::kThreeProng0PiZero;
      else if ( genTauDecayMode_string == "threeProng1Pi0"  ) genTauDecayMode_int = reco::PFTau::kThreeProng1PiZero;
      else if ( genTauDecayMode_string == "oneProngOther"   ||
      	  genTauDecayMode_string == "threeProngOther" ||
      	  genTauDecayMode_string == "rare"            ) genTauDecayMode_int = reco::PFTau::kRareDecayMode;
      if ( genTauDecayMode_int != -1 && genTauP4.pt() > minGenVisPt_ ) {
	const pat::Tau* recTau_matched = findMatchingRecTau(*recTaus, genTauP4);
	double genTauDeltaR = ( recTau_matched ) ? deltaR(recTau_matched->p4(), genTauP4) : 9.9;
	bool genTauMatch = (genTauDeltaR < 0.3);
	int genTauDecayMode = genTauDecayMode_int;
	setRecTauValues(recTau_matched, *recVetoElectrons);
	setGenTauMatchValues(genTauMatch, genTauP4, genTauDecayMode, genTauDeltaR);
	setGenElectronMatchValues(false);
	setGenMuonMatchValues(false);
	++numHypotheses;
      }
    }

    bool isGenElectron = false;
    for ( std::vector<int>::const_iterator pdgIdGenElectron = pdgIdsGenElectron.begin();
	  pdgIdGenElectron != pdgIdsGenElectron.end(); ++pdgIdGenElectron ) {
      if ( genParticle->status() == 1 && genParticle->pdgId() == (*pdgIdGenElectron) ) isGenElectron = true;
    }
    if ( isGenElectron && genParticle->pt() > minGenVisPt_ ) {
      reco::Candidate::LorentzVector genElectronP4 = genParticle->p4();
      const pat::Tau* recTau_matched = findMatchingRecTau(*recTaus, genElectronP4);
      double genElectronDeltaR = ( recTau_matched ) ? deltaR(recTau_matched->p4(), genElectronP4) : 9.9;
      bool genElectronMatch = (genElectronDeltaR < 0.3);
      setRecTauValues(recTau_matched, *recVetoElectrons);
      setGenElectronMatchValues(genElectronMatch, genElectronP4, genElectronDeltaR);
      setGenTauMatchValues(false);
      setGenMuonMatchValues(false);
      ++numHypotheses;
    }
  
    bool isGenMuon = false;
    for ( std::vector<int>::const_iterator pdgIdGenMuon = pdgIdsGenMuon.begin();
	  pdgIdGenMuon != pdgIdsGenMuon.end(); ++pdgIdGenMuon ) {
      if ( genParticle->status() == 1 && genParticle->pdgId() == (*pdgIdGenMuon) ) isGenMuon = true;
    }
    if ( isGenMuon && genParticle->pt() > minGenVisPt_ ) {
      reco::Candidate::LorentzVector genMuonP4 = genParticle->p4();
      const pat::Tau* recTau_matched = findMatchingRecTau(*recTaus, genMuonP4);
      double genMuonDeltaR = ( recTau_matched ) ? deltaR(recTau_matched->p4(), genMuonP4) : 9.9;
      bool genMuonMatch = (genMuonDeltaR < 0.3);
      setRecTauValues(recTau_matched, *recVetoElectrons);
      setGenMuonMatchValues(genMuonMatch, genMuonP4, genMuonDeltaR);
      setGenTauMatchValues(false);
      setGenElectronMatchValues(false);
      ++numHypotheses;
    }
      
    if ( numHypotheses > 1 ) 
      edm::LogWarning("PFTauIdEffNtupleProducer2::analyze")
	<< " Matching between reconstructed PFTau and generator level tau-jets, electrons and muons is ambiguous --> skipping !!";
    if ( numHypotheses != 1 ) continue;
    
    setValue("numVertices", vertices->size());
    setValue("evtWeight", evtWeight);

//--- fill all computed quantities into TTree
    assert(ntuple_);
    ntuple_->Fill();
  }
}

void PFTauIdEffNtupleProducer2::addBranch(const std::string& name) 
{
  assert(branches_.count(name) == 0);
  std::string name_and_format = name + "/F";
  ntuple_->Branch(name.c_str(), &branches_[name], name_and_format.c_str());
}

void PFTauIdEffNtupleProducer2::printBranches(std::ostream& stream)
{
  stream << "<PFTauIdEffNtupleProducer2::printBranches>:" << std::endl;
  stream << " registered branches for module = " << moduleLabel_ << std::endl;
  for ( branchMap::const_iterator branch = branches_.begin();
	branch != branches_.end(); ++branch ) {
    stream << " " << branch->first << std::endl;
  }
  stream << std::endl;
}

void PFTauIdEffNtupleProducer2::setValue(const std::string& name, double value) 
{
  if ( verbosity_ ) std::cout << "branch = " << name << ": value = " << value << std::endl;
  branchMap::iterator branch = branches_.find(name);
  if ( branch != branches_.end() ) {
    branch->second = value;
  } else {
    throw cms::Exception("InvalidParameter") 
      << "No branch with name = " << name << " defined !!\n";
  }
}

//
//-------------------------------------------------------------------------------
//

void PFTauIdEffNtupleProducer2::addBranch_EnPxPyPz(const std::string& name) 
{
  addBranch(std::string(name).append("En"));
  addBranch(std::string(name).append("Px"));
  addBranch(std::string(name).append("Py"));
  addBranch(std::string(name).append("Pz"));
  addBranch(std::string(name).append("M"));
  addBranch(std::string(name).append("Eta"));
  addBranch(std::string(name).append("Phi"));
  addBranch(std::string(name).append("Pt"));
}
//
//-------------------------------------------------------------------------------
//

void PFTauIdEffNtupleProducer2::setValue_EnPxPyPz(const std::string& name, const reco::Candidate::LorentzVector& p4)
{
  setValue(std::string(name).append("En"), p4.E());
  setValue(std::string(name).append("Px"), p4.px());
  setValue(std::string(name).append("Py"), p4.py());
  setValue(std::string(name).append("Pz"), p4.pz());
  setValue(std::string(name).append("M"), p4.M());
  setValue(std::string(name).append("Eta"), p4.eta());
  setValue(std::string(name).append("Phi"), p4.phi());
  setValue(std::string(name).append("Pt"), p4.pt());

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PFTauIdEffNtupleProducer2);
