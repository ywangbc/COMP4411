//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	int windowH=dlg->m_mainWindow->h();
	int drawHeight=dlg->m_paintView->GetDrawHeight();

	int startCol=dlg->m_paintView->GetStartCol();
	int endCol=dlg->m_paintView->GetEndCol();
	int startRow=dlg->m_paintView->GetStartRow()+windowH-drawHeight-25;
	int endRow=startRow+drawHeight;

	
	int x=target.x;
	int y=target.y;

	

	if(x<startCol)
	{
		x=startCol;
	}
	if(x>endCol)
	{
		x=endCol;
	}
	if(y<startRow)
	{
		y=startRow;
	}
	if(y>endRow)
	{
		y=endRow;
	}



	glBegin( GL_POINTS );
		SetColor( source );

		glVertex2d(x, y );

	glEnd();
}

void PointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

