//
// Created by arthur on 07.12.2019.
//

#include "Meta.h"
Meta::Meta(double pw,
    double ph,
    double xp,
    double yp,
    double xm,
    double ym,
    double lh,
    double sw,
    double bs)
    :
    pw_(pw),
    ph_(ph),
    xp_(xp),
    yp_(yp),
    xm_(xm),
    ym_(ym),
    lh_(lh),
    sw_(sw),
    bs_(bs)
{}
double Meta::pw() const
{ return pw_; }
double Meta::ph() const
{ return ph_; }
double Meta::xp() const
{ return xp_; }
double Meta::yp() const
{ return yp_; }
double Meta::xm() const
{ return xm_; }
double Meta::ym() const
{ return ym_; }
double Meta::lh() const
{ return lh_; }
double Meta::sw() const
{ return sw_; }
double Meta::bs() const
{ return bs_; }
