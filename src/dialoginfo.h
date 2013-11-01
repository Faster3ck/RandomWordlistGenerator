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

#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>

namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogInfo(QWidget *parent = 0);
    ~DialogInfo();
    
private slots:
    void on_pushButton_clicked();

    void on_pushOk_clicked();

private:
    Ui::DialogInfo *ui;
};

#endif // DIALOGINFO_H
