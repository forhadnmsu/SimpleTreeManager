#ifndef _TREE_DATA__H_
#define _TREE_DATA__H_
#include <phool/PHObject.h>

struct HitData {
  int    hit_id;         
  int    detector_id;    
  int    element_id;     
  double tdc_time;       
  double drift_distance; 

  HitData();
  virtual ~HitData() {;}
  ClassDef(HitData, 1);
};
typedef std::vector<HitData> HitList;

#endif /* _TREE_DATA__H_ */
