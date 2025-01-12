#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace Eigen;

int main() {
  // Define a matrix (example: 3x3)
  Matrix3d A;
  A << 1, 2, 3,
       4, 5, 6,
       7, 8, 9;

  std::cout << "Matrix A:\n" << A << "\n\n";

  // Compute eigenvalues and eigenvectors
  EigenSolver<Matrix3d> es(A);

  // Get eigenvalues
  Vector3cd eigenvalues = es.eigenvalues();
  std::cout << "Eigenvalues:\n" << eigenvalues << "\n\n";

  // Get eigenvectors
  Matrix3cd eigenvectors = es.eigenvectors();
  std::cout << "Eigenvectors:\n" << eigenvectors << "\n\n";

    // Verify the result (A * v = lambda * v) for the first eigenvector
    Vector3d v = eigenvectors.col(0).real(); // Get the first eigenvector (real part)
    std::complex<double> lambda = eigenvalues(0); // Get the first eigenvalue

    std::cout << "Verification for the first eigenvector:\n";
    std::cout << "A * v:\n" << A * v << "\n";
    std::cout << "lambda * v:\n" << (lambda * v).real() << "\n\n"; // Compare real parts

  // For real symmetric matrices, use SelfAdjointEigenSolver for better performance and guaranteed real eigenvalues/eigenvectors
    Matrix3d B;
    B << 2, -1, 0,
         -1, 2, -1,
         0, -1, 2;

    std::cout << "Real Symmetric Matrix B:\n" << B << "\n\n";

    SelfAdjointEigenSolver<Matrix3d> saes(B);
    Vector3d realEigenvalues = saes.eigenvalues();
    Matrix3d realEigenvectors = saes.eigenvectors();

    std::cout << "Real Eigenvalues of B:\n" << realEigenvalues << "\n\n";
    std::cout << "Real Eigenvectors of B:\n" << realEigenvectors << "\n\n";

    // Verify the result (B * v = lambda * v) for the first eigenvector
    Vector3d v_real = realEigenvectors.col(0); // Get the first eigenvector
    double lambda_real = realEigenvalues(0); // Get the first eigenvalue

    std::cout << "Verification for the first eigenvector of B:\n";
    std::cout << "B * v:\n" << B * v_real << "\n";
    std::cout << "lambda * v:\n" << lambda_real * v_real << "\n";

  return 0;
}