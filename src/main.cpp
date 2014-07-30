/*
* This file is part of Random Wordlist Generator
*
* (C) Francesco Mondello 2013 - 2014
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

#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#define VERSION "0.2"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(VERSION);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
