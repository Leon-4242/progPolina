// function_1d.h

#ifndef FUNCTION_1D_H
#define FUNCTION_1D_H

class abstract_function_1d
{
public:
  virtual ~abstract_function_1d () {}
  virtual double evaluate (double x) const = 0;
};

double compute_infinity_norm (
    const abstract_function_1d *func, double a, double b, int n_steps = 1000);

enum class function_id_t
{
  constant,
  linear,
  quadratic,
  cubic,
  fourth_degree,
  exponent,
  cauchy,

  COUNT
};

class function_1d final : public abstract_function_1d
{
public:
  function_1d () = default;
  explicit function_1d (int k);
  virtual double evaluate (double x) const override;
  void set_k (int k) { m_k = static_cast<function_id_t> (k) ; }
  const char *get_function_name () const;

  static int get_function_count () { return static_cast<int> (function_id_t::COUNT); }
private:
  function_id_t m_k = function_id_t::constant;
};

class abstract_interpolation_function_1d : public abstract_function_1d
{
friend class piecewise_linear_interpolation_function_1d;
public:
  virtual ~abstract_interpolation_function_1d ();
  virtual double evaluate (double x) const override final;
  void set_points (int n, double a, double b, int p, double norm, const abstract_function_1d *func);

protected:
  virtual void compute_points (int n, double a, double b, double *points) = 0;
  virtual double *allocate_workspace (int n) const = 0;
  virtual double *allocate_coefficients (int n) const = 0;
  virtual void compute_coefficients (
      int n,
      const double *points,
      const double *values,
      double *coeffs,
      double *workspace
      ) = 0;

  virtual double compute_interpolated_value (
      double x,
      double a,
      double b,
      int n,
      const double *points,
      const double *coeffs
      ) const = 0;
private:
  void clear ();

private:
  int m_n = 0;
  double m_a = 0.0;
  double m_b = 0.0;
  int m_p = 0;
  double m_norm = 0.0;
  double *m_points = nullptr;
  double *m_coeffs = nullptr;
};

class residual_function_1d final : public abstract_function_1d
{
public:
  residual_function_1d (const abstract_function_1d *func, const abstract_function_1d *approx);
  virtual double evaluate (double x) const override;
private:
  const abstract_function_1d *m_func = nullptr;
  const abstract_function_1d *m_approx = nullptr;
};


#endif // FUNCTION_1D_H
