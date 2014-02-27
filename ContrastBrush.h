//
// ContrastBrush.h
//
// The header file for Contrast Brush. 
//

#ifndef CONTRASTBRUSH_H
#define CONTRASTBRUSH_H

#include "ImpBrush.h"

class ContrastBrush : public ImpBrush
{
public:
	ContrastBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	void PointBrushMove( const Point source, const Point target );
	char* BrushName( void );
	void ContrastBrush::SetColor (const Point);
};

#endif