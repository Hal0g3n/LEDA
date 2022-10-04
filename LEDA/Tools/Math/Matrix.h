/**
 * @file        Matrix.h
 * @author      your name (you@domain.com)
 * @brief       The class representing a Matrix
 * @version     0.1
 * @date        15-08-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#ifndef LEDA_MATRIX_H_
#define LEDA_MATRIX_H_

#include "pch.h"
#include "LEDA_Math.h"

namespace LEDA {

    typedef union LEDA_API Mtx33 {
        // data members
        struct {
            double m00, m01, m02,
                m10, m11, m12,
                m20, m21, m22;
        };
        double m[9];
        double m2[3][3];

        // constructors
        Mtx33();
        Mtx33(const double*);
        Mtx33(double, double, double, double, double, double, double, double, double);

        // assignment operators
        Mtx33& operator*= (Mtx33 const& rhs); // performs matrix multiplication

        // member functions
        Mtx33 transpose() const;
        Mtx33 inverse() const;

        // static functions
        static Mtx33 identity();
        static Mtx33 translate(double, double);
        static Mtx33 scale(double, double);
        static Mtx33 rotateDeg(double);
        static Mtx33 rotateRad(double);

    } Mtx33, Matrix3x3, Mtx3x3;

    // binary operators
    Mtx33 operator*(Mtx33 const&, Mtx33 const&); // matrix multiplication
    Vec2D operator*(Mtx33 const&, Vec2D const&); // applying matrix to vector

    // 4x4 matrix
    typedef union LEDA_API Mtx44 {
        // data members
        struct {
            double m00, m01, m02, m03,
                m10, m11, m12, m13,
                m20, m21, m22, m23,
                m30, m31, m32, m33;
        };
        double m[16];
        double m2[4][4];

        // constructors
        Mtx44();
        Mtx44(const double*);
        Mtx44(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);

        // assignment operators
        Mtx44& operator*= (Mtx44 const& rhs); // performs matrix multiplication

        // member functions
        Mtx44 transpose() const;

        // static functions
        static Mtx44 identity();
        static Mtx44 translate(double, double, double);
        static Mtx44 scale(double, double, double);
        static Mtx44 rotateDeg(double, Vec3);
        static Mtx44 rotateRad(double, Vec3);

    } Mtx44, Matrix4x4, Mtx4x4;

    // binary operators
    Mtx44 operator*(Mtx44 const&, Mtx44 const&); // matrix multiplication
    Vec3D operator*(Mtx44 const&, Vec3D const&); // applying matrix to vector

}

#endif // LEDA_MATRIX_H_