#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QtGui/QDialog>
#include "thread.h"
#include <QMultiMap>

namespace Ui {
    class KeyBoard;
}

class KeyBoard : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBoard(QWidget *parent = 0);
    ~KeyBoard();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KeyBoard *ui;
    unsigned char page_multiple;   //中文输入时翻页的页数
    struct input_info
    {
        QString input_buf;  //输入的缓存内容
        unsigned char input_length;//输入的长度
    }input_info;

    struct keyboard_style   //键盘风格
    {
        bool caps;          //大小写标志,0小写,1大写
        bool pinyin;        //中英文标志,0英文输入,1中文输入
    }keyboard_style;
    QMultiMap<QString,QString> pinyin_map;  //存放中文字库
    //开辟新线程必须new一个对象(即放在堆上),放在栈上一样会卡
    Thread* keyboard_thread;    //新线程,用于读文件加载中文字库
    bool has_load_font_library; //是否已经加载中文字库的flag
    QVector<QPushButton*>  chinese_btn;     //中文备选汉字

public:
    inline QString GetInputBuf(){return input_info.input_buf;}  //内联函数,返回键盘的输入结果
    void SetLineEditEchoMode();     //输入密码时,使输入内容为小黑点
    void KeyboardInputCharacter(char c);    //接收键盘每次输入的一个字符
    void KeyboardLoadChinese(const QString& str);  //根据字符串(键)索引汉字(值)
    char GetInputLength();      //输入的长度,预留
    void SetKeyboardStyleCapital(bool caps);    //切换键盘按键的大小写风格
    void ShowChineseButton(bool pinyin);    //显示汉字备选字,共8个备选字
    void InputChinese(const QString& ch);  //中文输入时,除去输入框中的英文(键)

private slots:
  //  void on_pushButton_tab_clicked();
 //   void on_symbolBtn_12_clicked();
//    void on_symbolBtn_11_clicked();
//    void on_symbolBtn_10_clicked();
//    void on_symbolBtn_9_clicked();
//    void on_symbolBtn_8_clicked();
//    void on_symbolBtn_7_clicked();
//    void on_symbolBtn_6_clicked();
//    void on_symbolBtn_5_clicked();
//    void on_symbolBtn_4_clicked();
//    void on_symbolBtn_3_clicked();
//    void on_symbolBtn_2_clicked();
//    void on_symbolBtn_1_clicked();
//    void on_symbolBtn_0_clicked();
//    void on_pushButton_shift0_clicked();
//    void on_pushButton_shift9_clicked();
//    void on_pushButton_shift8_clicked();
//    void on_pushButton_shift7_clicked();
//    void on_pushButton_shift6_clicked();
//    void on_pushButton_shift5_clicked();
//    void on_pushButton_shift4_clicked();
//    void on_pushButton_shift3_clicked();
//    void on_pushButton_shift2_clicked();
//    void on_pushButton_shift1_clicked();
//    void on_pushButton_shift_clicked();
//    void on_symbolBtn_add_clicked();
//    void on_symbolBtn_mult_clicked();
//    void on_symbolBtn_div_clicked();
//    void on_symbolBtn_equal_clicked();
    void on_pushBtn_CH8_clicked();
    void on_pushBtn_CH7_clicked();
    void on_pushBtn_CH6_clicked();
    void on_pushBtn_CH5_clicked();
    void on_pushBtn_CH4_clicked();
    void on_pushBtn_CH3_clicked();
    void on_pushBtn_CH2_clicked();
    void on_pushBtn_CH1_clicked();
    void on_pushBtn_pagedown_clicked();
    void on_pushBtn_pageup_clicked();
    void on_pushBtn_CH_ENG_clicked();
    void on_pushButton_caps_clicked();
 //   void on_symbolBtn_sub_clicked();
   // void on_pushButton_kong_clicked();
    void on_pushButton_m_clicked();
    void on_pushButton_n_clicked();
    void on_pushButton_b_clicked();
    void on_pushButton_v_clicked();
    void on_pushButton_c_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_z_clicked();
    void on_pushButton_l_clicked();
    void on_pushButton_k_clicked();
    void on_pushButton_j_clicked();
    void on_pushButton_h_clicked();
    void on_pushButton_g_clicked();
    void on_pushButton_f_clicked();
    void on_pushButton_d_clicked();
    void on_pushButton_s_clicked();
    void on_pushButton_a_clicked();
    void on_pushButton_p_clicked();
    void on_pushButton_o_clicked();
    void on_pushButton_i_clicked();
    void on_pushButton_u_clicked();
    void on_pushButton_y_clicked();
    void on_pushButton_t_clicked();
    void on_pushButton_r_clicked();
    void on_pushButton_e_clicked();
    void on_pushButton_w_clicked();
    void on_pushButton_q_clicked();
  //  void on_pushButton_sub_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_yes_clicked();
    void ReceiveFontMap(const QMultiMap<QString,QString>& map);
    //void on_pushButton_kong_clicked();
   // void on_pushBtn_cancel_clicked();

};

#endif // KEYBOARD_H
