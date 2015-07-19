#ifndef CBM_ADJ_LAYER_H
#define CBM_ADJ_LAYER_H

#include "common.h"
#include <row.h>

namespace cbm {

class AdjLayer
{
public:
	AdjLayer();
	AdjLayer(long id);
	AdjLayer(soci::row& rs);
	std::string getSqlInsert() const;
	std::string getSqlUpdate() const;
	std::string getSqlDelete() const;
	long getId() const;
	void setId(const long& value);
	WorkSurfPtr getWorkSurf() const;
	void setWorkSurf(const WorkSurfPtr& value);
	CoalPtr getCoal() const;
	void setCoal(const CoalPtr& value);
	long getLayerNum() const;
	void setLayerNum(const long& value);
	double getLayerH() const;
	void setLayerH(const double& value);
	double getLayerHp() const;
	void setLayerHp(const double& value);
	long getLayerCaveZone() const;
	void setLayerCaveZone(const long& value);

private:
	long adj_layer_id;
	WorkSurfPtr work_surf;
	CoalPtr coal;
	long layer_num;
	double layer_h;
	double layer_hp;
	long layer_cave_zone;

}; // class AdjLayer

} // namespace cbm

#endif // CBM_ADJ_LAYER_H
