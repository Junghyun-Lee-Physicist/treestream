#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H
//----------------------------------------------------------------------------
// File:        eventBuffer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Tue Dec 16 02:48:44 2025 by mkanalyzer.py v2.0.3 14-Oct-2020
// Author:      Shakespeare's ghost
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <cassert>
#include "treestream.h"

struct eventBuffer
{
  //--------------------------------------------------------------------------
  // --- Declare variables
  //--------------------------------------------------------------------------
  std::vector<int>	Electron_charge;
  std::vector<int>	Electron_cleanmask;
  std::vector<bool>	Electron_convVeto;
  std::vector<int>	Electron_cutBased;
  std::vector<bool>	Electron_cutBased_HEEP;
  std::vector<float>	Electron_dEscaleDown;
  std::vector<float>	Electron_dEscaleUp;
  std::vector<float>	Electron_dEsigmaDown;
  std::vector<float>	Electron_dEsigmaUp;
  std::vector<float>	Electron_deltaEtaSC;
  std::vector<float>	Electron_dr03EcalRecHitSumEt;
  std::vector<float>	Electron_dr03HcalDepth1TowerSumEt;
  std::vector<float>	Electron_dr03TkSumPt;
  std::vector<float>	Electron_dr03TkSumPtHEEP;
  std::vector<float>	Electron_dxy;
  std::vector<float>	Electron_dxyErr;
  std::vector<float>	Electron_dz;
  std::vector<float>	Electron_dzErr;
  std::vector<float>	Electron_eCorr;
  std::vector<float>	Electron_eInvMinusPInv;
  std::vector<float>	Electron_energyErr;
  std::vector<float>	Electron_eta;
  std::vector<int>	Electron_genPartFlav;
  std::vector<int>	Electron_genPartIdx;
  std::vector<float>	Electron_hoe;
  std::vector<float>	Electron_ip3d;
  std::vector<bool>	Electron_isPFcand;
  std::vector<int>	Electron_jetIdx;
  std::vector<int>	Electron_jetNDauCharged;
  std::vector<float>	Electron_jetPtRelv2;
  std::vector<float>	Electron_jetRelIso;
  std::vector<int>	Electron_lostHits;
  std::vector<float>	Electron_mass;
  std::vector<float>	Electron_miniPFRelIso_all;
  std::vector<float>	Electron_miniPFRelIso_chg;
  std::vector<float>	Electron_mvaFall17V2Iso;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP80;
  std::vector<bool>	Electron_mvaFall17V2Iso_WP90;
  std::vector<bool>	Electron_mvaFall17V2Iso_WPL;
  std::vector<float>	Electron_mvaFall17V2noIso;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP80;
  std::vector<bool>	Electron_mvaFall17V2noIso_WP90;
  std::vector<bool>	Electron_mvaFall17V2noIso_WPL;
  std::vector<float>	Electron_mvaTTH;
  std::vector<int>	Electron_pdgId;
  std::vector<float>	Electron_pfRelIso03_all;
  std::vector<float>	Electron_pfRelIso03_chg;
  std::vector<float>	Electron_phi;
  std::vector<int>	Electron_photonIdx;
  std::vector<float>	Electron_pt;
  std::vector<float>	Electron_r9;
  std::vector<float>	Electron_scEtOverPt;
  std::vector<int>	Electron_seedGain;
  std::vector<float>	Electron_sieie;
  std::vector<float>	Electron_sip3d;
  std::vector<int>	Electron_tightCharge;
  std::vector<int>	Electron_vidNestedWPBitmap;
  std::vector<int>	Electron_vidNestedWPBitmapHEEP;
  std::vector<float>	GenJet_eta;
  std::vector<int>	GenJet_hadronFlavour;
  std::vector<float>	GenJet_mass;
  std::vector<int>	GenJet_partonFlavour;
  std::vector<float>	GenJet_phi;
  std::vector<float>	GenJet_pt;
  std::vector<float>	GenPart_eta;
  std::vector<int>	GenPart_genPartIdxMother;
  std::vector<float>	GenPart_mass;
  std::vector<int>	GenPart_pdgId;
  std::vector<float>	GenPart_phi;
  std::vector<float>	GenPart_pt;
  std::vector<int>	GenPart_status;
  std::vector<int>	GenPart_statusFlags;
  std::vector<float>	Jet_area;
  std::vector<float>	Jet_bRegCorr;
  std::vector<float>	Jet_bRegRes;
  std::vector<float>	Jet_btagCSVV2;
  std::vector<float>	Jet_btagDeepB;
  std::vector<float>	Jet_btagDeepCvB;
  std::vector<float>	Jet_btagDeepCvL;
  std::vector<float>	Jet_btagDeepFlavB;
  std::vector<float>	Jet_btagDeepFlavCvB;
  std::vector<float>	Jet_btagDeepFlavCvL;
  std::vector<float>	Jet_btagDeepFlavQG;
  std::vector<float>	Jet_cRegCorr;
  std::vector<float>	Jet_cRegRes;
  std::vector<float>	Jet_chEmEF;
  std::vector<float>	Jet_chFPV0EF;
  std::vector<float>	Jet_chHEF;
  std::vector<int>	Jet_cleanmask;
  std::vector<int>	Jet_electronIdx1;
  std::vector<int>	Jet_electronIdx2;
  std::vector<float>	Jet_eta;
  std::vector<int>	Jet_genJetIdx;
  std::vector<int>	Jet_hadronFlavour;
  std::vector<int>	Jet_hfadjacentEtaStripsSize;
  std::vector<int>	Jet_hfcentralEtaStripSize;
  std::vector<float>	Jet_hfsigmaEtaEta;
  std::vector<float>	Jet_hfsigmaPhiPhi;
  std::vector<int>	Jet_jetId;
  std::vector<float>	Jet_mass;
  std::vector<float>	Jet_muEF;
  std::vector<int>	Jet_muonIdx1;
  std::vector<int>	Jet_muonIdx2;
  std::vector<float>	Jet_muonSubtrFactor;
  std::vector<int>	Jet_nConstituents;
  std::vector<int>	Jet_nElectrons;
  std::vector<int>	Jet_nMuons;
  std::vector<float>	Jet_neEmEF;
  std::vector<float>	Jet_neHEF;
  std::vector<int>	Jet_partonFlavour;
  std::vector<float>	Jet_phi;
  std::vector<float>	Jet_pt;
  std::vector<int>	Jet_puId;
  std::vector<float>	Jet_puIdDisc;
  std::vector<float>	Jet_qgl;
  std::vector<float>	Jet_rawFactor;
  std::vector<int>	Muon_charge;
  std::vector<int>	Muon_cleanmask;
  std::vector<float>	Muon_dxy;
  std::vector<float>	Muon_dxyErr;
  std::vector<float>	Muon_dxybs;
  std::vector<float>	Muon_dz;
  std::vector<float>	Muon_dzErr;
  std::vector<float>	Muon_eta;
  std::vector<int>	Muon_fsrPhotonIdx;
  std::vector<int>	Muon_genPartFlav;
  std::vector<int>	Muon_genPartIdx;
  std::vector<int>	Muon_highPtId;
  std::vector<bool>	Muon_highPurity;
  std::vector<bool>	Muon_inTimeMuon;
  std::vector<float>	Muon_ip3d;
  std::vector<bool>	Muon_isGlobal;
  std::vector<bool>	Muon_isPFcand;
  std::vector<bool>	Muon_isStandalone;
  std::vector<bool>	Muon_isTracker;
  std::vector<int>	Muon_jetIdx;
  std::vector<int>	Muon_jetNDauCharged;
  std::vector<float>	Muon_jetPtRelv2;
  std::vector<float>	Muon_jetRelIso;
  std::vector<bool>	Muon_looseId;
  std::vector<float>	Muon_mass;
  std::vector<bool>	Muon_mediumId;
  std::vector<bool>	Muon_mediumPromptId;
  std::vector<int>	Muon_miniIsoId;
  std::vector<float>	Muon_miniPFRelIso_all;
  std::vector<float>	Muon_miniPFRelIso_chg;
  std::vector<int>	Muon_multiIsoId;
  std::vector<int>	Muon_mvaId;
  std::vector<float>	Muon_mvaLowPt;
  std::vector<int>	Muon_mvaLowPtId;
  std::vector<float>	Muon_mvaTTH;
  std::vector<int>	Muon_nStations;
  std::vector<int>	Muon_nTrackerLayers;
  std::vector<int>	Muon_pdgId;
  std::vector<int>	Muon_pfIsoId;
  std::vector<float>	Muon_pfRelIso03_all;
  std::vector<float>	Muon_pfRelIso03_chg;
  std::vector<float>	Muon_pfRelIso04_all;
  std::vector<float>	Muon_phi;
  std::vector<float>	Muon_pt;
  std::vector<float>	Muon_ptErr;
  std::vector<int>	Muon_puppiIsoId;
  std::vector<float>	Muon_segmentComp;
  std::vector<float>	Muon_sip3d;
  std::vector<bool>	Muon_softId;
  std::vector<float>	Muon_softMva;
  std::vector<bool>	Muon_softMvaId;
  std::vector<int>	Muon_tightCharge;
  std::vector<bool>	Muon_tightId;
  std::vector<int>	Muon_tkIsoId;
  std::vector<float>	Muon_tkRelIso;
  std::vector<bool>	Muon_triggerIdLoose;
  std::vector<float>	Muon_tunepRelPt;
  std::vector<float>	OtherPV_z;
  std::vector<float>	PSWeight;

  int	nGenPart;
  int	nGenJet;
  int	nOtherPV;
  int	nMuon;
  int	nPSWeight;
  int	nElectron;
  int	nJet;

  bool	Flag_BadChargedCandidateFilter;
  bool	Flag_BadChargedCandidateSummer16Filter;
  bool	Flag_BadPFMuonDzFilter;
  bool	Flag_BadPFMuonFilter;
  bool	Flag_BadPFMuonSummer16Filter;
  bool	Flag_CSCTightHalo2015Filter;
  bool	Flag_CSCTightHaloFilter;
  bool	Flag_CSCTightHaloTrkMuUnvetoFilter;
  bool	Flag_EcalDeadCellBoundaryEnergyFilter;
  bool	Flag_EcalDeadCellTriggerPrimitiveFilter;
  bool	Flag_HBHENoiseFilter;
  bool	Flag_HBHENoiseIsoFilter;
  bool	Flag_HcalStripHaloFilter;
  bool	Flag_METFilters;
  bool	Flag_chargedHadronTrackResolutionFilter;
  bool	Flag_ecalBadCalibFilter;
  bool	Flag_ecalLaserCorrFilter;
  bool	Flag_eeBadScFilter;
  bool	Flag_globalSuperTightHalo2016Filter;
  bool	Flag_globalTightHalo2016Filter;
  bool	Flag_goodVertices;
  bool	Flag_hcalLaserEventFilter;
  bool	Flag_hfNoisyHitsFilter;
  bool	Flag_muonBadTrackFilter;
  bool	Flag_trkPOGFilters;
  bool	Flag_trkPOG_logErrorTooManyClusters;
  bool	Flag_trkPOG_manystripclus53X;
  bool	Flag_trkPOG_toomanystripclus53X;
  float	GenVtx_t0;
  float	GenVtx_x;
  float	GenVtx_y;
  float	GenVtx_z;
  float	Generator_binvar;
  int	Generator_id1;
  int	Generator_id2;
  float	Generator_scalePDF;
  float	Generator_weight;
  float	Generator_x1;
  float	Generator_x2;
  float	Generator_xpdf1;
  float	Generator_xpdf2;
  bool	HLT_IsoMu20;
  bool	HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1;
  bool	HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1;
  bool	HLT_IsoMu24;
  bool	HLT_IsoMu24_eta2p1;
  bool	HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1;
  bool	HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1;
  bool	HLT_IsoMu27;
  bool	HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1;
  bool	HLT_IsoMu30;
  bool	HLT_PFHT1050;
  bool	HLT_PFHT180;
  bool	HLT_PFHT250;
  bool	HLT_PFHT300PT30_QuadPFJet_75_60_45_40;
  bool	HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0;
  bool	HLT_PFHT350;
  bool	HLT_PFHT350MinPFJet15;
  bool	HLT_PFHT370;
  bool	HLT_PFHT380_SixPFJet32;
  bool	HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2;
  bool	HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
  bool	HLT_PFHT430;
  bool	HLT_PFHT430_SixPFJet40;
  bool	HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
  bool	HLT_PFHT500_PFMET100_PFMHT100_IDTight;
  bool	HLT_PFHT500_PFMET110_PFMHT110_IDTight;
  bool	HLT_PFHT510;
  bool	HLT_PFHT590;
  bool	HLT_PFHT680;
  bool	HLT_PFHT700_PFMET85_PFMHT85_IDTight;
  bool	HLT_PFHT700_PFMET95_PFMHT95_IDTight;
  bool	HLT_PFHT780;
  bool	HLT_PFHT800_PFMET75_PFMHT75_IDTight;
  bool	HLT_PFHT800_PFMET85_PFMHT85_IDTight;
  bool	HLT_PFHT890;
  bool	HLTriggerFinalPath;
  bool	HLTriggerFirstPath;
  float	PV_chi2;
  float	PV_ndof;
  int	PV_npvs;
  int	PV_npvsGood;
  float	PV_score;
  float	PV_x;
  float	PV_y;
  float	PV_z;
  float	Pileup_gpudensity;
  int	Pileup_nPU;
  float	Pileup_nTrueInt;
  float	Pileup_pudensity;
  int	Pileup_sumEOOT;
  int	Pileup_sumLOOT;
  float	btagWeight_CSVV2;
  float	btagWeight_DeepCSVB;
  long	event;
  int	genTtbarId;
  float	genWeight;
  unsigned int	luminosityBlock;
  unsigned int	run;

  //--------------------------------------------------------------------------
  // --- Structs can be filled by calling fill(), or individual fill
  // --- methods, e.g., fillElectrons()
  // --- after the call to read(...)
  //----------- --------------------------------------------------------------
  struct Electron_s
  {
    int	charge;
    int	cleanmask;
    bool	convVeto;
    int	cutBased;
    bool	cutBased_HEEP;
    float	dEscaleDown;
    float	dEscaleUp;
    float	dEsigmaDown;
    float	dEsigmaUp;
    float	deltaEtaSC;
    float	dr03EcalRecHitSumEt;
    float	dr03HcalDepth1TowerSumEt;
    float	dr03TkSumPt;
    float	dr03TkSumPtHEEP;
    float	dxy;
    float	dxyErr;
    float	dz;
    float	dzErr;
    float	eCorr;
    float	eInvMinusPInv;
    float	energyErr;
    float	eta;
    int	genPartFlav;
    int	genPartIdx;
    float	hoe;
    float	ip3d;
    bool	isPFcand;
    int	jetIdx;
    int	jetNDauCharged;
    float	jetPtRelv2;
    float	jetRelIso;
    int	lostHits;
    float	mass;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    float	mvaFall17V2Iso;
    bool	mvaFall17V2Iso_WP80;
    bool	mvaFall17V2Iso_WP90;
    bool	mvaFall17V2Iso_WPL;
    float	mvaFall17V2noIso;
    bool	mvaFall17V2noIso_WP80;
    bool	mvaFall17V2noIso_WP90;
    bool	mvaFall17V2noIso_WPL;
    float	mvaTTH;
    int	pdgId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	phi;
    int	photonIdx;
    float	pt;
    float	r9;
    float	scEtOverPt;
    int	seedGain;
    float	sieie;
    float	sip3d;
    int	tightCharge;
    int	vidNestedWPBitmap;
    int	vidNestedWPBitmapHEEP;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Electron" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "convVeto", ( double)convVeto); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased", ( double)cutBased); os << r;
      sprintf(r, "  %-32s: %f\n", "cutBased_HEEP", ( double)cutBased_HEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleDown", ( double)dEscaleDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEscaleUp", ( double)dEscaleUp); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaDown", ( double)dEsigmaDown); os << r;
      sprintf(r, "  %-32s: %f\n", "dEsigmaUp", ( double)dEsigmaUp); os << r;
      sprintf(r, "  %-32s: %f\n", "deltaEtaSC", ( double)deltaEtaSC); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03EcalRecHitSumEt", ( double)dr03EcalRecHitSumEt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03HcalDepth1TowerSumEt", ( double)dr03HcalDepth1TowerSumEt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03TkSumPt", ( double)dr03TkSumPt); os << r;
      sprintf(r, "  %-32s: %f\n", "dr03TkSumPtHEEP", ( double)dr03TkSumPtHEEP); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dxyErr", ( double)dxyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "dzErr", ( double)dzErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eCorr", ( double)eCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "eInvMinusPInv", ( double)eInvMinusPInv); os << r;
      sprintf(r, "  %-32s: %f\n", "energyErr", ( double)energyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hoe", ( double)hoe); os << r;
      sprintf(r, "  %-32s: %f\n", "ip3d", ( double)ip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "jetNDauCharged", ( double)jetNDauCharged); os << r;
      sprintf(r, "  %-32s: %f\n", "jetPtRelv2", ( double)jetPtRelv2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetRelIso", ( double)jetRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "lostHits", ( double)lostHits); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso", ( double)mvaFall17V2Iso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP80", ( double)mvaFall17V2Iso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WP90", ( double)mvaFall17V2Iso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2Iso_WPL", ( double)mvaFall17V2Iso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso", ( double)mvaFall17V2noIso); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP80", ( double)mvaFall17V2noIso_WP80); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WP90", ( double)mvaFall17V2noIso_WP90); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaFall17V2noIso_WPL", ( double)mvaFall17V2noIso_WPL); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaTTH", ( double)mvaTTH); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "photonIdx", ( double)photonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "r9", ( double)r9); os << r;
      sprintf(r, "  %-32s: %f\n", "scEtOverPt", ( double)scEtOverPt); os << r;
      sprintf(r, "  %-32s: %f\n", "seedGain", ( double)seedGain); os << r;
      sprintf(r, "  %-32s: %f\n", "sieie", ( double)sieie); os << r;
      sprintf(r, "  %-32s: %f\n", "sip3d", ( double)sip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "tightCharge", ( double)tightCharge); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmap", ( double)vidNestedWPBitmap); os << r;
      sprintf(r, "  %-32s: %f\n", "vidNestedWPBitmapHEEP", ( double)vidNestedWPBitmapHEEP); os << r;
      return os;
    }
  };

  struct GenJet_s
  {
    float	eta;
    int	hadronFlavour;
    float	mass;
    int	partonFlavour;
    float	phi;
    float	pt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenJet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "partonFlavour", ( double)partonFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      return os;
    }
  };

  struct GenPart_s
  {
    float	eta;
    int	genPartIdxMother;
    float	mass;
    int	pdgId;
    float	phi;
    float	pt;
    int	status;
    int	statusFlags;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "GenPart" << std::endl;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdxMother", ( double)genPartIdxMother); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "status", ( double)status); os << r;
      sprintf(r, "  %-32s: %f\n", "statusFlags", ( double)statusFlags); os << r;
      return os;
    }
  };

  struct Jet_s
  {
    float	area;
    float	bRegCorr;
    float	bRegRes;
    float	btagCSVV2;
    float	btagDeepB;
    float	btagDeepCvB;
    float	btagDeepCvL;
    float	btagDeepFlavB;
    float	btagDeepFlavCvB;
    float	btagDeepFlavCvL;
    float	btagDeepFlavQG;
    float	cRegCorr;
    float	cRegRes;
    float	chEmEF;
    float	chFPV0EF;
    float	chHEF;
    int	cleanmask;
    int	electronIdx1;
    int	electronIdx2;
    float	eta;
    int	genJetIdx;
    int	hadronFlavour;
    int	hfadjacentEtaStripsSize;
    int	hfcentralEtaStripSize;
    float	hfsigmaEtaEta;
    float	hfsigmaPhiPhi;
    int	jetId;
    float	mass;
    float	muEF;
    int	muonIdx1;
    int	muonIdx2;
    float	muonSubtrFactor;
    int	nConstituents;
    int	nElectrons;
    int	nMuons;
    float	neEmEF;
    float	neHEF;
    int	partonFlavour;
    float	phi;
    float	pt;
    int	puId;
    float	puIdDisc;
    float	qgl;
    float	rawFactor;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Jet" << std::endl;
      sprintf(r, "  %-32s: %f\n", "area", ( double)area); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegCorr", ( double)bRegCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "bRegRes", ( double)bRegRes); os << r;
      sprintf(r, "  %-32s: %f\n", "btagCSVV2", ( double)btagCSVV2); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepB", ( double)btagDeepB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepCvB", ( double)btagDeepCvB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepCvL", ( double)btagDeepCvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavB", ( double)btagDeepFlavB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavCvB", ( double)btagDeepFlavCvB); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavCvL", ( double)btagDeepFlavCvL); os << r;
      sprintf(r, "  %-32s: %f\n", "btagDeepFlavQG", ( double)btagDeepFlavQG); os << r;
      sprintf(r, "  %-32s: %f\n", "cRegCorr", ( double)cRegCorr); os << r;
      sprintf(r, "  %-32s: %f\n", "cRegRes", ( double)cRegRes); os << r;
      sprintf(r, "  %-32s: %f\n", "chEmEF", ( double)chEmEF); os << r;
      sprintf(r, "  %-32s: %f\n", "chFPV0EF", ( double)chFPV0EF); os << r;
      sprintf(r, "  %-32s: %f\n", "chHEF", ( double)chHEF); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx1", ( double)electronIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "electronIdx2", ( double)electronIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "genJetIdx", ( double)genJetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "hadronFlavour", ( double)hadronFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "hfadjacentEtaStripsSize", ( double)hfadjacentEtaStripsSize); os << r;
      sprintf(r, "  %-32s: %f\n", "hfcentralEtaStripSize", ( double)hfcentralEtaStripSize); os << r;
      sprintf(r, "  %-32s: %f\n", "hfsigmaEtaEta", ( double)hfsigmaEtaEta); os << r;
      sprintf(r, "  %-32s: %f\n", "hfsigmaPhiPhi", ( double)hfsigmaPhiPhi); os << r;
      sprintf(r, "  %-32s: %f\n", "jetId", ( double)jetId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "muEF", ( double)muEF); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx1", ( double)muonIdx1); os << r;
      sprintf(r, "  %-32s: %f\n", "muonIdx2", ( double)muonIdx2); os << r;
      sprintf(r, "  %-32s: %f\n", "muonSubtrFactor", ( double)muonSubtrFactor); os << r;
      sprintf(r, "  %-32s: %f\n", "nConstituents", ( double)nConstituents); os << r;
      sprintf(r, "  %-32s: %f\n", "nElectrons", ( double)nElectrons); os << r;
      sprintf(r, "  %-32s: %f\n", "nMuons", ( double)nMuons); os << r;
      sprintf(r, "  %-32s: %f\n", "neEmEF", ( double)neEmEF); os << r;
      sprintf(r, "  %-32s: %f\n", "neHEF", ( double)neHEF); os << r;
      sprintf(r, "  %-32s: %f\n", "partonFlavour", ( double)partonFlavour); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "puId", ( double)puId); os << r;
      sprintf(r, "  %-32s: %f\n", "puIdDisc", ( double)puIdDisc); os << r;
      sprintf(r, "  %-32s: %f\n", "qgl", ( double)qgl); os << r;
      sprintf(r, "  %-32s: %f\n", "rawFactor", ( double)rawFactor); os << r;
      return os;
    }
  };

  struct Muon_s
  {
    int	charge;
    int	cleanmask;
    float	dxy;
    float	dxyErr;
    float	dxybs;
    float	dz;
    float	dzErr;
    float	eta;
    int	fsrPhotonIdx;
    int	genPartFlav;
    int	genPartIdx;
    int	highPtId;
    bool	highPurity;
    bool	inTimeMuon;
    float	ip3d;
    bool	isGlobal;
    bool	isPFcand;
    bool	isStandalone;
    bool	isTracker;
    int	jetIdx;
    int	jetNDauCharged;
    float	jetPtRelv2;
    float	jetRelIso;
    bool	looseId;
    float	mass;
    bool	mediumId;
    bool	mediumPromptId;
    int	miniIsoId;
    float	miniPFRelIso_all;
    float	miniPFRelIso_chg;
    int	multiIsoId;
    int	mvaId;
    float	mvaLowPt;
    int	mvaLowPtId;
    float	mvaTTH;
    int	nStations;
    int	nTrackerLayers;
    int	pdgId;
    int	pfIsoId;
    float	pfRelIso03_all;
    float	pfRelIso03_chg;
    float	pfRelIso04_all;
    float	phi;
    float	pt;
    float	ptErr;
    int	puppiIsoId;
    float	segmentComp;
    float	sip3d;
    bool	softId;
    float	softMva;
    bool	softMvaId;
    int	tightCharge;
    bool	tightId;
    int	tkIsoId;
    float	tkRelIso;
    bool	triggerIdLoose;
    float	tunepRelPt;

    std::ostream& operator<<(std::ostream& os)
    {
      char r[1024];
      os << "Muon" << std::endl;
      sprintf(r, "  %-32s: %f\n", "charge", ( double)charge); os << r;
      sprintf(r, "  %-32s: %f\n", "cleanmask", ( double)cleanmask); os << r;
      sprintf(r, "  %-32s: %f\n", "dxy", ( double)dxy); os << r;
      sprintf(r, "  %-32s: %f\n", "dxyErr", ( double)dxyErr); os << r;
      sprintf(r, "  %-32s: %f\n", "dxybs", ( double)dxybs); os << r;
      sprintf(r, "  %-32s: %f\n", "dz", ( double)dz); os << r;
      sprintf(r, "  %-32s: %f\n", "dzErr", ( double)dzErr); os << r;
      sprintf(r, "  %-32s: %f\n", "eta", ( double)eta); os << r;
      sprintf(r, "  %-32s: %f\n", "fsrPhotonIdx", ( double)fsrPhotonIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartFlav", ( double)genPartFlav); os << r;
      sprintf(r, "  %-32s: %f\n", "genPartIdx", ( double)genPartIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "highPtId", ( double)highPtId); os << r;
      sprintf(r, "  %-32s: %f\n", "highPurity", ( double)highPurity); os << r;
      sprintf(r, "  %-32s: %f\n", "inTimeMuon", ( double)inTimeMuon); os << r;
      sprintf(r, "  %-32s: %f\n", "ip3d", ( double)ip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "isGlobal", ( double)isGlobal); os << r;
      sprintf(r, "  %-32s: %f\n", "isPFcand", ( double)isPFcand); os << r;
      sprintf(r, "  %-32s: %f\n", "isStandalone", ( double)isStandalone); os << r;
      sprintf(r, "  %-32s: %f\n", "isTracker", ( double)isTracker); os << r;
      sprintf(r, "  %-32s: %f\n", "jetIdx", ( double)jetIdx); os << r;
      sprintf(r, "  %-32s: %f\n", "jetNDauCharged", ( double)jetNDauCharged); os << r;
      sprintf(r, "  %-32s: %f\n", "jetPtRelv2", ( double)jetPtRelv2); os << r;
      sprintf(r, "  %-32s: %f\n", "jetRelIso", ( double)jetRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "looseId", ( double)looseId); os << r;
      sprintf(r, "  %-32s: %f\n", "mass", ( double)mass); os << r;
      sprintf(r, "  %-32s: %f\n", "mediumId", ( double)mediumId); os << r;
      sprintf(r, "  %-32s: %f\n", "mediumPromptId", ( double)mediumPromptId); os << r;
      sprintf(r, "  %-32s: %f\n", "miniIsoId", ( double)miniIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_all", ( double)miniPFRelIso_all); os << r;
      sprintf(r, "  %-32s: %f\n", "miniPFRelIso_chg", ( double)miniPFRelIso_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "multiIsoId", ( double)multiIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaId", ( double)mvaId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaLowPt", ( double)mvaLowPt); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaLowPtId", ( double)mvaLowPtId); os << r;
      sprintf(r, "  %-32s: %f\n", "mvaTTH", ( double)mvaTTH); os << r;
      sprintf(r, "  %-32s: %f\n", "nStations", ( double)nStations); os << r;
      sprintf(r, "  %-32s: %f\n", "nTrackerLayers", ( double)nTrackerLayers); os << r;
      sprintf(r, "  %-32s: %f\n", "pdgId", ( double)pdgId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfIsoId", ( double)pfIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_all", ( double)pfRelIso03_all); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso03_chg", ( double)pfRelIso03_chg); os << r;
      sprintf(r, "  %-32s: %f\n", "pfRelIso04_all", ( double)pfRelIso04_all); os << r;
      sprintf(r, "  %-32s: %f\n", "phi", ( double)phi); os << r;
      sprintf(r, "  %-32s: %f\n", "pt", ( double)pt); os << r;
      sprintf(r, "  %-32s: %f\n", "ptErr", ( double)ptErr); os << r;
      sprintf(r, "  %-32s: %f\n", "puppiIsoId", ( double)puppiIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "segmentComp", ( double)segmentComp); os << r;
      sprintf(r, "  %-32s: %f\n", "sip3d", ( double)sip3d); os << r;
      sprintf(r, "  %-32s: %f\n", "softId", ( double)softId); os << r;
      sprintf(r, "  %-32s: %f\n", "softMva", ( double)softMva); os << r;
      sprintf(r, "  %-32s: %f\n", "softMvaId", ( double)softMvaId); os << r;
      sprintf(r, "  %-32s: %f\n", "tightCharge", ( double)tightCharge); os << r;
      sprintf(r, "  %-32s: %f\n", "tightId", ( double)tightId); os << r;
      sprintf(r, "  %-32s: %f\n", "tkIsoId", ( double)tkIsoId); os << r;
      sprintf(r, "  %-32s: %f\n", "tkRelIso", ( double)tkRelIso); os << r;
      sprintf(r, "  %-32s: %f\n", "triggerIdLoose", ( double)triggerIdLoose); os << r;
      sprintf(r, "  %-32s: %f\n", "tunepRelPt", ( double)tunepRelPt); os << r;
      return os;
    }
  };


  void fillElectrons()
  {
    Electron.resize(Electron_charge.size());
    for(unsigned int i=0; i < Electron.size(); ++i)
      {
        Electron[i].charge	= Electron_charge[i];
        Electron[i].cleanmask	= Electron_cleanmask[i];
        Electron[i].convVeto	= (bool)Electron_convVeto[i];
        Electron[i].cutBased	= Electron_cutBased[i];
        Electron[i].cutBased_HEEP	= (bool)Electron_cutBased_HEEP[i];
        Electron[i].dEscaleDown	= Electron_dEscaleDown[i];
        Electron[i].dEscaleUp	= Electron_dEscaleUp[i];
        Electron[i].dEsigmaDown	= Electron_dEsigmaDown[i];
        Electron[i].dEsigmaUp	= Electron_dEsigmaUp[i];
        Electron[i].deltaEtaSC	= Electron_deltaEtaSC[i];
        Electron[i].dr03EcalRecHitSumEt	= Electron_dr03EcalRecHitSumEt[i];
        Electron[i].dr03HcalDepth1TowerSumEt	= Electron_dr03HcalDepth1TowerSumEt[i];
        Electron[i].dr03TkSumPt	= Electron_dr03TkSumPt[i];
        Electron[i].dr03TkSumPtHEEP	= Electron_dr03TkSumPtHEEP[i];
        Electron[i].dxy	= Electron_dxy[i];
        Electron[i].dxyErr	= Electron_dxyErr[i];
        Electron[i].dz	= Electron_dz[i];
        Electron[i].dzErr	= Electron_dzErr[i];
        Electron[i].eCorr	= Electron_eCorr[i];
        Electron[i].eInvMinusPInv	= Electron_eInvMinusPInv[i];
        Electron[i].energyErr	= Electron_energyErr[i];
        Electron[i].eta	= Electron_eta[i];
        Electron[i].genPartFlav	= Electron_genPartFlav[i];
        Electron[i].genPartIdx	= Electron_genPartIdx[i];
        Electron[i].hoe	= Electron_hoe[i];
        Electron[i].ip3d	= Electron_ip3d[i];
        Electron[i].isPFcand	= (bool)Electron_isPFcand[i];
        Electron[i].jetIdx	= Electron_jetIdx[i];
        Electron[i].jetNDauCharged	= Electron_jetNDauCharged[i];
        Electron[i].jetPtRelv2	= Electron_jetPtRelv2[i];
        Electron[i].jetRelIso	= Electron_jetRelIso[i];
        Electron[i].lostHits	= Electron_lostHits[i];
        Electron[i].mass	= Electron_mass[i];
        Electron[i].miniPFRelIso_all	= Electron_miniPFRelIso_all[i];
        Electron[i].miniPFRelIso_chg	= Electron_miniPFRelIso_chg[i];
        Electron[i].mvaFall17V2Iso	= Electron_mvaFall17V2Iso[i];
        Electron[i].mvaFall17V2Iso_WP80	= (bool)Electron_mvaFall17V2Iso_WP80[i];
        Electron[i].mvaFall17V2Iso_WP90	= (bool)Electron_mvaFall17V2Iso_WP90[i];
        Electron[i].mvaFall17V2Iso_WPL	= (bool)Electron_mvaFall17V2Iso_WPL[i];
        Electron[i].mvaFall17V2noIso	= Electron_mvaFall17V2noIso[i];
        Electron[i].mvaFall17V2noIso_WP80	= (bool)Electron_mvaFall17V2noIso_WP80[i];
        Electron[i].mvaFall17V2noIso_WP90	= (bool)Electron_mvaFall17V2noIso_WP90[i];
        Electron[i].mvaFall17V2noIso_WPL	= (bool)Electron_mvaFall17V2noIso_WPL[i];
        Electron[i].mvaTTH	= Electron_mvaTTH[i];
        Electron[i].pdgId	= Electron_pdgId[i];
        Electron[i].pfRelIso03_all	= Electron_pfRelIso03_all[i];
        Electron[i].pfRelIso03_chg	= Electron_pfRelIso03_chg[i];
        Electron[i].phi	= Electron_phi[i];
        Electron[i].photonIdx	= Electron_photonIdx[i];
        Electron[i].pt	= Electron_pt[i];
        Electron[i].r9	= Electron_r9[i];
        Electron[i].scEtOverPt	= Electron_scEtOverPt[i];
        Electron[i].seedGain	= Electron_seedGain[i];
        Electron[i].sieie	= Electron_sieie[i];
        Electron[i].sip3d	= Electron_sip3d[i];
        Electron[i].tightCharge	= Electron_tightCharge[i];
        Electron[i].vidNestedWPBitmap	= Electron_vidNestedWPBitmap[i];
        Electron[i].vidNestedWPBitmapHEEP	= Electron_vidNestedWPBitmapHEEP[i];
      }
  }

  void fillGenJets()
  {
    GenJet.resize(GenJet_eta.size());
    for(unsigned int i=0; i < GenJet.size(); ++i)
      {
        GenJet[i].eta	= GenJet_eta[i];
        GenJet[i].hadronFlavour	= GenJet_hadronFlavour[i];
        GenJet[i].mass	= GenJet_mass[i];
        GenJet[i].partonFlavour	= GenJet_partonFlavour[i];
        GenJet[i].phi	= GenJet_phi[i];
        GenJet[i].pt	= GenJet_pt[i];
      }
  }

  void fillGenParts()
  {
    GenPart.resize(GenPart_eta.size());
    for(unsigned int i=0; i < GenPart.size(); ++i)
      {
        GenPart[i].eta	= GenPart_eta[i];
        GenPart[i].genPartIdxMother	= GenPart_genPartIdxMother[i];
        GenPart[i].mass	= GenPart_mass[i];
        GenPart[i].pdgId	= GenPart_pdgId[i];
        GenPart[i].phi	= GenPart_phi[i];
        GenPart[i].pt	= GenPart_pt[i];
        GenPart[i].status	= GenPart_status[i];
        GenPart[i].statusFlags	= GenPart_statusFlags[i];
      }
  }

  void fillJets()
  {
    Jet.resize(Jet_area.size());
    for(unsigned int i=0; i < Jet.size(); ++i)
      {
        Jet[i].area	= Jet_area[i];
        Jet[i].bRegCorr	= Jet_bRegCorr[i];
        Jet[i].bRegRes	= Jet_bRegRes[i];
        Jet[i].btagCSVV2	= Jet_btagCSVV2[i];
        Jet[i].btagDeepB	= Jet_btagDeepB[i];
        Jet[i].btagDeepCvB	= Jet_btagDeepCvB[i];
        Jet[i].btagDeepCvL	= Jet_btagDeepCvL[i];
        Jet[i].btagDeepFlavB	= Jet_btagDeepFlavB[i];
        Jet[i].btagDeepFlavCvB	= Jet_btagDeepFlavCvB[i];
        Jet[i].btagDeepFlavCvL	= Jet_btagDeepFlavCvL[i];
        Jet[i].btagDeepFlavQG	= Jet_btagDeepFlavQG[i];
        Jet[i].cRegCorr	= Jet_cRegCorr[i];
        Jet[i].cRegRes	= Jet_cRegRes[i];
        Jet[i].chEmEF	= Jet_chEmEF[i];
        Jet[i].chFPV0EF	= Jet_chFPV0EF[i];
        Jet[i].chHEF	= Jet_chHEF[i];
        Jet[i].cleanmask	= Jet_cleanmask[i];
        Jet[i].electronIdx1	= Jet_electronIdx1[i];
        Jet[i].electronIdx2	= Jet_electronIdx2[i];
        Jet[i].eta	= Jet_eta[i];
        Jet[i].genJetIdx	= Jet_genJetIdx[i];
        Jet[i].hadronFlavour	= Jet_hadronFlavour[i];
        Jet[i].hfadjacentEtaStripsSize	= Jet_hfadjacentEtaStripsSize[i];
        Jet[i].hfcentralEtaStripSize	= Jet_hfcentralEtaStripSize[i];
        Jet[i].hfsigmaEtaEta	= Jet_hfsigmaEtaEta[i];
        Jet[i].hfsigmaPhiPhi	= Jet_hfsigmaPhiPhi[i];
        Jet[i].jetId	= Jet_jetId[i];
        Jet[i].mass	= Jet_mass[i];
        Jet[i].muEF	= Jet_muEF[i];
        Jet[i].muonIdx1	= Jet_muonIdx1[i];
        Jet[i].muonIdx2	= Jet_muonIdx2[i];
        Jet[i].muonSubtrFactor	= Jet_muonSubtrFactor[i];
        Jet[i].nConstituents	= Jet_nConstituents[i];
        Jet[i].nElectrons	= Jet_nElectrons[i];
        Jet[i].nMuons	= Jet_nMuons[i];
        Jet[i].neEmEF	= Jet_neEmEF[i];
        Jet[i].neHEF	= Jet_neHEF[i];
        Jet[i].partonFlavour	= Jet_partonFlavour[i];
        Jet[i].phi	= Jet_phi[i];
        Jet[i].pt	= Jet_pt[i];
        Jet[i].puId	= Jet_puId[i];
        Jet[i].puIdDisc	= Jet_puIdDisc[i];
        Jet[i].qgl	= Jet_qgl[i];
        Jet[i].rawFactor	= Jet_rawFactor[i];
      }
  }

  void fillMuons()
  {
    Muon.resize(Muon_charge.size());
    for(unsigned int i=0; i < Muon.size(); ++i)
      {
        Muon[i].charge	= Muon_charge[i];
        Muon[i].cleanmask	= Muon_cleanmask[i];
        Muon[i].dxy	= Muon_dxy[i];
        Muon[i].dxyErr	= Muon_dxyErr[i];
        Muon[i].dxybs	= Muon_dxybs[i];
        Muon[i].dz	= Muon_dz[i];
        Muon[i].dzErr	= Muon_dzErr[i];
        Muon[i].eta	= Muon_eta[i];
        Muon[i].fsrPhotonIdx	= Muon_fsrPhotonIdx[i];
        Muon[i].genPartFlav	= Muon_genPartFlav[i];
        Muon[i].genPartIdx	= Muon_genPartIdx[i];
        Muon[i].highPtId	= Muon_highPtId[i];
        Muon[i].highPurity	= (bool)Muon_highPurity[i];
        Muon[i].inTimeMuon	= (bool)Muon_inTimeMuon[i];
        Muon[i].ip3d	= Muon_ip3d[i];
        Muon[i].isGlobal	= (bool)Muon_isGlobal[i];
        Muon[i].isPFcand	= (bool)Muon_isPFcand[i];
        Muon[i].isStandalone	= (bool)Muon_isStandalone[i];
        Muon[i].isTracker	= (bool)Muon_isTracker[i];
        Muon[i].jetIdx	= Muon_jetIdx[i];
        Muon[i].jetNDauCharged	= Muon_jetNDauCharged[i];
        Muon[i].jetPtRelv2	= Muon_jetPtRelv2[i];
        Muon[i].jetRelIso	= Muon_jetRelIso[i];
        Muon[i].looseId	= (bool)Muon_looseId[i];
        Muon[i].mass	= Muon_mass[i];
        Muon[i].mediumId	= (bool)Muon_mediumId[i];
        Muon[i].mediumPromptId	= (bool)Muon_mediumPromptId[i];
        Muon[i].miniIsoId	= Muon_miniIsoId[i];
        Muon[i].miniPFRelIso_all	= Muon_miniPFRelIso_all[i];
        Muon[i].miniPFRelIso_chg	= Muon_miniPFRelIso_chg[i];
        Muon[i].multiIsoId	= Muon_multiIsoId[i];
        Muon[i].mvaId	= Muon_mvaId[i];
        Muon[i].mvaLowPt	= Muon_mvaLowPt[i];
        Muon[i].mvaLowPtId	= Muon_mvaLowPtId[i];
        Muon[i].mvaTTH	= Muon_mvaTTH[i];
        Muon[i].nStations	= Muon_nStations[i];
        Muon[i].nTrackerLayers	= Muon_nTrackerLayers[i];
        Muon[i].pdgId	= Muon_pdgId[i];
        Muon[i].pfIsoId	= Muon_pfIsoId[i];
        Muon[i].pfRelIso03_all	= Muon_pfRelIso03_all[i];
        Muon[i].pfRelIso03_chg	= Muon_pfRelIso03_chg[i];
        Muon[i].pfRelIso04_all	= Muon_pfRelIso04_all[i];
        Muon[i].phi	= Muon_phi[i];
        Muon[i].pt	= Muon_pt[i];
        Muon[i].ptErr	= Muon_ptErr[i];
        Muon[i].puppiIsoId	= Muon_puppiIsoId[i];
        Muon[i].segmentComp	= Muon_segmentComp[i];
        Muon[i].sip3d	= Muon_sip3d[i];
        Muon[i].softId	= (bool)Muon_softId[i];
        Muon[i].softMva	= Muon_softMva[i];
        Muon[i].softMvaId	= (bool)Muon_softMvaId[i];
        Muon[i].tightCharge	= Muon_tightCharge[i];
        Muon[i].tightId	= (bool)Muon_tightId[i];
        Muon[i].tkIsoId	= Muon_tkIsoId[i];
        Muon[i].tkRelIso	= Muon_tkRelIso[i];
        Muon[i].triggerIdLoose	= (bool)Muon_triggerIdLoose[i];
        Muon[i].tunepRelPt	= Muon_tunepRelPt[i];
      }
  }


  std::vector<eventBuffer::Electron_s> Electron;
  std::vector<eventBuffer::GenJet_s> GenJet;
  std::vector<eventBuffer::GenPart_s> GenPart;
  std::vector<eventBuffer::Jet_s> Jet;
  std::vector<eventBuffer::Muon_s> Muon;

  void fillObjects()
  {
    fillElectrons();
    fillGenJets();
    fillGenParts();
    fillJets();
    fillMuons();
  }

   //--------------------------------------------------------------------------
  // Save objects for which the select function was called
  void saveObjects()
  {
    int n = 0;

    n = 0;
    try
      {
         n = indexmap["Electron"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Electron"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Electron_charge[i]	= Electron_charge[j];
            Electron_cleanmask[i]	= Electron_cleanmask[j];
            Electron_convVeto[i]	= Electron_convVeto[j];
            Electron_cutBased[i]	= Electron_cutBased[j];
            Electron_cutBased_HEEP[i]	= Electron_cutBased_HEEP[j];
            Electron_dEscaleDown[i]	= Electron_dEscaleDown[j];
            Electron_dEscaleUp[i]	= Electron_dEscaleUp[j];
            Electron_dEsigmaDown[i]	= Electron_dEsigmaDown[j];
            Electron_dEsigmaUp[i]	= Electron_dEsigmaUp[j];
            Electron_deltaEtaSC[i]	= Electron_deltaEtaSC[j];
            Electron_dr03EcalRecHitSumEt[i]	= Electron_dr03EcalRecHitSumEt[j];
            Electron_dr03HcalDepth1TowerSumEt[i]	= Electron_dr03HcalDepth1TowerSumEt[j];
            Electron_dr03TkSumPt[i]	= Electron_dr03TkSumPt[j];
            Electron_dr03TkSumPtHEEP[i]	= Electron_dr03TkSumPtHEEP[j];
            Electron_dxy[i]	= Electron_dxy[j];
            Electron_dxyErr[i]	= Electron_dxyErr[j];
            Electron_dz[i]	= Electron_dz[j];
            Electron_dzErr[i]	= Electron_dzErr[j];
            Electron_eCorr[i]	= Electron_eCorr[j];
            Electron_eInvMinusPInv[i]	= Electron_eInvMinusPInv[j];
            Electron_energyErr[i]	= Electron_energyErr[j];
            Electron_eta[i]	= Electron_eta[j];
            Electron_genPartFlav[i]	= Electron_genPartFlav[j];
            Electron_genPartIdx[i]	= Electron_genPartIdx[j];
            Electron_hoe[i]	= Electron_hoe[j];
            Electron_ip3d[i]	= Electron_ip3d[j];
            Electron_isPFcand[i]	= Electron_isPFcand[j];
            Electron_jetIdx[i]	= Electron_jetIdx[j];
            Electron_jetNDauCharged[i]	= Electron_jetNDauCharged[j];
            Electron_jetPtRelv2[i]	= Electron_jetPtRelv2[j];
            Electron_jetRelIso[i]	= Electron_jetRelIso[j];
            Electron_lostHits[i]	= Electron_lostHits[j];
            Electron_mass[i]	= Electron_mass[j];
            Electron_miniPFRelIso_all[i]	= Electron_miniPFRelIso_all[j];
            Electron_miniPFRelIso_chg[i]	= Electron_miniPFRelIso_chg[j];
            Electron_mvaFall17V2Iso[i]	= Electron_mvaFall17V2Iso[j];
            Electron_mvaFall17V2Iso_WP80[i]	= Electron_mvaFall17V2Iso_WP80[j];
            Electron_mvaFall17V2Iso_WP90[i]	= Electron_mvaFall17V2Iso_WP90[j];
            Electron_mvaFall17V2Iso_WPL[i]	= Electron_mvaFall17V2Iso_WPL[j];
            Electron_mvaFall17V2noIso[i]	= Electron_mvaFall17V2noIso[j];
            Electron_mvaFall17V2noIso_WP80[i]	= Electron_mvaFall17V2noIso_WP80[j];
            Electron_mvaFall17V2noIso_WP90[i]	= Electron_mvaFall17V2noIso_WP90[j];
            Electron_mvaFall17V2noIso_WPL[i]	= Electron_mvaFall17V2noIso_WPL[j];
            Electron_mvaTTH[i]	= Electron_mvaTTH[j];
            Electron_pdgId[i]	= Electron_pdgId[j];
            Electron_pfRelIso03_all[i]	= Electron_pfRelIso03_all[j];
            Electron_pfRelIso03_chg[i]	= Electron_pfRelIso03_chg[j];
            Electron_phi[i]	= Electron_phi[j];
            Electron_photonIdx[i]	= Electron_photonIdx[j];
            Electron_pt[i]	= Electron_pt[j];
            Electron_r9[i]	= Electron_r9[j];
            Electron_scEtOverPt[i]	= Electron_scEtOverPt[j];
            Electron_seedGain[i]	= Electron_seedGain[j];
            Electron_sieie[i]	= Electron_sieie[j];
            Electron_sip3d[i]	= Electron_sip3d[j];
            Electron_tightCharge[i]	= Electron_tightCharge[j];
            Electron_vidNestedWPBitmap[i]	= Electron_vidNestedWPBitmap[j];
            Electron_vidNestedWPBitmapHEEP[i]	= Electron_vidNestedWPBitmapHEEP[j];
          }
      }
    nElectron = n;

    n = 0;
    try
      {
         n = indexmap["GenJet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenJet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenJet_eta[i]	= GenJet_eta[j];
            GenJet_hadronFlavour[i]	= GenJet_hadronFlavour[j];
            GenJet_mass[i]	= GenJet_mass[j];
            GenJet_partonFlavour[i]	= GenJet_partonFlavour[j];
            GenJet_phi[i]	= GenJet_phi[j];
            GenJet_pt[i]	= GenJet_pt[j];
          }
      }
    nGenJet = n;

    n = 0;
    try
      {
         n = indexmap["GenPart"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["GenPart"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            GenPart_eta[i]	= GenPart_eta[j];
            GenPart_genPartIdxMother[i]	= GenPart_genPartIdxMother[j];
            GenPart_mass[i]	= GenPart_mass[j];
            GenPart_pdgId[i]	= GenPart_pdgId[j];
            GenPart_phi[i]	= GenPart_phi[j];
            GenPart_pt[i]	= GenPart_pt[j];
            GenPart_status[i]	= GenPart_status[j];
            GenPart_statusFlags[i]	= GenPart_statusFlags[j];
          }
      }
    nGenPart = n;

    n = 0;
    try
      {
         n = indexmap["Jet"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Jet"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Jet_area[i]	= Jet_area[j];
            Jet_bRegCorr[i]	= Jet_bRegCorr[j];
            Jet_bRegRes[i]	= Jet_bRegRes[j];
            Jet_btagCSVV2[i]	= Jet_btagCSVV2[j];
            Jet_btagDeepB[i]	= Jet_btagDeepB[j];
            Jet_btagDeepCvB[i]	= Jet_btagDeepCvB[j];
            Jet_btagDeepCvL[i]	= Jet_btagDeepCvL[j];
            Jet_btagDeepFlavB[i]	= Jet_btagDeepFlavB[j];
            Jet_btagDeepFlavCvB[i]	= Jet_btagDeepFlavCvB[j];
            Jet_btagDeepFlavCvL[i]	= Jet_btagDeepFlavCvL[j];
            Jet_btagDeepFlavQG[i]	= Jet_btagDeepFlavQG[j];
            Jet_cRegCorr[i]	= Jet_cRegCorr[j];
            Jet_cRegRes[i]	= Jet_cRegRes[j];
            Jet_chEmEF[i]	= Jet_chEmEF[j];
            Jet_chFPV0EF[i]	= Jet_chFPV0EF[j];
            Jet_chHEF[i]	= Jet_chHEF[j];
            Jet_cleanmask[i]	= Jet_cleanmask[j];
            Jet_electronIdx1[i]	= Jet_electronIdx1[j];
            Jet_electronIdx2[i]	= Jet_electronIdx2[j];
            Jet_eta[i]	= Jet_eta[j];
            Jet_genJetIdx[i]	= Jet_genJetIdx[j];
            Jet_hadronFlavour[i]	= Jet_hadronFlavour[j];
            Jet_hfadjacentEtaStripsSize[i]	= Jet_hfadjacentEtaStripsSize[j];
            Jet_hfcentralEtaStripSize[i]	= Jet_hfcentralEtaStripSize[j];
            Jet_hfsigmaEtaEta[i]	= Jet_hfsigmaEtaEta[j];
            Jet_hfsigmaPhiPhi[i]	= Jet_hfsigmaPhiPhi[j];
            Jet_jetId[i]	= Jet_jetId[j];
            Jet_mass[i]	= Jet_mass[j];
            Jet_muEF[i]	= Jet_muEF[j];
            Jet_muonIdx1[i]	= Jet_muonIdx1[j];
            Jet_muonIdx2[i]	= Jet_muonIdx2[j];
            Jet_muonSubtrFactor[i]	= Jet_muonSubtrFactor[j];
            Jet_nConstituents[i]	= Jet_nConstituents[j];
            Jet_nElectrons[i]	= Jet_nElectrons[j];
            Jet_nMuons[i]	= Jet_nMuons[j];
            Jet_neEmEF[i]	= Jet_neEmEF[j];
            Jet_neHEF[i]	= Jet_neHEF[j];
            Jet_partonFlavour[i]	= Jet_partonFlavour[j];
            Jet_phi[i]	= Jet_phi[j];
            Jet_pt[i]	= Jet_pt[j];
            Jet_puId[i]	= Jet_puId[j];
            Jet_puIdDisc[i]	= Jet_puIdDisc[j];
            Jet_qgl[i]	= Jet_qgl[j];
            Jet_rawFactor[i]	= Jet_rawFactor[j];
          }
      }
    nJet = n;

    n = 0;
    try
      {
         n = indexmap["Muon"].size();
      }
    catch (...)
      {}
    if ( n > 0 )
      {
        std::vector<int>& index = indexmap["Muon"];
        for(int i=0; i < n; ++i)
          {
            int j = index[i];
            Muon_charge[i]	= Muon_charge[j];
            Muon_cleanmask[i]	= Muon_cleanmask[j];
            Muon_dxy[i]	= Muon_dxy[j];
            Muon_dxyErr[i]	= Muon_dxyErr[j];
            Muon_dxybs[i]	= Muon_dxybs[j];
            Muon_dz[i]	= Muon_dz[j];
            Muon_dzErr[i]	= Muon_dzErr[j];
            Muon_eta[i]	= Muon_eta[j];
            Muon_fsrPhotonIdx[i]	= Muon_fsrPhotonIdx[j];
            Muon_genPartFlav[i]	= Muon_genPartFlav[j];
            Muon_genPartIdx[i]	= Muon_genPartIdx[j];
            Muon_highPtId[i]	= Muon_highPtId[j];
            Muon_highPurity[i]	= Muon_highPurity[j];
            Muon_inTimeMuon[i]	= Muon_inTimeMuon[j];
            Muon_ip3d[i]	= Muon_ip3d[j];
            Muon_isGlobal[i]	= Muon_isGlobal[j];
            Muon_isPFcand[i]	= Muon_isPFcand[j];
            Muon_isStandalone[i]	= Muon_isStandalone[j];
            Muon_isTracker[i]	= Muon_isTracker[j];
            Muon_jetIdx[i]	= Muon_jetIdx[j];
            Muon_jetNDauCharged[i]	= Muon_jetNDauCharged[j];
            Muon_jetPtRelv2[i]	= Muon_jetPtRelv2[j];
            Muon_jetRelIso[i]	= Muon_jetRelIso[j];
            Muon_looseId[i]	= Muon_looseId[j];
            Muon_mass[i]	= Muon_mass[j];
            Muon_mediumId[i]	= Muon_mediumId[j];
            Muon_mediumPromptId[i]	= Muon_mediumPromptId[j];
            Muon_miniIsoId[i]	= Muon_miniIsoId[j];
            Muon_miniPFRelIso_all[i]	= Muon_miniPFRelIso_all[j];
            Muon_miniPFRelIso_chg[i]	= Muon_miniPFRelIso_chg[j];
            Muon_multiIsoId[i]	= Muon_multiIsoId[j];
            Muon_mvaId[i]	= Muon_mvaId[j];
            Muon_mvaLowPt[i]	= Muon_mvaLowPt[j];
            Muon_mvaLowPtId[i]	= Muon_mvaLowPtId[j];
            Muon_mvaTTH[i]	= Muon_mvaTTH[j];
            Muon_nStations[i]	= Muon_nStations[j];
            Muon_nTrackerLayers[i]	= Muon_nTrackerLayers[j];
            Muon_pdgId[i]	= Muon_pdgId[j];
            Muon_pfIsoId[i]	= Muon_pfIsoId[j];
            Muon_pfRelIso03_all[i]	= Muon_pfRelIso03_all[j];
            Muon_pfRelIso03_chg[i]	= Muon_pfRelIso03_chg[j];
            Muon_pfRelIso04_all[i]	= Muon_pfRelIso04_all[j];
            Muon_phi[i]	= Muon_phi[j];
            Muon_pt[i]	= Muon_pt[j];
            Muon_ptErr[i]	= Muon_ptErr[j];
            Muon_puppiIsoId[i]	= Muon_puppiIsoId[j];
            Muon_segmentComp[i]	= Muon_segmentComp[j];
            Muon_sip3d[i]	= Muon_sip3d[j];
            Muon_softId[i]	= Muon_softId[j];
            Muon_softMva[i]	= Muon_softMva[j];
            Muon_softMvaId[i]	= Muon_softMvaId[j];
            Muon_tightCharge[i]	= Muon_tightCharge[j];
            Muon_tightId[i]	= Muon_tightId[j];
            Muon_tkIsoId[i]	= Muon_tkIsoId[j];
            Muon_tkRelIso[i]	= Muon_tkRelIso[j];
            Muon_triggerIdLoose[i]	= Muon_triggerIdLoose[j];
            Muon_tunepRelPt[i]	= Muon_tunepRelPt[j];
          }
      }
    nMuon = n;
  }

  //--------------------------------------------------------------------------
  // A read-only buffer 
  eventBuffer() : input(0), output(0), choose(std::map<std::string, bool>()) {}
  eventBuffer(itreestream& stream, std::string varlist="")
  : input(&stream),
    output(0),
    choose(std::map<std::string, bool>())
  {
    if ( !input->good() ) 
      {
        std::cout << "eventBuffer - please check stream!" 
                  << std::endl;
	    exit(0);
      }

    initBuffers();
    
    // default is to select all branches      
    bool DEFAULT = varlist == "";
    choose["Events/Electron_charge"]	= DEFAULT;
    choose["Events/Electron_cleanmask"]	= DEFAULT;
    choose["Events/Electron_convVeto"]	= DEFAULT;
    choose["Events/Electron_cutBased"]	= DEFAULT;
    choose["Events/Electron_cutBased_HEEP"]	= DEFAULT;
    choose["Events/Electron_dEscaleDown"]	= DEFAULT;
    choose["Events/Electron_dEscaleUp"]	= DEFAULT;
    choose["Events/Electron_dEsigmaDown"]	= DEFAULT;
    choose["Events/Electron_dEsigmaUp"]	= DEFAULT;
    choose["Events/Electron_deltaEtaSC"]	= DEFAULT;
    choose["Events/Electron_dr03EcalRecHitSumEt"]	= DEFAULT;
    choose["Events/Electron_dr03HcalDepth1TowerSumEt"]	= DEFAULT;
    choose["Events/Electron_dr03TkSumPt"]	= DEFAULT;
    choose["Events/Electron_dr03TkSumPtHEEP"]	= DEFAULT;
    choose["Events/Electron_dxy"]	= DEFAULT;
    choose["Events/Electron_dxyErr"]	= DEFAULT;
    choose["Events/Electron_dz"]	= DEFAULT;
    choose["Events/Electron_dzErr"]	= DEFAULT;
    choose["Events/Electron_eCorr"]	= DEFAULT;
    choose["Events/Electron_eInvMinusPInv"]	= DEFAULT;
    choose["Events/Electron_energyErr"]	= DEFAULT;
    choose["Events/Electron_eta"]	= DEFAULT;
    choose["Events/Electron_genPartFlav"]	= DEFAULT;
    choose["Events/Electron_genPartIdx"]	= DEFAULT;
    choose["Events/Electron_hoe"]	= DEFAULT;
    choose["Events/Electron_ip3d"]	= DEFAULT;
    choose["Events/Electron_isPFcand"]	= DEFAULT;
    choose["Events/Electron_jetIdx"]	= DEFAULT;
    choose["Events/Electron_jetNDauCharged"]	= DEFAULT;
    choose["Events/Electron_jetPtRelv2"]	= DEFAULT;
    choose["Events/Electron_jetRelIso"]	= DEFAULT;
    choose["Events/Electron_lostHits"]	= DEFAULT;
    choose["Events/Electron_mass"]	= DEFAULT;
    choose["Events/Electron_miniPFRelIso_all"]	= DEFAULT;
    choose["Events/Electron_miniPFRelIso_chg"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2Iso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WP80"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WP90"]	= DEFAULT;
    choose["Events/Electron_mvaFall17V2noIso_WPL"]	= DEFAULT;
    choose["Events/Electron_mvaTTH"]	= DEFAULT;
    choose["Events/Electron_pdgId"]	= DEFAULT;
    choose["Events/Electron_pfRelIso03_all"]	= DEFAULT;
    choose["Events/Electron_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/Electron_phi"]	= DEFAULT;
    choose["Events/Electron_photonIdx"]	= DEFAULT;
    choose["Events/Electron_pt"]	= DEFAULT;
    choose["Events/Electron_r9"]	= DEFAULT;
    choose["Events/Electron_scEtOverPt"]	= DEFAULT;
    choose["Events/Electron_seedGain"]	= DEFAULT;
    choose["Events/Electron_sieie"]	= DEFAULT;
    choose["Events/Electron_sip3d"]	= DEFAULT;
    choose["Events/Electron_tightCharge"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmap"]	= DEFAULT;
    choose["Events/Electron_vidNestedWPBitmapHEEP"]	= DEFAULT;
    choose["Events/Flag_BadChargedCandidateFilter"]	= DEFAULT;
    choose["Events/Flag_BadChargedCandidateSummer16Filter"]	= DEFAULT;
    choose["Events/Flag_BadPFMuonDzFilter"]	= DEFAULT;
    choose["Events/Flag_BadPFMuonFilter"]	= DEFAULT;
    choose["Events/Flag_BadPFMuonSummer16Filter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHalo2015Filter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHaloFilter"]	= DEFAULT;
    choose["Events/Flag_CSCTightHaloTrkMuUnvetoFilter"]	= DEFAULT;
    choose["Events/Flag_EcalDeadCellBoundaryEnergyFilter"]	= DEFAULT;
    choose["Events/Flag_EcalDeadCellTriggerPrimitiveFilter"]	= DEFAULT;
    choose["Events/Flag_HBHENoiseFilter"]	= DEFAULT;
    choose["Events/Flag_HBHENoiseIsoFilter"]	= DEFAULT;
    choose["Events/Flag_HcalStripHaloFilter"]	= DEFAULT;
    choose["Events/Flag_METFilters"]	= DEFAULT;
    choose["Events/Flag_chargedHadronTrackResolutionFilter"]	= DEFAULT;
    choose["Events/Flag_ecalBadCalibFilter"]	= DEFAULT;
    choose["Events/Flag_ecalLaserCorrFilter"]	= DEFAULT;
    choose["Events/Flag_eeBadScFilter"]	= DEFAULT;
    choose["Events/Flag_globalSuperTightHalo2016Filter"]	= DEFAULT;
    choose["Events/Flag_globalTightHalo2016Filter"]	= DEFAULT;
    choose["Events/Flag_goodVertices"]	= DEFAULT;
    choose["Events/Flag_hcalLaserEventFilter"]	= DEFAULT;
    choose["Events/Flag_hfNoisyHitsFilter"]	= DEFAULT;
    choose["Events/Flag_muonBadTrackFilter"]	= DEFAULT;
    choose["Events/Flag_trkPOGFilters"]	= DEFAULT;
    choose["Events/Flag_trkPOG_logErrorTooManyClusters"]	= DEFAULT;
    choose["Events/Flag_trkPOG_manystripclus53X"]	= DEFAULT;
    choose["Events/Flag_trkPOG_toomanystripclus53X"]	= DEFAULT;
    choose["Events/GenJet_eta"]	= DEFAULT;
    choose["Events/GenJet_hadronFlavour"]	= DEFAULT;
    choose["Events/GenJet_mass"]	= DEFAULT;
    choose["Events/GenJet_partonFlavour"]	= DEFAULT;
    choose["Events/GenJet_phi"]	= DEFAULT;
    choose["Events/GenJet_pt"]	= DEFAULT;
    choose["Events/GenPart_eta"]	= DEFAULT;
    choose["Events/GenPart_genPartIdxMother"]	= DEFAULT;
    choose["Events/GenPart_mass"]	= DEFAULT;
    choose["Events/GenPart_pdgId"]	= DEFAULT;
    choose["Events/GenPart_phi"]	= DEFAULT;
    choose["Events/GenPart_pt"]	= DEFAULT;
    choose["Events/GenPart_status"]	= DEFAULT;
    choose["Events/GenPart_statusFlags"]	= DEFAULT;
    choose["Events/GenVtx_t0"]	= DEFAULT;
    choose["Events/GenVtx_x"]	= DEFAULT;
    choose["Events/GenVtx_y"]	= DEFAULT;
    choose["Events/GenVtx_z"]	= DEFAULT;
    choose["Events/Generator_binvar"]	= DEFAULT;
    choose["Events/Generator_id1"]	= DEFAULT;
    choose["Events/Generator_id2"]	= DEFAULT;
    choose["Events/Generator_scalePDF"]	= DEFAULT;
    choose["Events/Generator_weight"]	= DEFAULT;
    choose["Events/Generator_x1"]	= DEFAULT;
    choose["Events/Generator_x2"]	= DEFAULT;
    choose["Events/Generator_xpdf1"]	= DEFAULT;
    choose["Events/Generator_xpdf2"]	= DEFAULT;
    choose["Events/HLT_IsoMu20"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu27"]	= DEFAULT;
    choose["Events/HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1"]	= DEFAULT;
    choose["Events/HLT_IsoMu30"]	= DEFAULT;
    choose["Events/HLT_PFHT1050"]	= DEFAULT;
    choose["Events/HLT_PFHT180"]	= DEFAULT;
    choose["Events/HLT_PFHT250"]	= DEFAULT;
    choose["Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40"]	= DEFAULT;
    choose["Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0"]	= DEFAULT;
    choose["Events/HLT_PFHT350"]	= DEFAULT;
    choose["Events/HLT_PFHT350MinPFJet15"]	= DEFAULT;
    choose["Events/HLT_PFHT370"]	= DEFAULT;
    choose["Events/HLT_PFHT380_SixPFJet32"]	= DEFAULT;
    choose["Events/HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2"]	= DEFAULT;
    choose["Events/HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"]	= DEFAULT;
    choose["Events/HLT_PFHT430"]	= DEFAULT;
    choose["Events/HLT_PFHT430_SixPFJet40"]	= DEFAULT;
    choose["Events/HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"]	= DEFAULT;
    choose["Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT510"]	= DEFAULT;
    choose["Events/HLT_PFHT590"]	= DEFAULT;
    choose["Events/HLT_PFHT680"]	= DEFAULT;
    choose["Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT780"]	= DEFAULT;
    choose["Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight"]	= DEFAULT;
    choose["Events/HLT_PFHT890"]	= DEFAULT;
    choose["Events/HLTriggerFinalPath"]	= DEFAULT;
    choose["Events/HLTriggerFirstPath"]	= DEFAULT;
    choose["Events/Jet_area"]	= DEFAULT;
    choose["Events/Jet_bRegCorr"]	= DEFAULT;
    choose["Events/Jet_bRegRes"]	= DEFAULT;
    choose["Events/Jet_btagCSVV2"]	= DEFAULT;
    choose["Events/Jet_btagDeepB"]	= DEFAULT;
    choose["Events/Jet_btagDeepCvB"]	= DEFAULT;
    choose["Events/Jet_btagDeepCvL"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavB"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavCvB"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavCvL"]	= DEFAULT;
    choose["Events/Jet_btagDeepFlavQG"]	= DEFAULT;
    choose["Events/Jet_cRegCorr"]	= DEFAULT;
    choose["Events/Jet_cRegRes"]	= DEFAULT;
    choose["Events/Jet_chEmEF"]	= DEFAULT;
    choose["Events/Jet_chFPV0EF"]	= DEFAULT;
    choose["Events/Jet_chHEF"]	= DEFAULT;
    choose["Events/Jet_cleanmask"]	= DEFAULT;
    choose["Events/Jet_electronIdx1"]	= DEFAULT;
    choose["Events/Jet_electronIdx2"]	= DEFAULT;
    choose["Events/Jet_eta"]	= DEFAULT;
    choose["Events/Jet_genJetIdx"]	= DEFAULT;
    choose["Events/Jet_hadronFlavour"]	= DEFAULT;
    choose["Events/Jet_hfadjacentEtaStripsSize"]	= DEFAULT;
    choose["Events/Jet_hfcentralEtaStripSize"]	= DEFAULT;
    choose["Events/Jet_hfsigmaEtaEta"]	= DEFAULT;
    choose["Events/Jet_hfsigmaPhiPhi"]	= DEFAULT;
    choose["Events/Jet_jetId"]	= DEFAULT;
    choose["Events/Jet_mass"]	= DEFAULT;
    choose["Events/Jet_muEF"]	= DEFAULT;
    choose["Events/Jet_muonIdx1"]	= DEFAULT;
    choose["Events/Jet_muonIdx2"]	= DEFAULT;
    choose["Events/Jet_muonSubtrFactor"]	= DEFAULT;
    choose["Events/Jet_nConstituents"]	= DEFAULT;
    choose["Events/Jet_nElectrons"]	= DEFAULT;
    choose["Events/Jet_nMuons"]	= DEFAULT;
    choose["Events/Jet_neEmEF"]	= DEFAULT;
    choose["Events/Jet_neHEF"]	= DEFAULT;
    choose["Events/Jet_partonFlavour"]	= DEFAULT;
    choose["Events/Jet_phi"]	= DEFAULT;
    choose["Events/Jet_pt"]	= DEFAULT;
    choose["Events/Jet_puId"]	= DEFAULT;
    choose["Events/Jet_puIdDisc"]	= DEFAULT;
    choose["Events/Jet_qgl"]	= DEFAULT;
    choose["Events/Jet_rawFactor"]	= DEFAULT;
    choose["Events/Muon_charge"]	= DEFAULT;
    choose["Events/Muon_cleanmask"]	= DEFAULT;
    choose["Events/Muon_dxy"]	= DEFAULT;
    choose["Events/Muon_dxyErr"]	= DEFAULT;
    choose["Events/Muon_dxybs"]	= DEFAULT;
    choose["Events/Muon_dz"]	= DEFAULT;
    choose["Events/Muon_dzErr"]	= DEFAULT;
    choose["Events/Muon_eta"]	= DEFAULT;
    choose["Events/Muon_fsrPhotonIdx"]	= DEFAULT;
    choose["Events/Muon_genPartFlav"]	= DEFAULT;
    choose["Events/Muon_genPartIdx"]	= DEFAULT;
    choose["Events/Muon_highPtId"]	= DEFAULT;
    choose["Events/Muon_highPurity"]	= DEFAULT;
    choose["Events/Muon_inTimeMuon"]	= DEFAULT;
    choose["Events/Muon_ip3d"]	= DEFAULT;
    choose["Events/Muon_isGlobal"]	= DEFAULT;
    choose["Events/Muon_isPFcand"]	= DEFAULT;
    choose["Events/Muon_isStandalone"]	= DEFAULT;
    choose["Events/Muon_isTracker"]	= DEFAULT;
    choose["Events/Muon_jetIdx"]	= DEFAULT;
    choose["Events/Muon_jetNDauCharged"]	= DEFAULT;
    choose["Events/Muon_jetPtRelv2"]	= DEFAULT;
    choose["Events/Muon_jetRelIso"]	= DEFAULT;
    choose["Events/Muon_looseId"]	= DEFAULT;
    choose["Events/Muon_mass"]	= DEFAULT;
    choose["Events/Muon_mediumId"]	= DEFAULT;
    choose["Events/Muon_mediumPromptId"]	= DEFAULT;
    choose["Events/Muon_miniIsoId"]	= DEFAULT;
    choose["Events/Muon_miniPFRelIso_all"]	= DEFAULT;
    choose["Events/Muon_miniPFRelIso_chg"]	= DEFAULT;
    choose["Events/Muon_multiIsoId"]	= DEFAULT;
    choose["Events/Muon_mvaId"]	= DEFAULT;
    choose["Events/Muon_mvaLowPt"]	= DEFAULT;
    choose["Events/Muon_mvaLowPtId"]	= DEFAULT;
    choose["Events/Muon_mvaTTH"]	= DEFAULT;
    choose["Events/Muon_nStations"]	= DEFAULT;
    choose["Events/Muon_nTrackerLayers"]	= DEFAULT;
    choose["Events/Muon_pdgId"]	= DEFAULT;
    choose["Events/Muon_pfIsoId"]	= DEFAULT;
    choose["Events/Muon_pfRelIso03_all"]	= DEFAULT;
    choose["Events/Muon_pfRelIso03_chg"]	= DEFAULT;
    choose["Events/Muon_pfRelIso04_all"]	= DEFAULT;
    choose["Events/Muon_phi"]	= DEFAULT;
    choose["Events/Muon_pt"]	= DEFAULT;
    choose["Events/Muon_ptErr"]	= DEFAULT;
    choose["Events/Muon_puppiIsoId"]	= DEFAULT;
    choose["Events/Muon_segmentComp"]	= DEFAULT;
    choose["Events/Muon_sip3d"]	= DEFAULT;
    choose["Events/Muon_softId"]	= DEFAULT;
    choose["Events/Muon_softMva"]	= DEFAULT;
    choose["Events/Muon_softMvaId"]	= DEFAULT;
    choose["Events/Muon_tightCharge"]	= DEFAULT;
    choose["Events/Muon_tightId"]	= DEFAULT;
    choose["Events/Muon_tkIsoId"]	= DEFAULT;
    choose["Events/Muon_tkRelIso"]	= DEFAULT;
    choose["Events/Muon_triggerIdLoose"]	= DEFAULT;
    choose["Events/Muon_tunepRelPt"]	= DEFAULT;
    choose["Events/OtherPV_z"]	= DEFAULT;
    choose["Events/PSWeight"]	= DEFAULT;
    choose["Events/PV_chi2"]	= DEFAULT;
    choose["Events/PV_ndof"]	= DEFAULT;
    choose["Events/PV_npvs"]	= DEFAULT;
    choose["Events/PV_npvsGood"]	= DEFAULT;
    choose["Events/PV_score"]	= DEFAULT;
    choose["Events/PV_x"]	= DEFAULT;
    choose["Events/PV_y"]	= DEFAULT;
    choose["Events/PV_z"]	= DEFAULT;
    choose["Events/Pileup_gpudensity"]	= DEFAULT;
    choose["Events/Pileup_nPU"]	= DEFAULT;
    choose["Events/Pileup_nTrueInt"]	= DEFAULT;
    choose["Events/Pileup_pudensity"]	= DEFAULT;
    choose["Events/Pileup_sumEOOT"]	= DEFAULT;
    choose["Events/Pileup_sumLOOT"]	= DEFAULT;
    choose["Events/btagWeight_CSVV2"]	= DEFAULT;
    choose["Events/btagWeight_DeepCSVB"]	= DEFAULT;
    choose["Events/event"]	= DEFAULT;
    choose["Events/genTtbarId"]	= DEFAULT;
    choose["Events/genWeight"]	= DEFAULT;
    choose["Events/luminosityBlock"]	= DEFAULT;
    choose["Events/run"]	= DEFAULT;

    if ( DEFAULT )
      {
        std::cout << std::endl
                  << "eventBuffer - All branches selected"
                  << std::endl;
      }
    else
      {
        std::cout << "eventBuffer - branches selected:"
                  << std::endl;      
        std::istringstream sin(varlist);
        while ( sin )
          {
            std::string key;
            sin >> key;
            if ( sin )
              {
		        std::map<std::string, bool>::iterator it;
		        for(it = choose.begin(); it != choose.end(); it++)
		          {
		            if ( it->first.length() > key.length() )
		              {
			            if ( it->first.substr(0, key.size()) == key )
			              {
			                choose[it->first] = true;
			              }
		              }
                  }
              }
          }
      }
    if ( choose["Events/Electron_charge"] )
      input->select("Events/Electron_charge", 	Electron_charge);
    if ( choose["Events/Electron_cleanmask"] )
      input->select("Events/Electron_cleanmask", 	Electron_cleanmask);
    if ( choose["Events/Electron_convVeto"] )
      input->select("Events/Electron_convVeto", 	Electron_convVeto);
    if ( choose["Events/Electron_cutBased"] )
      input->select("Events/Electron_cutBased", 	Electron_cutBased);
    if ( choose["Events/Electron_cutBased_HEEP"] )
      input->select("Events/Electron_cutBased_HEEP",
                     Electron_cutBased_HEEP);
    if ( choose["Events/Electron_dEscaleDown"] )
      input->select("Events/Electron_dEscaleDown", 	Electron_dEscaleDown);
    if ( choose["Events/Electron_dEscaleUp"] )
      input->select("Events/Electron_dEscaleUp", 	Electron_dEscaleUp);
    if ( choose["Events/Electron_dEsigmaDown"] )
      input->select("Events/Electron_dEsigmaDown", 	Electron_dEsigmaDown);
    if ( choose["Events/Electron_dEsigmaUp"] )
      input->select("Events/Electron_dEsigmaUp", 	Electron_dEsigmaUp);
    if ( choose["Events/Electron_deltaEtaSC"] )
      input->select("Events/Electron_deltaEtaSC", 	Electron_deltaEtaSC);
    if ( choose["Events/Electron_dr03EcalRecHitSumEt"] )
      input->select("Events/Electron_dr03EcalRecHitSumEt",
                     Electron_dr03EcalRecHitSumEt);
    if ( choose["Events/Electron_dr03HcalDepth1TowerSumEt"] )
      input->select("Events/Electron_dr03HcalDepth1TowerSumEt",
                     Electron_dr03HcalDepth1TowerSumEt);
    if ( choose["Events/Electron_dr03TkSumPt"] )
      input->select("Events/Electron_dr03TkSumPt", 	Electron_dr03TkSumPt);
    if ( choose["Events/Electron_dr03TkSumPtHEEP"] )
      input->select("Events/Electron_dr03TkSumPtHEEP",
                     Electron_dr03TkSumPtHEEP);
    if ( choose["Events/Electron_dxy"] )
      input->select("Events/Electron_dxy", 	Electron_dxy);
    if ( choose["Events/Electron_dxyErr"] )
      input->select("Events/Electron_dxyErr", 	Electron_dxyErr);
    if ( choose["Events/Electron_dz"] )
      input->select("Events/Electron_dz", 	Electron_dz);
    if ( choose["Events/Electron_dzErr"] )
      input->select("Events/Electron_dzErr", 	Electron_dzErr);
    if ( choose["Events/Electron_eCorr"] )
      input->select("Events/Electron_eCorr", 	Electron_eCorr);
    if ( choose["Events/Electron_eInvMinusPInv"] )
      input->select("Events/Electron_eInvMinusPInv",
                     Electron_eInvMinusPInv);
    if ( choose["Events/Electron_energyErr"] )
      input->select("Events/Electron_energyErr", 	Electron_energyErr);
    if ( choose["Events/Electron_eta"] )
      input->select("Events/Electron_eta", 	Electron_eta);
    if ( choose["Events/Electron_genPartFlav"] )
      input->select("Events/Electron_genPartFlav", 	Electron_genPartFlav);
    if ( choose["Events/Electron_genPartIdx"] )
      input->select("Events/Electron_genPartIdx", 	Electron_genPartIdx);
    if ( choose["Events/Electron_hoe"] )
      input->select("Events/Electron_hoe", 	Electron_hoe);
    if ( choose["Events/Electron_ip3d"] )
      input->select("Events/Electron_ip3d", 	Electron_ip3d);
    if ( choose["Events/Electron_isPFcand"] )
      input->select("Events/Electron_isPFcand", 	Electron_isPFcand);
    if ( choose["Events/Electron_jetIdx"] )
      input->select("Events/Electron_jetIdx", 	Electron_jetIdx);
    if ( choose["Events/Electron_jetNDauCharged"] )
      input->select("Events/Electron_jetNDauCharged",
                     Electron_jetNDauCharged);
    if ( choose["Events/Electron_jetPtRelv2"] )
      input->select("Events/Electron_jetPtRelv2", 	Electron_jetPtRelv2);
    if ( choose["Events/Electron_jetRelIso"] )
      input->select("Events/Electron_jetRelIso", 	Electron_jetRelIso);
    if ( choose["Events/Electron_lostHits"] )
      input->select("Events/Electron_lostHits", 	Electron_lostHits);
    if ( choose["Events/Electron_mass"] )
      input->select("Events/Electron_mass", 	Electron_mass);
    if ( choose["Events/Electron_miniPFRelIso_all"] )
      input->select("Events/Electron_miniPFRelIso_all",
                     Electron_miniPFRelIso_all);
    if ( choose["Events/Electron_miniPFRelIso_chg"] )
      input->select("Events/Electron_miniPFRelIso_chg",
                     Electron_miniPFRelIso_chg);
    if ( choose["Events/Electron_mvaFall17V2Iso"] )
      input->select("Events/Electron_mvaFall17V2Iso",
                     Electron_mvaFall17V2Iso);
    if ( choose["Events/Electron_mvaFall17V2Iso_WP80"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP80",
                     Electron_mvaFall17V2Iso_WP80);
    if ( choose["Events/Electron_mvaFall17V2Iso_WP90"] )
      input->select("Events/Electron_mvaFall17V2Iso_WP90",
                     Electron_mvaFall17V2Iso_WP90);
    if ( choose["Events/Electron_mvaFall17V2Iso_WPL"] )
      input->select("Events/Electron_mvaFall17V2Iso_WPL",
                     Electron_mvaFall17V2Iso_WPL);
    if ( choose["Events/Electron_mvaFall17V2noIso"] )
      input->select("Events/Electron_mvaFall17V2noIso",
                     Electron_mvaFall17V2noIso);
    if ( choose["Events/Electron_mvaFall17V2noIso_WP80"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP80",
                     Electron_mvaFall17V2noIso_WP80);
    if ( choose["Events/Electron_mvaFall17V2noIso_WP90"] )
      input->select("Events/Electron_mvaFall17V2noIso_WP90",
                     Electron_mvaFall17V2noIso_WP90);
    if ( choose["Events/Electron_mvaFall17V2noIso_WPL"] )
      input->select("Events/Electron_mvaFall17V2noIso_WPL",
                     Electron_mvaFall17V2noIso_WPL);
    if ( choose["Events/Electron_mvaTTH"] )
      input->select("Events/Electron_mvaTTH", 	Electron_mvaTTH);
    if ( choose["Events/Electron_pdgId"] )
      input->select("Events/Electron_pdgId", 	Electron_pdgId);
    if ( choose["Events/Electron_pfRelIso03_all"] )
      input->select("Events/Electron_pfRelIso03_all",
                     Electron_pfRelIso03_all);
    if ( choose["Events/Electron_pfRelIso03_chg"] )
      input->select("Events/Electron_pfRelIso03_chg",
                     Electron_pfRelIso03_chg);
    if ( choose["Events/Electron_phi"] )
      input->select("Events/Electron_phi", 	Electron_phi);
    if ( choose["Events/Electron_photonIdx"] )
      input->select("Events/Electron_photonIdx", 	Electron_photonIdx);
    if ( choose["Events/Electron_pt"] )
      input->select("Events/Electron_pt", 	Electron_pt);
    if ( choose["Events/Electron_r9"] )
      input->select("Events/Electron_r9", 	Electron_r9);
    if ( choose["Events/Electron_scEtOverPt"] )
      input->select("Events/Electron_scEtOverPt", 	Electron_scEtOverPt);
    if ( choose["Events/Electron_seedGain"] )
      input->select("Events/Electron_seedGain", 	Electron_seedGain);
    if ( choose["Events/Electron_sieie"] )
      input->select("Events/Electron_sieie", 	Electron_sieie);
    if ( choose["Events/Electron_sip3d"] )
      input->select("Events/Electron_sip3d", 	Electron_sip3d);
    if ( choose["Events/Electron_tightCharge"] )
      input->select("Events/Electron_tightCharge", 	Electron_tightCharge);
    if ( choose["Events/Electron_vidNestedWPBitmap"] )
      input->select("Events/Electron_vidNestedWPBitmap",
                     Electron_vidNestedWPBitmap);
    if ( choose["Events/Electron_vidNestedWPBitmapHEEP"] )
      input->select("Events/Electron_vidNestedWPBitmapHEEP",
                     Electron_vidNestedWPBitmapHEEP);
    if ( choose["Events/Flag_BadChargedCandidateFilter"] )
      input->select("Events/Flag_BadChargedCandidateFilter",
                     Flag_BadChargedCandidateFilter);
    if ( choose["Events/Flag_BadChargedCandidateSummer16Filter"] )
      input->select("Events/Flag_BadChargedCandidateSummer16Filter",
                     Flag_BadChargedCandidateSummer16Filter);
    if ( choose["Events/Flag_BadPFMuonDzFilter"] )
      input->select("Events/Flag_BadPFMuonDzFilter",
                     Flag_BadPFMuonDzFilter);
    if ( choose["Events/Flag_BadPFMuonFilter"] )
      input->select("Events/Flag_BadPFMuonFilter", 	Flag_BadPFMuonFilter);
    if ( choose["Events/Flag_BadPFMuonSummer16Filter"] )
      input->select("Events/Flag_BadPFMuonSummer16Filter",
                     Flag_BadPFMuonSummer16Filter);
    if ( choose["Events/Flag_CSCTightHalo2015Filter"] )
      input->select("Events/Flag_CSCTightHalo2015Filter",
                     Flag_CSCTightHalo2015Filter);
    if ( choose["Events/Flag_CSCTightHaloFilter"] )
      input->select("Events/Flag_CSCTightHaloFilter",
                     Flag_CSCTightHaloFilter);
    if ( choose["Events/Flag_CSCTightHaloTrkMuUnvetoFilter"] )
      input->select("Events/Flag_CSCTightHaloTrkMuUnvetoFilter",
                     Flag_CSCTightHaloTrkMuUnvetoFilter);
    if ( choose["Events/Flag_EcalDeadCellBoundaryEnergyFilter"] )
      input->select("Events/Flag_EcalDeadCellBoundaryEnergyFilter",
                     Flag_EcalDeadCellBoundaryEnergyFilter);
    if ( choose["Events/Flag_EcalDeadCellTriggerPrimitiveFilter"] )
      input->select("Events/Flag_EcalDeadCellTriggerPrimitiveFilter",
                     Flag_EcalDeadCellTriggerPrimitiveFilter);
    if ( choose["Events/Flag_HBHENoiseFilter"] )
      input->select("Events/Flag_HBHENoiseFilter", 	Flag_HBHENoiseFilter);
    if ( choose["Events/Flag_HBHENoiseIsoFilter"] )
      input->select("Events/Flag_HBHENoiseIsoFilter",
                     Flag_HBHENoiseIsoFilter);
    if ( choose["Events/Flag_HcalStripHaloFilter"] )
      input->select("Events/Flag_HcalStripHaloFilter",
                     Flag_HcalStripHaloFilter);
    if ( choose["Events/Flag_METFilters"] )
      input->select("Events/Flag_METFilters", 	Flag_METFilters);
    if ( choose["Events/Flag_chargedHadronTrackResolutionFilter"] )
      input->select("Events/Flag_chargedHadronTrackResolutionFilter",
                     Flag_chargedHadronTrackResolutionFilter);
    if ( choose["Events/Flag_ecalBadCalibFilter"] )
      input->select("Events/Flag_ecalBadCalibFilter",
                     Flag_ecalBadCalibFilter);
    if ( choose["Events/Flag_ecalLaserCorrFilter"] )
      input->select("Events/Flag_ecalLaserCorrFilter",
                     Flag_ecalLaserCorrFilter);
    if ( choose["Events/Flag_eeBadScFilter"] )
      input->select("Events/Flag_eeBadScFilter", 	Flag_eeBadScFilter);
    if ( choose["Events/Flag_globalSuperTightHalo2016Filter"] )
      input->select("Events/Flag_globalSuperTightHalo2016Filter",
                     Flag_globalSuperTightHalo2016Filter);
    if ( choose["Events/Flag_globalTightHalo2016Filter"] )
      input->select("Events/Flag_globalTightHalo2016Filter",
                     Flag_globalTightHalo2016Filter);
    if ( choose["Events/Flag_goodVertices"] )
      input->select("Events/Flag_goodVertices", 	Flag_goodVertices);
    if ( choose["Events/Flag_hcalLaserEventFilter"] )
      input->select("Events/Flag_hcalLaserEventFilter",
                     Flag_hcalLaserEventFilter);
    if ( choose["Events/Flag_hfNoisyHitsFilter"] )
      input->select("Events/Flag_hfNoisyHitsFilter",
                     Flag_hfNoisyHitsFilter);
    if ( choose["Events/Flag_muonBadTrackFilter"] )
      input->select("Events/Flag_muonBadTrackFilter",
                     Flag_muonBadTrackFilter);
    if ( choose["Events/Flag_trkPOGFilters"] )
      input->select("Events/Flag_trkPOGFilters", 	Flag_trkPOGFilters);
    if ( choose["Events/Flag_trkPOG_logErrorTooManyClusters"] )
      input->select("Events/Flag_trkPOG_logErrorTooManyClusters",
                     Flag_trkPOG_logErrorTooManyClusters);
    if ( choose["Events/Flag_trkPOG_manystripclus53X"] )
      input->select("Events/Flag_trkPOG_manystripclus53X",
                     Flag_trkPOG_manystripclus53X);
    if ( choose["Events/Flag_trkPOG_toomanystripclus53X"] )
      input->select("Events/Flag_trkPOG_toomanystripclus53X",
                     Flag_trkPOG_toomanystripclus53X);
    if ( choose["Events/GenJet_eta"] )
      input->select("Events/GenJet_eta", 	GenJet_eta);
    if ( choose["Events/GenJet_hadronFlavour"] )
      input->select("Events/GenJet_hadronFlavour", 	GenJet_hadronFlavour);
    if ( choose["Events/GenJet_mass"] )
      input->select("Events/GenJet_mass", 	GenJet_mass);
    if ( choose["Events/GenJet_partonFlavour"] )
      input->select("Events/GenJet_partonFlavour", 	GenJet_partonFlavour);
    if ( choose["Events/GenJet_phi"] )
      input->select("Events/GenJet_phi", 	GenJet_phi);
    if ( choose["Events/GenJet_pt"] )
      input->select("Events/GenJet_pt", 	GenJet_pt);
    if ( choose["Events/GenPart_eta"] )
      input->select("Events/GenPart_eta", 	GenPart_eta);
    if ( choose["Events/GenPart_genPartIdxMother"] )
      input->select("Events/GenPart_genPartIdxMother",
                     GenPart_genPartIdxMother);
    if ( choose["Events/GenPart_mass"] )
      input->select("Events/GenPart_mass", 	GenPart_mass);
    if ( choose["Events/GenPart_pdgId"] )
      input->select("Events/GenPart_pdgId", 	GenPart_pdgId);
    if ( choose["Events/GenPart_phi"] )
      input->select("Events/GenPart_phi", 	GenPart_phi);
    if ( choose["Events/GenPart_pt"] )
      input->select("Events/GenPart_pt", 	GenPart_pt);
    if ( choose["Events/GenPart_status"] )
      input->select("Events/GenPart_status", 	GenPart_status);
    if ( choose["Events/GenPart_statusFlags"] )
      input->select("Events/GenPart_statusFlags", 	GenPart_statusFlags);
    if ( choose["Events/GenVtx_t0"] )
      input->select("Events/GenVtx_t0", 	GenVtx_t0);
    if ( choose["Events/GenVtx_x"] )
      input->select("Events/GenVtx_x", 	GenVtx_x);
    if ( choose["Events/GenVtx_y"] )
      input->select("Events/GenVtx_y", 	GenVtx_y);
    if ( choose["Events/GenVtx_z"] )
      input->select("Events/GenVtx_z", 	GenVtx_z);
    if ( choose["Events/Generator_binvar"] )
      input->select("Events/Generator_binvar", 	Generator_binvar);
    if ( choose["Events/Generator_id1"] )
      input->select("Events/Generator_id1", 	Generator_id1);
    if ( choose["Events/Generator_id2"] )
      input->select("Events/Generator_id2", 	Generator_id2);
    if ( choose["Events/Generator_scalePDF"] )
      input->select("Events/Generator_scalePDF", 	Generator_scalePDF);
    if ( choose["Events/Generator_weight"] )
      input->select("Events/Generator_weight", 	Generator_weight);
    if ( choose["Events/Generator_x1"] )
      input->select("Events/Generator_x1", 	Generator_x1);
    if ( choose["Events/Generator_x2"] )
      input->select("Events/Generator_x2", 	Generator_x2);
    if ( choose["Events/Generator_xpdf1"] )
      input->select("Events/Generator_xpdf1", 	Generator_xpdf1);
    if ( choose["Events/Generator_xpdf2"] )
      input->select("Events/Generator_xpdf2", 	Generator_xpdf2);
    if ( choose["Events/HLT_IsoMu20"] )
      input->select("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    if ( choose["Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1);
    if ( choose["Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    if ( choose["Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1);
    if ( choose["Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    if ( choose["Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1",
                     HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1);
    if ( choose["Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1"] )
      input->select("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                     HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    if ( choose["Events/HLT_IsoMu24"] )
      input->select("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    if ( choose["Events/HLT_IsoMu24_eta2p1"] )
      input->select("Events/HLT_IsoMu24_eta2p1", 	HLT_IsoMu24_eta2p1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1",
                     HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"] )
      input->select("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr",
                     HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"] )
      input->select("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
                     HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1);
    if ( choose["Events/HLT_IsoMu27"] )
      input->select("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    if ( choose["Events/HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1"] )
      input->select("Events/HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
                     HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1);
    if ( choose["Events/HLT_IsoMu30"] )
      input->select("Events/HLT_IsoMu30", 	HLT_IsoMu30);
    if ( choose["Events/HLT_PFHT1050"] )
      input->select("Events/HLT_PFHT1050", 	HLT_PFHT1050);
    if ( choose["Events/HLT_PFHT180"] )
      input->select("Events/HLT_PFHT180", 	HLT_PFHT180);
    if ( choose["Events/HLT_PFHT250"] )
      input->select("Events/HLT_PFHT250", 	HLT_PFHT250);
    if ( choose["Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40"] )
      input->select("Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40",
                     HLT_PFHT300PT30_QuadPFJet_75_60_45_40);
    if ( choose["Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0"] )
      input->select("Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0",
                     HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0);
    if ( choose["Events/HLT_PFHT350"] )
      input->select("Events/HLT_PFHT350", 	HLT_PFHT350);
    if ( choose["Events/HLT_PFHT350MinPFJet15"] )
      input->select("Events/HLT_PFHT350MinPFJet15", 	HLT_PFHT350MinPFJet15);
    if ( choose["Events/HLT_PFHT370"] )
      input->select("Events/HLT_PFHT370", 	HLT_PFHT370);
    if ( choose["Events/HLT_PFHT380_SixPFJet32"] )
      input->select("Events/HLT_PFHT380_SixPFJet32",
                     HLT_PFHT380_SixPFJet32);
    if ( choose["Events/HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2"] )
      input->select("Events/HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2",
                     HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2);
    if ( choose["Events/HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"] )
      input->select("Events/HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
                     HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2);
    if ( choose["Events/HLT_PFHT430"] )
      input->select("Events/HLT_PFHT430", 	HLT_PFHT430);
    if ( choose["Events/HLT_PFHT430_SixPFJet40"] )
      input->select("Events/HLT_PFHT430_SixPFJet40",
                     HLT_PFHT430_SixPFJet40);
    if ( choose["Events/HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"] )
      input->select("Events/HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5",
                     HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5);
    if ( choose["Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                     HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    if ( choose["Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight"] )
      input->select("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                     HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    if ( choose["Events/HLT_PFHT510"] )
      input->select("Events/HLT_PFHT510", 	HLT_PFHT510);
    if ( choose["Events/HLT_PFHT590"] )
      input->select("Events/HLT_PFHT590", 	HLT_PFHT590);
    if ( choose["Events/HLT_PFHT680"] )
      input->select("Events/HLT_PFHT680", 	HLT_PFHT680);
    if ( choose["Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    if ( choose["Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight"] )
      input->select("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                     HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    if ( choose["Events/HLT_PFHT780"] )
      input->select("Events/HLT_PFHT780", 	HLT_PFHT780);
    if ( choose["Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                     HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    if ( choose["Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight"] )
      input->select("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                     HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    if ( choose["Events/HLT_PFHT890"] )
      input->select("Events/HLT_PFHT890", 	HLT_PFHT890);
    if ( choose["Events/HLTriggerFinalPath"] )
      input->select("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    if ( choose["Events/HLTriggerFirstPath"] )
      input->select("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
    if ( choose["Events/Jet_area"] )
      input->select("Events/Jet_area", 	Jet_area);
    if ( choose["Events/Jet_bRegCorr"] )
      input->select("Events/Jet_bRegCorr", 	Jet_bRegCorr);
    if ( choose["Events/Jet_bRegRes"] )
      input->select("Events/Jet_bRegRes", 	Jet_bRegRes);
    if ( choose["Events/Jet_btagCSVV2"] )
      input->select("Events/Jet_btagCSVV2", 	Jet_btagCSVV2);
    if ( choose["Events/Jet_btagDeepB"] )
      input->select("Events/Jet_btagDeepB", 	Jet_btagDeepB);
    if ( choose["Events/Jet_btagDeepCvB"] )
      input->select("Events/Jet_btagDeepCvB", 	Jet_btagDeepCvB);
    if ( choose["Events/Jet_btagDeepCvL"] )
      input->select("Events/Jet_btagDeepCvL", 	Jet_btagDeepCvL);
    if ( choose["Events/Jet_btagDeepFlavB"] )
      input->select("Events/Jet_btagDeepFlavB", 	Jet_btagDeepFlavB);
    if ( choose["Events/Jet_btagDeepFlavCvB"] )
      input->select("Events/Jet_btagDeepFlavCvB", 	Jet_btagDeepFlavCvB);
    if ( choose["Events/Jet_btagDeepFlavCvL"] )
      input->select("Events/Jet_btagDeepFlavCvL", 	Jet_btagDeepFlavCvL);
    if ( choose["Events/Jet_btagDeepFlavQG"] )
      input->select("Events/Jet_btagDeepFlavQG", 	Jet_btagDeepFlavQG);
    if ( choose["Events/Jet_cRegCorr"] )
      input->select("Events/Jet_cRegCorr", 	Jet_cRegCorr);
    if ( choose["Events/Jet_cRegRes"] )
      input->select("Events/Jet_cRegRes", 	Jet_cRegRes);
    if ( choose["Events/Jet_chEmEF"] )
      input->select("Events/Jet_chEmEF", 	Jet_chEmEF);
    if ( choose["Events/Jet_chFPV0EF"] )
      input->select("Events/Jet_chFPV0EF", 	Jet_chFPV0EF);
    if ( choose["Events/Jet_chHEF"] )
      input->select("Events/Jet_chHEF", 	Jet_chHEF);
    if ( choose["Events/Jet_cleanmask"] )
      input->select("Events/Jet_cleanmask", 	Jet_cleanmask);
    if ( choose["Events/Jet_electronIdx1"] )
      input->select("Events/Jet_electronIdx1", 	Jet_electronIdx1);
    if ( choose["Events/Jet_electronIdx2"] )
      input->select("Events/Jet_electronIdx2", 	Jet_electronIdx2);
    if ( choose["Events/Jet_eta"] )
      input->select("Events/Jet_eta", 	Jet_eta);
    if ( choose["Events/Jet_genJetIdx"] )
      input->select("Events/Jet_genJetIdx", 	Jet_genJetIdx);
    if ( choose["Events/Jet_hadronFlavour"] )
      input->select("Events/Jet_hadronFlavour", 	Jet_hadronFlavour);
    if ( choose["Events/Jet_hfadjacentEtaStripsSize"] )
      input->select("Events/Jet_hfadjacentEtaStripsSize",
                     Jet_hfadjacentEtaStripsSize);
    if ( choose["Events/Jet_hfcentralEtaStripSize"] )
      input->select("Events/Jet_hfcentralEtaStripSize",
                     Jet_hfcentralEtaStripSize);
    if ( choose["Events/Jet_hfsigmaEtaEta"] )
      input->select("Events/Jet_hfsigmaEtaEta", 	Jet_hfsigmaEtaEta);
    if ( choose["Events/Jet_hfsigmaPhiPhi"] )
      input->select("Events/Jet_hfsigmaPhiPhi", 	Jet_hfsigmaPhiPhi);
    if ( choose["Events/Jet_jetId"] )
      input->select("Events/Jet_jetId", 	Jet_jetId);
    if ( choose["Events/Jet_mass"] )
      input->select("Events/Jet_mass", 	Jet_mass);
    if ( choose["Events/Jet_muEF"] )
      input->select("Events/Jet_muEF", 	Jet_muEF);
    if ( choose["Events/Jet_muonIdx1"] )
      input->select("Events/Jet_muonIdx1", 	Jet_muonIdx1);
    if ( choose["Events/Jet_muonIdx2"] )
      input->select("Events/Jet_muonIdx2", 	Jet_muonIdx2);
    if ( choose["Events/Jet_muonSubtrFactor"] )
      input->select("Events/Jet_muonSubtrFactor", 	Jet_muonSubtrFactor);
    if ( choose["Events/Jet_nConstituents"] )
      input->select("Events/Jet_nConstituents", 	Jet_nConstituents);
    if ( choose["Events/Jet_nElectrons"] )
      input->select("Events/Jet_nElectrons", 	Jet_nElectrons);
    if ( choose["Events/Jet_nMuons"] )
      input->select("Events/Jet_nMuons", 	Jet_nMuons);
    if ( choose["Events/Jet_neEmEF"] )
      input->select("Events/Jet_neEmEF", 	Jet_neEmEF);
    if ( choose["Events/Jet_neHEF"] )
      input->select("Events/Jet_neHEF", 	Jet_neHEF);
    if ( choose["Events/Jet_partonFlavour"] )
      input->select("Events/Jet_partonFlavour", 	Jet_partonFlavour);
    if ( choose["Events/Jet_phi"] )
      input->select("Events/Jet_phi", 	Jet_phi);
    if ( choose["Events/Jet_pt"] )
      input->select("Events/Jet_pt", 	Jet_pt);
    if ( choose["Events/Jet_puId"] )
      input->select("Events/Jet_puId", 	Jet_puId);
    if ( choose["Events/Jet_puIdDisc"] )
      input->select("Events/Jet_puIdDisc", 	Jet_puIdDisc);
    if ( choose["Events/Jet_qgl"] )
      input->select("Events/Jet_qgl", 	Jet_qgl);
    if ( choose["Events/Jet_rawFactor"] )
      input->select("Events/Jet_rawFactor", 	Jet_rawFactor);
    if ( choose["Events/Muon_charge"] )
      input->select("Events/Muon_charge", 	Muon_charge);
    if ( choose["Events/Muon_cleanmask"] )
      input->select("Events/Muon_cleanmask", 	Muon_cleanmask);
    if ( choose["Events/Muon_dxy"] )
      input->select("Events/Muon_dxy", 	Muon_dxy);
    if ( choose["Events/Muon_dxyErr"] )
      input->select("Events/Muon_dxyErr", 	Muon_dxyErr);
    if ( choose["Events/Muon_dxybs"] )
      input->select("Events/Muon_dxybs", 	Muon_dxybs);
    if ( choose["Events/Muon_dz"] )
      input->select("Events/Muon_dz", 	Muon_dz);
    if ( choose["Events/Muon_dzErr"] )
      input->select("Events/Muon_dzErr", 	Muon_dzErr);
    if ( choose["Events/Muon_eta"] )
      input->select("Events/Muon_eta", 	Muon_eta);
    if ( choose["Events/Muon_fsrPhotonIdx"] )
      input->select("Events/Muon_fsrPhotonIdx", 	Muon_fsrPhotonIdx);
    if ( choose["Events/Muon_genPartFlav"] )
      input->select("Events/Muon_genPartFlav", 	Muon_genPartFlav);
    if ( choose["Events/Muon_genPartIdx"] )
      input->select("Events/Muon_genPartIdx", 	Muon_genPartIdx);
    if ( choose["Events/Muon_highPtId"] )
      input->select("Events/Muon_highPtId", 	Muon_highPtId);
    if ( choose["Events/Muon_highPurity"] )
      input->select("Events/Muon_highPurity", 	Muon_highPurity);
    if ( choose["Events/Muon_inTimeMuon"] )
      input->select("Events/Muon_inTimeMuon", 	Muon_inTimeMuon);
    if ( choose["Events/Muon_ip3d"] )
      input->select("Events/Muon_ip3d", 	Muon_ip3d);
    if ( choose["Events/Muon_isGlobal"] )
      input->select("Events/Muon_isGlobal", 	Muon_isGlobal);
    if ( choose["Events/Muon_isPFcand"] )
      input->select("Events/Muon_isPFcand", 	Muon_isPFcand);
    if ( choose["Events/Muon_isStandalone"] )
      input->select("Events/Muon_isStandalone", 	Muon_isStandalone);
    if ( choose["Events/Muon_isTracker"] )
      input->select("Events/Muon_isTracker", 	Muon_isTracker);
    if ( choose["Events/Muon_jetIdx"] )
      input->select("Events/Muon_jetIdx", 	Muon_jetIdx);
    if ( choose["Events/Muon_jetNDauCharged"] )
      input->select("Events/Muon_jetNDauCharged", 	Muon_jetNDauCharged);
    if ( choose["Events/Muon_jetPtRelv2"] )
      input->select("Events/Muon_jetPtRelv2", 	Muon_jetPtRelv2);
    if ( choose["Events/Muon_jetRelIso"] )
      input->select("Events/Muon_jetRelIso", 	Muon_jetRelIso);
    if ( choose["Events/Muon_looseId"] )
      input->select("Events/Muon_looseId", 	Muon_looseId);
    if ( choose["Events/Muon_mass"] )
      input->select("Events/Muon_mass", 	Muon_mass);
    if ( choose["Events/Muon_mediumId"] )
      input->select("Events/Muon_mediumId", 	Muon_mediumId);
    if ( choose["Events/Muon_mediumPromptId"] )
      input->select("Events/Muon_mediumPromptId", 	Muon_mediumPromptId);
    if ( choose["Events/Muon_miniIsoId"] )
      input->select("Events/Muon_miniIsoId", 	Muon_miniIsoId);
    if ( choose["Events/Muon_miniPFRelIso_all"] )
      input->select("Events/Muon_miniPFRelIso_all", 	Muon_miniPFRelIso_all);
    if ( choose["Events/Muon_miniPFRelIso_chg"] )
      input->select("Events/Muon_miniPFRelIso_chg", 	Muon_miniPFRelIso_chg);
    if ( choose["Events/Muon_multiIsoId"] )
      input->select("Events/Muon_multiIsoId", 	Muon_multiIsoId);
    if ( choose["Events/Muon_mvaId"] )
      input->select("Events/Muon_mvaId", 	Muon_mvaId);
    if ( choose["Events/Muon_mvaLowPt"] )
      input->select("Events/Muon_mvaLowPt", 	Muon_mvaLowPt);
    if ( choose["Events/Muon_mvaLowPtId"] )
      input->select("Events/Muon_mvaLowPtId", 	Muon_mvaLowPtId);
    if ( choose["Events/Muon_mvaTTH"] )
      input->select("Events/Muon_mvaTTH", 	Muon_mvaTTH);
    if ( choose["Events/Muon_nStations"] )
      input->select("Events/Muon_nStations", 	Muon_nStations);
    if ( choose["Events/Muon_nTrackerLayers"] )
      input->select("Events/Muon_nTrackerLayers", 	Muon_nTrackerLayers);
    if ( choose["Events/Muon_pdgId"] )
      input->select("Events/Muon_pdgId", 	Muon_pdgId);
    if ( choose["Events/Muon_pfIsoId"] )
      input->select("Events/Muon_pfIsoId", 	Muon_pfIsoId);
    if ( choose["Events/Muon_pfRelIso03_all"] )
      input->select("Events/Muon_pfRelIso03_all", 	Muon_pfRelIso03_all);
    if ( choose["Events/Muon_pfRelIso03_chg"] )
      input->select("Events/Muon_pfRelIso03_chg", 	Muon_pfRelIso03_chg);
    if ( choose["Events/Muon_pfRelIso04_all"] )
      input->select("Events/Muon_pfRelIso04_all", 	Muon_pfRelIso04_all);
    if ( choose["Events/Muon_phi"] )
      input->select("Events/Muon_phi", 	Muon_phi);
    if ( choose["Events/Muon_pt"] )
      input->select("Events/Muon_pt", 	Muon_pt);
    if ( choose["Events/Muon_ptErr"] )
      input->select("Events/Muon_ptErr", 	Muon_ptErr);
    if ( choose["Events/Muon_puppiIsoId"] )
      input->select("Events/Muon_puppiIsoId", 	Muon_puppiIsoId);
    if ( choose["Events/Muon_segmentComp"] )
      input->select("Events/Muon_segmentComp", 	Muon_segmentComp);
    if ( choose["Events/Muon_sip3d"] )
      input->select("Events/Muon_sip3d", 	Muon_sip3d);
    if ( choose["Events/Muon_softId"] )
      input->select("Events/Muon_softId", 	Muon_softId);
    if ( choose["Events/Muon_softMva"] )
      input->select("Events/Muon_softMva", 	Muon_softMva);
    if ( choose["Events/Muon_softMvaId"] )
      input->select("Events/Muon_softMvaId", 	Muon_softMvaId);
    if ( choose["Events/Muon_tightCharge"] )
      input->select("Events/Muon_tightCharge", 	Muon_tightCharge);
    if ( choose["Events/Muon_tightId"] )
      input->select("Events/Muon_tightId", 	Muon_tightId);
    if ( choose["Events/Muon_tkIsoId"] )
      input->select("Events/Muon_tkIsoId", 	Muon_tkIsoId);
    if ( choose["Events/Muon_tkRelIso"] )
      input->select("Events/Muon_tkRelIso", 	Muon_tkRelIso);
    if ( choose["Events/Muon_triggerIdLoose"] )
      input->select("Events/Muon_triggerIdLoose", 	Muon_triggerIdLoose);
    if ( choose["Events/Muon_tunepRelPt"] )
      input->select("Events/Muon_tunepRelPt", 	Muon_tunepRelPt);
    if ( choose["Events/OtherPV_z"] )
      input->select("Events/OtherPV_z", 	OtherPV_z);
    if ( choose["Events/PSWeight"] )
      input->select("Events/PSWeight", 	PSWeight);
    if ( choose["Events/PV_chi2"] )
      input->select("Events/PV_chi2", 	PV_chi2);
    if ( choose["Events/PV_ndof"] )
      input->select("Events/PV_ndof", 	PV_ndof);
    if ( choose["Events/PV_npvs"] )
      input->select("Events/PV_npvs", 	PV_npvs);
    if ( choose["Events/PV_npvsGood"] )
      input->select("Events/PV_npvsGood", 	PV_npvsGood);
    if ( choose["Events/PV_score"] )
      input->select("Events/PV_score", 	PV_score);
    if ( choose["Events/PV_x"] )
      input->select("Events/PV_x", 	PV_x);
    if ( choose["Events/PV_y"] )
      input->select("Events/PV_y", 	PV_y);
    if ( choose["Events/PV_z"] )
      input->select("Events/PV_z", 	PV_z);
    if ( choose["Events/Pileup_gpudensity"] )
      input->select("Events/Pileup_gpudensity", 	Pileup_gpudensity);
    if ( choose["Events/Pileup_nPU"] )
      input->select("Events/Pileup_nPU", 	Pileup_nPU);
    if ( choose["Events/Pileup_nTrueInt"] )
      input->select("Events/Pileup_nTrueInt", 	Pileup_nTrueInt);
    if ( choose["Events/Pileup_pudensity"] )
      input->select("Events/Pileup_pudensity", 	Pileup_pudensity);
    if ( choose["Events/Pileup_sumEOOT"] )
      input->select("Events/Pileup_sumEOOT", 	Pileup_sumEOOT);
    if ( choose["Events/Pileup_sumLOOT"] )
      input->select("Events/Pileup_sumLOOT", 	Pileup_sumLOOT);
    if ( choose["Events/btagWeight_CSVV2"] )
      input->select("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    if ( choose["Events/btagWeight_DeepCSVB"] )
      input->select("Events/btagWeight_DeepCSVB", 	btagWeight_DeepCSVB);
    if ( choose["Events/event"] )
      input->select("Events/event", 	event);
    if ( choose["Events/genTtbarId"] )
      input->select("Events/genTtbarId", 	genTtbarId);
    if ( choose["Events/genWeight"] )
      input->select("Events/genWeight", 	genWeight);
    if ( choose["Events/luminosityBlock"] )
      input->select("Events/luminosityBlock", 	luminosityBlock);
    if ( choose["Events/run"] )
      input->select("Events/run", 	run);

  }

  // A write-only buffer
  eventBuffer(otreestream& stream)
  : input(0),
    output(&stream)
  {
    initBuffers();

    output->add("nGenPart", 	nGenPart);
    output->add("nGenJet", 	nGenJet);
    output->add("nOtherPV", 	nOtherPV);
    output->add("nMuon", 	nMuon);
    output->add("nPSWeight", 	nPSWeight);
    output->add("nElectron", 	nElectron);
    output->add("nJet", 	nJet);
  
    output->add("Events/Electron_charge[nElectron]", 	Electron_charge);
    output->add("Events/Electron_cleanmask[nElectron]",
                 Electron_cleanmask);
    output->add("Events/Electron_convVeto[nElectron]", 	Electron_convVeto);
    output->add("Events/Electron_cutBased[nElectron]", 	Electron_cutBased);
    output->add("Events/Electron_cutBased_HEEP[nElectron]",
                 Electron_cutBased_HEEP);
    output->add("Events/Electron_dEscaleDown[nElectron]",
                 Electron_dEscaleDown);
    output->add("Events/Electron_dEscaleUp[nElectron]",
                 Electron_dEscaleUp);
    output->add("Events/Electron_dEsigmaDown[nElectron]",
                 Electron_dEsigmaDown);
    output->add("Events/Electron_dEsigmaUp[nElectron]",
                 Electron_dEsigmaUp);
    output->add("Events/Electron_deltaEtaSC[nElectron]",
                 Electron_deltaEtaSC);
    output->add("Events/Electron_dr03EcalRecHitSumEt[nElectron]",
                 Electron_dr03EcalRecHitSumEt);
    output->add("Events/Electron_dr03HcalDepth1TowerSumEt[nElectron]",
                 Electron_dr03HcalDepth1TowerSumEt);
    output->add("Events/Electron_dr03TkSumPt[nElectron]",
                 Electron_dr03TkSumPt);
    output->add("Events/Electron_dr03TkSumPtHEEP[nElectron]",
                 Electron_dr03TkSumPtHEEP);
    output->add("Events/Electron_dxy[nElectron]", 	Electron_dxy);
    output->add("Events/Electron_dxyErr[nElectron]", 	Electron_dxyErr);
    output->add("Events/Electron_dz[nElectron]", 	Electron_dz);
    output->add("Events/Electron_dzErr[nElectron]", 	Electron_dzErr);
    output->add("Events/Electron_eCorr[nElectron]", 	Electron_eCorr);
    output->add("Events/Electron_eInvMinusPInv[nElectron]",
                 Electron_eInvMinusPInv);
    output->add("Events/Electron_energyErr[nElectron]",
                 Electron_energyErr);
    output->add("Events/Electron_eta[nElectron]", 	Electron_eta);
    output->add("Events/Electron_genPartFlav[nElectron]",
                 Electron_genPartFlav);
    output->add("Events/Electron_genPartIdx[nElectron]",
                 Electron_genPartIdx);
    output->add("Events/Electron_hoe[nElectron]", 	Electron_hoe);
    output->add("Events/Electron_ip3d[nElectron]", 	Electron_ip3d);
    output->add("Events/Electron_isPFcand[nElectron]", 	Electron_isPFcand);
    output->add("Events/Electron_jetIdx[nElectron]", 	Electron_jetIdx);
    output->add("Events/Electron_jetNDauCharged[nElectron]",
                 Electron_jetNDauCharged);
    output->add("Events/Electron_jetPtRelv2[nElectron]",
                 Electron_jetPtRelv2);
    output->add("Events/Electron_jetRelIso[nElectron]",
                 Electron_jetRelIso);
    output->add("Events/Electron_lostHits[nElectron]", 	Electron_lostHits);
    output->add("Events/Electron_mass[nElectron]", 	Electron_mass);
    output->add("Events/Electron_miniPFRelIso_all[nElectron]",
                 Electron_miniPFRelIso_all);
    output->add("Events/Electron_miniPFRelIso_chg[nElectron]",
                 Electron_miniPFRelIso_chg);
    output->add("Events/Electron_mvaFall17V2Iso[nElectron]",
                 Electron_mvaFall17V2Iso);
    output->add("Events/Electron_mvaFall17V2Iso_WP80[nElectron]",
                 Electron_mvaFall17V2Iso_WP80);
    output->add("Events/Electron_mvaFall17V2Iso_WP90[nElectron]",
                 Electron_mvaFall17V2Iso_WP90);
    output->add("Events/Electron_mvaFall17V2Iso_WPL[nElectron]",
                 Electron_mvaFall17V2Iso_WPL);
    output->add("Events/Electron_mvaFall17V2noIso[nElectron]",
                 Electron_mvaFall17V2noIso);
    output->add("Events/Electron_mvaFall17V2noIso_WP80[nElectron]",
                 Electron_mvaFall17V2noIso_WP80);
    output->add("Events/Electron_mvaFall17V2noIso_WP90[nElectron]",
                 Electron_mvaFall17V2noIso_WP90);
    output->add("Events/Electron_mvaFall17V2noIso_WPL[nElectron]",
                 Electron_mvaFall17V2noIso_WPL);
    output->add("Events/Electron_mvaTTH[nElectron]", 	Electron_mvaTTH);
    output->add("Events/Electron_pdgId[nElectron]", 	Electron_pdgId);
    output->add("Events/Electron_pfRelIso03_all[nElectron]",
                 Electron_pfRelIso03_all);
    output->add("Events/Electron_pfRelIso03_chg[nElectron]",
                 Electron_pfRelIso03_chg);
    output->add("Events/Electron_phi[nElectron]", 	Electron_phi);
    output->add("Events/Electron_photonIdx[nElectron]",
                 Electron_photonIdx);
    output->add("Events/Electron_pt[nElectron]", 	Electron_pt);
    output->add("Events/Electron_r9[nElectron]", 	Electron_r9);
    output->add("Events/Electron_scEtOverPt[nElectron]",
                 Electron_scEtOverPt);
    output->add("Events/Electron_seedGain[nElectron]", 	Electron_seedGain);
    output->add("Events/Electron_sieie[nElectron]", 	Electron_sieie);
    output->add("Events/Electron_sip3d[nElectron]", 	Electron_sip3d);
    output->add("Events/Electron_tightCharge[nElectron]",
                 Electron_tightCharge);
    output->add("Events/Electron_vidNestedWPBitmap[nElectron]",
                 Electron_vidNestedWPBitmap);
    output->add("Events/Electron_vidNestedWPBitmapHEEP[nElectron]",
                 Electron_vidNestedWPBitmapHEEP);
    output->add("Events/Flag_BadChargedCandidateFilter",
                 Flag_BadChargedCandidateFilter);
    output->add("Events/Flag_BadChargedCandidateSummer16Filter",
                 Flag_BadChargedCandidateSummer16Filter);
    output->add("Events/Flag_BadPFMuonDzFilter", 	Flag_BadPFMuonDzFilter);
    output->add("Events/Flag_BadPFMuonFilter", 	Flag_BadPFMuonFilter);
    output->add("Events/Flag_BadPFMuonSummer16Filter",
                 Flag_BadPFMuonSummer16Filter);
    output->add("Events/Flag_CSCTightHalo2015Filter",
                 Flag_CSCTightHalo2015Filter);
    output->add("Events/Flag_CSCTightHaloFilter", 	Flag_CSCTightHaloFilter);
    output->add("Events/Flag_CSCTightHaloTrkMuUnvetoFilter",
                 Flag_CSCTightHaloTrkMuUnvetoFilter);
    output->add("Events/Flag_EcalDeadCellBoundaryEnergyFilter",
                 Flag_EcalDeadCellBoundaryEnergyFilter);
    output->add("Events/Flag_EcalDeadCellTriggerPrimitiveFilter",
                 Flag_EcalDeadCellTriggerPrimitiveFilter);
    output->add("Events/Flag_HBHENoiseFilter", 	Flag_HBHENoiseFilter);
    output->add("Events/Flag_HBHENoiseIsoFilter", 	Flag_HBHENoiseIsoFilter);
    output->add("Events/Flag_HcalStripHaloFilter",
                 Flag_HcalStripHaloFilter);
    output->add("Events/Flag_METFilters", 	Flag_METFilters);
    output->add("Events/Flag_chargedHadronTrackResolutionFilter",
                 Flag_chargedHadronTrackResolutionFilter);
    output->add("Events/Flag_ecalBadCalibFilter", 	Flag_ecalBadCalibFilter);
    output->add("Events/Flag_ecalLaserCorrFilter",
                 Flag_ecalLaserCorrFilter);
    output->add("Events/Flag_eeBadScFilter", 	Flag_eeBadScFilter);
    output->add("Events/Flag_globalSuperTightHalo2016Filter",
                 Flag_globalSuperTightHalo2016Filter);
    output->add("Events/Flag_globalTightHalo2016Filter",
                 Flag_globalTightHalo2016Filter);
    output->add("Events/Flag_goodVertices", 	Flag_goodVertices);
    output->add("Events/Flag_hcalLaserEventFilter",
                 Flag_hcalLaserEventFilter);
    output->add("Events/Flag_hfNoisyHitsFilter", 	Flag_hfNoisyHitsFilter);
    output->add("Events/Flag_muonBadTrackFilter", 	Flag_muonBadTrackFilter);
    output->add("Events/Flag_trkPOGFilters", 	Flag_trkPOGFilters);
    output->add("Events/Flag_trkPOG_logErrorTooManyClusters",
                 Flag_trkPOG_logErrorTooManyClusters);
    output->add("Events/Flag_trkPOG_manystripclus53X",
                 Flag_trkPOG_manystripclus53X);
    output->add("Events/Flag_trkPOG_toomanystripclus53X",
                 Flag_trkPOG_toomanystripclus53X);
    output->add("Events/GenJet_eta[nGenJet]", 	GenJet_eta);
    output->add("Events/GenJet_hadronFlavour[nGenJet]",
                 GenJet_hadronFlavour);
    output->add("Events/GenJet_mass[nGenJet]", 	GenJet_mass);
    output->add("Events/GenJet_partonFlavour[nGenJet]",
                 GenJet_partonFlavour);
    output->add("Events/GenJet_phi[nGenJet]", 	GenJet_phi);
    output->add("Events/GenJet_pt[nGenJet]", 	GenJet_pt);
    output->add("Events/GenPart_eta[nGenPart]", 	GenPart_eta);
    output->add("Events/GenPart_genPartIdxMother[nGenPart]",
                 GenPart_genPartIdxMother);
    output->add("Events/GenPart_mass[nGenPart]", 	GenPart_mass);
    output->add("Events/GenPart_pdgId[nGenPart]", 	GenPart_pdgId);
    output->add("Events/GenPart_phi[nGenPart]", 	GenPart_phi);
    output->add("Events/GenPart_pt[nGenPart]", 	GenPart_pt);
    output->add("Events/GenPart_status[nGenPart]", 	GenPart_status);
    output->add("Events/GenPart_statusFlags[nGenPart]",
                 GenPart_statusFlags);
    output->add("Events/GenVtx_t0", 	GenVtx_t0);
    output->add("Events/GenVtx_x", 	GenVtx_x);
    output->add("Events/GenVtx_y", 	GenVtx_y);
    output->add("Events/GenVtx_z", 	GenVtx_z);
    output->add("Events/Generator_binvar", 	Generator_binvar);
    output->add("Events/Generator_id1", 	Generator_id1);
    output->add("Events/Generator_id2", 	Generator_id2);
    output->add("Events/Generator_scalePDF", 	Generator_scalePDF);
    output->add("Events/Generator_weight", 	Generator_weight);
    output->add("Events/Generator_x1", 	Generator_x1);
    output->add("Events/Generator_x2", 	Generator_x2);
    output->add("Events/Generator_xpdf1", 	Generator_xpdf1);
    output->add("Events/Generator_xpdf2", 	Generator_xpdf2);
    output->add("Events/HLT_IsoMu20", 	HLT_IsoMu20);
    output->add("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1",
                 HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1);
    output->add("Events/HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1",
                 HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1);
    output->add("Events/HLT_IsoMu24", 	HLT_IsoMu24);
    output->add("Events/HLT_IsoMu24_eta2p1", 	HLT_IsoMu24_eta2p1);
    output->add("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1",
                 HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr",
                 HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1);
    output->add("Events/HLT_IsoMu27", 	HLT_IsoMu27);
    output->add("Events/HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
                 HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1);
    output->add("Events/HLT_IsoMu30", 	HLT_IsoMu30);
    output->add("Events/HLT_PFHT1050", 	HLT_PFHT1050);
    output->add("Events/HLT_PFHT180", 	HLT_PFHT180);
    output->add("Events/HLT_PFHT250", 	HLT_PFHT250);
    output->add("Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40",
                 HLT_PFHT300PT30_QuadPFJet_75_60_45_40);
    output->add("Events/HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0",
                 HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0);
    output->add("Events/HLT_PFHT350", 	HLT_PFHT350);
    output->add("Events/HLT_PFHT350MinPFJet15", 	HLT_PFHT350MinPFJet15);
    output->add("Events/HLT_PFHT370", 	HLT_PFHT370);
    output->add("Events/HLT_PFHT380_SixPFJet32", 	HLT_PFHT380_SixPFJet32);
    output->add("Events/HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2",
                 HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2);
    output->add("Events/HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
                 HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2);
    output->add("Events/HLT_PFHT430", 	HLT_PFHT430);
    output->add("Events/HLT_PFHT430_SixPFJet40", 	HLT_PFHT430_SixPFJet40);
    output->add("Events/HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5",
                 HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5);
    output->add("Events/HLT_PFHT500_PFMET100_PFMHT100_IDTight",
                 HLT_PFHT500_PFMET100_PFMHT100_IDTight);
    output->add("Events/HLT_PFHT500_PFMET110_PFMHT110_IDTight",
                 HLT_PFHT500_PFMET110_PFMHT110_IDTight);
    output->add("Events/HLT_PFHT510", 	HLT_PFHT510);
    output->add("Events/HLT_PFHT590", 	HLT_PFHT590);
    output->add("Events/HLT_PFHT680", 	HLT_PFHT680);
    output->add("Events/HLT_PFHT700_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT700_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT700_PFMET95_PFMHT95_IDTight",
                 HLT_PFHT700_PFMET95_PFMHT95_IDTight);
    output->add("Events/HLT_PFHT780", 	HLT_PFHT780);
    output->add("Events/HLT_PFHT800_PFMET75_PFMHT75_IDTight",
                 HLT_PFHT800_PFMET75_PFMHT75_IDTight);
    output->add("Events/HLT_PFHT800_PFMET85_PFMHT85_IDTight",
                 HLT_PFHT800_PFMET85_PFMHT85_IDTight);
    output->add("Events/HLT_PFHT890", 	HLT_PFHT890);
    output->add("Events/HLTriggerFinalPath", 	HLTriggerFinalPath);
    output->add("Events/HLTriggerFirstPath", 	HLTriggerFirstPath);
    output->add("Events/Jet_area[nJet]", 	Jet_area);
    output->add("Events/Jet_bRegCorr[nJet]", 	Jet_bRegCorr);
    output->add("Events/Jet_bRegRes[nJet]", 	Jet_bRegRes);
    output->add("Events/Jet_btagCSVV2[nJet]", 	Jet_btagCSVV2);
    output->add("Events/Jet_btagDeepB[nJet]", 	Jet_btagDeepB);
    output->add("Events/Jet_btagDeepCvB[nJet]", 	Jet_btagDeepCvB);
    output->add("Events/Jet_btagDeepCvL[nJet]", 	Jet_btagDeepCvL);
    output->add("Events/Jet_btagDeepFlavB[nJet]", 	Jet_btagDeepFlavB);
    output->add("Events/Jet_btagDeepFlavCvB[nJet]", 	Jet_btagDeepFlavCvB);
    output->add("Events/Jet_btagDeepFlavCvL[nJet]", 	Jet_btagDeepFlavCvL);
    output->add("Events/Jet_btagDeepFlavQG[nJet]", 	Jet_btagDeepFlavQG);
    output->add("Events/Jet_cRegCorr[nJet]", 	Jet_cRegCorr);
    output->add("Events/Jet_cRegRes[nJet]", 	Jet_cRegRes);
    output->add("Events/Jet_chEmEF[nJet]", 	Jet_chEmEF);
    output->add("Events/Jet_chFPV0EF[nJet]", 	Jet_chFPV0EF);
    output->add("Events/Jet_chHEF[nJet]", 	Jet_chHEF);
    output->add("Events/Jet_cleanmask[nJet]", 	Jet_cleanmask);
    output->add("Events/Jet_electronIdx1[nJet]", 	Jet_electronIdx1);
    output->add("Events/Jet_electronIdx2[nJet]", 	Jet_electronIdx2);
    output->add("Events/Jet_eta[nJet]", 	Jet_eta);
    output->add("Events/Jet_genJetIdx[nJet]", 	Jet_genJetIdx);
    output->add("Events/Jet_hadronFlavour[nJet]", 	Jet_hadronFlavour);
    output->add("Events/Jet_hfadjacentEtaStripsSize[nJet]",
                 Jet_hfadjacentEtaStripsSize);
    output->add("Events/Jet_hfcentralEtaStripSize[nJet]",
                 Jet_hfcentralEtaStripSize);
    output->add("Events/Jet_hfsigmaEtaEta[nJet]", 	Jet_hfsigmaEtaEta);
    output->add("Events/Jet_hfsigmaPhiPhi[nJet]", 	Jet_hfsigmaPhiPhi);
    output->add("Events/Jet_jetId[nJet]", 	Jet_jetId);
    output->add("Events/Jet_mass[nJet]", 	Jet_mass);
    output->add("Events/Jet_muEF[nJet]", 	Jet_muEF);
    output->add("Events/Jet_muonIdx1[nJet]", 	Jet_muonIdx1);
    output->add("Events/Jet_muonIdx2[nJet]", 	Jet_muonIdx2);
    output->add("Events/Jet_muonSubtrFactor[nJet]", 	Jet_muonSubtrFactor);
    output->add("Events/Jet_nConstituents[nJet]", 	Jet_nConstituents);
    output->add("Events/Jet_nElectrons[nJet]", 	Jet_nElectrons);
    output->add("Events/Jet_nMuons[nJet]", 	Jet_nMuons);
    output->add("Events/Jet_neEmEF[nJet]", 	Jet_neEmEF);
    output->add("Events/Jet_neHEF[nJet]", 	Jet_neHEF);
    output->add("Events/Jet_partonFlavour[nJet]", 	Jet_partonFlavour);
    output->add("Events/Jet_phi[nJet]", 	Jet_phi);
    output->add("Events/Jet_pt[nJet]", 	Jet_pt);
    output->add("Events/Jet_puId[nJet]", 	Jet_puId);
    output->add("Events/Jet_puIdDisc[nJet]", 	Jet_puIdDisc);
    output->add("Events/Jet_qgl[nJet]", 	Jet_qgl);
    output->add("Events/Jet_rawFactor[nJet]", 	Jet_rawFactor);
    output->add("Events/Muon_charge[nMuon]", 	Muon_charge);
    output->add("Events/Muon_cleanmask[nMuon]", 	Muon_cleanmask);
    output->add("Events/Muon_dxy[nMuon]", 	Muon_dxy);
    output->add("Events/Muon_dxyErr[nMuon]", 	Muon_dxyErr);
    output->add("Events/Muon_dxybs[nMuon]", 	Muon_dxybs);
    output->add("Events/Muon_dz[nMuon]", 	Muon_dz);
    output->add("Events/Muon_dzErr[nMuon]", 	Muon_dzErr);
    output->add("Events/Muon_eta[nMuon]", 	Muon_eta);
    output->add("Events/Muon_fsrPhotonIdx[nMuon]", 	Muon_fsrPhotonIdx);
    output->add("Events/Muon_genPartFlav[nMuon]", 	Muon_genPartFlav);
    output->add("Events/Muon_genPartIdx[nMuon]", 	Muon_genPartIdx);
    output->add("Events/Muon_highPtId[nMuon]", 	Muon_highPtId);
    output->add("Events/Muon_highPurity[nMuon]", 	Muon_highPurity);
    output->add("Events/Muon_inTimeMuon[nMuon]", 	Muon_inTimeMuon);
    output->add("Events/Muon_ip3d[nMuon]", 	Muon_ip3d);
    output->add("Events/Muon_isGlobal[nMuon]", 	Muon_isGlobal);
    output->add("Events/Muon_isPFcand[nMuon]", 	Muon_isPFcand);
    output->add("Events/Muon_isStandalone[nMuon]", 	Muon_isStandalone);
    output->add("Events/Muon_isTracker[nMuon]", 	Muon_isTracker);
    output->add("Events/Muon_jetIdx[nMuon]", 	Muon_jetIdx);
    output->add("Events/Muon_jetNDauCharged[nMuon]", 	Muon_jetNDauCharged);
    output->add("Events/Muon_jetPtRelv2[nMuon]", 	Muon_jetPtRelv2);
    output->add("Events/Muon_jetRelIso[nMuon]", 	Muon_jetRelIso);
    output->add("Events/Muon_looseId[nMuon]", 	Muon_looseId);
    output->add("Events/Muon_mass[nMuon]", 	Muon_mass);
    output->add("Events/Muon_mediumId[nMuon]", 	Muon_mediumId);
    output->add("Events/Muon_mediumPromptId[nMuon]", 	Muon_mediumPromptId);
    output->add("Events/Muon_miniIsoId[nMuon]", 	Muon_miniIsoId);
    output->add("Events/Muon_miniPFRelIso_all[nMuon]",
                 Muon_miniPFRelIso_all);
    output->add("Events/Muon_miniPFRelIso_chg[nMuon]",
                 Muon_miniPFRelIso_chg);
    output->add("Events/Muon_multiIsoId[nMuon]", 	Muon_multiIsoId);
    output->add("Events/Muon_mvaId[nMuon]", 	Muon_mvaId);
    output->add("Events/Muon_mvaLowPt[nMuon]", 	Muon_mvaLowPt);
    output->add("Events/Muon_mvaLowPtId[nMuon]", 	Muon_mvaLowPtId);
    output->add("Events/Muon_mvaTTH[nMuon]", 	Muon_mvaTTH);
    output->add("Events/Muon_nStations[nMuon]", 	Muon_nStations);
    output->add("Events/Muon_nTrackerLayers[nMuon]", 	Muon_nTrackerLayers);
    output->add("Events/Muon_pdgId[nMuon]", 	Muon_pdgId);
    output->add("Events/Muon_pfIsoId[nMuon]", 	Muon_pfIsoId);
    output->add("Events/Muon_pfRelIso03_all[nMuon]", 	Muon_pfRelIso03_all);
    output->add("Events/Muon_pfRelIso03_chg[nMuon]", 	Muon_pfRelIso03_chg);
    output->add("Events/Muon_pfRelIso04_all[nMuon]", 	Muon_pfRelIso04_all);
    output->add("Events/Muon_phi[nMuon]", 	Muon_phi);
    output->add("Events/Muon_pt[nMuon]", 	Muon_pt);
    output->add("Events/Muon_ptErr[nMuon]", 	Muon_ptErr);
    output->add("Events/Muon_puppiIsoId[nMuon]", 	Muon_puppiIsoId);
    output->add("Events/Muon_segmentComp[nMuon]", 	Muon_segmentComp);
    output->add("Events/Muon_sip3d[nMuon]", 	Muon_sip3d);
    output->add("Events/Muon_softId[nMuon]", 	Muon_softId);
    output->add("Events/Muon_softMva[nMuon]", 	Muon_softMva);
    output->add("Events/Muon_softMvaId[nMuon]", 	Muon_softMvaId);
    output->add("Events/Muon_tightCharge[nMuon]", 	Muon_tightCharge);
    output->add("Events/Muon_tightId[nMuon]", 	Muon_tightId);
    output->add("Events/Muon_tkIsoId[nMuon]", 	Muon_tkIsoId);
    output->add("Events/Muon_tkRelIso[nMuon]", 	Muon_tkRelIso);
    output->add("Events/Muon_triggerIdLoose[nMuon]", 	Muon_triggerIdLoose);
    output->add("Events/Muon_tunepRelPt[nMuon]", 	Muon_tunepRelPt);
    output->add("Events/OtherPV_z[nOtherPV]", 	OtherPV_z);
    output->add("Events/PSWeight[nPSWeight]", 	PSWeight);
    output->add("Events/PV_chi2", 	PV_chi2);
    output->add("Events/PV_ndof", 	PV_ndof);
    output->add("Events/PV_npvs", 	PV_npvs);
    output->add("Events/PV_npvsGood", 	PV_npvsGood);
    output->add("Events/PV_score", 	PV_score);
    output->add("Events/PV_x", 	PV_x);
    output->add("Events/PV_y", 	PV_y);
    output->add("Events/PV_z", 	PV_z);
    output->add("Events/Pileup_gpudensity", 	Pileup_gpudensity);
    output->add("Events/Pileup_nPU", 	Pileup_nPU);
    output->add("Events/Pileup_nTrueInt", 	Pileup_nTrueInt);
    output->add("Events/Pileup_pudensity", 	Pileup_pudensity);
    output->add("Events/Pileup_sumEOOT", 	Pileup_sumEOOT);
    output->add("Events/Pileup_sumLOOT", 	Pileup_sumLOOT);
    output->add("Events/btagWeight_CSVV2", 	btagWeight_CSVV2);
    output->add("Events/btagWeight_DeepCSVB", 	btagWeight_DeepCSVB);
    output->add("Events/event", 	event);
    output->add("Events/genTtbarId", 	genTtbarId);
    output->add("Events/genWeight", 	genWeight);
    output->add("Events/luminosityBlock", 	luminosityBlock);
    output->add("Events/run", 	run);

  }

  void initBuffers()
  {
    Electron	= std::vector<eventBuffer::Electron_s>(23);
    GenJet	= std::vector<eventBuffer::GenJet_s>(50);
    GenPart	= std::vector<eventBuffer::GenPart_s>(233);
    Jet	= std::vector<eventBuffer::Jet_s>(53);
    Muon	= std::vector<eventBuffer::Muon_s>(32);

  }
      
  void read(int entry)
  {
    if ( !input ) 
      { 
        std::cout << "** eventBuffer::read - first  call read-only constructor!"
                  << std::endl;
        assert(0);
      }
    input->read(entry);

    // clear indexmap
    for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
    ++item)
    item->second.clear();
  }

  void select(std::string objname)
  {
    indexmap[objname] = std::vector<int>();
  }

  void select(std::string objname, int index)
  {
    try
     {
       indexmap[objname].push_back(index);
     }
    catch (...)
     {
       std::cout << "** eventBuffer::select - first call select(""" 
                 << objname << """)" 
                 << std::endl;
       assert(0);
    }
  }

 void ls()
 {
   if( input ) input->ls();
 }

 int size()
 {
   if( input ) 
     return input->size();
   else
     return 0;
 }

 void close()
 {
   if( input )   input->close();
   if( output ) output->close();
 }

 // --- indexmap keeps track of which objects have been flagged for selection
 std::map<std::string, std::vector<int> > indexmap;

 // to read events
 itreestream* input;

 // to write events
 otreestream* output;

 // switches for choosing branches
 std::map<std::string, bool> choose;

}; 
#endif
