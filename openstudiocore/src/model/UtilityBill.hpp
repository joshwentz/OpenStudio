/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_UTILITYBILL_HPP
#define MODEL_UTILITYBILL_HPP

#include <model/ModelAPI.hpp>
#include <model/ModelObject.hpp>
#include <model/ModelExtensibleGroup.hpp>

#include <utilities/Data/Vector.hpp>

namespace openstudio {

class FuelType;
class InstallLocationType;
class EndUseCategoryType;
class Date;

namespace model {

class Meter;

namespace detail {

  class UtilityBill_Impl;

} // detail


/** BillingPeriod is a ModelExtensibleGroup that represents a single billing period in the
    UtilityBill ModelObject. */
class MODEL_API BillingPeriod : public ModelExtensibleGroup {
 public:
  /** @name Getters */
  //@{

  /** The date that the billing period starts. */
  Date startDate() const;

  /** The date that the billing period ends. */
  Date endDate() const;

  /** The duration of the billing period in days. */
  unsigned numberOfDays() const;

  boost::optional<double> consumption() const;

  boost::optional<double> peakDemand() const;

  boost::optional<double> totalCost() const;

  //@}
  /** @name Setters */
  //@{

  /** Sets the start date.  If startDate is before endDate then endDate is retained.
      If startDate is after endDate then numberOfDays is retained. */
  bool setStartDate(const Date& startDate);

  /** Sets the end date.  If endDate is after startDate then startDate is retained.
      If endDate is before startDate then numberOfDays is retained. */
  bool setEndDate(const Date& endDate);

  /** Sets the number of days in billing period, startDate is always retained. */
  bool setNumberOfDays(unsigned numberOfDays);

  bool setConsumption(double consumption);

  void resetConsumption();

  bool setPeakDemand(double peakDemand);

  void resetPeakDemand();

  bool setTotalCost(double totalCost);

  void resetTotalCost();

  //@}
  /** @name Other */
  //@{

  /** Returns true if this billing period is strictly within the model's run period.*/
  bool withinRunPeriod() const;

  /** Returns true if this billing period is within the model's run period assuming periodic boundary conditions.*/
  bool withinPeriodicRunPeriod() const;

  /** Returns true if this billing period is partially within the model's run period.*/
  bool overlapsRunPeriod() const;

  Vector modelConsumptionValues() const;

  Vector modelPeakDemandValues() const;

  Vector modelTotalCostValues() const;

  /** Returns the sum of modelConsumptionValues if it is not empty. */
  boost::optional<double> modelConsumption() const;

  /** Returns the sum of modelPeakDemandValues if it is not empty. */
  boost::optional<double> modelPeakDemand() const;

  /** Returns the sum of modelTotalCostValues if it is not empty. */
  boost::optional<double> modelTotalCost() const;

  //@}
 protected:
  /// @cond
  typedef detail::UtilityBill_Impl ImplType;

  friend class IdfExtensibleGroup;
  friend class detail::UtilityBill_Impl;

  BillingPeriod(boost::shared_ptr<detail::UtilityBill_Impl> impl,unsigned index);

  /// @endcond
 private:

  REGISTER_LOGGER("openstudio.model.BillingPeriod");
};

/** \relates BillingPeriod */
typedef std::vector<BillingPeriod> BillingPeriodVector;


/** UtilityBill is a ModelObject that wraps the OpenStudio IDD object 'OS:UtilityBill'. 
    This object allows the user to enter in actual fuel usage for model calibration.
*/
class MODEL_API UtilityBill : public ModelObject {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit UtilityBill(const FuelType& fuelType, const Model& model);

  virtual ~UtilityBill() {}

  //@}

  static IddObjectType iddObjectType();

  std::vector<std::string> consumptionUnitValues();

  std::vector<std::string> peakDemandUnitValues();

  /** @name Getters */
  //@{

  FuelType fuelType() const;

  InstallLocationType meterInstallLocation() const;

  bool isMeterInstallLocationDefaulted() const;

  boost::optional<std::string> meterSpecificInstallLocation() const;

  boost::optional<EndUseCategoryType> meterEndUseCategory() const;

  boost::optional<std::string> meterSpecificEndUse() const;

  std::string consumptionUnit() const;

  double consumptionUnitConversionFactor() const;

  bool isConsumptionUnitConversionFactorDefaulted() const;

  boost::optional<std::string> peakDemandUnit() const;

  std::vector<BillingPeriod> billingPeriods() const;

  //@}
  /** @name Setters */
  //@{

  bool setMeterInstallLocation(const InstallLocationType& meterInstallLocation);

  void resetMeterInstallLocation();

  bool setMeterSpecificInstallLocation(const std::string& meterSpecificInstallLocation);

  void resetMeterSpecificInstallLocation();

  bool setMeterEndUseCategory(const EndUseCategoryType& meterEndUseCategory);

  void resetMeterEndUseCategory();

  bool setMeterSpecificEndUse(const std::string& meterSpecificEndUse);

  void resetMeterSpecificEndUse();

  bool setConsumptionUnit(const std::string& consumptionUnit);

  bool setConsumptionUnitConversionFactor(double consumptionUnitConversionFactor);

  void resetConsumptionUnitConversionFactor();

  bool setPeakDemandUnit(const std::string& peakDemandUnit);

  void clearBillingPeriods();

  BillingPeriod addBillingPeriod();

  //@}
  /** @name Other */
  //@{

  /** Gets the meter associated with consumption for this UtilityBill, creates it if it does not exist.*/
  Meter consumptionMeter() const;

  /** Gets the meter associated with peak demand for this UtilityBill, creates it if it does not exist.*/
  Meter peakDemandMeter() const;

  /** Coefficient of variation of the root mean square error, see ASHRAE 14-2002 5.2.11.3.*/
  boost::optional<double> CVRMSE() const;

  /** Normalized mean bias error, see ASHRAE 14-2002 5.2.11.3.*/
  boost::optional<double> NMBE() const;

  //@}
 protected:
  /// @cond
  typedef detail::UtilityBill_Impl ImplType;

  explicit UtilityBill(boost::shared_ptr<detail::UtilityBill_Impl> impl);

  friend class detail::UtilityBill_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.UtilityBill");
};

/** \relates UtilityBill*/
typedef boost::optional<UtilityBill> OptionalUtilityBill;

/** \relates UtilityBill*/
typedef std::vector<UtilityBill> UtilityBillVector;

} // model
} // openstudio

#endif // MODEL_UTILITYBILL_HPP

