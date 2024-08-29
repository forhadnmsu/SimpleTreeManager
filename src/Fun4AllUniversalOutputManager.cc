#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHNode.h>
#include <phool/PHNodeIOManager.h>
#include <interface_main/SQEvent.h>
#include <interface_main/SQSpillMap.h>
#include <interface_main/SQHitVector.h>
#include "Fun4AllUniversalOutputManager.h"
using namespace std;

Fun4AllUniversalOutputManager::Fun4AllUniversalOutputManager(const std::string &myname)
  : Fun4AllOutputManager(myname),
    m_file(0),
    m_tree(0),
    m_tree_name("tree"),
    m_file_name("output.root"),
    m_evt(0),
    m_sp_map(0),
    m_hit_vec(0)
{
 ;
}

Fun4AllUniversalOutputManager::~Fun4AllUniversalOutputManager() {
    CloseFile();
}

void Fun4AllUniversalOutputManager::OpenFile(PHCompositeNode* startNode) {
if (m_file && m_tree) {
        std::cout << "File and tree already opened, skipping." << std::endl;
        return;
    }

std::cout << "Fun4AllUniversalOutputManager::OpenFile(): Attempting to open file: " << m_file_name << " with tree: " << m_tree_name << std::endl;

m_file = new TFile(m_file_name.c_str(), "RECREATE");
if (!m_file || m_file->IsZombie()) {
    std::cerr << "Error: Could not create file " << m_file_name << std::endl;
    exit(1);
} else {
    std::cout << "File " << m_file->GetName() << " opened successfully." << std::endl;
}
timer.Start();
m_file->SetCompressionAlgorithm(ROOT::kLZMA);
//m_file->SetCompressionAlgorithm(ROOT::kZLIB);
m_file->SetCompressionLevel(1);

m_tree = new TTree(m_tree_name.c_str(), "Tree for storing events");
if (!m_tree) {
    std::cerr << "Error: Could not create tree " << m_tree_name << std::endl;
    exit(1);
} else {
    std::cout <<  m_tree->GetName() << " created successfully." << std::endl;
}


    m_tree->Branch("RunID", &RunID, "RunID/I");
    m_tree->Branch("SpillID", &SpillID, "SpillID/I");
    m_tree->Branch("EventID", &EventID, "EventID/I");
    m_tree->Branch("RFID", &RFID, "RFID/I");
    m_tree->Branch("TurnID", &TurnID, "TurnID/I");
    m_tree->Branch("Intensity", Intensity, "Intensity[33]/I");
    m_tree->Branch("trig_bits", &trig_bits, "trig_bits/I");
    m_tree->Branch("list_hit", &list_hit);
   m_tree->SetBasketSize("*", 64000);  // 64 KB
if (!m_evt) {
        m_evt = findNode::getClass<SQEvent>(startNode, "SQEvent");
        m_hit_vec = findNode::getClass<SQHitVector>(startNode, "SQHitVector");
        //m_sp_map = findNode::getClass<SQSpillMap>(startNode, "SQSpillMap");
        //m_trig_hit_vec = findNode::getClass<SQHitVector>(startNode, "SQTriggerHitVector");
        if (!m_evt) {
            cout << PHWHERE << "Cannot find the SQ data nodes. Abort." << endl;
            exit(1);
        }   
    }
}

int Fun4AllUniversalOutputManager::Write(PHCompositeNode* startNode) {
    //event_count++; 
    //cout<< "processed "<< event_count << " events" <<endl;

    if (!m_file || !m_tree) {
        OpenFile(startNode);  // Call OpenFile() if the file or tree is not initialized
    }
	//using SQEvent
	RunID =  m_evt->get_run_id(); // SQRun class can be used here 
	SpillID= m_evt->get_spill_id();
	RFID = m_evt->get_qie_rf_id();
	EventID= m_evt->get_event_id();
	TurnID = m_evt->get_qie_turn_id ();
	trig_bits= m_evt->get_trigger(); 

	for (int i = -16; i <= 16; ++i) {
    		//cout << "intensity: " << m_evt->get_qie_rf_intensity(i) << endl;
		Intensity[i+16]= m_evt->get_qie_rf_intensity(i);
	}
     list_hit.clear();
     if (m_hit_vec) {
            for (int ihit = 0; ihit < m_hit_vec->size(); ++ihit) {
                SQHit* hit =m_hit_vec->at(ihit);
		    HitData ht;
                    ht.detector_id = hit->get_detector_id();
                    ht.element_id = hit->get_element_id();
                    ht.tdc_time = hit->get_tdc_time();
                    ht.drift_distance =hit-> get_drift_distance();
                    list_hit.push_back(ht);
        }
    }
    m_tree->Fill();
    return 0;
}

void Fun4AllUniversalOutputManager::CloseFile() {
if (!m_file) return;
    m_file->Write("", TObject::kOverwrite); 
    std::cout << "Fun4AllUniversalOutputManager::CloseFile(): Closing file: " << m_file_name << std::endl;
    m_file->Close();
    timer.Stop();
    double compressionTime = timer.RealTime();
    std::cout << "Compression time: " << compressionTime << " seconds" << std::endl;

    delete m_file;
    m_file = nullptr;
}
