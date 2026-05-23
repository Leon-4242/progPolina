// function_2d.h

#ifndef FUNCTION_2D_H
#define FUNCTION_2D_H

class abstract_function_2d
{
public:
  virtual ~abstract_function_2d () {}
  virtual double evaluate (double x, double y) const = 0;
};

double compute_infinity_norm (
    const abstract_function_2d *func, double a, double b, double c, double d, int n_steps_x = 50, int n_steps_y = 50);

enum class function_id_t
{
  constant,
  linear_x,
  linear_y,
  linear,
  radial,
  quadratic,
  exponent_quadratic,
  cauchy,

  COUNT
};

class function_2d final : public abstract_function_2d
{
public:
  function_2d () = default;
  explicit function_2d (int k);
  virtual double evaluate (double x, double y) const override;
  void set_k (int k) { m_k = static_cast<function_id_t> (k) ; }
  const char *get_function_name () const;

  static int get_function_count () { return static_cast<int> (function_id_t::COUNT); }
private:
  function_id_t m_k = function_id_t::constant;
};

class abstract_interpolation_function_2d : public abstract_function_2d
{
public:
  virtual ~abstract_interpolation_function_2d ();
  virtual double evaluate (double x, double y) const override final;
  void set_points (int nx, int ny, double a, double b, double c, double d, int p, double norm, const abstract_function_2d *func);

protected:
  virtual void compute_points (int nx, int ny, double a, double b, double c, double d, double *points_x, double *points_y) = 0;
  virtual double *allocate_workspace () const = 0;
  virtual double *allocate_coefficients (int nx, int ny) const = 0;
  virtual void compute_coefficients (
      int nx, int ny,
      const double *points_x,
      const double *points_y,
      const double *values,
      double *coeffs,
      double *workspace
      ) = 0;

  virtual double compute_interpolated_value (
      double x,
      double y,
      double a,
      double b,
      double c,
      double d,
      int nx,
      int ny,
      const double *points_x,
      const double *points_y,
      const double *coeffs
      ) const = 0;
private:
  void clear ();

private:
  int m_nx = 0;
  int m_ny = 0;
  double m_a = 0.0;
  double m_b = 0.0;
  double m_c = 0.0;
  double m_d = 0.0;

  int m_p = 0;
  double m_norm = 0.0;
  double *m_points_x = nullptr;
  double *m_points_y = nullptr;
  double *m_coeffs = nullptr;
};

class residual_function_1d final : public abstract_function_2d
{
public:
  residual_function_1d (const abstract_function_2d *func, const abstract_function_2d *approx);
  virtual double evaluate (double x, double y) const override;
private:
  const abstract_function_2d *m_func = nullptr;
  const abstract_function_2d *m_approx = nullptr;
};


#endif // FUNCTION_2D_H
