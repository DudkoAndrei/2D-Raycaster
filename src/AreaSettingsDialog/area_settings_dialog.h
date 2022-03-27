#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "area_settings.h"

class AreaSettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AreaSettingsDialog(
      QWidget* parent = nullptr,
      const AreaSettings& settings = {});

  const AreaSettings& Settings() const;

 private:
  void ConnectWidgets();
  void PlaceWidgets();

  AreaSettings settings_;

  QVBoxLayout* layout_;
  QPushButton* background_button_;
  QPushButton* polygons_button_;
  QPushButton* light_button_;
  QPushButton* static_light_button_;

  QPushButton* exit_button_;

  QLineEdit* count_edit_;
  QLineEdit* radius_edit_;

  QLabel* count_label_;
  QLabel* radius_label_;
};
