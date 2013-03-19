#ifndef EIGEN_QR_MODULE_H
#define EIGEN_QR_MODULE_H

#include "Core.hpp"

#include "src/Core/util/DisableStupidWarnings.h"

#include "Cholesky.hpp"
#include "Jacobi.hpp"
#include "Householder.hpp"

namespace Eigen {

/** \defgroup QR_Module QR module
  *
  *
  *
  * This module provides various QR decompositions
  * This module also provides some MatrixBase methods, including:
  *  - MatrixBase::qr(),
  *
  * \code
  * #include <Eigen/QR>
  * \endcode
  */

#include "src/misc/Solve.h"
#include "src/QR/HouseholderQR.h"
#include "src/QR/FullPivHouseholderQR.h"
#include "src/QR/ColPivHouseholderQR.h"

#ifdef EIGEN2_SUPPORT
#include "src/Eigen2Support/QR.h"
#endif

} // namespace Eigen

#include "src/Core/util/ReenableStupidWarnings.h"

#ifdef EIGEN2_SUPPORT
#include "Eigenvalues"
#endif

#endif // EIGEN_QR_MODULE_H
/* vim: set filetype=cpp et sw=2 ts=2 ai: */
