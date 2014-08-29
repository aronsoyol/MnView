#pragma once
#include "stdafx.h"
class Exception
{

};
class MnException :public Exception
{

};
class UspException:public Exception
{

};
class UspAllocateMemFaildException :public  UspException
{

};
class UspShapeRunException :public  UspException
{

};
class UspPlaceRunException :public  UspException
{

};
class UspBreakRunException :public  UspException
{

};
