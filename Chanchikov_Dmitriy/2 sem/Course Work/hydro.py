import subprocess
subprocess.run(["pyuic5", "-x", "version2.ui", "-o", "version2.py"])
subprocess.run(["pyuic5", "-x", "version2(1).ui", "-o", "version21.py"])
subprocess.run(["pyuic5", "-x", "version2(2).ui", "-o", "version22.py"])
subprocess.run(["pyuic5", "-x", "version2(3).ui", "-o", "version23.py"])

import math
from PyQt5 import QtCore
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap, QIcon
from PyQt5.QtWidgets import QApplication, QMainWindow, QDialog, QAction
from version2 import Ui_MainWindow
from version21 import Ui_NewWindow
from version22 import Ui_Error
from version23 import Ui_Warning

class MainWindow(QMainWindow, Ui_MainWindow):
    # Конструктор класса
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # Импрот и установка иконки
        self.setWindowIcon(QIcon('icons8-pipes-96.png'))

        # Импорт и установка чертежа
        self.label_chert.setPixmap(QPixmap("uzel_2.png"))
        self.label_chert.setScaledContents(True)

        # Установка фокуса на первом элементе (значении)
        self.setFocus()
        self.doubleSpinBox_chastota.setFocus()


        # Словарь названий и значений
        self.var_dict = {"chastota": 0, "lin_skoroct": 0, "davlenie": 0, "nach_temp": 0, "konech_temp": 0,
                         "rashod_vody": 0, "moshnoct_tepl": 0, "temp_uplotn_n_P": 0, "temp_uplotn_Kst_Kupl": 0,
                         "temp_uplotn_V_P_Dpr_Lpr": 0, "diam_nar": 0, "diam_vnutr": 0, "diam_priv": 0,
                         "dlina_uplotn": 0, "dlina_otv": 0, "dlina_priv": 0, "sheroh": 0,
                         "tepl_stali": 0, "tepl_uplotn": 0, "trenie_uplotn": 0}

        # Частота и лин. скорость не могут быть выбраны одновременно (но могут быть не выбраны одновременно)
        self.checkBox_chastota.clicked.connect(lambda: self.change_with_element(self.checkBox_lin_skoroct))
        self.checkBox_lin_skoroct.clicked.connect(lambda: self.change_with_element(self.checkBox_chastota))

        # При изменении шероховатости устанавливается флажок в коэфф. трения и наоборот
        self.checkBox_sheroh.clicked.connect(lambda state: self.change_flag(state, self.checkBox_trenie_uplotn))
        self.checkBox_trenie_uplotn.clicked.connect(lambda state: self.change_flag(state, self.checkBox_sheroh))

        # Следующие величины не могут быть отмечены флажками
        self.checkBox_nach_temp.clicked.connect(lambda: self.checkBox_nach_temp.setCheckState(QtCore.Qt.Unchecked))
        self.checkBox_konech_temp.clicked.connect(lambda: self.checkBox_konech_temp.setCheckState(QtCore.Qt.Unchecked))
        self.checkBox_dlina_uplotn.clicked.connect(lambda: self.checkBox_dlina_uplotn.setCheckState(QtCore.Qt.Unchecked))
        self.checkBox_dlina_otv.clicked.connect(lambda: self.checkBox_dlina_otv.setCheckState(QtCore.Qt.Unchecked))
        self.checkBox_tepl_stali.clicked.connect(lambda: self.checkBox_tepl_stali.setCheckState(QtCore.Qt.Unchecked))
        self.checkBox_tepl_uplotn.clicked.connect(lambda: self.checkBox_tepl_uplotn.setCheckState(QtCore.Qt.Unchecked))

        # Следующие величины отмечены флажками, которые нельзя снять
        self.checkBox_rashod_vody.clicked.connect(lambda: self.checkBox_rashod_vody.setCheckState(QtCore.Qt.Checked))
        self.checkBox_moshnoct_tepl.clicked.connect(lambda: self.checkBox_moshnoct_tepl.setCheckState(QtCore.Qt.Checked))
        self.checkBox_temp_uplotn_n_P.clicked.connect(lambda: self.checkBox_temp_uplotn_n_P.setCheckState(QtCore.Qt.Checked))
        self.checkBox_temp_uplotn_Kst_Kupl.clicked.connect(lambda: self.checkBox_temp_uplotn_Kst_Kupl.setCheckState(QtCore.Qt.Checked))
        self.checkBox_temp_uplotn_V_P_Dpr_Lpr.clicked.connect(lambda: self.checkBox_temp_uplotn_V_P_Dpr_Lpr.setCheckState(QtCore.Qt.Checked))
        self.checkBox_diam_priv.clicked.connect(lambda: self.checkBox_diam_priv.setCheckState(QtCore.Qt.Checked))
        self.checkBox_dlina_priv.clicked.connect(lambda: self.checkBox_dlina_priv.setCheckState(QtCore.Qt.Checked))

        # При установке флажка название и значение становятся не активными, при снятии наоборот
        for name, var in self.var_dict.items():
            self.connect_checkbox(name)

        # Создаем экземпляр нового окна
        self.new_window = NewWindow(self)

        # Создаем экземпляр диалогового окна
        self.error = Error(self)

        # Создаем экземпляр диалогового окна
        self.warning = Warning(self)

        # При нажатии на кнопку запускается функция для расчета
        self.pushButton_calculate.clicked.connect(self.calculate)


    # Функция для снятия флажка с переданного элемента (если на нем стоит флажок, то он снимается)
    def change_with_element(self, element):
        if element.isChecked():
            element.setChecked(False)

    # Функция для смены установки флажков (RadioButton)
    def change_flag(self, state, element):
        element.setChecked(not state)

    # Функция для связи события и действия по названию
    def connect_checkbox(self, name):
        checkbox = getattr(self, f"checkBox_{name}")
        label = getattr(self, f"label_{name}")
        spinbox = getattr(self, f"doubleSpinBox_{name}")
        checkbox.stateChanged.connect(lambda state: self.set_elements_disenabled(state, label, spinbox))

    # Функция для смены активности элементов (1 - не акт, 0 - акт)
    def set_elements_disenabled(self, state, *elements):
        for element in elements:
            element.setEnabled(not state)

    # Функция для получения значений из активных элементов
    def get_value_if_element_enabled(self):
        result_dict = {}
        for name, var in self.var_dict.items():
            if getattr(self, f"doubleSpinBox_{name}").isEnabled():
                var = getattr(self, f"doubleSpinBox_{name}").value()
            else:
                var = 0
            result_dict[name] = var
        return result_dict

    # Функция для расчета и вывода в новое окно
    def calculate(self):

        # Обновление словаря
        updated_dict = self.get_value_if_element_enabled()
        self.var_dict.update(updated_dict)

        # Рассчет параметров переменной активности
        if self.var_dict["davlenie"] != 0:
            t = 4.8 * math.exp(0.0161 * self.var_dict["davlenie"])  # Толщина стенки через давление
            if (self.var_dict["chastota"] != 0 and self.var_dict["lin_skoroct"] == 0) or \
                    (self.var_dict["chastota"] == 0 and self.var_dict["lin_skoroct"] != 0):
                if self.var_dict["diam_nar"] != 0:
                    if self.var_dict["diam_vnutr"] != 0:
                        self.warning.label_0.setText(self.label_diam_vnutr.text())
                        self.warning.exec_()
                    self.var_dict["diam_vnutr"] = self.var_dict["diam_nar"] - 2 * t
                elif self.var_dict["diam_nar"] == 0 and self.var_dict["diam_vnutr"] != 0:
                    self.var_dict["diam_nar"] = self.var_dict["diam_vnutr"] + 2 * t
                else:
                    self.error.label_0.setText(self.label_diam_nar.text())
                    self.error.label_1.setText(self.label_diam_vnutr.text())
                    if self.var_dict["lin_skoroct"] == 0: self.error.label_2.setText(self.label_lin_skoroct.text())
                    elif self.var_dict["chastota"] == 0: self.error.label_2.setText(self.label_chastota.text())
                    self.error.label_or.setVisible(True)
                    self.error.checkBox_2.setVisible(True)
                    self.error.exec_()
                    return
                if self.var_dict["lin_skoroct"] == 0:
                    self.var_dict["lin_skoroct"] = math.pi * self.var_dict["diam_nar"] * self.var_dict["chastota"] / (60000)
                elif self.var_dict["chastota"] == 0:
                    self.var_dict["chastota"] = 60000 * self.var_dict["lin_skoroct"] / (math.pi * self.var_dict["diam_nar"])
            else:
                if self.var_dict["diam_nar"] == 0 and self.var_dict["diam_vnutr"] == 0:
                    self.var_dict["diam_nar"] = 60000 * self.var_dict["lin_skoroct"] / (math.pi * self.var_dict["chastota"])
                else:
                    if self.var_dict["diam_nar"] != 0:
                        self.warning.label_0.setText(self.label_lin_skoroct.text())
                        self.warning.exec_()
                    if self.var_dict["diam_vnutr"] != 0:
                        self.warning.label_0.setText(self.label_diam_vnutr.text())
                        self.warning.exec_()
                    self.var_dict["lin_skoroct"] = math.pi * self.var_dict["diam_nar"] * self.var_dict["chastota"] / (60000)
                self.var_dict["diam_vnutr"] = self.var_dict["diam_nar"] - 2 * t
        else:
            if (self.var_dict["chastota"] != 0 and self.var_dict["lin_skoroct"] == 0) or \
                    (self.var_dict["chastota"] == 0 and self.var_dict["lin_skoroct"] != 0):
                if self.var_dict["diam_nar"] != 0 and self.var_dict["diam_vnutr"] != 0:
                    t = self.var_dict["diam_nar"] - self.var_dict["diam_vnutr"]  # Толщина стенки через разность диаметров
                    self.var_dict["davlenie"] = math.log2(t / (2 * 4.8)) / 0.0161
                else:
                    if self.var_dict["diam_nar"] == 0:
                        self.error.label_0.setText(self.label_davlenie.text())
                        self.error.label_1.setText(self.label_diam_nar.text())
                        if self.var_dict["lin_skoroct"] == 0: self.error.label_2.setText(self.label_lin_skoroct.text())
                        elif self.var_dict["chastota"] == 0: self.error.label_2.setText(self.label_chastota.text())
                        self.error.label_or.setVisible(True)
                        self.error.checkBox_2.setVisible(True)
                        self.error.exec_()
                        return
                    if self.var_dict["diam_vnutr"] == 0:
                        self.error.label_0.setText(self.label_davlenie.text())
                        self.error.label_1.setText(self.label_diam_vnutr.text())
                        self.error.label_2.setText('')
                        self.error.label_or.setVisible(False)
                        self.error.checkBox_2.setVisible(False)
                        self.error.exec_()
                        return
            else:
                if self.var_dict["diam_vnutr"] != 0:
                    if self.var_dict["diam_nar"] == 0:
                        self.var_dict["diam_nar"] = 60000 * self.var_dict["lin_skoroct"] \
                                                    / (math.pi * self.var_dict["chastota"])
                    else:
                        self.warning.label_0.setText(self.label_lin_skoroct.text())
                        self.warning.exec_()
                        self.var_dict["lin_skoroct"] = math.pi * self.var_dict["diam_nar"] \
                                                       * self.var_dict["chastota"] / (60000)
                    t = self.var_dict["diam_nar"] - self.var_dict["diam_vnutr"]  # Толщина стенки через разность диаметров
                    if t > 0: self.var_dict["davlenie"] = math.log2(t / (2 * 4.8)) / 0.0161
                    else: self.var_dict["davlenie"] = 0
                else:
                    self.error.label_0.setText(self.label_davlenie.text())
                    self.error.label_1.setText(self.label_diam_vnutr.text())
                    self.error.label_2.setText('')
                    self.error.label_or.setVisible(False)
                    self.error.checkBox_2.setVisible(False)
                    self.error.exec_()
                    return
        if self.var_dict["sheroh"] != 0:
            self.var_dict["trenie_uplotn"] = 0.15 * math.log2(self.var_dict["sheroh"]) + 0.7
            print('')
        else:
            self.var_dict["sheroh"] = math.exp((self.var_dict["trenie_uplotn"] - 0.7) / 0.15)
            print('')

        # Рассчет остальных параметров
        self.var_dict["diam_priv"] = self.var_dict["diam_vnutr"] / self.var_dict["diam_nar"]
        self.var_dict["dlina_priv"] = self.var_dict["dlina_otv"] / self.var_dict["dlina_uplotn"]
        self.var_dict["rashod_vody"] = 5 * self.var_dict["trenie_uplotn"] \
                        * math.pow(self.var_dict["lin_skoroct"], 1.418) * math.pow(self.var_dict["davlenie"], 0.843) \
                        * math.pow(self.var_dict["nach_temp"], 0.253) / math.pow(self.var_dict["konech_temp"], 1.282)
        self.var_dict["moshnoct_tepl"] = 4.25 * math.pow(self.var_dict["lin_skoroct"], 0.576) \
                        * math.pow(self.var_dict["trenie_uplotn"], 0.876) * math.pow(self.var_dict["davlenie"], 0.783)
        self.var_dict["temp_uplotn_n_P"] = 3 * math.pow(self.var_dict["chastota"], 0.514) \
                                             * math.pow(self.var_dict["davlenie"], 0.639)
        self.var_dict["temp_uplotn_Kst_Kupl"] = 6722 * math.pow(self.var_dict["tepl_uplotn"], 0.0027) \
                                             / math.pow(self.var_dict["tepl_stali"], 0.96)
        self.var_dict["temp_uplotn_V_P_Dpr_Lpr"] = \
                    130 * math.pow(self.var_dict["davlenie"], 0.59) * math.pow(self.var_dict["lin_skoroct"], 0.445) \
                        * math.pow(self.var_dict["diam_priv"], 0.12) * math.pow(self.var_dict["dlina_priv"], 1.08)

        # Выгрузка значений в новое окно и его вывод
        self.new_window.set_value_and_change_enable(self.var_dict)
        self.new_window.show()


class NewWindow(QMainWindow, Ui_NewWindow):
    # Конструктор класса
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window  # Сохранение ссылки на MainWindow
        self.setupUi(self)

    # Функция для вывода значений в новое окно
    def set_value_and_change_enable(self, values_dict):
        for name, value in values_dict.items():
            label = getattr(self, f"label_{name}")
            doubleSpinBox = getattr(self, f"doubleSpinBox_{name}")
            enable = getattr(self.main_window, f"doubleSpinBox_{name}").isEnabled()
            label.setEnabled(not enable)
            doubleSpinBox.setEnabled(not enable)
            getattr(self, f"doubleSpinBox_{name}").setValue(value)

class Error(QDialog, Ui_Error):
    # Конструктор класса
    def __init__(self, parent=None):
        super(Error, self).__init__(parent)
        self.setupUi(self)

        self.checkBox_2.setVisible(False)
        self.checkBox_3.setVisible(False)
        self.checkBox_0.clicked.connect(lambda: self.checkBox_0.setCheckState(QtCore.Qt.Checked))

class Warning(QDialog, Ui_Warning):
    # Конструктор класса
    def __init__(self, parent=None):
        super(Warning, self).__init__(parent)
        self.setupUi(self)

        #self.buttonBox.button(self.buttonBox.Cancel).clicked.connect(self.reject)

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()

