#include "area_settings_dialog.h"

#include <QColorDialog>
#include <QString>

AreaSettingsDialog::AreaSettingsDialog(
    QWidget* parent,
    const AreaSettings& settings)
    : QDialog(parent),
      settings_(settings),
      background_button_(new QPushButton{"Background color", this}),
      polygons_button_(new QPushButton{"Polygons color", this}),
      light_button_(new QPushButton{"Light color", this}),
      static_light_button_(new QPushButton{"Static light color", this}),
      exit_button_(new QPushButton{"Exit", this}),
      layout_(new QVBoxLayout{this}),
      count_label_(new QLabel{"Fuzzy points count:", this}),
      radius_label_(new QLabel{"Light source radius:", this}),
      count_edit_(new QLineEdit(QString::number(settings_.fuzzy_points_count),
                                this)),
      radius_edit_(new QLineEdit(QString::number(settings_.light_source_radius),
                                 this)) {
  setWindowTitle("Settings");

  PlaceWidgets();
  ConnectWidgets();
}

const AreaSettings& AreaSettingsDialog::Settings() const {
  return settings_;
}

void AreaSettingsDialog::PlaceWidgets() {
  layout_->addWidget(background_button_, 0);
  layout_->addWidget(polygons_button_, 1);
  layout_->addWidget(light_button_, 2);
  layout_->addWidget(static_light_button_, 3);
  layout_->addWidget(count_label_, 4);
  layout_->addWidget(count_edit_, 5);
  layout_->addWidget(radius_label_, 6);
  layout_->addWidget(radius_edit_, 7);
  layout_->addWidget(exit_button_, 8);

  background_button_->setAutoDefault(false);
  polygons_button_->setAutoDefault(false);
  light_button_->setAutoDefault(false);
  static_light_button_->setAutoDefault(false);
  exit_button_->setAutoDefault(false);

  setLayout(layout_);
}

void AreaSettingsDialog::ConnectWidgets() {
  connect(background_button_, &QPushButton::clicked, [&]() {
    auto temp =
        QColorDialog::getColor(settings_.background_color,
                               this,
                               "Background color");
    if (temp.isValid()) {
      settings_.background_color = temp;
    }
  });

  connect(polygons_button_, &QPushButton::clicked, [&]() {
    auto temp =
        QColorDialog::getColor(settings_.polygons_color,
                               this,
                               "Polygons color");
    if (temp.isValid()) {
      settings_.polygons_color = temp;
    }
  });

  connect(light_button_, &QPushButton::clicked, [&]() {
    auto temp =
        QColorDialog::getColor(settings_.light_color, this, "Light color");
    if (temp.isValid()) {
      settings_.light_color = temp;
    }
  });

  connect(static_light_button_, &QPushButton::clicked, [&]() {
    auto temp =
        QColorDialog::getColor(settings_.static_light_color,
                               this,
                               "Static light color");
    if (temp.isValid()) {
      settings_.static_light_color = temp;
    }
  });

  connect(count_edit_, &QLineEdit::textEdited, [&]() {
    int count = (count_edit_->text()).toInt();
    if (count < 0) {
      count = 0;
      count_edit_->setText("0");
    }

    settings_.fuzzy_points_count = count;
  });

  connect(radius_edit_, &QLineEdit::textEdited, [&]() {
    settings_.light_source_radius = (radius_edit_->text()).toDouble();
  });

  connect(exit_button_, &QPushButton::clicked, [&]() {
    close();
  });
}
