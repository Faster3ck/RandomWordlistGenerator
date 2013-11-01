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

#include "wordgenerator.h"
#include "randomize.h"

WordGenerator::WordGenerator(QObject *parent) :
    QThread(parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(passwordCompleted()));
}

void WordGenerator::run()
{
    qsrand(QTime::currentTime().msec());
    generatePassword();
}

void WordGenerator::generatePassword()
{
    m_password = "";

    for (int i = 0; i < m_length; i++) {
        m_password += randomSymbol();
    }

    if (m_list.contains(m_password))
        generatePassword();
    else
        m_list << m_password;
}

void WordGenerator::defineCharsets()
{
    QString alpha_m = "abcdefghijklmnopqrstuvwxyz";
    QString alpha_M = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString numbers = "0123456789";
    QString common_symb = " -_@?!";

    m_charsetList.clear();
    m_list.clear();

    if (!m_use_custom_symb) {
        if (!m_use_all_print) {
            if (m_use_alpha_m)
                m_charsetList << alpha_m;
            if (m_use_alpha_M)
                m_charsetList << alpha_M;
            if (m_use_numbers)
                m_charsetList << numbers;
            if (m_use_common_symb)
                m_charsetList << common_symb;
        }
        else {
            QString all = "";
            for (int i = 32; i <= 126; i++) {
                char c = i;
                all += c;
            }

            m_charsetList << all;
        }
    }
    else
        m_charsetList << m_custom_charset;
}

void WordGenerator::passwordCompleted()
{
    emit sendPassword(m_password);
}

QString WordGenerator::randomSymbol()
{
    int n_charsets, n_symbols;
    QString selectedCharset;
    QString selectedChar;

    n_charsets = m_charsetList.count();

    if (n_charsets > 1)
        selectedCharset = m_charsetList.at(Randomize::randomize(0, n_charsets));
    else
        selectedCharset = m_charsetList.at(0);

    n_symbols = selectedCharset.length();
    selectedChar = selectedCharset.at(Randomize::randomize(0, n_symbols));

    return selectedChar;
}

void  WordGenerator::setCharacterSet_m(bool status)
{
    m_use_alpha_m = status;
}

void  WordGenerator::setCharacterSet_M(bool status)
{
    m_use_alpha_M = status;
}

void  WordGenerator::setNumberSet(bool status)
{
    m_use_numbers = status;
}

void  WordGenerator::setCommonSymbols(bool status)
{
    m_use_common_symb = status;
}

void  WordGenerator::setCustomSet(bool status)
{
    m_use_custom_symb = status;
}

void  WordGenerator::setAllPrintableSet(bool status)
{
    m_use_all_print = status;
}

void  WordGenerator::setPasswordLength(int lenght)
{
    m_length = lenght;
}

void WordGenerator::setCheckDuplicates(bool status)
{
    m_check_duplicates = status;
}

void WordGenerator::addCustomCharset(QString customCharset)
{
    m_custom_charset = customCharset;
}
