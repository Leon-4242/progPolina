// graph_widget.cpp

#include "graph_widget.h"

#include "common_defs.h"
#include <QPainter>
#include <QPainterPath>
#include <math.h>

QString draw_mode_to_string (draw_mode_t draw_mode)
{
  switch (draw_mode)
  {
  case draw_mode_t::function:
    return QString::fromUtf8 ("Function");
  case draw_mode_t::approximation:
    return QString::fromUtf8 ("Approximation");
  case draw_mode_t::residual:
    return QString::fromUtf8 ("Residual");
  case draw_mode_t::COUNT:
    assert (false);
    return QString ();
  }
  assert (false);
  return QString ();
}

graph_widget_t::graph_widget_t (QWidget *parent,
                                double a, double b, double c, double d,
                                int nx, int ny, int k)
    : QWidget (parent),
      m_piecewise_linear_residual (&m_func, &m_piecewise_linear_interpolation)
{
  m_a = a;
  m_b = b;
  m_c = c;
  m_d = d;
  m_nx = nx;
  m_ny = ny;
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
  m_piecewise_linear_interpolation.set_points (m_nx, m_ny, m_a, m_b, m_c, m_d, m_p, m_func_infinity_norm, &m_func);
  recompute_bounds ();
  update_and_print_f_max ();
  update ();
}

void graph_widget_t::change_func ()
{
  m_k = (m_k + 1) % function_2d::get_function_count ();
  update_func ();
}

void graph_widget_t::update_func ()
{
  m_s = 0;
  m_func.set_k (m_k);
  m_func_infinity_norm = compute_infinity_norm (&m_func, m_a, m_b, m_c, m_d);
  reset_points ();

}

void graph_widget_t::increase_points_count ()
{
  if (m_nx * m_ny * 4 <= 1e7)
    {
      m_nx *= 2;
      m_ny *= 2;
    }
  reset_points ();
}

void graph_widget_t::decrease_points_count ()
{
  if (m_nx % 2 == 0 && m_ny % 2 == 0 && m_nx >= 10 && m_ny >= 10)
    {
      m_nx /= 2;
      m_ny /= 2;
    }
  reset_points ();
}

void graph_widget_t::increase_rendering_points_count ()
{
  if (m_mx * m_my * 4 <= 65536)
    {
      m_mx *= 2;
      m_my *= 2;
    }
  recompute_bounds ();
  update ();
}

void graph_widget_t::decrease_rendering_points_count ()
{
  if (m_mx % 2 == 0 && m_my % 2 == 0 && m_mx >= 4 && m_my >= 4)
    {
      m_mx /= 2;
      m_my /= 2;
    }
  recompute_bounds ();
  update ();
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
  return m_top_margin + static_cast<int> ((m_max_y - graph_y) / (m_max_y - m_min_y) * canvas_height ());
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
  recompute_z_bounds ();
}

void graph_widget_t::recompute_x_bounds ()
{
  double middle = 0.5 * (m_a + m_b);
  double half_length = 0.5 * (m_b - m_a);
  int zoom = 1 << abs (m_s);
  half_length /= zoom;
  m_min_x = middle - half_length;
  m_max_x = middle + half_length;
}

void graph_widget_t::recompute_y_bounds ()
{
  double middle = 0.5 * (m_c + m_d);
  double half_length = 0.5 * (m_d - m_c);
  int zoom = 1 << abs (m_s);
  half_length /= zoom;
  m_min_y = middle - half_length;
  m_max_y = middle + half_length;
}

static void update_min_max_by_function_value (
    const abstract_function_2d *func, double x, double y, double &min_z, double &max_z, bool &first_step)
{
  double z = func->evaluate (x, y);
  if (first_step)
    {
      min_z = max_z = z;
      first_step = false;
    }
  if (z < min_z)
    min_z = z;
  if (z > max_z)
    max_z = z;
}

void graph_widget_t::update_min_max_by_functions_value (
    double x, double y, double &min_z, double &max_z, bool &first_step)
{
  switch (m_draw_mode)
  {
  case draw_mode_t::function:
    update_min_max_by_function_value (&m_func, x, y, min_z, max_z, first_step);
    break;
  case draw_mode_t::approximation:
    update_min_max_by_function_value (&m_piecewise_linear_interpolation, x, y, min_z, max_z, first_step);
    break;
  case draw_mode_t::residual:
    update_min_max_by_function_value (&m_piecewise_linear_residual, x, y, min_z, max_z, first_step);
    break;
  case draw_mode_t::COUNT:
    assert (false);
    break;
  }
}

static void compute_centroid (
    double x1, double y1,
    double x2, double y2,
    double x3, double y3,
    double *px, double *py)
{
  *px = (x1 + x2 + x3) / 3.0;
  *py = (y1 + y2 + y3) / 3.0;
}

static double get_value_in_triangle (
    const abstract_function_2d *func,
    double x1, double y1,
    double x2, double y2,
    double x3, double y3)
{
  double x, y;
  compute_centroid (x1, y1, x2, y2, x3, y3, &x, &y);
  return func->evaluate (x, y);
}

void graph_widget_t::recompute_z_bounds ()
{
  bool first_step = true;

  double len_x = m_b - m_a;
  double len_y = m_d - m_c;

  double dx = len_x / (m_mx - 1);
  double dy = len_y / (m_my - 1);

  for (int I = 1; I < m_mx; I++)
    {
      int i = I - 1;
      double x_i = m_a + i * dx;
      double x_I = m_a + I * dx;
      for (int J = 1; J < m_my; J++)
        {
          int j = J - 1;
          double y_j = m_c + j * dy;
          double y_J = m_c + J * dy;
          double x, y;
          compute_centroid (x_i, y_j, x_i, y_J, x_I, y_J, &x , &y);
          update_min_max_by_functions_value (x, y, m_min_z, m_max_z, first_step);
          compute_centroid (x_i, y_j, x_I, y_j, x_I, y_J, &x, &y);
          update_min_max_by_functions_value (x, y, m_min_z, m_max_z, first_step);
        }
    }

  m_palette_max_z = m_max_z;
  m_palette_min_z = m_min_z;
  assert (m_palette_max_z >= m_palette_min_z);
  if (m_palette_max_z - m_palette_min_z < EPSILON_FOR_COMPARE)
    {
      m_palette_max_z += 1.0;
      m_palette_min_z -= 1.0;
    }
}


void graph_widget_t::draw_triangle (QPainter &painter, const abstract_function_2d *func,
                               double x1, double y1,
                               double x2, double y2,
                               double x3, double y3)
{
  double value = get_value_in_triangle (func, x1, y1, x2, y2, x3, y3);
  assert (value >= m_palette_min_z);
  assert (value <= m_palette_max_z);
  QColor max_col (Qt::red);
  QColor min_col (Qt::darkBlue);
  int max_r, max_g, max_b;
  int min_r, min_g, min_b;
  max_col.getRgb (&max_r, &max_g, &max_b);
  min_col.getRgb (&min_r, &min_g, &min_b);
  double coeff = (value - m_palette_min_z) / (m_palette_max_z - m_palette_min_z);
  int r = (int) (min_r + (max_r - min_r) * coeff);
  int g = (int) (min_g + (max_g - min_g) * coeff);
  int b = (int) (min_b + (max_b - min_b) * coeff);
  QColor col = QColor::fromRgb (r, g, b);

  QPolygon triangle;
  triangle << QPoint (graph_x_to_window_x (x1), graph_y_to_window_y (y1));
  triangle << QPoint (graph_x_to_window_x (x2), graph_y_to_window_y (y2));
  triangle << QPoint (graph_x_to_window_x (x3), graph_y_to_window_y (y3));
  QBrush brush (col);
  QPen pen(col, 0, Qt::SolidLine);
  painter.setBrush (brush);
  painter.setPen (pen);
  painter.drawPolygon (triangle);
}


void graph_widget_t::draw_graph (QPainter &painter, const abstract_function_2d *func)
{
  double len_x = m_b - m_a;
  double len_y = m_d - m_c;

  double dx = len_x / (m_mx - 1);
  double dy = len_y / (m_my - 1);

  for (int J = 1; J < m_my; J++)
    {
      int j = J - 1;
      double y_j = m_c + j * dy;
      double y_J = m_c + J * dy;
      for (int I = 1; I < m_mx; I++)
        {
          int i = I - 1;
          double x_i = m_a + i * dx;
          double x_I = m_a + I * dx;

          draw_triangle (painter, func, x_i, y_j, x_i, y_J, x_I, y_J);
          draw_triangle (painter, func, x_i, y_j, x_I, y_j, x_I, y_J);
        }
    }
}

void graph_widget_t::draw_canvas (QPainter &painter)
{
  painter.drawRect (m_left_margin, m_top_margin, canvas_width (), canvas_height ());
}

void graph_widget_t::draw_information (QPainter &painter)
{
  int text_x = 30;
  QPen pen_black(Qt::black, 0, Qt::SolidLine);
  painter.setPen (pen_black);
  painter.drawText (
      text_x, 20,
      QString::fromUtf8 ("k = %1 f(x) = %2, draw mode = %3, nx = %4, ny = %5, mx = %6, my = %7, p =%8")
          .arg(m_k)
          .arg (m_func.get_function_name ())
          .arg (draw_mode_to_string (m_draw_mode))
          .arg (m_nx)
          .arg (m_ny)
          .arg (m_mx)
          .arg (m_my)
          .arg (m_p)
      );

  painter.drawText (
      text_x, 40,
      QString::fromUtf8 ("minx = %1 max_x = %2 min_y = %3 max_z = %4 min_z = %5 max_y = %6 F_max = %7")
          .arg (m_min_x).arg (m_max_x)
          .arg (m_min_y).arg (m_max_y)
          .arg (m_min_z).arg (m_max_z)
          .arg (m_f_max)
      );
}

void graph_widget_t::paintEvent (QPaintEvent * /* event */)
{
  QPainter painter (this);

  QPen pen_black(Qt::black, 0, Qt::SolidLine);
  painter.setPen (pen_black);
#if 1
  draw_canvas (painter);
#endif

  switch (m_draw_mode)
    {
    case draw_mode_t::function:
      draw_graph (painter, &m_func);
      break;
    case draw_mode_t::approximation:
      draw_graph (painter, &m_piecewise_linear_interpolation);
      break;
    case draw_mode_t::residual:
      draw_graph (painter, &m_piecewise_linear_residual);
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
