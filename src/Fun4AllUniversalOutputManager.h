#ifndef _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_
#define _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_

#include <fun4all/Fun4AllOutputManager.h>
#include <string>
#include <vector>
#include <map>
#include "TreeData.h"

class TFile;
class TTree;
class PHCompositeNode;
class SRawEvent;
class SQEvent;
class SQSpillMap;
class SQHitVector;
class DbSvc;


class Fun4AllUniversalOutputManager : public Fun4AllOutputManager {
public:
    Fun4AllUniversalOutputManager(const std::string &myname = "UNIVERSALOUT");
    virtual ~Fun4AllUniversalOutputManager();

    void SetTreeName(const std::string& name) { m_tree_name = name; }
    void SetFileName(const std::string& name) { m_file_name = name; }
    virtual int Write(PHCompositeNode* startNode);

protected:
    void OpenFile();
    void CloseFile();

private:
    std::string m_tree_name;
    std::string m_file_name;
    std::string m_dir_base;
   
    TFile* m_file;
    TTree* m_tree;

    SQEvent* m_evt;
    SQSpillMap* m_sp_map;
    SQHitVector* m_hit_vec;
    SRawEvent* m_sraw;

  int trig_bits;
  int RunID;
  int SpillID;
  int EventID;
  int RFID;
  int TurnID;
  int Intensity[33];

    HitList list_hit;
};

#endif /* _FUN4ALL_UNIVERSAL_OUTPUT_MANAGER__H_ */

