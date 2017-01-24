#pragma once
#include "Renderable.h"

namespace glutframework
{

class Grid : public Renderable
{

public:
	Grid( float size=1.0f );
	virtual ~Grid();
	
	virtual void draw() const;

private:
	float size;
};

};