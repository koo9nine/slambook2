#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv) {
  Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);

  cout << "1. Quarterniond" << endl;
  cout << "== before normalization ==" << endl;
  cout << "q1.w : " << q1.w() << endl;
  cout << "q1.vec() : " << q1.vec().transpose() << endl;
  cout << "q1.norm() : " << q1.norm() << endl;

  q1.normalize();
  q2.normalize();

  cout << "\n== after normalization ==" << endl;
  cout << "q1.w : " << q1.w() << endl;
  cout << "q1.vec() : " << q1.vec().transpose() << endl;
  cout << "q1.norm() : " << q1.norm() << endl;

  Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
  Vector3d p1(0.5, 0, 0.2);

  cout << "\n2. Isometry" << endl;
  Isometry3d T1w(q1), T2w(q2);
  T1w.pretranslate(t1);
  T2w.pretranslate(t2);

  cout << "T1w.rotation : " << T1w.rotation() << endl;
  cout << "T1w.translation : " << T1w.translation().transpose() << endl;

  Quaterniond q3(T1w.rotation());
  cout << "quaternion(q3) from T1w.ratation : " << endl;
  cout << "q3.w : " << q3.w() << endl;
  cout << "q3.vec() : " << q3.vec().transpose() << endl;

  Vector3d p2 = T2w * T1w.inverse() * p1;
  cout << endl << p2.transpose() << endl;

  cout << "\n== Rotation test1 ==" << endl;
  cout << "p1 : " << p1.transpose() << endl;

  cout << "q1.w : " << q1.w() << endl;
  cout << "q1.vec() : " << q1.vec().transpose() << endl;
  cout << "q1.norm() : " << q1.norm() << endl;
  Matrix3d rmat1(q1);
  cout << "\nrmat1 (from q1) : " << rmat1 << endl;
  
  cout << "\nrotated p1 using rotation matrix rmat1 : " << rmat1 * p1 << endl;

  Quaterniond quarterniod_p1;
  quarterniod_p1.w() = 0;
  quarterniod_p1.vec() = p1;
  Quaterniond rotated_quarterniod_p1 = q1 * quarterniod_p1 * q1.inverse();
  cout << "\nrotatied p1 using q1 : " << rotated_quarterniod_p1.vec() << endl;
 
  cout << "\n== Rotation test2 ==" << endl;
  cout << "q2.w : " << q2.w() << endl;
  cout << "q2.vec() : " << q2.vec().transpose() << endl;
  cout << "q2.norm() : " << q2.norm() << endl;

  Matrix3d rmat2(q2);
  cout << "\nrmat2 (from q2) : " << rmat2 << endl;
  cout << "\nrmat2 * rmat1 * p1 : " << rmat2 * rmat1 * p1 << endl;

  Quaterniond q4 = q2 * q1;
  Quaterniond double_rotated_quarterniod_p1 = q4 * quarterniod_p1 * q4.inverse();
  cout << "\nrotatied p1 using q2 after q1 : " << double_rotated_quarterniod_p1.vec() << endl;
  return 0;
}