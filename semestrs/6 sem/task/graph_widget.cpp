// graph_widget.cpp

#include "graph_widget.h"

#include "common_defs.h"
#include <QPainter>
#include <math.h>

QString draw_mode_to_string (draw_mode_t draw_mode)
{
  switch (draw_mode)
  {
  case draw_mode_t::function_first:
    return QString::fromUtf8 ("Function and Polynom");
  case draw_mode_t::function_second:
    return QString::fromUtf8 ("Function and Piece polynom");
  case draw_mode_t::function_all:
    return QString::fromUtf8 ("Function and Polynom and Piece polynom");
  case draw_mode_t::residual:
    return QString::fromUtf8 ("Residual");
  case draw_mode_t::COUNT:
    assert (false);
    return QString ();
  }
  assert (false);
  return QString ();
}

graph_widget_t::graph_widget_t (QWidget *parent, double a, double b, int n, int k)
    : QWidget (parent),
      m_piecewise_linear_residual (&m_func, &m_piecewise_linear_interpolation),
      m_linear_residual (&m_func, &m_linear_interpolation)
{
  m_a = a;
  m_b = b;
  m_n = n;
  m_k = k;
  m_min_x = m_a;
  m_max_x = m_b;

  update_func ();
}

QSize graph_widget_t::minimumSizeHint () const
{
  return QSize (100, 100);
}

QSize graph_widget_t::sizeHint () const
{
  return QSize (1000, 1000);
}

void graph_widget_t::update_and_print_f_max ()
{
  m_f_max = fmax (fabs (m_max_y), fabs(m_min_y));
  printf ("F_max = %le\n", m_f_max);
  fflush (stdout);
}

void graph_widget_t::reset_points ()
{
  m_linear_interpolation.set_points (m_n, m_a, m_b, m_p, m_func_infinity_norm, &m_func);
  m_piecewise_linear_interpolation.set_points (m_n, m_a, m_b, m_p, m_func_infinity_norm, &m_func);
  recompute_bounds ();
  update_and_print_f_max ();
  update ();
}

void graph_widget_t::change_func ()
{
  m_k = (m_k + 1) % function_1d::get_function_count ();
  update_func ();
}

void graph_widget_t::update_func ()
{
  m_s = 0;
  m_func.set_k (m_k);
  m_func_infinity_norm = compute_infinity_norm (&m_func, m_a, m_b);
  reset_points ();

}

void graph_widget_t::increase_points_count ()
{
  if (m_n <= 1e7)
    m_n *= 2;
  reset_points ();
}

void graph_widget_t::decrease_points_count ()
{
  if (m_n % 2 == 0 && m_n >= 6)
    m_n /= 2;
  reset_points ();
}

void graph_widget_t::increase_permutation ()
{
  m_p++;
  reset_points ();
}

void graph_widget_t::decrease_permutation ()
{
  m_p--;
  reset_points ();
}

void graph_widget_t::change_draw_mode ()
{
  m_s = 0;
  m_draw_mode = static_cast<draw_mode_t>((static_cast<int> (m_draw_mode) + 1) % static_cast<int> (draw_mode_t::COUNT));
  recompute_bounds ();
  update_and_print_f_max ();
  update ();
}

QPoint graph_widget_t::graph_to_window (double graph_x, double graph_y)
{
  double x_win = graph_x_to_window_x (graph_x);
  double y_win =  graph_y_to_window_y (graph_y);
  return QPoint (x_win, y_win);
}

int graph_widget_t::canvas_width () const
{
  return width () - m_left_margin - m_right_margin;
}


int graph_widget_t::canvas_height () const
{
  return height () - m_top_margin - m_bottom_margin;
}

int graph_widget_t::graph_x_to_window_x (double graph_x)
{
  return m_left_margin + static_cast<int> ((graph_x - m_min_x) / (m_max_x - m_min_x) * canvas_width ());
}

int graph_widget_t::graph_y_to_window_y (double graph_y)
{
  return m_top_margin + static_cast<int> ((m_axis_max_y - graph_y) / (m_axis_max_y - m_axis_min_y) * canvas_height ());
}

double graph_widget_t::window_x_to_graph_x (int window_x)
{
  return m_min_x + (m_max_x - m_min_x) * (window_x - m_left_margin) / canvas_width ();
}


void graph_widget_t::zoom_in_by_x ()
{
  if (m_s < 30)
    m_s++;
  recompute_bounds ();
  update ();
}


void graph_widget_t::zoom_out_by_x ()
{
  if (m_s > 0)
    m_s--;
  recompute_bounds ();
  update ();
}

void graph_widget_t::recompute_bounds ()
{
  recompute_x_bounds ();
  recompute_y_bounds ();
}

void graph_widget_t::recompute_x_bounds ()
{
  double middle = 0.5 * (m_a + m_b);
  double half_length = 0.5 * (m_b - m_a);
  int zoom_by_x = 1 << abs (m_s);
  half_length /= zoom_by_x;
  m_min_x = middle - half_length;
  m_max_x = middle + half_length;
}

static void update_min_max_by_function_value (
    const abstract_function_1d *func, double x, double &min_y, double &max_y, bool &first_step)
{
  double y = func->evaluate (x);
  if (first_step)
    {
      min_y = max_y = y;
      first_step = false;
    }
  if (y < min_y)
    min_y = y;
  if (y > max_y)
    max_y = y;
}

void graph_widget_t::recompute_y_bounds ()
{
  int pixel_min = graph_x_to_window_x (m_min_x);
  int pixel_max = graph_x_to_window_x (m_max_x);

  bool first_step = true;
  for (int pixel = pixel_min; pixel <= pixel_max; pixel++)
    {
      double x = window_x_to_graph_x (pixel);
      switch (m_draw_mode)
        {
        case draw_mode_t::function_first:
          update_min_max_by_function_value (&m_func, x, m_min_y, m_max_y, first_step);
          update_min_max_by_function_value (&m_linear_interpolation, x, m_min_y, m_max_y, first_step);
          break;
        case draw_mode_t::function_second:
          update_min_max_by_function_value (&m_func, x, m_min_y, m_max_y, first_step);
          update_min_max_by_function_value (&m_piecewise_linear_interpolation, x, m_min_y, m_max_y, first_step);
          break;
        case draw_mode_t::function_all:
          update_min_max_by_function_value (&m_func, x, m_min_y, m_max_y, first_step);
          update_min_max_by_function_value (&m_linear_interpolation, x, m_min_y, m_max_y, first_step);
          update_min_max_by_function_value (&m_piecewise_linear_interpolation, x, m_min_y, m_max_y, first_step);
		  break;
        case draw_mode_t::residual:
          update_min_max_by_function_value (&m_piecewise_linear_residual, x, m_min_y, m_max_y, first_step);
          update_min_max_by_function_value (&m_linear_residual, x, m_min_y, m_max_y, first_step);
          break;
        case draw_mode_t::COUNT:
          assert (false);
          break;
        }
    }

  m_axis_max_y = m_max_y;
  m_axis_min_y = m_min_y;
  assert (m_axis_max_y >= m_axis_min_y);
  if (m_axis_max_y - m_axis_min_y < EPSILON_FOR_COMPARE)
    {
      m_axis_max_y += 1.0;
      m_axis_min_y -= 1.0;
    }
}

void graph_widget_t::draw_graph (QPainter &painter, const abstract_function_1d *func)
{
  int pixel_min = graph_x_to_window_x (m_min_x);
  int pixel_max = graph_x_to_window_x (m_max_x);
  for (int pixel = pixel_min + 1; pixel < pixel_max; pixel++)
    {
      double x1 = window_x_to_graph_x (pixel - 1);
      if (x1 < m_min_x || x1 < m_a)
        continue;
      double y1 = func->evaluate (x1);
      double x2 = window_x_to_graph_x (pixel);
      if (x2 > m_max_x || x2 > m_b)
        continue;
      double y2 = func->evaluate (x2);

      QPoint tmp1 = graph_to_window (x1, y1);
      QPoint tmp2 = graph_to_window (x2, y2);

      painter.drawLine(tmp1, tmp2);
    }
}

static double compute_axis_coord (double min_coord, double max_coord)
{
  assert (max_coord >= min_coord);
  double axis_coord = 0.0;
  if (max_coord < 0.0)
    axis_coord = max_coord;
  if (min_coord > 0.0)
    axis_coord = min_coord;
  return axis_coord;
}

static void compute_axis_ticks (
    double min_coord, double max_coord, int n_ticks_per_axis,
    int &ticks_begin, int &ticks_end, double &ticks_step)
{
  double rough_ticks_step = (max_coord - min_coord) / n_ticks_per_axis;
  double n = round (log2 (rough_ticks_step));
  ticks_step = pow (2.0, n);
  ticks_begin = static_cast<int> (ceil (min_coord / ticks_step));
  ticks_end = static_cast<int> (floor(max_coord / ticks_step));
}

void graph_widget_t::draw_x_axis (QPainter &painter)
{
  double x_axis_y = compute_axis_coord (m_axis_min_y, m_axis_max_y);
  painter.drawLine (graph_to_window (m_min_x, x_axis_y), graph_to_window (m_max_x, x_axis_y));

  int ticks_begin = 0;
  int ticks_end = 0;
  double ticks_step = 0.0;
  compute_axis_ticks (m_min_x, m_max_x, 10, ticks_begin, ticks_end, ticks_step);

  for (int i = ticks_begin; i <= ticks_end; i++)
    {
      if (i == 0)
        continue;
      double tick_x =i * ticks_step;
      QPoint p = graph_to_window(tick_x, x_axis_y);
      painter.drawLine (p.x(), p.y() - 5, p.x(), p.y() + 5);
      painter.drawText (p.x(), p.y() - 6, QString::number(tick_x));
    }
}

void graph_widget_t::draw_y_axis (QPainter &painter)
{
  double y_axis_x = compute_axis_coord (m_min_x, m_max_x);
  painter.drawLine (graph_to_window (y_axis_x, m_axis_min_y), graph_to_window (y_axis_x, m_axis_max_y));

  int ticks_begin = 0;
  int ticks_end = 0;
  double ticks_step = 0.0;
  compute_axis_ticks (m_axis_min_y, m_axis_max_y, 10, ticks_begin, ticks_end, ticks_step);

  for (int i = ticks_begin; i <= ticks_end; i++)
    {
      if (i == 0)
        continue;
      double tick_y = i * ticks_step;
      QPoint p = graph_to_window (y_axis_x, tick_y);
      painter.drawLine (p.x() - 5, p.y(), p.x() + 5, p.y());
      painter.drawText (p.x() + 6, p.y(), QString::number(tick_y));
    }
}

void graph_widget_t::draw_canvas (QPainter &painter)
{
  painter.drawRect (m_left_margin, m_top_margin, canvas_width (), canvas_height ());
}

void graph_widget_t::draw_functions_first (QPainter &painter)
{
  QPen pen_red(Qt::red, 0, Qt::SolidLine);
  painter.setPen (pen_red);
  draw_graph (painter, &m_func);

  QPen pen_blue(Qt::blue, 0, Qt::SolidLine);
  painter.setPen (pen_blue);
  draw_graph (painter, &m_linear_interpolation);
}

void graph_widget_t::draw_functions_second (QPainter &painter)
{
  QPen pen_red(Qt::red, 0, Qt::SolidLine);
  painter.setPen (pen_red);
  draw_graph (painter, &m_func);

  QPen pen_blue(Qt::blue, 0, Qt::SolidLine);
  painter.setPen (pen_blue);
  draw_graph (painter, &m_piecewise_linear_interpolation);
}

void graph_widget_t::draw_functions_all (QPainter &painter)
{
  QPen pen_red(Qt::red, 0, Qt::SolidLine);
  painter.setPen (pen_red);
  draw_graph (painter, &m_func);

  QPen pen_green(Qt::green, 0, Qt::SolidLine);
  painter.setPen (pen_green);
  draw_graph (painter, &m_linear_interpolation);

  QPen pen_blue(Qt::blue, 0, Qt::SolidLine);
  painter.setPen (pen_blue);
  draw_graph (painter, &m_piecewise_linear_interpolation);
}

void graph_widget_t::draw_residuals (QPainter &painter)
{
  QPen pen_blue(Qt::blue, 0, Qt::SolidLine);
  painter.setPen (pen_blue);
  draw_graph (painter, &m_linear_residual);

  QPen pen_red(Qt::red, 0, Qt::SolidLine);
  painter.setPen (pen_red);
  draw_graph (painter, &m_piecewise_linear_residual);

}

void graph_widget_t::draw_information (QPainter &painter)
{
  int text_x = 30;
  QPen pen_black(Qt::black, 0, Qt::SolidLine);
  painter.setPen (pen_black);
  painter.drawText (
      text_x, 20,
      QString::fromUtf8 ("k = %1 f(x) = %2, draw mode = %3, n = %4, p =%5")
          .arg(m_k)
          .arg (m_func.get_function_name ())
          .arg (draw_mode_to_string (m_draw_mode))
          .arg (m_n)
          .arg (m_p)
      );

  painter.drawText (
      text_x, 40,
      QString::fromUtf8 ("min_x = %1 max_x = %2 min_y = %3 max_y = %4 F_max = %5")
          .arg (m_min_x).arg (m_max_x)
          .arg (m_min_y).arg (m_max_y)
          .arg (m_f_max)
      );
}

void graph_widget_t::paintEvent (QPaintEvent * /* event */)
{
  QPainter painter (this);

  QPen pen_black(Qt::black, 0, Qt::SolidLine);
  painter.setPen (pen_black);
#if 0
  draw_canvas (painter);
#endif
  draw_x_axis (painter);
  draw_y_axis (painter);

  switch (m_draw_mode)
    {
    case draw_mode_t::function_first:
      draw_functions_first (painter);
      break;
    case draw_mode_t::function_second:
      draw_functions_second (painter);
      break;
    case draw_mode_t::function_all:
      draw_functions_all (painter);
      break;
    case draw_mode_t::residual:
      draw_residuals (painter);
      break;
    case draw_mode_t::COUNT:
      assert (false);
      break;
    }

  draw_information (painter);
}

void graph_widget_t::resizeEvent (QResizeEvent * /*event*/)
{
  recompute_bounds ();
}
