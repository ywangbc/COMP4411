//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include <cmath>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	/* (Tim) Save Paint for Undo [START] */
	savePaintForUndo();
	/* (Tim) Save Paint for Undo [END] */

	int size = pDoc->getSize();



	glPointSize(size);
	pDoc->current=target;

	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
	//Processing LineWidth STARTED
	int width=GetDocument()->getLineWidth();
	double halfWidth=width/2.0;   //converted to double in case width is 1
	//Processing LineWIdth ENDED

	//Processsing LineLength STARTED
	int length;
	glGetIntegerv(GL_POINT_SIZE ,&length);
	double halfLength = length/2.0;  //Need to be converted to double. Or nothing will be drawn when length is 1
	//Processing LineLength ENDED
	
	int windowH=dlg->m_mainWindow->h();
	int drawHeight=dlg->m_paintView->GetDrawHeight();

	int startCol=dlg->m_paintView->GetStartCol();
	int endCol=dlg->m_paintView->GetEndCol();
	int startRow=dlg->m_paintView->GetStartRow()+windowH-drawHeight-25;
	int endRow=startRow+drawHeight;
	//Processing LineAngle STARTED
	int angle = 0;

	switch(pDoc->lineDirectPattern)
	{
	case STROKE_SLIDER:
	{
		angle= pDoc->getLineAngle();
	}
		break;
	case STROKE_GRAD:
	{
		int x=target.x-startCol;
		int y=target.y-startRow;
		int width=pDoc->m_nWidth;
		int height=pDoc->m_nHeight;
		if(x<=0||x>width)
		{
			angle=90;
		}
		else if(y<=0||y>height)
		{
			angle=0;
		}
		else
		{
			angle= pDoc->m_ucAngle[x+y*width];
		}
	}
		break;
	case STROKE_BRUSH:
	{
		double xDiff=target.x-(pDoc->current.x);
		double yDiff=target.y-(pDoc->current.y);

		pDoc->current=target;

		if(xDiff==0) angle=90;
		else
		{
			angle = atan2(yDiff,xDiff)/(2*PI)*360;
		}
	}
		break;
	default:
		printf("No such brush exist\n");
	}

	double mathAngle=(angle%360)/360.0*2*PI;
	double cosV=cos(mathAngle);
	double sinV=sin(mathAngle);
	//Processing LineAngle ENDED




	double axis[8];
	axis[0]=target.x-halfLength*cosV-halfWidth*sinV;
	axis[1]=target.y-halfLength*sinV+halfWidth*cosV;
	axis[2]=target.x-halfLength*cosV+halfWidth*sinV;
	axis[3]=target.y-halfLength*sinV-halfWidth*cosV;
	axis[4]=target.x+halfLength*cosV+halfWidth*sinV;
	axis[5]=target.y+halfLength*sinV-halfWidth*cosV;
	axis[6]=target.x+halfLength*cosV-halfWidth*sinV;
	axis[7]=target.y+halfLength*sinV+halfWidth*cosV;


	for(int i=0;i<8;i+=2)
	{
		if(axis[i]<startCol) axis[i]=startCol;
		if(axis[i]>endCol) axis[i]=endCol;
	}
	for(int i=1;i<8;i+=2)
	{
		if(axis[i]<startRow) axis[i]=startRow;
		if(axis[i]>endRow) axis[i]=endRow;
	}

	glBegin( GL_POLYGON );
		SetColor( source );
		glVertex2d( axis[0], axis[1]);
		glVertex2d( axis[2], axis[3]);
		glVertex2d( axis[4], axis[5]);
		glVertex2d( axis[6], axis[7]);
	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

