/*
* This file is part of Random Wordlist Generator
*
* (C) Francesco Mondello 2013
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: Faster <faster3ck@gmail.com>
*
*/

#include <QDesktopServices>
#include <QUrl>
#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    ui->labelVersion->setText(tr("Version") + " " + QCoreApplication::applicationVersion());
}

DialogInfo::~DialogInfo()
{
    delete ui;
}

void DialogInfo::on_pushButton_clicked()
{
    // https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=TZ9BUC4YDYJF2
    QDesktopServices::openUrl(QUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=TZ9BUC4YDYJF2", QUrl::TolerantMode));
}

void DialogInfo::on_pushOk_clicked()
{
    close();
}
