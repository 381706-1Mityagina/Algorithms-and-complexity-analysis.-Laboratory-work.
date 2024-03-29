//---------------------------//
// ---- NAIVE ALGORITHM ---- //
//---------------------------//
#include "line_segment.cpp"

enum IntersectionType 
{
    NotIntersected = 0,
	IntersectedInPoint = 1,
	IntersectedInSegment = 2,
};

struct Result 
{
	IntersectionType type;
	MyVector point;
	LineSegment lineSegment;

	void SetResult(IntersectionType type_, const MyVector& point_, const LineSegment& lineSegment_);
};

double Determinant(const MyVector& v1, const MyVector& v2, const MyVector& v3);

// Проверяет что все координаты v1 больше или равны координат v2
bool CheckBoundingBox(const MyVector& v1, const MyVector& v2);


// Проверяет как лежат два отрезка относительно друг друга:
// лежат ли вершины отрезка seg2 по одну сторону от прямой проходящей через отрезок seg1
// возвращает true - если лежат по разные стороны
//					или если хотя бы одна из вершин лежит на самой прямой
// возвращает false - иначе
bool CheckCrossProducts(const LineSegment& seg1, const LineSegment& seg2, const Context& context);

// Функция находящая пересечение двух отрезков seg1 и seg2
// oVector - точка пересечения в случае если отрезки пересекаются в точке
// oSegment - отрезок пересечения в случае если отрезки пересекаются по отрезку
Result Intersect(const LineSegment& seg1, const LineSegment& seg2, const Context& context);

// --------------------------------------------------------------------------
void Result::SetResult(IntersectionType type_, const MyVector& point_, const LineSegment& lineSegment_) 
{
	type = type_;
	point = point_;
	lineSegment = lineSegment_;
}

double Determinant(const MyVector& v1, const MyVector& v2, const MyVector& v3) 
{
	double x1 = v1.GetX();
	double x2 = v2.GetX();
	double x3 = v3.GetX();

	double y1 = v1.GetY();
	double y2 = v2.GetY();
	double y3 = v3.GetY();

	double z1 = v1.GetZ();
	double z2 = v2.GetZ();
	double z3 = v3.GetZ();

	return x1*(y2*z3-z2*y3) - y1*(x2*z3-z2*x3) + z1*(x2*y3-y2*x3);
}

// -------------------------------------------------------------------------------------------------
// Проверяет что все координаты v1 больше или равны координат v2
bool CheckBoundingBox(const MyVector& v1, const MyVector& v2) 
{
	return ( (v1.GetX() >= v2.GetX()) && (v1.GetY() >= v2.GetY()) && (v1.GetZ() >= v2.GetZ()));
}

// -------------------------------------------------------------------------------------------------
// Проверяет как лежат два отрезка относительно друг друга:
// лежат ли вершины отрезка seg2 по одну сторону от прямой проходящей через отрезок seg1
// возвращает true - если лежат по разные стороны
//					или если хотя бы одна из вершин лежит на самой прямой
// возвращает false - иначе
bool CheckCrossProducts(const LineSegment& seg1, const LineSegment& seg2, const Context& context) 
{
	// Составляем векторы для которых будем считать векторное произведения
	MyVector v13 = seg2.GetStart() - seg1.GetStart();
	MyVector v14 = seg2.GetEnd() - seg1.GetStart();
	MyVector v12 = seg1.GetEnd() - seg1.GetStart();

	// Считаем векторное произведение
	MyVector cross_product1 = CrossProduct(v13, v12);
	MyVector cross_product2 = CrossProduct(v14, v12);

	// проверка сонаправленности векторов
	if (!context.EqualToZero(cross_product1.GetX()) && !context.EqualToZero(cross_product2.GetX()))
		return cross_product1.GetX() * cross_product2.GetX() < 0;
	else if (!context.EqualToZero(cross_product1.GetY()) && !context.EqualToZero(cross_product2.GetY()))
		return cross_product1.GetY() * cross_product2.GetY() < 0;
	else if (!context.EqualToZero(cross_product1.GetZ()) && !context.EqualToZero(cross_product2.GetZ()))
		return cross_product1.GetZ() * cross_product2.GetZ() < 0;

	return true; // случай когда вершина лежит на прямой проходящей через отрезок
}

// -------------------------------------------------------------------------------------------------
// Функция находящая пересечение двух отрезков seg1 и seg2
// oVector - точка пересечения в случае если отрезки пересекаются в точке
// oSegment - отрезок пересечения в случае если отрезки пересекаются по отрезку
Result Intersect(const LineSegment& seg1, const LineSegment& seg2, const Context& context) 
{

	MyVector oVector;
	LineSegment oSegment;
	Result result;

	// Алгоритм проверки пересечения двух отрезков:
	// 1 проверяем что отрезки лежат в одной плоскости
	// 2 проверяем что пересекаются их ограничивающие параллелепипеды
	// 3 для каждого из двух отрезков проверяем что его концы лежат по разные стороны
	//	от прямой проходящей через другой отрезок

	MyVector v1 = seg1.GetStart();
	MyVector v2 = seg1.GetEnd();
	MyVector v3 = seg2.GetStart();
	MyVector v4 = seg2.GetEnd();

	// проверяем что отрезки лежат в одной плоскости
	if (fabs(Determinant(v4-v1, v2-v1, v3-v1)) > context.precision) 
	{
        result.SetResult(IntersectionType::NotIntersected, oVector, oSegment);
		return result;
	}
	else 
	{
		// проверяем что отрезки лежат вблизи друг друга
		// для каждого из отрезков считаем две точки составленные из минимальных и максимальных координат концов
		MyVector box1_min = MyVector(min(v1.GetX(),v2.GetX()), min(v1.GetY(),v2.GetY()), min(v1.GetZ(),v2.GetZ()));
		MyVector box1_max = MyVector(max(v1.GetX(),v2.GetX()), max(v1.GetY(),v2.GetY()), max(v1.GetZ(),v2.GetZ()));
		MyVector box2_min = MyVector(min(v3.GetX(),v4.GetX()), min(v3.GetY(),v4.GetY()), min(v3.GetZ(),v4.GetZ()));
		MyVector box2_max = MyVector(max(v3.GetX(),v4.GetX()), max(v3.GetY(),v4.GetY()), max(v3.GetZ(),v4.GetZ()));

		if (CheckBoundingBox(box1_max, box2_min) && (CheckBoundingBox(box2_max, box1_min)))	
		{ ///2

			if (CheckCrossProducts(seg1, seg2, context) && CheckCrossProducts(seg2, seg1, context)) 
			{ ///3

				auto cp1 = CrossProduct(v3-v1, v4-v1);
				auto cp2 = CrossProduct(v3-v2, v4-v2);

				if ((cp1.GetLength() <= context.precision)&&(cp2.GetLength() <= context.precision)) 
				{  //случай когда отрезки лежат на одной прямой
					MyVector oSegmentPoint1, oSegmentPoint2;
					if (fabs((v3-v1).GetLength() + (v4-v1).GetLength() - (v3-v4).GetLength()) <= context.precision) 
					{
						// случай когда v1 лежит между v3 и v4
						oSegmentPoint1 = v1;
					}
					else 
					{
						// случай когда v2 лежит между v3 и v4
						oSegmentPoint1 = v2;
					}

					if (fabs((v1-v3).GetLength() + (v2-v3).GetLength() - (v1-v2).GetLength()) <= context.precision) 
					{
						// случай когда v3 лежит между v1 и v2
						oSegmentPoint2 = v3;
					}
					else 
					{
						// случай когда v4 лежит между v1 и v2
						oSegmentPoint2 = v4;
					}

					if ((oSegmentPoint1-oSegmentPoint2).GetLength() <= context.precision) 
					{
						if ( (((v1-v3).GetLength() <= context.precision) && ((v2-v4).GetLength() <= context.precision)) ||
							 (((v1-v4).GetLength() <= context.precision) && ((v2-v3).GetLength() <= context.precision)) ) 
						{
							// Случай когда отрезки совпадают
							oSegment = LineSegment("", v1, v2, context);
						}
						else 
						{
							// Случай когда пересекаются в вершине
							oVector = oSegmentPoint1;
							result.SetResult(IntersectionType::IntersectedInPoint, oVector, oSegment);
							return result;
						}
					}
					else oSegment = LineSegment("", oSegmentPoint1, oSegmentPoint2, context);

					result.SetResult(IntersectionType::IntersectedInSegment, oVector, oSegment);
					return result;
				}
				else if (cp1.GetLength() <= context.precision) 
				{
					oVector = v1;
					result.SetResult(IntersectionType::IntersectedInPoint, oVector, oSegment);
					return result;
				}
				else if (cp2.GetLength() <= context.precision) 
				{
					oVector = v2;
					result.SetResult(IntersectionType::IntersectedInPoint, oVector, oSegment);
					return result;
				}
				else 
				{
					double cosinus1 = ScalarProduct(v2-v1, v3-v1)/((v2-v1).GetLength() * (v3-v1).GetLength());
					double cosinus2 = ScalarProduct(v1-v2, v3-v4)/((v1-v2).GetLength() * (v3-v4).GetLength());

					double sinus1 = pow(1.0-cosinus1*cosinus1, 0.5);
					double sinus2 = pow(1.0-cosinus2*cosinus2, 0.5);
					// находим длину отрезка до точки пересечения по теореме синусов
					double l = (v3-v1).GetLength()*sinus1/sinus2;
					double t = l/(v4-v3).GetLength();
					oVector = v3 - (-t)*(v4-v3);
					result.SetResult(IntersectionType::IntersectedInPoint, oVector, oSegment);
					return result;
				}
			}
			else 
			{
				result.SetResult(IntersectionType::NotIntersected, oVector, oSegment);
				return result;
			}
		}
		else 
		{
			result.SetResult(IntersectionType::NotIntersected, oVector, oSegment);
			return result;
		}
	}
}
