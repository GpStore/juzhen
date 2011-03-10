smatrix m1(2, 3);
m1 << 1, 3, 5,
      2, 4, 6;
smatrix m2(2, 2);
m2 << 20, 40,
      30, 50;

V(m1.Block(0, 0, 0, 1), "1 3 ")
V(m1.Block(0, 0, 0, 0), "1 ")
V(m1.Block(0, 0, 0, 0)*3, "3 ")

m1.Replace(0, 1, m2);
V(m1, "1 20 40 \n2 30 50 ")

V((2*m1).Replace(0, 1, 2*m2)/2, "1 20 40 \n2 30 50 ")

double a[] = {1., 2., 3., 4., 5., 6.};
smatrix m3(a, 2, 3);

V(m3.GetCol(1), "3 \n4 ")

V(m3.GetRow(1), "2 4 6 ")