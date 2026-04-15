// graph_widget.h

#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include "function_1d.h"
#include "linear_interpolation_function_1d.h"
#include "piecewise_linear_interpolation_function_1d.h"

typedef double (*func_t) (double);

enum class draw_mode_t
{
  function_first,
  function_second,
  function_all,
  residual,

  COUNT
};

QString draw_mode_to_string (draw_mode_t draw_mode);

class graph_widget_t : public QWidget
{
  Q_OBJECT

private:
  int m_k = 0;
  double m_a = 0.0;
  double m_b = 0.0;
  int m_p = 0;
  int m_n = 0;
  int m_s = 0; // zooming by x in 2^s times

  draw_mode_t m_draw_mode = draw_mode_t::function_first;
  function_1d m_func;
  linear_interpolation_function_1d m_linear_interpolation;
  piecewise_linear_interpolation_function_1d m_piecewise_linear_interpolation;
  residual_function_1d m_piecewise_linear_residual;
  residual_function_1d m_linear_residual;

  double m_func_infinity_norm = 0.0;
  double m_f_max = 0.0;

  double m_min_x = 0.0;
  double m_max_x = 0.0;
  double m_min_y = 0.0;
  double m_max_y = 0.0;
  double m_axis_min_y = 0.0;
  double m_axis_max_y = 0.0;
  double m_left_margin = 10.0;
  double m_right_margin = 100.0;
  double m_top_margin = 60.0;
  double m_bottom_margin = 10.0;
public:
  graph_widget_t (QWidget *parent, double a, double b, int n, int k);

  QSize minimumSizeHint () const;
  QSize sizeHint () const;

  QPoint graph_to_window (double x_graph, double y_graph);
  int graph_x_to_window_x (double graph_x);
  int graph_y_to_window_y (double graph_y);
  double window_x_to_graph_x (int x_window);
  void change_func ();
  void change_draw_mode ();
  void zoom_in_by_x ();
  void zoom_out_by_x ();
  void increase_points_count ();
  void decrease_points_count ();
  void increase_permutation ();
  void decrease_permutation ();

protected:
  void paintEvent (QPaintEvent *event);
  void resizeEvent (QResizeEvent *event);

private:
  void update_func ();
  void reset_points ();
  int canvas_width () const;
  int canvas_height () const;
  void draw_canvas (QPainter &painter);
  void draw_graph (QPainter &painter, const abstract_function_1d *func);

  void draw_functions_first (QPainter &painter);
  void draw_functions_second (QPainter &painter);
  void draw_functions_all (QPainter &painter);

  void draw_residuals (QPainter &painter);
  void draw_x_axis (QPainter &painter);
  void draw_y_axis (QPainter &painter);
  void draw_information (QPainter &painter);
  void recompute_bounds ();
  void recompute_x_bounds ();
  void recompute_y_bounds ();
  void update_and_print_f_max ();
};

#endif // GRAPH_WIDGET_H
