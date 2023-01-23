#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QComboBox>
#include <QFileDialog>
#include <QIntValidator>
#include <QLineEdit>
#include <QString>
#include <sstream>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::remove;
using std::string;

bool Boot_Last_OS_bool;
bool Enable_Mouse_bool;
bool Firmware_BootNum_bool;
QString Background;
QString Background_fileName;
QString Boot_Option_1;
QString Boot_Option_2;
QString Boot_Option_3;
QString Boot_Option_4;
QString default_sel;
QString Linux_Select;
QString OS_Icon1;
QString OS_Icon2;
QString OS_Icon3;
QString OS_Icon4;
QString OS_Icon1_fileName;
QString OS_Icon2_fileName;
QString OS_Icon3_fileName;
QString OS_Icon4_fileName;
QString refind_install_source;
QString refind_GUI_timeout;
QString Default_Background = "/home/deck/.SteamDeck_rEFInd/GUI/background.png";
QString Default_OS_Icon1 = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon1.png";
QString Default_OS_Icon2 = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon2.png";
QString Default_OS_Icon3 = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon3.png";
QString Default_OS_Icon4 = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon4.png";
string Default_Background_str = "/home/deck/.SteamDeck_rEFInd/GUI/background.png";
string Default_OS_Icon1_str = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon1.png";
string Default_OS_Icon2_str = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon2.png";
string Default_OS_Icon3_str = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon3.png";
string Default_OS_Icon4_str = "/home/deck/.SteamDeck_rEFInd/GUI/os_icon4.png";
string Background_path;
string Boot_Opt1_str;
string Boot_Opt2_str;
string Boot_Opt3_str;
string Boot_Opt4_str;
string Boot_Stanza_GUI;
string Boot_Stanza_1;
string Boot_Stanza_2;
string Boot_Stanza_3;
string Boot_Stanza_4;
string Config_FW_BootNum;
string default_OS_sel;
string FW_BootNum_SteamOS;
string GUID_Label;
string Linux_Select_str;
string OS_Icon1_path;
string OS_Icon2_path;
string OS_Icon3_path;
string OS_Icon4_path;
string refind_background;
string refind_enable_mouse = "";
string refind_timeout = "5";
string refind_USER = getlogin();
string MICRO_SD_GUID = "SD";
string USB_GUID = "USB";
string Windows_SD_GUID;
string Windows_USB_GUID;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QValidator *validator = new QIntValidator(-1, 99, this);
    ui->TimeOut_lineEdit->setValidator(validator);
    ui->Background_lineEdit->setReadOnly(true);
    ui->Boot_Option_01_Icon_lineEdit->setReadOnly(true);
    ui->Boot_Option_02_Icon_lineEdit->setReadOnly(true);
    ui->Boot_Option_03_Icon_lineEdit->setReadOnly(true);
    ui->Boot_Option_04_Icon_lineEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Background_pushButton_clicked()
{
    QFileDialog Background_File_Dialog(this, tr("Select Background PNG"));
    Background_fileName = Background_File_Dialog.getOpenFileName(this, tr("Select Background PNG"), "/home/chia02", tr("Image (*.png)"));
    if (Background_fileName != "")
    {
        ui->Background_lineEdit->setText(Background_fileName);
    }
}

void MainWindow::on_Boot_Option_01_Icon_pushButton_clicked()
{
    QFileDialog OS_Icon1_File_Dialog(this, tr("Select OS Icon 1 PNG"));
    OS_Icon1_fileName = OS_Icon1_File_Dialog.getOpenFileName(this, tr("Select OS Icon 1 PNG"), "/home/chia02", tr("Image (*.png)"));
    if (OS_Icon1_fileName != "")
    {
        ui->Boot_Option_01_Icon_lineEdit->setText(OS_Icon1_fileName);
    }
}

void MainWindow::on_Boot_Option_02_Icon_pushButton_clicked()
{
    QFileDialog OS_Icon2_File_Dialog(this, tr("Select OS Icon 2 PNG"));
    OS_Icon2_fileName = OS_Icon2_File_Dialog.getOpenFileName(this, tr("Select OS Icon 2 PNG"), "/home/chia02", tr("Image (*.png)"));
    if (OS_Icon2_fileName != "")
    {
        ui->Boot_Option_02_Icon_lineEdit->setText(OS_Icon2_fileName);
    }
}

void MainWindow::on_Boot_Option_03_Icon_pushButton_clicked()
{
    QFileDialog OS_Icon3_File_Dialog(this, tr("Select OS Icon 3 PNG"));
    OS_Icon3_fileName = OS_Icon3_File_Dialog.getOpenFileName(this, tr("Select OS Icon 3 PNG"), "/home/chia02", tr("Image (*.png)"));
    if (OS_Icon3_fileName != "")
    {
        ui->Boot_Option_03_Icon_lineEdit->setText(OS_Icon3_fileName);
    }
}

void MainWindow::on_Boot_Option_04_Icon_pushButton_clicked()
{
    QFileDialog OS_Icon4_File_Dialog(this, tr("Select OS Icon 4 PNG"));
    OS_Icon4_fileName = OS_Icon4_File_Dialog.getOpenFileName(this, tr("Select OS Icon 4 PNG"), "/home/chia02", tr("Image (*.png)"));
    if (OS_Icon4_fileName != "")
    {
        ui->Boot_Option_04_Icon_lineEdit->setText(OS_Icon4_fileName);
    }
}

void MainWindow::on_Install_rEFInd_clicked()
{
    refind_install_source = ui->Install_Source_comboBox->currentText();
    if(refind_install_source == "Pacman")
    {
        system("/home/deck/.SteamDeck_rEFInd/refind_install_pacman_GUI.sh");
    }
    if(refind_install_source == "Sourceforge")
    {
        system("/home/deck/.SteamDeck_rEFInd/refind_install_no_pacman_GUI.sh");
    }
}

void MainWindow::on_Create_Config_clicked()
{
    Background.clear();
    OS_Icon1.clear();
    OS_Icon2.clear();
    OS_Icon3.clear();
    OS_Icon4.clear();
    Background_path.clear();
    OS_Icon1_path.clear();
    OS_Icon2_path.clear();
    OS_Icon3_path.clear();
    OS_Icon4_path.clear();
    ostringstream refind_temp_path;
    refind_temp_path << "/home/" << refind_USER << "/.SteamDeck_rEFInd/GUI/refind.conf";
    string refind_conf_path = refind_temp_path.str();
    ofstream refind_conf(refind_conf_path);
    cout << refind_conf.is_open() << endl;
    refind_conf << "# GUI generated refind.conf Config File\n";
    refind_GUI_timeout = ui->TimeOut_lineEdit->text();
    refind_timeout = refind_GUI_timeout.toStdString();
    if(refind_timeout == "") {
        refind_timeout = "5";
        }
    refind_conf << "timeout " << refind_timeout << "\n"; //GUI variable
    refind_conf << "use_nvram false\n";
    refind_conf << "hideui singleuser,hints,arrows,label,badges\n";
    refind_background = "background.png";
    refind_conf << "banner " << refind_background << "\n"; //GUI background option
    refind_conf << "banner_scale fillscreen\n";
    refind_conf << "resolution 3\n";
    refind_conf << "enable_touch\n";
    Boot_Last_OS_bool = ui->Last_OS_CheckBox->isChecked();
    Enable_Mouse_bool = ui->Enable_Mouse_checkBox->isChecked();
    if(Enable_Mouse_bool) {
        refind_enable_mouse = "";
    }
    else {
        refind_enable_mouse = "#";
    }
    refind_conf << refind_enable_mouse << "enable_mouse\n"; //GUI enable mouse option
    refind_conf << "showtools\n";
    refind_conf << "#scanfor manual,external\n";
    refind_conf << "scanfor manual\n";
    default_sel = ui->Default_Boot_comboBox->currentText();
    Firmware_BootNum_bool = ui->Firmware_bootnum_CheckBox->isChecked();
    Boot_Option_1 = ui->Boot_Option_01_comboBox->currentText();
    Boot_Option_2 = ui->Boot_Option_02_comboBox->currentText();
    Boot_Option_3 = ui->Boot_Option_03_comboBox->currentText();
    Boot_Option_4 = ui->Boot_Option_04_comboBox->currentText();
    default_OS_sel = getDefaultBoot(default_sel, Boot_Last_OS_bool, Firmware_BootNum_bool, Boot_Option_1, Boot_Option_2, Boot_Option_3, Boot_Option_4);
    refind_conf << "default_selection \"" << default_OS_sel << "\"\n"; //GUI variable
    Boot_Stanza_1 = CreateBootStanza(Boot_Option_1, "1", Firmware_BootNum_bool);
    refind_conf << Boot_Stanza_1;
    Boot_Stanza_2 = CreateBootStanza(Boot_Option_2, "2", Firmware_BootNum_bool);
    refind_conf << Boot_Stanza_2;
    Boot_Stanza_3 = CreateBootStanza(Boot_Option_3, "3", Firmware_BootNum_bool);
    refind_conf << Boot_Stanza_3;
    Boot_Stanza_4 = CreateBootStanza(Boot_Option_4, "4", Firmware_BootNum_bool);
    refind_conf << Boot_Stanza_4;
    refind_conf.close();
    Background = ui->Background_lineEdit->text();
    if((Background != "") && (Background != Default_Background)){
        Background_path = Background.toStdString();
        string cmd = string("yes | cp '") + Background_path + "' '" + Default_Background_str + "'";
        system(cmd.c_str());
    }
    OS_Icon1 = ui->Boot_Option_01_Icon_lineEdit->text();
    if((OS_Icon1 != "" ) && (OS_Icon1 != Default_OS_Icon1)){
        OS_Icon1_path = OS_Icon1.toStdString();
        string cmd1 = string("yes | cp '") + OS_Icon1_path + "' '" + Default_OS_Icon1_str + "'";
        system(cmd1.c_str());
        }
    OS_Icon2 = ui->Boot_Option_02_Icon_lineEdit->text();
    if((OS_Icon2 != "" ) && (OS_Icon2 != Default_OS_Icon2)){
        OS_Icon2_path = OS_Icon2.toStdString();
        string cmd2 = string("yes | cp '") + OS_Icon2_path + "' '" + Default_OS_Icon2_str + "'";
        system(cmd2.c_str());
        }
    OS_Icon3 = ui->Boot_Option_03_Icon_lineEdit->text();
    if((OS_Icon3 != "" ) && (OS_Icon3 != Default_OS_Icon3)){
        OS_Icon3_path = OS_Icon3.toStdString();
        string cmd3 = string("yes | cp '") + OS_Icon3_path + "' '" + Default_OS_Icon3_str + "'";
        system(cmd3.c_str());
        }
    OS_Icon4 = ui->Boot_Option_04_Icon_lineEdit->text();
    if((OS_Icon4 != "" ) && (OS_Icon4 != Default_OS_Icon4)){
        OS_Icon4_path = OS_Icon4.toStdString();
        string cmd4 = string("yes | cp '") + OS_Icon4_path + "' '" + Default_OS_Icon4_str + "'";
        system(cmd4.c_str());
        }
}

void MainWindow::on_Install_Config_clicked()
{
    system("/home/deck/.SteamDeck_rEFInd/install_config_from_GUI.sh");
}

string MainWindow::Get_FW_BootNum() {
    FILE *process;
    char buff[1024];
    process = popen("/usr/bin/efibootmgr | grep steam | grep -Eo '[0-9]{1,4}' | head -1", "r");
    if (process != NULL) {
        while (fgets(buff, sizeof(buff), process)) {
            printf("%s", buff);
            FW_BootNum_SteamOS += buff;
        }
        pclose(process);
    }
    return FW_BootNum_SteamOS;
}

string MainWindow::CreateBootStanza(QString &BootOption, const char *BootNum, bool FW_BootNum_bool) {
    Boot_Stanza_GUI.clear();
    Config_FW_BootNum.clear();
    if(BootOption == "SteamOS") {
        Boot_Stanza_GUI.append("\nmenuentry \"SteamOS\" {\n");
        Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
        Boot_Stanza_GUI.append(BootNum);
        Boot_Stanza_GUI.append(".png\n");
        if(FW_BootNum_bool) {
            Config_FW_BootNum = Get_FW_BootNum();
            Boot_Stanza_GUI.append("\tfirmware_bootnum ");
            Boot_Stanza_GUI.append(Config_FW_BootNum);
            Boot_Stanza_GUI.append("}\n");
            return Boot_Stanza_GUI;
        }
        else {
            Boot_Stanza_GUI.append("\tloader /EFI/steamos/steamcl.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
    }
    if(BootOption == "Windows") {
        Boot_Stanza_GUI.append("\nmenuentry \"Windows\" {\n");
        Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
        Boot_Stanza_GUI.append(BootNum);
        Boot_Stanza_GUI.append(".png\n");
        Boot_Stanza_GUI.append("\tloader /EFI/Microsoft/Boot/bootmgfw.efi\n");
        Boot_Stanza_GUI.append("\tgraphics on\n}\n");
        return Boot_Stanza_GUI;
    }
    if(BootOption == "Batocera (SD)") {
        Boot_Stanza_GUI.append("\nmenuentry \"Batocera\" {\n");
        Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
        Boot_Stanza_GUI.append(BootNum);
        Boot_Stanza_GUI.append(".png\n");
        Boot_Stanza_GUI.append("\tvolume \"BATOCERA\"\n");
        Boot_Stanza_GUI.append("\tloader /EFI/BOOT/bootx64.efi\n");
        Boot_Stanza_GUI.append("\tgraphics on\n}\n");
        return Boot_Stanza_GUI;
    }
    if(BootOption == "Windows (SD)") {
        Windows_SD_GUID = getPartitionGUIDLabel(MICRO_SD_GUID);
        Boot_Stanza_GUI.append("\nmenuentry \"Windows Micro SD\" {\n");
        Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
        Boot_Stanza_GUI.append(BootNum);
        Boot_Stanza_GUI.append(".png\n");
        Boot_Stanza_GUI.append("\tvolume ");
        Boot_Stanza_GUI.append(Windows_SD_GUID);
        Boot_Stanza_GUI.append("\tloader /EFI/Microsoft/Boot/bootmgfw.efi\n");
        Boot_Stanza_GUI.append("\tgraphics on\n}\n");
        return Boot_Stanza_GUI;
    }
    if(BootOption == "Windows (USB)") {
        Windows_USB_GUID = getPartitionGUIDLabel(USB_GUID);
        Boot_Stanza_GUI.append("\nmenuentry \"Windows Micro SD\" {\n");
        Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
        Boot_Stanza_GUI.append(BootNum);
        Boot_Stanza_GUI.append(".png\n");
        Boot_Stanza_GUI.append("\tvolume ");
        Boot_Stanza_GUI.append(Windows_USB_GUID);
        Boot_Stanza_GUI.append("\tloader /EFI/Microsoft/Boot/bootmgfw.efi\n");
        Boot_Stanza_GUI.append("\tgraphics on\n}\n");
        return Boot_Stanza_GUI;
    }
    if(BootOption == "Linux") {
        Linux_Select = ui->Linux_Select_comboBox->currentText();
        Linux_Select_str = Linux_Select.toStdString();
        if(Linux_Select_str == "Ubuntu") {
            Boot_Stanza_GUI.append("\nmenuentry \"Ubuntu\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/ubuntu/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "CentOS") {
            Boot_Stanza_GUI.append("\nmenuentry \"CentOS\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/CentOS/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Debian") {
            Boot_Stanza_GUI.append("\nmenuentry \"Debian\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/debian/grubx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Elementary") {
            Boot_Stanza_GUI.append("\nmenuentry \"Elementary\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/elementary/grubx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Fedora") {
            Boot_Stanza_GUI.append("\nmenuentry \"Fedora\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/fedora/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Kali") {
            Boot_Stanza_GUI.append("\nmenuentry \"Kali\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/kali/grubx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "KDE Neon") {
            Boot_Stanza_GUI.append("\nmenuentry \"KDE Neon\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/neon/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Manjaro") {
            Boot_Stanza_GUI.append("\nmenuentry \"Manjaro\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/manjaro/grubx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Mint") {
            Boot_Stanza_GUI.append("\nmenuentry \"Mint\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/ubuntu/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "openSUSE") {
            Boot_Stanza_GUI.append("\nmenuentry \"openSUSE\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/opensuse/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Pop!_OS") {
            Boot_Stanza_GUI.append("\nmenuentry \"Pop!_OS\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/ubuntu/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
        if(Linux_Select_str == "Zorin") {
            Boot_Stanza_GUI.append("\nmenuentry \"Zorin\" {\n");
            Boot_Stanza_GUI.append("\ticon /EFI/refind/os_icon");
            Boot_Stanza_GUI.append(BootNum);
            Boot_Stanza_GUI.append(".png\n");
            Boot_Stanza_GUI.append("\tloader /EFI/ubuntu/shimx64.efi\n");
            Boot_Stanza_GUI.append("\tgraphics on\n}\n");
            return Boot_Stanza_GUI;
        }
    }
    if(BootOption == "None") {
        return Boot_Stanza_GUI;
    }
    return Boot_Stanza_GUI;
}

string MainWindow::getDefaultBoot(QString &DefaultBootOption, bool Last_OS, bool FW_BootNum_boot_bool, QString &Boot_Opt1, QString &Boot_Opt2, QString &Boot_Opt3, QString &Boot_Opt4)
{
    default_OS_sel.clear();
    Boot_Opt1_str = Boot_Opt1.toStdString();
    Boot_Opt2_str = Boot_Opt2.toStdString();
    Boot_Opt3_str = Boot_Opt3.toStdString();
    Boot_Opt4_str = Boot_Opt4.toStdString();
    if(Last_OS){
        default_OS_sel.append("+,");
    }
    if(DefaultBootOption == "SteamOS") {
        if(FW_BootNum_boot_bool) {
            if(Boot_Opt1_str == "SteamOS"){
                default_OS_sel.append("1");
                return default_OS_sel;
            }
            if(Boot_Opt2_str == "SteamOS"){
                default_OS_sel.append("2");
                return default_OS_sel;
            }
            if(Boot_Opt3_str == "SteamOS"){
                default_OS_sel.append("3");
                return default_OS_sel;
            }
            if(Boot_Opt4_str == "SteamOS"){
                default_OS_sel.append("4");
                return default_OS_sel;
            }
        }
        else {
            default_OS_sel.append("steam");
            return default_OS_sel;
        }

    }
    if(DefaultBootOption == "Windows") {
        default_OS_sel.append("Microsoft");
        return default_OS_sel;
    }
    if(DefaultBootOption == "Linux") {
        if(Boot_Opt1_str == "Linux"){
            default_OS_sel.append("1");
            return default_OS_sel;
        }
        if(Boot_Opt2_str == "Linux"){
            default_OS_sel.append("2");
            return default_OS_sel;
        }
        if(Boot_Opt3_str == "Linux"){
            default_OS_sel.append("3");
            return default_OS_sel;
        }
        if(Boot_Opt4_str == "Linux"){
            default_OS_sel.append("4");
            return default_OS_sel;
        }
    }
    return default_OS_sel;
}

string MainWindow::getPartitionGUIDLabel(string &GUID_Source){
    FILE *GUID_process;
    char GUID_buff[1024];
    GUID_Label.clear();
    if(GUID_Source == "USB"){
        GUID_process = popen("hwinfo --block | grep /dev/sda1 | grep -o 'by-partuuid.*' | cut -f2 -d'/' | cut -f1 -d ','", "r");
    }
    if(GUID_Source == "SD"){
        GUID_process = popen("hwinfo --block | grep /dev/mmcblk0p1 | grep -o 'by-partuuid.*' | cut -f2 -d'/' | cut -f1 -d ','", "r");
    }
    if (GUID_process != NULL) {
        while (fgets(GUID_buff, sizeof(GUID_buff), GUID_process)) {
            printf("%s", GUID_buff);
            GUID_Label += GUID_buff;
        }
        pclose(GUID_process);
    }
    return GUID_Label;
}