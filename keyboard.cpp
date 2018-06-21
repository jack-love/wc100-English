/***********************************************************
************************************************************
************************************************************
*文件名：      keyboard.cpp
*
*作者：        jegbrother
*
*日期：        2017-05-22
*
*版本：        V1.0
*
*说明：        软键盘
*
*修改记录：
************************************************************
************************************************************
************************************************************/

#include "keyboard.h"
#include "ui_keyboard.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QMetaType>
#include <QFile>

KeyBoard::KeyBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBoard)
{
    ui->setupUi(this);
    page_multiple = 0;    
    keyboard_style.caps = false;
    keyboard_style.pinyin = false;
    has_load_font_library = false;
    input_info.input_length = 0;
    ShowChineseButton(false);
    chinese_btn.push_back(ui->pushBtn_CH1);
    chinese_btn.push_back(ui->pushBtn_CH2);
    chinese_btn.push_back(ui->pushBtn_CH3);
    chinese_btn.push_back(ui->pushBtn_CH4);
    chinese_btn.push_back(ui->pushBtn_CH5);
    chinese_btn.push_back(ui->pushBtn_CH6);
    chinese_btn.push_back(ui->pushBtn_CH7);
    chinese_btn.push_back(ui->pushBtn_CH8);
    qRegisterMetaType< QMultiMap<QString,QString> >("QMultiMap<QString,QString>");//注册QMultiMap<QString,QString>类型,用于多线程间的数据交换
    //开辟新线程必须new一个对象(即放在堆上),放在栈上一样会卡
    keyboard_thread = new Thread(); //只有new 没有delete
    connect(keyboard_thread,SIGNAL(SendFontMap(QMultiMap<QString,QString>)),this,SLOT(ReceiveFontMap(QMultiMap<QString,QString>)));
}

KeyBoard::~KeyBoard()
{
    delete ui;
}

void KeyBoard::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void KeyBoard::ReceiveFontMap(const QMultiMap<QString,QString>& map)
{
    pinyin_map = map;
}

void KeyBoard::KeyboardInputCharacter(char c)
{
    if(c>=97 && c<=122 && keyboard_style.caps==true)       //ASCII码97-122且大写开启
        c-=32;                                             //小写转换为大写
    input_info.input_buf = ui->lineEdit_keyboard->text();  //获取输入框中的内容
    unsigned char pos = ui->lineEdit_keyboard->cursorPosition();     //获取当前光标所在位置
    input_info.input_buf.insert(pos,c);                    //把字符c接到input_info.input_buf中
    ui->lineEdit_keyboard->setText(input_info.input_buf);  //显示
    ui->lineEdit_keyboard->setCursorPosition(pos+1);       //将光标向后移动一位

    if(keyboard_style.pinyin==true)               //如果是中文输入风格
    {
        page_multiple = 0;                          //重置翻页页码
        unsigned char current_frame = input_info.input_buf.indexOf(QRegExp("([a-z])"));    //正则表达式查找小写字母
        input_info.input_buf.remove(0,current_frame);   //移除中文汉字
        KeyboardLoadChinese(input_info.input_buf);      //加载汉字
    }
}

void KeyBoard::KeyboardLoadChinese(const QString& str)
{
    QList<QString> pinyin_list = pinyin_map.values(str);    //匹配拼音对应的汉字
    short count = pinyin_list.size()-1;   //索引从0计数,以count作为数组下标时,必须减1防止越界
    if(count<0){ui->label_tips->setText(tr("未检索到汉字\n请检查拼写结果"));}
    else{ui->label_tips->setText(tr("中文输入中..."));}
    if(count>8){ui->pushBtn_pagedown->setHidden(false);}    //超过8个候选字则激活"下一页"按钮
    else{ui->pushBtn_pagedown->setHidden(true);}
    if(page_multiple==0){ui->pushBtn_pageup->setHidden(true);}  //初始不显示"上一页"按钮
    if((page_multiple>0)&&(count/(8*(page_multiple+1))==0))     //当"下一页"到底时隐藏按钮
        {ui->pushBtn_pagedown->setHidden(true);}
    for(unsigned char i=0,j=page_multiple*8;i<8;i++,j++)
    {
        chinese_btn.at(i)->setText(tr(pinyin_list.value(count-j).toAscii()));   //显示中文备选汉字
    }
}

void KeyBoard::on_pushBtn_pageup_clicked()  //每次翻页刷新备选汉字
{
    page_multiple -=1;
    KeyboardLoadChinese(input_info.input_buf);
}

void KeyBoard::on_pushBtn_pagedown_clicked()
{
    page_multiple +=1;
    KeyboardLoadChinese(input_info.input_buf);
    ui->pushBtn_pageup->setHidden(false);
}

void KeyBoard::on_pushButton_back_clicked()
{
    input_info.input_buf = ui->lineEdit_keyboard->text();
    unsigned char pos = ui->lineEdit_keyboard->cursorPosition();   //获取光标所在位置
    if(input_info.input_buf.size()>0 && pos>0)
    {
        input_info.input_buf.remove(pos-1,1);
        ui->lineEdit_keyboard->setText(input_info.input_buf);
        ui->lineEdit_keyboard->setCursorPosition(pos-1); //设定光标的位置
    }

    if(input_info.input_buf.size()>0 && keyboard_style.pinyin == true)   //中文输入风格时刷新备选汉字
    {
        page_multiple = 0;
        unsigned char current_frame = input_info.input_buf.indexOf(QRegExp("([a-z])"));    //正则表达式查找小写字母
        input_info.input_buf.remove(0,current_frame);   //移除中文汉字
        KeyboardLoadChinese(input_info.input_buf);
    }
}

void KeyBoard::on_pushButton_yes_clicked()
{
    input_info.input_buf = ui->lineEdit_keyboard->text();
    ui->lineEdit_keyboard->clear();
    accept();
}

char KeyBoard::GetInputLength()
{
    input_info.input_length = input_info.input_buf.size();
    return input_info.input_length;
}


void KeyBoard::on_pushButton_caps_clicked()
{
    if(keyboard_style.caps == false)
    {
        keyboard_style.caps = true;
        SetKeyboardStyleCapital(keyboard_style.caps);
    }
    else if(keyboard_style.caps == true)
    {
        keyboard_style.caps = false;
        SetKeyboardStyleCapital(keyboard_style.caps);
    }
}

void KeyBoard::SetKeyboardStyleCapital(bool caps)
{
    if(caps == true)
    {
        ui->pushButton_caps->setStyleSheet("background-color:rgb(0,255,127)");
        ui->pushButton_q->setText("Q");
        ui->pushButton_w->setText("W");
        ui->pushButton_e->setText("E");
        ui->pushButton_r->setText("R");
        ui->pushButton_t->setText("T");
        ui->pushButton_y->setText("Y");
        ui->pushButton_u->setText("U");
        ui->pushButton_i->setText("I");
        ui->pushButton_o->setText("O");
        ui->pushButton_p->setText("P");
        ui->pushButton_a->setText("A");
        ui->pushButton_s->setText("S");
        ui->pushButton_d->setText("D");
        ui->pushButton_f->setText("F");
        ui->pushButton_g->setText("G");
        ui->pushButton_h->setText("H");
        ui->pushButton_j->setText("J");
        ui->pushButton_k->setText("K");
        ui->pushButton_l->setText("L");
        ui->pushButton_z->setText("Z");
        ui->pushButton_x->setText("X");
        ui->pushButton_c->setText("C");
        ui->pushButton_v->setText("V");
        ui->pushButton_b->setText("B");
        ui->pushButton_n->setText("N");
        ui->pushButton_m->setText("M");
    }
    else if(caps == false)
    {
        ui->pushButton_caps->setStyleSheet("background-color:rgb(170,170,127)");
        ui->pushButton_q->setText("q");
        ui->pushButton_w->setText("w");
        ui->pushButton_e->setText("e");
        ui->pushButton_r->setText("r");
        ui->pushButton_t->setText("t");
        ui->pushButton_y->setText("y");
        ui->pushButton_u->setText("u");
        ui->pushButton_i->setText("i");
        ui->pushButton_o->setText("o");
        ui->pushButton_p->setText("p");
        ui->pushButton_a->setText("a");
        ui->pushButton_s->setText("s");
        ui->pushButton_d->setText("d");
        ui->pushButton_f->setText("f");
        ui->pushButton_g->setText("g");
        ui->pushButton_h->setText("h");
        ui->pushButton_j->setText("j");
        ui->pushButton_k->setText("k");
        ui->pushButton_l->setText("l");
        ui->pushButton_z->setText("z");
        ui->pushButton_x->setText("x");
        ui->pushButton_c->setText("c");
        ui->pushButton_v->setText("v");
        ui->pushButton_b->setText("b");
        ui->pushButton_n->setText("n");
        ui->pushButton_m->setText("m");
    }
}

void KeyBoard::on_pushBtn_CH_ENG_clicked()
{
    if(has_load_font_library == false)
    {
        has_load_font_library = true;
        //在新线程中加载字库,并用信号和槽的方式将新线程中的字库Map传递到UI线程
        keyboard_thread->start();
    }

    keyboard_style.caps = false;
    if(keyboard_style.pinyin == false)
    {
        input_info.input_buf.clear();
        ui->lineEdit_keyboard->clear();
        keyboard_style.pinyin = true;
        SetKeyboardStyleCapital(false);
        ShowChineseButton(true);
        ui->pushButton_caps->setDisabled(true);
        ui->label_tips->setText(tr("中文输入中..."));
    }
    else if(keyboard_style.pinyin == true)
    {
        keyboard_style.pinyin = false;
        ShowChineseButton(false);
        ui->pushButton_caps->setDisabled(false);
        ui->label_tips->setText(tr("英文输入中..."));
    }

}

void KeyBoard::ShowChineseButton(bool pinyin)
{
    if(pinyin == true)
    {
        ui->pushBtn_CH1->setHidden(false);
        ui->pushBtn_CH2->setHidden(false);
        ui->pushBtn_CH3->setHidden(false);
        ui->pushBtn_CH4->setHidden(false);
        ui->pushBtn_CH5->setHidden(false);
        ui->pushBtn_CH6->setHidden(false);
        ui->pushBtn_CH7->setHidden(false);
        ui->pushBtn_CH8->setHidden(false);
    }
    else if(pinyin == false)
    {
        ui->pushBtn_CH1->setHidden(true);
        ui->pushBtn_CH2->setHidden(true);
        ui->pushBtn_CH3->setHidden(true);
        ui->pushBtn_CH4->setHidden(true);
        ui->pushBtn_CH5->setHidden(true);
        ui->pushBtn_CH6->setHidden(true);
        ui->pushBtn_CH7->setHidden(true);
        ui->pushBtn_CH8->setHidden(true);
        ui->pushBtn_pageup->setHidden(true);
        ui->pushBtn_pagedown->setHidden(true);
    }
}

void KeyBoard::InputChinese(const QString& ch)
{
    QString str = ui->lineEdit_keyboard->text();    //获取输入框中的内容
    if(str.contains(QRegExp("([a-z])")))            //如果包含英文字母
        input_info.input_buf = str.replace(input_info.input_buf,"");    //移除英文
//    quint8 i = input_info.input_buf.indexOf(QRegExp("([a-z])"));
//    if(str.contains(QRegExp("([a-z])")))
//        input_info.input_buf.remove(i,input_info.input_buf.size()-i);
    input_info.input_buf += ch;                  //获取备选汉字
    ui->lineEdit_keyboard->setText(input_info.input_buf);           //显示
}

void KeyBoard::SetLineEditEchoMode()
{
    ui->lineEdit_keyboard->setEchoMode(QLineEdit::Password);
}

void KeyBoard::on_pushButton_1_clicked(){KeyboardInputCharacter('1');}

void KeyBoard::on_pushButton_2_clicked(){KeyboardInputCharacter('2');}

void KeyBoard::on_pushButton_3_clicked(){KeyboardInputCharacter('3');}

void KeyBoard::on_pushButton_4_clicked(){KeyboardInputCharacter('4');}

void KeyBoard::on_pushButton_5_clicked(){KeyboardInputCharacter('5');}

void KeyBoard::on_pushButton_6_clicked(){KeyboardInputCharacter('6');}

void KeyBoard::on_pushButton_7_clicked(){KeyboardInputCharacter('7');}

void KeyBoard::on_pushButton_8_clicked(){KeyboardInputCharacter('8');}

void KeyBoard::on_pushButton_9_clicked(){KeyboardInputCharacter('9');}

void KeyBoard::on_pushButton_0_clicked(){KeyboardInputCharacter('0');}

void KeyBoard::on_pushButton_q_clicked(){KeyboardInputCharacter('q');}

void KeyBoard::on_pushButton_w_clicked(){KeyboardInputCharacter('w');}

void KeyBoard::on_pushButton_e_clicked(){KeyboardInputCharacter('e');}

void KeyBoard::on_pushButton_r_clicked(){KeyboardInputCharacter('r');}

void KeyBoard::on_pushButton_t_clicked(){KeyboardInputCharacter('t');}

void KeyBoard::on_pushButton_y_clicked(){KeyboardInputCharacter('y');}

void KeyBoard::on_pushButton_u_clicked(){KeyboardInputCharacter('u');}

void KeyBoard::on_pushButton_i_clicked(){KeyboardInputCharacter('i');}

void KeyBoard::on_pushButton_o_clicked(){KeyboardInputCharacter('o');}

void KeyBoard::on_pushButton_p_clicked(){KeyboardInputCharacter('p');}

void KeyBoard::on_pushButton_a_clicked(){KeyboardInputCharacter('a');}

void KeyBoard::on_pushButton_s_clicked(){KeyboardInputCharacter('s');}

void KeyBoard::on_pushButton_d_clicked(){KeyboardInputCharacter('d');}

void KeyBoard::on_pushButton_f_clicked(){KeyboardInputCharacter('f');}

void KeyBoard::on_pushButton_g_clicked(){KeyboardInputCharacter('g');}

void KeyBoard::on_pushButton_h_clicked(){KeyboardInputCharacter('h');}

void KeyBoard::on_pushButton_j_clicked(){KeyboardInputCharacter('j');}

void KeyBoard::on_pushButton_k_clicked(){KeyboardInputCharacter('k');}

void KeyBoard::on_pushButton_l_clicked(){KeyboardInputCharacter('l');}

void KeyBoard::on_pushButton_z_clicked(){KeyboardInputCharacter('z');}

void KeyBoard::on_pushButton_x_clicked(){KeyboardInputCharacter('x');}

void KeyBoard::on_pushButton_c_clicked(){KeyboardInputCharacter('c');}

void KeyBoard::on_pushButton_v_clicked(){KeyboardInputCharacter('v');}

void KeyBoard::on_pushButton_b_clicked(){KeyboardInputCharacter('b');}

void KeyBoard::on_pushButton_n_clicked(){KeyboardInputCharacter('n');}

void KeyBoard::on_pushButton_m_clicked(){KeyboardInputCharacter('m');}

void KeyBoard::on_pushButton_point_clicked(){KeyboardInputCharacter('.');}

//void KeyBoard::on_pushButton_sub_clicked(){KeyboardInputCharacter('_');}
//void KeyBoard::on_pushButton_kong_clicked(){KeyboardInputCharacter(' ');}

void KeyBoard::on_pushButton_clear_clicked(){ui->lineEdit_keyboard->clear();}

void KeyBoard::on_pushBtn_CH1_clicked(){InputChinese(ui->pushBtn_CH1->text());}

void KeyBoard::on_pushBtn_CH2_clicked(){InputChinese(ui->pushBtn_CH2->text());}

void KeyBoard::on_pushBtn_CH3_clicked(){InputChinese(ui->pushBtn_CH3->text());}

void KeyBoard::on_pushBtn_CH4_clicked(){InputChinese(ui->pushBtn_CH4->text());}

void KeyBoard::on_pushBtn_CH5_clicked(){InputChinese(ui->pushBtn_CH5->text());}

void KeyBoard::on_pushBtn_CH6_clicked(){InputChinese(ui->pushBtn_CH6->text());}

void KeyBoard::on_pushBtn_CH7_clicked(){InputChinese(ui->pushBtn_CH7->text());}

void KeyBoard::on_pushBtn_CH8_clicked(){InputChinese(ui->pushBtn_CH8->text());}

//void KeyBoard::on_symbolBtn_equal_clicked(){KeyboardInputCharacter('=');}

//void KeyBoard::on_symbolBtn_div_clicked(){KeyboardInputCharacter('/');}

//void KeyBoard::on_symbolBtn_mult_clicked(){KeyboardInputCharacter('*');}

//void KeyBoard::on_symbolBtn_sub_clicked(){KeyboardInputCharacter('-');}

//void KeyBoard::on_symbolBtn_add_clicked(){KeyboardInputCharacter('+');}

//void KeyBoard::on_pushButton_shift_clicked(){KeyboardInputCharacter('~');}

//void KeyBoard::on_pushButton_shift1_clicked(){KeyboardInputCharacter('!');}

//void KeyBoard::on_pushButton_shift2_clicked(){KeyboardInputCharacter('@');}

//void KeyBoard::on_pushButton_shift3_clicked(){KeyboardInputCharacter('#');}

//void KeyBoard::on_pushButton_shift4_clicked(){KeyboardInputCharacter('$');}

//void KeyBoard::on_pushButton_shift5_clicked(){KeyboardInputCharacter('%');}

//void KeyBoard::on_pushButton_shift6_clicked(){KeyboardInputCharacter('^');}

//void KeyBoard::on_pushButton_shift7_clicked(){KeyboardInputCharacter('&');}

//void KeyBoard::on_pushButton_shift8_clicked(){KeyboardInputCharacter('|');}

//void KeyBoard::on_pushButton_shift9_clicked(){KeyboardInputCharacter('(');}

//void KeyBoard::on_pushButton_shift0_clicked(){KeyboardInputCharacter(')');}

//void KeyBoard::on_symbolBtn_0_clicked(){KeyboardInputCharacter('{');}

//void KeyBoard::on_symbolBtn_1_clicked(){KeyboardInputCharacter('}');}

//void KeyBoard::on_symbolBtn_2_clicked(){KeyboardInputCharacter(39);}

//void KeyBoard::on_symbolBtn_3_clicked(){KeyboardInputCharacter('[');}

//void KeyBoard::on_symbolBtn_4_clicked(){KeyboardInputCharacter(']');}

//void KeyBoard::on_symbolBtn_5_clicked(){KeyboardInputCharacter(':');}

//void KeyBoard::on_symbolBtn_6_clicked(){KeyboardInputCharacter(';');}

//void KeyBoard::on_symbolBtn_7_clicked(){KeyboardInputCharacter('"');}

//void KeyBoard::on_symbolBtn_8_clicked(){KeyboardInputCharacter('<');}

//void KeyBoard::on_symbolBtn_9_clicked(){KeyboardInputCharacter('>');}

//void KeyBoard::on_symbolBtn_10_clicked(){KeyboardInputCharacter(',');}

//void KeyBoard::on_symbolBtn_11_clicked(){KeyboardInputCharacter('?');}

//void KeyBoard::on_symbolBtn_12_clicked(){KeyboardInputCharacter('\\');}

//void KeyBoard::on_pushButton_tab_clicked(){KeyboardInputCharacter(96);}




