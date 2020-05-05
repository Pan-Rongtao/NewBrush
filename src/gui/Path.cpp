#include "newbrush/gui/Path.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

std::shared_ptr<MetaObject> Path::getMetaObject()
{
	auto meta = MetaObject::get<Path, Shape>("Shape", "Path", "�켣����״��һ�֣����������⿪��·����", [] {return std::make_shared<Path>(); });
	return meta;
}
