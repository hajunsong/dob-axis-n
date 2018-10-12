#ifndef DOB_H
#define DOB_H

#include "matrix.h"
#include <time.h>

#define simulation
#define experiment

class Body
{
public:
    Body() { u_vec << 0, 0, 1; }
    // base body information
    Matrix A0 = Matrix(3,3), C01 = Matrix(3,3);
    Vector s01p = Vector(3);
    // body initial data
    double qi, qi_dot, m;
    Vector ri = Vector(3), ri_dot = Vector(3), wi = Vector(3), rhoip = Vector(3), sijp = Vector(3);
    Matrix Jip = Matrix(3, 3), Cii = Matrix(3, 3), Cij = Matrix(3, 3);
    // Orientation
    Matrix Aijpp = Matrix(3, 3), Ai = Matrix(3, 3);
    Vector Hi = Vector(3), u_vec = Vector(3);
    // Position
    Vector sij = Vector(3), rhoi = Vector(3), ric = Vector(3);
    Matrix rit = Matrix(3, 3);
    // Velocity State
    Vector Bi = Vector(6), Yih = Vector(6);
    // Cartesian velocity state
    Matrix Ti = Matrix(6, 6), wit = Matrix(3, 3);
    Vector Yib = Vector(6), ric_dot = Vector(3);
    // Mass & Force
    Matrix Jic = Matrix(3, 3), rict = Matrix(3, 3), rict_dot = Matrix(3, 3), Mih = Matrix(6, 6);
    Vector Fic = Vector(3), Tic = Vector(3), Qih = Vector(6);
    // Velocity Coupling
    Matrix rit_dot = Matrix(3, 3);
    Vector dHi = Vector(3), Di = Vector(6);
    // System EQM
    Matrix Ki = Matrix(6, 6);
    Vector Li = Vector(6);
    // Acceleration
    double qi_ddot;
    // Generalized Force(Torque)
    double Q = 0;
    // Gravity force
    Vector Fg = Vector(6);
    double Tg = 0;
    // Control
    double des_vel, err_vel, err_vel_accum, err_vel_prev, T_control, T_control_vel, Kp_vel, Ki_vel, Kd_vel;
    // Residual
    double r_hat = 0, K = 0, p = 0, Ta = 0, Td = 0, yp = 0;
};

class DOB
{
public:
    DOB(uint num_body);
    ~DOB();
    void run();
    double total_time = 0, average_time = 0;
private:
    uint num_body;
    Body* body;

    double start_time, end_time, h, g, t_current;

    Vector Y, Yp, Y_old, Yp_old;

    void analysis();
        void Y2qdq();
        void kinematics_analysis();
        void generalized_mass_force();
        void residual_analysis();
        void dynamics_analysis();
            Matrix ludcmp(Matrix a, uint* indx);
            Vector lubksb(Matrix fac, uint* indx, Vector b);
        void dqddq2Yp();
};

#endif // DOB_H
