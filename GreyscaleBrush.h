//
// GrayBrush.h
//
// The header file for Gray Brush. 
//

#ifndef GREYSCALEBRUSH_H
#define GREYSCALEBRUSH_H

#include "ImpBrush.h"

class GreyscaleBrush : public ImpBrush
{
public:
	GreyscaleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
	void GreyscaleBrush::SetColor (const Point);
};

#endif