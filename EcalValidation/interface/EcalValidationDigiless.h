#ifndef EcalValidationDigiless_h
#define EcalValidationDigiless_h

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"


// ROOT include
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <map>


// Less than operator for sorting EcalRecHits according to energy.
class ecalRecHitLess : public std::binary_function<EcalRecHit, EcalRecHit, bool>
{
public:
  bool operator()(EcalRecHit x, EcalRecHit y)
  {
    return (x.energy() > y.energy());
  }
};


class EcalValidationDigiless : public edm::EDAnalyzer {
  
      public:
         explicit EcalValidationDigiless(const edm::ParameterSet&);
	 ~EcalValidationDigiless();
  
  
      private:
	 virtual void beginJob() ;
	 virtual void analyze(const edm::Event&, const edm::EventSetup&);
	 virtual void endJob() ;

	 // ----------additional functions-------------------
	 void convxtalid(int & , int &);
	 int diff_neta_s(int,int);
	 int diff_nphi_s(int,int);

      protected:
	 void doPi0Barrel(const CaloGeometry *theCaloGeometry,
			  const CaloTopology *theCaloTopology,
			  edm::Handle<EcalRecHitCollection> recHitsEB);

	 void doPi0Endcap(const CaloGeometry *theCaloGeometry,
			  const CaloTopology *theCaloTopology,
			  edm::Handle<EcalRecHitCollection> recHitsEE);
  

	 // ----------member data ---------------------------
         edm::InputTag PVTag_;
	 edm::InputTag recHitCollection_EB_;
	 edm::InputTag recHitCollection_EE_;
         edm::InputTag redRecHitCollection_EB_;
         edm::InputTag redRecHitCollection_EE_;
         edm::InputTag basicClusterCollection_EB_;
	 edm::InputTag basicClusterCollection_EE_;
	 edm::InputTag superClusterCollection_EB_;
	 edm::InputTag superClusterCollection_EE_;
	 edm::InputTag esRecHitCollection_;
	 edm::InputTag esClusterCollectionX_ ;
	 edm::InputTag esClusterCollectionY_ ;

	 edm::InputTag tracks_ ;
	 edm::InputTag beamSpot_ ;
         edm::InputTag jets_;
	 
	 double ethrEB_;
	 double ethrEE_;
         double gainId_;

	 double scEtThrEB_;
	 double scEtThrEE_;
         
	 std::ofstream noisyChannelsFileEB_cut6;
	 std::ofstream noisyChannelsFileEEP_cut6;
	 std::ofstream noisyChannelsFileEEM_cut6;
	 std::ofstream noisyChannelsFileEB_cut3;
	 std::ofstream noisyChannelsFileEEP_cut3;
	 std::ofstream noisyChannelsFileEEM_cut3;
	 std::ofstream noisyChannelsFileSC;
         FILE *f_noisyChannelsSC;


	 // for Pi0
	 PositionCalc posCalculator_ ;
	 
	 double clusSeedThr_;
	 double clusSeedThr_EE_;
	 int clusEtaSize_;
	 int clusPhiSize_;
	 
	 double seleXtalMinEnergy_;
	 double seleXtalMinEnergy_EE_;
	 
	 bool isMaskEB_;
	 bool isMaskEE_;
	 
	 /// Files with xtals masked
	 std::string maskEBFile_;
	 std::string maskEEFile_;
	 
	 /// Use Reco Flag from RH
	 bool useRecoFlag_;
	 
	 // ... barrel
	 bool isMonEBpi0_;

	 double selePtGamma_;
	 double selePtPi0_;
	 double seleMinvMaxPi0_;
	 double seleMinvMinPi0_;
	 double seleS4S9Gamma_;
	 double selePi0BeltDR_;
	 double selePi0BeltDeta_;
	 double selePi0Iso_;
	 double ptMinForIsolation_;
	 
	 // ... endcap
	 bool isMonEEpi0_;
	 
	 double selePtGamma_EE_;
	 double selePtPi0_EE_;
	 double seleMinvMaxPi0_EE_;
	 double seleMinvMinPi0_EE_;
	 double seleS4S9Gamma_EE_;
	 double selePi0Iso_EE_;
	 double selePi0BeltDR_EE_;
	 double selePi0BeltDeta_EE_;
	 double ptMinForIsolation_EE_;
	 
	 double region1_Pi0_EE_;
	 double selePtGammaPi0_EE_region1_;
	 double selePtPi0_EE_region1_;
	 double region2_Pi0_EE_;
	 double selePtGammaPi0_EE_region2_;
	 double selePtPi0_EE_region2_;
	 double selePtGammaPi0_EE_region3_;
	 double selePtPi0_EE_region3_;



	 // ------------- HISTOGRAMS ------------------------------------

	 int naiveId_;
	 
	 TH1D *h_numberOfEvents;
         TH1D* h_PV_n;
         TH1D* h_PV_cut_n;
         
	 // ReducedRecHits ----------------------------------------------
	 // ... barrel 
         TH1D *h_redRecHits_EB_recoFlag;
	 // ... endcap 
         TH1D *h_redRecHits_EE_recoFlag;
	 // ... all 
         TH1D *h_redRecHits_recoFlag;
	 
	 // RecHits ----------------------------------------------
         
         // ... Utils
         std::map<int,float> sumRecHitEtEB;
         std::map<int,float> sumRecHitEtEEP;
         std::map<int,float> sumRecHitEtCutEEP;
         std::map<int,float> sumRecHitEtEEM;
         std::map<int,float> sumRecHitEtCutEEM;
        
         // ... DataBase noise map
         TH2D* h_DB_noiseMap_EB;
         TH2D* h_DB_noiseMap_EEP;
         TH2D* h_DB_noiseMap_EEM;
         TH2D* h_DB_noiseMap_EB_cut6;
         TH2D* h_DB_noiseMap_EEP_cut6;
         TH2D* h_DB_noiseMap_EEM_cut6;
         TH2D* h_DB_noiseMap_EB_cut5_5;
         TH2D* h_DB_noiseMap_EEP_cut5_5;
         TH2D* h_DB_noiseMap_EEM_cut5_5;
         TH2D* h_DB_noiseMap_EB_cut5;
         TH2D* h_DB_noiseMap_EEP_cut5;
         TH2D* h_DB_noiseMap_EEM_cut5;
         TH2D* h_DB_noiseMap_EB_cut4_5;
         TH2D* h_DB_noiseMap_EEP_cut4_5;
         TH2D* h_DB_noiseMap_EEM_cut4_5;
         TH2D* h_DB_noiseMap_EB_cut4;
         TH2D* h_DB_noiseMap_EEP_cut4;
         TH2D* h_DB_noiseMap_EEM_cut4;
         TH2D* h_DB_noiseMap_EB_cut3_5;
         TH2D* h_DB_noiseMap_EEP_cut3_5;
         TH2D* h_DB_noiseMap_EEM_cut3_5;
         TH2D* h_DB_noiseMap_EB_cut3;
         TH2D* h_DB_noiseMap_EEP_cut3;
         TH2D* h_DB_noiseMap_EEM_cut3;

         // ... DataBase LaserCorr map
         TH2D* h_DB_LaserCorrMap_EB;
         TH2D* h_DB_LaserCorrMap_EEP;
         TH2D* h_DB_LaserCorrMap_EEM;
         
	 // ... barrel 
	 TH1D *h_recHits_EB_size; 
	 TH1D *h_recHits_EB_energy;
         TH1D *h_recHits_EB_recoFlag;
         TH1D *h_recHits_EB_energyMax;
         TH1D *h_recHits_EB_sumEt;
	 TH1D *h_recHits_EB_time;
	 TH1D *h_recHits_EB_Chi2;
	 TH1D *h_recHits_EB_OutOfTimeChi2;
	 TH1D *h_recHits_EB_E1oE4; 
         TH1D *h_recHits_EB_iPhiOccupancy;
         TH1D *h_recHits_EB_iEtaOccupancy;
	 TH2D *h_recHits_EB_occupancy;
	 TH2D *h_recHits_EB_deviation;
         
	 TH1D *h_recHits_EB_energy_spike;

	 //... barrel ( with spike cleaning )
	 TH1D *h_recHits_EB_size_cleaned; 
	 TH1D *h_recHits_EB_energy_cleaned;
	 TH1D *h_recHits_EB_energyMax_cleaned;
	 TH1D *h_recHits_EB_time_cleaned;
	 TH1D *h_recHits_EB_Chi2_cleaned;
	 TH1D *h_recHits_EB_OutOfTimeChi2_cleaned;

	 // ... endcap

	 TH1D *h_recHits_EE_size;
         TH1D *h_recHits_EE_recoFlag;

	 TH1D *h_recHits_EEP_size;
	 TH1D *h_recHits_EEP_energy;
         TH1D *h_recHits_EEP_sumEt; 
         TH1D *h_recHits_EEP_sumEtCut; 
	 TH1D *h_recHits_EEP_energyMax;
	 TH1D *h_recHits_EEP_time;
	 TH1D *h_recHits_EEP_Chi2;
	 TH1D *h_recHits_EEP_OutOfTimeChi2;
	 TH1D *h_recHits_EEP_E1oE4; 
         TH1D *h_recHits_EEP_iXoccupancy;
         TH1D *h_recHits_EEP_iYoccupancy;
	 TH2D *h_recHits_EEP_occupancy;
	 TH2D *h_recHits_EEP_deviation;
         
	 TH1D *h_recHits_EEM_size;
	 TH1D *h_recHits_EEM_energy;
         TH1D *h_recHits_EEM_sumEt;
         TH1D *h_recHits_EEM_sumEtCut; 
	 TH1D *h_recHits_EEM_energyMax;
	 TH1D *h_recHits_EEM_time;
	 TH1D *h_recHits_EEM_Chi2;
	 TH1D *h_recHits_EEM_OutOfTimeChi2;
	 TH1D *h_recHits_EEM_E1oE4; 
         TH1D *h_recHits_EEM_iXoccupancy;
         TH1D *h_recHits_EEM_iYoccupancy;
	 TH2D *h_recHits_EEM_occupancy;
	 TH2D *h_recHits_EEM_deviation;
       
	 // ... All
         TH1D *h_recHits_recoFlag;

         // max E eta/phi distributions
         TH1D *h_recHits_eta;  // all
         TH1D *h_recHits_EB_eta;
         TH1D *h_recHits_EEP_eta;
         TH1D *h_recHits_EEM_eta;

         TH1D *h_recHits_EB_phi;
         TH1D *h_recHits_EE_phi;
         TH1D *h_recHits_EEP_phi;
         TH1D *h_recHits_EEM_phi;
         
         TH1D *h_recHits_eta_cut6;  // all
         TH1D *h_recHits_EB_eta_cut6;
         TH1D *h_recHits_EEP_eta_cut6;
         TH1D *h_recHits_EEM_eta_cut6;

         TH1D *h_recHits_EB_phi_cut6;
         TH1D *h_recHits_EE_phi_cut6;
         TH1D *h_recHits_EEP_phi_cut6;
         TH1D *h_recHits_EEM_phi_cut6;
          
         TH1D *h_recHits_eta_cut5_5;  // all
         TH1D *h_recHits_EB_eta_cut5_5;
         TH1D *h_recHits_EEP_eta_cut5_5;
         TH1D *h_recHits_EEM_eta_cut5_5;

         TH1D *h_recHits_EB_phi_cut5_5;
         TH1D *h_recHits_EE_phi_cut5_5;
         TH1D *h_recHits_EEP_phi_cut5_5;
         TH1D *h_recHits_EEM_phi_cut5_5;
         
         TH1D *h_recHits_eta_cut5;  // all
         TH1D *h_recHits_EB_eta_cut5;
         TH1D *h_recHits_EEP_eta_cut5;
         TH1D *h_recHits_EEM_eta_cut5;

         TH1D *h_recHits_EB_phi_cut5;
         TH1D *h_recHits_EE_phi_cut5;
         TH1D *h_recHits_EEP_phi_cut5;
         TH1D *h_recHits_EEM_phi_cut5;
   
         TH1D *h_recHits_eta_cut4_5;  // all
         TH1D *h_recHits_EB_eta_cut4_5;
         TH1D *h_recHits_EEP_eta_cut4_5;
         TH1D *h_recHits_EEM_eta_cut4_5;

         TH1D *h_recHits_EB_phi_cut4_5;
         TH1D *h_recHits_EE_phi_cut4_5;
         TH1D *h_recHits_EEP_phi_cut4_5;
         TH1D *h_recHits_EEM_phi_cut4_5;

         TH1D *h_recHits_eta_cut4;  // all
         TH1D *h_recHits_EB_eta_cut4;
         TH1D *h_recHits_EEP_eta_cut4;
         TH1D *h_recHits_EEM_eta_cut4;

         TH1D *h_recHits_EB_phi_cut4;
         TH1D *h_recHits_EE_phi_cut4;
         TH1D *h_recHits_EEP_phi_cut4;
         TH1D *h_recHits_EEM_phi_cut4;
   
         TH1D *h_recHits_eta_cut3_5;  // all
         TH1D *h_recHits_EB_eta_cut3_5;
         TH1D *h_recHits_EEP_eta_cut3_5;
         TH1D *h_recHits_EEM_eta_cut3_5;

         TH1D *h_recHits_EB_phi_cut3_5;
         TH1D *h_recHits_EE_phi_cut3_5;
         TH1D *h_recHits_EEP_phi_cut3_5;
         TH1D *h_recHits_EEM_phi_cut3_5;
 
         TH1D *h_recHits_eta_cut3;  // all
         TH1D *h_recHits_EB_eta_cut3;
         TH1D *h_recHits_EEP_eta_cut3;
         TH1D *h_recHits_EEM_eta_cut3;

         TH1D *h_recHits_EB_phi_cut3;
         TH1D *h_recHits_EE_phi_cut3;
         TH1D *h_recHits_EEP_phi_cut3;
         TH1D *h_recHits_EEM_phi_cut3;

         // max Et eta/phi distributions
         TH1D *h_recHits_eta_MaxEt;
         TH1D *h_recHits_EB_phi_MaxEt;
         TH1D *h_recHits_EE_phi_MaxEt;

	 // Basic Clusters ----------------------------------------------
	 
	 // ... barrel
	 TH1D *h_basicClusters_EB_size;
	 TH1D *h_basicClusters_EB_nXtals;
	 TH1D *h_basicClusters_EB_energy;
	 
	 // ... barrel (with spike cleaning)
	 TH1D *h_basicClusters_EB_size_cleaned;
	 TH1D *h_basicClusters_EB_nXtals_cleaned;
	 TH1D *h_basicClusters_EB_energy_cleaned;
         
         // ... barrel (with spike cleaning and track matching)
         TH1D *h_basicClusters_EB_size_cleaned_tkmatched;
         TH1D *h_basicClusters_EB_nXtals_cleaned_tkmatched;
         TH1D *h_basicClusters_EB_energy_cleaned_tkmatched;
         TH1D *h_basicClusters_EB_dr_cleaned_tkmatched;
         // ... associated barrel rec hits
         TH1D *h_basicClusters_recHits_EB_recoFlag;

	 // ... endcap
	 TH1D *h_basicClusters_EEP_size;
	 TH1D *h_basicClusters_EEP_nXtals;
	 TH1D *h_basicClusters_EEP_energy;
	 
	 TH1D *h_basicClusters_EEM_size;
	 TH1D *h_basicClusters_EEM_nXtals;
	 TH1D *h_basicClusters_EEM_energy;
	 
         TH1D *h_basicClusters_EEP_size_tkmatched;
         TH1D *h_basicClusters_EEP_nXtals_tkmatched;
         TH1D *h_basicClusters_EEP_energy_tkmatched;
         TH1D *h_basicClusters_EEP_dr_tkmatched;
	 
         TH1D *h_basicClusters_EEM_size_tkmatched;
         TH1D *h_basicClusters_EEM_nXtals_tkmatched;
         TH1D *h_basicClusters_EEM_energy_tkmatched;
         TH1D *h_basicClusters_EEM_dr_tkmatched;

	 TH1D *h_basicClusters_eta;
	 TH1D *h_basicClusters_EB_eta;
	 TH1D *h_basicClusters_EE_eta;
	 TH1D *h_basicClusters_EB_phi;
	 TH1D *h_basicClusters_EE_phi;
	 
         TH1D *h_basicClusters_eta_tkmatched;
         TH1D *h_basicClusters_EB_eta_tkmatched;
         TH1D *h_basicClusters_EE_eta_tkmatched;
         TH1D *h_basicClusters_EB_phi_tkmatched;
         TH1D *h_basicClusters_EE_phi_tkmatched;
         
         TH2D *h_basicClusters_EEP_occupancy_esmatched;
         TH1D *h_basicClusters_EEP_eta_esmatched;
         TH1D *h_basicClusters_EEP_phi_esmatched;
         TH2D *h_basicClusters_EEM_occupancy_esmatched;
         TH1D *h_basicClusters_EEM_eta_esmatched;
         TH1D *h_basicClusters_EEM_phi_esmatched;
         
         // ... associated endcap rec hits
         TH1D *h_basicClusters_recHits_EE_recoFlag;

         // ... associated all rec hits
         TH1D *h_basicClusters_recHits_recoFlag;

         TProfile2D *h_Jets_EB_emf;
         TProfile2D *h_Jets_EEP_emf;
         TProfile2D *h_Jets_EEM_emf;
	 
         TProfile *h_Jets_EB_emf_eta;
         TProfile *h_Jets_EEP_emf_eta;
         TProfile *h_Jets_EEM_emf_eta;
	 
         TProfile *h_Jets_EB_emf_phi;
         TProfile *h_Jets_EEP_emf_phi;
         TProfile *h_Jets_EEM_emf_phi;

// Super Clusters ----------------------------------------------
	 // ... barrel
	 TH1D *h_superClusters_EB_size;
	 TH1D *h_superClusters_EB_nXtals;
	 TH1D *h_superClusters_EB_nBC;
	 TH1D *h_superClusters_EB_energy;
	 TH1D *h_superClusters_EB_E1oE4;
         TH2D *h_superClusters_EB_occupancy;

	 // ... barrel (with spike cleaning)
	 TH1D *h_superClusters_EB_size_cleaned;
	 TH1D *h_superClusters_EB_nXtals_cleaned;
	 TH1D *h_superClusters_EB_nBC_cleaned;
	 TH1D *h_superClusters_EB_energy_cleaned;
	 TH1D *h_superClusters_EB_rawEnergy_cleaned;
	 TH1D *h_superClusters_EB_rawEt_cleaned;

	 // ... endcap
	 TH1D *h_superClusters_EEP_size;
	 TH1D *h_superClusters_EEP_nXtals;
	 TH1D *h_superClusters_EEP_nBC;
	 TH1D *h_superClusters_EEP_energy;
	 TH1D *h_superClusters_EEP_rawEnergy;
	 TH1D *h_superClusters_EEP_rawEt;
	 TH1D *h_superClusters_EEP_E1oE4; 
         TH2D *h_superClusters_EEP_occupancy;
	 
	 TH1D *h_superClusters_EEM_size;
	 TH1D *h_superClusters_EEM_nXtals;
	 TH1D *h_superClusters_EEM_nBC;
	 TH1D *h_superClusters_EEM_energy;
	 TH1D *h_superClusters_EEM_rawEnergy;
	 TH1D *h_superClusters_EEM_rawEt;
	 TH1D *h_superClusters_EEM_E1oE4; 
         TH2D *h_superClusters_EEM_occupancy;
	 
         TH2D *h_superClusters_occupancyPhiEta;
         
	 TH1D *h_superClusters_eta;
         TH1D *h_superClusters_eta_scCut;
	 TH1D *h_superClusters_EB_eta;
	 TH1D *h_superClusters_EE_eta;
	 TH1D *h_superClusters_EB_phi;
	 TH1D *h_superClusters_EE_phi;
         
         TH1D *h_superClusters_eta_cut6;
	 TH1D *h_superClusters_EB_eta_cut6;
	 TH1D *h_superClusters_EE_eta_cut6;
	 TH1D *h_superClusters_EB_phi_cut6;
	 TH1D *h_superClusters_EE_phi_cut6;

	 TH1D *h_superClusters_eta_cut5_5;
	 TH1D *h_superClusters_EB_eta_cut5_5;
	 TH1D *h_superClusters_EE_eta_cut5_5;
	 TH1D *h_superClusters_EB_phi_cut5_5;
	 TH1D *h_superClusters_EE_phi_cut5_5;

	 TH1D *h_superClusters_eta_cut5;
	 TH1D *h_superClusters_EB_eta_cut5;
	 TH1D *h_superClusters_EE_eta_cut5;
	 TH1D *h_superClusters_EB_phi_cut5;
	 TH1D *h_superClusters_EE_phi_cut5;

	 TH1D *h_superClusters_eta_cut4_5;
	 TH1D *h_superClusters_EB_eta_cut4_5;
	 TH1D *h_superClusters_EE_eta_cut4_5;
	 TH1D *h_superClusters_EB_phi_cut4_5;
	 TH1D *h_superClusters_EE_phi_cut4_5;

	 TH1D *h_superClusters_eta_cut4;
	 TH1D *h_superClusters_EB_eta_cut4;
	 TH1D *h_superClusters_EE_eta_cut4;
	 TH1D *h_superClusters_EB_phi_cut4;
	 TH1D *h_superClusters_EE_phi_cut4;

	 TH1D *h_superClusters_eta_cut3_5;
	 TH1D *h_superClusters_EB_eta_cut3_5;
	 TH1D *h_superClusters_EE_eta_cut3_5;
	 TH1D *h_superClusters_EB_phi_cut3_5;
	 TH1D *h_superClusters_EE_phi_cut3_5;

	 TH1D *h_superClusters_eta_cut3;
	 TH1D *h_superClusters_EB_eta_cut3;
	 TH1D *h_superClusters_EE_eta_cut3;
	 TH1D *h_superClusters_EB_phi_cut3;
	 TH1D *h_superClusters_EE_phi_cut3;
         
         TH2D *h2_superClusters_EB_seedTimeVsEnergy;
         TH2D *h2_superClusters_EE_seedTimeVsEnergy;
	 
	 
	 // PRESHOWER ----------------------------------------------
	 
	 TH1D *h_recHits_ES_size;
	 TH1D *h_recHits_ES_size_F[2];
	 TH1D *h_recHits_ES_size_R[2];


	 TH1D *h_recHits_ES_energy;
	 TH1D *h_recHits_ES_energy_F[2];
	 TH1D *h_recHits_ES_energy_R[2];

	 TH1D *h_recHits_ES_energyMax;
	 TH1D *h_recHits_ES_energyMax_F[2];
	 TH1D *h_recHits_ES_energyMax_R[2];
	
	 TH1D *h_recHits_ES_time;
	 TH1D *h_recHits_ES_time_F[2];
	 TH1D *h_recHits_ES_time_R[2];

	 TH1D *h_esClusters_energy_plane1;
	 TH1D *h_esClusters_energy_plane2;
	 TH1D *h_esClusters_energy_ratio;
	 
	 // Pi0 peak ----------------------------------------------

	 TH1D *h_Pi0_EB_mass;
	 TH1D *h_Pi0_EB_pt1;
	 TH1D *h_Pi0_EB_pt2;
	 TH1D *h_Pi0_EB_pt;
	 TH1D *h_Pi0_EB_eta;
	 TH1D *h_Pi0_EB_phi;

	 TH1D *h_Pi0_EE_mass;
	 TH1D *h_Pi0_EE_pt1;
	 TH1D *h_Pi0_EE_pt2;
	 TH1D *h_Pi0_EE_pt;
	 TH1D *h_Pi0_EE_eta;
	 TH1D *h_Pi0_EE_phi;


};


#endif
