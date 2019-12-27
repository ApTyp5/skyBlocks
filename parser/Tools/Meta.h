//
// Created by arthur on 07.12.2019.
//

#ifndef META_H
#define META_H


class Meta
{
public:
    Meta() = default;
  Meta(double pw, double ph, double xp, double yp, double xm, double ym, double lh, double sw, double bs);
  double pw() const;
  double ph() const;
  double xp() const;
  double yp() const;
  double xm() const;
  double ym() const;
  double lh() const;
  double sw() const;
  double bs() const;

  void setSW(double sw) {
    sw_ = sw;
  }
 private:
  double pw_;
  double ph_;
  double xp_;
  double yp_;
  double xm_;
  double ym_;
  double lh_;
  double sw_;
  double bs_;
};


#endif //META_H
