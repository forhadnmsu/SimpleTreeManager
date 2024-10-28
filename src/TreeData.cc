#include "TreeData.h"
using namespace std;

EventData::EventData()
  : run_id(0)
  , spill_id(0)
  , event_id(0)
  , trig_bits(0)
  , rf_id(0)
{
;
/* for (int ii = 0; ii < 5; ii++) {
    //fpga_bits [ii] = 0;
    //nim_bits [ii] = 0;
  }
*/
}

HitData::HitData()
  : detector_id(0)
  , element_id(0)
  , tdc_time(0)
  , drift_distance(0)
{
  ;
}

