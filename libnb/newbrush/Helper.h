#pragma once
#include "newbrush/Node2D.h"

namespace nb
{

class NB_API TreeHelper
{
public:
	static Node2D *getRoot(Node2D *node);

	static Point getWolrdOffset(Node2D *node);

	static std::vector<ref<Node2D>> getAllChildren(ref<Node2D> node);

	//ģ�������е��ӽڵ����ƶ���Ψһ�ģ�������
	static ref<Node> find(ref<Node> node, const std::string &name);

};

}