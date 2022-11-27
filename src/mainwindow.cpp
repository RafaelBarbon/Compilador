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
Token *tokenList = NULL; // Used to store built tokens from source file (lexic and syntatic)
Symbol *symbolList = NULL; // Used to store all identifiers (syntatic and semantic)
ExpressionAnalyzer *inFix = NULL; // Used to store the expressions (semantic)

int lineCount = 1; // Source file line counter
FILE *sourceFile, *outputCode;
bool flagUpdate = true; // Flag to allow cursor update to next character in source file (lexic)
bool debug = false; // Flag to allow logs in debug mode
bool insertArray = false; // Flag used to collect the expressions (attributions, conditionals and loops) (semantic)
bool error = false; // Flag to identify if any errors have occur
int label = 1; // Label for code generation
int address = 0; // Address 0 is used for store function return values
QString caminho;

// Update the cursor in source file to get the next character
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
    caminho = file_name;
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
    caminho= file_name;
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


void MainWindow::on_actionRun_triggered()
{

    sourceFile = fopen(caminho.toLocal8Bit().data(), "r");

    if(!sourceFile) {
        detectError(7, 0, '\0',ui);
        exit(1);
    } else if(debug)
        printf("DEBUG - Arquivo fonte aberto com sucesso.\n");

    outputCode = fopen("AssemblyCode.obj", "w");

    char c;

    updateCursor(&c);
    ui->listWidget->clear();
    syntacticAnalyzer(&c, &tokenList, &symbolList, &inFix, ui);

    fclose(sourceFile);
    fclose(outputCode);

    //printToken(tokenList);
     error ? ui->listWidget->addItem("Falhou "): ui->listWidget->addItem("Compilou") ;



    freeToken(&tokenList);
    freeSymbol(&symbolList);
    freeExpression(&inFix);
    lineCount = 1; // Source file line counter
    flagUpdate = true; // Flag to allow cursor update to next character in source file (lexic)
    debug = false; // Flag to allow logs in debug mode
    insertArray = false; // Flag used to collect the expressions (attributions, conditionals and loops) (semantic)
    error = false; // Flag to identify if any errors have occur
    label = 1; // Label for code generation
    address = 0; // Address 0 is used for store function return values
}

