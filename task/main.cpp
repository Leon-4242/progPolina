// main.cpp

#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>

#include "common_defs.h"
#include "graph_widget.h"

#define DEFAULT_A (-5.5)
#define DEFAULT_B (5.5)
#define DEFAULT_N (10)
#define DEFAULT_K (0)


static int parse_command_line (int argc, char **argv, double *pa, double *pb, int *pn, int *pk)
{
  if (argc == 1)
    return 0;

  if (argc != 4)
    {
      fprintf (stderr, "Wrong number of arguments!\n");
      return -1;
    }

  double a, b;
  int n;
  int k;

  if (sscanf (argv[1], "%lf", &a) != 1)
    {
      fprintf (stderr, "Invalid value for a!\n");
      return -1;
    }

  if (sscanf (argv[2], "%lf", &b) != 1)
    {
      fprintf (stderr, "Invalid value for b!\n");
      return -1;
    }

  if (sscanf (argv[3], "%d", &n) != 1)
    {
      fprintf (stderr, "Invalid value for n!\n");
      return -1;
    }

  if (sscanf (argv[4], "%d", &k) != 1)
    {
      fprintf (stderr, "Invalid value for k!\n");
      return -1;
    }


  double segment_length = b - a;
  if (segment_length < EPSILON_FOR_COMPARE)
    {
      fprintf (stderr, "Too short segment: %lf\n", segment_length);
      return -1;
    }

  if (n < 3)
    {
      fprintf (stderr, "Too small number of points!\n");
      return -1;
    }

  if (k < 0 || k > 7)
    {
      fprintf (stderr, "Invalid function number (0 <= k <= 7 required)!\n");
      return -1;
    }

  *pa = a;
  *pb = b;
  *pn = n;
  *pk = k;

  return 0;
}

int main (int argc, char **argv)
{
  double a = DEFAULT_A;
  double b = DEFAULT_B;
  int n = DEFAULT_N;
  int k = DEFAULT_K;

  int err = parse_command_line (argc, argv, &a, &b, &n, &k);
  if (err < 0)
    return -1;

#if QT_VERSION_MAJOR == 5
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
  QApplication app (argc, argv);

  QMainWindow *main_window = new QMainWindow;
  graph_widget_t *graph_widget = new graph_widget_t (main_window, a, b, n, k);

  QMenuBar *menu_bar = new QMenuBar (main_window);

  QMenu *file_menu = new QMenu ("&File", menu_bar);
  menu_bar->addMenu(file_menu);
  QAction *exit_action = file_menu->addAction ("E&xit", main_window, &graph_widget_t::close);
  exit_action->setShortcut (QString ("Ctrl+X"));

  QMenu *mode_menu = new QMenu ("&Mode", menu_bar);
  menu_bar->addMenu(mode_menu);
  QAction *change_mode_action = mode_menu->addAction ("&Change", graph_widget, &graph_widget_t::change_draw_mode);
  change_mode_action->setShortcut (QString ("1"));

  QMenu *function_menu = new QMenu ("F&unction", menu_bar);
  menu_bar->addMenu(function_menu);
  QAction *change_function_action = function_menu->addAction ("&Change", graph_widget, &graph_widget_t::change_func);
  change_function_action->setShortcut (QString ("0"));

  QMenu *zoom_menu = new QMenu ("&Zoom", menu_bar);
  menu_bar->addMenu(zoom_menu);
  QAction *zoom_in_action = zoom_menu->addAction ("Zoom &in", graph_widget, &graph_widget_t::zoom_in_by_x);
  zoom_in_action->setShortcut (QString ("2"));
  QAction *zoom_out_action = zoom_menu->addAction ("Zoom &out", graph_widget, &graph_widget_t::zoom_out_by_x);
  zoom_out_action->setShortcut (QString ("3"));

  QMenu *approximation_menu = new QMenu ("&Approximation", menu_bar);
  menu_bar->addMenu(approximation_menu);
  QAction *increase_points_count_action = approximation_menu->addAction ("Increase points count", graph_widget, &graph_widget_t::increase_points_count);
  increase_points_count_action->setShortcut (QString ("4"));
  QAction *decrease_points_count_action = approximation_menu->addAction ("Decrease points count", graph_widget, &graph_widget_t::decrease_points_count);
  decrease_points_count_action->setShortcut (QString ("5"));

  QMenu *permutation_menu = new QMenu ("Permutation", menu_bar);
  menu_bar->addMenu(permutation_menu);
  QAction *increase_permutation_action = permutation_menu->addAction ("Increase permutation", graph_widget, &graph_widget_t::increase_permutation);
  increase_permutation_action->setShortcut (QString ("6"));
  QAction *decrease_permutation_action = permutation_menu->addAction ("Decrease permutation", graph_widget, &graph_widget_t::decrease_permutation);
  decrease_permutation_action->setShortcut (QString ("7"));


  main_window->setMenuBar (menu_bar);
  main_window->setCentralWidget (graph_widget);
  main_window->setWindowTitle ("Graph");

  main_window->show ();
  app.exec ();
  delete main_window;
  return 0;
}
