#ifndef CMATRIX4X4_H
#define CMATRIX4X4_H
//------------------------------------------------------------------------
//
//  Name:   CMatrix4X4.h
//
//  Author: Hoon-il Song (Sider)
//
//  Desc:   3D Matrix class 
//
//------------------------------------------------------------------------

class CMatrix4X4{
private:
  
  struct Matrix{
    double _11, _12, _13, _14;
    double _21, _22, _23, _24;
    double _31, _32, _33, _34;
		double _41, _42, _43, _44;

    Matrix(){
      _11=0.0; _12=0.0; _13=0.0; _14=0.0;
      _21=0.0; _22=0.0; _23=0.0; _24=0.0;
      _31=0.0; _32=0.0; _33=0.0; _34=0.0;
			_41=0.0; _42=0.0; _43=0.0; _44=0.0;
    }

  };

  Matrix m_Matrix;

  //multiplies m_Matrix with mIn
  inline void  MatrixMultiply(Matrix &mIn);

public:
  CMatrix4X4(){
    //initialize the matrix to an identity matrix
    Identity();
  }

  //create an identity matrix
  inline void Identity();
  
  //create a transformation matrix
  inline void Translate(double x, double y);
	inline void Translate(Vector2D _vPos);

  //create a scale matrix
  inline void Scale(double xScale, double yScale);

  //create a rotation matrix
  inline void  RotateZ(double _dRotation);

  //create a rotation matrix from a fwd and side 2D vector
  inline void  RotateZ(const Vector2D &fwd, const Vector2D &side);

   //applys a transformation matrix to a std::vector of points
  inline void TransformVector2Ds(std::vector<Vector2D> &vPoints);

  //applys a transformation matrix to a point
  inline void TransformVector2Ds(Vector2D &vPoint);

  //accessors to the matrix elements
  void _11(double _dVal){m_Matrix._11 = _dVal;}
  void _12(double _dVal){m_Matrix._12 = _dVal;}
  void _13(double _dVal){m_Matrix._13 = _dVal;}
	void _14(double _dVal){m_Matrix._14 = _dVal;}

  void _21(double _dVal){m_Matrix._21 = _dVal;}
  void _22(double _dVal){m_Matrix._22 = _dVal;}
  void _23(double _dVal){m_Matrix._23 = _dVal;}
	void _24(double _dVal){m_Matrix._24 = _dVal;}

  void _31(double _dVal){m_Matrix._31 = _dVal;}
  void _32(double _dVal){m_Matrix._32 = _dVal;}
  void _33(double _dVal){m_Matrix._33 = _dVal;}
	void _34(double _dVal){m_Matrix._34 = _dVal;}

	void _41(double _dVal){m_Matrix._41 = _dVal;}
  void _42(double _dVal){m_Matrix._42 = _dVal;}
  void _43(double _dVal){m_Matrix._43 = _dVal;}
	void _44(double _dVal){m_Matrix._44 = _dVal;}
};

//multiply two matrices together
inline void CMatrix4X4::MatrixMultiply(Matrix &mIn){
  CMatrix4X4::Matrix mat_temp;
  
  //first row
  mat_temp._11 = (m_Matrix._11*mIn._11) + (m_Matrix._12*mIn._21) + (m_Matrix._13*mIn._31) + (m_Matrix._14*mIn._41);
  mat_temp._12 = (m_Matrix._11*mIn._12) + (m_Matrix._12*mIn._22) + (m_Matrix._13*mIn._32) + (m_Matrix._14*mIn._42);
  mat_temp._13 = (m_Matrix._11*mIn._13) + (m_Matrix._12*mIn._23) + (m_Matrix._13*mIn._33) + (m_Matrix._14*mIn._43);
	mat_temp._14 = (m_Matrix._11*mIn._14) + (m_Matrix._12*mIn._24) + (m_Matrix._13*mIn._34) + (m_Matrix._14*mIn._44);

  //second
  mat_temp._21 = (m_Matrix._21*mIn._11) + (m_Matrix._22*mIn._21) + (m_Matrix._23*mIn._31) + (m_Matrix._24*mIn._41);
  mat_temp._22 = (m_Matrix._21*mIn._12) + (m_Matrix._22*mIn._22) + (m_Matrix._23*mIn._32) + (m_Matrix._24*mIn._42);
  mat_temp._23 = (m_Matrix._21*mIn._13) + (m_Matrix._22*mIn._23) + (m_Matrix._23*mIn._33) + (m_Matrix._24*mIn._43);
	mat_temp._24 = (m_Matrix._21*mIn._14) + (m_Matrix._22*mIn._24) + (m_Matrix._23*mIn._34) + (m_Matrix._24*mIn._44);

  //third
  mat_temp._31 = (m_Matrix._31*mIn._11) + (m_Matrix._32*mIn._21) + (m_Matrix._33*mIn._31) + (m_Matrix._34*mIn._41);
  mat_temp._32 = (m_Matrix._31*mIn._12) + (m_Matrix._32*mIn._22) + (m_Matrix._33*mIn._32) + (m_Matrix._34*mIn._42);
  mat_temp._33 = (m_Matrix._31*mIn._13) + (m_Matrix._32*mIn._23) + (m_Matrix._33*mIn._33) + (m_Matrix._34*mIn._43);
	mat_temp._34 = (m_Matrix._31*mIn._14) + (m_Matrix._32*mIn._24) + (m_Matrix._33*mIn._34) + (m_Matrix._34*mIn._44);

	// forth
  mat_temp._41 = (m_Matrix._41*mIn._11) + (m_Matrix._42*mIn._21) + (m_Matrix._43*mIn._31) + (m_Matrix._44*mIn._41);
  mat_temp._42 = (m_Matrix._41*mIn._12) + (m_Matrix._42*mIn._22) + (m_Matrix._43*mIn._32) + (m_Matrix._44*mIn._42);
  mat_temp._43 = (m_Matrix._41*mIn._13) + (m_Matrix._42*mIn._23) + (m_Matrix._43*mIn._33) + (m_Matrix._44*mIn._43);
	mat_temp._44 = (m_Matrix._41*mIn._14) + (m_Matrix._42*mIn._24) + (m_Matrix._43*mIn._34) + (m_Matrix._44*mIn._44);

  m_Matrix = mat_temp;
}

//applies a 2D transformation matrix to a std::vector of Vector2Ds
inline void CMatrix4X4::TransformVector2Ds(std::vector<Vector2D> &vPoint){
  for (unsigned int i=0; i<vPoint.size(); ++i){
    double tempX = (m_Matrix._11*vPoint[i].x) + (m_Matrix._21*vPoint[i].y) + (m_Matrix._41);

    double tempY = (m_Matrix._12*vPoint[i].x) + (m_Matrix._22*vPoint[i].y) + (m_Matrix._42);
  
    vPoint[i].x = tempX;

    vPoint[i].y = tempY;
  }
}

//applies a 2D transformation matrix to a single Vector2D
inline void CMatrix4X4::TransformVector2Ds(Vector2D &vPoint){
  double tempX = (m_Matrix._11*vPoint.x) + (m_Matrix._21*vPoint.y) + (m_Matrix._41);

  double tempY = (m_Matrix._12*vPoint.x) + (m_Matrix._22*vPoint.y) + (m_Matrix._42);
  
  vPoint.x = tempX;

  vPoint.y = tempY;
}

//create an identity matrix
inline void CMatrix4X4::Identity(){
  m_Matrix._11 = 1; m_Matrix._12 = 0; m_Matrix._13 = 0; m_Matrix._14 = 0;

  m_Matrix._21 = 0; m_Matrix._22 = 1; m_Matrix._23 = 0; m_Matrix._24 = 0;

  m_Matrix._31 = 0; m_Matrix._32 = 0; m_Matrix._33 = 1; m_Matrix._34 = 0;

	m_Matrix._41 = 0; m_Matrix._42 = 0; m_Matrix._43 = 0; m_Matrix._44 = 1;
}

//create a transformation matrix
inline void CMatrix4X4::Translate(double x, double y){
  Matrix mat;
  
  mat._11 = 1; mat._12 = 0; mat._13 = 0; mat._14 = 0;
  
  mat._21 = 0; mat._22 = 1; mat._23 = 0; mat._24 = 0;
  
  mat._31 = 0; mat._32 = 0; mat._33 = 1; mat._34 = 0;

	mat._41 = x; mat._42 = y; mat._43 = 0; mat._34 = 1;
  
  //and multiply
  MatrixMultiply(mat);
}

//create a transformation matrix
inline void CMatrix4X4::Translate(Vector2D _vPos){
  Matrix mat;
  
  mat._11 = 1;			 mat._12 = 0;				mat._13 = 0; mat._14 = 0;
  
  mat._21 = 0;			 mat._22 = 1;				mat._23 = 0; mat._24 = 0;
  
  mat._31 = 0;			 mat._32 = 0;				mat._33 = 1; mat._34 = 0;

	mat._41 = _vPos.x; mat._42 = _vPos.y; mat._43 = 0; mat._44 = 1;
  
  //and multiply
  MatrixMultiply(mat);
}

//create a scale matrix
inline void CMatrix4X4::Scale(double xScale, double yScale){
  CMatrix4X4::Matrix mat;
  
  mat._11 = xScale; mat._12 = 0;			mat._13 = 0; mat._14 = 0;
  
  mat._21 = 0;			mat._22 = yScale; mat._23 = 0; mat._24 = 0;
  
  mat._31 = 0;			mat._32 = 0;			mat._33 = 1; mat._34 = 0;

	mat._41 = 0;			mat._42 = 0;			mat._43 = 0; mat._44 = 1;
  
  //and multiply
  MatrixMultiply(mat);
}

//create a rotation matrix
inline void CMatrix4X4::RotateZ(double rot){
  CMatrix4X4::Matrix mat;

  double Sin = sin(rot);
  double Cos = cos(rot);
  
  mat._11 = Cos;  mat._12 = -Sin; mat._13 = 0; mat._14 = 0;
  
  mat._21 = Sin;	mat._22 = Cos;	mat._23 = 0; mat._24 = 0;
  
  mat._31 = 0;		mat._32 = 0;		mat._33 = 1; mat._34 = 0;

	mat._41 = 0;		mat._42 = 0;		mat._43 = 0; mat._44 = 1;
  
  //and multiply
  MatrixMultiply(mat);
}

//create a rotation matrix from a 2D vector
inline void CMatrix4X4::RotateZ(const Vector2D &fwd, const Vector2D &side){
  CMatrix4X4::Matrix mat;
  
  mat._11 = fwd.x;  mat._12 = fwd.y;	mat._13 = 0; mat._14 = 0;
  
  mat._21 = side.x; mat._22 = side.y; mat._23 = 0; mat._24 = 0;
  
  mat._31 = 0;			mat._32 = 0;			mat._33 = 1; mat._34 = 0;

	mat._41 = 0;			mat._42 = 0;			mat._43 = 0; mat._44 = 1;
  
  //and multiply
  MatrixMultiply(mat);
}

#endif