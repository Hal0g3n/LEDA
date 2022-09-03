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

#include "LEDA_Math.h"

#ifndef LEDA_MATRIX_H_
#define LEDA_MATRIX_H_

namespace LEDA {
    typedef union Mtx33 {
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
}

#endif // LEDA_MATRIX_H_