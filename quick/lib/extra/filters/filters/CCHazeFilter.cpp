#include "CCHazeFilter.h"

NS_CC_EXT_BEGIN

//================== HazeFilter

HazeFilter* HazeFilter::create()
{
	HazeFilter* __filter = new HazeFilter();
	__filter->autorelease();
	return __filter;
}

HazeFilter* HazeFilter::create(float $hazeDistance, float $slope)
{
	HazeFilter* __filter = HazeFilter::create();
	__filter->setParameter($hazeDistance, $slope);
	return __filter;
}

HazeFilter::HazeFilter()
: _hazeDistance(0.f)
, _slope(0.f)
{
	this->shaderName = kCCFilterShader_haze;
}

GLProgram* HazeFilter::loadShader()
{
	GLProgram* __p = new GLProgram();
	//CCLOG("HazeFilter::loadShader, program:%d", __p);
	__p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_haze_frag);
	return __p;
}

void HazeFilter::setParameter(float $hazeDistance, float $slope)
{
	_hazeDistance = MIN(0.5f, MAX($hazeDistance, -0.5f));
	_slope = MIN(0.5f, MAX($slope, -0.5f));
	initProgram();
}

void HazeFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("HazeFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void HazeFilter::setUniforms(GLProgram* $cgp)
{
	int __hazeDistance = $cgp->getUniformLocationForName("u_hazeDistance");
	int __slope = $cgp->getUniformLocationForName("u_slope");
	//CCLOG("HazeFilter::setUniforms %d, %d", __hazeDistance, __slope);
	$cgp->setUniformLocationWith1f(__hazeDistance, _hazeDistance);
	$cgp->setUniformLocationWith1f(__slope, _slope);
	//CCLOG("HazeFilter::setUniforms _hazeDistance:%.5f, _slope:%.5f", _hazeDistance, _slope);
}
NS_CC_EXT_END
