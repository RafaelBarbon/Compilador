#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextEdit>
#include <QMessageBox>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error.h"
#include "symbol.h"
#include "sintatico.h"
#include "token.h"
#include "verifyChar.h"
#include "sintatico.h"

//QString local="C:";
//QString nome="compilador.txt";

// Control variables
Token *tokenList = NULL;
Symbol *symbolList = NULL;
ExpressionAnalyzer *inFix = NULL;

int lineCount = 1;
FILE *sourceFile;
bool flagUpdate = true; // Flag to allow the update cursor
bool debug = false;
bool insertArray = false;
bool error = false;

void updateCursor(char *c) {
    *c = getc(sourceFile);
    if(*c == '\n')
        lineCount++;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::information(this,"Teste", item->text());
    qDebug()<<item->text();
}

void MainWindow::on_actionNew_triggered(){
    QString file_path_ = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered(){
    QString file_name = QFileDialog::getOpenFileName (this, "Open the file");
    QFile File (file_name);
    QString file_path_ = file_name;
     if (File.open (QIODevice::ReadOnly)){
         QTextStream stream (&File);
         QString FileData;
         while (stream.atEnd() == false){
             FileData += stream.readLine () + "\n";
         }
        ui->textEdit->setText(FileData);
     }
     else {
          QMessageBox::warning (this,"..", "file not open");
          return;
      }
     File.close();
}

void MainWindow::on_actionSave_As_triggered(){
    QString file_name = QFileDialog::getSaveFileName (this, "Open the file");
    QFile File (file_name);
    QString file_path_ = file_name;
    if (File .open (QIODevice::Truncate| QIODevice::ReadWrite)){
        QTextStream stream (&File);
        stream << ui->textEdit->toPlainText();
    }
    File.flush();
    File.close();
}

void MainWindow::on_actionDelete_File_triggered(){
    QString file_name = QFileDialog::getSaveFileName (this, "Open the file");
    QFile File (file_name);
    QString file_path_ = file_name;
    File.remove();
}

void MainWindow::on_actionCopy_triggered(){
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered(){
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered(){
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered(){
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered(){
    ui->textEdit->undo();
}


void MainWindow::on_actionCompiler_triggered(){
    QString about_text;
     about_text = "Compilador : Grupo 2\n";
     about_text += "Date  : 23/10/2022\n";
     about_text += "(C) Compilador (R)\n";
    QMessageBox::about (this, "About Compilador",about_text);

}



void MainWindow::on_textBrowser_textChanged()
{


}

void MainWindow::on_actionRun_triggered()
{
    int argc;
    char *argv[99];

    QWidget *parent;
        ui->setupUi(this);
        //this->setCentralWidget(ui->textEdit);

        for (int i= 1; i<=10; i++){
            QIcon ic = QApplication::style()->standardPixmap(QStyle::SP_DirHomeIcon);
            ui->listWidget->addItem("Erro-"+QString::number(i));
            ui->listWidget->item(i - 1)->setIcon(ic);
        }

    QMessageBox::information(this,"Teste", "2");
    qDebug()<<"2";


    //path file -> renomeia pra run.txt

if(argc < 1) {
        detectError(6, 0, '\0');
        exit(1);
    } else if(argc > 2 && strcmp(argv[2],"1") == 0) {
        debug = true;
        printf("\n\nWARN - Modo debug ativo\n\n");
    }

    sourceFile = fopen("C:", "r");

    if(!sourceFile) {
        detectError(7, 0, '\0');
        exit(1);
    }
    else if(debug)
        printf("DEBUG - Arquivo aberto com sucesso.\n");

    char c;

    updateCursor(&c);

    syntacticAnalyzer(&c, &tokenList, &symbolList, &inFix);
    char ret[30] = {0};

    // TODO Geração de código

    fclose(sourceFile);

    //printToken(tokenList);
    printf("\n\n%s\n\n", error ? "FALHOU" : "COMPILOU");

    freeToken(&tokenList);
    freeSymbol(&symbolList);
}

