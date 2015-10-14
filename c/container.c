#include <stdio.h>

typedef int ArrayType[4];
#define ARRAY_TYPE_INITIALIZER	{0, 0, 0, 0}

typedef struct {
	int				y;
	ArrayType		sArrayType;
} SimpleStructure;
#define SIMPLE_STRUCTURE_INITIALIZER	{0, ARRAY_TYPE_INITIALIZER}

typedef struct {
	int					x;
	SimpleStructure		sSimpleStructure;
} CompositeStructure;
#define COMPOSITE_STRUCTURE_INITIALIZER	{0, SIMPLE_STRUCTURE_INITIALIZER}

int main(void)
{
	CompositeStructure sCompositeStructure = COMPOSITE_STRUCTURE_INITIALIZER;
	return 0;
}
