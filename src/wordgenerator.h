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

#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

#include <QObject>
#include <QThread>
#include <QStringList>

class WordGenerator : public QThread
{
    Q_OBJECT
public:
    explicit WordGenerator(QObject *parent = 0);
    void run();
    void defineCharsets();
    void setCharacterSet_m(bool status);
    void setCharacterSet_M(bool status);
    void setNumberSet(bool status);
    void setCommonSymbols(bool status);
    void setCustomSet(bool status);
    void setAllPrintableSet(bool status);
    void setPasswordLength(int length);
    void setCheckDuplicates(bool status);
    void addCustomCharset(QString customCharset);

private:   
    void generatePassword();
    QString randomSymbol();

    QString m_password;
    QString m_custom_charset;
    QStringList m_charsetList;
    QStringList m_list; // used for check duplicates
    bool m_use_alpha_m;
    bool m_use_alpha_M;
    bool m_use_numbers;
    bool m_use_common_symb;
    bool m_use_custom_symb;
    bool m_use_all_print;
    bool m_check_duplicates;
    int m_length;

signals:
    void sendPassword(QString);
    
private slots:
    void passwordCompleted();
};

#endif // WORDGENERATOR_H
