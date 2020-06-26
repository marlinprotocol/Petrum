#pragma once

// use std string and string view for layout
#include <string>

/**
  The Layout is a simple place holder for the distribution layout.

 */
struct Layout {
  Layout(std::string_view const _prefix = {});
  ~Layout();

  /**
   Return file path relative to Layout->prefix

  */
  std::string relative(std::string_view file);

  /**
   update the sysconfdir to a test conf dir

   */
  void update_sysconfdir(std::string_view dir);

  /**
   Return file path relative to dir
   Example usage: Layout::relative_to(default_layout()->sysconfdir, "foo.bar");

  */
  static std::string relative_to(std::string_view dir, std::string_view file);

  /**
   Return file path relative to dir
   Store the path to buf. The buf should be large eough to store
   Example usage: Layout::relative_to(default_layout()->sysconfdir, "foo.bar");

  */
  static void relative_to(char *buf, size_t bufsz, std::string_view dir, std::string_view file);

  /**
   Creates a Layout Object with the given prefix.  If no
   prefix is given, the prefix defaults to the one specified
   at the compile time.

  */
  static void create(std::string_view const prefix = {});

  /**
   Returns the Layout object created by create_default_layout().

  */
  static Layout *get();

  std::string prefix;
  std::string exec_prefix;
  std::string bindir;
  std::string sbindir;
  std::string sysconfdir;
  std::string datadir;
  std::string includedir;
  std::string libdir;
  std::string libexecdir;
  std::string localstatedir;
  std::string runtimedir;
  std::string logdir;
  std::string mandir;
  std::string infodir;
  std::string cachedir;
};
