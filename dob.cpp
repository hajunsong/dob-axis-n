#include "dob.h"

DOB::DOB(uint numbody)
{
    num_body = numbody;
    body = new Body[num_body];

    // read data
    start_time = 0;
    end_time = 5;
    h = 0.001;
    g = -9.80665;

    body[0].A0 << 0, 0, 1,
            1, 0, 0,
            0, 1, 0;
    body[0].C01 = Matrix::eye(3);
    body[0].s01p = Vector::zeros(3);

    switch(num_body){
    case 6:
        // body 6 variable
        body[5].qi = 0;
        body[5].qi_dot = 0;
        body[5].m = 25;
        body[5].Jip << 12, 0, 0,
                0, 12, 0,
                0, 0, 12;
        body[5].rhoip << 0, -0.4, 0;
        body[5].Cii << 0, 1, 0,
                0, 0, 1,
                1, 0, 0;
        body[5].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[5].sijp << 0, -0.8, 0;
        body[5].K = 1500;
        goto CASE5;
CASE5: case 5:
        // body 5 variable
        body[4].qi = 0;
        body[4].qi_dot = 0;
        body[4].m = 20;
        body[4].Jip << 10, 0, 0,
                0, 10, 0,
                0, 0, 10;
        body[4].rhoip << 0.35, 0, 0;
        body[4].Cii << 0, 0, -1,
                0, 1, 0,
                1, 0, 0;
        body[4].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[4].sijp << 0.7, 0, 0;
        body[4].K = 1500;
        goto CASE4;
CASE4: case 4:
        // body 4 variable
        body[3].qi = 0;
        body[3].qi_dot = 0;
        body[3].m = 15;
        body[3].Jip << 7, 0, 0,
                0, 7, 0,
                0, 0, 7;
        body[3].rhoip << 0, 0.3, 0;
        body[3].Cii << 0, -1, 0,
                0, 0, -1,
                1, 0, 0;
        body[3].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[3].sijp << 0, 0.6, 0;
        body[3].K = 1500;
        goto CASE3;
CASE3: case 3:
        // body 3 variable
        body[2].qi = 0;
        body[2].qi_dot = 0;
        body[2].m = 10;
        body[2].Jip << 5, 0, 0,
                0, 5, 0,
                0, 0, 5;
        body[2].rhoip << -0.25, 0, 0;
        body[2].Cii << 0, 0, 1,
                0, -1, 0,
                0, 0, 1;
        body[2].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[2].sijp << -0.5, 0, 0;
        body[2].K = 1500;
        goto CASE2;
CASE2: case 2:
        // body 2 variable
        body[1].qi = 0;
        body[1].qi_dot = 0;
        body[1].m = 5;
        body[1].Jip << 3, 0, 0,
                0, 3, 0,
                0, 0, 3;
        body[1].rhoip << 0, -0.2, 0;
        body[1].Cii << 0, 1, 0,
                0, 0, 1,
                1, 0, 0;
        body[1].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[1].sijp << 0, -0.4, 0;
        body[1].K = 1500;
        goto CASE1;
CASE1 : case 1:
        // body 1 variable
        body[0].qi = 0;
        body[0].qi_dot = 0;
        body[0].m = 2.0;
        body[0].Jip << 1.5, 0, 0,
                0, 1.5, 0,
                0, 0, 1.5;
        body[0].rhoip << 0.15, 0, 0;
        body[0].Cii << 0, 0, -1,
                0, 1, 0,
                1, 0, 0;
        body[0].Cij << 0, -1, 0,
                1, 0, 0,
                0, 0, 1;
        body[0].sijp << 0.3, 0, 0;
        body[0].K = 1500;
    }

    // define Y vector
    Y = Vector(num_body * 3);
    Yp = Vector(num_body * 3);
    if (num_body == 1) {
        Y(0) = body[0].qi;
        Y(1) = body[0].qi_dot;
        Y(2) = 0;
    }
    else {
        for (uint i = 0; i < num_body; i++) {
            Y(i) = body[i].qi;
        }
        for (uint i = 0; i < num_body; i++) {
            Y(i + num_body) = body[i].qi_dot;
        }
        for (uint i = 0; i < num_body; i++) {
            Y(i + num_body*2) = body[i].r_hat;
        }
    }
    Y_old = Y;
    Yp_old = Vector::zeros(Yp.len);
}

DOB::~DOB(){
    delete[] body;
}

void DOB::run()
{
    while (t_current <= end_time) {
        analysis();

        Y = Y_old + Yp_old*h + 0.5*h*(Yp - Yp_old);

        for(uint i = 0; i < num_body; i++){
            body[i].p = 0.5*body[i].qi_dot*body[i].qi_dot*(body[i].Jic(0,0)*body[i].wi(0)*body[i].wi(0) + body[i].Jic(1,1)*body[i].wi(1)*body[i].wi(1) + body[i].Jic(2,2)*body[i].wi(2)*body[i].wi(2));
            body[i].r_hat = body[i].K*(Y(2*num_body + i) - body[i].p);
        }

        printf("Time : %.5f[s]", t_current);
        for(uint i = 0; i < num_body; i++){
            printf("Position1 : %.10f[rad] ", body[i].qi);
        }
        for(uint i = 0; i < num_body; i++){
            printf("R : %.5f[Nm] ", body[i].r_hat);
        }
        printf("\n");

        Yp_old = Yp;
        t_current += h;
    }

    cout << "Total Processing Time : " << total_time << " ms" << endl;
    average_time = total_time / ((end_time - start_time)/h);
    cout << "Average Processing Time : " << average_time << " ms" << endl;
}

void DOB::analysis() {
    Y2qdq();

    clock_t start, end;
    start = clock();
    kinematics_analysis();
    generalized_mass_force();
    residual_analysis();
    end = clock();
    total_time += static_cast<double>((end - start));

    dynamics_analysis();

    dqddq2Yp();
}

void DOB::Y2qdq()
{
    for (uint i = 0; i < num_body; i++) {
        body[i].qi = Y(i);
    }
    for (uint i = 0; i < num_body; i++) {
        body[i].qi_dot = Y(i + num_body);
    }
}

void DOB::kinematics_analysis() {
    for (uint i = 0; i < num_body; i++) {
        // Orientation
        body[i].Aijpp << cos(body[i].qi), -sin(body[i].qi), 0,
                sin(body[i].qi), cos(body[i].qi), 0,
                0, 0, 1;
        if (i == 0) {
            body[i].Ai = body[i].A0 * body[i].C01*body[i].Aijpp;
            body[i].Hi = body[i].A0 * body[i].C01*body[i].u_vec;
        }
        else {
            body[i].Ai = body[i - 1].Ai*body[i - 1].Cij*body[i].Aijpp;
            body[i].Hi = body[i - 1].Ai*body[i - 1].Cij*body[i].u_vec;
        }
        // Position
        if (i == 0) {
            body[i].ri = body[i].A0 * body[i].s01p;
        }
        else {
            body[i - 1].sij = body[i - 1].Ai*body[i - 1].sijp;
            body[i].ri = body[i - 1].ri + body[i - 1].sij;
        }
        body[i].rhoi = body[i].Ai * body[i].rhoip;
        body[i].ric = body[i].ri + body[i].rhoi;
        // Inertial matrix
        Matrix Ai_Cii = body[i].Ai * body[i].Cii;
        body[i].Jic = Ai_Cii * body[i].Jip*Ai_Cii.t();
    }
}

void DOB::generalized_mass_force() {
    for (uint i = 0; i < num_body; i++) {
        // Velocity State
        body[i].rit = body[i].ri.tilde();
        body[i].Bi = body[i].rit * body[i].Hi
                << body[i].Hi;
        if (i == 0) {
            body[i].Yih = body[i].Bi * body[i].qi_dot;
        }
        else {
            body[i].Yih = body[i - 1].Yih + body[i].Bi * body[i].qi_dot;
        }
        // Cartesian Velocity
        body[i].Ti = (Matrix::eye(3), -body[i].rit)
                << (Matrix::zeros(3, 3), Matrix::eye(3));
        body[i].Yib = body[i].Ti * body[i].Yih;
        body[i].ri_dot << body[i].Yib(0), body[i].Yib(1), body[i].Yib(2);
        body[i].wi << body[i].Yib(3), body[i].Yib(4), body[i].Yib(5);
        body[i].wit = body[i].wi.tilde();
        body[i].ric_dot = body[i].ri_dot + body[i].wit * body[i].rhoi;
        // Mass & Force
        body[i].rict = body[i].ric.tilde();
        body[i].rict_dot = body[i].ric_dot.tilde();
        body[i].Mih = ((Matrix::eye(3)*body[i].m, -body[i].m * body[i].rict)
                       << (body[i].m*body[i].rict, body[i].Jic - body[i].m * body[i].rict*body[i].rict));
        body[i].Fic << 0, 0, body[i].m*g;
        body[i].Tic << 0, 0, 0;
        body[i].Qih = body[i].Fic + body[i].m * body[i].rict_dot*body[i].wi
                << body[i].Tic + body[i].rict * body[i].Fic + body[i].m * body[i].rict*body[i].rict_dot*body[i].wi - body[i].wit * body[i].Jic*body[i].wi;
        // Velocity Coupling
        body[i].rit_dot = body[i].ri_dot.tilde();
        if (i == 0) {
            body[i].dHi = Vector::zeros(3);
        }
        else {
            body[i].dHi = body[i - 1].wit*body[i].Hi;
        }
        body[i].Di = (body[i].rit_dot*body[i].Hi + body[i].rit * body[i].dHi
                      << body[i].dHi)*body[i].qi_dot;

        body[i].err_vel = body[i].des_vel - body[i].qi_dot;
        body[i].err_vel_accum += body[i].err_vel*h;
        body[i].T_control_vel = body[i].Kp_vel*body[i].err_vel + body[i].Kd_vel*(body[i].err_vel - body[i].err_vel_prev)/h + body[i].Ki_vel*body[i].err_vel_accum;
        body[i].err_vel_prev = body[i].err_vel;

        body[i].T_control = body[i].T_control_vel;
        body[i].T_control = 0;
    }

    for (int i = num_body - 1; i >= 0; i--) {
        body[i].Ki = body[i].Mih;
        body[i].Li = body[i].Qih;
        if (i != num_body - 1) {
            body[i].Ki += body[i + 1].Ki;
            body[i].Li += body[i + 1].Li - body[i + 1].Ki*body[i + 1].Di;
        }
    }
}

void DOB::residual_analysis(){
    for(uint i = 0; i < num_body; i++){
        Vector D_temp = Vector::zeros(6);
        for(uint j = 0; j <= i; j++){
            D_temp += body[j].Di;
        }

        body[i].Fg = -(body[i].Fic << body[i].rict*body[i].Fic);
        body[i].Tg = (body[i].Bi.t()*(body[i].Fg - body[i].Ki*D_temp))(0);
        //        body[i].Tg = 0;

        body[i].Ta = body[i].T_control + body[i].Tg;

        body[i].yp = body[i].Ta - body[i].Tg - body[i].r_hat;
    }
}

void DOB::dynamics_analysis() {
    Matrix M;
    Vector Q;

    for (uint i = 0; i < num_body; i++) {
        Matrix M_temp;
        for (uint j = 0; j < num_body; j++) {
            if (i == j) {
                M_temp = (M_temp, body[i].Bi.t()*body[i].Ki*body[i].Bi);
            }
            else if (i < j) {
                M_temp = (M_temp, body[i].Bi.t()*body[j].Ki*body[j].Bi);
            }
            else if (i > j) {
                M_temp = (M_temp, body[i].Bi.t()*body[i].Ki*body[j].Bi);
            }
        }
        M = M << M_temp;
        Vector D_temp = Vector::zeros(6);
        for (uint j = 0; j <= i; j++) {
            D_temp += body[j].Di;
        }
        Q = Q << body[i].Bi.t()*(body[i].Li - body[i].Ki*D_temp);
        Q(i) = Q(i) + body[i].Tg;
    }

    Vector dYh(num_body);
    Matrix fac(num_body, num_body);
    uint *indx = new uint[num_body];
    fac = ludcmp(M, indx);
    dYh = lubksb(fac, indx, Q);
    delete[] indx;

    for (uint i = 0; i < num_body; i++) {
        body[i].qi_ddot = dYh(i);
    }
}

void DOB::dqddq2Yp() {
    for (uint i = 0; i < num_body; i++) {
        Yp(i) = body[i].qi_dot;
    }
    for (uint i = 0; i < num_body; i++) {
        Yp(i + num_body) = body[i].qi_ddot;
    }
    for(uint i = 0; i < num_body; i++){
        Yp(i + num_body*2) = body[i].yp;
    }
}

Matrix DOB::ludcmp(Matrix A, uint* indx)
{
    int n = A.rows;
    Matrix a = A;
    Matrix fac(n, n);
    int i, imax, j, k;
    double big, temp, d = 0.0;
    double *vv = new double[n];
    const double TINY = 1.0e-20;
    for (i = 0; i < n; i++) {
        big = 0.0;
        for (j = 0; j < n; j++)
            if ((temp = fabs(a(i, j))) > big) big = temp;
        if (big == 0.0) {
            cout << ("Singular matrix in LUdcmp") << endl;
        }
        vv[i] = 1.0 / big;
    }
    for (k = 0; k < n; k++) {
        big = 0.0;
        for (i = k; i < n; i++) {
            temp = vv[i] * fabs(a(i, k));
            if (temp > big) {
                big = temp;
                imax = i;
            }
        }
        if (k != imax) {
            for (j = 0; j < n; j++) {
                temp = a(imax, j);
                a(imax, j) = a(k, j);
                a(k, j) = temp;
            }
            d = -d;
            vv[imax] = vv[k];
        }
        indx[k] = imax;
        if (a(k, k) == 0.0) a(k, k) = TINY;
        for (i = k + 1; i < n; i++) {
            temp = a(i, k) /= a(k, k);
            for (j = k + 1; j < n; j++)
                a(i, j) -= temp * a(k, j);
        }
    }
    //////////////////
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fac(i, j) = a(i, j);
        }
    }
    delete[] vv;
    return fac;
}
Vector DOB::lubksb(Matrix fac, uint* indx, Vector b)
{
    int n = fac.rows;
    Vector x(n);

    int i, ii = 0, ip, j;
    double sum;
    x = b;
    for (i = 0; i < n; i++) {
        ip = indx[i];
        sum = x(ip);
        x(ip) = x(i);
        if (ii != 0)
            for (j = ii - 1; j < i; j++) sum -= fac(i, j) * x(j);
        else if (sum != 0.0)
            ii = i + 1;
        x(i) = sum;
    }
    for (i = n - 1; i >= 0; i--) {
        sum = x(i);
        for (j = i + 1; j < n; j++) sum -= fac(i, j) * x(j);
        x(i) = sum / fac(i, i);
    }

    return x;
}
