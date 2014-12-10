#ifndef TauAnalysis_Test_PFTauIdEffNtupleProducer2_h  
#define TauAnalysis_Test_PFTauIdEffNtupleProducer2_h

/** \class PFTauIdEffNtupleNtupleProducer2
 *
 * Produce an Ntuple of various quantities useful 
 * to check tau id. efficiencies and e/mu -> tau fake-rates
 *
 * \author Christian Veelken, LLR
 *
 * \version $Revision: 1.3 $
 *
 * $Id: PFTauIdEffNtupleProducer2.h,v 1.3 2012/03/08 10:31:49 veelken Exp $
 *
 */

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include <TTree.h>

#include <map>
#include <string>
#include <vector>
#include <ostream>

class PFTauIdEffNtupleProducer2 : public edm::EDProducer 
{
 public:
  
  PFTauIdEffNtupleProducer2(const edm::ParameterSet&);
  ~PFTauIdEffNtupleProducer2();

  void produce(edm::Event&, const edm::EventSetup&);
  void beginJob();

 private:

  void addBranch(const std::string&);
  void addBranch_EnPxPyPz(const std::string&);

  void printBranches(std::ostream&);

  void setValue(const std::string&, double);
  void setValue_EnPxPyPz(const std::string&, const reco::Candidate::LorentzVector&);

  const pat::Tau* findMatchingRecTau(const pat::TauCollection&, const reco::Candidate::LorentzVector&);
  void setRecTauValues(const pat::Tau*);
  void setGenTauMatchValues(bool, const reco::Candidate::LorentzVector& = reco::Candidate::LorentzVector(0.,0.,0.,0.), int = -1, double = 9.9);
  void setGenElectronMatchValues(bool, const reco::Candidate::LorentzVector& = reco::Candidate::LorentzVector(0.,0.,0.,0.), double = 9.9);
  void setGenMuonMatchValues(bool, const reco::Candidate::LorentzVector& = reco::Candidate::LorentzVector(0.,0.,0.,0.), double = 9.9);
  
  std::string moduleLabel_;

  edm::InputTag srcGenParticles_;
  edm::InputTag srcRecTaus_;
  edm::InputTag srcVertices_;

  typedef std::vector<edm::InputTag> vInputTag;
  vInputTag srcWeights_;

  typedef std::vector<std::string> vstring;
  vstring tauIdDiscriminators_;

  double minGenVisPt_;

  typedef std::map<std::string, Float_t> branchMap; // key = branch name
  branchMap branches_;

  TTree* ntuple_;

  static int verbosity_;
};

#endif


