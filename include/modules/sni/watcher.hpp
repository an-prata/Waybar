#pragma once

#include <dbus-status-notifier-watcher.h>
#include <giomm.h>
#include <glibmm/refptr.h>

namespace waybar::modules::SNI {

class Watcher {
 public:
  Watcher();
  ~Watcher();

 private:
  typedef enum { GF_WATCH_TYPE_HOST, GF_WATCH_TYPE_ITEM } GfWatchType;

  typedef struct {
    GfWatchType type;
    Watcher *   watcher;
    gchar *     service;
    gchar *     bus_name;
    gchar *     object_path;
    guint       watch_id;
  } GfWatch;

  void            busAcquired(const Glib::RefPtr<Gio::DBus::Connection> &, Glib::ustring);
  static gboolean handleRegisterHost(Watcher *, GDBusMethodInvocation *, const gchar *);
  static gboolean handleRegisterItem(Watcher *, GDBusMethodInvocation *, const gchar *);
  static GfWatch *gfWatchFind(GSList *list, const gchar *bus_name, const gchar *object_path);
  static GfWatch *gfWatchNew(GfWatchType, const gchar *, const gchar *, const gchar *, Watcher *);
  static void     nameVanished(GDBusConnection *connection, const char *name, gpointer data);
  static void     gfWatchFree(gpointer data);

  void updateRegisteredItems(SnWatcher *obj);

  uint32_t   bus_name_id_;
  uint32_t   watcher_id_;
  GSList *   hosts_ = nullptr;
  GSList *   items_ = nullptr;
  SnWatcher *watcher_ = nullptr;
  gulong     handler_item_id_;
  gulong     handler_host_id_;
};

}  // namespace waybar::modules::SNI
