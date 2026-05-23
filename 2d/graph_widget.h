// graph_widget.h

#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include "function_2d.h"
#include "piecewise_linear_interpolation_function_2d.h"

typedef double (*func_t) (double);

enum class draw_mode_t
{
  function,
  approximation,
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
  double m_c = 0.0;
  double m_d = 0.0;
  int m_p = 0;
  int m_nx = 0;
  int m_ny = 0;
  int m_mx = 64;
  int m_my = 64;
  int m_s = 0; // zooming by x in 2^s times

  draw_mode_t m_draw_mode = draw_mode_t::function;
  function_2d m_func;
  piecewise_linear_interpolation_function_2d m_piecewise_linear_interpolation;
  residual_function_1d m_piecewise_linear_residual;
  double m_func_infinity_norm = 0.0;
  double m_f_max = 0.0;

  double m_min_x = 0.0;
  double m_max_x = 0.0;
  double m_min_y = 0.0;
  double m_max_y = 0.0;
  double m_min_z = 0.0;
  double m_max_z = 0.0;
  double m_palette_min_z = 0.0;
  double m_palette_max_z = 0.0;
  double m_left_margin = 10.0;
  double m_right_margin = 100.0;
  double m_top_margin = 60.0;
  double m_bottom_margin = 10.0;
public:
  graph_widget_t (QWidget *parent, double a, double b, double c, double d, int nx, int ny, int k);

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
  void increase_rendering_points_count ();
  void decrease_rendering_points_count ();
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
  void draw_graph (QPainter &painter, const abstract_function_2d *func);
  void draw_triangle (QPainter &painter, const abstract_function_2d *func,
                      double x1, double y1,
                      double x2, double y2,
                      double x3, double y3);
  void draw_information (QPainter &painter);
  void recompute_bounds ();
  void recompute_x_bounds ();
  void recompute_y_bounds ();
  void recompute_z_bounds ();
  void update_and_print_f_max ();
  void update_min_max_by_functions_value (
      double x, double y, double &min_z, double &max_z, bool &first_step);

};

#endif // GRAPH_WIDGET_H
