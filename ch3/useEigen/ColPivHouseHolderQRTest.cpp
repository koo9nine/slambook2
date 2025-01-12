#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main() {
  // Example matrix (can be rectangular or square)
  MatrixXd A(4, 3);
  A << 1, 2, 3,
       4, 5, 6,
       7, 8, 9,
       10, 11, 12;

  std::cout << "Matrix A:\n" << A << "\n\n";

  // Perform QR decomposition with column pivoting
  ColPivHouseholderQR<MatrixXd> qr(A);

  // Get the orthogonal matrix Q
  MatrixXd Q = qr.householderQ();
  std::cout << "Orthogonal matrix Q:\n" << Q << "\n\n";

  // Get the upper triangular matrix R
  MatrixXd R = qr.matrixR();
  std::cout << "Upper triangular matrix R:\n" << R << "\n\n";

  // Get the permutation matrix P (representing column swaps)
  MatrixXi P = qr.colsPermutation();
  std::cout << "Permutation matrix P:\n" << P << "\n\n";

  // Verify the decomposition: A * P = Q * R
  MatrixXd AP = A * P.cast<double>(); // Important: cast P to double
  MatrixXd QR = Q * R;
  std::cout << "A * P:\n" << AP << "\n\n";
  std::cout << "Q * R:\n" << QR << "\n\n";
  std::cout << "Is A * P == Q * R: " << AP.isApprox(QR) << "\n\n";

    // Example of solving a linear system Ax = b using QR decomposition with pivoting
    VectorXd b(4);
    b << 1, 2, 3, 4;
    std::cout << "Vector b:\n" << b << "\n\n";

    VectorXd x = qr.solve(b);
    std::cout << "Solution x (using solve()):\n" << x << "\n\n";
    std::cout << "A * x:\n" << A * x << "\n\n";

    // Solving using back substitution (more efficient if you need to solve multiple systems with the same A)
    VectorXd y = Q.transpose() * b;
    VectorXd x_backsub = R.triangularView<Upper>().solve(y);
    x_backsub = P.inverse() * x_backsub;
    std::cout << "Solution x (using back substitution):\n" << x_backsub << "\n\n";
    std::cout << "A * x_backsub:\n" << A * x_backsub << "\n\n";

  return 0;
}