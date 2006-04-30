
/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef qla_termstructures_hpp
#define qla_termstructures_hpp

#include <qla/zerocurve.hpp>
#include <ql/termstructure.hpp>
#include <ql/TermStructures/piecewiseflatforward.hpp>
#include <ql/TermStructures/forwardspreadedtermstructure.hpp>
#include <ql/TermStructures/ratehelpers.hpp>
#include <ql/Functions/termstructures.hpp>

#include <oh/objhandler.hpp>

namespace QuantLibAddin {

    class RateHelper : public ObjHandler::Object {
      public:
        virtual boost::shared_ptr<void> getReference() const {
            return boost::static_pointer_cast<void>(rateHelper_);
        }
        double setQuote(double quote);
        QuantLib::Handle<QuantLib::Quote> quoteHandle() const {
            return quoteHandle_;
        }
        const QuantLib::RateHelper& getObject() const {
            return *rateHelper_;
        }
      protected:
        boost::shared_ptr<QuantLib::SimpleQuote> quote_;
        boost::shared_ptr<QuantLib::RateHelper> rateHelper_;
        QuantLib::Handle<QuantLib::Quote> quoteHandle_;
    };
    
    class DepositRateHelper : public RateHelper {
      public:
        DepositRateHelper(
            const double &quote,
            const long &maturity,
            const std::string &timeUnitsID,
            const long &fixingDays,
            const std::string &calendarID,
            const std::string &conventionID,
            const std::string &dayCounterID);
    };

    class SwapRateHelper : public RateHelper {
      public:
        SwapRateHelper(
            const double &quote,
            const long &maturity,
            const std::string &timeUnitsID,
            const long &fixingDays,
            const std::string &calendarID,
            const std::string &fixedFrequencyID,
            const std::string &fixedConventionID,
            const std::string &fixedDayCounterID,
            const std::string &floatingFrequencyID,
            const std::string &floatingConventionID,
            const std::string &floatingDayCounterID);
    };

    class FuturesRateHelper : public RateHelper {
      public:
        FuturesRateHelper(
            const double &price,
            const std::string &immDateID,
            const QuantLib::Integer &months,
            const std::string &dayCounterID,
            const std::string &bDayConventionID,
            const std::string &calendarID,
            const QuantLib::Integer &decade);
    };

    class YieldTermStructure : public ObjHandler::Object {
      public:
        virtual boost::shared_ptr<void> getReference() const {
            return boost::static_pointer_cast<void>(termStructure_);
        }
        const QuantLib::YieldTermStructure& getObject() const {return *termStructure_;}
      protected:
        boost::shared_ptr<QuantLib::YieldTermStructure> termStructure_;
    };


    class PiecewiseFlatForward : public YieldTermStructure {
      public:
        PiecewiseFlatForward(
            const long &settlement,
            const std::vector<std::string> &handlesRateHelper,
            const std::string &dayCounterID);
    };
    
    class ForwardCurve : public YieldTermStructure {
      public:
        ForwardCurve(
            const std::vector < long > &dates,
            const std::vector < double > &forwards,
            const std::string &dayCounterID);
    };

    class ForwardSpreadedTermStructure : public YieldTermStructure {
      public:
        ForwardSpreadedTermStructure(
            const std::string &baseTermStructure,
            const double &spread);
    };

    /*
    std::vector<std::string> qlRateHelperSelection(
        const std::vector<std::string> &handlesRateHelper,
        const std::vector<bool>& includeFlag,
        int nFutures) {
        
        std::vector<boost::shared_ptr<QuantLib::RateHelper> > rateHelpersQL;
        std::vector<std::string>::const_iterator i;
        for (i=handlesRateHelper.begin() ; i != handlesRateHelper.end() ; i++) {
            OH_GET_REFERENCE(rateHelper, *i, RateHelper, QuantLib::RateHelper)
            rateHelpersQL.push_back(rateHelper);
        }

        rateHelperSelection(rateHelpersQL, includeFlag, nFutures);
        return handlesRateHelper;
    }
    */

    
    
    
}

#endif

