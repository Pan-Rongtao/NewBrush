#pragma once
#include "newbrush/core/Def.h"

namespace nb {

class NB_API NoneCopyable
{
public:
	NoneCopyable(const NoneCopyable &rhs) = delete;
	NoneCopyable(NoneCopyable &&rhs) = delete;
	NoneCopyable &operator=(const NoneCopyable &rhs) = delete;
	NoneCopyable &operator=(const NoneCopyable &&rhs) = delete;

protected:
	NoneCopyable() = default;
	virtual ~NoneCopyable() = default;
};

}