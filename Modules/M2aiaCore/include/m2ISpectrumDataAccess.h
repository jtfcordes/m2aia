/*===================================================================

MSI applications for interactive analysis in MITK (M2aia)

Copyright (c) Jonas Cordes
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt for details.

===================================================================*/
#pragma once

#include <M2aiaCoreExports.h>
#include <mitkMessage.h>
#include <vector>

namespace mitk
{
  class Image;
}

namespace m2
{
  /**
  *
  *
  */

  class M2AIACORE_EXPORT ISpectrumDataAccess
  {
  public:
    virtual void ReceiveIntensities(unsigned int index,
                                    std::vector<double> &ints,
                                    unsigned int sourceIndex = 0) const = 0;
    virtual void ReceivePositions(unsigned int index, std::vector<double> &mzs, unsigned int sourceIndex = 0) const = 0;
    
	virtual void ReceiveSpectrum(unsigned int index,
                                 std::vector<double> &xs,
                                 std::vector<double> &ints,
                                 unsigned int sourceIndex = 0) const = 0;

    virtual void GenerateImageData(double mz, double tol, const mitk::Image *mask, mitk::Image *img) const = 0;
    /**
     * \brief Messages to emit
     *
     * Observers should register to this event by calling myLabelSet->AddLabelEvent.AddListener(myObject,
     * MyObject::MyMethod).
     * After registering, myObject->MyMethod() will be called every time a new label has been added to the LabelSet.
     * Observers should unregister by calling myLabelSet->AddLabelEvent.RemoveListener(myObject, MyObject::MyMethod).
     *
     * member variable is not needed to be locked in multi-threaded scenarios since the LabelSetEvent is a typedef for
     * a Message1 object which is thread safe
     */
    mutable mitk::Message<> ReceiveSpectrumEnd;
    mutable mitk::Message<> ReceiveSpectrumStart;
    mutable mitk::Message<> GenerateImageStart;
    mutable mitk::Message<> GenerateImageEnd;
  };

} // namespace m2