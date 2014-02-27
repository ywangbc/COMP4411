//
// ContrastBrush.cpp
//
// The implementation of Contrast Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ContrastBrush.h"

extern float frand();

ContrastBrush::ContrastBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ContrastBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ContrastBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ContrastBrush::BrushMove  document is NULL\n" );
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

void ContrastBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

void ContrastBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[3];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	// Convert the color to a Contrast
	for (int i = 0; i < 3; ++i) {
		color[i] = GLubyte(255 - color[i]);
	}
	glColor3ubv( color );
}

