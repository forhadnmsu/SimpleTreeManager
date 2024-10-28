#ifndef _TREE_DATA__H_
#define _TREE_DATA__H_
#include <phool/PHObject.h>

struct EventData {
  int  run_id;
  int  spill_id;
  int  event_id;
  int trig_bits; 
  int rf_id;
  //TMatrixD *matrix; 
  EventData();
  virtual ~EventData() {
/*if (matrix) delete matrix*/;} 
  ClassDef(EventData, 1); 
};

struct HitData {
  unsigned int    detector_id;    
  unsigned int    element_id;     
  double tdc_time;       
  double drift_distance; 

  HitData();
  virtual ~HitData() {;}
  ClassDef(HitData, 1);
};
typedef std::vector<HitData> HitList;
#endif /* _TREE_DATA__H_ */
