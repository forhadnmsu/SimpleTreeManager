#ifndef _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_
#define _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_

#include <fun4all/Fun4AllOutputManager.h>
#include <string>
#include <vector>
#include <map>
#include "TreeData.h"
#include <TStopwatch.h>

class TFile;
class TTree;
class PHCompositeNode;
class SQEvent;
class SQSpillMap;
class SQHitVector;
class SQMCEvent;


class Fun4AllUniversalOutputManager : public Fun4AllOutputManager {
public:
    int event_count =0;
    bool fileOpened; 
    Fun4AllUniversalOutputManager(const std::string &myname = "UNIVERSALOUT");
    virtual ~Fun4AllUniversalOutputManager();

    void SetTreeName(const std::string& name) { m_tree_name = name; }
    void SetFileName(const std::string& name) { m_file_name = name; }
    virtual int Write(PHCompositeNode* startNode);
    void SetCompression(const std::string& algo, int level);
    static void SetFileCompression(TFile* file, const std::string& algo, int level);
   
    void SetBasketSize(int size) { m_basket_size = size; }
    void SetAutoFlush(int flush) { m_auto_flush = flush; }
    void SetCompressionLevel(int level) { m_compression_level = level; }
    void SetMCMode(bool enable) { m_mc_mode = enable; }

    TStopwatch timer;


protected:
    //void OpenFile();
    void CloseFile();
    void OpenFile(PHCompositeNode* startNode);

private:
    std::string m_tree_name;
    std::string m_file_name;
    std::string m_dir_base;
   
    TFile* m_file;
    TTree* m_tree;
   
    SQMCEvent* mi_evt_true;
    SQEvent* m_evt;
    SQSpillMap* m_sp_map;
    SQHitVector* m_hit_vec;
    
  int trig_bits;
  int RunID;
  int SpillID;
  int EventID;
  int RFID;
  int TurnID;
  int Intensity[33];
  int m_basket_size;
  int m_auto_flush;
  int m_compression_level;


  bool m_mc_mode;

  std::string m_compression_algo = "LZMA";

  HitList list_hit;
  EventData  evt;
};

#endif /* _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_ */

