/*===================================================================

MSI applications for interactive analysis in MITK (M2aia)

Copyright (c) Jonas Cordes.

All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or https://www.github.com/jtfcordes/m2aia for details.

===================================================================*/

#pragma once


#include <itkEuler3DTransform.h>
#include "mapRegistration.h"
#include "mapContinuous.h"

#include <mitkPoint.h>

#include <QWidget>

#include <MitkMatchPointRegistrationUIExports.h>

#include "ui_m2ManipulationWidget.h"


/*!
\brief QmitkMatchPointRegistrationManipulator

\warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

\sa QmitkFunctionality
\ingroup ${plugin_target}_internal
*/
class m2ManipulationWidget : public QWidget, private Ui::m2ManipulationWidget
{
  Q_OBJECT

public:
  m2ManipulationWidget(QWidget *parent = nullptr);

  ~m2ManipulationWidget() override;

  /** Type of transform that can be provided as preceding transform.*/
  typedef map::core::Registration<3, 3> MAPRegistrationType;

  /** Initializing/reset widget with identity transform.*/
  void Initialize();

  /** Initializing/reset widget with a preceding registration.*/
  void Initialize(MAPRegistrationType* precedingRegistration);

  /** Initializing/reset widget with an translation transform deduced by the to passed reference points.*/
  void Initialize(const mitk::Point3D& movingReference, const mitk::Point3D& targetReference);

  /**This function offers access to a registration instance that represents the internal state of the
  registration currently manipulated by the widget. It can be used for example to update the visualization.*/
  map::core::RegistrationBase* GetInterimRegistration() const;

  /**This function generates a new registration instance that resembles the state when the method was called.
  Ownership of the return goes to the caller.*/
  map::core::RegistrationBase::Pointer GenerateRegistration()const ;

public Q_SLOTS:
  void SetCenterOfRotation(const mitk::Point3D& center);

  /** Sets the internal m_CenterOfRotationIsRelativeToTarget. see below.*/
  void SetCenterOfRotationIsRelativeToTarget(bool targetRelative);

signals:
  void RegistrationChanged(map::core::RegistrationBase *registration);

protected slots:

  void OnRotXChanged(double);
  void OnRotYChanged(double);
  void OnRotZChanged(double);

  void OnTransXChanged(double);
  void OnTransYChanged(double);
  void OnTransZChanged(double);

  void OnRotXSlideChanged(int);
  void OnRotYSlideChanged(int);
  void OnRotZSlideChanged(int);

  void OnTransXSlideChanged(int);
  void OnTransYSlideChanged(int);
  void OnTransZSlideChanged(int);

private:

  /** Initializes/resets the transforms.*/
  void ResetTransforms();
  /** Initialize the sub widgets according to the internal state of the transforms.*/
  void InitControls();

  /**
  * Updates the widgets that manipulate the transform according to the transform.*/
  void UpdateTransformWidgets();

  /**
  * Updates the transform according to the widgets that manipulate the transform.*/
  void UpdateTransform(bool updateRotation = false);

  void ConfigureTransformCenter();

  MAPRegistrationType::Pointer m_PreRegistration;

  using TransformType = itk::Euler3DTransform<::map::core::continuous::ScalarType>;
  TransformType::Pointer m_InverseCurrentTransform;
  TransformType::Pointer m_DirectCurrentTransform;

  MAPRegistrationType::Pointer m_CurrentRegistration;
  mitk::Point3D m_CenterOfRotation;
  /** This flag indicates if the center of rotation is specified relative to the target
  (true; thus must be updated when the inverse transform is changed) or relative to the moving
  (false; thus must not be updated).*/
  bool m_CenterOfRotationIsRelativeToTarget;

  bool m_internalUpdate;
};

