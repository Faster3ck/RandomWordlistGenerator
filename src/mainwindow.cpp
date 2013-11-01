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

#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoginfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->reset();

    wordGen = new WordGenerator(this);

    connect(wordGen, SIGNAL(sendPassword(QString)), this, SLOT(setCurrentPassword(QString)));

    wordlist_thread_started = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPasswordGeneration()
{
    m_index = 0;
    m_max_index = ui->spinNumber->value();

    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(m_max_index);

    setCharacterSets();

    generatePassword();
}

void MainWindow::generatePassword()
{
    if ((m_index < m_max_index) && wordlist_thread_started) {
        disableInterface(false);
        wordGen->start();
    }
    else
    {
        ui->pushGenerate->setText(tr("Generate wordlist"));
        ui->statusBar->showMessage(tr("Stopped"), 2000);
        disableInterface(true);
    }
}

void MainWindow::setCharacterSets()
{
    wordGen->setCharacterSet_m(ui->checkaz->isChecked());
    wordGen->setCharacterSet_M(ui->checkAZ->isChecked());
    wordGen->setNumberSet(ui->check09->isChecked());
    wordGen->setCommonSymbols(ui->checkCommon->isChecked());
    wordGen->setCustomSet(ui->checkCustomChar->isChecked());
    wordGen->setAllPrintableSet(ui->checkAll->isChecked());
    wordGen->setCheckDuplicates(ui->checkDuplicates->isChecked());

    if (ui->checkCustomChar->isChecked())
        wordGen->addCustomCharset(ui->lineCustomSet->text());

    wordGen->setPasswordLength(ui->spinMin->value());

    wordGen->defineCharsets();  // Setup che choosen charsets and options
}

void MainWindow::setCurrentPassword(QString password)
{
    QString fileName = ui->lineSaveFile->text();

    QFile file(fileName);
    if (!file.open(QFile::Append | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));

        wordlist_thread_started = false;

        ui->pushGenerate->setText(tr("Generate wordlist"));
        ui->statusBar->showMessage(tr("Stopped"), 2000);

        return;
    }

    m_index++;
    ui->progressBar->setValue(m_index);

    QString numberPass = QString("%1/%2")
            .arg(QString::number(m_index))
            .arg(QString::number(m_max_index));

    ui->label_Npass->setText(numberPass);
    ui->statusBar->showMessage(tr("Current password: ") + password, 500);

    QTextStream out(&file);
    out << password << endl;

    generatePassword();
}

// Check if at least 1 charset is selected and similar features
bool MainWindow::checkCurrentSets()
{
    if (!ui->checkaz->isChecked() && !ui->checkAZ->isChecked() &&
            !ui->check09->isChecked() && !ui->checkCommon->isChecked() &&
            !ui->checkCustomChar->isChecked() && !ui->checkAll->isChecked()) {

        QMessageBox::warning(this, tr("Warning!"),
                                       tr("You must select at least one charset"),
                                       QMessageBox::Ok);

        return false;
    }

    if (ui->checkCustomChar->isChecked()) {
        if (ui->lineCustomSet->text().length() < 3) {
            QMessageBox::warning(this, tr("Warning!"),
                                           tr("Your custom charset have to contain at least 3 symbols"),
                                           QMessageBox::Ok);

            return false;
        }
    }

    return true;
}

void MainWindow::setGuiCheckstates_ALL()
{
    bool other = false;

    if (ui->checkAll->isChecked()) {
        other = false;

        ui->checkaz->setEnabled(other);
        ui->checkAZ->setEnabled(other);
        ui->check09->setEnabled(other);
        ui->checkCommon->setEnabled(other);
        ui->checkCustomChar->setEnabled(other);
    }
    else {
        other = true;

        ui->checkaz->setEnabled(other);
        ui->checkAZ->setEnabled(other);
        ui->check09->setEnabled(other);
        ui->checkCommon->setEnabled(other);
        ui->checkCustomChar->setEnabled(other);
    }
}

void MainWindow::setGuiCheckstates_CUSTOM()
{
    bool other = false;

    if (ui->checkCustomChar->isChecked()) {
        other = false;

        ui->checkaz->setEnabled(other);
        ui->checkAZ->setEnabled(other);
        ui->check09->setEnabled(other);
        ui->checkCommon->setEnabled(other);
        ui->checkAll->setEnabled(other);

        ui->lineCustomSet->setEnabled(true);
    }
    else {
        other = true;

        ui->checkaz->setEnabled(other);
        ui->checkAZ->setEnabled(other);
        ui->check09->setEnabled(other);
        ui->checkCommon->setEnabled(other);
        ui->checkAll->setEnabled(other);

        ui->lineCustomSet->setEnabled(false);
    }
}

void MainWindow::on_pushGenerate_clicked()
{
    if (!wordlist_thread_started) {
        if (!ui->lineSaveFile->text().isEmpty()) {
            if (checkCurrentSets()) {
                wordlist_thread_started = true;
                startPasswordGeneration();
                ui->pushGenerate->setText(tr("Stop"));
            }
        }
        else
            QMessageBox::warning(this, tr("Warning!"),
                                           tr("Your have to select an output file"),
                                           QMessageBox::Ok);
    }
    else {
        wordlist_thread_started = false;
    }
}

void MainWindow::on_checkAll_clicked()
{
    setGuiCheckstates_ALL();
}

void MainWindow::on_checkCustomChar_clicked()
{
    setGuiCheckstates_CUSTOM();
}

void MainWindow::saveFileOutput()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Text File"), QDir::homePath(), tr("Text files (*.txt *)"));
    if (!fileName.isEmpty()) {
        ui->lineSaveFile->setText(fileName);
    }
}

void MainWindow::disableInterface(bool status)
{
    ui->groupBox->setEnabled(status);
    ui->groupBox_2->setEnabled(status);
    ui->groupBox_3->setEnabled(status);
}

void MainWindow::on_pushSave_clicked()
{
    saveFileOutput();
}

void MainWindow::on_action_Close_triggered()
{
    close();
}

void MainWindow::on_action_About_triggered()
{
    DialogInfo dlg;
    dlg.exec();
}
