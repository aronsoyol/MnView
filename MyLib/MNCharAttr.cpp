#include "StdAfx.h"
#include "MNCharAttr.h"


MNCharAttr::MNCharAttr(void):
	bgColor			(RGB(255,255,255)),
	fgColor			(RGB(0  ,  0,  0)),
	fontIndex		(0		),
	size			(20		),
	selcted			(false	),
	bold			(false	),
	italic			(false	),
	underLine		(false	),
	isMonCtrlChar	(false  )
{

}
MNCharAttr::MNCharAttr(const MNCharAttr& src):
	bgColor		(src.bgColor	),
	fgColor		(src.fgColor	),
	fontIndex	(src.fontIndex	),
	size		(src.size		),
	selcted		(src.selcted	),
	bold		(src.bold		),
	italic		(src.italic		),
	underLine   (src.underLine	),
	isMonCtrlChar		(src.isMonCtrlChar		)
{

}

MNCharAttr::~MNCharAttr(void)
{
}
bool MNCharAttr::operator == (const MNCharAttr& src)
{
	if(bgColor	== src.bgColor
	&& fgColor	== src.fgColor
	&& fontIndex== src.fontIndex
	&& size		== src.size
	&& selcted	== src.selcted
	&& bold		== src.bold
	&& italic	== src.italic
	&& underLine== src.underLine 
	&& isMonCtrlChar   == src.isMonCtrlChar 
	)
	return true;
	else return false;
}
bool MNCharAttr::operator != (const MNCharAttr& src)
{
	if(	   bgColor	!= src.bgColor
		||fgColor	!= src.fgColor
		||fontIndex	!= src.fontIndex
		||size		!= src.size
		||selcted	!= src.selcted
		||bold		!= src.bold
		||italic	!= src.italic
		||underLine != src.underLine 
		||isMonCtrlChar   == src.isMonCtrlChar 
	)
	return true;
	else return false;
}