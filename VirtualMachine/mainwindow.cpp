#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextEdit>
#include <QMessageBox>
#include <QApplication>
#include <QInputDialog>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instruction.h"
#include <sstream>
FILE *sourceFile, *outputCode;
QString caminho;

void executeProgram(InstructionVector *instructions, int numberOfInstructions,Ui::MainWindow *ui);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int instructionAddr = 0;
    //sourceFile
    QString file_name =caminho;
    QFile File (file_name);
    QString file_path_ = file_name;
    if (File .open (QIODevice::Truncate| QIODevice::ReadWrite)){
        QTextStream stream (&File);
        stream << ui->textEdit->toPlainText();
    }
    File.flush();
    File.close();
    sourceFile = fopen(caminho.toLocal8Bit().data(), "r");
    if(!sourceFile) {
        printf("\nError! File could not be opened!\n");
        //exit(1);
    }

    InstructionVector instructions[2048] = {0};
    // Stack *stack = NULL;

    readInstructions(sourceFile, instructions, &instructionAddr);

    //printInstructions(instructions, instructionAddr);

    executeProgram(instructions, instructionAddr,ui);
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName (this, "Open the file");
    QFile File (file_name);
    QString file_path_ = file_name;
    caminho = file_name;
     if (File.open (QIODevice::ReadOnly)){
         QTextStream stream (&File);
         QString FileData;

         while (stream.atEnd() == false){
             FileData += stream.readLine () + "\n" ;

         }


        ui->textEdit->setPlainText(FileData);


     }
     else {
          QMessageBox::warning (this,"..", "file not open");
          return;
      }
     ui->listWidget->clear();
     File.close();
}


void MainWindow::on_actionSave_triggered()
{
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


void MainWindow::on_actionCopy_triggered()
{
        ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
        ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
        ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
        ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
        ui->textEdit->redo();
}


void MainWindow::on_actionNew_triggered()
{
    QString file_path_ = "";
    ui->textEdit->setPlainText("");
}


void MainWindow::on_actionSobre_a_Vm_triggered()
{
    QString about_text;
     about_text = "Compilador : Grupo 2\n";
     about_text += "Date  : 23/10/2022\n";
     about_text += "(C) Compilador (R)\n";
    QMessageBox::about (this, "About Compilador",about_text);
}

bool isEqualString(char *str1, char *str2){
    return strcmp(str1, str2) == 0;

}

int searchLabelIndex(InstructionVector *instructions, int numberOfInstructions, char *label){
    for(int i = 0; i < numberOfInstructions; i++){
        if(isEqualString(instructions[i].label, label))
            return i;
    }
    return -1;
}

void printStack(int *s, int addr,Ui::MainWindow *ui) {
    printf("\nSTACK");

    while(addr != -1) {
       std::ostringstream stack_Print;
       stack_Print << "\n       " << addr<<"\t    "<< s[addr];
       printf("\n%d", s[addr]);
       addr--;
       std::string textStack = stack_Print.str();
       ui->listWidget_2->addItem(textStack.c_str());
    }
}

void executeProgram(InstructionVector *instructions, int numberOfInstructions,Ui::MainWindow *ui) {

    int stack[500] = {0}, addr = 0, aux, instructionAddr = 0, n, m;
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();

    while(instructionAddr != numberOfInstructions){
        std::ostringstream instructions_Print,text_PRN,text_STEP,text_STEP2,text_Error;
        std::string textStep,textStep2,textError;
        instructions_Print << "\nInstruction:" << instructions[instructionAddr].label<< instructions[instructionAddr].instruction << instructions[instructionAddr].param1<< instructions[instructionAddr].param2;
        printf("\n\nInstruction: %s %s %s %s", instructions[instructionAddr].label, instructions[instructionAddr].instruction, instructions[instructionAddr].param1, instructions[instructionAddr].param2);
        //getchar();
        if(isEqualString(instructions[instructionAddr].instruction, "LDC     ")) {
            addr++;
            stack[addr] = toInt(instructions[instructionAddr].param1);
        } else if(isEqualString(instructions[instructionAddr].instruction, "LDV     ")) {
            addr++;
            stack[addr] = stack[toInt(instructions[instructionAddr].param1)];
        } else if(isEqualString(instructions[instructionAddr].instruction, "ADD     ")) {
            stack[addr-1] = stack[addr-1] + stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "SUB     ")) {
            stack[addr-1] = stack[addr-1] - stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "MULT    ")) {
            stack[addr-1] = stack[addr-1] * stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "DIVI    ")) {
            int op1 = stack[addr-1], op2 = stack[addr];
                        if(op2 == 0){
                            text_Error <<"\nDivisao Por Zero";
                            std::string textError = text_Error.str();
                            ui->listWidget_3->addItem(textError.c_str());
                            printf("Divisao Por Zero");
                            break;
                        }
                        stack[addr-1] = op1 / op2;
                        addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "INV     ")) {
            stack[addr] = - stack[addr];
        } else if(isEqualString(instructions[instructionAddr].instruction, "AND     ")) {
            if(stack[addr-1] == 1 && stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "OR      ")) {
            if(stack[addr-1] == 1 || stack[addr] == 1){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "NEG     ")) {
            stack[addr] = 1 - stack[addr];
        } else if(isEqualString(instructions[instructionAddr].instruction, "CME     ")) {
            if(stack[addr-1] < stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMA     ")) {
            if(stack[addr-1] > stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CEQ     ")) {
            if(stack[addr-1] == stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CDIF    ")) {
            if(stack[addr-1] != stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMEQ    ")) {
            if(stack[addr-1] <= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CMAQ    ")) {
            if(stack[addr-1] >= stack[addr]){
                stack[addr-1] = 1;
            }else{
                stack[addr-1] = 0;
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "STR     ")) {
            stack[toInt(instructions[instructionAddr].param1)] = stack[addr];
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "JMP     ")) {
            aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
            instructionAddr = aux;//Instrução logo após o "LABEL NULL";
        } else if(isEqualString(instructions[instructionAddr].instruction, "JMPF    ")) {
            if(stack[addr] == 0){
                aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
                instructionAddr = aux;//Instrução logo após o "LABEL NULL";
            }
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "RD      ")) {
            addr++;
            //scanf("%d", &aux);  /////////////////////
            int aux = QInputDialog::getInt(0,"Inserção RD","Value:");
            stack[addr] = aux;
        } else if(isEqualString(instructions[instructionAddr].instruction, "PRN     ")) {
            printf("\n\n\n\n\n\n%d", stack[addr]);
            text_PRN <<"\n" << stack[addr];
            std::string textPRN = text_PRN.str();
            ui->listWidget_3->addItem(textPRN.c_str());
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "START   ")) {
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "ALLOC   ")) {
            //printf("\nANTES ALLOC\n\n");
            text_STEP.clear();
            text_STEP <<"\nANTES ALLOC";
            textStep = text_STEP.str();
            ui->listWidget_2->addItem(textStep.c_str());
            printStack(stack, addr,ui);

            m = toInt(instructions[instructionAddr].param1);
            n = toInt(instructions[instructionAddr].param2);
            for(int k = 0; k < n; k++){
                addr++;
                stack[addr] = stack[m + k];
            }
            text_STEP2.clear();
            text_STEP2 <<"\nDEPOIS ALLOC";
            textStep2 = text_STEP2.str();
            ui->listWidget_2->addItem(textStep2.c_str());
            //printf("\nDEPOIS ALLOC\n\n");
            printStack(stack, addr,ui);

        } else if(isEqualString(instructions[instructionAddr].instruction, "DALLOC  ")) {
            text_STEP.clear();
            text_STEP <<"\nANTES DALLOC";
            textStep = text_STEP.str();
            ui->listWidget_2->addItem(textStep.c_str());
            printf("\nANTES DALLOC\n\n");
            printStack(stack, addr,ui);
            m = toInt(instructions[instructionAddr].param1);
            n = toInt(instructions[instructionAddr].param2);
            for(int k = n - 1; k >= 0; k--){
                stack[m+k] = stack[addr];
                addr--;
            }
            text_STEP2.clear();
            text_STEP2 <<"\nDEPOIS DALLOC";
            textStep2 = text_STEP2.str();
            ui->listWidget_2->addItem(textStep2.c_str());
            printf("\nDEPOIS DALLOC\n\n");
            printStack(stack, addr,ui);
        } else if(isEqualString(instructions[instructionAddr].instruction, "HLT     ")) {
            return;
        } else if(isEqualString(instructions[instructionAddr].instruction, "CALL    ")) {
            addr++;
            stack[addr] = instructionAddr+1;
            aux = searchLabelIndex(instructions, numberOfInstructions, instructions[instructionAddr].param1);
            instructionAddr = aux;//Instrução logo após o "LABEL NULL";
        } else if(isEqualString(instructions[instructionAddr].instruction, "RETURN  ")) {
            instructionAddr = (stack[addr] - 1); //Atualiza no final
            addr--;
        } else if(isEqualString(instructions[instructionAddr].instruction, "RETURNF ")) { //VERIFICAR SE Ë ESSE MESMO O RETORNO QUE PRECISA
            instructionAddr = stack[addr] - 1;
            addr--;
        }

        instructionAddr++;

        std::string textInstructions = instructions_Print.str();
        ui->listWidget->addItem(textInstructions.c_str());

    }


}
