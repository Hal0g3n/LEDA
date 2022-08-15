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

#pragma once

namespace LEDA {
    typedef union {
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
        Mtx33(const double* arr);
        Mtx33(double _00, double _01, double _02, double _10, double _11, double _12, double _20, double _21, double _22);

        // assignment operators
        Mtx33& operator*= (Mtx33 const& rhs); // performs matrix multiplication

        // member functions
        Mtx33 transpose() const;
        Mtx33 inverse() const;

        // static functions
        static Mtx33 identity();
        static Mtx33 translate();
        static Mtx33 scale();
        static Mtx33 rotateDeg();
        static Mtx33 rotateRad();

    } Matrix3x3, Mtx3x3, Mtx33;

    // binary operators
    Mtx33 operator*(Mtx33 const& lhs, Mtx33 const& rhs); // matrix multiplication
    Vec2D operator*(Mtx33 const& lhs, Vec2D const& rhs); // applying matrix to vector
}