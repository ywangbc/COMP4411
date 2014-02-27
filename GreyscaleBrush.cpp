//
// GreyscaleBrush.cpp
//
// The implementation of Greyscale Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "GreyscaleBrush.h"

extern float frand();

GreyscaleBrush::GreyscaleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void GreyscaleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	/* (Tim) Save Paint for Undo [START] */
	savePaintForUndo();
	/* (Tim) Save Paint for Undo [END] */

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void GreyscaleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	int size;
	glGetIntegerv(GL_POINT_SIZE ,&size);
	double halfSize=size/2.0;
	double startXS=source.x-halfSize;
	double startYS=source.y-halfSize;
	double startXT=target.x-halfSize;
	double startYT=target.y-halfSize;


	glPointSize(1);

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			int seed = rand()%50;
			if(seed<25) 
			{
				Point newS=Point(startXS+i,startYS+j);
				Point newT=Point(startXT+i,startYT+j);
				PointBrushMove(newS, newT);
			}
		}

	glPointSize(float(size));
}

void GreyscaleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

void GreyscaleBrush::PointBrushMove( const Point source, const Point target )
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

		//GLfloat pixels[4];
		//glReadPixels(source.x,source.y,1,1,GL_RGBA,GL_FLOAT,&pixels);
		//glColor4fv(pixels);
		SetColor(source);

		glVertex2d(x, y );


	glEnd();
}

void GreyscaleBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[3];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	// Convert the color to a greyscale
	float brightness = 2.0;
	float gray = (color[0]/255.0*0.299 + color[1]/255.0*0.587 + color[2]/255.0*0.114)/3.0 * brightness;
	gray = (gray > 1.0) ? 1.0 : gray;
	glColor3f( gray, gray, gray );
}

